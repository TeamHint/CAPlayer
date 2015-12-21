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

package tv.danmaku.cap.media.player.misc;

import android.annotation.TargetApi;
import android.os.Build;
import android.text.TextUtils;

import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

import tv.danmaku.cap.media.player.CapMediaMeta;

public class CapMediaFormat implements IMediaFormat {
    // Common
    public static final String KEY_CAP_CODEC_LONG_NAME_UI = "cap-codec-long-name-ui";
    public static final String KEY_CAP_BIT_RATE_UI = "cap-bit-rate-ui";

    // Video
    public static final String KEY_CAP_CODEC_PROFILE_LEVEL_UI = "cap-profile-level-ui";
    public static final String KEY_CAP_CODEC_PIXEL_FORMAT_UI = "cap-pixel-format-ui";
    public static final String KEY_CAP_RESOLUTION_UI = "cap-resolution-ui";
    public static final String KEY_CAP_FRAME_RATE_UI = "cap-frame-rate-ui";

    // Audio
    public static final String KEY_CAP_SAMPLE_RATE_UI = "cap-sample-rate-ui";
    public static final String KEY_CAP_CHANNEL_UI = "cap-channel-ui";

    // Codec
    public static final String CODEC_NAME_H264 = "h264";

    public CapMediaMeta.CapStreamMeta mMediaFormat;

    public CapMediaFormat(CapMediaMeta.CapStreamMeta streamMeta) {
        mMediaFormat = streamMeta;
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    @Override
    public int getInteger(String name) {
        if (mMediaFormat == null)
            return 0;

        return mMediaFormat.getInt(name);
    }

    @Override
    public String getString(String name) {
        if (mMediaFormat == null)
            return null;

        if (sFormatterMap.containsKey(name)) {
            Formatter formatter = sFormatterMap.get(name);
            return formatter.format(this);
        }

        return mMediaFormat.getString(name);
    }

    //-------------------------
    // Formatter
    //-------------------------

    private static abstract class Formatter {
        public String format(CapMediaFormat mediaFormat) {
            String value = doFormat(mediaFormat);
            if (TextUtils.isEmpty(value))
                return getDefaultString();
            return value;
        }

        protected abstract String doFormat(CapMediaFormat mediaFormat);

        protected String getDefaultString() {
            return "N/A";
        }
    }

    private static Map<String, Formatter> sFormatterMap = new HashMap<String, Formatter>();

    {
        sFormatterMap.put(KEY_CAP_CODEC_LONG_NAME_UI, new Formatter() {
            @Override
            public String doFormat(CapMediaFormat mediaFormat) {
                return mMediaFormat.getString(CapMediaMeta.CAPM_KEY_CODEC_LONG_NAME);
            }
        });
        sFormatterMap.put(KEY_CAP_BIT_RATE_UI, new Formatter() {
            @Override
            protected String doFormat(CapMediaFormat mediaFormat) {
                int bitRate = mediaFormat.getInteger(CapMediaMeta.CAPM_KEY_BITRATE);
                if (bitRate <= 0) {
                    return null;
                } else if (bitRate < 1000) {
                    return String.format(Locale.US, "%d bit/s", bitRate);
                } else {
                    return String.format(Locale.US, "%d kb/s", bitRate / 1000);
                }
            }
        });
        sFormatterMap.put(KEY_CAP_CODEC_PROFILE_LEVEL_UI, new Formatter() {
            @Override
            protected String doFormat(CapMediaFormat mediaFormat) {
                String profile = mediaFormat.getString(CapMediaMeta.CAPM_KEY_CODEC_PROFILE);
                if (TextUtils.isEmpty(profile))
                    return null;

                StringBuilder sb = new StringBuilder();
                sb.append(profile);

                String codecName = mediaFormat.getString(CapMediaMeta.CAPM_KEY_CODEC_NAME);
                if (TextUtils.isEmpty(codecName)) {
                } else if (codecName.equalsIgnoreCase(CODEC_NAME_H264)) {
                    int level = mediaFormat.getInteger(CapMediaMeta.CAPM_KEY_CODEC_LEVEL);
                    if (level < 10)
                        return sb.toString();

                    sb.append(" Profile Level ");
                    sb.append((level / 10) % 10);
                    if ((level % 10) != 0) {
                        sb.append(".");
                        sb.append(level % 10);
                    }
                }

                return sb.toString();
            }
        });
        sFormatterMap.put(KEY_CAP_CODEC_PIXEL_FORMAT_UI, new Formatter() {
            @Override
            protected String doFormat(CapMediaFormat mediaFormat) {
                return mediaFormat.getString(CapMediaMeta.CAPM_KEY_CODEC_PIXEL_FORMAT);
            }
        });
        sFormatterMap.put(KEY_CAP_RESOLUTION_UI, new Formatter() {
            @Override
            protected String doFormat(CapMediaFormat mediaFormat) {
                int width = mediaFormat.getInteger(KEY_WIDTH);
                int height = mediaFormat.getInteger(KEY_HEIGHT);
                int sarNum = mediaFormat.getInteger(CapMediaMeta.CAPM_KEY_SAR_NUM);
                int sarDen = mediaFormat.getInteger(CapMediaMeta.CAPM_KEY_SAR_DEN);

                if (width <= 0 || height <= 0) {
                    return null;
                } else if (sarNum <= 0 || sarDen <= 0) {
                    return String.format(Locale.US, "%d x %d", width, height);
                } else {
                    return String.format(Locale.US, "%d x %d [SAR %d:%d]", width,
                            height, sarNum, sarDen);
                }
            }
        });
        sFormatterMap.put(KEY_CAP_FRAME_RATE_UI, new Formatter() {
            @Override
            protected String doFormat(CapMediaFormat mediaFormat) {
                int fpsNum = mediaFormat.getInteger(CapMediaMeta.CAPM_KEY_FPS_NUM);
                int fpsDen = mediaFormat.getInteger(CapMediaMeta.CAPM_KEY_FPS_DEN);
                if (fpsNum <= 0 || fpsDen <= 0) {
                    return null;
                } else {
                    return String.valueOf(((float) (fpsNum)) / fpsDen);
                }
            }
        });
        sFormatterMap.put(KEY_CAP_SAMPLE_RATE_UI, new Formatter() {
            @Override
            protected String doFormat(CapMediaFormat mediaFormat) {
                int sampleRate = mediaFormat.getInteger(CapMediaMeta.CAPM_KEY_SAMPLE_RATE);
                if (sampleRate <= 0) {
                    return null;
                } else {
                    return String.format(Locale.US, "%d Hz", sampleRate);
                }
            }
        });
        sFormatterMap.put(KEY_CAP_CHANNEL_UI, new Formatter() {
            @Override
            protected String doFormat(CapMediaFormat mediaFormat) {
                int channelLayout = mediaFormat.getInteger(CapMediaMeta.CAPM_KEY_CHANNEL_LAYOUT);
                if (channelLayout <= 0) {
                    return null;
                } else {
                    if (channelLayout == CapMediaMeta.AV_CH_LAYOUT_MONO) {
                        return "mono";
                    } else if (channelLayout == CapMediaMeta.AV_CH_LAYOUT_STEREO) {
                        return "stereo";
                    } else {
                        return String.format(Locale.US, "%x", channelLayout);
                    }
                }
            }
        });
    }
}
