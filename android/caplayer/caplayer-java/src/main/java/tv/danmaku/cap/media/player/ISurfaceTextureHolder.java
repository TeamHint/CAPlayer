

package tv.danmaku.cap.media.player;

import android.graphics.SurfaceTexture;

public interface ISurfaceTextureHolder {
    void setSurfaceTexture(SurfaceTexture surfaceTexture);

    SurfaceTexture getSurfaceTexture();

    void setSurfaceTextureHost(ISurfaceTextureHost surfaceTextureHost);
}
