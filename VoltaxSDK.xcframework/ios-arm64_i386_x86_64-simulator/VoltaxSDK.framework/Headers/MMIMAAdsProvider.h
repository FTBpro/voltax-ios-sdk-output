//
//  MMIMAAdsProvider.h
//  VoltaxSDK
//
//  Created by Alon Shprung on 16/01/2022.
//
#import <UIKit/UIKit.h>
#import "MMIMAAd.h"

typedef NS_ENUM(NSUInteger, MMIMAAdEvent) {
    EVENT_LOADED = 1,
    EVENT_PAUSE,
    EVENT_RESUME,
    EVENT_TAPPED,
    EVENT_COMPLETE,
    EVENT_STARTED,
    EVENT_SKIPPED,
    EVENT_CLICKED,
    EVENT_FIRST_QUARTILE,
    EVENT_MIDPOINT,
    EVENT_THIRD_QUARTILE
};

typedef NS_ENUM(NSUInteger, MMIMAAdsManagerTask) {
    ADS_MANAGER_START = 1,
    ADS_MANAGER_PAUSE,
    ADS_MANAGER_RESUME,
    ADS_MANAGER_MUTE,
    ADS_MANAGER_UNMUTE
};

@protocol MMIMAAdsProviderDelegate <NSObject>

-(void) adsLoaderDidRecieveError:(NSString * _Nullable)message;
-(void) adsManagerDidRecieveError:(NSString * _Nullable)message;
-(void) adsManagerDidRequestContentPause;
-(void) adsManagerDidRequestContentResume;
-(void) adsManagerDidRecieveEvent:(MMIMAAdEvent)event ad:(MMIMAAd * _Nonnull)ad;
-(void) handleSoundView:(UIView * _Nonnull)view;

@end

@protocol MMIMAAdsProvider <NSObject>

@property (nonatomic, weak) id<MMIMAAdsProviderDelegate> _Nullable delegate;

-(void) requestAdsInView:(UIView * _Nonnull)view with:(NSString * _Nonnull)tagUrl;
-(void) requestAdsManagerTo:(MMIMAAdsManagerTask)task;
-(bool) isPlaying;
-(bool) isMuted;

@end
