//
// Created by Iann on 2019/5/29.
//

#ifndef OPENGLBYNDK_IMAGE_H
#define OPENGLBYNDK_IMAGE_H
#include <EGL/egl.h>
#include <GLES3/gl32.h>

#include "Renderable.h"


class Image// : public IRenderable
{
public:
    typedef void (*FuncOnClick)();
    GLuint programID_image;
    GLuint vertexbuffer_image;
    GLuint uvbuffer_image;
    GLuint texture = 0;
    GLuint textureID;
    GLuint rectID;
    GLuint screenWidthID;
    GLuint screenHeightID;
    GLuint statusID;

    GLfloat x, y, w, h;

public:
    GLfloat status;
    FuncOnClick onClick = nullptr;


public:
    Image(const char* path, float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f);
    ~Image();

    void Update();
    void Render();
    void SetTexture(const char* path);


private:
    bool RayCast(float x, float y);
};


#endif //OPENGLBYNDK_IMAGE_H
