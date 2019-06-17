//
//  AppDelegate.h
//  HelloMac
//
//  Created by iann on 2019/4/12.
//  Copyright © 2019 iann. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OpenGLView.h"

NS_ASSUME_NONNULL_BEGIN

@interface AppDelegate : NSObject
{
@public
    OpenGLView *view0;
    OpenGLView *view1;
}

- (BOOL) windowShouldClose:(id)window;

@end

NS_ASSUME_NONNULL_END
