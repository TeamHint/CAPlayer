

#include <assert.h>
#include "libavformat/avformat.h"
#include "libavformat/url.h"
#include "libavutil/avstring.h"
#include "libavutil/log.h"
#include "libavutil/opt.h"

#include "caplayer/capavutil/opt.h"
#include "capavformat.h"

typedef struct Context {
    AVClass        *class;
    URLContext     *inner;

    /* options */
    int64_t         opaque;
    int             segment_index;
    int             async_http;
} Context;

static void *capsegment_get_opaque(URLContext *h) {
    Context *c = h->priv_data;
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#endif
    return (void *)c->opaque;
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
}

static int capsegment_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    Context *c = h->priv_data;
    CAPAVInject_OnUrlOpenData inject_data = {0};
    CapAVInjectCallback inject_callback = capav_get_inject_callback();
    int ret = -1;
    void *opaque = capsegment_get_opaque(h);
    assert(opaque);

    if (!c->opaque) {
        av_log(h, AV_LOG_ERROR, "null opaque\n");
        return AVERROR_EXTERNAL;
    }

    if (!inject_callback) {
        av_log(h, AV_LOG_ERROR, "null inject_callback\n");
        return AVERROR_EXTERNAL;
    }

    av_strstart(arg, "capsegment:", &arg);
    if (!arg || !*arg)
        return AVERROR_EXTERNAL;

    inject_data.size = sizeof(inject_data);
    inject_data.segment_index = (int)strtol(arg, NULL, 0);
    strlcpy(inject_data.url,    arg,    sizeof(inject_data.url));

    if (opaque && inject_callback &&
        inject_data.segment_index < 0) {
        ret = AVERROR_EXTERNAL;
        goto fail;
    }

    ret = inject_callback(opaque, CAPAVINJECT_CONCAT_RESOLVE_SEGMENT, &inject_data, sizeof(inject_data));
    if (ret || !inject_data.url[0]) {
        ret = AVERROR_EXIT;
        goto fail;
    }

    av_dict_set_int(options, "capsegment-opaque",        c->opaque, 0);
    av_dict_set_int(options, "capsegment-segment-index", c->segment_index, 0);

    if (av_strstart(inject_data.url, "http://", NULL)) {
        ret = ffurl_open(&c->inner, inject_data.url, flags, &h->interrupt_callback, options);
    } else {
        char async_url[4096] = "async:";
        av_strlcat(async_url, inject_data.url, sizeof(async_url));
        ret = ffurl_open(&c->inner, async_url, flags, &h->interrupt_callback, options);
    }
    if (ret)
        goto fail;

    return 0;
fail:
    return ret;
}

static int capsegment_close(URLContext *h)
{
    Context *c = h->priv_data;

    return ffurl_close(c->inner);
}

static int capsegment_read(URLContext *h, unsigned char *buf, int size)
{
    Context *c = h->priv_data;

    return ffurl_read(c->inner, buf, size);
}

static int64_t capsegment_seek(URLContext *h, int64_t pos, int whence)
{
    Context *c = h->priv_data;

    return ffurl_seek(c->inner, pos, whence);
}

#define OFFSET(x) offsetof(Context, x)
#define D AV_OPT_FLAG_DECODING_PARAM

static const AVOption options[] = {
    { "capinject-opaque",           "private data of user, passed with custom callback",
        OFFSET(opaque),             CAPAV_OPTION_INT64(0, INT64_MIN, INT64_MAX) },
    { "capinject-segment-index",    "segment index of current url",
        OFFSET(segment_index),      CAPAV_OPTION_INT(0, 0, INT_MAX) },
    { "capsegment-async-http",      "add prefix async: to http stream",
        OFFSET(async_http),         CAPAV_OPTION_INT(0, 0, INT_MAX) },
    { NULL }
};

#undef D
#undef OFFSET

static const AVClass capsegment_context_class = {
    .class_name = "Inject",
    .item_name  = av_default_item_name,
    .option     = options,
    .version    = LIBAVUTIL_VERSION_INT,
};

URLProtocol capff_capsegment_protocol = {
    .name                = "capsegment",
    .url_open2           = capsegment_open,
    .url_read            = capsegment_read,
    .url_seek            = capsegment_seek,
    .url_close           = capsegment_close,
    .priv_data_size      = sizeof(Context),
    .priv_data_class     = &capsegment_context_class,
};
