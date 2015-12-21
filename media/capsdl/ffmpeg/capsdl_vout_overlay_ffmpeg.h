/*****************************************************************************
 * capsdl_vout_overlay_ffmpeg.h
 *****************************************************************************

 */

#ifndef CAPSDL__FFMPEG__CAPSDL_VOUT_OVERLAY_FFMPEG_H
#define CAPSDL__FFMPEG__CAPSDL_VOUT_OVERLAY_FFMPEG_H

#include "../capsdl_stdinc.h"
#include "../capsdl_vout.h"
#include "capsdl_inc_ffmpeg.h"

// TODO: 9 alignment to speed up memcpy when display
SDL_VoutOverlay *SDL_VoutFFmpeg_CreateOverlay(int width, int height, Uint32 format, SDL_Vout *vout);

#endif
