//
//  GrowlDisplayWindowController.h
//  Display Plugins
//
//  Created by Mac-arena the Bored Zo on 2005-06-03.
//  Copyright 2004-2005 The Growl Project. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define GrowlDisplayWindowControllerWillDisplayWindowNotification  @"GrowlDisplayWindowControllerWillDisplayWindowNotification"
#define GrowlDisplayWindowControllerDidDisplayWindowNotification   @"GrowlDisplayWindowControllerDidDisplayWindowNotification"
#define GrowlDisplayWindowControllerWillTakeDownWindowNotification @"GrowlDisplayWindowControllerWillTakeDownWindowNotification"
#define GrowlDisplayWindowControllerDidTakeDownWindowNotification  @"GrowlDisplayWindowControllerDidTakeDownWindowNotification"

@class GrowlWindowTransition;

@interface GrowlDisplayWindowController : NSWindowController
{
	SEL					action;
	id					target;
	id					clickContext;
	NSNumber			*clickHandlerEnabled;
	NSString			*appName;
	NSNumber			*appPid;
	id					delegate;
	CFRunLoopTimerRef	displayTimer;
	NSMutableArray		*windowTransitions;

	NSTimeInterval		displayDuration;
	unsigned			screenNumber;
	unsigned			WCReserved: 31;
	unsigned			screenshotMode: 1;
}

- (void) takeScreenshot;

- (void) startDisplay;
- (void) stopDisplay;
	
/*call these from subclasses as various phases of display occur.
 *for example, in GrowlDisplayFadingWindowController:
 *	* -startFadeIn  calls -willDisplayNotification
 *	* -stopFadeIn   calls  -didDisplayNotification
 *	* -startFadeOut calls -willTakeDownNotification
 *	* -stopFadeOut  calls  -didTakeDownNotification
 */
- (void) willDisplayNotification;
- (void)  didDisplayNotification;
- (void) willTakeDownNotification;
- (void)  didTakeDownNotification;

#pragma mark -

- (void) startDisplayTimer;
- (void) stopDisplayTimer;

#pragma mark -

- (void) addTransition:(GrowlWindowTransition *)transition;
- (void) removeTransition:(GrowlWindowTransition *)transition;

- (NSArray *) allTransitions;
- (NSArray *) activeTransitions;
- (NSArray *) inactiveTransitions;

- (void) startAllTransitions;
- (void) startAllTransitionsOfKind:(Class)transitionsClass;

- (void) stopAllTransitions;
- (void) stopAllTransitionsOfKind:(Class)transitionsClass;

#pragma mark -

- (NSTimeInterval) displayDuration;
- (void) setDisplayDuration:(NSTimeInterval) newDuration;

- (BOOL) screenshotModeEnabled;
- (void) setScreenshotModeEnabled:(BOOL) newScreenshotMode;

- (NSScreen *) screen;
- (void) setScreen:(NSScreen *) newScreen;

- (id) target;
- (void) setTarget:(id) object;

- (SEL) action;
- (void) setAction:(SEL) selector;

- (NSString *) notifyingApplicationName;
- (void) setNotifyingApplicationName:(NSString *) inAppName;

- (NSNumber *) notifyingApplicationProcessIdentifier;
- (void) setNotifyingApplicationProcessIdentifier:(NSNumber *) inAppPid;

- (id) clickContext;
- (void) setClickContext:(id) clickContext;

- (void) notificationClicked:(id) sender;

- (void) addNotificationObserver:(id) observer;
- (void) removeNotificationObserver:(id) observer;

- (id) delegate;
- (void) setDelegate:(id) newDelegate;

- (NSNumber *) clickHandlerEnabled;
- (void) setClickHandlerEnabled:(NSNumber *) flag;

@end
