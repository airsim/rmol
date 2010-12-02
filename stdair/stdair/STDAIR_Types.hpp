#ifndef __STDAIR_STDAIR_TYPES_HPP
#define __STDAIR_STDAIR_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
#include <list>
#include <map>
// Boost Random
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>

// Forward declarations
namespace soci {
  class session;
  class statement;
}

namespace stdair {
  // Forward declarations
  class STDAIR_Service;

  // ////////////////////////////////////////////////////////////////////
  //
  // Exceptions
  //
  // ////////////////////////////////////////////////////////////////////
  // ////////////////////////////////////////////////////////////////////
  class RootException : public std::exception { 
  public:
    /** Constructors. */
    RootException (const std::string& iWhat) : _what (iWhat) {}
    RootException () : _what ("No more details") {}
    /** Destructor. */
    virtual ~RootException() throw() {}
    /** Give the details of the exception. */
    const char* what() const throw() { return _what.c_str(); } 
  protected:
    /** Details for the exception. */
    std::string _what;
  };
  // ////////////////////////////////////////////////////////////////////
  class FileNotFoundException : public RootException { 
  public:
    /** Constructor. */
    FileNotFoundException (const std::string& iWhat) : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedLogServiceException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedLogServiceException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedDBSessionManagerException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedDBSessionManagerException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedServiceException : public RootException {
  public:
    /** Constructor. */
    NonInitialisedServiceException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedContainerException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedContainerException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedRelationShipException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedRelationShipException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class MemoryAllocationException : public RootException { 
  public:
    /** Constructor. */
    MemoryAllocationException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class ObjectLinkingException : public RootException { 
  public:
    /** Constructor. */
    ObjectLinkingException (const std::string& iWhat) : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class ParserException : public RootException { 
  public:
    /** Constructor. */
    ParserException (const std::string& iWhat) : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class DocumentNotFoundException : public RootException {
  public:
    /** Constructor. */
    DocumentNotFoundException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class CodeConversionException : public ParserException {  
  public:
    /** Constructor. */
    CodeConversionException (const std::string& iWhat)
      : ParserException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class CodeDuplicationException : public ParserException { 
  public:
    /** Constructor. */
    CodeDuplicationException (const std::string& iWhat)
      : ParserException(iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class ObjectCreationgDuplicationException : public ParserException {
  public:
    /** Constructor. */
    ObjectCreationgDuplicationException (const std::string& iWhat) 
      : ParserException (iWhat) {} 
  };
  // ////////////////////////////////////////////////////////////////////
  class ObjectNotFoundException : public RootException {
  public:
    /** Constructor. */
    ObjectNotFoundException (const std::string& iWhat) : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class SQLDatabaseException : public RootException {
  public:
    /** Constructor. */
    SQLDatabaseException (const std::string& iWhat) : RootException (iWhat) {}
  };
  // ////////////////////////////////////////////////////////////////////
  class SQLDatabaseConnectionImpossibleException : public SQLDatabaseException {
  public:
    /** Constructor. */
    SQLDatabaseConnectionImpossibleException (const std::string& iWhat)
      : SQLDatabaseException (iWhat) {}
  };

  // /////////////// Log /////////////
  /** Level of logs. */
  namespace LOG {
    typedef enum {
      CRITICAL = 0,
      ERROR,
      NOTIFICATION,
      WARNING,
      DEBUG,
      VERBOSE,
      LAST_VALUE
    } EN_LogLevel;
    
    static const std::string _logLevels[LAST_VALUE] =
      {"C", "E", "N", "W", "D", "V"};
  }

  // //////// Type definitions /////////
  /** Database session handler. */
  typedef soci::session DBSession_T;
  
  /** Database request statement handler. */
  typedef soci::statement DBRequestStatement_T;
  
  /** Define the type for network ID. */
  typedef std::string NetworkID_T;

  /** Define the Airline Code type (2-letter-code, e.g., BA). */
  typedef std::string AirlineCode_T;

    /** Define a list of airline code. */
  typedef std::vector<AirlineCode_T> AirlineCodeList_T;

  /** Location code (3-letter-code, e.g., LON). */
  typedef std::string LocationCode_T;
  
  /** Define the Airport Code type (3-letter-code, e.g., LHR). */
  typedef LocationCode_T AirportCode_T;

  /** Define the type for flight numbers. */
  typedef unsigned short FlightNumber_T;

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

  /** Define the type for durations (e.g., elapsed in-flight time). */
  typedef boost::posix_time::time_duration Duration_T;

  /** Define the type for date (e.g., departure date of a flight). */
  typedef boost::gregorian::date Date_T;
    
  /** Time */
  typedef boost::posix_time::time_duration Time_T;

  /** Define an accurate time (date+time). */
  typedef boost::posix_time::ptime DateTime_T;

  /** Define a distance (kilometers). */
  typedef long int Distance_T;

  /** Define the Period (e.g., period during which flights depart). */
  typedef boost::gregorian::date_period DatePeriod_T;

  /** Define the Day-Of-the-Week as a string. */
  typedef std::string DOW_String_T;

  /** Define the Date Offset (e.g., -1 ). */
  typedef boost::gregorian::date_duration DateOffset_T;

  /** Define a duration in number of days. */
  typedef unsigned int DayDuration_T;

  /** Define the Saturday stay status of a travel. */
  typedef bool SaturdayStay_T;

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

  /** Define a percentage value (between 0 and 100%). */
  typedef double Percentage_T;

  /** Define a cancellation & and no-show rate pair. */
  typedef std::pair<Percentage_T, Percentage_T> CancellationNoShowRatePair_T;

  /** Define the identifier of a demand characteristics pattern
      (e.g. Ch12); for a customer choice model   */
  typedef std::string CharacteristicsPatternId_T;

  /** Define characteristics component index (e.g. W for WTP) */
  typedef std::string CharacteristicsIndex_T;

  /** Define the cabin code (class of service, e.g., first, business,
      economy). */
  typedef std::string CabinCode_T;

  /** Define a price value (e.g., 1000.0 Euros). */
  typedef double PriceValue_T;

  /** Define a price currency (e.g., EUR for Euros). */
  typedef std::string PriceCurrency_T;

  /** Define a Willingness-To-Pay (WTP) (e.g., 1000.0 Euros). */
  typedef double WTP_T;

  /** Define the number of seats (it can be non integer, because the
      overbooking can be applied at booking class or PNR level). */
  typedef double NbOfSeats_T;

  /** Define the number of seats required by a demand. */
  // typedef unsigned short NbOfSeats_T;

  /** Number of passengers (in a group) for a booking. */
  typedef unsigned short PartySize_T;

  /** Define a mean value (e.g., 20.2). */
  typedef double MeanValue_T;

  /** Define a standard deviation value (e.g., 1.5). */
  typedef double StdDevValue_T;

  /** Define the cabin capacity (resource, e.g., 200 seats).
      <br>The capacity is expressed as a double to cope with overbooking. */
  typedef double CabinCapacity_T;

  /** Define the number of seat which could not be used for the booking. */
  typedef double BlockSpace_T;

  /** Define the code of the fare family (e.g., 1, 2, 3, etc.). */
  typedef std::string FamilyCode_T;

  /** Define the booking class code (product segment class, e.g., H,
      B, K, etc.). */
  typedef std::string ClassCode_T;

    /** Define a list of class code. */
  typedef std::vector<ClassCode_T> ClassCodeList_T;

  /** Define the sub-class code (e.g., 0, 1, 2, etc.). The subclass is
      a sub-structure for the booking class, allowing to have specific
      rules for some criteria like POS. */
  typedef unsigned short SubclassCode_T;

  /** Define the flight path code (code made by a suite of flight numbers). */
  typedef std::string FlightPathCode_T;

  /** Define an availability. */
  typedef double Availability_T;

  /** Define an availability. */
  typedef bool AvailabilityStatus_T;

  /** Define a list of availabilities. */
  typedef std::vector<Availability_T> BucketAvailabilities_T;

  /** Define a identity number. */
  typedef unsigned long Identity_T;

  /** Define a map between a BookingID and a TravelSolutionID. */
  typedef std::map<Identity_T, Identity_T> BookingTSIDMap_T;

  /** Define a number of requests. */
  typedef double NbOfRequests_T;

  /** Define a number of bookings. */
  typedef NbOfRequests_T NbOfBookings_T;

  /** Define a number of cancellations (travellers). */
  typedef NbOfRequests_T NbOfCancellations_T;

  /** Define a number of no-shows. */
  typedef NbOfRequests_T NbOfNoShows_T;

  /** Define a number of fare rules. */
  typedef double NbOfFareRules_T;

  /** Define a number of yields. */
  typedef double NbOfYields_T;

  /** Define a number of InventoryControlRules. */
  typedef double NbOfInventoryControlRules_T;

  /** Define a number of flight dates. */
  typedef double NbOfFlightDates_T;

  /** Define the commited space of a cabin. */
  typedef double CommitedSpace_T;

  /** Define the unsold protection (UPR). */
  typedef double UPR_T;

  /** Define availibility of booking limit. */
  typedef bool CensorshipFlag_T;

  /** Define the list of censorship flags (une list per booking
      class, one censorship flag per DCP). */
  typedef std::vector<bool> CensorshipFlagList_T;

  /** Define the value of the booking limit. */
  typedef double BookingLimit_T;

  /** Define the value of the authorization level. */
  typedef double AuthorizationLevel_T;

  /** Define the value of the adjustment for cabin capacity. */
  typedef double CapacityAdjustment_T;

  /** Define the rate of overbooking */
  typedef double OverbookingRate_T;

  /** Define the bookingRatio (for instance OnD bookings
      over whole class bookings). */
  typedef double BookingRatio_T;

  /** Define the list of class codes as a string. */
  typedef std::string ClassList_String_T;

  /** Define a number of segment-dates (in a path). */
  typedef unsigned short NbOfSegments_T;

  /** Define a number of airlines (in a path). */
  typedef unsigned short NbOfAirlines_T;

  /** Define the fare of a travel solution. */
  typedef double Fare_T;

  /** Define the yield of a virtual class. */
  typedef double Yield_T;

  /** Define the Bid-Price. */
  typedef double BidPrice_T;

  /** Define a Bid-Price Vector. */
  typedef std::vector<BidPrice_T> BidPriceVector_T;

  /** Define the current index of a Bid-Price Vector (for a given LegCabin). */
  typedef unsigned int SeatIndex_T;
  
  /** Define a number of travel solutions
      (in a travel solution block). */
  typedef unsigned short NbOfTravelSolutions_T;

  /** Define a indicator of demand to class matching. */
  typedef double MatchingIndicator_T;

  /** Define an amount of revenue. */
  typedef double Revenue_T;

  /** Define the name of an event. */
  typedef std::string EventName_T;

  /** Define the name of an database connection. */
  typedef std::string DBConnectionName_T;

  /** Define a number of events. */
  typedef double NbOfEvents_T;

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
  
  /** Pointer on the STDAIR Service handler. */
  typedef boost::shared_ptr<STDAIR_Service> STDAIR_ServicePtr_T;

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
  // Date / Time
  /** Time duration in (integer) number of seconds */
  typedef long int IntDuration_T;

  /** Time duration in (long long integer) number of milliseconds */
  typedef long long int LongDuration_T;
  
  /** Duration in (float) number of time units */
  typedef float FloatDuration_T;

  // //////////////////////////////////////////////////////////////////////
  // Basic types
  /** Event type */
  typedef std::string EventType_T;
  
  /** Count */
  typedef int Count_T;
  
  /** City code */
  typedef LocationCode_T CityCode_T;
  
  /** Trip type */
  typedef std::string TripType_T;
  
  /** Monetary value */
  typedef double MonetaryValue_T;
  
  /** Real number */
  typedef double RealNumber_T;
  
  /** Type definition for the hashed key of the DemandStreamKey object. */
  typedef std::string DemandStreamKeyStr_T;

  /** Type of booking channel (D=direct, I=indirect, N=oNline, F=oFfline). */
  typedef std::string ChannelLabel_T;

  /** Type of trip type (RO=outbound of round-trip, RI=inbound of round-trip, 
      OW=one way). */
  typedef std::string TripType_T;

  /** Type of frequent flyer (P=Platinum, G=Gold, S=Silver, M=Member, N=None). */
  typedef std::string FrequentFlyer_T;

  /** Key of a STL map. */
  typedef std::string MapKey_T;

  /** List of keys. */
  typedef std::vector<std::string> KeyList_T;

  /** Map between the cabin codes and the booking class codes within
      each cabin. */
  typedef std::map<CabinCode_T, ClassList_String_T> CabinBookingClassMap_T;
  
}

#define CATCH_ALL_EXCEPTIONS                                            \
  catch (const stdair::FileNotFoundException& ex) {                     \
    std::cerr << "FileNotFoundException" << ex.what() << std::endl;     \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedLogServiceException& ex) {       \
    std::cerr << "NonInitialisedLogServiceException"                    \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedDBSessionManagerException& ex) { \
    std::cerr << "NonInitialisedDBSessionManagerException"              \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedServiceException& ex) {          \
    std::cerr << "NonInitialisedServiceException"                       \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedContainerException& ex) {        \
    std::cerr << "NonInitialisedContainerException"                     \
              << ex.what() <<std::endl;                                 \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedRelationShipException& ex) {     \
    std::cerr << "NonInitialisedRelationShipException"                  \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::MemoryAllocationException& ex) {               \
    std::cerr << "MemoryAllocationException" << ex.what() << std::endl; \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::ObjectLinkingException& ex) {                  \
    std::cerr << "ObjectLinkingException" << ex.what() << std::endl;    \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::CodeConversionException& ex) {                 \
    std::cerr << "CodeConversionException" << ex.what() << std::endl;   \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::CodeDuplicationException& ex) {                \
    std::cerr << "CodeDuplicationException" << ex.what() << std::endl;  \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::ObjectCreationgDuplicationException& ex) {     \
    std::cerr << "ObjectCreationgDuplicationException"                  \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::ObjectNotFoundException& ex) {                 \
    std::cerr << "ObjectNotFoundException" << ex.what() << std::endl;   \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::DocumentNotFoundException& ex) {               \
    std::cerr << "DocumentNotFoundException" << ex.what() << std::endl; \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::SQLDatabaseConnectionImpossibleException& ex) {\
    std::cerr << "SQLDatabaseConnectionImpossibleException"             \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::SQLDatabaseException& ex) {                    \
    std::cerr << "SQLDatabaseException" << ex.what() << std::endl;      \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::ParserException& ex) {                         \
    std::cerr << "ParserException" << ex.what() << std::endl;           \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::RootException& ex) {                           \
    std::cerr << "RootException" << ex.what() <<std::endl;              \
    return -1;                                                          \
                                                                        \
  } catch (const std::exception& stde) {                                \
    std::cerr << "Standard exception: " << stde.what() << std::endl;    \
    return -1;                                                          \
                                                                        \
  } catch (...) {                                                       \
    return -1;                                                          \
  } 

#endif // __STDAIR_STDAIR_TYPES_HPP
