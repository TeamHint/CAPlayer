/*
 * ffpipenode_ffplay_vdec.h

 */

#ifndef FFPLAY__FF_FFPIPENODE_FFPLAY_VDEC_H
#define FFPLAY__FF_FFPIPENODE_FFPLAY_VDEC_H

#include "../ff_ffpipenode.h"

struct FFPlayer;

CAPFF_Pipenode *ffpipenode_create_video_decoder_from_ffplay(struct FFPlayer *ffp);

#endif
