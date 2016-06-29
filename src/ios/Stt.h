//
//  Stt.h
//  Watson Speech-to-Text Plugin
//
//  Created by Mihui on 5/11/16.
//
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

#import "Cordova/CDVPlugin.h"
#import "watsonsdk/SpeechToText.h"
#import "watsonsdk/STTConfiguration.h"

@interface Stt : CDVPlugin<AVAudioPlayerDelegate>

@property SpeechToText *sttInstance;

- (void) recognize:(CDVInvokedUrlCommand*) command;
- (void) endTransmission:(CDVInvokedUrlCommand*) command;
- (void) listModels: (CDVInvokedUrlCommand*) command;
- (void) setModel:(CDVInvokedUrlCommand*) command;

@end
