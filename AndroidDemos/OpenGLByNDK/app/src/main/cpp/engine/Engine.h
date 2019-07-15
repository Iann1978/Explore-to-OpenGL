//
// Created by Iann on 2019/5/28.
//



#ifndef OPENGLBYNDK_ENGINE_H
#define OPENGLBYNDK_ENGINE_H

#include <EGL/egl.h>
#include <GLES3/gl32.h>

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
void printGLString(const char *name, GLenum s);
void checkGlError(const char* op);
class Engine
{
    int texture;
public:
    Engine();

    void init(int w, int h, int texture);

    void RenderOneFrame();
};


#endif //OPENGLBYNDK_ENGINE_H
