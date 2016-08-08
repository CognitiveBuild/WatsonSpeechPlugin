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
#import <AVFoundation/AVFoundation.h>
#import "SpeechUtility.h"
#import "TTSConfiguration.h"
#import "TTSCustomVoice.h"
#import "TTSCustomWord.h"

@interface TextToSpeech : NSObject <NSURLSessionDelegate>

@property (nonatomic,retain) TTSConfiguration *config;

+ (id)initWithConfig:(TTSConfiguration *)config;
- (id)initWithConfig:(TTSConfiguration *)config;

- (void)synthesize:(DataHandlerWithError) synthesizeHandler theText:(NSString*) text;
- (void)synthesize:(DataHandlerWithError) synthesizeHandler theText:(NSString*) text customizationId:(NSString*) customizationId;

- (void)listVoices:(JSONHandlerWithError)handler;
- (void)saveAudio:(NSData*) audio toFile:(NSString*) path;
- (void)playAudio:(void (^)(NSError*)) audioHandler withData:(NSData *) audio;
- (void)playAudio:(void (^)(NSError*)) audioHandler withData:(NSData *) audio sampleRate:(long) rate;
- (void)stopAudio;

- (void)createVoiceModelWithCustomVoice: (TTSCustomVoice*) customVoice handler: (JSONHandlerWithError) customizationHandler;
- (void)addWord:(NSString *)customizationId word:(TTSCustomWord *)customWord handler:(JSONHandlerWithError)customizationHandler;
- (void)addWords:(NSString *)customizationId voice:(TTSCustomVoice *)customVoice handler:(JSONHandlerWithError)customizationHandler;
- (void)deleteWord:(NSString *)customizationId word:(NSString *) wordString handler:(JSONHandlerWithError)customizationHandler;
- (void)listWords:(NSString *)customizationId handler:(JSONHandlerWithError)customizationHandler;
- (void)listWord:(NSString *)customizationId word:(NSString *) wordString handler:(JSONHandlerWithError)customizationHandler;
- (void)updateVoiceModelWithCustomVoice:(NSString *)customizationId voice:(TTSCustomVoice *)customVoice handler:(JSONHandlerWithError)customizationHandler;
- (void)deleteVoiceModel:(NSString *)customizationId handler:(JSONHandlerWithError)customizationHandler;
- (void)listCustomizedVoiceModels: (JSONHandlerWithError) handler;

- (void)queryPronunciation: (JSONHandlerWithError) handler text:(NSString*) theText;
- (void)queryPronunciation: (JSONHandlerWithError) handler text:(NSString*) theText parameters:(NSDictionary*) theParameters;
@end
