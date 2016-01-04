

#include "ByteBuffer.h"

typedef struct JJKC_ByteBuffer {
    jclass id;

    jmethodID method_allocate;
    jmethodID method_allocateDirect;
    jmethodID method_limit;
} JJKC_ByteBuffer;
static JJKC_ByteBuffer class_JJKC_ByteBuffer;

jobject JJKC_ByteBuffer__allocate(JNIEnv *env, jint capacity)
{
    return (*env)->CallStaticObjectMethod(env, class_JJKC_ByteBuffer.id, class_JJKC_ByteBuffer.method_allocate, capacity);
}

jobject JJKC_ByteBuffer__allocate__catchAll(JNIEnv *env, jint capacity)
{
    jobject ret_object = JJKC_ByteBuffer__allocate(env, capacity);
    if (JJK_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}

jobject JJKC_ByteBuffer__allocate__asGlobalRef__catchAll(JNIEnv *env, jint capacity)
{
    jobject ret_object   = NULL;
    jobject local_object = JJKC_ByteBuffer__allocate__catchAll(env, capacity);
    if (JJK_ExceptionCheck__catchAll(env) || !local_object) {
        ret_object = NULL;
        goto fail;
    }

    ret_object = JJK_NewGlobalRef__catchAll(env, local_object);
    if (!ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    JJK_DeleteLocalRef__p(env, &local_object);
    return ret_object;
}

jobject JJKC_ByteBuffer__allocateDirect(JNIEnv *env, jint capacity)
{
    return (*env)->CallStaticObjectMethod(env, class_JJKC_ByteBuffer.id, class_JJKC_ByteBuffer.method_allocateDirect, capacity);
}

jobject JJKC_ByteBuffer__allocateDirect__catchAll(JNIEnv *env, jint capacity)
{
    jobject ret_object = JJKC_ByteBuffer__allocateDirect(env, capacity);
    if (JJK_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}

jobject JJKC_ByteBuffer__allocateDirect__asGlobalRef__catchAll(JNIEnv *env, jint capacity)
{
    jobject ret_object   = NULL;
    jobject local_object = JJKC_ByteBuffer__allocateDirect__catchAll(env, capacity);
    if (JJK_ExceptionCheck__catchAll(env) || !local_object) {
        ret_object = NULL;
        goto fail;
    }

    ret_object = JJK_NewGlobalRef__catchAll(env, local_object);
    if (!ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    JJK_DeleteLocalRef__p(env, &local_object);
    return ret_object;
}

jobject JJKC_ByteBuffer__limit(JNIEnv *env, jobject thiz, jint newLimit)
{
    return (*env)->CallObjectMethod(env, thiz, class_JJKC_ByteBuffer.method_limit, newLimit);
}

jobject JJKC_ByteBuffer__limit__catchAll(JNIEnv *env, jobject thiz, jint newLimit)
{
    jobject ret_object = JJKC_ByteBuffer__limit(env, thiz, newLimit);
    if (JJK_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}

jobject JJKC_ByteBuffer__limit__asGlobalRef__catchAll(JNIEnv *env, jobject thiz, jint newLimit)
{
    jobject ret_object   = NULL;
    jobject local_object = JJKC_ByteBuffer__limit__catchAll(env, thiz, newLimit);
    if (JJK_ExceptionCheck__catchAll(env) || !local_object) {
        ret_object = NULL;
        goto fail;
    }

    ret_object = JJK_NewGlobalRef__catchAll(env, local_object);
    if (!ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    JJK_DeleteLocalRef__p(env, &local_object);
    return ret_object;
}

int JJK_loadClass__JJKC_ByteBuffer(JNIEnv *env)
{
    int         ret                   = -1;
    const char *JJK_UNUSED(name)      = NULL;
    const char *JJK_UNUSED(sign)      = NULL;
    jclass      JJK_UNUSED(class_id)  = NULL;
    int         JJK_UNUSED(api_level) = 0;

    sign = "java/nio/ByteBuffer";
    class_JJKC_ByteBuffer.id = JJK_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_JJKC_ByteBuffer.id == NULL)
        goto fail;

    class_id = class_JJKC_ByteBuffer.id;
    name     = "allocate";
    sign     = "(I)Ljava/nio/ByteBuffer;";
    class_JJKC_ByteBuffer.method_allocate = JJK_GetStaticMethodID__catchAll(env, class_id, name, sign);
    if (class_JJKC_ByteBuffer.method_allocate == NULL)
        goto fail;

    class_id = class_JJKC_ByteBuffer.id;
    name     = "allocateDirect";
    sign     = "(I)Ljava/nio/ByteBuffer;";
    class_JJKC_ByteBuffer.method_allocateDirect = JJK_GetStaticMethodID__catchAll(env, class_id, name, sign);
    if (class_JJKC_ByteBuffer.method_allocateDirect == NULL)
        goto fail;

    class_id = class_JJKC_ByteBuffer.id;
    name     = "limit";
    sign     = "(I)Ljava/nio/Buffer;";
    class_JJKC_ByteBuffer.method_limit = JJK_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_JJKC_ByteBuffer.method_limit == NULL)
        goto fail;

    ALOGD("JJKLoader: OK: '%s' loaded\n", "java.nio.ByteBuffer");
    ret = 0;
fail:
    return ret;
}
