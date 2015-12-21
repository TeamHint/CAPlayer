#ifndef ANDROID_NDK_PROF__PROF_H
#define ANDROID_NDK_PROF__PROF_H

#ifdef __cplusplus
extern "C" {
#endif

void monstartup(const char *libname);
void moncleanup(void);

#ifdef __cplusplus
}
#endif

#endif//ANDROID_NDK_PROF__PROF_H
