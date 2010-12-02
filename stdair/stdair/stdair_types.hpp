#ifndef __STDAIR_STDAIR_TYPES_HPP
#define __STDAIR_STDAIR_TYPES_HPP

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
#include <stdair/stdair_exceptions.hpp>
#include <stdair/stdair_log.hpp>
#include <stdair/stdair_db.hpp>
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/stdair_fare_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/stdair_service.hpp>

namespace stdair {

  // //////// Type definitions /////////
  /** Define the type for network ID. */
  typedef std::string NetworkID_T;

  /** Define the file address type (e.g. "a_directory/a_filename")*/
  typedef std::string FileAddress_T;

  /** Define the replication number. */
  typedef unsigned int ReplicationNumber_T;

  /** Define the seed type of an Exponential function. */
  typedef unsigned long int ExponentialSeed_T;

  /** Define the seed type of an Uniform function. */
  typedef unsigned long int UniformSeed_T;

  /** Define the Request status for booking (1-letter-code, e.g.,
      B: booked, C: cancelled, R: Rejected). */
  typedef std::string RequestStatus_T;

  /** Define a mean value (e.g., 20.2). */
  typedef double MeanValue_T;

  /** Define a standard deviation value (e.g., 1.5). */
  typedef double StdDevValue_T;

  /** Define a map between a BookingID and a TravelSolutionID. */
  typedef std::map<Identity_T, Identity_T> BookingTSIDMap_T;

  /** Define a indicator of demand to class matching. */
  typedef double MatchingIndicator_T;

  /** Frequency of the Data Collection Point description (daily, monthly or
      detailed). */
  typedef std::string DCPModeFrequency_T;

  /** Mode of the Data Collection Point description (Forecaster only,
      Optimizer only or both of them). */
  typedef std::string DCPMode_T;

  /** Mode of the forecaster. */
  typedef std::string ForecasterMode_T;

  /** Limit of similar flight-dates used in the forecaster. */
  typedef short HistoricalDataLimit_T;

  /** Mode of the forecaster. */
  typedef std::string OptimizerMode_T;

  /** Mode of the forecaster. */
  typedef std::string DicoOptimizerMode_T;

  /** Mode of inventory control. */
  typedef std::string ControlMode_T;

  /** Define the name of a multiplier. */
  typedef double Multiplier_T;

  /** Define the name of a WTP-component of characteristics pattern. */
  typedef boost::tuples::tuple<double, double> CharacteristicsWTP_tuple_T;

  /** Define the name of sell-up probability flag for RMS optimizer. */
  typedef bool SellupFlagForOptimizer_T;

  /** Define the name of sell-up probability for RMS optimizer. */
  typedef double SellupProbabilityForOptimizer_T;

  /** Define the name of sell-up probability vector for RMS optimizer. */
  typedef std::vector<SellupProbabilityForOptimizer_T>
  SellupProbabilityVector_T;

  /** Define the demand for a policy. */
  typedef NbOfBookings_T PolicyDemand_T;

  /** Define the total revenue of an unconstrained policy. */
  typedef double PolicyRevenue_T;

  /** Define the total revenue of an unconstrained policy. */
  typedef double PolicyRevenue_T;

  // ///////////// Technical ////////////////
  /** File or directory name.
      <br>It may contain paths, relative or absolute (e.g., /foo/bar
      or C:\foo\bar). */
  typedef std::string Filename_T;
  
  // //////////////////////////////////////////////////////////////////////
  // Random generation
  /** Seed for the random generation, so that it can be reproductible. */
  typedef unsigned long int RandomSeed_T;
  
  /** Random number generator. */
  typedef boost::minstd_rand BaseGenerator_T;

  /** Uniform random generator. */
  typedef boost::variate_generator<stdair::BaseGenerator_T&,
                                   boost::uniform_real<> > UniformGenerator_T;

  // //////////////////////////////////////////////////////////////////////
  // Probability
  /** Probability */
  typedef float Probability_T;

  // //////////////////////////////////////////////////////////////////////
  /** Type definition for the hashed key of the DemandStreamKey object. */
  typedef std::string DemandStreamKeyStr_T;

  /** Type of booking channel (D=direct, I=indirect, N=oNline, F=oFfline). */
  typedef std::string ChannelLabel_T;

  /** Type of trip type (RO=outbound of round-trip, RI=inbound of round-trip, 
      OW=one way). */
  typedef std::string TripType_T;

  /** Type of frequent flyer (P=Platinum, G=Gold, S=Silver, M=Member, N=None). */
  typedef std::string FrequentFlyer_T;

}
#endif // __STDAIR_STDAIR_TYPES_HPP
