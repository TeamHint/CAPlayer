#!/bin/sh

adb logcat | ndk-stack -sym caplayer/caplayer-armv7a/src/main/obj/local/armeabi-v7a
