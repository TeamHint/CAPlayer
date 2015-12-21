package tv.danmaku.cap.media.player;

import android.annotation.TargetApi;
import android.content.Context;
import android.net.Uri;
import android.os.Build;
import android.view.Surface;

import java.io.FileDescriptor;
import java.io.IOException;
import java.util.Map;

@Deprecated
public abstract class BaseMediaPlayer implements IMediaPlayer {
    private boolean mIsLogEnabled;

    public boolean isLogEnabled() {
        return mIsLogEnabled;
    }

    @Override
    public void setLogEnabled(boolean enable) {
        mIsLogEnabled = enable;
    }

    @Override
    public boolean isPlayable() {
        return true;
    }

    @Override
    public void setAudioStreamType(int streamtype) {
    }

    @Override
    public void setKeepInBackground(boolean keepInBackground) {
    }

    @Override
    public int getVideoSarNum() {
        return 1;
    }

    @Override
    public int getVideoSarDen() {
        return 1;
    }

    @Deprecated
    @Override
    public void setWakeMode(Context context, int mode) {
        return;
    }

    @Override
    public int getAudioSessionId() {
        return 0;
    }

    @TargetApi(Build.VERSION_CODES.ICE_CREAM_SANDWICH)
    @Override
    public void setSurface(Surface surface) {
    }

    @Override
    public void setDataSource(Context context, Uri uri)
            throws IOException, IllegalArgumentException, SecurityException, IllegalStateException {
        setDataSource(uri.getPath());
    }

    @TargetApi(Build.VERSION_CODES.ICE_CREAM_SANDWICH)
    @Override
    public void setDataSource(Context context, Uri uri, Map<String, String> headers)
            throws IOException, IllegalArgumentException, SecurityException, IllegalStateException {
        setDataSource(uri.getPath());
    }

    @Override
    public void setDataSource(FileDescriptor fd)
            throws IOException, IllegalArgumentException, IllegalStateException {
        throw new RuntimeException("does not support setDataSource(FileDescriptor fd)");
    }
}
