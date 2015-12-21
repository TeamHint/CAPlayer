/*****************************************************************************
 * capsdl_misc.h
 *****************************************************************************

 */

#ifndef CAPSDL__CAPSDL_MISC_H
#define CAPSDL__CAPSDL_MISC_H

#include <stdlib.h>
#include <memory.h>

#ifndef CAPMAX
#define CAPMAX(a, b)    ((a) > (b) ? (a) : (b))
#endif

#ifndef CAPMIN
#define CAPMIN(a, b)    ((a) < (b) ? (a) : (b))
#endif

#ifndef CAPALIGN
#define CAPALIGN(x, align) ((( x ) + (align) - 1) / (align) * (align))
#endif

#define CAP_CHECK_RET(condition__, retval__, ...) \
    if (!(condition__)) { \
        ALOGE(__VA_ARGS__); \
        return (retval__); \
    }

#ifndef NELEM
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

inline static void *mallocz(size_t size)
{
    void *mem = malloc(size);
    if (!mem)
        return mem;

    memset(mem, 0, size);
    return mem;
}

inline static void freep(void **mem)
{
    if (mem && *mem) {
        free(*mem);
        *mem = NULL;
    }
}

#endif
