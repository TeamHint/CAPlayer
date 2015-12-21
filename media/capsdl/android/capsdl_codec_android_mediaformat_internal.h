/*****************************************************************************
 * capsdl_codec_android_mediaformat_internal.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIAFORMAT_INTERNAL_H
#define CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIAFORMAT_INTERNAL_H

#include "capsdl_codec_android_mediaformat.h"

inline static SDL_AMediaFormat *SDL_AMediaFormat_CreateInternal(size_t opaque_size)
{
    SDL_AMediaFormat *aformat = (SDL_AMediaFormat*) mallocz(sizeof(SDL_AMediaFormat));
    if (!aformat)
        return NULL;

    aformat->opaque = mallocz(opaque_size);
    if (!aformat->opaque) {
        free(aformat);
        return NULL;
    }

    aformat->mutex = SDL_CreateMutex();
    if (aformat->mutex == NULL) {
        free(aformat->opaque);
        free(aformat);
        return NULL;
    }

    return aformat;
}

inline static void SDL_AMediaFormat_FreeInternal(SDL_AMediaFormat *aformat)
{
    if (!aformat)
        return;

    if (aformat->mutex) {
        SDL_DestroyMutexP(&aformat->mutex);
    }

    free(aformat->opaque);
    memset(aformat, 0, sizeof(SDL_AMediaFormat));
    free(aformat);
}

#endif

