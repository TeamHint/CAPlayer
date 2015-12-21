

#include "ArrayList.h"

typedef struct JJKC_ArrayList {
    jclass id;

    jmethodID constructor_ArrayList;
    jmethodID method_add;
} JJKC_ArrayList;
static JJKC_ArrayList class_JJKC_ArrayList;

jobject JJKC_ArrayList__ArrayList(JNIEnv *env)
{
    return (*env)->NewObject(env, class_JJKC_ArrayList.id, class_JJKC_ArrayList.constructor_ArrayList);
}

jobject JJKC_ArrayList__ArrayList__catchAll(JNIEnv *env)
{
    jobject ret_object = JJKC_ArrayList__ArrayList(env);
    if (JJK_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}

jobject JJKC_ArrayList__ArrayList__asGlobalRef__catchAll(JNIEnv *env)
{
    jobject ret_object   = NULL;
    jobject local_object = JJKC_ArrayList__ArrayList__catchAll(env);
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

jboolean JJKC_ArrayList__add(JNIEnv *env, jobject thiz, jobject object)
{
    return (*env)->CallBooleanMethod(env, thiz, class_JJKC_ArrayList.method_add, object);
}

jboolean JJKC_ArrayList__add__catchAll(JNIEnv *env, jobject thiz, jobject object)
{
    jboolean ret_value = JJKC_ArrayList__add(env, thiz, object);
    if (JJK_ExceptionCheck__catchAll(env)) {
        return false;
    }

    return ret_value;
}

int JJK_loadClass__JJKC_ArrayList(JNIEnv *env)
{
    int         ret                   = -1;
    const char *JJK_UNUSED(name)      = NULL;
    const char *JJK_UNUSED(sign)      = NULL;
    jclass      JJK_UNUSED(class_id)  = NULL;
    int         JJK_UNUSED(api_level) = 0;

    sign = "java/util/ArrayList";
    class_JJKC_ArrayList.id = JJK_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_JJKC_ArrayList.id == NULL)
        goto fail;

    class_id = class_JJKC_ArrayList.id;
    name     = "<init>";
    sign     = "()V";
    class_JJKC_ArrayList.constructor_ArrayList = JJK_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_JJKC_ArrayList.constructor_ArrayList == NULL)
        goto fail;

    class_id = class_JJKC_ArrayList.id;
    name     = "add";
    sign     = "(Ljava/lang/Object;)Z";
    class_JJKC_ArrayList.method_add = JJK_GetMethodID__catchAll(env, class_id, name, sign);
    if (class_JJKC_ArrayList.method_add == NULL)
        goto fail;

    ALOGD("JJKLoader: OK: '%s' loaded\n", "java.util.ArrayList");
    ret = 0;
fail:
    return ret;
}
