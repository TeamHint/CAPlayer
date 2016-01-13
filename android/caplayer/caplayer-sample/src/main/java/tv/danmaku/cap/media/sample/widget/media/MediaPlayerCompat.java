

package tv.danmaku.cap.media.sample.widget.media;

import tv.danmaku.cap.media.player.IMediaPlayer;
import tv.danmaku.cap.media.player.CapMediaPlayer;
import tv.danmaku.cap.media.player.MediaPlayerProxy;
import tv.danmaku.cap.media.player.TextureMediaPlayer;

public class MediaPlayerCompat {
    public static String getName(IMediaPlayer mp) {
        if (mp == null) {
            return "null";
        } else if (mp instanceof TextureMediaPlayer) {
            StringBuilder sb = new StringBuilder("TextureMediaPlayer <");
            IMediaPlayer internalMediaPlayer = ((TextureMediaPlayer) mp).getInternalMediaPlayer();
            if (internalMediaPlayer == null) {
                sb.append("null>");
            } else {
                sb.append(internalMediaPlayer.getClass().getSimpleName());
                sb.append(">");
            }
            return sb.toString();
        } else {
            return mp.getClass().getSimpleName();
        }
    }

    public static CapMediaPlayer getCapMediaPlayer(IMediaPlayer mp) {
        CapMediaPlayer capMediaPlayer = null;
        if (mp == null) {
            return null;
        } if (mp instanceof CapMediaPlayer) {
            capMediaPlayer = (CapMediaPlayer) mp;
        } else if (mp instanceof MediaPlayerProxy && ((MediaPlayerProxy) mp).getInternalMediaPlayer() instanceof CapMediaPlayer) {
            capMediaPlayer = (CapMediaPlayer) ((MediaPlayerProxy) mp).getInternalMediaPlayer();
        }
        return capMediaPlayer;
    }

    public static void selectTrack(IMediaPlayer mp, int stream) {
        CapMediaPlayer capMediaPlayer = getCapMediaPlayer(mp);
        if (capMediaPlayer == null)
            return;
        capMediaPlayer.selectTrack(stream);
    }

    public static void deselectTrack(IMediaPlayer mp, int stream) {
        CapMediaPlayer capMediaPlayer = getCapMediaPlayer(mp);
        if (capMediaPlayer == null)
            return;
        capMediaPlayer.deselectTrack(stream);
    }

    public static int getSelectedTrack(IMediaPlayer mp, int trackType) {
        CapMediaPlayer capMediaPlayer = getCapMediaPlayer(mp);
        if (capMediaPlayer == null)
            return -1;
        return capMediaPlayer.getSelectedTrack(trackType);
    }
}
