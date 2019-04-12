//
//  main.m
//  HelloMac
//
//  Created by iann on 2019/4/12.
//  Copyright © 2019 iann. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"
#import "OpenGLView.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, Mac!");
        
        // Create the main window
        NSApplication *app = [NSApplication sharedApplication];
        NSRect rc = NSMakeRect(0, 0, 800, 600);
        NSInteger uiStyle = NSWindowStyleMaskTitled | NSWindowStyleMaskResizable | NSWindowStyleMaskClosable;
        NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
        NSWindow *win = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
        [win setTitle:@"Hello Mac"];
        [win makeKeyAndOrderFront:win];
        [win makeMainWindow];
        
        // Set an OpenGL view to a window.
        OpenGLView *view = [[OpenGLView alloc] initWithFrame:rc];
        [win setContentView:view];
        
        
        


        // Set delegate to application
        AppDelegate *appDelegate = [[AppDelegate alloc] init];
        [app setDelegate:appDelegate];
        
        
        
        [app run];
        
        NSLog(@"Hello, Mac Exit!!!");
    }
    NSLog(@"Hello, Mac Exit!!!");
    return 0;
}
