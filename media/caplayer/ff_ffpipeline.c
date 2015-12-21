/*
 * ff_ffpipeline.c

 */

#include "ff_ffpipeline.h"
#include <stdlib.h>
#include <string.h>

CAPFF_Pipeline *ffpipeline_alloc(SDL_Class *opaque_class, size_t opaque_size)
{
    CAPFF_Pipeline *pipeline = (CAPFF_Pipeline*) calloc(1, sizeof(CAPFF_Pipeline));
    if (!pipeline)
        return NULL;

    pipeline->opaque_class = opaque_class;
    pipeline->opaque       = calloc(1, opaque_size);
    if (!pipeline->opaque) {
        free(pipeline);
        return NULL;
    }

    return pipeline;
}

void ffpipeline_free(CAPFF_Pipeline *pipeline)
{
    if (!pipeline)
        return;

    if (pipeline->func_destroy) {
        pipeline->func_destroy(pipeline);
    }

    free(pipeline->opaque);
    memset(pipeline, 0, sizeof(CAPFF_Pipeline));
    free(pipeline);
}

void ffpipeline_free_p(CAPFF_Pipeline **pipeline)
{
    if (!pipeline)
        return;

    ffpipeline_free(*pipeline);
}

CAPFF_Pipenode* ffpipeline_open_video_decoder(CAPFF_Pipeline *pipeline, FFPlayer *ffp)
{
    return pipeline->func_open_video_decoder(pipeline, ffp);
}

SDL_Aout *ffpipeline_open_audio_output(CAPFF_Pipeline *pipeline, FFPlayer *ffp)
{
    return pipeline->func_open_audio_output(pipeline, ffp);
}
