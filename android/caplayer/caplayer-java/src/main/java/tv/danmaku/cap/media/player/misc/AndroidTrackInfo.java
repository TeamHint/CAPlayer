

package tv.danmaku.cap.media.player.misc;

import android.annotation.TargetApi;
import android.media.MediaFormat;
import android.media.MediaPlayer;
import android.os.Build;

public class AndroidTrackInfo implements ITrackInfo {
    private MediaPlayer.TrackInfo mTrackInfo;

    public static AndroidTrackInfo[] fromMediaPlayer(MediaPlayer mp) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN)
            return fromTrackInfo(mp.getTrackInfo());

        return null;
    }

    public static AndroidTrackInfo[] fromTrackInfo(MediaPlayer.TrackInfo[] trackInfos) {
        if (trackInfos == null)
            return null;

        AndroidTrackInfo androidTrackInfo[] = new AndroidTrackInfo[trackInfos.length];
        for (int i = 0; i < trackInfos.length; ++i) {
            androidTrackInfo[i] = new AndroidTrackInfo(trackInfos[i]);
        }

        return androidTrackInfo;
    }

    public AndroidTrackInfo(MediaPlayer.TrackInfo trackInfo) {
        mTrackInfo = trackInfo;
    }

    @TargetApi(Build.VERSION_CODES.KITKAT)
    @Override
    public IMediaFormat getFormat() {
        if (mTrackInfo == null)
            return null;

        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.KITKAT)
            return null;

        MediaFormat mediaFormat = mTrackInfo.getFormat();
        if (mediaFormat == null)
            return null;

        return new AndroidMediaFormat(mediaFormat);
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    @Override
    public int getTrackType() {
        if (mTrackInfo == null)
            return MEDIA_TRACK_TYPE_UNKNOWN;

        return mTrackInfo.getTrackType();
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    @Override
    public String toString() {
        StringBuilder out = new StringBuilder(128);
        out.append(getClass().getSimpleName());
        out.append('{');
        if (mTrackInfo != null) {
            out.append(mTrackInfo.toString());
        } else {
            out.append("null");
        }
        out.append('}');
        return out.toString();
    }

    @Override
    public String getInfoInline() {
        return mTrackInfo.toString();
    }
}
