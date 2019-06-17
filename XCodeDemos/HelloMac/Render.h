//
//  Render.h
//  HelloMac
//
//  Created by iann on 2019/6/13.
//  Copyright © 2019 iann. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface Render : NSObject
{
    @public
    int index;
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
- (NSOpenGLContext *) CreateContext: (NSOpenGLContext *) context;
- (IOSurfaceRef) CreateSurf;
- (GLuint) CreateTextureThroughSurf: (IOSurfaceRef) surf;
- (void) LoadResource;
- (void) RenderTriangle;
- (void) ReleaseResource;


@end

NS_ASSUME_NONNULL_END
