/*****************************************************************************
 * capsdl_thread.h
 *****************************************************************************

 */

#ifndef CAPSDL__CAPSDL_TIMER_H
#define CAPSDL__CAPSDL_TIMER_H

#include "capsdl_stdinc.h"

void SDL_Delay(Uint32 ms);

Uint64 SDL_GetTickHR(void);


typedef struct SDL_Profiler
{
    int64_t total_elapsed;
    int     total_counter;

    int64_t sample_elapsed;
    int     sample_counter;
    float   sample_per_seconds;
    int64_t average_elapsed;

    int64_t begin_time;

    int     max_sample;
} SDL_Profiler;

void    SDL_ProfilerReset(SDL_Profiler* profiler, int max_sample);
void    SDL_ProfilerBegin(SDL_Profiler* profiler);
int64_t SDL_ProfilerEnd(SDL_Profiler* profiler);

typedef struct SDL_SpeedSampler
{
    Uint64  samples[10];

    int     capacity;
    int     count;
    int     first_index;
    int     next_index;

    Uint64  last_log_time;
} SDL_SpeedSampler;

void  SDL_SpeedSamplerReset(SDL_SpeedSampler *sampler);
// return samples per seconds
float SDL_SpeedSamplerAdd(SDL_SpeedSampler *sampler, int enable_log, const char *log_tag);

#endif
