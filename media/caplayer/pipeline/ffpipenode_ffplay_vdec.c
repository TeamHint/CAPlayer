/*
 * ffpipenode_ffplay_vdec.c

 */

#include "ffpipenode_ffplay_vdec.h"
#include "../ff_ffpipenode.h"
#include "../ff_ffplay.h"

struct CAPFF_Pipenode_Opaque {
    FFPlayer *ffp;
};

static void func_destroy(CAPFF_Pipenode *node)
{
    // do nothing
}

static int func_run_sync(CAPFF_Pipenode *node)
{
    CAPFF_Pipenode_Opaque *opaque = node->opaque;

    return ffp_video_thread(opaque->ffp);
}

CAPFF_Pipenode *ffpipenode_create_video_decoder_from_ffplay(FFPlayer *ffp)
{
    CAPFF_Pipenode *node = ffpipenode_alloc(sizeof(CAPFF_Pipenode_Opaque));
    if (!node)
        return node;

    CAPFF_Pipenode_Opaque *opaque = node->opaque;
    opaque->ffp         = ffp;

    node->func_destroy  = func_destroy;
    node->func_run_sync = func_run_sync;

    ffp_set_video_codec_info(ffp, AVCODEC_MODULE_NAME, avcodec_get_name(ffp->is->viddec.avctx->codec_id));
    return node;
}
