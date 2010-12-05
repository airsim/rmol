#ifndef __RMOL_COM_BAS_BASCHRONOMETER_HPP
#define __RMOL_COM_BAS_BASCHRONOMETER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Date-Time (http://boost.org/doc/html/date_time/posix_time.html)
#include <boost/date_time/posix_time/posix_time.hpp>

namespace RMOL {

  /** Structure allowing measuring the time elapsed between two events. */
  struct BasChronometer {
    /** Constructor. */
    BasChronometer();
      
    /** Start the chronometer from the local time
        <br>The elapsed time given is the one elapsed since the start
        is launched. */
    void start ();
    
    /** Get the start time. */
    std::string getStart () const {
      return boost::posix_time::to_simple_string (_startTime);
    }
    
    /** Return the time elapsed since the structure has been instanciated.
        <br>That elapsed time is expressed in seconds. */
    double elapsed () const;
    
  private:
    /** Start time. */
    boost::posix_time::ptime _startTime;

    /** Boolean which states whether the chronometer is started or not.*/
    bool _startTimeLaunched;
  };

}
#endif // __RMOL_COM_BAS_BASCHRONOMETER_HPP
