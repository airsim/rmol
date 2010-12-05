#ifndef __STDAIR_STDAIR_DATE_TIME_TYPES_HPP
#define __STDAIR_STDAIR_DATE_TIME_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace stdair {

  // //////// Type definitions /////////
  /** Define the type for durations (e.g., elapsed in-flight time). */
  typedef boost::posix_time::time_duration Duration_T;

  /** Define the type for date (e.g., departure date of a flight). */
  typedef boost::gregorian::date Date_T;
    
  /** Time */
  typedef boost::posix_time::time_duration Time_T;

  /** Define an accurate time (date+time). */
  typedef boost::posix_time::ptime DateTime_T;

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
  
  /** Time duration in (integer) number of seconds */
  typedef long int IntDuration_T;

  /** Time duration in (long long integer) number of milliseconds */
  typedef long long int LongDuration_T;
  
  /** Duration in (float) number of time units */
  typedef float FloatDuration_T;

}
#endif // __STDAIR_STDAIR_DATE_TIME_TYPES_HPP
