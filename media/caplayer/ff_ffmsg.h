/*
 * ff_ffmsg.h
 *      based on PacketQueue in ffplay.c

 */

#ifndef FFPLAY__FF_FFMSG_H
#define FFPLAY__FF_FFMSG_H

#define FFP_MSG_FLUSH                       0
#define FFP_MSG_ERROR                       100     /* arg1 = error */
#define FFP_MSG_PREPARED                    200
#define FFP_MSG_COMPLETED                   300
#define FFP_MSG_VIDEO_SIZE_CHANGED          400     /* arg1 = width, arg2 = height */
#define FFP_MSG_SAR_CHANGED                 401     /* arg1 = sar.num, arg2 = sar.den */
#define FFP_MSG_VIDEO_RENDERING_START       402
#define FFP_MSG_AUDIO_RENDERING_START       403
#define FFP_MSG_VIDEO_ROTATION_CHANGED      404     /* arg1 = degree */
#define FFP_MSG_BUFFERING_START             500
#define FFP_MSG_BUFFERING_END               501
#define FFP_MSG_BUFFERING_UPDATE            502     /* arg1 = buffering head position in time, arg2 = minimum percent in time or bytes */
#define FFP_MSG_BUFFERING_BYTES_UPDATE      503     /* arg1 = cached data in bytes,            arg2 = high water mark */
#define FFP_MSG_BUFFERING_TIME_UPDATE       504     /* arg1 = cached duration in milliseconds, arg2 = high water mark */
#define FFP_MSG_SEEK_COMPLETE               600
#define FFP_MSG_PLAYBACK_STATE_CHANGED      700

#define FFP_MSG_VIDEO_DECODER_OPEN          10001

#define FFP_REQ_START                       20001
#define FFP_REQ_PAUSE                       20002
#define FFP_REQ_SEEK                        20003

#define FFP_PROP_FLOAT_VIDEO_DECODE_FRAMES_PER_SECOND   10001
#define FFP_PROP_FLOAT_VIDEO_OUTPUT_FRAMES_PER_SECOND   10002
#define FFP_PROP_FLOAT_PLAYBACK_RATE                    10003

#define FFP_PROP_INT64_SELECTED_VIDEO_STREAM              20001
#define FFP_PROP_INT64_SELECTED_AUDIO_STREAM              20002

#endif
