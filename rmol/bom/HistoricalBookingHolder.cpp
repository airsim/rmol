// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
// GSL Random Number Generation 
// (GSL Reference Manual, version 1.7, Chapter 19)
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_randist.h>
// C
#include <assert.h>
#include <math.h>
// STL
#include <iostream>
#include <iomanip>
#include <cmath>
// RMU
=======
// STL
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
// StdAir
#include <stdair/service/Logger.hpp>
// RMOL
>>>>>>> 0.24
#include <rmol/bom/HistoricalBooking.hpp>
#include <rmol/bom/HistoricalBookingHolder.hpp>

namespace RMOL {

<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////
  HistoricalBookingHolder::HistoricalBookingHolder () {
  }

  // //////////////////////////////////////////////////////////////////
=======
  // ////////////////////////////////////////////////////////////////////
  HistoricalBookingHolder::HistoricalBookingHolder () {
  }

  // ////////////////////////////////////////////////////////////////////
>>>>>>> 0.24
  HistoricalBookingHolder::~HistoricalBookingHolder () {
    _historicalBookingVector.clear();
  }

<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////
  const short HistoricalBookingHolder::getNumberOfFlights () const {
    return _historicalBookingVector.size();
  }

  // //////////////////////////////////////////////////////////////////
  const short HistoricalBookingHolder::getNumberOfUncensoredData () const {
=======
  // ////////////////////////////////////////////////////////////////////
  const short HistoricalBookingHolder::getNbOfFlights () const {
    return _historicalBookingVector.size();
  }

  // ////////////////////////////////////////////////////////////////////
  const short HistoricalBookingHolder::getNbOfUncensoredData () const {
>>>>>>> 0.24
    short lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
<<<<<<< HEAD
      const bool lFlag = _historicalBookingVector.at(ite).getFlag ();
=======
      const stdair::Flag_T lFlag = _historicalBookingVector.at(ite).getFlag ();
>>>>>>> 0.24
      if (lFlag == false) {
        ++ lResult;
      }
    }

    return lResult;
  }

<<<<<<< HEAD
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
=======
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
>>>>>>> 0.24
        lResult += lBooking;
      }
    }

    return lResult;
  }

<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getUncensoredStandardDeviation
  (const double iMeanOfUncensoredBookings, const short iNumberOfUncensoredData)
    const {
=======
  // ////////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::
  getUncensoredStandardDeviation (const double& iMeanOfUncensoredBookings,
                                  const short iNbOfUncensoredData) const {
>>>>>>> 0.24
      
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
<<<<<<< HEAD
      const bool lFlag = _historicalBookingVector.at(ite).getFlag ();
      if (lFlag == false) {
        const HistoricalBooking lHistorialBooking =
          _historicalBookingVector.at(ite);
          
        const double lBooking =
          lHistorialBooking.getNumberOfBookings ();
=======
      const stdair::Flag_T lFlag = _historicalBookingVector.at(ite).getFlag ();
      if (lFlag == false) {
        const HistoricalBooking& lHistorialBooking =
          _historicalBookingVector.at (ite);
          
        const stdair::NbOfBookings_T& lBooking =
          lHistorialBooking.getNbOfBookings ();
>>>>>>> 0.24
          
        lResult += (lBooking - iMeanOfUncensoredBookings)
          * (lBooking - iMeanOfUncensoredBookings);
      }
    }
<<<<<<< HEAD
    lResult /= (iNumberOfUncensoredData - 1);
=======
    lResult /= (iNbOfUncensoredData - 1);
>>>>>>> 0.24
    lResult = sqrt (lResult);
      
    return lResult;
  }

<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getMeanDemand () const {
=======
  // ////////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getDemandMean () const {
>>>>>>> 0.24
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
<<<<<<< HEAD
      const HistoricalBooking lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const double lDemand =
=======
      const HistoricalBooking& lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const stdair::NbOfBookings_T& lDemand =
>>>>>>> 0.24
        lHistorialBooking.getUnconstrainedDemand ();
        
      lResult += static_cast<double>(lDemand);
    }

    lResult /= lSize;

    return lResult;
  }

