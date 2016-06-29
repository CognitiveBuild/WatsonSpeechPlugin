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
#import "ogg.h"

@interface OggHelper : NSObject{
    ogg_page oggPage;
    ogg_int64_t packetCount;
    ogg_int16_t granulePos;
    ogg_stream_state streamState;
}

- (OggHelper *) init;
- (NSData *) getOggOpusHeader: (int) sampleRate;
- (NSMutableData *) writePacket: (NSData*) data frameSize:(int) frameSize;
@end
