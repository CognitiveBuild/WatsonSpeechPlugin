/**
 * Copyright IBM Corporation 2017
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
 *  Find unexpected error by code
 *
 *  @param code HTTP / WebSocket status code
 *
 *  @return error message
 */
+ (NSString*)findUnexpectedErrorWithCode: (NSInteger)code;

/**
 *  Raise error with code
 *
 *  @param code error code
 *
 *  @return NSError
 */
+ (NSError*)raiseErrorWithCode:(NSInteger)code;

/**
 *  Raise error with message only
 *
 *  @param code         error code
 *  @param errorMessage error message
 *
 *  @return NSError
 */
+ (NSError*)raiseErrorWithCode: (NSInteger)code message: (NSString*) errorMessage;

/**
 *  Raise error with code and messages
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
 *  Process dictionary (JSON)
 *
 *  @param handler      JSON handler
 *  @param authConfig   configuration
 *  @param httpResponse HTTP response
 *  @param responseData response data
 *  @param requestError request error
 */
+ (void)processJSON: (JSONHandlerWithError)handler
                response:(NSURLResponse*) httpResponse
                    data:(NSData*) responseData
                   error: (NSError*) requestError;

/**
 *  Process binary
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
 *  Peform GET with cache
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
 *  Peform GET
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
 *  Peform GET with header
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
 *  Peform GET with cache settings
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
 *  Basic GET
 *
 *  @param handler          data handler
 *  @param url              request URL
 *  @param sessionDelegate  session delegate
 *  @param withoutCache     disable cache
 *  @param extraHeader      extra header
 */
+ (void) performGet:(void(^)(NSData *data, NSURLResponse *response, NSError *error))handler
             forURL:(NSURL*)url
           delegate: (id<NSURLSessionDelegate>) sessionDelegate
       disableCache:(BOOL) withoutCache
             header:(NSDictionary *)extraHeader;

/**
 Add Wav header

 @param wavNoheader Wav data without header
 @param sampleRate Sample rate
 @return Wav audio data with header
 */
+ (NSMutableData *)addWavHeader:(NSData *)wavNoheader rate:(long) sampleRate;


/**
 For detecting activity of proximity

 @param enable true as `Enable`, false otherwise
 */
+ (void)setProximityMonitor:(BOOL)enable;
@end
