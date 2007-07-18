#ifndef __LATUS_COM_BAS_BASCONST_BOOST_DATETIME_HPP
#define __LATUS_COM_BAS_BASCONST_BOOST_DATETIME_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace LATUS {

  namespace COM {

    /** Time duration representing a full day (in boost::time_duration unit).*/
    extern const boost::posix_time::time_duration BOOST_TIME_DURATION_FOR_A_DAY;

    /** Time duration representing a full day (in seconds).*/
    extern const int TIME_DURATION_FOR_A_DAY_IN_SECONDS;

    /** Date duration representing a full day (in boost::date_duration unit).*/
    extern const boost::gregorian::date_duration BOOST_DATE_DURATION_FOR_A_DAY;
    
  }
}
#endif // __LATUS_COM_BAS_BASCONST_BOOST_DATETIME_HPP
