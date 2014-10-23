//
//  EBBeaconsTracker.h
//  Copyright (c) 2014 Empatika. All rights reserved.
//
//  Link your project with CoreLocation.framework and CoreBluetooth.framework library.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>

typedef NS_ENUM(NSInteger, EBTRegionState) {
    EBRegionStateInside,
    EBRegionStateOutside,
    EBRegionStateUnknown
};

/*
 *  EBRegion
 *
 *  Discussion:
 *    Represents a region entity.
 *
 *    @property NSString *uuid
 *      UUID of the region.
 *    @property NSNumber *major 
 *      Major version of the region.
 *    @property NSNumber *minor
 *      Minor version of the region.
 *    @property NSString *identifier
 *      Identifier of the region.
 */
@class EBTRegion;


/*
 *  EBbeacon
 *
 *  Discussion:
 *    Represents a beacon entity.
 *
 *    @property NSString *uuid
 *      UUID of the beacon.
 *    @property NSNumber *major
 *      Major version of the beacon.
 *    @property NSNumber *minor
 *      Minor version of the beacon.
 *    @property CLProximity proximity
 *      Proximity of the beacon from the device.
 *    @property double accuracy;
 *      Accuracy in meters between the beacon and the user device.
 */
@class EBTBeacon;


/*
 *  EBBeaconsTrackerDelegate
 *
 *  Discussion:
 *    Delegate for RBBeaconsTracker.
 */
@protocol EBTBeaconsTrackerDelegate <NSObject>

@optional

/*  
 *  determineState:forRegion:
 *
 *  Discussion:
 *    Invoked when a new state for the region is available. Works in background. 
 *
 *    Use of this method is preferable for user notification and motivation to open the application.
 */
- (void)determineState:(EBTRegionState)state forRegion:(EBTRegion *)region;

/*
 *  enterRegion:
 *
 *  Discussion:
 *    Invoked when the user enters a monitored region.
 *    Works only on foreground.
 */
- (void)managerDidEnterRegion:(EBTRegion *)region;

/*
 *  exitRegion:
 *
 *  Discussion:
 *    Invoked when the user exits a monitored region.
 *    Works only on foreground.
 */
- (void)managerDidExitRegion:(EBTRegion *)region;

/*
 *  rangeBeacon:forRegion:
 *
 *  Discussion:
 *    Invoked when a new state of beacon is available in the specified region. This method has strange
 *    behavior in background. Has a chance to be invoked while user is on lock screen. 
 *    Recommended to use only on foreground.
 */
- (void)managerDidRangeBeacon:(EBTBeacon *)beacon forRegion:(EBTRegion *)region;

/*
 *  rangeBeacons:forRegion:
 *
 *  Discussion:
 *    Invoked when a new state of beacon is available in the specified region. This method has strange
 *    behavior in background. Has a chance to be invoked while user is on lock screen.
 *    Recommended to use only on foreground.
 */
- (void)managerDidRangeBeacons:(NSArray *)beacons forRegion:(EBTRegion *)region;

/*
 *  bluetoothDidUpdateState
 *
 *  Discussion:
 *    Invoked when a new state of ble is available. Possible values are:
 *    See CBCentralManagerState doc.
 *
 */
- (void)bluetoothDidUpdateState:(CBCentralManagerState)state;

/*
 *  popupDidAppear
 *
 *  Discussion:
 *    Invoked when popup view is added as a subview to baseView property.
 *    Use this method for setting timers or other triggers for removing popup with method removePopupView:
 */
- (void)popupDidAppear;

@end


/*
 *  EBBeaconsTracker
 *
 *  Discussion:
 *    The EBBeaconsTracker is your entry point for monitoring the beacons.
 */
@interface EBTBeaconsTracker : NSObject

/*
 *  appID
 *
 *  Discussion:
 *    The unique appID that used inside SDK.
 */
@property (nonatomic, strong) NSString *appID;
@property (nonatomic) BOOL disableBluetoothDialog;

/*
 *  UUIDs
 *
 *  Discussion:
 *    The array of regions UUID
 */
@property (nonatomic, strong) NSArray *uuids;


/*
 *  baseView
 *
 *  Discussion:
 *    The view  used for popup view placement.
 */
@property (nonatomic, strong) UIView *baseView;


/*
 *  sharedInstance
 *
 *  Discussion:
 *    Returns instance of this class. Typical singleton pattern.
 */
+ (instancetype)sharedInstance;

/*
 *  addDelegate:
 *
 *  Discussion:
 *    Adds EBBeaconsTrackerDelegate object (weak reference) to delegates' array.
 */
- (void)addDelegate:(id<EBTBeaconsTrackerDelegate>)delegate;

/*
 *  removeDelegate:
 *
 *  Discussion:
 *    Removes EBBeaconsTrackerDelegate object from delegates' array.
 */
- (void)removeDelegate:(id<EBTBeaconsTrackerDelegate>)delegate;

/*
 *  startMonitoring
 *
 *  Discussion:
 *    Start monitoring beacons.
 *
 *    Requires a valid appID. Otherwise an IllegalAppID exception will be thrown.
 */
- (BOOL)startMonitoring;

/*
 *  stopMonitoring
 *
 *  Discussion:
 *    Stop monitoring beacons.
 */
- (void)stopMonitoringRegions;

/*
 *  stopMonitoringRegionWithUUID:
 *
 *  Discussion:
 *    Stop monitoring beacons in region with given uuid.
 */
- (void)stopMonitoringRegionWithUUID:(NSString *)uuid;

/*
 *  enableRules:
 *
 *  Discussion:
 *    Enable rules fetching and execution. By default, rules are disabled.
 */
- (void)enableRules;


/*
 *  disableRules:
 *
 *  Discussion:
 *    Disable rules fetching and execution. By default, rules are disabled.
 */
- (void)disableRules;


- (void)fetchRules;

/*
 *  removePopupView:
 *
 *  Discussion:
 *    Remove popup view from superview (baseView property).
 */
- (void)removePopupView;

/*
 */
- (void)setPopupOffset:(float)offset;

/*
 */
- (void)setCustomDictionary:(NSDictionary *)dict;

@end
