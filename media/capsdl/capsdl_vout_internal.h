/*****************************************************************************
 * capsdl_vout_internal.h
 *****************************************************************************

 */

#ifndef CAPSDL__CAPSDL_VOUT_INTERNAL_H
#define CAPSDL__CAPSDL_VOUT_INTERNAL_H

#include <stdlib.h>
#include <string.h>
#include "capsdl_vout.h"

inline static SDL_Vout *SDL_Vout_CreateInternal(size_t opaque_size)
{
    SDL_Vout *vout = (SDL_Vout*) calloc(1, sizeof(SDL_Vout));
    if (!vout)
        return NULL;

    vout->opaque = calloc(1, opaque_size);
    if (!vout->opaque) {
        free(vout);
        return NULL;
    }

    vout->mutex = SDL_CreateMutex();
    if (vout->mutex == NULL) {
        free(vout->opaque);
        free(vout);
        return NULL;
    }

    return vout;
}

inline static void SDL_Vout_FreeInternal(SDL_Vout *vout)
{
    if (!vout)
        return;

    if (vout->mutex) {
        SDL_DestroyMutex(vout->mutex);
    }

    free(vout->opaque);
    memset(vout, 0, sizeof(SDL_Vout));
    free(vout);
}

inline static SDL_VoutOverlay *SDL_VoutOverlay_CreateInternal(size_t opaque_size)
{
    SDL_VoutOverlay *overlay = (SDL_VoutOverlay*) calloc(1, sizeof(SDL_VoutOverlay));
    if (!overlay)
        return NULL;

    overlay->opaque = calloc(1, opaque_size);
    if (!overlay->opaque) {
        free(overlay);
        return NULL;
    }
    return overlay;
}

inline static void SDL_VoutOverlay_FreeInternal(SDL_VoutOverlay *overlay)
{
    if (!overlay)
        return;

    if (overlay->opaque)
        free(overlay->opaque);

    memset(overlay, 0, sizeof(SDL_VoutOverlay));
    free(overlay);
}

#endif
