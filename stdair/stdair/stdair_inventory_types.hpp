#ifndef __STDAIR_STDAIR_INVENTORY_TYPES_HPP
#define __STDAIR_STDAIR_INVENTORY_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
#include <map>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>

namespace stdair {

  // //////// Type definitions /////////
  /** Define the type for network ID. */
  typedef std::string NetworkID_T;

  /** Define a list of airline code. */
  typedef std::vector<AirlineCode_T> AirlineCodeList_T;

  /** Define a list of class code. */
  typedef std::vector<ClassCode_T> ClassCodeList_T;

  /** Define the sub-class code (e.g., 0, 1, 2, etc.). The subclass is
      a sub-structure for the booking class, allowing to have specific
      rules for some criteria like POS. */
  typedef unsigned short SubclassCode_T;

  /** Define the flight path code (code made by a suite of flight numbers). */
  typedef std::string FlightPathCode_T;

  /** Map between the cabin codes and the booking class codes within
      each cabin. */
  typedef std::map<CabinCode_T, ClassList_String_T> CabinBookingClassMap_T;
  
  /** Define the cabin capacity (resource, e.g., 200 seats).
      <br>The capacity is expressed as a double to cope with overbooking. */
  typedef double CabinCapacity_T;

  /** Define a number of flight dates. */
  typedef double NbOfFlightDates_T;

  /** Define the commited space of a cabin. */
  typedef double CommitedSpace_T;

  /** Define the unsold protection (UPR). */
  typedef double UPR_T;

  /** Define the value of the booking limit. */
  typedef double BookingLimit_T;

  /** Define the value of the authorization level. */
  typedef double AuthorizationLevel_T;

  /** Define the value of the adjustment for cabin capacity. */
  typedef double CapacityAdjustment_T;

  /** Define the number of seat which could not be used for the booking. */
  typedef double BlockSpace_T;

  /** Define an availability status (AVS). */
  typedef bool AvailabilityStatus_T;

  /** Define a list of availabilities. */
  typedef std::vector<Availability_T> BucketAvailabilities_T;

  /** Define a number of yields. */
  typedef double NbOfYields_T;

  /** Define a number of InventoryControlRules. */
  typedef double NbOfInventoryControlRules_T;

  /** Define availibility of booking limit. */
  typedef bool CensorshipFlag_T;

  /** Define the list of censorship flags (une list per booking
      class, one censorship flag per DCP). */
  typedef std::vector<bool> CensorshipFlagList_T;

  /** Define the bookingRatio (for instance OnD bookings
      over whole class bookings). */
  typedef double BookingRatio_T;

  /** Define the yield of a virtual class. */
  typedef double Yield_T;

  /** Define the Bid-Price. */
  typedef double BidPrice_T;

  /** Define a Bid-Price Vector. */
  typedef std::vector<BidPrice_T> BidPriceVector_T;

  /** Define the current index of a Bid-Price Vector (for a given LegCabin). */
  typedef unsigned int SeatIndex_T;
  
  /** Mode of inventory control. */
  typedef std::string ControlMode_T;

}
#endif // __STDAIR_STDAIR_INVENTORY_TYPES_HPP
