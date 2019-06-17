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
uniform sampler2DRect mytexture;
void main()
{
    color = texture(mytexture, uv*256).rgb;
}
)SHADER";

@implementation OpenGLView

- (instancetype)initWithFrame:(NSRect)frameRect;
{
    NSLog(@"OpenGLView.initWithFrame:\n");
    self = [super initWithFrame:frameRect];
    //self->render = render;
    //self->context = nsglContext.CGLContextObj;
    //[nsglContext setView:self];
    
    
    
    NSOpenGLContext *nsglContext0 = [self CreateContext:nil];
    [self LoadResource];
    self->surf = [self CreateSurf];
    self->texture = [self CreateTextureThroughSurf:self->surf];
    [nsglContext0 setView:self];
    return self;
}
-(void)startRender
{
    auto func = [self]()->void{
        CGLSetCurrentContext(self->cglContext);
        //Render *render = self->render;
        while(true)
        {
            [self RenderTriangle];
        }
        
    };
    thread *th = new thread(func);
}


- (void)shutDown {
    NSLog(@"shutDown:\n");

}

- (void)render {
    return;
}
- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    
}

- (void)mouseDown:(NSEvent *) theEvent {
    NSLog(@"OpenGLView.mouseDown");
    [self drawRect:NSMakeRect(0,0,100,100)];
}

- (IOSurfaceRef) CreateSurf
{
    int width = 256;
    int height = 256;
    
    NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:
                          [NSNumber numberWithInt:width], kIOSurfaceWidth,
                          [NSNumber numberWithInt:height], kIOSurfaceHeight,
                          [NSNumber numberWithInt:4], kIOSurfaceBytesPerElement,
                          nil];
    IOSurfaceRef surf = IOSurfaceCreate((CFDictionaryRef)dict);
    IOSurfaceLock(surf, 0, NULL);
    void *data = IOSurfaceGetBaseAddress(surf);
    size_t stride = IOSurfaceGetBytesPerRow(surf);
    CGColorSpaceRef rgb = CGColorSpaceCreateDeviceRGB();
    CGContextRef ctx = CGBitmapContextCreate(data, width, height, 8, stride,
                                             rgb, kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Host);
    CGColorSpaceRelease(rgb);
    CGContextSetRGBFillColor(ctx, 1,1,1,1);
    CGContextFillRect(ctx, CGRectMake(0,0,200,200));
    
    for (int i=0; i<30; i++) {
        CGFloat radius = 20.0f + 4.0f * i;
        CGFloat angle = i * 1.1;
        CGPoint circleCenter = { 150 + radius * cos(angle), 100 + radius * sin(angle) };
        CGFloat circleRadius = 10;
        CGContextSetRGBFillColor(ctx, 0, i % 2, 1 - (i % 2), 1);
        CGContextFillEllipseInRect(ctx, CGRectMake(circleCenter.x - circleRadius,  circleCenter.y - circleRadius,
                                                   circleRadius*2, circleRadius * 2));
    }
    IOSurfaceUnlock(surf, 0, NULL);
    return surf;
}

- (GLuint) CreateTextureThroughSurf: (IOSurfaceRef) surf
{
    GLuint texture = 0;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_RECTANGLE, texture);
    CGLTexImageIOSurface2D(cglContext, GL_TEXTURE_RECTANGLE, GL_RGBA, 256, 256,
                           GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, surf, 0);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}
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
    nsglContext = [[NSOpenGLContext alloc] initWithFormat:format shareContext:context];
    self->cglContext = nsglContext.CGLContextObj;
    
    
    
    //CreateTextureThroughIOSurface(NSMakeSize(256, 256), context1, nil);
    return nsglContext;
}
- (void) LoadResource
{
    CGLSetCurrentContext(cglContext);
    
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
    
    shader = CreateShader(vertexSource, fragmentSource);
    mytexture = glGetUniformLocation(shader, "mytexture");
    offset = glGetUniformLocation(shader, "offset");
    
    
    // Generate vertex array
    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);
    
    // Generate vertex buffer
    glGenBuffers(1, &vertexarray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexarray);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
    
    // Generate uv buffer
    glGenBuffers(1, &uvbuffer0);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);
    
    
    
    
}

- (void)RenderTriangle{
    NSLog(@"OpenGLView.render:\n");
    
    
    
    float offsetvalue = 0.2f*sin(timer+=0.02f);
    
    glClearColor(0.0f,1.0f*index,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shader);
    glUniform1f(offset, offsetvalue);
    
    glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE0, textureId);
    glBindTexture(GL_TEXTURE_RECTANGLE, texture);
    glUniform1i(mytexture, 0);
    
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexarray);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    
    glSwapAPPLE();
    
}

- (void) ReleaseResource {
    CGLSetCurrentContext(cglContext);
    glDeleteBuffers(1, &vertexbuffer0);
    glDeleteBuffers(1, &uvbuffer0);
    glDeleteVertexArrays(1, &vertexarray);
    glDeleteProgram(shader);
}
@end
