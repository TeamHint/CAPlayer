

#include "jjk_internal.h"
#include "capsdl/android/jjk/c/java/nio/ByteBuffer.h"
#include "capsdl/android/jjk/c/java/util/ArrayList.h"
#include "capsdl/android/jjk/c/android/os/Build.h"
#include "capsdl/android/jjk/c/android/media/AudioTrack.h"
#include "capsdl/android/jjk/c/android/media/MediaCodec.h"
#include "capsdl/android/jjk/c/android/media/MediaFormat.h"
#include "capsdl/android/jjk/c/android/os/Bundle.h"
#include "capsdl/android/jjk/c/tv/danmaku/cap/media/player/CapMediaPlayer.h"
#include "capsdl/android/jjk/c/tv/danmaku/cap/media/player/misc/IMediaDataSource.h"

#define JJK_LOAD_CLASS(class__) \
    do { \
        ret = JJK_loadClass__JJKC_##class__(env); \
        if (ret) \
            goto fail; \
    } while (0)

int JJK_LoadAll__catchAll(JNIEnv *env)
{
    int ret = 0;

    JJK_LOAD_CLASS(ByteBuffer); // java_nio_ByteBuffer
    JJK_LOAD_CLASS(ArrayList);  // java_util_ArrayList

    // must load before all other android classes
    JJK_LOAD_CLASS(android_os_Build);

    JJK_LOAD_CLASS(AudioTrack);  // android_media_AudioTrack
    JJK_LOAD_CLASS(MediaCodec);  // android_media_MediaCodec
    JJK_LOAD_CLASS(MediaFormat); // android_media_MediaFormat
    JJK_LOAD_CLASS(Bundle);      // android_os_Bundle

    JJK_LOAD_CLASS(CapMediaPlayer);     // tv_danmaku_cap_media_player_CapMediaPlayer
    JJK_LOAD_CLASS(IMediaDataSource);   // tv_danmaku_cap_media_player_misc_IMediaDataSource

fail:
    return ret;
}
