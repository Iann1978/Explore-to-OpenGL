//
//  OpenGLView.h
//  HelloMac
//
//  Created by iann on 2019/4/12.
//  Copyright © 2019 iann. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

@interface OpenGLView : NSView
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
    CGLContextObj context;
    
}
-(void)shutDown;
-(void)render;
-(void)renderThreadFunc;
@end

NS_ASSUME_NONNULL_END
