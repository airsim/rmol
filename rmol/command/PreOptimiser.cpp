// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#include <cmath>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentSnapshotTable.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/Utilities.hpp>
#include <rmol/command/PreOptimiser.hpp>
#include <rmol/command/DemandInputPreparation.hpp>
#include <rmol/command/FareAdjustment.hpp>
#include <rmol/command/MarginalRevenueTransformation.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  bool PreOptimiser::
  preOptimise (stdair::FlightDate& ioFlightDate,
               const stdair::PreOptimisationMethod& iPreOptimisationMethod) {
    bool isSucceeded = true;
    const stdair::SegmentDateList_T& lSDList =
      stdair::BomManager::getList<stdair::SegmentDate> (ioFlightDate);
    for (stdair::SegmentDateList_T::const_iterator itSD = lSDList.begin();
         itSD != lSDList.end(); ++itSD) {
      stdair::SegmentDate* lSD_ptr = *itSD;
      assert (lSD_ptr != NULL);

      //
      const stdair::SegmentCabinList_T& lSCList =
        stdair::BomManager::getList<stdair::SegmentCabin> (*lSD_ptr);
      for (stdair::SegmentCabinList_T::const_iterator itSC = lSCList.begin();
           itSC != lSCList.end(); ++itSC) {
        stdair::SegmentCabin* lSC_ptr = *itSC;
        assert (lSC_ptr != NULL);

        //
        // STDAIR_LOG_NOTIFICATION (ioFlightDate.getDepartureDate()
        //                          << ";" << lSegmentDTD);
        bool isPreOptimised = preOptimise (*lSC_ptr, iPreOptimisationMethod);
        if (isPreOptimised == false) {
          isSucceeded = false;
        }
      }
    }

    return isSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  bool PreOptimiser::
  preOptimise (stdair::SegmentCabin& ioSegmentCabin,
               const stdair::PreOptimisationMethod& iPreOptimisationMethod) {
    const stdair::PreOptimisationMethod::EN_PreOptimisationMethod& lPreOptimisationMethod =
      iPreOptimisationMethod.getMethod();
    switch (lPreOptimisationMethod) {
    case stdair::PreOptimisationMethod::NONE: {
      return DemandInputPreparation::prepareDemandInput (ioSegmentCabin);
    }
    case stdair::PreOptimisationMethod::FA: {
      return FareAdjustment::adjustYield (ioSegmentCabin);
    }
    case stdair::PreOptimisationMethod::MRT: {
      if (ioSegmentCabin.getFareFamilyStatus()==false) {
        return FareAdjustment::adjustYield (ioSegmentCabin);
      } else {
        return MarginalRevenueTransformation::
          prepareDemandInput (ioSegmentCabin);
      } 
    }
    default:{
      assert (false);
      break;
    }
    }
    return false;
  }
  
  // ////////////////////////////////////////////////////////////////////
  // void PreOptimiser::
  // setDemandForecastsToZero(const stdair::SegmentCabin& iSegmentCabin) {
  // }
}
