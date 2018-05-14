//
//  Stt.m
//  Watson Speech-to-Text Plugin
//
//  Created by Mihui on 5/11/16.
//
//

#import "Stt.h"

@implementation Stt

@synthesize sttInstance = _sttInstance;

static STTConfiguration *sttConfigurations = nil;
NSString *recognitionCallbackId = nil;

- (void)pluginInitialize{
    [self setSttInstance:[SpeechToText initWithConfig:[Stt sharedConfigurations]]];
}

/**
 *  Get speech recognition configurations
 *
 *  @return STTConfiguration*
 */
+ (STTConfiguration*) sharedConfigurations{
    if(sttConfigurations == nil){
        NSString *credentialFilePath = [[NSBundle mainBundle] pathForResource:@"Credentials" ofType:@"plist"];
        NSDictionary *credentials = [[NSDictionary alloc] initWithContentsOfFile:credentialFilePath];

        sttConfigurations = [[STTConfiguration alloc] init];
        [sttConfigurations setBasicAuthUsername:credentials[@"STTUsername"]];
        [sttConfigurations setBasicAuthPassword:credentials[@"STTPassword"]];
        [sttConfigurations setApiURL:@"https://stream.watsonplatform.net/speech-to-text/api"];
        [sttConfigurations setAudioCodec:WATSONSDK_AUDIO_CODEC_TYPE_OPUS];
        [sttConfigurations setModelName:WATSONSDK_DEFAULT_STT_MODEL];
        [sttConfigurations setInterimResults:YES];
    }
    return sttConfigurations;
}

/**
 *  Send data back to JavaScript
 *
 *  @param message  Transcription
 *  @param isEnding If the message is final transcription
 */
- (void) send:(NSDictionary*) res{
    SpeechToTextResult *sttResult = [[self sttInstance] getResult:res];
    NSString *transcript = ([sttResult transcript] == nil ? @"" : [sttResult transcript]);
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] initWithCapacity:2];
    [dict setObject:transcript forKey:@"message"];
    [dict setObject:[sttResult isFinal] ? @"Yes": @"No" forKey:@"isfinal"];
    [dict setObject:[sttResult isCompleted] ? @"Yes": @"No" forKey:@"iscompleted"];

    CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: dict];
    [result setKeepCallback:[NSNumber numberWithBool:YES]];
    [[self commandDelegate] sendPluginResult:result callbackId: recognitionCallbackId];
}


/**
 *  Start speech recognition
 *
 *  @param command CDVInvokedUrlCommand*
 */
- (void) recognize:(CDVInvokedUrlCommand*) command{
    [self _recognize:command];
}

/**
 *  Start speech recognition
 *
 *  @param command CDVInvokedUrlCommand*
 */
- (void) _recognize:(CDVInvokedUrlCommand*) command{
    recognitionCallbackId = [command callbackId];
    [[self sttInstance] recognize:^(NSDictionary* res, NSError* err){
        if(err) {

            [[self sttInstance] endRecognize];
            CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[err localizedDescription]];
            [[self commandDelegate] sendPluginResult:result callbackId:recognitionCallbackId];
            return;
        }

        [self.commandDelegate runInBackground:^{
            [self send:res];
        }];
    }];
}

/**
 *  Send out the end marker of WebSocket
 *
 *  @param command CDVInvokedUrlCommand*
 */
- (void) endTransmission:(CDVInvokedUrlCommand*) command {
    CDVCommandStatus status = CDVCommandStatus_NO_RESULT;
    NSString *message = @"";
    [[self sttInstance] endTransmission];
    message = @"Marker has been sent or buffered";
    status = CDVCommandStatus_OK;
    CDVPluginResult * result = [CDVPluginResult resultWithStatus:status messageAsString:message];
    [[self commandDelegate] sendPluginResult:result callbackId:[command callbackId]];
}


/**
 *  Query all the supported language models
 *
 *  @param command CDVInvokedUrlCommand*
 */
- (void) listModels: (CDVInvokedUrlCommand*) command {
    [[self sttInstance] listModels:^(NSDictionary* models, NSError* err) {
        CDVPluginResult *result = nil;
        if(err){
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[err localizedDescription]];
        }
        else{
            NSString *model = [sttConfigurations modelName];
            NSArray *data = @[model, models];
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsArray:data];
        }
        [[self commandDelegate] sendPluginResult:result callbackId:[command callbackId]];
    }];
}

/**
 *  Set language model
 *
 *  @param command CDVInvokedUrlCommand*
 */
- (void) setModel:(CDVInvokedUrlCommand*) command {
    [sttConfigurations setModelName:command.arguments[0]];
    [[[self sttInstance] config] setModelName:command.arguments[0]];
    CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:command.arguments[0]];
    [[self commandDelegate] sendPluginResult:result callbackId:[command callbackId]];
}

@end
