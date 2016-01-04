/*****************************************************************************
 * capsdl_codec_android_mediacodec.c
 *****************************************************************************

 */

#include "capsdl_codec_android_mediacodec.h"
#include <assert.h>

static int g_amediacodec_object_serial;

// TODO: thread-safe
int SDL_AMediaCodec_create_object_serial()
{
    int object_serial = ++g_amediacodec_object_serial;
    if (object_serial == 0)
        object_serial = SDL_AMediaCodec_create_object_serial();
    return object_serial;
}

// FIXME: release SDL_AMediaCodec
sdl_amedia_status_t SDL_AMediaCodec_delete(SDL_AMediaCodec* acodec)
{
    if (!acodec)
        return SDL_AMEDIA_OK;

    assert(acodec->func_delete);
    return acodec->func_delete(acodec);
}

sdl_amedia_status_t SDL_AMediaCodec_deleteP(SDL_AMediaCodec** acodec)
{
    if (!acodec)
        return SDL_AMEDIA_OK;
    sdl_amedia_status_t ret = SDL_AMediaCodec_delete(*acodec);
    *acodec = NULL;
    return ret;
}

sdl_amedia_status_t SDL_AMediaCodec_configure(
    SDL_AMediaCodec* acodec,
    const SDL_AMediaFormat* aformat,
    ANativeWindow* surface,
    SDL_AMediaCrypto *crypto,
    uint32_t flags)
{
    assert(acodec->func_configure);
    sdl_amedia_status_t ret = acodec->func_configure(acodec, aformat, surface, crypto, flags);
    acodec->is_configured = true;
    acodec->is_started    = false;
    return ret;
}

sdl_amedia_status_t SDL_AMediaCodec_configure_surface(
    JNIEnv*env,
    SDL_AMediaCodec* acodec,
    const SDL_AMediaFormat* aformat,
    jobject android_surface,
    SDL_AMediaCrypto *crypto,
    uint32_t flags)
{
    assert(acodec->func_configure_surface);
    sdl_amedia_status_t ret = acodec->func_configure_surface(env, acodec, aformat, android_surface, crypto, flags);
    acodec->is_configured = true;
    acodec->is_started    = false;
    return ret;
}

void SDL_AMediaCodec_increaseReference(SDL_AMediaCodec *acodec)
{
    assert(acodec);
    __sync_fetch_and_add(&acodec->ref_count, 1);
}

void SDL_AMediaCodec_decreaseReference(SDL_AMediaCodec *acodec)
{
    if (!acodec)
        return;

    int ref_count = __sync_sub_and_fetch(&acodec->ref_count, 1);
    if (ref_count == 0) {
        AMCTRACE("%s(): ref=0\n", __func__);
        if (SDL_AMediaCodec_isStarted(acodec)) {
            SDL_AMediaCodec_stop(acodec);
        }
        SDL_AMediaCodec_delete(acodec);
    }
}

void SDL_AMediaCodec_decreaseReferenceP(SDL_AMediaCodec **acodec)
{
    if (!acodec)
        return;

    SDL_AMediaCodec_decreaseReference(*acodec);
    *acodec = NULL;
}

bool SDL_AMediaCodec_isConfigured(SDL_AMediaCodec *acodec)
{
    return acodec->is_configured;
}

bool SDL_AMediaCodec_isStarted(SDL_AMediaCodec *acodec)
{
    return acodec->is_started;
}

sdl_amedia_status_t SDL_AMediaCodec_start(SDL_AMediaCodec* acodec)
{
    assert(acodec->func_start);
    sdl_amedia_status_t amc_ret = acodec->func_start(acodec);
    if (amc_ret == SDL_AMEDIA_OK) {
        acodec->is_started = true;
    }
    return amc_ret;
}

sdl_amedia_status_t SDL_AMediaCodec_stop(SDL_AMediaCodec* acodec)
{
    assert(acodec->func_stop);
    acodec->is_started = false;
    return acodec->func_stop(acodec);
}

sdl_amedia_status_t SDL_AMediaCodec_flush(SDL_AMediaCodec* acodec)
{
    assert(acodec->func_flush);
    return acodec->func_flush(acodec);
}

uint8_t* SDL_AMediaCodec_getInputBuffer(SDL_AMediaCodec* acodec, size_t idx, size_t *out_size)
{
    assert(acodec->func_getInputBuffer);
    return acodec->func_getInputBuffer(acodec, idx, out_size);
}

uint8_t* SDL_AMediaCodec_getOutputBuffer(SDL_AMediaCodec* acodec, size_t idx, size_t *out_size)
{
    assert(acodec->func_getOutputBuffer);
    return acodec->func_getOutputBuffer(acodec, idx, out_size);
}

ssize_t SDL_AMediaCodec_dequeueInputBuffer(SDL_AMediaCodec* acodec, int64_t timeoutUs)
{
    assert(acodec->func_dequeueInputBuffer);
    return acodec->func_dequeueInputBuffer(acodec, timeoutUs);
}

sdl_amedia_status_t SDL_AMediaCodec_queueInputBuffer(SDL_AMediaCodec* acodec, size_t idx, off_t offset, size_t size, uint64_t time, uint32_t flags)
{
    assert(acodec->func_queueInputBuffer);
    return acodec->func_queueInputBuffer(acodec, idx, offset, size, time, flags);
}

ssize_t SDL_AMediaCodec_dequeueOutputBuffer(SDL_AMediaCodec* acodec, SDL_AMediaCodecBufferInfo *info, int64_t timeoutUs)
{
    assert(acodec->func_dequeueOutputBuffer);
    return acodec->func_dequeueOutputBuffer(acodec, info, timeoutUs);
}

SDL_AMediaFormat* SDL_AMediaCodec_getOutputFormat(SDL_AMediaCodec* acodec)
{
    assert(acodec->func_getOutputFormat);
    return acodec->func_getOutputFormat(acodec);
}

sdl_amedia_status_t SDL_AMediaCodec_releaseOutputBuffer(SDL_AMediaCodec* acodec, size_t idx, bool render)
{
    assert(acodec->func_releaseOutputBuffer);
    return acodec->func_releaseOutputBuffer(acodec, idx, render);
}

bool SDL_AMediaCodec_isInputBuffersValid(SDL_AMediaCodec* acodec)
{
    assert(acodec->func_isInputBuffersValid);
    return acodec->func_isInputBuffersValid(acodec);
}

int SDL_AMediaCodec_getSerial(SDL_AMediaCodec* acodec)
{
    if (!acodec)
        return 0;
    return acodec->object_serial;
}

bool SDL_AMediaCodec_isSameSerial(SDL_AMediaCodec* acodec, int acodec_serial)
{
    if (acodec == NULL)
        return false;
    return acodec->object_serial == acodec_serial;
}
