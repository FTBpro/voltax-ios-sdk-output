//
//  MMVideoViewError.h
//  VoltaxSDK
//
//  Created by Alon Shprung on 10/03/2022.
//

@interface MMVideoViewError : NSObject

@property (nonatomic, assign) NSString * _Nonnull message;
@property (nonatomic, assign) NSNumber * _Nonnull code;
@property (nonatomic, assign) bool isFatalError;

- (id _Nonnull )initWithMessage:(NSString * _Nonnull)message
                   code:(NSNumber * _Nonnull)code
                   isFatelError:(bool)isFatalError;
@end
