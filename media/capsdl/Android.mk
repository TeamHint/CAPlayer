LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -std=c99
LOCAL_LDLIBS += -llog -landroid -lOpenSLES

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH)/..)
LOCAL_C_INCLUDES += $(MY_APP_FFMPEG_INCLUDE_PATH)
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH)/../capyuv/include)

LOCAL_SRC_FILES += capsdl_aout.c
LOCAL_SRC_FILES += capsdl_audio.c
LOCAL_SRC_FILES += capsdl_error.c
LOCAL_SRC_FILES += capsdl_mutex.c
LOCAL_SRC_FILES += capsdl_stdinc.c
LOCAL_SRC_FILES += capsdl_thread.c
LOCAL_SRC_FILES += capsdl_timer.c
LOCAL_SRC_FILES += capsdl_vout.c

LOCAL_SRC_FILES += dummy/capsdl_vout_dummy.c

LOCAL_SRC_FILES += ffmpeg/capsdl_vout_overlay_ffmpeg.c
LOCAL_SRC_FILES += ffmpeg/abi_all/image_convert.c

LOCAL_SRC_FILES += android/android_audiotrack.c
LOCAL_SRC_FILES += android/android_nativewindow.c
LOCAL_SRC_FILES += android/capsdl_android_jni.c
LOCAL_SRC_FILES += android/capsdl_aout_android_audiotrack.c
LOCAL_SRC_FILES += android/capsdl_aout_android_opensles.c
LOCAL_SRC_FILES += android/capsdl_codec_android_mediacodec_java.c
LOCAL_SRC_FILES += android/capsdl_codec_android_mediacodec.c
LOCAL_SRC_FILES += android/capsdl_codec_android_mediadef.c
LOCAL_SRC_FILES += android/capsdl_codec_android_mediaformat_java.c
LOCAL_SRC_FILES += android/capsdl_codec_android_mediaformat.c
LOCAL_SRC_FILES += android/capsdl_vout_android_nativewindow.c
LOCAL_SRC_FILES += android/capsdl_vout_android_surface.c
LOCAL_SRC_FILES += android/capsdl_vout_overlay_android_mediacodec.c

# TODO: move to individual lib
LOCAL_SRC_FILES += android/jjk/internal/jjk_allclasses.c
LOCAL_SRC_FILES += android/jjk/internal/jjk_internal.c
LOCAL_SRC_FILES += android/jjk/c/android/media/AudioTrack.c
LOCAL_SRC_FILES += android/jjk/c/android/media/MediaCodec.c
LOCAL_SRC_FILES += android/jjk/c/android/media/MediaFormat.c
LOCAL_SRC_FILES += android/jjk/c/android/os/Build.c
LOCAL_SRC_FILES += android/jjk/c/android/os/Bundle.c
LOCAL_SRC_FILES += android/jjk/c/java/nio/Buffer.c
LOCAL_SRC_FILES += android/jjk/c/java/nio/ByteBuffer.c
LOCAL_SRC_FILES += android/jjk/c/java/nio/ByteBuffer.util.c
LOCAL_SRC_FILES += android/jjk/c/java/util/ArrayList.c
LOCAL_SRC_FILES += android/jjk/c/tv/danmaku/cap/media/player/CapMediaPlayer.c
LOCAL_SRC_FILES += android/jjk/c/tv/danmaku/cap/media/player/misc/IMediaDataSource.c

LOCAL_SHARED_LIBRARIES := capffmpeg
LOCAL_STATIC_LIBRARIES := cpufeatures yuv_static

LOCAL_MODULE := capsdl
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/cpufeatures)
