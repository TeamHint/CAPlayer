/*
 * ffpipenode_android_mediacodec_vdec.h

 */

#ifndef FFPLAY__FF_FFPIPENODE_ANDROID_MEDIACODEC_VDEC_H
#define FFPLAY__FF_FFPIPENODE_ANDROID_MEDIACODEC_VDEC_H

#include "../../ff_ffpipenode.h"
#include "../../ff_ffpipeline.h"
#include "capsdl/capsdl_vout.h"

typedef struct FFPlayer FFPlayer;

CAPFF_Pipenode *ffpipenode_create_video_decoder_from_android_mediacodec(FFPlayer *ffp, CAPFF_Pipeline *pipeline, SDL_Vout *vout);

#endif
