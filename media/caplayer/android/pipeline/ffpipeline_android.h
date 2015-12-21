/*
 * ffpipeline_android.h

 */

#ifndef FFPLAY__FF_FFPIPELINE_ANDROID_H
#define FFPLAY__FF_FFPIPELINE_ANDROID_H

#include <stdbool.h>
#include <jni.h>
#include "../caplayer_android_def.h"
#include "../../ff_ffpipeline.h"
#include "capsdl/capsdl_vout.h"

typedef struct FFPlayer       FFPlayer;
typedef struct CAPFF_Pipeline CAPFF_Pipeline;

CAPFF_Pipeline *ffpipeline_create_from_android(FFPlayer *ffp);

void    ffpipeline_set_vout(CAPFF_Pipeline* pipeline, SDL_Vout *vout);

int     ffpipeline_set_surface(JNIEnv *env, CAPFF_Pipeline* pipeline, jobject surface);

int     ffpipeline_lock_surface(CAPFF_Pipeline* pipeline);
int     ffpipeline_unlock_surface(CAPFF_Pipeline* pipeline);
jobject ffpipeline_get_surface_as_global_ref_l(JNIEnv *env, CAPFF_Pipeline* pipeline);
jobject ffpipeline_get_surface_as_global_ref(JNIEnv *env, CAPFF_Pipeline* pipeline);

bool    ffpipeline_is_surface_need_reconfigure_l(CAPFF_Pipeline* pipeline);
void    ffpipeline_set_surface_need_reconfigure_l(CAPFF_Pipeline* pipeline, bool need_reconfigure);

void    ffpipeline_set_mediacodec_select_callback(CAPFF_Pipeline* pipeline, bool (*callback)(void *opaque, capmp_mediacodecinfo_context *mcc), void *opaque);
bool    ffpipeline_select_mediacodec_l(CAPFF_Pipeline* pipeline, capmp_mediacodecinfo_context *mcc);

void    ffpipeline_set_volume(CAPFF_Pipeline* pipeline, float left, float right);

#endif
