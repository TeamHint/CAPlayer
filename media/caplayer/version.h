

#ifndef FFPLAY__VERSION_H
#define FFPLAY__VERSION_H

#include "libavutil/version.h"

/*
 * The major version number is incremented with backward incompatible changes
 *   - e.g. removing parts of the public API, reordering public struct members, etc. 
 * The minor version number is incremented for backward compatible API changes
 * or major new features
 *   - e.g. adding a new public function or a new decoder.
 * The micro version number is incremented for smaller changes that a calling program
 * might still want to check for
 *   - e.g. changing behavior in a previously unspecified situation.
 */

#define LIBCAPLAYER_VERSION_MAJOR  2
#define LIBCAPLAYER_VERSION_MINOR  0
#define LIBCAPLAYER_VERSION_MICRO  0

#define LIBCAPLAYER_VERSION_INT    AV_VERSION_INT(LIBCAPLAYER_VERSION_MAJOR, \
                                                   LIBCAPLAYER_VERSION_MINOR, \
                                                   LIBCAPLAYER_VERSION_MICRO)
#define LIBCAPLAYER_VERSION        AV_VERSION(LIBCAPLAYER_VERSION_MAJOR,     \
                                               LIBCAPLAYER_VERSION_MINOR,     \
                                               LIBCAPLAYER_VERSION_MICRO)
#define LIBCAPLAYER_BUILD          LIBCAPLAYER_VERSION_INT

#define LIBCAPLAYER_IDENT          "caplayer " AV_STRINGIFY(LIBCAPLAYER_VERSION)

#define CAPVERSION_GET_MAJOR(x)     ((x >> 16) & 0xFF)
#define CAPVERSION_GET_MINOR(x)     ((x >>  8) & 0xFF)
#define CAPVERSION_GET_MICRO(x)     ((x      ) & 0xFF)

#endif//FFPLAY__VERSION_H
