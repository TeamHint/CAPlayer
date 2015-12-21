/*
 * ff_ffpipeline_vdec.c
*/

#include "ff_ffpipenode.h"
#include <stdlib.h>
#include <string.h>

CAPFF_Pipenode *ffpipenode_alloc(size_t opaque_size)
{
    CAPFF_Pipenode *node = (CAPFF_Pipenode*) calloc(1, sizeof(CAPFF_Pipenode));
    if (!node)
        return NULL;

    node->opaque = calloc(1, opaque_size);
    if (!node->opaque) {
        free(node);
        return NULL;
    }

    node->mutex = SDL_CreateMutex();
    if (node->mutex == NULL) {
        free(node->opaque);
        free(node);
        return NULL;
    }

    return node;
}

void ffpipenode_free(CAPFF_Pipenode *node)
{
    if (!node)
        return;

    if (node->func_destroy) {
        node->func_destroy(node);
    }

    SDL_DestroyMutexP(&node->mutex);

    free(node->opaque);
    memset(node, 0, sizeof(CAPFF_Pipenode));
    free(node);
}

void ffpipenode_free_p(CAPFF_Pipenode **node)
{
    if (!node)
        return;

    ffpipenode_free(*node);
    *node = NULL;
}

int ffpipenode_run_sync(CAPFF_Pipenode *node)
{
    return node->func_run_sync(node);
}

int ffpipenode_flush(CAPFF_Pipenode *node)
{
    if (!node || !node->func_flush)
        return 0;

    return node->func_flush(node);
}
