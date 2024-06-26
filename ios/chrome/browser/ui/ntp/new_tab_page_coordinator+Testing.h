// Copyright 2022 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_CHROME_BROWSER_UI_NTP_NEW_TAB_PAGE_COORDINATOR_TESTING_H_
#define IOS_CHROME_BROWSER_UI_NTP_NEW_TAB_PAGE_COORDINATOR_TESTING_H_

#import "ios/chrome/browser/ui/ntp/new_tab_page_coordinator.h"

#import "ios/chrome/browser/ui/ntp/feed_wrapper_view_controller.h"
#import "ios/chrome/browser/ui/ntp/new_tab_page_header_commands.h"
#import "ios/chrome/browser/ui/ntp/new_tab_page_metrics_delegate.h"

@class ContentSuggestionsCoordinator;
@class FeedHeaderViewController;
@class FeedTopSectionCoordinator;
@class NewTabPageHeaderViewController;
@class NewTabPageMetricsRecorder;
@class NewTabPageMediator;
@class NewTabPageViewController;

// Testing category that is intended to only be imported in
// new_tab_page_coordinator.mm and tests.
@interface NewTabPageCoordinator (Testing) <FeedWrapperViewControllerDelegate,
                                            NewTabPageHeaderCommands,
                                            NewTabPageMetricsDelegate>

@property(nonatomic, strong, readonly)
    NewTabPageHeaderViewController* headerViewController;

@property(nonatomic, strong)
    ContentSuggestionsCoordinator* contentSuggestionsCoordinator;

// Tracks the visibility of the NTP to report NTP usage metrics.
// True if the NTP view is currently displayed to the user.
@property(nonatomic, readonly) BOOL visible;

@property(nonatomic, strong) NewTabPageViewController* NTPViewController;

@property(nonatomic, strong) NewTabPageMetricsRecorder* NTPMetricsRecorder;

@property(nonatomic, strong) NewTabPageMediator* NTPMediator;

@property(nonatomic, strong)
    FeedWrapperViewController* feedWrapperViewController;

@property(nonatomic, strong)
    FeedTopSectionCoordinator* feedTopSectionCoordinator;

@property(nonatomic, strong) FeedHeaderViewController* feedHeaderViewController;

- (void)configureNTPViewController;

- (void)restoreNTPState;

@end

#endif  // IOS_CHROME_BROWSER_UI_NTP_NEW_TAB_PAGE_COORDINATOR_TESTING_H_
