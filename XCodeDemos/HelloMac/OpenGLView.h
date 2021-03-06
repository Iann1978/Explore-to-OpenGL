//
//  OpenGLView.h
//  HelloMac
//
//  Created by iann on 2019/4/12.
//  Copyright © 2019 iann. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "RenderBuffer.h"
#import "RenderView.h"


NS_ASSUME_NONNULL_BEGIN

@interface OpenGLView : NSView
{
    @public
    int index;
    
    

    float timer;
    GLuint shader;
    GLuint vertexarray;
    GLuint vertexbuffer0;
    GLuint uvbuffer0;
    GLuint mytexture;
    GLuint offset;
    
    GLuint framebuffer;
    GLuint rendertexture;
    IOSurfaceRef rendersurf;
    
    
    CGLContextObj cglContext;
    NSOpenGLContext *nsglContext;
    
    @public
    IOSurfaceRef surf;
    @public
    GLuint texture;
    
    RenderBuffer *renderBuffer;
    RenderView *renderView;
}
- (instancetype)initWithFrame:(NSRect)frameRect;

-(void)startRender;
-(void)shutDown;


@end

NS_ASSUME_NONNULL_END
