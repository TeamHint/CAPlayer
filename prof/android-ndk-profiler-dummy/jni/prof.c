#include "prof.h"
#include <android/log.h>

extern void monstartup(const char *libname)
{
    __android_log_print(ANDROID_LOG_DEBUG, "aprof-fake", "fake-monstartup %s\n", libname);
}

extern void moncleanup(void)
{
    __android_log_print(ANDROID_LOG_DEBUG, "aprof-fake", "fake-momcleanup\n");
}
