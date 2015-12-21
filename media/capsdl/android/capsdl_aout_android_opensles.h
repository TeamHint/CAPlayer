/*****************************************************************************
 * capsdl_aout_android_opensles.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__CAPSDL_AOUT_ANDROID_OPENSLES_H
#define CAPSDL_ANDROID__CAPSDL_AOUT_ANDROID_OPENSLES_H

#include "../capsdl_aout.h"

SDL_Aout *SDL_AoutAndroid_CreateForOpenSLES();
bool      SDL_AoutAndroid_IsObjectOfOpenSLES(SDL_Aout *aout);

#endif
