/*
 * ffpipeline_ffplay.c

 */

#include "ffpipeline_ffplay.h"
#include "ffpipenode_ffplay_vdec.h"
#include "../ff_ffplay.h"

static SDL_Class g_pipeline_class = {
    .name = "ffpipeline_ffplay",
};

struct CAPFF_Pipeline_Opaque {
    FFPlayer *ffp;
};

static void func_destroy(CAPFF_Pipeline *pipeline)
{
    // do nothing
}

static CAPFF_Pipenode *func_open_video_decoder(CAPFF_Pipeline *pipeline, FFPlayer *ffp)
{
    return ffpipenode_create_video_decoder_from_ffplay(ffp);
}

static SDL_Aout *func_open_audio_output(CAPFF_Pipeline *pipeline, FFPlayer *ffp)
{
    return NULL;
}

CAPFF_Pipeline *ffpipeline_create_from_ffplay(FFPlayer *ffp)
{
    CAPFF_Pipeline *pipeline = ffpipeline_alloc(&g_pipeline_class, sizeof(CAPFF_Pipeline_Opaque));
    if (!pipeline)
        return pipeline;

    CAPFF_Pipeline_Opaque *opaque = pipeline->opaque;
    opaque->ffp                   = ffp;

    pipeline->func_destroy            = func_destroy;
    pipeline->func_open_video_decoder = func_open_video_decoder;
    pipeline->func_open_audio_output  = func_open_audio_output;

    return pipeline;
}
