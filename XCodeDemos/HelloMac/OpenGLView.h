//
//  OpenGLView.h
//  HelloMac
//
//  Created by iann on 2019/4/12.
//  Copyright © 2019 iann. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Render.h"

NS_ASSUME_NONNULL_BEGIN

@interface OpenGLView : NSView
{
    @public
    int index;

    //CGLContextObj context;
    //Render *render;
    
    

    float timer;
    GLuint shaderId;
    GLuint vertexArrayId;
    GLuint vertexBufferId;
    GLuint uvBufferId;
    GLuint mytexture;
    GLuint offset;
    
    
    CGLContextObj context;
    NSOpenGLContext *nsglContext;
    
    @public
    IOSurfaceRef surf;
    @public
    GLuint textureId;
}
- (instancetype)initWithFrame:(NSRect)frameRect withRender:(Render *) render withContext:(NSOpenGLContext *) nsglContext;

-(void)startRender;
-(void)shutDown;


@end

NS_ASSUME_NONNULL_END
