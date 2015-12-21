/*****************************************************************************
 * capsdl_aout_android_audiotrack.h
 *****************************************************************************

 */

#ifndef CAPSDL_ANDROID__CAPSDL_AOUT_ANDROID_AUDIOTRACK_H
#define CAPSDL_ANDROID__CAPSDL_AOUT_ANDROID_AUDIOTRACK_H

#include "../capsdl_aout.h"

SDL_Aout *SDL_AoutAndroid_CreateForAudioTrack();
bool      SDL_AoutAndroid_IsObjectOfAudioTrack(SDL_Aout *aout);

#endif
