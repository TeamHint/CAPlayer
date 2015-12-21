

#ifdef __ANDROID__

#include <assert.h>
#include "libavformat/avformat.h"
#include "libavformat/url.h"
#include "libavutil/avstring.h"
#include "libavutil/log.h"
#include "libavutil/opt.h"

#include "caplayer/capavutil/opt.h"
#include "capavformat.h"

#include "capsdl/android/capsdl_android_jni.h"
#include "capsdl/android/jjk/c/tv/danmaku/cap/media/player/misc/IMediaDataSource.h"

typedef struct Context {
    AVClass        *class;

    /* options */
    int64_t         logical_pos;
    int64_t         logical_size;

    int64_t         media_data_source_ptr;
    jobject         media_data_source;
    jbyteArray      jbuffer;
    int             jbuffer_capacity;
} Context;

static int capmds_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    Context *c = h->priv_data;
    JNIEnv *env = NULL;
    jobject media_data_source = NULL;
    char *final = NULL;

    av_strstart(arg, "capmediadatasource:", &arg);

    media_data_source = (jobject) (intptr_t) strtoll(arg, &final, 10);
    if (!media_data_source)
        return AVERROR(EINVAL);

    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        av_log(h, AV_LOG_ERROR, "%s: SDL_JNI_SetupThreadEnv: failed", __func__);
        return AVERROR(EINVAL);
    }

    c->logical_size = JJKC_IMediaDataSource__getSize(env, media_data_source);
    if (JJK_ExceptionCheck__catchAll(env)) {
        return AVERROR(EINVAL);
    } else if (c->logical_size < 0) {
        h->is_streamed = 1;
        c->logical_size = -1;
    }

    c->media_data_source = (*env)->NewGlobalRef(env, media_data_source);
    if (JJK_ExceptionCheck__catchAll(env) || !c->media_data_source) {
        return AVERROR(ENOMEM);
    }

    return 0;
}

static int capmds_close(URLContext *h)
{
    Context *c = h->priv_data;
    JNIEnv *env = NULL;

    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        av_log(h, AV_LOG_ERROR, "%s: SDL_JNI_SetupThreadEnv: failed", __func__);
        return AVERROR(EINVAL);
    }

    JJK_DeleteGlobalRef__p(env, &c->jbuffer);

    if (c->media_data_source) {
        JJKC_IMediaDataSource__close__catchAll(env, c->media_data_source);
        JJK_DeleteGlobalRef__p(env, &c->media_data_source);
    }
    c->media_data_source_ptr = 0;

    return 0;
}

static jobject jbuffer_grow(JNIEnv *env, URLContext *h, int new_capacity) {
    Context *c = h->priv_data;

    if (c->jbuffer && c->jbuffer_capacity >= new_capacity)
        return c->jbuffer;

    new_capacity = FFMAX(new_capacity, c->jbuffer_capacity * 2);

    JJK_DeleteGlobalRef__p(env, &c->jbuffer);
    c->jbuffer_capacity = 0;

    c->jbuffer = JJK_NewByteArray__asGlobalRef__catchAll(env, new_capacity);
    if (JJK_ExceptionCheck__catchAll(env) || !c->jbuffer) {
        c->jbuffer = NULL;
        return NULL;
    }

    c->jbuffer_capacity = new_capacity;
    return c->jbuffer;
}

static int capmds_read(URLContext *h, unsigned char *buf, int size)
{
    Context    *c = h->priv_data;
    JNIEnv     *env = NULL;
    jbyteArray  jbuffer = NULL;
    jint        ret = 0;

    if (!c->media_data_source) 
        return AVERROR(EINVAL);

    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        av_log(h, AV_LOG_ERROR, "%s: SDL_JNI_SetupThreadEnv: failed", __func__);
        return AVERROR(EINVAL);
    }

    jbuffer = jbuffer_grow(env, h, size);
    if (!jbuffer)
        return AVERROR(ENOMEM);

    ret = JJKC_IMediaDataSource__readAt(env, c->media_data_source, c->logical_pos, jbuffer, 0, size);
    if (JJK_ExceptionCheck__catchAll(env))
        return AVERROR(EIO);
    else if (ret < 0)
        return AVERROR_EOF;
    else if (ret == 0)
        return AVERROR(EAGAIN);

    (*env)->GetByteArrayRegion(env, jbuffer, 0, ret, (jbyte*)buf);
    if (JJK_ExceptionCheck__catchAll(env))
        return AVERROR(EIO);

    c->logical_pos += ret;
    return ret;
}

static int64_t capmds_seek(URLContext *h, int64_t pos, int whence)
{
    Context *c = h->priv_data;
    int64_t  ret;
    int64_t  new_logical_pos;
    JNIEnv  *env = NULL;
    jobject  jbuffer = NULL;

    if (!c->media_data_source) 
        return AVERROR(EINVAL);

    if (whence == AVSEEK_SIZE) {
        av_log(h, AV_LOG_TRACE, "%s: AVSEEK_SIZE: %"PRId64"\n", __func__, (int64_t)c->logical_size);
        return c->logical_size;
    } else if (whence == SEEK_CUR) {
        av_log(h, AV_LOG_TRACE, "%s: %"PRId64"\n", __func__, pos);
        new_logical_pos = pos + c->logical_pos;
    } else if (whence == SEEK_SET){
        av_log(h, AV_LOG_TRACE, "%s: %"PRId64"\n", __func__, pos);
        new_logical_pos = pos;
    } else {
        return AVERROR(EINVAL);
    }
    if (new_logical_pos < 0)
        return AVERROR(EINVAL);

    jbuffer = jbuffer_grow(env, h, 0);
    if (!jbuffer)
        return AVERROR(ENOMEM);

    ret = JJKC_IMediaDataSource__readAt(env, c->media_data_source, new_logical_pos, jbuffer, 0, 0);
    if (JJK_ExceptionCheck__catchAll(env))
        return AVERROR(EIO);
    else if (ret < 0)
        return AVERROR_EOF;

    c->logical_pos = new_logical_pos;
    return c->logical_pos;
}

#define OFFSET(x) offsetof(Context, x)
#define D AV_OPT_FLAG_DECODING_PARAM

static const AVOption options[] = {
    { NULL }
};

#undef D
#undef OFFSET

static const AVClass capmediadatasource_context_class = {
    .class_name = "CapMediaDataSource",
    .item_name  = av_default_item_name,
    .option     = options,
    .version    = LIBAVUTIL_VERSION_INT,
};

URLProtocol capff_capmediadatasource_protocol = {
    .name                = "capmediadatasource",
    .url_open2           = capmds_open,
    .url_read            = capmds_read,
    .url_seek            = capmds_seek,
    .url_close           = capmds_close,
    .priv_data_size      = sizeof(Context),
    .priv_data_class     = &capmediadatasource_context_class,
};

#endif
