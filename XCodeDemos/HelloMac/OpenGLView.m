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

static GLuint CreateShader(const char *vertShaderSource, const char *fragShaderSource)
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
        printf(buff);
        delete buff;
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
        printf(buff);
        delete buff;
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


@implementation OpenGLView

- (instancetype)initWithFrame:(NSRect)frameRect
{
    NSLog(@"OpenGLView.initWithFrame:\n");
    self = [super initWithFrame:frameRect];
    
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
    NSOpenGLContext *glContext = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nil];
    [glContext setView:self];
    
    CGLSetCurrentContext(glContext.CGLContextObj);
    
    
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
    

    textureId =  loadDDS("/Users/iann/Pictures/uvtemplate.DDS");

    return self;
}

- (void)shutDown {
    NSLog(@"shutDown:\n");
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &uvBufferId);
    glDeleteVertexArrays(1, &vertexArrayId);
    glDeleteProgram(shaderId);
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    NSLog(@"OpenGLView.drawRect:\n");

    static float timer = 0;
    float offsetvalue = 0.2f*sin(timer+=0.02f);
    
    glClearColor(0.0f,1.0f*index,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderId);
    glUniform1f(offset, offsetvalue);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE0, textureId);
    glUniform1i(mytexture, 0);
     
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glSwapAPPLE();
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
