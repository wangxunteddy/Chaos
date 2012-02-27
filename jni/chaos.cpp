#include <string.h>
#include <jni.h>

#include "chaos/ChsEngine.h"

Chaos::ChsEngine * engine;


JNIEXPORT void JNICALL Java_net_sniperbat_chaos_GL2JNILib_update(JNIEnv * env, jobject obj)
{
    engine->run();
}
