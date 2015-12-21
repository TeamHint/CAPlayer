

#ifndef JJK__tv_danmaku_cap_media_player_CapMediaPlayer__H
#define JJK__tv_danmaku_cap_media_player_CapMediaPlayer__H

#include "capsdl/android/jjk/internal/jjk_internal.h"

jlong JJKC_CapMediaPlayer__mNativeMediaPlayer__get(JNIEnv *env, jobject thiz);
jlong JJKC_CapMediaPlayer__mNativeMediaPlayer__get__catchAll(JNIEnv *env, jobject thiz);
void JJKC_CapMediaPlayer__mNativeMediaPlayer__set(JNIEnv *env, jobject thiz, jlong value);
void JJKC_CapMediaPlayer__mNativeMediaPlayer__set__catchAll(JNIEnv *env, jobject thiz, jlong value);
jlong JJKC_CapMediaPlayer__mNativeMediaDataSource__get(JNIEnv *env, jobject thiz);
jlong JJKC_CapMediaPlayer__mNativeMediaDataSource__get__catchAll(JNIEnv *env, jobject thiz);
void JJKC_CapMediaPlayer__mNativeMediaDataSource__set(JNIEnv *env, jobject thiz, jlong value);
void JJKC_CapMediaPlayer__mNativeMediaDataSource__set__catchAll(JNIEnv *env, jobject thiz, jlong value);
void JJKC_CapMediaPlayer__postEventFromNative(JNIEnv *env, jobject weakThiz, jint what, jint arg1, jint arg2, jobject obj);
void JJKC_CapMediaPlayer__postEventFromNative__catchAll(JNIEnv *env, jobject weakThiz, jint what, jint arg1, jint arg2, jobject obj);
jstring JJKC_CapMediaPlayer__onSelectCodec(JNIEnv *env, jobject weakThiz, jstring mimeType, jint profile, jint level);
jstring JJKC_CapMediaPlayer__onSelectCodec__catchAll(JNIEnv *env, jobject weakThiz, jstring mimeType, jint profile, jint level);
jstring JJKC_CapMediaPlayer__onSelectCodec__asGlobalRef__catchAll(JNIEnv *env, jobject weakThiz, jstring mimeType, jint profile, jint level);
const char *JJKC_CapMediaPlayer__onSelectCodec__asCBuffer(JNIEnv *env, jobject weakThiz, jstring mimeType, jint profile, jint level, char *out_buf, int out_len);
const char *JJKC_CapMediaPlayer__onSelectCodec__asCBuffer__catchAll(JNIEnv *env, jobject weakThiz, jstring mimeType, jint profile, jint level, char *out_buf, int out_len);
jstring JJKC_CapMediaPlayer__onSelectCodec__withCString(JNIEnv *env, jobject weakThiz, const char *mimeType_cstr__, jint profile, jint level);
jstring JJKC_CapMediaPlayer__onSelectCodec__withCString__catchAll(JNIEnv *env, jobject weakThiz, const char *mimeType_cstr__, jint profile, jint level);
jstring JJKC_CapMediaPlayer__onSelectCodec__withCString__asGlobalRef__catchAll(JNIEnv *env, jobject weakThiz, const char *mimeType_cstr__, jint profile, jint level);
const char *JJKC_CapMediaPlayer__onSelectCodec__withCString__asCBuffer(JNIEnv *env, jobject weakThiz, const char *mimeType_cstr__, jint profile, jint level, char *out_buf, int out_len);
const char *JJKC_CapMediaPlayer__onSelectCodec__withCString__asCBuffer__catchAll(JNIEnv *env, jobject weakThiz, const char *mimeType_cstr__, jint profile, jint level, char *out_buf, int out_len);
jboolean JJKC_CapMediaPlayer__onNativeInvoke(JNIEnv *env, jobject weakThiz, jint what, jobject args);
jboolean JJKC_CapMediaPlayer__onNativeInvoke__catchAll(JNIEnv *env, jobject weakThiz, jint what, jobject args);
int JJK_loadClass__JJKC_CapMediaPlayer(JNIEnv *env);

#endif//JJK__tv_danmaku_cap_media_player_CapMediaPlayer__H
