/*
 * caplayer_android.h

 */

#ifndef CAPLAYER_ANDROID__CAPLAYER_ANDROID_H
#define CAPLAYER_ANDROID__CAPLAYER_ANDROID_H

#include <jni.h>
#include "caplayer_android_def.h"
#include "../caplayer.h"

typedef struct capmp_android_media_format_context {
    const char *mime_type;
    int         profile;
    int         level;
} capmp_android_media_format_context;

// ref_count is 1 after open
CapMediaPlayer *capmp_android_create(int(*msg_loop)(void*));

void capmp_android_set_surface(JNIEnv *env, CapMediaPlayer *mp, jobject android_surface);
void capmp_android_set_volume(JNIEnv *env, CapMediaPlayer *mp, float left, float right);
int  capmp_android_get_audio_session_id(JNIEnv *env, CapMediaPlayer *mp);
void capmp_android_set_mediacodec_select_callback(CapMediaPlayer *mp, bool (*callback)(void *opaque, capmp_mediacodecinfo_context *mcc), void *opaque);

#endif
