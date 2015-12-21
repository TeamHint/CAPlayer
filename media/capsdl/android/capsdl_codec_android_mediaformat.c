/*****************************************************************************
 * capsdl_codec_android_mediaformat.c
 *****************************************************************************

 */

#include "capsdl_codec_android_mediaformat.h"
#include <assert.h>

// FIXME: release SDL_AMediaFormat
sdl_amedia_status_t SDL_AMediaFormat_delete(SDL_AMediaFormat* aformat)
{
    if (!aformat)
        return SDL_AMEDIA_OK;
    assert(aformat->func_delete);
    return aformat->func_delete(aformat);
}

sdl_amedia_status_t SDL_AMediaFormat_deleteP(SDL_AMediaFormat** aformat)
{
    if (!aformat)
        return SDL_AMEDIA_OK;
    sdl_amedia_status_t amc_ret = SDL_AMediaFormat_delete(*aformat);
    aformat = NULL;
    return amc_ret;
}

bool SDL_AMediaFormat_getInt32(SDL_AMediaFormat* aformat, const char* name, int32_t *out)
{
    assert(aformat->func_getInt32);
    return aformat->func_getInt32(aformat, name, out);
}

void SDL_AMediaFormat_setInt32(SDL_AMediaFormat* aformat, const char* name, int32_t value)
{
    assert(aformat->func_setInt32);
    aformat->func_setInt32(aformat, name, value);
}

void SDL_AMediaFormat_setBuffer(SDL_AMediaFormat* aformat, const char* name, void* data, size_t size)
{
    assert(aformat->func_setInt32);
    aformat->func_setBuffer(aformat, name, data, size);
}
