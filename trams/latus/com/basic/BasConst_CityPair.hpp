#ifndef __COM_BAS_BASCONT_CITYPAIR_HPP
#define __COM_BAS_BASCONT_CITYPAIR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>

namespace LATUS {

  namespace COM {

    /** Default departure date for CityPairDate. */
    extern const boost::gregorian::date DEFAULT_DEPARTURE_DATE;
    
    /** Date duration representing the time during which a flight-date is open
        to the reservation (in boost::date_duration unit).*/
    extern const boost::gregorian::date_duration DEFAULT_FLIGHT_DATE_RESERVATION_DURATION;

    /** Default nember of required seats by the demand. */
    extern const unsigned short DEFAULT_NUMBER_OF_REQUIRED_SEATS;

    /** Default epsilon value in order to be able to compare
        availabilities with 0. */
    extern const double DEFAULT_EPSILON_VALUE;

  }
}
#endif
