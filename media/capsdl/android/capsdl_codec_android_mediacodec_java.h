/*****************************************************************************
 * capsdl_codec_android_mediacodec_java.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIACODEC_JAVA_H
#define CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIACODEC_JAVA_H

#include "capsdl_codec_android_mediacodec.h"

typedef struct ASDK_MediaCodec ASDK_MediaCodec;

SDL_AMediaCodec  *SDL_AMediaCodecJava_createByCodecName(JNIEnv *env, const char *codec_name);
jobject           SDL_AMediaCodecJava_getObject(JNIEnv *env, const SDL_AMediaCodec *thiz);

#endif
