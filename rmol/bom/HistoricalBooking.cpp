// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <cassert>
#include <iomanip>
#include <iostream>
// RMOL
#include <rmol/bom/HistoricalBooking.hpp>

namespace RMOL {
    
  // ////////////////////////////////////////////////////////////////////
  HistoricalBooking::HistoricalBooking () : 
    _numberOfBookings (0.0),_unconstrainedDemand (0.0), _flag (false) {
  }

  // ////////////////////////////////////////////////////////////////////
  HistoricalBooking::
  HistoricalBooking (const stdair::NbOfBookings_T iNbOfBookings,
                     const stdair::Flag_T iFlag)
    : _numberOfBookings (iNbOfBookings),
      _unconstrainedDemand (iNbOfBookings), _flag (iFlag) {
  }
    
  // ////////////////////////////////////////////////////////////////////
  HistoricalBooking::HistoricalBooking 
  (const HistoricalBooking& iHistoricalBooking) :
    _numberOfBookings (iHistoricalBooking.getNbOfBookings()), 
    _unconstrainedDemand (iHistoricalBooking.getUnconstrainedDemand()),
    _flag (iHistoricalBooking.getFlag()) {
  }
    
  // ////////////////////////////////////////////////////////////////////
  HistoricalBooking::~HistoricalBooking() {
  }

  // ////////////////////////////////////////////////////////////////////
  void HistoricalBooking::setParameters
  (const stdair::NbOfBookings_T iNbOfBookings, const stdair::Flag_T iFlag) {
    _numberOfBookings = iNbOfBookings;
    _unconstrainedDemand = iNbOfBookings;
    _flag = iFlag;
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string HistoricalBooking::describe() const {
    std::ostringstream ostr;
    ostr << "Struct of hitorical booking, unconstrained demand and flag of "
         << "censorship for a FlightDate/Class.";
     
    return ostr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  void HistoricalBooking::toStream (std::ostream& ioOut) const {
    const stdair::NbOfBookings_T bj = getNbOfBookings();
    const stdair::NbOfBookings_T uj = getUnconstrainedDemand();
    const stdair::Flag_T fj = getFlag();
    ioOut << std::fixed << std::setprecision (2)
          << bj << "; " << uj << "; " << fj << std::endl;
  }
    
  // ////////////////////////////////////////////////////////////////////
  void HistoricalBooking::display () const {
    toStream (std::cout);
  }
}
