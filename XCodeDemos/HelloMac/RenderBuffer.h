//
//  RenderBuffer.h
//  HelloMac
//
//  Created by Iann on 2019/6/18.
//  Copyright © 2019 iann. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface RenderBuffer : NSObject
{
@public
    int index;
    float timer;
    
    
    
    // mesh
    GLuint vertexarray;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    
    // materail
    GLuint texture;
    GLuint shader;
    GLuint mytexture;
    GLuint offset;
    
    // fbo
    GLuint framebuffer;
    GLuint rendertexture;
    IOSurfaceRef rendersurf;
    
    
    @public
    NSOpenGLContext *nsglContext;
    
    
}
- (NSOpenGLContext *) CreateContext: (NSOpenGLContext *) context;
- (void) LoadResource;
- (void) RenderTriangle;
- (void) SetTarget: (IOSurfaceRef) surf;
@end

NS_ASSUME_NONNULL_END
