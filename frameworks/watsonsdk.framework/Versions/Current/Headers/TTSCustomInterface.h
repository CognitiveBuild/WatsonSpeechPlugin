//
//  TTSCustomInterface.h
//  watsonsdk
//
//  Created by Mihui on 5/26/16.
//  Copyright © 2016 IBM. All rights reserved.
//

#ifndef TTSCustomInterface_h
#define TTSCustomInterface_h

#import <Foundation/Foundation.h>

@interface TTSCustomInterface : NSObject

-(NSData*)producePostData;
-(NSMutableDictionary*)produceDictionary;

@end

#endif /* TTSCustomInterface_h */
