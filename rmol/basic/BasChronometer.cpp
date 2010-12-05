// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// Rmol
#include <rmol/basic/BasChronometer.hpp>
#include <rmol/service/Logger.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  BasChronometer::BasChronometer () : _startTimeLaunched (false) {
  }

  // //////////////////////////////////////////////////////////////////////
  void BasChronometer::start () {
    // Get the time-stamp of now, and store it for later use
    _startTime = boost::posix_time::microsec_clock::local_time();
    
    // Update the boolean which states whether the chronometer
    // is launched
    _startTimeLaunched = true;
  }
    
  // //////////////////////////////////////////////////////////////////////
  double BasChronometer::elapsed () const {
    assert (_startTimeLaunched == true);
    
    // Get the time-stamp of now
    const boost::posix_time::ptime lStopTime =
      boost::posix_time::microsec_clock::local_time();
    
    // Calculate the time elapsed since the last time-stamp
    const boost::posix_time::time_duration lElapsedTime =
      lStopTime - _startTime;

    // Derived the corresponding number of milliseconds
    const double lElapsedTimeInMicroSeconds =
      static_cast<const double> (lElapsedTime.total_microseconds());
    
    /*RMOL_LOG_DEBUG ("Elapsed: " << lElapsedTime
      << "; (micros): "
      << lElapsedTimeInMicroSeconds / 1e6);*/
    
    // The elapsed time given in return is expressed in seconds
    return (lElapsedTimeInMicroSeconds / 1e6);
  }

}
