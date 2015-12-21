/*
 * ff_ffpipenode.h

 */

#ifndef FFPLAY__FF_FFPIPENODE_H
#define FFPLAY__FF_FFPIPENODE_H

#include "capsdl/capsdl_mutex.h"

typedef struct CAPFF_Pipenode_Opaque CAPFF_Pipenode_Opaque;
typedef struct CAPFF_Pipenode CAPFF_Pipenode;
struct CAPFF_Pipenode {
    SDL_mutex *mutex;
    void *opaque;

    void (*func_destroy) (CAPFF_Pipenode *node);
    int  (*func_run_sync)(CAPFF_Pipenode *node);
    int  (*func_flush)   (CAPFF_Pipenode *node); // optional
};

CAPFF_Pipenode *ffpipenode_alloc(size_t opaque_size);
void ffpipenode_free(CAPFF_Pipenode *node);
void ffpipenode_free_p(CAPFF_Pipenode **node);

int  ffpipenode_run_sync(CAPFF_Pipenode *node);
int  ffpipenode_flush(CAPFF_Pipenode *node);

#endif
