//
//  EBRegion.h
//  EmpatikaBeaconsSDK
//
//  Copyright (c) 2014 empatika. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLBeaconRegion;

@interface EBTRegion : NSObject

@property (nonatomic, strong) NSString *uuid;
@property (nonatomic, strong) NSNumber *major;
@property (nonatomic, strong) NSNumber *minor;
@property (nonatomic, strong) NSString *identifier;

- (id)initWithBeaconRegion:(CLBeaconRegion *)region;
- (NSString *)fullIdentifier;

@end
