/**
 * Copyright IBM Corporation 2016
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "BaseConfiguration.h"

@interface SpeechUtility : NSObject

/**
 *  find unexpected error by code
 *
 *  @param code HTTP / WebSocket status code
 *
 *  @return error message
 */
+ (NSString*)findUnexpectedErrorWithCode: (NSInteger)code;

/**
 *  raise error with code
 *
 *  @param code error code
 *
 *  @return NSError
 */
+ (NSError*)raiseErrorWithCode:(NSInteger)code;

/**
 *  raise error with message only
 *
 *  @param code         error code
 *  @param errorMessage error message
 *
 *  @return NSError
 */
+ (NSError*)raiseErrorWithCode: (NSInteger)code message: (NSString*) errorMessage;

/**
 *  raise error with code and messages
 *
 *  @param code              error code
 *  @param errorMessage      error message
 *  @param reasonMessage     reason message
 *  @param suggestionMessage suggestion message
 *
 *  @return NSError
 */
+ (NSError*)raiseErrorWithCode: (NSInteger)code message: (NSString*) errorMessage reason: (NSString*) reasonMessage suggestion:(NSString*) suggestionMessage;

/**
 *  process dictionary (JSON)
 *
 *  @param handler      JSON handler
 *  @param authConfig   configuration
 *  @param httpResponse HTTP response
 *  @param responseData response data
 *  @param requestError request error
 */
+ (void)processJSON: (JSONHandlerWithError)handler
                  config: (BaseConfiguration*) authConfig
                response:(NSURLResponse*) httpResponse
                    data:(NSData*) responseData
                   error: (NSError*) requestError;

/**
 *  process binary
 *
 *  @param handler      data handler
 *  @param authConfig   configuration
 *  @param httpResponse HTTP response
 *  @param responseData response data
 *  @param requestError request error
 */
+ (void)processData: (DataHandlerWithError)handler
              config: (BaseConfiguration*) authConfig
            response:(NSURLResponse*) httpResponse
                data:(NSData*) responseData
               error: (NSError*) requestError;

/**
 *  perform get with cache
 *
 *  @param handler         JSON handler
 *  @param url             request URL
 *  @param authConfig      configuration
 *  @param sessionDelegate URL session delegate
 */
+ (void) performGet:(JSONHandlerWithError)handler forURL:(NSURL*)url
             config: (BaseConfiguration*) authConfig
           delegate: (id<NSURLSessionDelegate>) sessionDelegate;
/**
 *  perform get
 *
 *  @param handler         JSON handler
 *  @param url             request URL
 *  @param authConfig      configuration
 *  @param sessionDelegate URL session delegate
 *  @param withoutCache    disable cache
 */
+ (void) performGet:(JSONHandlerWithError)handler forURL:(NSURL*)url
             config: (BaseConfiguration*) authConfig
           delegate: (id<NSURLSessionDelegate>) sessionDelegate
       disableCache:(BOOL) withoutCache;

/**
 *  perform get with header
 *
 *  @param handler         data handler
 *  @param url             request URL
 *  @param authConfig      configuration
 *  @param sessionDelegate session delegate
 *  @param extraHeader     extra header
 */
+ (void) performGet:(JSONHandlerWithError)handler
             forURL:(NSURL*) url
             config: (BaseConfiguration*) authConfig
           delegate:(id<NSURLSessionDelegate>) sessionDelegate
             header:(NSDictionary*) extraHeader;
/**
 *  perform get with cache settings
 *
 *  @param handler         data handler
 *  @param url             request URL
 *  @param authConfig      configuration
 *  @param sessionDelegate session delegate
 *  @param withoutCache    cache settings
 *  @param extraHeader     extra header
 */
+ (void) performGet:(JSONHandlerWithError)handler
             forURL:(NSURL*)url
             config:(BaseConfiguration*) authConfig
           delegate:(id<NSURLSessionDelegate>) sessionDelegate
       disableCache:(BOOL) withoutCache
             header:(NSDictionary*) extraHeader;

/**
 *  iOS 6 compatibility
 *
 *  @param handler      data handler
 *  @param url          request URL
 *  @param withoutCache disable cache
 *  @param config       configuration
 */
+ (void)performGet:(void (^)(NSURLResponse* response, NSData* data, NSError* connectionError))handler
            forURL:(NSURL*) url
      disableCache:(BOOL) withoutCache
     configuration: (BaseConfiguration *) config
            header:(NSDictionary*) extraHeader;

+ (BOOL)isOS6;

+ (NSMutableData *)addWavHeader:(NSData *)wavNoheader rate:(long) sampleRate;

+ (void)setProximityMonitor:(BOOL)enable;
@end
