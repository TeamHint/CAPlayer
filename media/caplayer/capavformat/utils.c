/*
 * utils.c

 */

#include <stdlib.h>
#include "capavformat.h"

static CapAVInjectCallback s_av_inject_callback = NULL;

CapAVInjectCallback capav_register_inject_callback(CapAVInjectCallback callback)
{
    CapAVInjectCallback prev_callback = s_av_inject_callback;
    s_av_inject_callback = callback;
    return prev_callback;
}

CapAVInjectCallback capav_get_inject_callback()
{
    return s_av_inject_callback;
}
