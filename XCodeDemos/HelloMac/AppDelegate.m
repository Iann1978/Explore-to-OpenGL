//
//  AppDelegate.m
//  HelloMac
//
//  Created by iann on 2019/4/12.
//  Copyright © 2019 iann. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#import "AppDelegate.h"
#import <Cocoa/Cocoa.h>
#import "OpenGLView.h"

@implementation AppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    NSLog(@"applicationDidFinishLaunching");
    [view0 startRender];
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *) theApplication
{
    NSLog(@"AppDelegate.applicationShouldTerminateAfterLastWindowClosed\n");
    return YES;
}

- (BOOL) windowShouldClose:(id)window
{
    NSLog(@"windowShouldClose\n");
    OpenGLView *view = [window contentView];
    if (view)
    {
        [view shutDown];
    }
    return YES;
}

@end
