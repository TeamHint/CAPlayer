/*
 * Copyright (C) 2015 Zhang Rui <bbcallen@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
