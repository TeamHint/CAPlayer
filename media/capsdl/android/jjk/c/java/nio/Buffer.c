

#include "Buffer.h"

typedef struct JJKC_java_nio_Buffer {
    jclass id;
} JJKC_java_nio_Buffer;
static JJKC_java_nio_Buffer class_JJKC_java_nio_Buffer;

int JJK_loadClass__JJKC_java_nio_Buffer(JNIEnv *env)
{
    int         ret                   = -1;
    const char *JJK_UNUSED(name)      = NULL;
    const char *JJK_UNUSED(sign)      = NULL;
    jclass      JJK_UNUSED(class_id)  = NULL;
    int         JJK_UNUSED(api_level) = 0;

    sign = "java/nio/Buffer";
    class_JJKC_java_nio_Buffer.id = JJK_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_JJKC_java_nio_Buffer.id == NULL)
        goto fail;

    ALOGD("JJKLoader: OK: '%s' loaded\n", "java.nio.Buffer");
    ret = 0;
fail:
    return ret;
}
