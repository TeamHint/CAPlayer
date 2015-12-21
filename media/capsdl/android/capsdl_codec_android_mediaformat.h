/*****************************************************************************
 * capsdl_codec_android_mediaformat.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIAFORMAT_H
#define CAPSDL_ANDROID__ANDROID_CODEC_ANDROID_MEDIAFORMAT_H

#include "../capsdl_stdinc.h"
#include <stdbool.h>
#include <jni.h>
#include <sys/types.h>
#include "../capsdl_mutex.h"
#include "capsdl_codec_android_mediadef.h"

typedef struct SDL_AMediaFormat_Opaque      SDL_AMediaFormat_Opaque;
typedef struct SDL_AMediaFormat             SDL_AMediaFormat;
typedef struct SDL_AMediaFormat
{
    SDL_mutex *mutex;

    SDL_AMediaFormat_Opaque *opaque;

    sdl_amedia_status_t (*func_delete)(SDL_AMediaFormat *aformat);

    bool (*func_getInt32)(SDL_AMediaFormat* aformat, const char* name, int32_t *out);
    void (*func_setInt32)(SDL_AMediaFormat* aformat, const char* name, int32_t value);

    void (*func_setBuffer)(SDL_AMediaFormat* aformat, const char* name, void* data, size_t size);
} SDL_AMediaFormat;

sdl_amedia_status_t SDL_AMediaFormat_delete(SDL_AMediaFormat* aformat);
sdl_amedia_status_t SDL_AMediaFormat_deleteP(SDL_AMediaFormat** aformat);

bool SDL_AMediaFormat_getInt32(SDL_AMediaFormat* aformat, const char* name, int32_t *out);
void SDL_AMediaFormat_setInt32(SDL_AMediaFormat* aformat, const char* name, int32_t value);

void SDL_AMediaFormat_setBuffer(SDL_AMediaFormat* aformat, const char* name, void* data, size_t size);

#endif
