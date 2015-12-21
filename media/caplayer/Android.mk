LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
# -mfloat-abi=soft is a workaround for FP register corruption on Exynos 4210
# http://www.spinics.net/lists/arm-kernel/msg368417.html
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
LOCAL_CFLAGS += -mfloat-abi=soft
endif
LOCAL_CFLAGS += -std=c99
LOCAL_LDLIBS += -llog -landroid

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH)/..)
LOCAL_C_INCLUDES += $(MY_APP_FFMPEG_INCLUDE_PATH)

LOCAL_SRC_FILES += ff_cmdutils.c
LOCAL_SRC_FILES += ff_ffplay.c
LOCAL_SRC_FILES += ff_ffpipeline.c
LOCAL_SRC_FILES += ff_ffpipenode.c
LOCAL_SRC_FILES += capmeta.c
LOCAL_SRC_FILES += caplayer.c

LOCAL_SRC_FILES += pipeline/ffpipeline_ffplay.c
LOCAL_SRC_FILES += pipeline/ffpipenode_ffplay_vdec.c

LOCAL_SRC_FILES += android/ffmpeg_api_jni.c
LOCAL_SRC_FILES += android/caplayer_android.c
LOCAL_SRC_FILES += android/caplayer_jni.c

LOCAL_SRC_FILES += android/pipeline/ffpipeline_android.c
LOCAL_SRC_FILES += android/pipeline/ffpipenode_android_mediacodec_vdec.c

LOCAL_SRC_FILES += capavformat/allformats.c
LOCAL_SRC_FILES += capavformat/async.c
LOCAL_SRC_FILES += capavformat/capinject.c
LOCAL_SRC_FILES += capavformat/caplivehook.c
LOCAL_SRC_FILES += capavformat/caplongurl.c
LOCAL_SRC_FILES += capavformat/capmediadatasource.c
LOCAL_SRC_FILES += capavformat/capsegment.c
LOCAL_SRC_FILES += capavformat/capurlhook.c
LOCAL_SRC_FILES += capavformat/utils.c

LOCAL_SHARED_LIBRARIES := capffmpeg capsdl
LOCAL_STATIC_LIBRARIES := android-ndk-profiler

LOCAL_MODULE := caplayer
include $(BUILD_SHARED_LIBRARY)
