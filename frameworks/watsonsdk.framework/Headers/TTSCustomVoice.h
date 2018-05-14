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

#import <Foundation/Foundation.h>

#define TTS_CUSTOM_VOICE_LANGUAGE_EN_US @"en-US"
#define TTS_CUSTOM_VOICE_LANGUAGE_DE_DE @"de-DE"
#define TTS_CUSTOM_VOICE_LANGUAGE_EN_GB @"en-GB"
#define TTS_CUSTOM_VOICE_LANGUAGE_ES_ES @"es-ES"
#define TTS_CUSTOM_VOICE_LANGUAGE_ES_US @"es-US"
#define TTS_CUSTOM_VOICE_LANGUAGE_FR_FR @"fr-FR"
#define TTS_CUSTOM_VOICE_LANGUAGE_IT_IT @"it-IT"
#define TTS_CUSTOM_VOICE_LANGUAGE_JA_JP @"ja-JP"
#define TTS_CUSTOM_VOICE_LANGUAGE_PT_BR @"pt-BR"

@interface TTSCustomVoice : NSObject
@property NSString* name;
@property NSString* language;
@property NSString* description;

@property NSArray* words;

-(NSData*)producePostData;

@end
