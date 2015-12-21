/*****************************************************************************
 * capsdl_vout_dummy.c
 *****************************************************************************

 */

#include "capsdl_vout_dummy.h"

#include "../capsdl_vout.h"
#include "../capsdl_vout_internal.h"

typedef struct SDL_VoutSurface_Opaque {
    SDL_Vout *vout;
} SDL_VoutSurface_Opaque;

struct SDL_Vout_Opaque {
    char dummy;
};

static void vout_free_l(SDL_Vout *vout)
{
    if (!vout)
        return;

    SDL_Vout_Opaque *opaque = vout->opaque;
    if (opaque) {
    }

    SDL_Vout_FreeInternal(vout);
}

static int voud_display_overlay_l(SDL_Vout *vout, SDL_VoutOverlay *overlay)
{
    return 0;
}

static int voud_display_overlay(SDL_Vout *vout, SDL_VoutOverlay *overlay)
{
    SDL_LockMutex(vout->mutex);
    int retval = voud_display_overlay_l(vout, overlay);
    SDL_UnlockMutex(vout->mutex);
    return retval;
}

SDL_Vout *SDL_VoutDummy_Create()
{
    SDL_Vout *vout = SDL_Vout_CreateInternal(sizeof(SDL_Vout_Opaque));
    if (!vout)
        return NULL;

    // SDL_Vout_Opaque *opaque = vout->opaque;

    vout->free_l = vout_free_l;
    vout->display_overlay = voud_display_overlay;

    return vout;
}
