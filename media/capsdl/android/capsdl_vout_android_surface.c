/*****************************************************************************
 * capsdl_vout_android_surface.c
 *****************************************************************************

 */

#include "capsdl_vout_android_surface.h"

#include <android/native_window_jni.h>
#include "../capsdl_inc_internal.h"
#include "capsdl_android_jni.h"
#include "capsdl_vout_android_nativewindow.h"

SDL_Vout *SDL_VoutAndroid_CreateForAndroidSurface()
{
    return SDL_VoutAndroid_CreateForANativeWindow();
}

void SDL_VoutAndroid_SetAndroidSurface(JNIEnv *env, SDL_Vout *vout, jobject android_surface)
{
    ANativeWindow *native_window = NULL;
    if (android_surface) {
        native_window = ANativeWindow_fromSurface(env, android_surface);
        if (!native_window) {
            ALOGE("%s: ANativeWindow_fromSurface: failed\n", __func__);
            // do not return fail here;
        }
    }

    SDL_VoutAndroid_SetNativeWindow(vout, native_window);
    if (native_window)
        ANativeWindow_release(native_window);
}
