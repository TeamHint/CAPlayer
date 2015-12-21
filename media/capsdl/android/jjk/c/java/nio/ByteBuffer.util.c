

#include "ByteBuffer.h"
#include "ByteBuffer.util.h"
#include <string.h>

#ifdef JJK_HAVE__JJKC_ByteBuffer
#define CALL_METHOD(method__) JJKC_ByteBuffer__##method__
#else
#define CALL_METHOD(method__) JJKC_java_nio_ByteBuffer__##method__
#endif

void *JJKC_java_nio_ByteBuffer__getDirectBufferAddress(JNIEnv *env, jobject thiz)
{
    return (*env)->GetDirectBufferAddress(env, thiz);
}

void *JJKC_java_nio_ByteBuffer__getDirectBufferAddress__catchAll(JNIEnv *env, jobject thiz)
{
    void *ret = (*env)->GetDirectBufferAddress(env, thiz);
    if (JJK_ExceptionCheck__catchAll(env) || !ret)
        return NULL;

    return ret;
}

int JJKC_java_nio_ByteBuffer__assignData__catchAll(JNIEnv *env, jobject thiz, void* data, size_t size)
{
    jobject buffer = CALL_METHOD(limit)(env, thiz, size);
    if (JJK_ExceptionCheck__catchAll(env) || !buffer)
        return -1;
    JJK_DeleteLocalRef__p(env, &buffer);

    uint8_t *c_buffer = JJKC_java_nio_ByteBuffer__getDirectBufferAddress__catchAll(env, thiz);
    if (!c_buffer)
        return -1;

    memcpy(c_buffer, data, size);
    return 0;
}