<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getStandardDeviation
  (const double iMeanDemand) const {
=======
  // ////////////////////////////////////////////////////////////////////
  const double HistoricalBookingHolder::getStandardDeviation
  (const double iDemandMean) const {
>>>>>>> 0.24
    double lResult = 0;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
<<<<<<< HEAD
      const HistoricalBooking lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const double lDemand =
        lHistorialBooking.getUnconstrainedDemand ();
        
      const double lDoubleDemand = static_cast<double> (lDemand);
      lResult += (lDoubleDemand - iMeanDemand) * (lDoubleDemand - iMeanDemand);
=======
      const HistoricalBooking& lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const stdair::NbOfBookings_T& lDemand =
        lHistorialBooking.getUnconstrainedDemand ();
        
      const double lDoubleDemand = static_cast<double> (lDemand);
      lResult += (lDoubleDemand - iDemandMean) * (lDoubleDemand - iDemandMean);
>>>>>>> 0.24
    }

    lResult /= (lSize - 1);

    lResult = sqrt (lResult);

    return lResult;
  }

<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////
=======
  // ////////////////////////////////////////////////////////////////////
>>>>>>> 0.24
  const std::vector<bool> HistoricalBookingHolder::
  getListOfToBeUnconstrainedFlags () const {
    std::vector<bool> lResult;
    const short lSize = _historicalBookingVector.size();

    for (short ite = 0; ite < lSize; ++ite) {
<<<<<<< HEAD
      const HistoricalBooking lHistorialBooking =
        _historicalBookingVector.at(ite);
      const bool lFlag = lHistorialBooking.getFlag ();
=======
      const HistoricalBooking& lHistorialBooking =
        _historicalBookingVector.at(ite);
      const stdair::Flag_T lFlag = lHistorialBooking.getFlag ();
>>>>>>> 0.24
      if (lFlag == true) {
        lResult.push_back(true);
      }
      else {
        lResult.push_back(false);
      }
    }

    return lResult;
  }

<<<<<<< HEAD
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
      
    d1 = gsl_cdf_gaussian_Q (lBooking - iMean, iSD);
      
    e = - (lBooking - iMean) * (lBooking - iMean) * 0.5 / (iSD * iSD);
    e = exp (e);

    d2 = e * iSD / sqrt(2 * 3.14159265);
      
    // std::cout << "d1, d2 = " << d1 << "     " << d2 << std::endl;

=======
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

    double s = sqrt (1 - e);
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
    d2 = e * iSD / sqrt(2 * 3.14159265);
    //STDAIR_LOG_DEBUG ("d2: " << d2);
    
>>>>>>> 0.24
    if (d1 == 0) {
      return iDemand;
    }
      
<<<<<<< HEAD
    const double lDemand =
      static_cast<double> (iMean + d2/d1);
=======
    const stdair::NbOfBookings_T lDemand =
      static_cast<stdair::NbOfBookings_T> (iMean + d2/d1);
>>>>>>> 0.24
      
    return lDemand;
  }

<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::addHistoricalBooking
  (const HistoricalBooking iHistoricalBooking) {
    _historicalBookingVector.push_back(iHistoricalBooking);
  }

  // //////////////////////////////////////////////////////////////////
=======
  // ////////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::addHistoricalBooking
  (const HistoricalBooking& iHistoricalBooking) {
    _historicalBookingVector.push_back(iHistoricalBooking);
  }

  // ////////////////////////////////////////////////////////////////////
>>>>>>> 0.24
  void HistoricalBookingHolder::toStream (std::ostream& ioOut) const {
    const short lSize = _historicalBookingVector.size();

    ioOut << "Historical Booking; Unconstrained Demand; Flag" << std::endl;

    for (short ite = 0; ite < lSize; ++ite) {
<<<<<<< HEAD
      const HistoricalBooking lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const double lBooking =
        lHistorialBooking.getNumberOfBookings();
        
      const double lDemand =
        lHistorialBooking.getUnconstrainedDemand();
        
      const bool lFlag = lHistorialBooking.getFlag();
=======
      const HistoricalBooking& lHistorialBooking =
        _historicalBookingVector.at(ite);
        
      const stdair::NbOfBookings_T& lBooking =
        lHistorialBooking.getNbOfBookings();
        
      const stdair::NbOfBookings_T& lDemand =
        lHistorialBooking.getUnconstrainedDemand();
        
      const stdair::Flag_T lFlag = lHistorialBooking.getFlag();
>>>>>>> 0.24

      ioOut << lBooking << "    "
            << lDemand << "    "
            << lFlag << std::endl;
    }
  }

<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////////
=======
  // ////////////////////////////////////////////////////////////////////
>>>>>>> 0.24
  const std::string HistoricalBookingHolder::describe() const {
    std::ostringstream ostr;
    ostr << "Holder of HistoricalBooking structs.";
     
    return ostr.str();
  }
    
<<<<<<< HEAD
  // //////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::display() const {
    toStream (std::cout);
  }
    
=======
  // ////////////////////////////////////////////////////////////////////
  void HistoricalBookingHolder::display() const {
    toStream (std::cout);
  }
>>>>>>> 0.24
}
