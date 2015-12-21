/*****************************************************************************
 * capsdl_codec_android_mediaformat_java.c
 *****************************************************************************

 */

#include "capsdl_codec_android_mediaformat_java.h"

#include "capsdl/android/jjk/c/android/media/MediaFormat.h"
#include "capsdl/android/jjk/c/java/nio/ByteBuffer.h"
#include "capsdl_android_jni.h"
#include "capsdl_codec_android_mediaformat_internal.h"
#include "capsdl_inc_internal_android.h"

typedef struct SDL_AMediaFormat_Opaque {
    jobject android_media_format;

    jobject android_byte_buffer;
} SDL_AMediaFormat_Opaque;

jobject SDL_AMediaFormatJava_getObject(JNIEnv *env, const SDL_AMediaFormat *thiz)
{
    if (!thiz || !thiz->opaque)
        return NULL;

    SDL_AMediaFormat_Opaque *opaque = (SDL_AMediaFormat_Opaque *)thiz->opaque;
    return opaque->android_media_format;
}

static jobject getAndroidMediaFormat(JNIEnv *env, const SDL_AMediaFormat* thiz) {
    if (!thiz)
        return NULL;

    SDL_AMediaFormat_Opaque *opaque = (SDL_AMediaFormat_Opaque *)thiz->opaque;
    if (!opaque)
        return NULL;

    return opaque->android_media_format;
}

static sdl_amedia_status_t SDL_AMediaFormatJava_delete(SDL_AMediaFormat* aformat)
{
    if (!aformat)
        return SDL_AMEDIA_OK;

    JNIEnv *env = NULL;
    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        ALOGE("%s: SetupThreadEnv failed", __func__);
        return SDL_AMEDIA_ERROR_UNKNOWN;
    }

    SDL_AMediaFormat_Opaque *opaque = (SDL_AMediaFormat_Opaque *)aformat->opaque;
    if (opaque) {
        SDL_JNI_DeleteGlobalRefP(env, &opaque->android_byte_buffer);
        SDL_JNI_DeleteGlobalRefP(env, &opaque->android_media_format);
    }

    SDL_AMediaFormat_FreeInternal(aformat);
    return SDL_AMEDIA_OK;
}

static bool SDL_AMediaFormatJava_getInt32(SDL_AMediaFormat* aformat, const char* name, int32_t *out)
{
    JNIEnv *env = NULL;
    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        ALOGE("%s: SDL_JNI_SetupThreadEnv: failed", __func__);
        return false;
    }

    jobject android_media_format = getAndroidMediaFormat(env, aformat);
    if (!android_media_format) {
        ALOGE("%s: getAndroidMediaFormat: failed", __func__);
        return false;
    }

    jint ret = JJKC_MediaFormat__getInteger__withCString(env, android_media_format, name);
    if (JJK_ExceptionCheck__catchAll(env)) {
        ALOGE("%s: CallIntMethod: failed", __func__);
        return false;
    }

    if (out)
        *out = ret;
    return true;
}

static void SDL_AMediaFormatJava_setInt32(SDL_AMediaFormat* aformat, const char* name, int32_t value)
{
    JNIEnv *env = NULL;
    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        ALOGE("%s: SDL_JNI_SetupThreadEnv: failed", __func__);
        return;
    }

    jobject android_media_format = getAndroidMediaFormat(env, aformat);
    if (!android_media_format) {
        ALOGE("%s: getAndroidMediaFormat: failed", __func__);
        return;
    }

    JJKC_MediaFormat__setInteger__withCString(env, android_media_format, name, value);
    if (JJK_ExceptionCheck__catchAll(env)) {
        ALOGE("%s: CallVoidMethod: failed", __func__);
        return;
    }
}

static void SDL_AMediaFormatJava_setBuffer(SDL_AMediaFormat* aformat, const char* name, void* data, size_t size)
{
    int    ret  = -1;
    JNIEnv *env = NULL;
    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        ALOGE("%s: SDL_JNI_SetupThreadEnv: failed", __func__);
        return;
    }

    SDL_AMediaFormat_Opaque *opaque = (SDL_AMediaFormat_Opaque *)aformat->opaque;
    jobject android_media_format = opaque->android_media_format;
    if (!opaque->android_byte_buffer) {
        opaque->android_byte_buffer = JJKC_ByteBuffer__allocateDirect__asGlobalRef__catchAll(env, size);
        if (!opaque->android_byte_buffer) {
            JJK_FUNC_FAIL_TRACE();
            return;
        }
    }

    ret = JJKC_ByteBuffer__assignData__catchAll(env, opaque->android_byte_buffer, data, size);
    if (ret < 0) {
        JJK_FUNC_FAIL_TRACE();
        return;
    }

    JJKC_MediaFormat__setByteBuffer__withCString(env, android_media_format, name, opaque->android_byte_buffer);
    if (JJK_ExceptionCheck__catchAll(env)) {
        ALOGE("%s: call jmid_setByteBuffer: failed", __func__);
        return;
    }
}

static void setup_aformat(SDL_AMediaFormat *aformat, jobject android_media_format) {
    SDL_AMediaFormat_Opaque *opaque = aformat->opaque;
    opaque->android_media_format = android_media_format;

    aformat->func_delete    = SDL_AMediaFormatJava_delete;
    aformat->func_getInt32  = SDL_AMediaFormatJava_getInt32;
    aformat->func_setInt32  = SDL_AMediaFormatJava_setInt32;
    aformat->func_setBuffer = SDL_AMediaFormatJava_setBuffer;
}

SDL_AMediaFormat *SDL_AMediaFormatJava_init(JNIEnv *env, jobject android_format)
{
    SDLTRACE("%s", __func__);
    jobject global_android_media_format = (*env)->NewGlobalRef(env, android_format);
    if (JJK_ExceptionCheck__catchAll(env) || !global_android_media_format) {
        return NULL;
    }

    SDL_AMediaFormat *aformat = SDL_AMediaFormat_CreateInternal(sizeof(SDL_AMediaFormat_Opaque));
    if (!aformat) {
        SDL_JNI_DeleteGlobalRefP(env, &global_android_media_format);
        return NULL;
    }

    setup_aformat(aformat, global_android_media_format);
    return aformat;
}

SDL_AMediaFormat *SDL_AMediaFormatJava_createVideoFormat(JNIEnv *env, const char *mime, int width, int height)
{
    SDLTRACE("%s", __func__);

    jobject android_media_format = JJKC_MediaFormat__createVideoFormat__withCString__asGlobalRef__catchAll(env, mime, width, height);
    if (JJK_ExceptionCheck__catchAll(env) || !android_media_format) {
        return NULL;
    }

    SDL_AMediaFormat *aformat = SDL_AMediaFormat_CreateInternal(sizeof(SDL_AMediaFormat_Opaque));
    if (!aformat) {
        SDL_JNI_DeleteGlobalRefP(env, &android_media_format);
        return NULL;
    }

    setup_aformat(aformat, android_media_format);
    SDL_AMediaFormat_setInt32(aformat, AMEDIAFORMAT_KEY_MAX_INPUT_SIZE, 0);
    return aformat;
}
