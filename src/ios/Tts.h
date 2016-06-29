//
//  Tts.h
//  Watson Text-to-Speech Plugin
//
//  Created by Mihui on 5/11/16.
//
//

#import <Foundation/Foundation.h>
#import "Cordova/CDVPlugin.h"
#import "watsonsdk/TextToSpeech.h"
#import "watsonsdk/TTSConfiguration.h"

@interface Tts : CDVPlugin

@property NSArray *ttsVoices;
@property TextToSpeech *ttsInstance;

- (void) synthesize:(CDVInvokedUrlCommand*) command;
- (void) stop:(CDVInvokedUrlCommand*) command;
- (void) listVoices: (CDVInvokedUrlCommand*) command;
- (void) setVoice:(CDVInvokedUrlCommand*) command;

@end
