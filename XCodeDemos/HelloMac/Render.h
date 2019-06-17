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
    GLuint textureId;
    GLuint mytexture;
    GLuint offset;
    CGLContextObj context1;
    CGLContextObj context2;
    NSOpenGLContext *nsglContext1;
    
    IOSurfaceRef surf;
    
}

- (NSOpenGLContext *) CreateContext1;
- (NSOpenGLContext *) CreateContext2;
- (void) LoadResource;
- (void) RenderTriangle;
- (void) ReleaseResource;


@end

NS_ASSUME_NONNULL_END
