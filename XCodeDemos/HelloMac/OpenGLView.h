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
    
    GLuint shaderId;
    GLuint vertexArrayId;
    GLuint vertexBufferId;
    GLuint uvBufferId;
    GLuint textureId;
    GLuint mytexture;
    GLuint offset;
    
}
-(void)shutDown;
-(void)render;
@end

NS_ASSUME_NONNULL_END
