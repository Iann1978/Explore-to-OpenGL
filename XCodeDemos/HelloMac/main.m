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
#import "Render.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, Mac!");
        
        
        NSApplication *app = [NSApplication sharedApplication];
        NSRect rc = NSMakeRect(0, 0, 800, 600);
        NSInteger uiStyle = NSWindowStyleMaskTitled | NSWindowStyleMaskResizable | NSWindowStyleMaskClosable;
        NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
        // Set delegate to application
        AppDelegate *appDelegate = [[AppDelegate alloc] init];
        [app setDelegate:appDelegate];
        
        
        Render *render = [Render alloc];
        NSOpenGLContext *nsglContext = [render CreateContext1];
        NSOpenGLContext *nsglContext2 = [render CreateContext2];
        [render LoadResource];
        
        
        
        // Create the main window
        NSWindow *win0 = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
        [win0 setTitle:@"win0"];
        [win0 makeKeyAndOrderFront:win0];
        [win0 makeMainWindow];
        OpenGLView *view0 = [[OpenGLView alloc] initWithFrame:rc withRender:render withContext:nsglContext2];
        view0->index = 0;
        [win0 setContentView:view0];
        [win0 setDelegate:appDelegate];
        
        
        


        
        // Create other window
//        NSWindow *win1 = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
//        [win1 setTitle:@"win1"];
//        [win1 makeKeyAndOrderFront:win1];
//        [win1 makeMainWindow];
//        OpenGLView *view1 = [[OpenGLView alloc] initWithFrame:rc withRender:render withContext:nsglContext2];
//        view1->index = 1;
//        [win1 setContentView:view1];
//        [win1 setDelegate:appDelegate];
        
        
        
        [app run];
        
        NSLog(@"Hello, Mac Exit!!!");
    }
    NSLog(@"Hello, Mac Exit!!!");
    return 0;
}
