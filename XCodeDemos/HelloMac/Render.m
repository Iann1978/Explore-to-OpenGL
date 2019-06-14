//
//  Render.m
//  HelloMac
//
//  Created by iann on 2019/6/13.
//  Copyright © 2019 iann. All rights reserved.
//
#import <Cocoa/Cocoa.h>
#import "Render.h"
#define GL_SILENCE_DEPRECATION
#import <OpenGL/gl.h>
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>
#import "shader.hpp"
#import "texture.hpp"

#include <CoreGraphics/CoreGraphics.h>

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

static GLuint CreateTextureThroughIOSurface(NSSize size, CGLContextObj context, void (^drawCallback)(CGContextRef ctx))
{
    int width = size.width;
    int height = size.height;
    
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
    
    GLuint texture = 0;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_RECTANGLE_EXT, texture);
    CGLTexImageIOSurface2D(context, GL_TEXTURE_RECTANGLE_EXT, GL_RGB, width, height,
                            GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, surf, 0);
    glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}

@implementation Render
- (NSOpenGLContext *) CreateContext1
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
    nsglContext1 = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nil];
    context1 = nsglContext1.CGLContextObj;
    
    surf = [self CreagteSurface];
    
    //CreateTextureThroughIOSurface(NSMakeSize(256, 256), context1, nil);
    return nsglContext1;
}
- (IOSurfaceRef) CreagteSurface
{
    int width = 256;
    int height = 256;
    NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:
                          [NSNumber numberWithInt:width], kIOSurfaceWidth,
                          [NSNumber numberWithInt:height], kIOSurfaceHeight,
                          [NSNumber numberWithInt:4], kIOSurfaceBytesPerElement,
                          nil];
    IOSurfaceRef surf = IOSurfaceCreate((CFDictionaryRef)dict);
    return surf;
}

                                         
- (NSOpenGLContext *) CreateContext2
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
    NSOpenGLContext *glContext = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nsglContext1];
    context2 = glContext.CGLContextObj;
     return glContext;
}

- (void) LoadResource
{
    CGLSetCurrentContext(context2);
    
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
    
    shaderId = CreateShader(vertexSource, fragmentSource);
    mytexture = glGetUniformLocation(shaderId, "mytexture");
    offset = glGetUniformLocation(shaderId, "offset");
    
    
    // Generate vertex array
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    
    // Generate vertex buffer
    glGenBuffers(1, &vertexArrayId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
    
    // Generate uv buffer
    glGenBuffers(1, &uvBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);
    
    
    textureId =  loadDDS("/Users/iann/Documents/uvtemplate.DDS");
    //textureId = CreateTextureThroughIOSurface(NSMakeSize(256, 256), context1, nil);
    int a = 0;
    int b = 0;
    
}

- (void)RenderTriangle{
    //NSLog(@"OpenGLView.render:\n");
    
 
 
    float offsetvalue = 0.2f*sin(timer+=0.02f);
    
    glClearColor(0.0f,1.0f*index,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderId);
    glUniform1f(offset, offsetvalue);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE0, textureId);
    //glBindTexture(GL_TEXTURE_RECTANGLE_EXT, textureId);
    glUniform1i(mytexture, 0);
    
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glSwapAPPLE();
    
}

- (void) ReleaseResource {
    CGLSetCurrentContext(context1);
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &uvBufferId);
    glDeleteVertexArrays(1, &vertexArrayId);
    glDeleteProgram(shaderId);
}
@end
