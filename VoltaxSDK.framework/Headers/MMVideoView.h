//
//  MMVideoView.h
//  VoltaxSDK
//
//  Created by Alon Shprung on 14/01/2021.
//

#import <UIKit/UIKit.h>
#import <VoltaxSDK/VoltaxSDK.h>

@protocol MMVideoViewDelegate <NSObject>

-(void) openUrl:(NSURL *_Nonnull)url;

@optional
-(void) mmVideoViewHeight:(CGFloat)height;

@end

@interface MMVideoView : NSObject

@property (nonatomic, assign) NSString * _Nullable articleUrl;

@property (nonatomic, weak) id<MMVideoViewDelegate> _Nullable delegate;

- (id _Nonnull )initWithPlayerId:(NSString * _Nonnull)playerId
                   contentId:(NSString * _Nonnull)contentId
                      articleUrl:(NSString * _Nonnull)articleUrl;

- (id _Nonnull )initWithPlayerId:(NSString * _Nonnull)playerId
                       contentId:(NSString * _Nonnull)contentId;


-(void) load:(UIView * _Nonnull)containerView;

-(void) viewWillTransition:(id<UIViewControllerTransitionCoordinator> _Nonnull)coordinator;

-(void) willDisplay;

@end
