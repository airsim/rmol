#ifndef __STDAIR_STDAIR_DEMAND_TYPES_HPP
#define __STDAIR_STDAIR_DEMAND_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
#include <map>
// Boost Random
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/tuple/tuple.hpp>
// StdAir
#include <stdair/stdair_basic_types.hpp>

namespace stdair {

  // //////// Type definitions /////////
  /** Define the availability option allowing the ticket change. */
  typedef bool ChangeFees_T;

  /** Define the refundable availability of a tickets. */
  typedef bool NonRefundable_T;

  /** Define the average ratio (between 0 and 100) of demand with
      a saturday stay status equal to TRUE. */
  typedef unsigned int SaturdayStayRatio_T;

  /** Define the average ratio of demand with change fee
      availability. */
  typedef unsigned int ChangeFeesRatio_T;

  /** Define the average ratio of demand with non-refundable
      availability. */
  typedef unsigned int NonRefundableRatio_T;

  /** Define the passenger characteristics, leisure or business
      for instance (1-letter-code, e.g., L or B). */
  typedef std::string PassengerType_T;

  /** Define the identifier of a distribution pattern (e.g., 1). */
  typedef std::string DistributionPatternId_T;

  /** Define the identifier of a cancellation rate curve (e.g., C1). */
  typedef std::string CancellationRateCurveId_T;

  /** Define the identifier of an airline preference set list (e.g., AP1). */
  typedef std::string AirlinePreferenceId_T;

  /** Define a cancellation & and no-show rate pair. */
  typedef std::pair<Percentage_T, Percentage_T> CancellationNoShowRatePair_T;

  /** Define the identifier of a demand characteristics pattern
      (e.g. Ch12); for a customer choice model   */
  typedef std::string CharacteristicsPatternId_T;

  /** Define characteristics component index (e.g. W for WTP) */
  typedef std::string CharacteristicsIndex_T;

  /** Define a Willingness-To-Pay (WTP) (e.g., 1000.0 Euros). */
  typedef double WTP_T;

  /** Define the name of a WTP-component of characteristics pattern. */
  typedef boost::tuples::tuple<double, WTP_T> CharacteristicsWTP_tuple_T;

  /** Define a number of cancellations (travellers). */
  typedef NbOfRequests_T NbOfCancellations_T;

  /** Define a number of no-shows. */
  typedef NbOfRequests_T NbOfNoShows_T;

  /** Define a indicator of demand to class matching. */
  typedef double MatchingIndicator_T;

  /** Define the name of an event. */
  typedef std::string EventName_T;

  /** Define a number of events. */
  typedef double NbOfEvents_T;

  /** Type definition for the hashed key of the DemandStreamKey object. */
  typedef std::string DemandStreamKeyStr_T;

  /** Type of booking channel (D=direct, I=indirect, N=oNline, F=oFfline). */
  typedef std::string ChannelLabel_T;

  /** Type of trip type (RO=outbound of round-trip, RI=inbound of round-trip, 
      OW=one way). */
  typedef std::string TripType_T;

  /** Type of frequent flyer (P=Platinum, G=Gold, S=Silver, M=Member, N=None).*/
  typedef std::string FrequentFlyer_T;

  /** Define the Request status for booking (1-letter-code, e.g.,
      B: booked, C: cancelled, R: Rejected). */
  typedef std::string RequestStatus_T;

  /** Define a map between a BookingID and a TravelSolutionID. */
  typedef std::map<Identity_T, Identity_T> BookingTSIDMap_T;

}
#endif // __STDAIR_STDAIR_DEMAND_TYPES_HPP
