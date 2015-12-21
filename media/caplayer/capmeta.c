/*
 * capmeta.c

 */

#include "capmeta.h"
#include "ff_ffinc.h"
#include "capsdl/capsdl_misc.h"

#define CAP_META_INIT_CAPACITY 13

struct CapMediaMeta {
    SDL_mutex *mutex;

    AVDictionary *dict;

    size_t children_count;
    size_t children_capacity;
    CapMediaMeta **children;
};

CapMediaMeta *capmeta_create()
{
    CapMediaMeta *meta = (CapMediaMeta *)calloc(1, sizeof(CapMediaMeta));
    if (!meta)
        return NULL;

    meta->mutex = SDL_CreateMutex();
    if (!meta->mutex)
        goto fail;

    return meta;
fail:
    capmeta_destroy(meta);
    return NULL;
}

void capmeta_reset(CapMediaMeta *meta)
{
    if (meta && meta->dict)
        av_dict_free(&meta->dict);
}

void capmeta_destroy(CapMediaMeta *meta)
{
    if (!meta)
        return;

    if (meta->dict) {
        av_dict_free(&meta->dict);
    }

    if (meta->children) {
        for(int i = 0; i < meta->children_count; ++i) {
            CapMediaMeta *child = meta->children[i];
            if (child) {
                capmeta_destroy(child);
            }
        }
        free(meta->children);
        meta->children = NULL;
    }

    SDL_DestroyMutexP(&meta->mutex);
}

void capmeta_destroy_p(CapMediaMeta **meta)
{
    if (!meta)
        return;

    capmeta_destroy(*meta);
    *meta = NULL;
}

void capmeta_lock(CapMediaMeta *meta)
{
    if (!meta || !meta->mutex)
        return;

    SDL_LockMutex(meta->mutex);
}

void capmeta_unlock(CapMediaMeta *meta)
{
    if (!meta || !meta->mutex)
        return;

    SDL_UnlockMutex(meta->mutex);
}

void capmeta_append_child_l(CapMediaMeta *meta, CapMediaMeta *child)
{
    if (!meta || !child)
        return;

    if (!meta->children) {
        meta->children = (CapMediaMeta **)calloc(CAP_META_INIT_CAPACITY, sizeof(CapMediaMeta *));
        if (!meta->children)
            return;
        meta->children_count    = 0;
        meta->children_capacity = CAP_META_INIT_CAPACITY;
    } else if (meta->children_count >= meta->children_capacity) {
        size_t new_capacity = meta->children_capacity * 2;
        CapMediaMeta **new_children = (CapMediaMeta **)calloc(new_capacity, sizeof(CapMediaMeta *));
        if (!new_children)
            return;

        memcpy(new_children, meta->children, meta->children_capacity * sizeof(CapMediaMeta *));
        free(meta->children);
        meta->children          = new_children;
        meta->children_capacity = new_capacity;
    }

    meta->children[meta->children_count] = child;
    meta->children_count++;
}

void capmeta_set_int64_l(CapMediaMeta *meta, const char *name, int64_t value)
{
    if (!meta)
        return;

    av_dict_set_int(&meta->dict, name, value, 0);
}

void capmeta_set_string_l(CapMediaMeta *meta, const char *name, const char *value)
{
    if (!meta)
        return;

    av_dict_set(&meta->dict, name, value, 0);
}

static int get_bit_rate(AVCodecContext *ctx)
{
    int bit_rate;
    int bits_per_sample;

    switch (ctx->codec_type) {
        case AVMEDIA_TYPE_VIDEO:
        case AVMEDIA_TYPE_DATA:
        case AVMEDIA_TYPE_SUBTITLE:
        case AVMEDIA_TYPE_ATTACHMENT:
            bit_rate = ctx->bit_rate;
            break;
        case AVMEDIA_TYPE_AUDIO:
            bits_per_sample = av_get_bits_per_sample(ctx->codec_id);
            bit_rate = bits_per_sample ? ctx->sample_rate * ctx->channels * bits_per_sample : ctx->bit_rate;
            break;
        default:
            bit_rate = 0;
            break;
    }
    return bit_rate;
}

