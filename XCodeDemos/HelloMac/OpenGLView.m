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


@implementation OpenGLView

- (instancetype)initWithFrame:(NSRect)frameRect withRender:(Render *) render withContext:(NSOpenGLContext *) nsglContext;
{
    NSLog(@"OpenGLView.initWithFrame:\n");
    self = [super initWithFrame:frameRect];
    self->render = render;
    self->context = nsglContext.CGLContextObj;
    [nsglContext setView:self];
    
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

@end
