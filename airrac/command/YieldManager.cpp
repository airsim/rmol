// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/TravelSolutionStruct.hpp>
#include <stdair/bom/AirportPair.hpp>
#include <stdair/bom/PosChannel.hpp>
#include <stdair/bom/DatePeriod.hpp>
#include <stdair/bom/TimePeriod.hpp>
#include <stdair/bom/YieldFeatures.hpp>
#include <stdair/bom/AirlineClassList.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
// Airrac
#include <airrac/AIRRAC_Types.hpp>
#include <airrac/command/YieldManager.hpp>

namespace AIRRAC {

  // ////////////////////////////////////////////////////////////////////
  YieldManager::YieldManager() {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  YieldManager::YieldManager (const YieldManager&) {
    assert (false);
  }

  // ////////////////////////////////////////////////////////////////////
  YieldManager::~YieldManager() {
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldManager::
  calculateYield (stdair::TravelSolutionList_T& ioTravelSolutionList,
                  const stdair::BomRoot& iBomRoot) {

    // Browse the list of TravelSolution structures
    for (stdair::TravelSolutionList_T::iterator itTravelSolution =
           ioTravelSolutionList.begin();
         itTravelSolution != ioTravelSolutionList.end(); ++itTravelSolution) {
      stdair::TravelSolutionStruct& lTravelSolution = *itTravelSolution;
      
      //
      YieldManager::calculateYield (lTravelSolution, iBomRoot);
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldManager::
  calculateYield (stdair::TravelSolutionStruct& ioTravelSolution,
                  const stdair::BomRoot& iBomRoot) {

    // Calculate/retrieve the yield for the given travel solution
    //YieldStore::calculateYield (ioYield, ioTravelSolution);

    // TODO: update the statistical attributes of the yield.
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldManager::updateYields (const stdair::BomRoot& iBomRoot) {
    // Browse the list of booking classes and update yield for each one.
    const stdair::InventoryList_T lInvList =
      stdair::BomManager::getList<stdair::Inventory> (iBomRoot);
    for (stdair::InventoryList_T::const_iterator itInv = lInvList.begin();
         itInv != lInvList.end(); ++itInv) {
      const stdair::Inventory* lInv_ptr = *itInv;
      assert (lInv_ptr != NULL);

      // Retrieve the airline code.
      const stdair::AirlineCode_T& lAirlineCode = lInv_ptr->getAirlineCode();

      //
      const stdair::FlightDateList_T& lFDList =
        stdair::BomManager::getList<stdair::FlightDate> (*lInv_ptr);
      for (stdair::FlightDateList_T::const_iterator itFD = lFDList.begin();
           itFD != lFDList.end(); ++itFD) {
        const stdair::FlightDate* lFD_ptr = *itFD;
        assert (lFD_ptr != NULL);

        //
        const stdair::SegmentDateList_T& lSDList =
          stdair::BomManager::getList<stdair::SegmentDate> (*lFD_ptr);
        for (stdair::SegmentDateList_T::const_iterator itSD = lSDList.begin();
             itSD != lSDList.end(); ++itSD) {
          const stdair::SegmentDate* lSD_ptr = *itSD;
          assert (lSD_ptr != NULL);

          // Retrieve the origin and the destination
          const stdair::AirportCode_T& lOrigin = lSD_ptr->getBoardingPoint();
          const stdair::AirportCode_T& lDestination = lSD_ptr->getOffPoint();

          // Retrieve the airport pair in the yield structure.
          const stdair::AirportPairKey lAirportPairKey (lOrigin, lDestination);
          stdair::AirportPair* lAirportPair_ptr = stdair::BomManager::
            getObjectPtr<stdair::AirportPair> (iBomRoot,
                                               lAirportPairKey.toString());
          if (lAirportPair_ptr == NULL) {
            STDAIR_LOG_ERROR ("Cannot find yield corresponding to the airport "
                              << "pair: " << lAirportPairKey.toString());
            assert (false);
          }

          // Retrieve the boarding date and time
          const stdair::Date_T& lDate = lSD_ptr->getBoardingDate();
          const stdair::Duration_T& lTime = lSD_ptr->getBoardingTime();

          // Retrieve the corresponding date period.
          const stdair::DatePeriodList_T& lDatePeriodList =
            stdair::BomManager::getList<stdair::DatePeriod> (*lAirportPair_ptr);
          for (stdair::DatePeriodList_T::const_iterator itDatePeriod =
                 lDatePeriodList.begin();
               itDatePeriod != lDatePeriodList.end(); ++itDatePeriod) {
            const stdair::DatePeriod* lDatePeriod_ptr = *itDatePeriod;
            assert (lDatePeriod_ptr != NULL);

            const bool isDepartureDateValid =
              lDatePeriod_ptr->isDepartureDateValid (lDate);

            if (isDepartureDateValid == true) {

              // Retrieve the PoS-Channel.
              const stdair::PosChannelKey lPosChannelKey (stdair::DEFAULT_POS,
                                                          stdair::DEFAULT_CHANNEL);
              stdair::PosChannel* lPosChannel_ptr = stdair::BomManager::
                getObjectPtr<stdair::PosChannel> (*lDatePeriod_ptr,
                                                  lPosChannelKey.toString());
              if (lPosChannel_ptr == NULL) {
                STDAIR_LOG_ERROR ("Cannot find yield corresponding to the PoS-"
                                  << "Channel: " << lPosChannelKey.toString());
                assert (false);
              }
              
              // Retrieve the corresponding time period.
              const stdair::TimePeriodList_T& lTimePeriodList = stdair::
                BomManager::getList<stdair::TimePeriod> (*lDatePeriod_ptr);
              for (stdair::TimePeriodList_T::const_iterator itTimePeriod =
                     lTimePeriodList.begin();
                   itTimePeriod != lTimePeriodList.end(); ++itTimePeriod) {
                const stdair::TimePeriod* lTimePeriod_ptr = *itTimePeriod;
                assert (lTimePeriod_ptr != NULL);

                const bool isDepartureTimeValid =
                  lTimePeriod_ptr->isDepartureTimeValid (lTime);

                if (isDepartureTimeValid == true) {
                  updateYields (*lSD_ptr, *lTimePeriod_ptr, lAirlineCode);
                }
              }
            }
          }
        }
      }
    }
  }

  // ////////////////////////////////////////////////////////////////////
  void YieldManager::updateYields (const stdair::SegmentDate& iSegmentDate,
                                   const stdair::TimePeriod& iTimePeriod,
                                   const stdair::AirlineCode_T& iAirlineCode) {
    // Browse the segment-cabin list and retrieve the corresponding
    // yield features.
    const stdair::SegmentCabinList_T& lSegmentCabinList =
      stdair::BomManager::getList<stdair::SegmentCabin> (iSegmentDate);
    for (stdair::SegmentCabinList_T::const_iterator itSC =
           lSegmentCabinList.begin(); itSC != lSegmentCabinList.end(); ++itSC) {
      const stdair::SegmentCabin* lSegmentCabin_ptr = *itSC;
      assert (lSegmentCabin_ptr != NULL);

      const stdair::CabinCode_T& lCabinCode = lSegmentCabin_ptr->getCabinCode();
      const stdair::YieldFeatures* lYieldFeatures_ptr = stdair::BomManager::
        getObjectPtr<stdair::YieldFeatures> (iTimePeriod, lCabinCode);
      if (lYieldFeatures_ptr == NULL) {
        STDAIR_LOG_ERROR ("Cannot find the yield features corresponding to "
                          << iTimePeriod.describeKey() << ", " << lCabinCode);
        assert (false);
      }

      // Browse the list of booking class and update the yield for each one.
      const stdair::FareFamilyList_T& lFFlist = stdair::BomManager::
        getList<stdair::FareFamily> (*lSegmentCabin_ptr);
      for (stdair::FareFamilyList_T::const_iterator itFF = lFFlist.begin();
           itFF != lFFlist.end(); ++itFF) {
        const stdair::FareFamily* lFF_ptr = *itFF;
        assert (lFF_ptr != NULL);

        const stdair::BookingClassList_T& lBCList = stdair::BomManager::
          getList<stdair::BookingClass> (*lFF_ptr);
        for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
             itBC != lBCList.end(); ++itBC) {
          stdair::BookingClass* lBookingClass_ptr = *itBC;
          assert (lBookingClass_ptr != NULL);

          const stdair::ClassCode_T& lClassCode =
            lBookingClass_ptr->getClassCode();
          stdair::AirlineCodeList_T lAirlineCodeList;
          lAirlineCodeList.push_back (iAirlineCode);
          stdair::ClassList_StringList_T lClassList;
          lClassList.push_back (lClassCode);
          const stdair::AirlineClassListKey lACListKey (lAirlineCodeList,
                                                        lClassList);

          const stdair::AirlineClassList* lAirlineClassList_ptr = stdair::
            BomManager::getObjectPtr<stdair::AirlineClassList> (*lYieldFeatures_ptr, lACListKey.toString());
          if (lAirlineClassList_ptr != NULL) {
            const stdair::Yield_T& lYield = lAirlineClassList_ptr->getYield();
            lBookingClass_ptr->setYield (lYield);

            //DEBUG
            STDAIR_LOG_DEBUG ("Update yield of " << lYield << " for "
                              << iAirlineCode << ", "
                              << iSegmentDate.describeKey() << ", "
                              << lBookingClass_ptr->describeKey());
          }
        }
      }
    }
  }
}