void capmeta_set_avformat_context_l(CapMediaMeta *meta, AVFormatContext *ic)
{
    if (!meta || !ic)
        return;

    if (ic->iformat && ic->iformat->name)
        capmeta_set_string_l(meta, CAPM_KEY_FORMAT, ic->iformat->name);

    if (ic->duration != AV_NOPTS_VALUE)
        capmeta_set_int64_l(meta, CAPM_KEY_DURATION_US, ic->duration);

    if (ic->start_time != AV_NOPTS_VALUE)
        capmeta_set_int64_l(meta, CAPM_KEY_START_US, ic->start_time);

    if (ic->bit_rate)
        capmeta_set_int64_l(meta, CAPM_KEY_BITRATE, ic->bit_rate);

    CapMediaMeta *stream_meta = NULL;
    for (int i = 0; i < ic->nb_streams; i++) {
        if (!stream_meta)
            capmeta_destroy_p(&stream_meta);

        AVStream *st = ic->streams[i];
        if (!st || !st->codec)
            continue;

        stream_meta = capmeta_create();
        if (!stream_meta)
            continue;

        AVCodecContext *avctx = st->codec;
        const char *codec_name = avcodec_get_name(avctx->codec_id);
        if (codec_name)
            capmeta_set_string_l(stream_meta, CAPM_KEY_CODEC_NAME, codec_name);
        if (avctx->profile != FF_PROFILE_UNKNOWN) {
            const AVCodec *codec = avctx->codec ? avctx->codec : avcodec_find_decoder(avctx->codec_id);
            if (codec) {
                const char *profile = av_get_profile_name(codec, avctx->profile);
                if (profile)
                    capmeta_set_string_l(stream_meta, CAPM_KEY_CODEC_PROFILE, profile);
                if (codec->long_name)
                    capmeta_set_string_l(stream_meta, CAPM_KEY_CODEC_LONG_NAME, codec->long_name);
                capmeta_set_int64_l(stream_meta, CAPM_KEY_CODEC_LEVEL, avctx->level);
                if (avctx->pix_fmt != AV_PIX_FMT_NONE)
                    capmeta_set_string_l(stream_meta, CAPM_KEY_CODEC_PIXEL_FORMAT, av_get_pix_fmt_name(avctx->pix_fmt));
            }
        }

        int64_t bitrate = get_bit_rate(avctx);
        if (bitrate > 0) {
            capmeta_set_int64_l(stream_meta, CAPM_KEY_BITRATE, bitrate);
        }

        switch (avctx->codec_type) {
            case AVMEDIA_TYPE_VIDEO: {
                capmeta_set_string_l(stream_meta, CAPM_KEY_TYPE, CAPM_VAL_TYPE__VIDEO);

                if (avctx->width > 0)
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_WIDTH, avctx->width);
                if (avctx->height > 0)
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_HEIGHT, avctx->height);
                if (st->sample_aspect_ratio.num > 0 && st->sample_aspect_ratio.den > 0) {
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_SAR_NUM, avctx->sample_aspect_ratio.num);
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_SAR_DEN, avctx->sample_aspect_ratio.den);
                }

                if (st->avg_frame_rate.num > 0 && st->avg_frame_rate.den > 0) {
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_FPS_NUM, st->avg_frame_rate.num);
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_FPS_DEN, st->avg_frame_rate.den);
                }
                if (st->r_frame_rate.num > 0 && st->r_frame_rate.den > 0) {
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_TBR_NUM, st->avg_frame_rate.num);
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_TBR_DEN, st->avg_frame_rate.den);
                }
                break;
            }
            case AVMEDIA_TYPE_AUDIO: {
                capmeta_set_string_l(stream_meta, CAPM_KEY_TYPE, CAPM_VAL_TYPE__AUDIO);

                if (avctx->sample_rate)
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_SAMPLE_RATE, avctx->sample_rate);
                if (avctx->channel_layout)
                    capmeta_set_int64_l(stream_meta, CAPM_KEY_CHANNEL_LAYOUT, avctx->channel_layout);
                break;
            }
            default: {
                capmeta_set_string_l(stream_meta, CAPM_KEY_TYPE, CAPM_VAL_TYPE__UNKNOWN);
                break;
            }
        }

        capmeta_append_child_l(meta, stream_meta);
        stream_meta = NULL;
    }

    if (!stream_meta)
        capmeta_destroy_p(&stream_meta);
}

const char *capmeta_get_string_l(CapMediaMeta *meta, const char *name)
{
    if (!meta || !meta->dict)
        return NULL;

    AVDictionaryEntry *entry = av_dict_get(meta->dict, name, NULL, 0);
    if (!entry)
        return NULL;

    return entry->value;
}

int64_t capmeta_get_int64_l(CapMediaMeta *meta, const char *name, int64_t defaultValue)
{
    if (!meta || !meta->dict)
        return defaultValue;

    AVDictionaryEntry *entry = av_dict_get(meta->dict, name, NULL, 0);
    if (!entry || !entry->value)
        return defaultValue;

    return atoll(entry->value);
}

size_t capmeta_get_children_count_l(CapMediaMeta *meta)
{
    if (!meta || !meta->children)
        return 0;

    return meta->children_count;
}

CapMediaMeta *capmeta_get_child_l(CapMediaMeta *meta, size_t index)
{
    if (!meta)
        return NULL;

    if (index >= meta->children_count)
        return NULL;

    return meta->children[index];
}
