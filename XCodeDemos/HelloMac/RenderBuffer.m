//
//  RenderBuffer.m
//  HelloMac
//
//  Created by Iann on 2019/6/18.
//  Copyright © 2019 iann. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#import "RenderBuffer.h"
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>
#import "shader.hpp"
#import "texture.hpp"

static const char *vertexSource =
R"SHADER(
#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 texcoord;
uniform float offset;
out vec2 uv;
void main(){
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.x += offset;
    gl_Position.w = 1.0;
    uv = texcoord;
}
)SHADER";



static const char *fragmentSource =
R"SHADER(
#version 330 core
in vec2 uv;
out vec3 color;
uniform sampler2D mytexture;
void main()
{
    color = texture(mytexture, uv).rgb;
}
)SHADER";

@implementation RenderBuffer


- (NSOpenGLContext *) CreateContext: (NSOpenGLContext *) context
{
    NSOpenGLPixelFormatAttribute glAttributes[] =
    {
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAColorFloat,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADoubleBuffer,
        //NSOpenGLPFAAccelerated,
        NSOpenGLPFAMultisample,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        0
    };
    
    NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc] initWithAttributes:glAttributes];
    return [[NSOpenGLContext alloc] initWithFormat:format shareContext:context];
}

- (GLuint) CreateTextureThroughSurf: (IOSurfaceRef) surf
{
    GLuint texture = 0;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_RECTANGLE, texture);
    CGLTexImageIOSurface2D(nsglContext.CGLContextObj, GL_TEXTURE_RECTANGLE, GL_RGBA, 256, 256,
                           GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, surf, 0);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}


- (void) SetTarget: (IOSurfaceRef) surf
{
    CGLSetCurrentContext(nsglContext.CGLContextObj);
    rendersurf = surf;
    rendertexture = [self CreateTextureThroughSurf:rendersurf];
    
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, rendertexture, 0);
    GLenum drawbuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawbuffers);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        NSLog(@"glCheckFramebufferStatus:\n");
    }
}
- (void) LoadResource
{
    
    CGLSetCurrentContext(nsglContext.CGLContextObj);
    
    // mesh
    static const GLfloat vertexBufferData[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    static const GLfloat uvBufferData[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f,  1.0f,
    };
    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);
    
    // material

    
    
    texture = loadDDS("/Users/iann/Documents/uvtemplate.dds");
    shader = CreateShader(vertexSource, fragmentSource);
    mytexture = glGetUniformLocation(shader, "mytexture");
    offset = glGetUniformLocation(shader, "offset");
}

- (void) RenderTriangle
{
    NSLog(@"RenderBuffer.RenderTiangle:\n");
    
    float offsetvalue = 0.2f*sin(timer+=0.02f);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, 256, 256);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shader);
    
    glUniform1f(offset, offsetvalue);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(mytexture, 0);
    
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glSwapAPPLE();
}

- (void) ReleaseResource {
//    CGLSetCurrentContext(cglContext);
//    glDeleteBuffers(1, &vertexbuffer0);
//    glDeleteBuffers(1, &uvbuffer0);
//    glDeleteVertexArrays(1, &vertexarray);
//    glDeleteProgram(shader);
}

@end
