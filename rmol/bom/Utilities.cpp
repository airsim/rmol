
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
// StdAir
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/bom/Utilities.hpp>
#include <rmol/bom/SegmentSnapshotTableHelper.hpp>
#include <rmol/basic/BasConst_Curves.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  void Utilities::
  computeDistributionParameters (const stdair::UncDemVector_T& iVector,
                                 double& ioMean, double& ioStdDev) {
    ioMean = 0.0; ioStdDev = 0.0;
    unsigned int lNbOfSamples = iVector.size();
    assert (lNbOfSamples > 1);

    // Compute the mean
    for (stdair::UncDemVector_T::const_iterator itSample = iVector.begin();
         itSample != iVector.end(); ++itSample) {
      //STDAIR_LOG_NOTIFICATION (*itSample);
      ioMean += *itSample;
    }
    ioMean /= lNbOfSamples;

    // Compute the standard deviation
    for (stdair::UncDemVector_T::const_iterator itSample = iVector.begin();
         itSample != iVector.end(); ++itSample) {
      const double& lSample = *itSample;
      ioStdDev += ((lSample - ioMean) * (lSample - ioMean));
    }
    ioStdDev /= (lNbOfSamples - 1);
    ioStdDev = sqrt (ioStdDev);

    // Sanity check
    if (ioStdDev == 0) {
      ioStdDev = 0.1;
    }
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::DCPList_T Utilities::
  buildRemainingDCPList (const stdair::DTD_T& iDTD) {
    stdair::DCPList_T oDCPList;

    const stdair::DCPList_T lWholeDCPList = stdair::DEFAULT_DCP_LIST;
    stdair::DCPList_T::const_iterator itDCP = lWholeDCPList.begin();
    while (itDCP != lWholeDCPList.end()) {
      const stdair::DCP_T& lDCP = *itDCP;
      if (iDTD >= lDCP) {
        break;
      }
      ++itDCP;
    }
    assert (itDCP != lWholeDCPList.end());

    oDCPList.push_back (iDTD);
    ++itDCP;
    for (; itDCP != lWholeDCPList.end(); ++itDCP) {
      oDCPList.push_back (*itDCP);
    }
    
    return oDCPList;
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::DCPList_T Utilities::
  buildPastDCPList (const stdair::DTD_T& iDTD) {
    stdair::DCPList_T oDCPList;

    const stdair::DCPList_T lWholeDCPList = stdair::DEFAULT_DCP_LIST;
    stdair::DCPList_T::const_iterator itDCP = lWholeDCPList.begin();
    while (itDCP != lWholeDCPList.end()) {
      const stdair::DCP_T& lDCP = *itDCP;
      if (iDTD <= lDCP) {
        oDCPList.push_back (lDCP);
        ++itDCP;
      } else {
        break;
      }
    }
    
    return oDCPList;
  }
  
  // ////////////////////////////////////////////////////////////////////
  stdair::NbOfSegments_T Utilities::
  getNbOfDepartedSimilarSegments (const stdair::SegmentCabin& iSegmentCabin,
                                  const stdair::Date_T& iEventDate) {
    stdair::DTD_T lDTD = 0;
    // Retrieve the guillotine block.
    const stdair::SegmentSnapshotTable& lSegmentSnapshotTable =
      iSegmentCabin.getSegmentSnapshotTable();
    return SegmentSnapshotTableHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lSegmentSnapshotTable, lDTD, iEventDate);
  }
  
// ////////////////////////////////////////////////////////////////////
  const BookingClassMeanStdDevPairMap_T Utilities::
  createBookingClassMeanStdDevPairMap(
    const stdair::FareFamilyList_T& iFareFamilyList,
    const bool isCumulated) {
    BookingClassMeanStdDevPairMap_T lBCMSDMap;
    stdair::FareFamilyList_T::const_iterator itFF = iFareFamilyList.begin();
    // Browse the fare families
    for (; itFF != iFareFamilyList.end(); ++itFF) {
      // Retrieve the unconstrained demand  
      const stdair::FareFamily* lFF_ptr = *itFF;
      const stdair::MeanStdDevPairVector_T& lFareFamilyDemand = 
        lFF_ptr->getMeanStdDev();
      const unsigned int& lFareFamilyDemandSize = lFareFamilyDemand.size();
      // Retrieve the class list.
      const stdair::BookingClassList_T& lBookingClassList =
        stdair::BomManager::getList<stdair::BookingClass> (*lFF_ptr);

      // Retrieve the PSellUp curve
      const stdair::BookingClassSellUpCurveMap_T& lBCSUCMap = 
        createBookingClassSellUpCurveMap(lBookingClassList, isCumulated);
      stdair::BookingClassList_T::const_iterator itBC = 
        lBookingClassList.begin();
      // Browse the booking class list
      for (; itBC != lBookingClassList.end(); ++itBC) {
        stdair::MeanValue_T lMean = 0.0;
        stdair::StdDevValue_T lStdDev = 0.0;
        stdair::BookingClass* lBC_ptr = *itBC;
        stdair::BookingClassSellUpCurveMap_T::const_iterator itBCSUCMap =
          lBCSUCMap.find(lBC_ptr);
        assert (itBCSUCMap != lBCSUCMap.end());
        const stdair::SellUpCurve_T& lSellUpCurve = itBCSUCMap->second;
        const unsigned int& lSellUpCurveSize = lSellUpCurve.size();      
        if (lSellUpCurveSize != lFareFamilyDemandSize) {
          std::ostringstream ostr;
          ostr << "The Fare Family demand vector size (" 
               << lFareFamilyDemandSize << ") is not the same than "
               << "the sell up curve size (" << lSellUpCurveSize << ").";
          STDAIR_LOG_DEBUG(ostr.str());
          throw FareFamilyDemandVectorSizeException (ostr.str());
        }
        assert(lSellUpCurveSize == lFareFamilyDemandSize);
        // Retrieve the sell up curves and the fare family demand
        for (unsigned int idx = 0; idx < lSellUpCurveSize; ++idx) {
          const double& lPSellUp = lSellUpCurve[idx];
          // Calculate the demand and its standard deviation
          const stdair::MeanStdDevPair_T& lMeanStdDevPair = 
            lFareFamilyDemand[idx];
          stdair::MeanValue_T lDailyDemand = lMeanStdDevPair.first;
          lDailyDemand *= lPSellUp;
          stdair::StdDevValue_T lDailyStdDev = lMeanStdDevPair.second;
          lDailyStdDev *= sqrt(lPSellUp);
          lMean += lDailyDemand;
          lStdDev = sqrt(lStdDev * lStdDev + lDailyStdDev * lDailyStdDev);
        }
        // Insert the demand and its standard deviation in the map
        const stdair::MeanStdDevPair_T lMeanStdDevPair (lMean, lStdDev);
        const bool insertionSucceeded = lBCMSDMap.insert(
          BookingClassMeanStdDevPairMap_T::
          value_type(lBC_ptr, lMeanStdDevPair)).second;
        assert (insertionSucceeded == true);
      }
    }
  return lBCMSDMap;

  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::BookingClassSellUpCurveMap_T Utilities::
  createBookingClassSellUpCurveMap(
    const stdair::BookingClassList_T& iBookingClassList,
    const bool isCumulated) {
    stdair::BookingClassSellUpCurveMap_T lBCSUCMap;
    
    // Retrieve the yield of the cheapest booking class of the fare family
    stdair::BookingClassList_T::const_reverse_iterator ritBC =
         iBookingClassList.rbegin();
    stdair::BookingClass* lCheapestBC_ptr = *ritBC;
    assert (lCheapestBC_ptr != NULL);
    const stdair::Yield_T& lcheapestYield = lCheapestBC_ptr->getYield ();
      
    stdair::BookingClassList_T::const_reverse_iterator ritNextBC = ritBC;
    ++ritNextBC; 
    const stdair::FRAT5Curve_T& lFRAT5Curve = DEFAULT_FRAT5_CURVE;
    stdair::SellUpCurve_T lBasedSellUpCurve (lFRAT5Curve.size(), 1.0);
    for (; ritNextBC != iBookingClassList.rend(); ++ritBC, ++ritNextBC) {
      stdair::BookingClass* lBC_ptr = *ritBC;
      stdair::BookingClass* lNextBC_ptr = *ritNextBC;
    
      // Create a SellUpCurve
      stdair::SellUpCurve_T lSellUpCurve;
      stdair::FRAT5Curve_T::const_reverse_iterator ritFRAT5CURV = 
        lFRAT5Curve.rbegin();
      assert(ritFRAT5CURV != lFRAT5Curve.rend());
      unsigned int idx = 0;
      for (; ritFRAT5CURV != lFRAT5Curve.rend(); ++ritFRAT5CURV, ++idx) {
        const double lFRAT5 = ritFRAT5CURV->second;
        assert(lFRAT5 > 1);
        // Retrieve yield of the next BC to calculate the probability of sell up
        const stdair::Yield_T& lNextYield = lNextBC_ptr->getYield ();
        double lPSUp = 1.0;
        
        // Calculate the probability of sell up
        const double lSellUpConstant = -log(0.5)/(lFRAT5 - 1);
        lPSUp = exp(-(lNextYield/lcheapestYield-1) * lSellUpConstant);
        double& lBasedFactor = lBasedSellUpCurve[idx];
        if (isCumulated == true) {
          lSellUpCurve.push_back(lBasedFactor);
        } else {
          lSellUpCurve.push_back(lBasedFactor - lPSUp);
        }
        
        lBasedFactor = lPSUp;
      }
      // Insert the Sell Up curve in the map
      const bool insertionSucceeded = lBCSUCMap.insert(
        stdair::BookingClassSellUpCurveMap_T::
        value_type(lBC_ptr, lSellUpCurve)).second;
      assert (insertionSucceeded == true);
    }
    // Insert the Sell Up curve of the last booking class in the map
    stdair::BookingClass* lBC_ptr = *ritBC;
    const bool insertionSucceeded = lBCSUCMap.insert(
        stdair::BookingClassSellUpCurveMap_T::
        value_type(lBC_ptr, lBasedSellUpCurve)).second;
      assert (insertionSucceeded == true);

    return lBCSUCMap;
  }

}
