/*****************************************************************************
 * capsdl_vout_android_nativewindow.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__CAPSDL_VOUT_ANDROID_NATIVEWINDOW_H
#define CAPSDL_ANDROID__CAPSDL_VOUT_ANDROID_NATIVEWINDOW_H

#include "../capsdl_stdinc.h"
#include "../capsdl_vout.h"

typedef struct ANativeWindow   ANativeWindow;
typedef struct SDL_AMediaCodec SDL_AMediaCodec;

SDL_Vout *SDL_VoutAndroid_CreateForANativeWindow();
void SDL_VoutAndroid_SetNativeWindow(SDL_Vout *vout, ANativeWindow *native_window);
void             SDL_VoutAndroid_setAMediaCodec(SDL_Vout *vout, SDL_AMediaCodec *acodec);
SDL_AMediaCodec *SDL_VoutAndroid_peekAMediaCodec(SDL_Vout *vout);
void             SDL_VoutAndroid_invalidateAllBuffers(SDL_Vout *vout);

/*
 * MediaCodec buffer proxy
 */

typedef struct SDL_AMediaCodecBufferProxy SDL_AMediaCodecBufferProxy;
void SDL_AMediaCodecBufferProxy_lock(SDL_AMediaCodecBufferProxy *proxy);
void SDL_AMediaCodecBufferProxy_unlock(SDL_AMediaCodecBufferProxy *proxy);

SDL_AMediaCodecBufferProxy *SDL_VoutAndroid_obtainBufferProxy(SDL_Vout *vout, int acodec_serial, int buffer_index);
int SDL_VoutAndroid_releaseBufferProxyP(SDL_Vout *vout, SDL_AMediaCodecBufferProxy **proxy, bool render);
int SDL_VoutAndroid_releaseBufferProxyP_l(SDL_Vout *vout, SDL_AMediaCodecBufferProxy **proxy, bool render);

#endif
