

#ifndef JJK__tv_danmaku_cap_media_player_misc_IMediaDataSource__H
#define JJK__tv_danmaku_cap_media_player_misc_IMediaDataSource__H

#include "capsdl/android/jjk/internal/jjk_internal.h"

jint JJKC_IMediaDataSource__readAt(JNIEnv *env, jobject thiz, jlong position, jbyteArray buffer, jint offset, jint size);
jint JJKC_IMediaDataSource__readAt__catchAll(JNIEnv *env, jobject thiz, jlong position, jbyteArray buffer, jint offset, jint size);
jlong JJKC_IMediaDataSource__getSize(JNIEnv *env, jobject thiz);
jlong JJKC_IMediaDataSource__getSize__catchAll(JNIEnv *env, jobject thiz);
void JJKC_IMediaDataSource__close(JNIEnv *env, jobject thiz);
void JJKC_IMediaDataSource__close__catchAll(JNIEnv *env, jobject thiz);
int JJK_loadClass__JJKC_IMediaDataSource(JNIEnv *env);

#endif//JJK__tv_danmaku_cap_media_player_misc_IMediaDataSource__H
