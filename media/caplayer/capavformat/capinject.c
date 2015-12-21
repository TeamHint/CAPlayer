

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
    char           *inner_url;

    /* options */
    int64_t         opaque;
    int             segment_index;
} Context;

#if 0
static void *capinject_get_opaque(URLContext *h) {
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
#endif

static int capinject_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    Context *c = h->priv_data;
    int ret = -1;

    av_strstart(arg, "capinject:", &arg);

    c->inner_url = av_strdup(arg);

    av_dict_set_int(options, "capinject-opaque",        c->opaque, 0);
    av_dict_set_int(options, "capinject-segment-index", c->segment_index, 0);
    ret = ffurl_open(&c->inner, arg, flags, &h->interrupt_callback, options);
    if (ret)
        goto fail;

    return ret;
fail:
    av_freep(&c->inner_url);
    return ret;
}

static int capinject_close(URLContext *h)
{
    Context *c = h->priv_data;

    av_freep(&c->inner_url);

    return ffurl_close(c->inner);
}

static int capinject_read(URLContext *h, unsigned char *buf, int size)
{
    Context *c = h->priv_data;

    return ffurl_read(c->inner, buf, size);
}

static int64_t capinject_seek(URLContext *h, int64_t pos, int whence)
{
    Context *c = h->priv_data;

    return ffurl_seek(c->inner, pos, whence);
}

#define OFFSET(x) offsetof(Context, x)
#define D AV_OPT_FLAG_DECODING_PARAM

static const AVOption options[] = {
    { "capinject-opaque",           "private data of user, passed with custom callback",
        OFFSET(opaque),             CAPAV_OPTION_INT64(0, INT64_MIN, INT64_MAX) },
    { NULL }
};

#undef D
#undef OFFSET

static const AVClass capinject_context_class = {
    .class_name = "Inject",
    .item_name  = av_default_item_name,
    .option     = options,
    .version    = LIBAVUTIL_VERSION_INT,
};

URLProtocol capff_capinject_protocol = {
    .name                = "capinject",
    .url_open2           = capinject_open,
    .url_read            = capinject_read,
    .url_seek            = capinject_seek,
    .url_close           = capinject_close,
    .priv_data_size      = sizeof(Context),
    .priv_data_class     = &capinject_context_class,
};
