/**
 * Copyright IBM Corporation 2015
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

#import <Foundation/Foundation.h>

#define WATSON_DATAFORMAT_ERROR_CODE 700
// Only used for the code returned from connection closure delegate
#define WATSON_WEBSOCKETS_ERROR_CODE 701
// http://www.ibm.com/watson/developercloud/doc/speech-to-text/websockets.shtml#WSreturn
#define WATSON_SPEECHAPIS_ERROR_CODE 702
#define WATSON_PERMISSION_ERROR_CODE 800
#define WATSON_SDK_ERROR_DOMAIN @"Watons Speech SDK"

#define HTTP_METHOD_GET @"GET"
#define HTTP_METHOD_POST @"POST"
#define HTTP_METHOD_PUT @"PUT"
#define HTTP_METHOD_DELETE @"DELETE"

#define WEBSOCKETS_SCHEME @"wss"

typedef void (^DataHandlerWithError) (NSData* data, NSError* error);
typedef void (^JSONHandlerWithError) (NSDictionary* dict, NSError* error);

typedef void (^DataHandler)(NSData* data);
typedef void (^ClosureHandler)(NSInteger code, NSString* reason);
typedef void (^PowerLevelHandler)(float powerLevel);

@interface BaseConfiguration : NSObject

@property NSString* basicAuthUsername;
@property NSString* basicAuthPassword;

@property (nonatomic, retain) NSString *token;
@property (copy, nonatomic) void (^tokenGenerator) (void (^tokenHandler)(NSString *token));

@property (readonly) NSString* apiURL;
@property NSURL* apiEndpoint;
@property BOOL isCertificateValidationDisabled;
@property BOOL xWatsonLearningOptOut;

- (void) invalidateToken;
- (void)requestToken:(void (^)(BaseConfiguration *config))completionHandler refreshCache:(BOOL) refreshCachedToken;
- (NSMutableDictionary*) createRequestHeaders;

- (void)setApiURL:(NSString *)apiURLStr;

- (NSURL*)getRequestURL:(NSString*) servicePath params:(NSDictionary*)parameters;
- (NSURL*)getRequestURL:(NSString*) servicePath params:(NSDictionary*)parameters isWebSocket:(BOOL) isUsingWebSocket;
@end
