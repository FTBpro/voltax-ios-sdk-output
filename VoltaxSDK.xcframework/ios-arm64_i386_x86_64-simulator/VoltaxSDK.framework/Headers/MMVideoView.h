//
//  MMVideoView.h
//  VoltaxSDK
//
//  Created by Alon Shprung on 14/01/2021.
//

#import <UIKit/UIKit.h>
#import <VoltaxSDK/VoltaxSDK.h>
#import <VoltaxSDK/MMIMAAdsProvider.h>
#import <VoltaxSDK/MMVideoViewError.h>

@protocol MMVideoViewDelegate <NSObject>

@optional
-(void) mmVideoViewHeight:(CGFloat)height;

@optional
-(void) clickOnUrl:(NSURL * _Nonnull)url;

@optional
-(void) onPlayerLoaded;

@optional
-(void) onPlayerError:(MMVideoViewError * _Nonnull)error;

@end

@interface MMVideoView : NSObject

@property (nonatomic, assign) NSString * _Nullable articleUrl;

@property (nonatomic, weak) id<MMVideoViewDelegate> _Nullable delegate;

@property (nonatomic, weak) id<MMIMAAdsProvider> _Nullable adsProvider;

- (id _Nonnull )initWithPlayerId:(NSString * _Nonnull)playerId
                   contentId:(NSString * _Nonnull)contentId
                      articleUrl:(NSString * _Nullable)articleUrl;

- (id _Nonnull )initWithPlayerId:(NSString * _Nonnull)playerId
                       contentId:(NSString * _Nonnull)contentId;


-(void) load:(UIView * _Nonnull)containerView;

-(void) viewWillTransition:(id<UIViewControllerTransitionCoordinator> _Nonnull)coordinator;

-(void) willDisplay;

-(void) play;
-(void) pause;

@end
