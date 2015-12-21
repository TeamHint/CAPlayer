

#ifndef JJK__java_nio_ByteBuffer__H
#define JJK__java_nio_ByteBuffer__H

#include "capsdl/android/jjk/internal/jjk_internal.h"

jobject JJKC_ByteBuffer__allocate(JNIEnv *env, jint capacity);
jobject JJKC_ByteBuffer__allocate__catchAll(JNIEnv *env, jint capacity);
jobject JJKC_ByteBuffer__allocate__asGlobalRef__catchAll(JNIEnv *env, jint capacity);
jobject JJKC_ByteBuffer__allocateDirect(JNIEnv *env, jint capacity);
jobject JJKC_ByteBuffer__allocateDirect__catchAll(JNIEnv *env, jint capacity);
jobject JJKC_ByteBuffer__allocateDirect__asGlobalRef__catchAll(JNIEnv *env, jint capacity);
jobject JJKC_ByteBuffer__limit(JNIEnv *env, jobject thiz, jint newLimit);
jobject JJKC_ByteBuffer__limit__catchAll(JNIEnv *env, jobject thiz, jint newLimit);
jobject JJKC_ByteBuffer__limit__asGlobalRef__catchAll(JNIEnv *env, jobject thiz, jint newLimit);
int JJK_loadClass__JJKC_ByteBuffer(JNIEnv *env);

#define JJK_HAVE__JJKC_ByteBuffer

#include "ByteBuffer.util.h"

#endif//JJK__java_nio_ByteBuffer__H
