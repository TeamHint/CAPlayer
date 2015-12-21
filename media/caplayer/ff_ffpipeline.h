/*
 * ff_ffpipeline.h

 */

#ifndef FFPLAY__FF_FFPIPELINE_H
#define FFPLAY__FF_FFPIPELINE_H

#include "capsdl/capsdl_class.h"
#include "capsdl/capsdl_mutex.h"
#include "capsdl/capsdl_aout.h"
#include "ff_ffpipenode.h"
#include "ff_ffplay_def.h"

typedef struct CAPFF_Pipeline_Opaque CAPFF_Pipeline_Opaque;
typedef struct CAPFF_Pipeline CAPFF_Pipeline;
struct CAPFF_Pipeline {
    SDL_Class             *opaque_class;
    CAPFF_Pipeline_Opaque *opaque;

    void            (*func_destroy)             (CAPFF_Pipeline *pipeline);
    CAPFF_Pipenode *(*func_open_video_decoder)  (CAPFF_Pipeline *pipeline, FFPlayer *ffp);
    SDL_Aout       *(*func_open_audio_output)   (CAPFF_Pipeline *pipeline, FFPlayer *ffp);
};

CAPFF_Pipeline *ffpipeline_alloc(SDL_Class *opaque_class, size_t opaque_size);
void ffpipeline_free(CAPFF_Pipeline *pipeline);
void ffpipeline_free_p(CAPFF_Pipeline **pipeline);

CAPFF_Pipenode *ffpipeline_open_video_decoder(CAPFF_Pipeline *pipeline, FFPlayer *ffp);
SDL_Aout       *ffpipeline_open_audio_output(CAPFF_Pipeline *pipeline, FFPlayer *ffp);

#endif
