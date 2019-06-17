//
//  OpenGLView.m
//  HelloMac
//
//  Created by iann on 2019/4/12.
//  Copyright © 2019 iann. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#import "OpenGLView.h"
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>
#import "texture.hpp"
#import <thread>
#include <functional>
#include "shader.hpp"

using std::thread;
using std::function;



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


@implementation OpenGLView

- (instancetype)initWithFrame:(NSRect)frameRect withRender:(Render *) render withContext:(NSOpenGLContext *) nsglContext;
{
    NSLog(@"OpenGLView.initWithFrame:\n");
    self = [super initWithFrame:frameRect];
    self->render = render;
    self->context = nsglContext.CGLContextObj;
    
    //render = [Render alloc];
    //NSOpenGLContext *nsglContext = [render CreateContext1];
    //context = nsglContext.CGLContextObj;
    //[render LoadResource];
    [nsglContext setView:self];
    

//    NSOpenGLPixelFormatAttribute glAttributes[] =
//    {
//        NSOpenGLPFAColorSize, 24,
//        NSOpenGLPFAColorFloat,
//        NSOpenGLPFAAlphaSize, 8,
//        NSOpenGLPFADoubleBuffer,
//        //NSOpenGLPFAAccelerated,
//        NSOpenGLPFAMultisample,
//        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
//        0
//    };
//
//    NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc] initWithAttributes:glAttributes];
//    NSOpenGLContext *glContext = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nil];
//    [glContext setView:self];
//
//    CGLSetCurrentContext(glContext.CGLContextObj);
//
//
//    shaderId = CreateShader(vertexSource, fragmentSource);
//    mytexture = glGetUniformLocation(shaderId, "mytexture");
//    offset = glGetUniformLocation(shaderId, "offset");
//
//
//    // Generate vertex array
//    glGenVertexArrays(1, &vertexArrayId);
//    glBindVertexArray(vertexArrayId);
//
//    // Generate vertex buffer
//    glGenBuffers(1, &vertexArrayId);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayId);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
//
//    // Generate uv buffer
//    glGenBuffers(1, &uvBufferId);
//    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);
//
//
//    textureId =  loadDDS("/Users/iann/Documents/uvtemplate.DDS");
//    context = glContext.CGLContextObj;
//    timer = 0;
//
    

    return self;
}
-(void)startRender
{
    auto func = [self]()->void{
        CGLSetCurrentContext(self->context);
        Render *render = self->render;
        while(true)
        {
            [render RenderTriangle];
        }
        
    };
    thread *th = new thread(func);
}
-(void)renderThreadFunc {
    //CGLSetCurrentContext(context);
    while(true)
    {
        //[self. render];
    }
}

- (void)shutDown {
    NSLog(@"shutDown:\n");
//    CGLSetCurrentContext(context);
//    glDeleteBuffers(1, &vertexBufferId);
//    glDeleteBuffers(1, &uvBufferId);
//    glDeleteVertexArrays(1, &vertexArrayId);
//    glDeleteProgram(shaderId);
}

- (void)render {
    return;
    //NSLog(@"OpenGLView.render:\n");
    
    //static float timer = 0;
//    float offsetvalue = 0.2f*sin(timer+=0.02f);
//    
//    glClearColor(0.0f,1.0f*index,1.0f,1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    
//    glUseProgram(shaderId);
//    glUniform1f(offset, offsetvalue);
//    
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE0, textureId);
//    glUniform1i(mytexture, 0);
//    
//    
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayId);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    
//    glEnableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
//    
//    
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    
//    glSwapAPPLE();
//    
}
- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    //glClearColor(0.0f,1.0f*index,1.0f,1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);
    
    
    //glFlush();
    //glSwapAPPLE();
    
    // Drawing code here.
}

- (void)mouseDown:(NSEvent *) theEvent {
    NSLog(@"OpenGLView.mouseDown");
    [self drawRect:NSMakeRect(0,0,100,100)];
}

@end
