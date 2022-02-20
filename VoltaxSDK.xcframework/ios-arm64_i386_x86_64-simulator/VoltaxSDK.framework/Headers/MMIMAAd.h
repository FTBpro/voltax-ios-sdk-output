//
//  MMIMAAd.h
//  VoltaxSDK
//
//  Created by Alon Shprung on 20/02/2022.
//

@interface MMIMAAd : NSObject

@property (nonatomic, assign) double currentPosition;
@property (nonatomic, assign) double duration;

@property (nonatomic, assign) int adPosition;

@property (nonatomic, assign) NSString * _Nonnull contentType;

- (id _Nonnull) initWithCurrentPosition:(double)currentPosition duration:(double )duration adPosition:(int)adPosition contentType:(NSString * _Nonnull)contentType;

//- (id _Nonnull) initWithCurrentPosition:(double)currentPosition;

@end
