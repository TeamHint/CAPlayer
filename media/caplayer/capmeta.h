/*
 * capmeta.h

 */

#ifndef CAPLAYER__CAPMETA_H
#define CAPLAYER__CAPMETA_H

#include <stdint.h>
#include <stdlib.h>

// media meta
#define CAPM_KEY_FORMAT         "format"
#define CAPM_KEY_DURATION_US    "duration_us"
#define CAPM_KEY_START_US       "start_us"
#define CAPM_KEY_BITRATE        "bitrate"
#define CAPM_KEY_VIDEO_STREAM   "video"
#define CAPM_KEY_AUDIO_STREAM   "audio"

// stream meta
#define CAPM_KEY_TYPE           "type"
#define CAPM_VAL_TYPE__VIDEO    "video"
#define CAPM_VAL_TYPE__AUDIO    "audio"
#define CAPM_VAL_TYPE__UNKNOWN  "unknown"

#define CAPM_KEY_CODEC_NAME         "codec_name"
#define CAPM_KEY_CODEC_PROFILE      "codec_profile"
#define CAPM_KEY_CODEC_LEVEL        "codec_level"
#define CAPM_KEY_CODEC_LONG_NAME    "codec_long_name"
#define CAPM_KEY_CODEC_PIXEL_FORMAT "codec_pixel_format"

// stream: video
#define CAPM_KEY_WIDTH          "width"
#define CAPM_KEY_HEIGHT         "height"
#define CAPM_KEY_FPS_NUM        "fps_num"
#define CAPM_KEY_FPS_DEN        "fps_den"
#define CAPM_KEY_TBR_NUM        "tbr_num"
#define CAPM_KEY_TBR_DEN        "tbr_den"
#define CAPM_KEY_SAR_NUM        "sar_num"
#define CAPM_KEY_SAR_DEN        "sar_den"
// stream: audio
#define CAPM_KEY_SAMPLE_RATE    "sample_rate"
#define CAPM_KEY_CHANNEL_LAYOUT "channel_layout"

// reserved for user
#define CAPM_KEY_STREAMS        "streams"

struct AVFormatContext;
typedef struct CapMediaMeta CapMediaMeta;

CapMediaMeta *capmeta_create();
void capmeta_reset(CapMediaMeta *meta);
void capmeta_destroy(CapMediaMeta *meta);
void capmeta_destroy_p(CapMediaMeta **meta);

void capmeta_lock(CapMediaMeta *meta);
void capmeta_unlock(CapMediaMeta *meta);

void capmeta_append_child_l(CapMediaMeta *meta, CapMediaMeta *child);
void capmeta_set_int64_l(CapMediaMeta *meta, const char *name, int64_t value);
void capmeta_set_string_l(CapMediaMeta *meta, const char *name, const char *value);
void capmeta_set_avformat_context_l(CapMediaMeta *meta, struct AVFormatContext *ic);

// must be freed with free();
const char   *capmeta_get_string_l(CapMediaMeta *meta, const char *name);
int64_t       capmeta_get_int64_l(CapMediaMeta *meta, const char *name, int64_t defaultValue);
size_t        capmeta_get_children_count_l(CapMediaMeta *meta);
// do not free
CapMediaMeta *capmeta_get_child_l(CapMediaMeta *meta, size_t index);

#endif//CAPLAYER__CAPMETA_H
