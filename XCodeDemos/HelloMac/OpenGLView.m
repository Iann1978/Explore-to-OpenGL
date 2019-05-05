//
//  OpenGLView.m
//  HelloMac
//
//  Created by iann on 2019/4/12.
//  Copyright © 2019 iann. All rights reserved.
//

#import "OpenGLView.h"
#import <OpenGL/gl.h>

@implementation OpenGLView

- (instancetype)initWithFrame:(NSRect)frameRect
{
    NSLog(@"OpenGLView.initWithFrame:\n");
    self = [super initWithFrame:frameRect];
    
    NSOpenGLPixelFormatAttribute glAttributes[] =
    {
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAAccelerated,
        0
    };
    
    NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc] initWithAttributes:glAttributes];
    NSOpenGLContext *glContext = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nil];
    [glContext setView:self];
    
    [glContext ]
    return self;
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    glClearColor(0.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glSwapAPPLE();
    // Drawing code here.
}

- (void)mouseDown:(NSEvent *) theEvent {
    NSLog(@"OpenGLView.mouseDown");
}

@end
