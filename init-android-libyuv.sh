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


CAP_LIBYUV_UPSTREAM=https://github.com/TeamHint/libyuv.git
CAP_LIBYUV_FORK=https://github.com/TeamHint/libyuv.git
CAP_LIBYUV_LOCAL_REPO=extra/libyuv

set -e
TOOLS=tools

echo "== pull libyuv base =="
sh $TOOLS/pull-repo-base.sh $CAP_LIBYUV_UPSTREAM $CAP_LIBYUV_LOCAL_REPO

echo "== pull libyuv fork =="
sh $TOOLS/pull-repo-ref.sh $CAP_LIBYUV_FORK media/yuv ${CAP_LIBYUV_LOCAL_REPO}
cd media/yuv
cd -
