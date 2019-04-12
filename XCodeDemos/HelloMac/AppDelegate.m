//
//  AppDelegate.m
//  HelloMac
//
//  Created by iann on 2019/4/12.
//  Copyright © 2019 iann. All rights reserved.
//

#import "AppDelegate.h"
#import <Cocoa/Cocoa.h>

@implementation AppDelegate

- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *) theApplication
{
    return YES;
}

- (BOOL) windowShouldClose:(id)window
{
    return YES;
}

@end
