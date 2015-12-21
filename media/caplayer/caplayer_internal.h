/*
 * caplayer_internal.h

 */

#ifndef CAPLAYER_ANDROID__CAPLAYER_INTERNAL_H
#define CAPLAYER_ANDROID__CAPLAYER_INTERNAL_H

#include <assert.h>
#include "capsdl/capsdl.h"
#include "ff_fferror.h"
#include "ff_ffplay.h"
#include "caplayer.h"

struct CapMediaPlayer {
    volatile int ref_count;
    pthread_mutex_t mutex;
    FFPlayer *ffplayer;

    int (*msg_loop)(void*);
    SDL_Thread *msg_thread;
    SDL_Thread _msg_thread;

    int mp_state;
    char *data_source;
    void *weak_thiz;

    int restart;
    int restart_from_beginning;
    int seek_req;
    long seek_msec;
};

#endif
