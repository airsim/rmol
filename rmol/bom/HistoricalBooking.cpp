// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <iomanip>
// RMU
#include <rmol/bom/HistoricalBooking.hpp>

namespace RMOL {
    
  // //////////////////////////////////////////////////////////////////////
  HistoricalBooking::HistoricalBooking () : 
    _numberOfBookings (0.0),_unconstrainedDemand (0.0), _flag (false) {
  }

  // //////////////////////////////////////////////////////////////////////
  void HistoricalBooking::setParameters
  (const double iNumberOfBookings, const bool iFlag) {
    _numberOfBookings = iNumberOfBookings;
    _unconstrainedDemand = iNumberOfBookings;
    _flag = iFlag;
  }
    
  // //////////////////////////////////////////////////////////////////////
  HistoricalBooking::HistoricalBooking 
  (const HistoricalBooking& iHistoricalBooking) :
    _numberOfBookings (iHistoricalBooking.getNumberOfBookings()), 
    _unconstrainedDemand (iHistoricalBooking.getUnconstrainedDemand()),
    _flag (iHistoricalBooking.getFlag()) {
  }
    
  // //////////////////////////////////////////////////////////////////////
  HistoricalBooking::~HistoricalBooking() {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string HistoricalBooking::describe() const {
    std::ostringstream ostr;
    ostr << "Struct of hitorical booking, unconstrained demand and flag of "
         << "censorship for a FlightDate/Class.";
     
    return ostr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  void HistoricalBooking::toStream (std::ostream& ioOut) const {
    const double bj = getNumberOfBookings();
    const double uj = getUnconstrainedDemand();
    const bool fj = getFlag();
    ioOut << std::fixed << std::setprecision (2)
          << bj << "; " << uj << "; " << fj << std::endl;
  }
    
  // //////////////////////////////////////////////////////////////////////
  void HistoricalBooking::display () const {
    toStream (std::cout);
  }
}
