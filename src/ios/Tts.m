//
//  Tts.m
//  Watson Text-to-Speech Plugin
//
//  Created by Mihui on 5/11/16.
//
//

#import "Tts.h"

@implementation Tts

static TTSConfiguration *ttsConfigurations = nil;

- (void) pluginInitialize{
    [self setTtsInstance:[TextToSpeech initWithConfig:[Tts sharedConfigurations]]];
    [[self ttsInstance] listVoices:^(NSDictionary* models, NSError* err){
        if(err){
            NSLog(@"Error getting voices[%ld]: %@", (long)[err code], [err description]);
        }
        else{
            for (NSDictionary* model in [models objectForKey:@"voices"]) {
                NSLog(@"### %@: %@ ###", [model valueForKey:@"name"], [model valueForKey:@"language"]);
            }
        }
    }];
}

+ (TTSConfiguration*) sharedConfigurations{
    if(ttsConfigurations == nil){
        NSString *credentialFilePath = [[NSBundle mainBundle] pathForResource:@"Credentials" ofType:@"plist"];
        NSDictionary *credentials = [[NSDictionary alloc] initWithContentsOfFile:credentialFilePath];

        ttsConfigurations = [[TTSConfiguration alloc] init];
        [ttsConfigurations setBasicAuthUsername:credentials[@"TTSUsername"]];
        [ttsConfigurations setBasicAuthPassword:credentials[@"TTSPassword"]];
        [ttsConfigurations setAudioCodec:WATSONSDK_TTS_AUDIO_CODEC_TYPE_OPUS];
        [ttsConfigurations setVoiceName:@"en-US_AllisonVoice"];
    }
    return ttsConfigurations;
}

- (void) synthesize:(CDVInvokedUrlCommand*) command{
    NSString *text = command.arguments[0];
    NSString *customizationId = nil;
    NSLog(@"[command.arguments count]->%ld", [command.arguments count]);
    if([command.arguments count] >= 2) {
        customizationId = command.arguments[1];
    }
    NSLog(@"customizationId->%@", customizationId);

    [[self ttsInstance] synthesize:^(NSData *data, NSError *err) {
        if(err){
            NSLog(@"Error requesting data[%ld]: %@", (long)[err code], [err description]);
            CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[err description]];
            [[self commandDelegate] sendPluginResult:result callbackId:[command callbackId]];
            return;
        }
        // Succeed
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Synthesize Succeed"];
        [[self commandDelegate] sendPluginResult:result callbackId:[command callbackId]];

        [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:nil];
        [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:nil];

        [[self ttsInstance] playAudio:^(NSError *err) {
            if (err){
                NSLog(@"Error playing audio[%ld]: %@", (long)[err code], [err description]);
                CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[err description]];
                [[self commandDelegate] sendPluginResult:result callbackId:[command callbackId]];
                return;
            }
        } withData:data];
    } theText: text customizationId: customizationId];
}

- (void) stop:(CDVInvokedUrlCommand*) command {
    [[self ttsInstance] stopAudio];
    CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Stop Succeed"];
    [self.commandDelegate sendPluginResult:result callbackId:[command callbackId]];
}

- (void) listVoices: (CDVInvokedUrlCommand*) command{
    [[self ttsInstance] listVoices:^(NSDictionary* voices, NSError* err){
        CDVPluginResult *result = nil;
        if(err){
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[err localizedDescription]];
        }
        else{
            NSString *model = [ttsConfigurations voiceName];
            NSArray *data = @[model, voices];
            result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsArray:data];
        }
        [[self commandDelegate] sendPluginResult:result callbackId:[command callbackId]];
    }];
}

- (void) setVoice:(CDVInvokedUrlCommand*) command{
    [ttsConfigurations setVoiceName:command.arguments[0]];
    [[[self ttsInstance] config] setVoiceName:command.arguments[0]];
    CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:command.arguments[0]];
    [[self commandDelegate] sendPluginResult:result callbackId:[command callbackId]];
}

@end
