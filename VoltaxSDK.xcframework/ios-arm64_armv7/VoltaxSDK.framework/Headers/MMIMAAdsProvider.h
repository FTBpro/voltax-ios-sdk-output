//
//  MMIMAAdsProvider.h
//  VoltaxSDK
//
//  Created by Alon Shprung on 16/01/2022.
//
#import <UIKit/UIKit.h>

@protocol MMIMAAdsProviderDelegate <NSObject>

-(void) adsLoaderDidRecieveError:(NSString * _Nullable)message;
-(void) adsManagerDidRecieveError:(NSString * _Nullable)message;
-(void) adsManagerDidRequestContentPause;
-(void) adsManagerDidRequestContentResume;

@end

@protocol MMIMAAdsProvider <NSObject>

@property (nonatomic, weak) id<MMIMAAdsProviderDelegate> _Nullable delegate;

-(void) requestAdsInView:(UIView * _Nonnull)view with:(NSString * _Nonnull)tagUrl;

@end
