// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import "ios/web/net/cookies/crw_wk_http_cookie_store.h"

#import "base/check_op.h"
#import "ios/web/public/thread/web_thread.h"

namespace {
// Prioritizes queued WKHTTPCookieStore completion handlers to run as soon as
// possible. This function is needed because some of WKHTTPCookieStore methods
// completion handlers are not called until there is a WKWebView on the view
// hierarchy.
void PrioritizeWKHTTPCookieStoreCallbacks() {
  // TODO(crbug.com/41414488): Currently this hack is needed to fix
  // crbug.com/885218. Remove when the behavior of
  // [WKHTTPCookieStore getAllCookies:] changes.
  NSSet* data_types = [NSSet setWithObject:WKWebsiteDataTypeCookies];
  [[WKWebsiteDataStore defaultDataStore]
      fetchDataRecordsOfTypes:data_types
            completionHandler:^(NSArray<WKWebsiteDataRecord*>* records){
            }];
}
}  // namespace

@interface CRWWKHTTPCookieStore () <WKHTTPCookieStoreObserver>

// The last getAllCookies output. Will always be set from the UI
// thread.
@property(nonatomic) NSArray<NSHTTPCookie*>* cachedCookies;

@end

@implementation CRWWKHTTPCookieStore

- (void)getAllCookies:(void (^)(NSArray<NSHTTPCookie*>*))completionHandler {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  NSArray<NSHTTPCookie*>* result = _HTTPCookieStore ? _cachedCookies : @[];
  if (result) {
    dispatch_async(dispatch_get_main_queue(), ^{
      completionHandler(result);
    });
  } else {
    __weak __typeof(self) weakSelf = self;
    [_HTTPCookieStore getAllCookies:^(NSArray<NSHTTPCookie*>* cookies) {
      weakSelf.cachedCookies = cookies;
      completionHandler(cookies);
    }];
    PrioritizeWKHTTPCookieStoreCallbacks();
  }
}

- (void)setCookie:(NSHTTPCookie*)cookie
    completionHandler:(nullable void (^)(void))completionHandler {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  _cachedCookies = nil;
  [_HTTPCookieStore setCookie:cookie completionHandler:completionHandler];
}

- (void)deleteCookie:(NSHTTPCookie*)cookie
    completionHandler:(nullable void (^)(void))completionHandler {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  _cachedCookies = nil;
  [_HTTPCookieStore deleteCookie:cookie completionHandler:completionHandler];
}

- (void)clearCookies:(void (^)(void))completionHandler {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  __weak CRWWKHTTPCookieStore* weakSelf = self;
  [self getAllCookies:^(NSArray<NSHTTPCookie*>* cookies) {
    [weakSelf deleteCookies:cookies completionHandler:completionHandler];
  }];
}

- (void)setHTTPCookieStore:(WKHTTPCookieStore*)newCookieStore {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  _cachedCookies = nil;
  if (newCookieStore == _HTTPCookieStore)
    return;
  [_HTTPCookieStore removeObserver:self];
  _HTTPCookieStore = newCookieStore;
  [_HTTPCookieStore addObserver:self];
}

#pragma mark WKHTTPCookieStoreObserver method

- (void)cookiesDidChangeInCookieStore:(WKHTTPCookieStore*)cookieStore {
  _cachedCookies = nil;
}

#pragma mark - Private methods

- (void)deleteCookies:(NSArray<NSHTTPCookie*>*)cookies
    completionHandler:(void (^)(void))completionHandler {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  _cachedCookies = nil;

  // If there are no cookies to clear, then invoke the completion handler and
  // return, otherwise ask `_HTTPCookieStore` to delete all cookies, invoking
  // the completion handler after the last delete operation completes.
  __block NSUInteger counter = cookies.count;
  if (counter == 0) {
    completionHandler();
    return;
  }

  for (NSHTTPCookie* cookie in cookies) {
    [_HTTPCookieStore deleteCookie:cookie
                 completionHandler:^{
                   if (--counter == 0) {
                     completionHandler();
                   }
                 }];
  }
}

@end
