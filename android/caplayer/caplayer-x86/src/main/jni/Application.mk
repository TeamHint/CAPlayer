# copyright (c) 2016 Team Hint
#
# This file is a part of CAPlayer.

APP_OPTIM := release
APP_PLATFORM := android-9
APP_ABI := x86
NDK_TOOLCHAIN_VERSION=4.8
APP_PIE := false

APP_CFLAGS := -O3 -Wall -pipe \
    -ffast-math \
    -fstrict-aliasing -Werror=strict-aliasing \
    -Wno-psabi -Wa,--noexecstack \
    -DANDROID -DNDEBUG
