

package tv.danmaku.cap.media.player.misc;

import android.annotation.TargetApi;
import android.media.MediaFormat;
import android.os.Build;

public class AndroidMediaFormat implements IMediaFormat {
    private MediaFormat mMediaFormat;

    public AndroidMediaFormat(MediaFormat mediaFormat) {
        mMediaFormat = mediaFormat;
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    @Override
    public int getInteger(String name) {
        if (mMediaFormat == null)
            return 0;

        return mMediaFormat.getInteger(name);
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    @Override
    public String getString(String name) {
        if (mMediaFormat == null)
            return null;

        return mMediaFormat.getString(name);
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    @Override
    public String toString() {
        StringBuilder out = new StringBuilder(128);
        out.append(getClass().getName());
        out.append('{');
        if (mMediaFormat != null) {
            out.append(mMediaFormat.toString());
        } else {
            out.append("null");
        }
        out.append('}');
        return out.toString();
    }
}
