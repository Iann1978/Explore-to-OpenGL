//
//  shader.cpp
//  HelloMac
//
//  Created by Iann on 2019/6/12.
//  Copyright © 2019 iann. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>
#include "shader.hpp"

GLuint CreateShader(const char *vertShaderSource, const char *fragShaderSource)
{
    GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Compile Vertex Shader
    glShaderSource(vertShaderId, 1, &vertShaderSource, 0);
    glCompileShader(vertShaderId);
    GLint status = GL_TRUE;
    GLint infoLen = 0;
    glGetShaderiv(vertShaderId, GL_COMPILE_STATUS, &status);
    glGetShaderiv(vertShaderId, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen)
    {
        GLchar *buff = new GLchar[infoLen+1];
        buff[infoLen] = 0;
        glGetShaderInfoLog(vertShaderId, infoLen, 0, buff);
        printf("%s", buff);
        delete[] buff;
    }
    
    // Compile Fragment Shader
    glShaderSource(fragShaderId, 1, &fragShaderSource, 0);
    glCompileShader(fragShaderId);
    status = GL_TRUE;
    infoLen = 0;
    glGetShaderiv(fragShaderId, GL_COMPILE_STATUS, &status);
    glGetShaderiv(fragShaderId, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen)
    {
        GLchar *buff = new GLchar[infoLen+1];
        buff[infoLen] = 0;
        glGetShaderInfoLog(fragShaderId, infoLen, 0, buff);
        printf("%s", buff);
        delete[] buff;
    }
    
    // Link the program
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertShaderId);
    glAttachShader(programId, fragShaderId);
    glLinkProgram(programId);
    status = GL_TRUE;
    infoLen = 0;
    glGetProgramiv(programId, GL_COMPILE_STATUS, &status);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen)
    {
        GLchar  *buff = new GLchar[infoLen + 1];
        buff[infoLen] = 0;
        glGetProgramInfoLog(programId, infoLen, 0, buff);
        printf(buff);
        delete buff;
    }
    
    glDetachShader(programId, vertShaderId);
    glDetachShader(programId, fragShaderId);
    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);
    return programId;
}
