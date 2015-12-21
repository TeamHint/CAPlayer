

#ifndef JJK__android_media_AudioTrack__H
#define JJK__android_media_AudioTrack__H

#include "capsdl/android/jjk/internal/jjk_internal.h"

jobject JJKC_AudioTrack__AudioTrack(JNIEnv *env, jint streamType, jint sampleRateInHz, jint channelConfig, jint audioFormat, jint bufferSizeInBytes, jint mode);
jobject JJKC_AudioTrack__AudioTrack__catchAll(JNIEnv *env, jint streamType, jint sampleRateInHz, jint channelConfig, jint audioFormat, jint bufferSizeInBytes, jint mode);
jobject JJKC_AudioTrack__AudioTrack__asGlobalRef__catchAll(JNIEnv *env, jint streamType, jint sampleRateInHz, jint channelConfig, jint audioFormat, jint bufferSizeInBytes, jint mode);
jint JJKC_AudioTrack__getMinBufferSize(JNIEnv *env, jint sampleRateInHz, jint channelConfig, jint audioFormat);
jint JJKC_AudioTrack__getMinBufferSize__catchAll(JNIEnv *env, jint sampleRateInHz, jint channelConfig, jint audioFormat);
jfloat JJKC_AudioTrack__getMaxVolume(JNIEnv *env);
jfloat JJKC_AudioTrack__getMaxVolume__catchAll(JNIEnv *env);
jfloat JJKC_AudioTrack__getMinVolume(JNIEnv *env);
jfloat JJKC_AudioTrack__getMinVolume__catchAll(JNIEnv *env);
jint JJKC_AudioTrack__getNativeOutputSampleRate(JNIEnv *env, jint streamType);
jint JJKC_AudioTrack__getNativeOutputSampleRate__catchAll(JNIEnv *env, jint streamType);
void JJKC_AudioTrack__play(JNIEnv *env, jobject thiz);
void JJKC_AudioTrack__play__catchAll(JNIEnv *env, jobject thiz);
void JJKC_AudioTrack__pause(JNIEnv *env, jobject thiz);
void JJKC_AudioTrack__pause__catchAll(JNIEnv *env, jobject thiz);
void JJKC_AudioTrack__stop(JNIEnv *env, jobject thiz);
void JJKC_AudioTrack__stop__catchAll(JNIEnv *env, jobject thiz);
void JJKC_AudioTrack__flush(JNIEnv *env, jobject thiz);
void JJKC_AudioTrack__flush__catchAll(JNIEnv *env, jobject thiz);
void JJKC_AudioTrack__release(JNIEnv *env, jobject thiz);
void JJKC_AudioTrack__release__catchAll(JNIEnv *env, jobject thiz);
jint JJKC_AudioTrack__write(JNIEnv *env, jobject thiz, jbyteArray audioData, jint offsetInBytes, jint sizeInBytes);
jint JJKC_AudioTrack__write__catchAll(JNIEnv *env, jobject thiz, jbyteArray audioData, jint offsetInBytes, jint sizeInBytes);
jint JJKC_AudioTrack__setStereoVolume(JNIEnv *env, jobject thiz, jfloat leftGain, jfloat rightGain);
jint JJKC_AudioTrack__setStereoVolume__catchAll(JNIEnv *env, jobject thiz, jfloat leftGain, jfloat rightGain);
jint JJKC_AudioTrack__getAudioSessionId(JNIEnv *env, jobject thiz);
jint JJKC_AudioTrack__getAudioSessionId__catchAll(JNIEnv *env, jobject thiz);
int JJK_loadClass__JJKC_AudioTrack(JNIEnv *env);

#endif//JJK__android_media_AudioTrack__H
