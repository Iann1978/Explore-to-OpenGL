#include <jni.h>
#include <string>
#include <jni.h>
#include <android/log.h>

//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <GLES3/gl32.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "engine/Engine.h"

Engine* engine;



extern "C" JNIEXPORT jstring JNICALL
Java_com_example_openglbyndk_GL2JNILib_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C" JNIEXPORT void JNICALL Java_com_example_openglbyndk_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height, jint texture)
{
    engine = new Engine();
    engine->init(width, height, texture);
}

extern "C" JNIEXPORT void JNICALL Java_com_example_openglbyndk_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    engine->RenderOneFrame();
}
