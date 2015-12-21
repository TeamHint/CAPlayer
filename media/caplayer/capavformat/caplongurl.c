

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
    char           *url;
} Context;

static int caplongurl_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    Context *c = h->priv_data;

    if (!c->url || !*c->url)
        return AVERROR_EXTERNAL;

    return ffurl_open(&c->inner, c->url, flags, &h->interrupt_callback, options);
}

static int caplongurl_close(URLContext *h)
{
    Context *c = h->priv_data;

    return ffurl_close(c->inner);
}

static int caplongurl_read(URLContext *h, unsigned char *buf, int size)
{
    Context *c = h->priv_data;

    return ffurl_read(c->inner, buf, size);
}

static int64_t caplongurl_seek(URLContext *h, int64_t pos, int whence)
{
    Context *c = h->priv_data;

    return ffurl_seek(c->inner, pos, whence);
}

#define OFFSET(x) offsetof(Context, x)
#define D AV_OPT_FLAG_DECODING_PARAM

static const AVOption options[] = {
    { "caplongurl-url",         "real url to access",
        OFFSET(url),            CAPAV_OPTION_STR(NULL) },
    { NULL }
};

#undef D
#undef OFFSET

static const AVClass caplongurl_context_class = {
    .class_name = "LongUrl",
    .item_name  = av_default_item_name,
    .option     = options,
    .version    = LIBAVUTIL_VERSION_INT,
};

URLProtocol capff_caplongurl_protocol = {
    .name                = "caplongurl",
    .url_open2           = caplongurl_open,
    .url_read            = caplongurl_read,
    .url_seek            = caplongurl_seek,
    .url_close           = caplongurl_close,
    .priv_data_size      = sizeof(Context),
    .priv_data_class     = &caplongurl_context_class,
};
