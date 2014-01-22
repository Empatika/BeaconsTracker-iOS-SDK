//
//  EBBeaconsTracker.h
//  Copyright (c) 2014 Empatika. All rights reserved.
//
//  Link your project with CoreLocation.framework library.
//
//

#import <Foundation/Foundation.h>

/*
 *  EBRegion
 *
 *  Discussion:
 *    Represents a region entity.
 *
 *    @property NSNumber *major
 *      Major version of the region.
 *    @property NSNumber *minor
 *      Minor version of the region.
 *    @property NSString *identifier
 *      Identifier of the region.
 */
@class EBRegion;


/*
 *  EBbeacon
 *
 *  Discussion:
 *    Represents a beacon entity.
 *
 *    @property NSNumber *major
 *      Major version of the beacon.
 *    @property NSNumber *minor
 *      Minor version of the beacon.
 *    @property CLProximity proximity
 *      Proximity of the beacon from the device.
 *    @property double accuracy;
 *      Accuracy in meters between the beacon and the user device.
 */
@class EBBeacon;


/*
 *  EBBeaconsTrackerDelegate
 *
 *  Discussion:
 *    Delegate for RBBeaconsTracker.
 */
@protocol EBBeaconsTrackerDelegate <NSObject>

@optional

/*  
 *  determineState:forRegion:
 *
 *  Discussion:
 *    Invoked when a new state for the region is available. Possible values for state are @"inside", 
 *    @"outside" and @"unknown". Works in background. 
 *
 *    Use of this method is preferable for user notification and motivation to open the application.
 */
- (void)determineState:(NSString *)state forRegion:(EBRegion *)region;

/*
 *  enterRegion:
 *
 *  Discussion:
 *    Invoked when the user enters a monitored region.
 *    Works only on foreground.
 */
- (void)enterRegion:(EBRegion *)region;

/*
 *  exitRegion:
 *
 *  Discussion:
 *    Invoked when the user exits a monitored region.
 *    Works only on foreground.
 */
- (void)exitRegion:(EBRegion *)region;

/*
 *  rangeBeacon:forRegion:
 *
 *  Discussion:
 *    Invoked when a new state of beacon is available in the specified region. This method has strange
 *    behavior in background. Has a chance to be invoked while user is on lock screen. 
 *    Recommended to use only on foreground.
 */
- (void)rangeBeacon:(EBBeacon *)beacon forRegion:(EBRegion *)region;

@end


/*
 *  EBBeaconsTracker
 *
 *  Discussion:
 *    The EBBeaconsTracker is your entry point for monitoring the beacons.
 */
@interface EBBeaconsTracker : NSObject

/*
 *  appID
 *
 *  Discussion:
 *    The unique appID that used inside SDK.
 */
@property (nonatomic) NSString *appID;


/*
 *  sharedInstance
 *
 *  Discussion:
 *    Returns instance of this class. Typical singleton pattern.
 */
+ (id)sharedInstance;

/*
 *  addDelegate:
 *
 *  Discussion:
 *    Adds EBBeaconsTrackerDelegate object to delegates' array.
 */
- (void)addDelegate:(id<EBBeaconsTrackerDelegate>)delegate;

/*
 *  removeDelegate:
 *
 *  Discussion:
 *    Removes EBBeaconsTrackerDelegate object from delegates' array.
 */
- (void)removeDelegate:(id<EBBeaconsTrackerDelegate>)delegate;

/*
 *  startMonitoring:
 *
 *  Discussion:
 *    Start monitoring beacons.
 *
 *    Requires a valid appID. Otherwise an IllegalAppID exception will be thrown.
 */
- (void)startMonitoring;

/*
 *  stopMonitoring:
 *
 *  Discussion:
 *    Stop monitoring beacons.
 */
- (void)stopMonitoring;

@end
