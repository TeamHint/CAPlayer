/*
 * capsdl_ffinc.h
 *      ffmpeg headers

 */

#ifndef CAPSDL__FFMPEG__CAPSDL_IMAGE_CONVERT_H
#define CAPSDL__FFMPEG__CAPSDL_IMAGE_CONVERT_H

#include <stdint.h>
#include "capsdl_inc_ffmpeg.h"

int cap_image_convert(int width, int height,
    enum AVPixelFormat dst_format, uint8_t **dst_data, int *dst_linesize,
    enum AVPixelFormat src_format, const uint8_t **src_data, const int *src_linesize);

#endif
