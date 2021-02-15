//
//  MMSdkManager.h
//  VoltaxSDK
//
//  Created by Alon Shprung on 17/01/2021.
//

// The current version of the sdk
extern NSString * _Nonnull const MM_SDK_VERSION;

@interface MMSdkManager : NSObject

@property (nonatomic, assign) BOOL testMode;

+(MMSdkManager * _Nonnull) sharedInstance;

@end
