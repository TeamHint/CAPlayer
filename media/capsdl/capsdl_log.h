/*****************************************************************************
 * capsdl_log.h
 *****************************************************************************

 */

#ifndef CAPSDL__CAPSDL_LOG_H
#define CAPSDL__CAPSDL_LOG_H

#include <stdio.h>

#ifdef __ANDROID__

#include <android/log.h>

#define CAP_LOG_UNKNOWN     ANDROID_LOG_UNKNOWN
#define CAP_LOG_DEFAULT     ANDROID_LOG_DEFAULT

#define CAP_LOG_VERBOSE     ANDROID_LOG_VERBOSE
#define CAP_LOG_DEBUG       ANDROID_LOG_DEBUG
#define CAP_LOG_INFO        ANDROID_LOG_INFO
#define CAP_LOG_WARN        ANDROID_LOG_WARN
#define CAP_LOG_ERROR       ANDROID_LOG_ERROR
#define CAP_LOG_FATAL       ANDROID_LOG_FATAL
#define CAP_LOG_SILENT      ANDROID_LOG_SILENT

#define VLOG(level, TAG, ...)    ((void)__android_log_vprint(level, TAG, __VA_ARGS__))
#define ALOG(level, TAG, ...)    ((void)__android_log_print(level, TAG, __VA_ARGS__))

#else

#define CAP_LOG_UNKNOWN     0
#define CAP_LOG_DEFAULT     1

#define CAP_LOG_VERBOSE     2
#define CAP_LOG_DEBUG       3
#define CAP_LOG_INFO        4
#define CAP_LOG_WARN        5
#define CAP_LOG_ERROR       6
#define CAP_LOG_FATAL       7
#define CAP_LOG_SILENT      8

#define VLOG(level, TAG, ...)    ((void)vprintf(__VA_ARGS__))
#define ALOG(level, TAG, ...)    ((void)printf(__VA_ARGS__))

#endif

#define CAP_LOG_TAG "CAPMEDIA"

#define VLOGV(...)  VLOG(CAP_LOG_VERBOSE,   CAP_LOG_TAG, __VA_ARGS__)
#define VLOGD(...)  VLOG(CAP_LOG_DEBUG,     CAP_LOG_TAG, __VA_ARGS__)
#define VLOGI(...)  VLOG(CAP_LOG_INFO,      CAP_LOG_TAG, __VA_ARGS__)
#define VLOGW(...)  VLOG(CAP_LOG_WARN,      CAP_LOG_TAG, __VA_ARGS__)
#define VLOGE(...)  VLOG(CAP_LOG_ERROR,     CAP_LOG_TAG, __VA_ARGS__)

#define ALOGV(...)  ALOG(CAP_LOG_VERBOSE,   CAP_LOG_TAG, __VA_ARGS__)
#define ALOGD(...)  ALOG(CAP_LOG_DEBUG,     CAP_LOG_TAG, __VA_ARGS__)
#define ALOGI(...)  ALOG(CAP_LOG_INFO,      CAP_LOG_TAG, __VA_ARGS__)
#define ALOGW(...)  ALOG(CAP_LOG_WARN,      CAP_LOG_TAG, __VA_ARGS__)
#define ALOGE(...)  ALOG(CAP_LOG_ERROR,     CAP_LOG_TAG, __VA_ARGS__)
#define LOG_ALWAYS_FATAL(...)   do { ALOGE(__VA_ARGS__); exit(1); } while (0)

#endif
