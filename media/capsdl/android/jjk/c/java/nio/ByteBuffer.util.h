

#ifndef JJK__java_nio_ByteBuffer__UTIL__H
#define JJK__java_nio_ByteBuffer__UTIL__H

#include "capsdl/android/jjk/internal/jjk_internal.h"
#include "ByteBuffer.h"

void *JJKC_java_nio_ByteBuffer__getDirectBufferAddress(JNIEnv *env, jobject thiz);
void *JJKC_java_nio_ByteBuffer__getDirectBufferAddress__catchAll(JNIEnv *env, jobject thiz);
int   JJKC_java_nio_ByteBuffer__assignData__catchAll(JNIEnv *env, jobject thiz, void* data, size_t size);

#ifdef JJK_HAVE__JJKC_ByteBuffer
inline static void *JJKC_ByteBuffer__getDirectBufferAddress(JNIEnv *env, jobject thiz) {return JJKC_java_nio_ByteBuffer__getDirectBufferAddress(env, thiz);}
inline static void *JJKC_ByteBuffer__getDirectBufferAddress__catchAll(JNIEnv *env, jobject thiz) {return JJKC_java_nio_ByteBuffer__getDirectBufferAddress__catchAll(env, thiz);}
inline static int   JJKC_ByteBuffer__assignData__catchAll(JNIEnv *env, jobject thiz, void* data, size_t size) {return JJKC_java_nio_ByteBuffer__assignData__catchAll(env, thiz, data, size);}
#endif

#endif
