
#include "libavformat/avformat.h"
#include "libavformat/url.h"
#include "libavformat/version.h"

#define FF_REGISTER_PROTOCOL(x)                                         \
    {                                                                   \
        extern URLProtocol ff_##x##_protocol;                           \
        capav_register_protocol(&ff_##x##_protocol);                    \
    }

#define CAP_REGISTER_PROTOCOL(x)                                        \
    {                                                                   \
        extern URLProtocol capff_##x##_protocol;                        \
        capav_register_protocol(&capff_##x##_protocol);                 \
    }

#define CAP_REGISTER_DEMUXER(x)                                         \
    {                                                                   \
        extern AVInputFormat capff_##x##_demuxer;                       \
        capav_register_input_format(&capff_##x##_demuxer);              \
    }


static struct URLProtocol *capav_find_protocol(const char *proto_name)
{
    URLProtocol *up = NULL;
    if (!proto_name)
        return NULL;
    while ((up = ffurl_protocol_next(up)) != NULL) {
        if (!up->name)
            continue;
        if (!strcmp(proto_name, up->name))
            break;
    }
    return up;
}

static struct AVInputFormat *capav_find_input_format(const char *iformat_name)
{
    AVInputFormat *fmt = NULL;
    if (!iformat_name)
        return NULL;
    while ((fmt = av_iformat_next(fmt))) {
        if (!fmt->name)
            continue;
        if (!strcmp(iformat_name, fmt->name))
            return fmt;
    }
    return NULL;
}

static void capav_register_protocol(URLProtocol *protocol)
{
    if (capav_find_protocol(protocol->name)) {
        av_log(NULL, AV_LOG_WARNING, "skip     protocol: %s (duplicated)\n", protocol->name);
    } else {
        av_log(NULL, AV_LOG_INFO,    "register protocol: %s\n", protocol->name);
        ffurl_register_protocol(protocol);
    }
}

static void capav_register_input_format(AVInputFormat *iformat)
{
    if (capav_find_input_format(iformat->name)) {
        av_log(NULL, AV_LOG_WARNING, "skip     demuxer : %s (duplicated)\n", iformat->name);
    } else {
        av_log(NULL, AV_LOG_INFO,    "register demuxer : %s\n", iformat->name);
        av_register_input_format(iformat);
    }
}

void capav_register_all(void)
{
    static int initialized;

    if (initialized)
        return;
    initialized = 1;

    av_register_all();

    /* protocols */
    av_log(NULL, AV_LOG_INFO, "===== custom modules begin =====\n");
    FF_REGISTER_PROTOCOL(async);
    CAP_REGISTER_PROTOCOL(caphttphook);
    CAP_REGISTER_PROTOCOL(capinject);
    CAP_REGISTER_PROTOCOL(caplongurl);
#ifdef __ANDROID__
    CAP_REGISTER_PROTOCOL(capmediadatasource);
#endif
    CAP_REGISTER_PROTOCOL(capsegment);
    CAP_REGISTER_PROTOCOL(captcphook);

    /* demuxers */
    CAP_REGISTER_DEMUXER(caplivehook);
    av_log(NULL, AV_LOG_INFO, "===== custom modules end =====\n");
}
