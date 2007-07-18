// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasConst_GSL.hpp>
#include <latus/com/basic/BasConst_BOOST_DateTime.hpp>
#include <latus/com/basic/BasConst_BookingDay.hpp>
#include <latus/com/basic/BasConst_LATUS_Service.hpp>
#include <latus/com/basic/BasConst_CityPair.hpp>

namespace LATUS {

  namespace COM {
    
    // ///////// GSL /////////
    /** Default (GSL) random generator type. */
    const gsl_rng_type* DEFAULT_LATUS_RANDOM_GENERATOR_TYPE = gsl_rng_default;


    // ///////// BOOST Date-Time /////////
    // Time duration representing a full day
    // (i.e., 24h or 1,440 minutes or 86,400 seconds)

    /** Time duration representing a full day (in boost::time_duration unit).*/
    const boost::posix_time::time_duration BOOST_TIME_DURATION_FOR_A_DAY =
    boost::posix_time::hours(24);

    /** Time duration representing a full day (in seconds).*/
    const int TIME_DURATION_FOR_A_DAY_IN_SECONDS =
    static_cast<const int> (BOOST_TIME_DURATION_FOR_A_DAY.total_seconds());

    /** Date duration representing a full day (in boost::date_duration unit).*/
    const boost::gregorian::date_duration BOOST_DATE_DURATION_FOR_A_DAY (1);

    
    // //////// CityPair ////////
    /** Default booking date for BookingDay. */
    const boost::gregorian::date DEFAULT_BOOKING_DATE (2007,
                                                       boost::gregorian::Jan,
                                                       1);
    
    /** Default departure date for CityPairDate. */
    const boost::gregorian::date DEFAULT_DEPARTURE_DATE (2008,
                                                         boost::gregorian::Jan,
                                                         1);
    
    /** Date duration representing the time during which a flight-date is open
        to the reservation (in boost::date_duration unit).*/
    const boost::gregorian::date_duration DEFAULT_FLIGHT_DATE_RESERVATION_DURATION (365);

    
    // ///////// LATUS Service /////////

    /** Default number of airlines for the LATUS_Service. */
    const unsigned int DEFAULT_LATUS_SERVICE_NUMBER_OF_AIRLINES = 1;

  }

}
