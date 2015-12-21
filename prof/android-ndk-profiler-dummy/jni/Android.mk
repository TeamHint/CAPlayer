LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := android-ndk-profiler
LOCAL_SRC_FILES := prof.c

include $(BUILD_STATIC_LIBRARY)
