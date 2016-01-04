#! /usr/bin/env bash
#
# Copyright (C) 2013-2015 Zhang Rui <bbcallen@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

CAP_FFMPEG_UPSTREAM=https://github.com/TeamHint/FFmpeg.git
CAP_FFMPEG_FORK=https://github.com/TeamHint/FFmpeg.git
CAP_FFMPEG_COMMIT=ff2.8--ijk0.4.1.1--dev0.3.3--rc4
CAP_FFMPEG_LOCAL_REPO=extra/ffmpeg

set -e
TOOLS=tools

echo "== pull ffmpeg base =="
sh $TOOLS/pull-repo-base.sh $CAP_FFMPEG_UPSTREAM $CAP_FFMPEG_LOCAL_REPO

function pull_fork()
{
    echo "== pull ffmpeg fork $1 =="
    sh $TOOLS/pull-repo-ref.sh $CAP_FFMPEG_FORK android/contrib/ffmpeg-$1 ${CAP_FFMPEG_LOCAL_REPO}
    cd android/contrib/ffmpeg-$1
    git checkout ${CAP_FFMPEG_COMMIT} -B caplayer
    cd -
}

pull_fork "armv7a"
pull_fork "armv5"
pull_fork "x86"
pull_fork "arm64"

./init-config.sh
./init-android-libyuv.sh
