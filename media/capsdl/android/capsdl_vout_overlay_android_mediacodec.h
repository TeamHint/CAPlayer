/*****************************************************************************
 * capsdl_vout_overlay_android_mediacodec.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__CAPSDL_VOUT_OVERLAY_ANDROID_MEDIACODEC_H
#define CAPSDL_ANDROID__CAPSDL_VOUT_OVERLAY_ANDROID_MEDIACODEC_H

#include "../capsdl_stdinc.h"
#include "../capsdl_vout.h"

typedef struct SDL_AMediaCodec           SDL_AMediaCodec;
typedef struct SDL_AMediaCodecBufferInfo SDL_AMediaCodecBufferInfo;

SDL_VoutOverlay *SDL_VoutAMediaCodec_CreateOverlay(int width, int height, Uint32 format, SDL_Vout *vout);

bool SDL_VoutOverlayAMediaCodec_isKindOf(SDL_VoutOverlay *overlay);
int  SDL_VoutOverlayAMediaCodec_releaseFrame_l(SDL_VoutOverlay *overlay, SDL_AMediaCodec *acodec, bool render);

#endif
