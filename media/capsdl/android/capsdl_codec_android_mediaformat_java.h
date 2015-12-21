/*****************************************************************************
 * capsdl_codec_android_mediaformat_java.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIAFORMAT_JAVA_H
#define CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIAFORMAT_JAVA_H

#include "capsdl_codec_android_mediaformat.h"

SDL_AMediaFormat *SDL_AMediaFormatJava_init(JNIEnv *env, jobject android_format);
SDL_AMediaFormat *SDL_AMediaFormatJava_createVideoFormat(JNIEnv *env, const char *mime, int width, int height);
jobject           SDL_AMediaFormatJava_getObject(JNIEnv *env, const SDL_AMediaFormat *thiz);

#endif

