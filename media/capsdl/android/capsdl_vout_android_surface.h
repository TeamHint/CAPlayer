/*****************************************************************************
 * capsdl_vout_android_surface.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__CAPSDL_VOUT_ANDROID_SURFACE_H
#define CAPSDL_ANDROID__CAPSDL_VOUT_ANDROID_SURFACE_H

#include <jni.h>
#include "../capsdl_stdinc.h"
#include "../capsdl_vout.h"

SDL_Vout *SDL_VoutAndroid_CreateForAndroidSurface();
void SDL_VoutAndroid_SetAndroidSurface(JNIEnv*env, SDL_Vout *vout, jobject android_surface);

#endif
