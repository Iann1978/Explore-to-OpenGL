//
// Created by Iann on 2019/5/29.
//

#ifndef OPENGLBYNDK_SHADER_H
#define OPENGLBYNDK_SHADER_H

#include <EGL/egl.h>
#include <GLES3/gl32.h>

class Shader {
public:
    static GLuint loadShader(GLenum shaderType, const char* pSource);
    static GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

};


#endif //OPENGLBYNDK_SHADER_H
