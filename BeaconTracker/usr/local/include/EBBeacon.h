//
//  EBBeacon.h
//  EmpatikaBeaconsSDK
//
//  Copyright (c) 2014 empatika. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLBeaconRegion.h>

@interface EBBeacon : NSObject

@property (nonatomic, strong) NSString *uuid;
@property (nonatomic, strong) NSNumber *major;
@property (nonatomic, strong) NSNumber *minor;
@property (nonatomic) CLProximity proximity;
@property (nonatomic) double accuracy;

- (id)initWithBeacon:(CLBeacon *)beacon;

@end
