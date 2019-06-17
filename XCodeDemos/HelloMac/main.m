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
        
        
        Render *render0 = [Render alloc];
        NSOpenGLContext *nsglContext0 = [render0 CreateContext:nil];
        [render0 LoadResource];
        render0->surf = [render0 CreateSurf];
        render0->textureId = [render0 CreateTextureThroughSurf:render0->surf];
        
        
        
        // Create the main window
        NSWindow *win0 = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
        [win0 setTitle:@"win0"];
        [win0 makeKeyAndOrderFront:win0];
        [win0 makeMainWindow];
        OpenGLView *view0 = [[OpenGLView alloc] initWithFrame:rc withRender:render0 withContext:nsglContext0];
        view0->index = 0;
        [win0 setContentView:view0];
        [win0 setDelegate:appDelegate];
        appDelegate->view0 = view0;
        //[view0 startRender];
        
        

//        Render *render1 = [Render alloc];
//        NSOpenGLContext *nsglContext1 = [render1 CreateContext:render0->nsglContext];
//        [render1 LoadResource];
//        render1->surf = render0->surf;
//        render1->textureId = [render1 CreateTextureThroughSurf:render1->surf];
//        
//        // Create other window
//        NSWindow *win1 = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
//        [win1 setTitle:@"win1"];
//        [win1 makeKeyAndOrderFront:win1];
//        [win1 makeMainWindow];
//        OpenGLView *view1 = [[OpenGLView alloc] initWithFrame:rc withRender:render1 withContext:nsglContext1];
//        view1->index = 1;
//        [win1 setContentView:view1];
//        [win1 setDelegate:appDelegate];
//        appDelegate->view1 = view1;
        
        
        
        [app run];
        
        NSLog(@"Hello, Mac Exit!!!");
    }
    NSLog(@"Hello, Mac Exit!!!");
    return 0;
}
