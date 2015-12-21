/*****************************************************************************
 * capsdl_vout.h
 *****************************************************************************

 */

#ifndef CAPSDL__CAPSDL_VOUT_H
#define CAPSDL__CAPSDL_VOUT_H

#include "capsdl_stdinc.h"
#include "capsdl_class.h"
#include "capsdl_mutex.h"
#include "capsdl_video.h"
#include "ffmpeg/capsdl_inc_ffmpeg.h"

typedef struct SDL_VoutOverlay_Opaque SDL_VoutOverlay_Opaque;
typedef struct SDL_VoutOverlay SDL_VoutOverlay;
struct SDL_VoutOverlay {
    int w; /**< Read-only */
    int h; /**< Read-only */
    Uint32 format; /**< Read-only */
    int planes; /**< Read-only */
    Uint16 *pitches; /**< in bytes, Read-only */
    Uint8 **pixels; /**< Read-write */

    int is_private;

    int sar_num;
    int sar_den;

    SDL_Class               *opaque_class;
    SDL_VoutOverlay_Opaque  *opaque;

    void    (*free_l)(SDL_VoutOverlay *overlay);
    int     (*lock)(SDL_VoutOverlay *overlay);
    int     (*unlock)(SDL_VoutOverlay *overlay);
    void    (*unref)(SDL_VoutOverlay *overlay);

    int     (*func_fill_frame)(SDL_VoutOverlay *overlay, const AVFrame *frame);
};

typedef struct SDL_Vout_Opaque SDL_Vout_Opaque;
typedef struct SDL_Vout SDL_Vout;
struct SDL_Vout {
    SDL_mutex *mutex;

    SDL_Class       *opaque_class;
    SDL_Vout_Opaque *opaque;
    SDL_VoutOverlay *(*create_overlay)(int width, int height, Uint32 format, SDL_Vout *vout);
    void (*free_l)(SDL_Vout *vout);
    int (*display_overlay)(SDL_Vout *vout, SDL_VoutOverlay *overlay);
};

void SDL_VoutFree(SDL_Vout *vout);
void SDL_VoutFreeP(SDL_Vout **pvout);
int SDL_VoutDisplayYUVOverlay(SDL_Vout *vout, SDL_VoutOverlay *overlay);

SDL_VoutOverlay *SDL_Vout_CreateOverlay(int width, int height, Uint32 format, SDL_Vout *vout);
int     SDL_VoutLockYUVOverlay(SDL_VoutOverlay *overlay);
int     SDL_VoutUnlockYUVOverlay(SDL_VoutOverlay *overlay);
void    SDL_VoutFreeYUVOverlay(SDL_VoutOverlay *overlay);
void    SDL_VoutUnrefYUVOverlay(SDL_VoutOverlay *overlay);
int     SDL_VoutFillFrameYUVOverlay(SDL_VoutOverlay *overlay, const AVFrame *frame);

#endif
