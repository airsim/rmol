// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
// StdAir
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  HistoricalBookingHolder::HistoricalBookingHolder () {
  }

  // ////////////////////////////////////////////////////////////////////
  HistoricalBookingHolder::~HistoricalBookingHolder () {
    _historicalBookingVector.clear();
  }

  // ////////////////////////////////////////////////////////////////////
  const short HistoricalBookingHolder::getNbOfFlights () const {
    return _historicalBookingVector.size();
  }

  // ////////////////////////////////////////////////////////////////////
  const short HistoricalBookingHolder::getNbOfUncensoredData () const {
    short lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const stdair::Flag_T lFlag = _historicalBookingVector.at(ite).getFlag ();
      if (lFlag == false) {
        ++ lResult;
      }
    }

    return lResult;
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::NbOfBookings_T HistoricalBookingHolder::
  getNbOfUncensoredBookings () const {
    stdair::NbOfBookings_T lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking& lHistorialBooking =
        _historicalBookingVector.at (ite);
      const stdair::Flag_T lFlag = lHistorialBooking.getFlag ();
      if (lFlag == false) {
        const stdair::NbOfBookings_T& lBooking = 
          lHistorialBooking.getNbOfBookings ();
        lResult += lBooking;
      }
    }

    return lResult;
  }

  // ////////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::
  getUncensoredStandardDeviation (const double& iMeanOfUncensoredBookings,
                                  const short iNbOfUncensoredData) const {
      
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const stdair::Flag_T lFlag = _historicalBookingVector.at(ite).getFlag ();
      if (lFlag == false) {
        const HistoricalBooking& lHistorialBooking =
          _historicalBookingVector.at (ite);
          
        const stdair::NbOfBookings_T& lBooking =
          lHistorialBooking.getNbOfBookings ();
          
        lResult += (lBooking - iMeanOfUncensoredBookings)
          * (lBooking - iMeanOfUncensoredBookings);
      }
    }
    lResult /= (iNbOfUncensoredData - 1);
    lResult = std::sqrt (lResult);
      
    return lResult;
  }

  // ////////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getDemandMean () const {
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking& lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const stdair::NbOfBookings_T& lDemand =
        lHistorialBooking.getUnconstrainedDemand ();
        
      lResult += static_cast<double>(lDemand);
    }

    lResult /= lSize;

    return lResult;
  }

  // ////////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getStandardDeviation
  (const double iDemandMean) const {
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking& lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const stdair::NbOfBookings_T& lDemand =
        lHistorialBooking.getUnconstrainedDemand ();
        
      const double lDoubleDemand = static_cast<double> (lDemand);
      lResult += (lDoubleDemand - iDemandMean) * (lDoubleDemand - iDemandMean);
    }

    lResult /= (lSize - 1);

    lResult = std::sqrt (lResult);

    return lResult;
  }

  // ////////////////////////////////////////////////////////////////////
  const std::vector<bool> HistoricalBookingHolder::
  getListOfToBeUnconstrainedFlags () const {
    std::vector<bool> lResult;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking& lHistorialBooking =
        _historicalBookingVector.at(ite);
      const stdair::Flag_T lFlag = lHistorialBooking.getFlag ();
      if (lFlag == true) {
        lResult.push_back(true);
      }
      else {
        lResult.push_back(false);
      }
    }

    return lResult;
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::NbOfBookings_T& HistoricalBookingHolder::
  getHistoricalBooking (const short i) const {
    const HistoricalBooking& lHistorialBooking =
      _historicalBookingVector.at(i);
    return lHistorialBooking.getNbOfBookings();
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::NbOfBookings_T& HistoricalBookingHolder::
  getUnconstrainedDemand (const short i) const {
    const HistoricalBooking& lHistorialBooking =
      _historicalBookingVector.at(i);
    return lHistorialBooking.getUnconstrainedDemand();
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::Flag_T& HistoricalBookingHolder::
  getCensorshipFlag (const short i) const {
    const HistoricalBooking& lHistorialBooking =
      _historicalBookingVector.at(i);
    return lHistorialBooking.getFlag();
  }

  // ////////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::setUnconstrainedDemand
  (const stdair::NbOfBookings_T& iExpectedDemand, const short i) {
    _historicalBookingVector.at(i).setUnconstrainedDemand(iExpectedDemand);
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::NbOfBookings_T HistoricalBookingHolder::calculateExpectedDemand
  (const double iMean, const double iSD,
   const short i, const stdair::NbOfBookings_T iDemand) const {

    const HistoricalBooking lHistorialBooking =
      _historicalBookingVector.at(i);
    const double lBooking =
      static_cast <double> (lHistorialBooking.getNbOfBookings());
    double e, d1, d2;
    
    e = - (lBooking - iMean) * (lBooking - iMean) * 0.625 / (iSD * iSD);
    //STDAIR_LOG_DEBUG ("e: " << e);
    e = exp (e);
    //STDAIR_LOG_DEBUG ("e: " << e);

    double s = std::sqrt (1 - e);
    //STDAIR_LOG_DEBUG ("s: " << s);
    
    if (lBooking >= iMean) {
      if (e < 0.01) {
        return iDemand;
      }
      d1 = 0.5 * (1 - s);
    }
    else {
      d1 = 0.5 * (1 + s);
    }
    //STDAIR_LOG_DEBUG ("d1: " << d1);
    
    e = - (lBooking - iMean) * (lBooking - iMean) * 0.5 / (iSD * iSD);
    e = exp (e);
    d2 = e * iSD / std::sqrt(2 * 3.14159265);
    //STDAIR_LOG_DEBUG ("d2: " << d2);
    
    if (d1 == 0) {
      return iDemand;
    }
      
    const stdair::NbOfBookings_T lDemand =
      static_cast<stdair::NbOfBookings_T> (iMean + d2/d1);
      
    return lDemand;
  }

  // ////////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::addHistoricalBooking
  (const HistoricalBooking& iHistoricalBooking) {
    _historicalBookingVector.push_back(iHistoricalBooking);
  }

  // ////////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::toStream (std::ostream& ioOut) const {
    const short lSize = _historicalBookingVector.size();

    ioOut << "Historical Booking; Unconstrained Demand; Flag" << std::endl;

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking& lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const stdair::NbOfBookings_T& lBooking =
        lHistorialBooking.getNbOfBookings();
        
      const stdair::NbOfBookings_T& lDemand =
        lHistorialBooking.getUnconstrainedDemand();
        
      const stdair::Flag_T lFlag = lHistorialBooking.getFlag();

      ioOut << lBooking << "    "
            << lDemand << "    "
            << lFlag << std::endl;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string HistoricalBookingHolder::describe() const {
    std::ostringstream ostr;
    ostr << "Holder of HistoricalBooking structs.";
     
    return ostr.str();
  }
    
  // ////////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::display() const {
    toStream (std::cout);
  }
}
