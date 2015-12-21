/*
 * capavformat.h

 */

#ifndef FFPLAY__CAPAVFORMAT_CAPAVFORMAT_H
#define FFPLAY__CAPAVFORMAT_CAPAVFORMAT_H

void capav_register_all(void);

#define AV_PKT_FLAG_DISCONTINUITY 0x0100

/**
 * Injection
 */

typedef struct CAPAVInject_OnUrlOpenData {
    size_t  size;
    char    url[4096];      /* in, out */
    int     segment_index;  /* in, default = 0 */
    int     retry_counter;  /* in */

    int     is_handled;     /* out, default = false */
    int     is_url_changed; /* out, default = false */
} CAPAVInject_OnUrlOpenData;

/**
 * Resolve segment url from concatdec
 *
 * @param data      CAPAVInject_OnUrlOpenData*
 * @param data_size size of CAPAVInject_OnUrlOpenData;
 * @return 0 if OK, AVERROR_xxx otherwise
 */
#define CAPAVINJECT_CONCAT_RESOLVE_SEGMENT  0x10000

/**
 * Protocol open event
 *
 * @param data      CAPAVInject_OnUrlOpenData*
 * @param data_size size of CAPAVInject_OnUrlOpenData;
 * @return 0 if OK, AVERROR_xxx otherwise
 */
#define CAPAVINJECT_ON_TCP_OPEN         0x10001
#define CAPAVINJECT_ON_HTTP_OPEN        0x10002
#define CAPAVINJECT_ON_HTTP_RETRY       0x10003
#define CAPAVINJECT_ON_LIVE_RETRY       0x10004

typedef int (*CapAVInjectCallback)(void *opaque, int message, void *data, size_t data_size);

CapAVInjectCallback capav_register_inject_callback(CapAVInjectCallback callback);
CapAVInjectCallback capav_get_inject_callback();

#endif
