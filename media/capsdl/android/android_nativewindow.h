/*****************************************************************************
 * android_nativewindow.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__ANDROID_NATIVEWINDOW_H
#define CAPSDL_ANDROID__ANDROID_NATIVEWINDOW_H

typedef struct ANativeWindow ANativeWindow;
typedef struct SDL_VoutOverlay SDL_VoutOverlay;

int SDL_Android_NativeWindow_display_l(ANativeWindow* native_window, SDL_VoutOverlay *overlay);

#endif
