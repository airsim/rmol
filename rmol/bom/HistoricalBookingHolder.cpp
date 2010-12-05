// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
#include <iomanip>
#include <cmath>
// Boost Math
#include <boost/math/distributions/normal.hpp>
// RMOL
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////
  HistoricalBookingHolder::HistoricalBookingHolder () {
  }

  // //////////////////////////////////////////////////////////////////
  HistoricalBookingHolder::~HistoricalBookingHolder () {
    _historicalBookingVector.clear();
  }

  // //////////////////////////////////////////////////////////////////
  const short HistoricalBookingHolder::getNumberOfFlights () const {
    return _historicalBookingVector.size();
  }

  // //////////////////////////////////////////////////////////////////
  const short HistoricalBookingHolder::getNumberOfUncensoredData () const {
    short lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const bool lFlag = _historicalBookingVector.at(ite).getFlag ();
      if (lFlag == false) {
        ++ lResult;
      }
    }

    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::
  getNumberOfUncensoredBookings () const {
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking lHistorialBooking =
        _historicalBookingVector.at(ite);
      const bool lFlag = lHistorialBooking.getFlag ();
      if (lFlag == false) {
        const double lBooking = 
          lHistorialBooking.getNumberOfBookings ();
        lResult += lBooking;
      }
    }

    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getUncensoredStandardDeviation
  (const double iMeanOfUncensoredBookings, const short iNumberOfUncensoredData)
    const {
      
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const bool lFlag = _historicalBookingVector.at(ite).getFlag ();
      if (lFlag == false) {
        const HistoricalBooking lHistorialBooking =
          _historicalBookingVector.at(ite);
          
        const double lBooking =
          lHistorialBooking.getNumberOfBookings ();
          
        lResult += (lBooking - iMeanOfUncensoredBookings)
          * (lBooking - iMeanOfUncensoredBookings);
      }
    }
    lResult /= (iNumberOfUncensoredData - 1);
    lResult = sqrt (lResult);
      
    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getMeanDemand () const {
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const double lDemand =
        lHistorialBooking.getUnconstrainedDemand ();
        
      lResult += static_cast<double>(lDemand);
    }

    lResult /= lSize;

    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getStandardDeviation
  (const double iMeanDemand) const {
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const double lDemand =
        lHistorialBooking.getUnconstrainedDemand ();
        
      const double lDoubleDemand = static_cast<double> (lDemand);
      lResult += (lDoubleDemand - iMeanDemand) * (lDoubleDemand - iMeanDemand);
    }

    lResult /= (lSize - 1);

    lResult = sqrt (lResult);

    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  const std::vector<bool> HistoricalBookingHolder::
  getListOfToBeUnconstrainedFlags () const {
    std::vector<bool> lResult;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking lHistorialBooking =
        _historicalBookingVector.at(ite);
      const bool lFlag = lHistorialBooking.getFlag ();
      if (lFlag == true) {
        lResult.push_back(true);
      }
      else {
        lResult.push_back(false);
      }
    }

    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::
  getHistoricalBooking (const short i) const {
    const HistoricalBooking lHistorialBooking =
      _historicalBookingVector.at(i);
    double lResult = lHistorialBooking.getNumberOfBookings();
    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::
  getUnconstrainedDemand (const short i) const {
    const HistoricalBooking lHistorialBooking =
      _historicalBookingVector.at(i);
    double lResult = lHistorialBooking.getUnconstrainedDemand();
    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::setUnconstrainedDemand
  (const double iExpectedDemand, const short i) {
    _historicalBookingVector.at(i).setUnconstrainedDemand(iExpectedDemand);
  }

  // //////////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::calculateExpectedDemand
  (const double iMean, const double iSD,
   const short i, const double iDemand) const {

    const HistoricalBooking lHistorialBooking =
      _historicalBookingVector.at(i);
    const double lBooking = static_cast <double>
      (lHistorialBooking.getNumberOfBookings());
    double e, d1, d2;
    /*
      e = - (lBooking - iMean) * (lBooking - iMean) * 0.625 / (iSD * iSD);
      e = exp (e);

      // Prevent e to be too close to 0: that can cause d1 = 0.
      //if (e < 0.01) {
      //  return iDemand;
      //}

      double s = sqrt (1 - e);
      
      if (lBooking >= iMean) {
      d1 = 0.5 * (1 - s);
      }
      else {
      d1 = 0.5 * (1 + s);
      }
    */

    //
    boost::math::normal lNormalDistribution (iMean, iSD);
    d1 = boost::math::cdf (boost::math::complement (lBooking, _capacity));
      
    e = - (lBooking - iMean) * (lBooking - iMean) * 0.5 / (iSD * iSD);
    e = exp (e);

    d2 = e * iSD / sqrt (2 * 3.14159265);
      
    // std::cout << "d1, d2 = " << d1 << "     " << d2 << std::endl;

    if (d1 == 0) {
      return iDemand;
    }
      
    const double lDemand =
      static_cast<double> (iMean + d2/d1);
      
    return lDemand;
  }

  // //////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::addHistoricalBooking
  (const HistoricalBooking iHistoricalBooking) {
    _historicalBookingVector.push_back(iHistoricalBooking);
  }

  // //////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::toStream (std::ostream& ioOut) const {
    const short lSize = _historicalBookingVector.size();

    ioOut << "Historical Booking; Unconstrained Demand; Flag" << std::endl;

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalBooking lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const double lBooking =
        lHistorialBooking.getNumberOfBookings();
        
      const double lDemand =
        lHistorialBooking.getUnconstrainedDemand();
        
      const bool lFlag = lHistorialBooking.getFlag();

      ioOut << lBooking << "    "
            << lDemand << "    "
            << lFlag << std::endl;
    }
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string HistoricalBookingHolder::describe() const {
    std::ostringstream ostr;
    ostr << "Holder of HistoricalBooking structs.";
     
    return ostr.str();
  }
    
  // //////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::display() const {
    toStream (std::cout);
  }
    
}
