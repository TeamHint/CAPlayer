/*
 * opt.h

 */

#ifndef FFPLAY__CAPOPT_H
#define FFPLAY__CAPOPT_H

#include "libavutil/opt.h"

#define CAPAV_OPTION_INT(default__, min__, max__) \
    .type = AV_OPT_TYPE_INT, \
    { .i64 = default__ }, \
    .min = min__, \
    .max = max__, \
    .flags = AV_OPT_FLAG_DECODING_PARAM

#define CAPAV_OPTION_INT64(default__, min__, max__) \
    .type = AV_OPT_TYPE_INT64, \
    { .i64 = default__ }, \
    .min = min__, \
    .max = max__, \
    .flags = AV_OPT_FLAG_DECODING_PARAM

#define CAPAV_OPTION_CONST(default__) \
    .type = AV_OPT_TYPE_CONST, \
    { .i64 = default__ }, \
    .min = INT_MIN, \
    .max = INT_MAX, \
    .flags = AV_OPT_FLAG_DECODING_PARAM

#define CAPAV_OPTION_STR(default__) \
    .type = AV_OPT_TYPE_STRING, \
    { .str = default__ }, \
    .min = 0, \
    .max = 0, \
    .flags = AV_OPT_FLAG_DECODING_PARAM

#endif
