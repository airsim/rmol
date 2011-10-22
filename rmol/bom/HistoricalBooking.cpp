// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
// C
#include <assert.h>
// STL
#include <iostream>
#include <iomanip>
// RMU
=======
// STL
#include <sstream>
#include <cassert>
#include <iomanip>
#include <iostream>
// RMOL
>>>>>>> 0.24
#include <rmol/bom/HistoricalBooking.hpp>

namespace RMOL {
    
<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////////
=======
  // ////////////////////////////////////////////////////////////////////
>>>>>>> 0.24
  HistoricalBooking::HistoricalBooking () : 
    _numberOfBookings (0.0),_unconstrainedDemand (0.0), _flag (false) {
  }

<<<<<<< HEAD
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
=======
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
>>>>>>> 0.24
    _unconstrainedDemand (iHistoricalBooking.getUnconstrainedDemand()),
    _flag (iHistoricalBooking.getFlag()) {
  }
    
<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////////
  HistoricalBooking::~HistoricalBooking() {
  }

  // //////////////////////////////////////////////////////////////////////
=======
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
>>>>>>> 0.24
  const std::string HistoricalBooking::describe() const {
    std::ostringstream ostr;
    ostr << "Struct of hitorical booking, unconstrained demand and flag of "
         << "censorship for a FlightDate/Class.";
     
    return ostr.str();
  }
    
<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////////
  void HistoricalBooking::toStream (std::ostream& ioOut) const {
    const double bj = getNumberOfBookings();
    const double uj = getUnconstrainedDemand();
    const bool fj = getFlag();
=======
  // ////////////////////////////////////////////////////////////////////
  void HistoricalBooking::toStream (std::ostream& ioOut) const {
    const stdair::NbOfBookings_T bj = getNbOfBookings();
    const stdair::NbOfBookings_T uj = getUnconstrainedDemand();
    const stdair::Flag_T fj = getFlag();
>>>>>>> 0.24
    ioOut << std::fixed << std::setprecision (2)
          << bj << "; " << uj << "; " << fj << std::endl;
  }
    
<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////////
=======
  // ////////////////////////////////////////////////////////////////////
>>>>>>> 0.24
  void HistoricalBooking::display () const {
    toStream (std::cout);
  }
}
