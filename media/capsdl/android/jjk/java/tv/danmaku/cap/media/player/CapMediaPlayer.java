package tv.danmaku.cap.media.player;

import android.os.Bundle;

@SimpleCClassName
public class CapMediaPlayer {
    private long mNativeMediaPlayer;
    private long mNativeMediaDataSource;

    private static void postEventFromNative(Object weakThiz, int what, int arg1, int arg2, Object obj);
    private static String onSelectCodec(Object weakThiz, String mimeType, int profile, int level);
    private static boolean onNativeInvoke(Object weakThiz, int what, Bundle args);
}
