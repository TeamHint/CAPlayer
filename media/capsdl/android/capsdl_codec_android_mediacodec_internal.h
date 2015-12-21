/*****************************************************************************
 * capsdl_codec_android_mediacodec_internal.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIACODEC_INTERNAL_H
#define CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIACODEC_INTERNAL_H

#include "capsdl_codec_android_mediacodec.h"

inline static SDL_AMediaCodec *SDL_AMediaCodec_CreateInternal(size_t opaque_size)
{
    SDL_AMediaCodec *acodec = (SDL_AMediaCodec*) mallocz(sizeof(SDL_AMediaCodec));
    if (!acodec)
        return NULL;

    acodec->opaque = mallocz(opaque_size);
    if (!acodec->opaque) {
        free(acodec);
        return NULL;
    }

    acodec->mutex = SDL_CreateMutex();
    if (acodec->mutex == NULL) {
        free(acodec->opaque);
        free(acodec);
        return NULL;
    }

    return acodec;
}

inline static void SDL_AMediaCodec_FreeInternal(SDL_AMediaCodec *acodec)
{
    if (!acodec)
        return;

    if (acodec->mutex) {
        SDL_DestroyMutexP(&acodec->mutex);
    }

    free(acodec->opaque);
    memset(acodec, 0, sizeof(SDL_AMediaCodec));
    free(acodec);
}

#endif

