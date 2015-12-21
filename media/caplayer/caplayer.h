/*
 * caplayer.h

 */

#ifndef CAPLAYER_ANDROID__CAPLAYER_H
#define CAPLAYER_ANDROID__CAPLAYER_H

#include <stdbool.h>
#include "ff_ffmsg_queue.h"

#include "capmeta.h"

#ifndef MPTRACE
#define MPTRACE ALOGD
#endif

typedef struct CapMediaPlayer CapMediaPlayer;
struct FFPlayer;
struct SDL_Vout;

/*-
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_IDLE);
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_INITIALIZED);
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_ASYNC_PREPARING);
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_PREPARED);
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_STARTED);
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_PAUSED);
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_COMPLETED);
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_STOPPED);
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_ERROR);
 MPST_CHECK_NOT_RET(mp->mp_state, MP_STATE_END);
 */

/*-
 * capmp_set_data_source()  -> MP_STATE_INITIALIZED
 *
 * capmp_reset              -> self
 * capmp_release            -> MP_STATE_END
 */
#define MP_STATE_IDLE               0

/*-
 * capmp_prepare_async()    -> MP_STATE_ASYNC_PREPARING
 *
 * capmp_reset              -> MP_STATE_IDLE
 * capmp_release            -> MP_STATE_END
 */
#define MP_STATE_INITIALIZED        1

/*-
 *                   ...    -> MP_STATE_PREPARED
 *                   ...    -> MP_STATE_ERROR
 *
 * capmp_reset              -> MP_STATE_IDLE
 * capmp_release            -> MP_STATE_END
 */
#define MP_STATE_ASYNC_PREPARING    2

/*-
 * capmp_seek_to()          -> self
 * capmp_start()            -> MP_STATE_STARTED
 *
 * capmp_reset              -> MP_STATE_IDLE
 * capmp_release            -> MP_STATE_END
 */
#define MP_STATE_PREPARED           3

/*-
 * capmp_seek_to()          -> self
 * capmp_start()            -> self
 * capmp_pause()            -> MP_STATE_PAUSED
 * capmp_stop()             -> MP_STATE_STOPPED
 *                   ...    -> MP_STATE_COMPLETED
 *                   ...    -> MP_STATE_ERROR
 *
 * capmp_reset              -> MP_STATE_IDLE
 * capmp_release            -> MP_STATE_END
 */
#define MP_STATE_STARTED            4

/*-
 * capmp_seek_to()          -> self
 * capmp_start()            -> MP_STATE_STARTED
 * capmp_pause()            -> self
 * capmp_stop()             -> MP_STATE_STOPPED
 *
 * capmp_reset              -> MP_STATE_IDLE
 * capmp_release            -> MP_STATE_END
 */
#define MP_STATE_PAUSED             5

/*-
 * capmp_seek_to()          -> self
 * capmp_start()            -> MP_STATE_STARTED (from beginning)
 * capmp_pause()            -> self
 * capmp_stop()             -> MP_STATE_STOPPED
 *
 * capmp_reset              -> MP_STATE_IDLE
 * capmp_release            -> MP_STATE_END
 */
#define MP_STATE_COMPLETED          6

/*-
 * capmp_stop()             -> self
 * capmp_prepare_async()    -> MP_STATE_ASYNC_PREPARING
 *
 * capmp_reset              -> MP_STATE_IDLE
 * capmp_release            -> MP_STATE_END
 */
#define MP_STATE_STOPPED            7

/*-
 * capmp_reset              -> MP_STATE_IDLE
 * capmp_release            -> MP_STATE_END
 */
#define MP_STATE_ERROR              8

/*-
 * capmp_release            -> self
 */
#define MP_STATE_END                9



#define CAPMP_IO_STAT_READ 1


#define CAPMP_OPT_CATEGORY_FORMAT FFP_OPT_CATEGORY_FORMAT
#define CAPMP_OPT_CATEGORY_CODEC  FFP_OPT_CATEGORY_CODEC
#define CAPMP_OPT_CATEGORY_SWS    FFP_OPT_CATEGORY_SWS
#define CAPMP_OPT_CATEGORY_PLAYER FFP_OPT_CATEGORY_PLAYER


void            capmp_global_init();
void            capmp_global_uninit();
void            capmp_global_set_log_report(int use_report);
void            capmp_global_set_log_level(int log_level);   // log_level = AV_LOG_xxx
void            capmp_global_set_inject_callback(cap_inject_callback cb);
const char     *capmp_version_ident();
unsigned int    capmp_version_int();
void            capmp_io_stat_register(void (*cb)(const char *url, int type, int bytes));
void            capmp_io_stat_complete_register(void (*cb)(const char *url,
                                                           int64_t read_bytes, int64_t total_size,
                                                           int64_t elpased_time, int64_t total_duration));

// ref_count is 1 after open
CapMediaPlayer *capmp_create(int (*msg_loop)(void*));
void            capmp_set_inject_opaque(CapMediaPlayer *mp, void *opaque);

void            capmp_set_option(CapMediaPlayer *mp, int opt_category, const char *name, const char *value);
void            capmp_set_option_int(CapMediaPlayer *mp, int opt_category, const char *name, int64_t value);

int             capmp_get_video_codec_info(CapMediaPlayer *mp, char **codec_info);
int             capmp_get_audio_codec_info(CapMediaPlayer *mp, char **codec_info);
void            capmp_set_playback_rate(CapMediaPlayer *mp, float rate);
int             capmp_set_stream_selected(CapMediaPlayer *mp, int stream, int selected);

float           capmp_get_property_float(CapMediaPlayer *mp, int id, float default_value);
void            capmp_set_property_float(CapMediaPlayer *mp, int id, float value);
int64_t         capmp_get_property_int64(CapMediaPlayer *mp, int id, int64_t default_value);
void            capmp_set_property_int64(CapMediaPlayer *mp, int id, int64_t value);

// must be freed with free();
CapMediaMeta   *capmp_get_meta_l(CapMediaPlayer *mp);

// preferred to be called explicity, can be called multiple times
// NOTE: capmp_shutdown may block thread
void            capmp_shutdown(CapMediaPlayer *mp);

void            capmp_inc_ref(CapMediaPlayer *mp);

// call close at last release, also free memory
// NOTE: capmp_dec_ref may block thread
void            capmp_dec_ref(CapMediaPlayer *mp);
void            capmp_dec_ref_p(CapMediaPlayer **pmp);

int             capmp_set_data_source(CapMediaPlayer *mp, const char *url);
int             capmp_prepare_async(CapMediaPlayer *mp);
int             capmp_start(CapMediaPlayer *mp);
int             capmp_pause(CapMediaPlayer *mp);
int             capmp_stop(CapMediaPlayer *mp);
int             capmp_seek_to(CapMediaPlayer *mp, long msec);
int             capmp_get_state(CapMediaPlayer *mp);
bool            capmp_is_playing(CapMediaPlayer *mp);
long            capmp_get_current_position(CapMediaPlayer *mp);
long            capmp_get_duration(CapMediaPlayer *mp);
long            capmp_get_playable_duration(CapMediaPlayer *mp);
void            capmp_set_loop(CapMediaPlayer *mp, int loop);
int             capmp_get_loop(CapMediaPlayer *mp);

void           *capmp_get_weak_thiz(CapMediaPlayer *mp);
void           *capmp_set_weak_thiz(CapMediaPlayer *mp, void *weak_thiz);

/* return < 0 if aborted, 0 if no packet and > 0 if packet.  */
int             capmp_get_msg(CapMediaPlayer *mp, AVMessage *msg, int block);

#endif
