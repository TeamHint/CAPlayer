/*
 * caplayer_android.c

 */

#include "caplayer_android.h"

#include <assert.h>
#include "capsdl/android/capsdl_android.h"
#include "../ff_fferror.h"
#include "../ff_ffplay.h"
#include "../caplayer_internal.h"
#include "../pipeline/ffpipeline_ffplay.h"
#include "pipeline/ffpipeline_android.h"

CapMediaPlayer *capmp_android_create(int(*msg_loop)(void*))
{
    CapMediaPlayer *mp = capmp_create(msg_loop);
    if (!mp)
        goto fail;

    mp->ffplayer->vout = SDL_VoutAndroid_CreateForAndroidSurface();
    if (!mp->ffplayer->vout)
        goto fail;

    mp->ffplayer->pipeline = ffpipeline_create_from_android(mp->ffplayer);
    if (!mp->ffplayer->pipeline)
        goto fail;

    ffpipeline_set_vout(mp->ffplayer->pipeline, mp->ffplayer->vout);

    return mp;

fail:
    capmp_dec_ref_p(&mp);
    return NULL;
}

void capmp_android_set_surface_l(JNIEnv *env, CapMediaPlayer *mp, jobject android_surface)
{
    if (!mp || !mp->ffplayer || !mp->ffplayer->vout)
        return;

    SDL_VoutAndroid_SetAndroidSurface(env, mp->ffplayer->vout, android_surface);
    ffpipeline_set_surface(env, mp->ffplayer->pipeline, android_surface);
}

void capmp_android_set_surface(JNIEnv *env, CapMediaPlayer *mp, jobject android_surface)
{
    if (!mp)
        return;

    MPTRACE("capmp_set_android_surface(surface=%p)", (void*)android_surface);
    pthread_mutex_lock(&mp->mutex);
    capmp_android_set_surface_l(env, mp, android_surface);
    pthread_mutex_unlock(&mp->mutex);
    MPTRACE("capmp_set_android_surface(surface=%p)=void", (void*)android_surface);
}

void capmp_android_set_volume(JNIEnv *env, CapMediaPlayer *mp, float left, float right)
{
    if (!mp)
        return;

    MPTRACE("capmp_android_set_volume(%f, %f)", left, right);
    pthread_mutex_lock(&mp->mutex);

    if (mp && mp->ffplayer && mp->ffplayer->pipeline) {
        ffpipeline_set_volume(mp->ffplayer->pipeline, left, right);
    }

    pthread_mutex_unlock(&mp->mutex);
    MPTRACE("capmp_android_set_volume(%f, %f)=void", left, right);
}

int capmp_android_get_audio_session_id(JNIEnv *env, CapMediaPlayer *mp)
{
    int audio_session_id = 0;
    if (!mp)
        return audio_session_id;

    MPTRACE("%s()", __func__);
    pthread_mutex_lock(&mp->mutex);

    if (mp && mp->ffplayer && mp->ffplayer->aout) {
        audio_session_id = SDL_AoutGetAudioSessionId(mp->ffplayer->aout);
    }

    pthread_mutex_unlock(&mp->mutex);
    MPTRACE("%s()=%d", __func__, audio_session_id);

    return audio_session_id;
}

void capmp_android_set_mediacodec_select_callback(CapMediaPlayer *mp, bool (*callback)(void *opaque, capmp_mediacodecinfo_context *mcc), void *opaque)
{
    if (!mp)
        return;

    MPTRACE("capmp_android_set_mediacodec_select_callback()");
    pthread_mutex_lock(&mp->mutex);

    if (mp && mp->ffplayer && mp->ffplayer->pipeline) {
        ffpipeline_set_mediacodec_select_callback(mp->ffplayer->pipeline, callback, opaque);
    }

    pthread_mutex_unlock(&mp->mutex);
    MPTRACE("capmp_android_set_mediacodec_select_callback()=void");
}
