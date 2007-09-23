// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasConst_GSL.hpp>
#include <latus/com/basic/BasConst_BOOST_DateTime.hpp>
#include <latus/com/basic/BasConst_WorldSchedule.hpp>
#include <latus/com/basic/BasConst_WholeDemand.hpp>
#include <latus/com/basic/BasConst_TravelSolution.hpp>
#include <latus/com/basic/BasConst_BookingDay.hpp>
#include <latus/com/basic/BasConst_LATUS_Service.hpp>
#include <latus/com/basic/BasConst_ServiceContextManagement.hpp>
#include <latus/com/basic/BasConst_CityPair.hpp>
#include <latus/com/basic/BasConst_Period_BOM.hpp>
#include <latus/com/basic/BasConst_ClassStruct.hpp>

namespace LATUS {

  namespace COM {
    
    // ///////// GSL /////////
    /** Default (GSL) random generator type. */
    const gsl_rng_type* DEFAULT_LATUS_RANDOM_GENERATOR_TYPE = gsl_rng_default;


    // ///////// BOOST Date-Time /////////
    // Time duration representing a full day
    // (i.e., 24h or 1,440 minutes or 86,400 seconds)

    /** Time duration representing a full day (in boost::time_duration unit).*/
    const Duration_T BOOST_TIME_DURATION_FOR_A_DAY =
      boost::posix_time::hours(24);

    /** Time duration representing a full day (in seconds).*/
    const int TIME_DURATION_FOR_A_DAY_IN_SECONDS =
    static_cast<const int> (BOOST_TIME_DURATION_FOR_A_DAY.total_seconds());

    /** Date duration representing a full day (in boost::date_duration unit).*/
    const DateOffSet_T BOOST_DATE_DURATION_FOR_A_DAY (1);

    
    // //////// (Flight-)Period-related BOM ///////
    /** Default date period (0-length, i.e., it lasts one day).*/
    const DatePeriod_T BOOST_DEFAULT_DATE_PERIOD (DateTime_T (2007, 1, 1),
                                                  DateTime_T (2007, 1, 1));

    /** Representation of Dow-Of-the-Week */
    const std::string DOW_STR[] = {"Mon", "Tue", "Wed", "Thu", "Fri",
                                   "Sat", "Sun"};
    
    /** Default DOW String (e.g., "1111100"). */
    const DOW_String_T DEFAULT_DOW_STRING ("1111100");
    
    /** Default Date OffSet (e.g., 0). */
    const DateOffSet_T DEFAULT_DATE_OFFSET (0);

    
    // //////// WorldSchedule ///////
    /** Default update date for the WorldSchedule. */
    const DateTime_T DEFAULT_WORLD_SCHEDULE_UPDATE_DATE (2007,
                                                         boost::gregorian::Jan,
                                                         1);
    

    // //////// WholeDemand ///////
    /** Default update date for the WholeDemand. */
    const DateTime_T DEFAULT_WHOLE_DEMAND_UPDATE_DATE (2007,
                                                       boost::gregorian::Jan,
                                                       1);
    

    // //////// (Segment-)Class-related BOM ///////
    /** Default booking number for ClassStruct_T. */
    const BookingNumber_T DEFAULT_CLASS_BOOKING_NUMBER = 0;
    
    /** Default availability for ClassStruct_T. */
    const Availability_T DEFAULT_CLASS_AVAILABILITY = 0.0;

     /** Default boolean for booking limit availability for ClassStruct_T. */
    const BookingLimitBool_T DEFAULT_CLASS_BOOKING_LIMIT_BOOL = false;

    /** Default booking limit value for ClassStruct_T. */
    const BookingLimit_T DEFAULT_CLASS_BOOKING_LIMIT = 0.0;

     /** Default over-booking rate for ClassStruct_T. */
    const OverbookingRate_T DEFAULT_CLASS_OVERBOOKING_RATE = 0.0;

    
    // //////// Travel Solutions ///////
    /** Default Minimum connection time. */
    const Duration_T DEFAULT_MINIMUM_CONNECTION_TIME (2, 0, 0);

    
    // //////// CityPair ////////
    /** Default booking date for BookingDay. */
    const DateTime_T DEFAULT_BOOKING_DATE (2007, boost::gregorian::Jan, 1);
    
    /** Default departure date for CityPairDate. */
    const DateTime_T DEFAULT_DEPARTURE_DATE (2008, boost::gregorian::Jan, 1);
    
    /** Date duration representing the time during which a flight-date is open
        to the reservation (in boost::date_duration unit).*/
    const DateOffSet_T DEFAULT_FLIGHT_DATE_RESERVATION_DURATION (365);

    
    // ///////// Service Context Management /////////

    /** Default name for the Simulator (SIM) module. */
    const std::string DEFAULT_LATUS_SIM_MODULE_NAME ("SIM");

    /** Default name for the Discrete Event Generator (DEG) module. */
    const std::string DEFAULT_LATUS_DEG_MODULE_NAME ("DEG");

    /** Default name for the User Choice Model (UCM) module. */
    const std::string DEFAULT_LATUS_UCM_MODULE_NAME ("UCM");

    /** Default name for the Central Reservation System (CRS) module. */
    const std::string DEFAULT_LATUS_CRS_MODULE_NAME ("CRS");

    /** Default name for the Travel Service Provider (TSP) module. */
    const std::string DEFAULT_LATUS_TSP_MODULE_NAME ("TSP");

    /** Default name for the Fare Quote (FQT) module. */
    const std::string DEFAULT_LATUS_FQT_MODULE_NAME ("FQT");

    /** Default root name for the Inventory (INV) module. */
    const std::string DEFAULT_LATUS_INV_ROOT_MODULE_NAME ("INV");

    /** Default root name for the Revenue Management System (RMS) module. */
    const std::string DEFAULT_LATUS_RMS_ROOT_MODULE_NAME ("RMS");

    
    // ///////// LATUS Service /////////

    /** Default number of airlines for the LATUS_Service. */
    const unsigned int DEFAULT_LATUS_SERVICE_NUMBER_OF_AIRLINES = 1;

    /** Maximum number of legs linked to a single flight-date.
        <br>Note that the number of derived segments is n*(n+1)/2 if n
        is the number of legs. */
    const unsigned short MAXIMUM_NUMBER_OF_LEGS_IN_FLIGHT = 7;

    /** Maximum number of segments linked to a single O&D
        (Origin & Destination). */
    const unsigned short MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND = 3;

    /** Default name for the first Inventory (INV) airline owner. */
    const std::string DEFAULT_LATUS_INV1_AIRLINE_CODE ("BA");

    /** Default name for the second Inventory (INV) airline owner. */
    const std::string DEFAULT_LATUS_INV2_AIRLINE_CODE ("AA");
  }

}
