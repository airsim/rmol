// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/AirportPair.hpp>
#include <stdair/bom/PosChannel.hpp>
#include <stdair/bom/DatePeriod.hpp>
#include <stdair/bom/TimePeriod.hpp>
#include <stdair/bom/YieldFeatures.hpp>
#include <stdair/bom/AirlineClassList.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
// AirRAC
#include <airrac/bom/YieldRuleStruct.hpp>
#include <airrac/command/YieldRuleGenerator.hpp>

namespace AIRRAC {

  // //////////////////////////////////////////////////////////////////////
  void YieldRuleGenerator::
  createAirportPair (stdair::BomRoot& ioBomRoot,
                     const YieldRuleStruct& iYieldRuleStruct) {

    // Set the airport-pair primary key.
    const stdair::AirportCode_T& lBoardPoint = iYieldRuleStruct.getOrigin ();
    const stdair::AirportCode_T& lOffPoint = iYieldRuleStruct.getDestination ();
    const stdair::AirportPairKey lAirportPairKey (lBoardPoint, lOffPoint);

    // Check that the airport-pair object is not already existing. If an
    // airport-pair object with the same key has not already been created,
    // create it and link it to the ioBomRoot object.
    stdair::AirportPair* lAirportPair_ptr = stdair::BomManager::
      getObjectPtr<stdair::AirportPair> (ioBomRoot, lAirportPairKey.toString());
    if (lAirportPair_ptr == NULL) {
      lAirportPair_ptr = &stdair::FacBom<stdair::AirportPair>::
        instance().create (lAirportPairKey);
      stdair::FacBomManager::addToListAndMap (ioBomRoot, *lAirportPair_ptr);
      stdair::FacBomManager::linkWithParent (ioBomRoot, *lAirportPair_ptr);
    }
    // Sanity check.
    assert (lAirportPair_ptr != NULL);

    stdair::AirportPair& lAirportPair = *lAirportPair_ptr;
    // Generate the date-period object corresponding to the given
    // yieldRule.  
    createDateRange (lAirportPair, iYieldRuleStruct);
    
  }


  // //////////////////////////////////////////////////////////////////////
  void YieldRuleGenerator::
  createDateRange (stdair::AirportPair& iAirportPair,
                   const YieldRuleStruct& iYieldRuleStruct) {

    // Create the yield date-period primary key.
    const stdair::Date_T& lDateRangeStart = 
      iYieldRuleStruct.getDateRangeStart ();
    const stdair::Date_T& lDateRangeEnd = 
      iYieldRuleStruct.getDateRangeEnd ();
    const stdair::DatePeriod_T lDatePeriod (lDateRangeStart, lDateRangeEnd); 
    const stdair::DatePeriodKey lYieldDatePeriodKey (lDatePeriod);

    // Check that the date-period object is not already existing.
    // If a date-period object with the same key has not already been
    // created, create it and link it to the airport-pair object.
    stdair::DatePeriod* lYieldDatePeriod_ptr = stdair::BomManager::
      getObjectPtr<stdair::DatePeriod> (iAirportPair, 
                                        lYieldDatePeriodKey.toString());
    if (lYieldDatePeriod_ptr == NULL) {
      lYieldDatePeriod_ptr = &stdair::FacBom<stdair::DatePeriod>::
        instance().create (lYieldDatePeriodKey);
      stdair::FacBomManager::
        addToListAndMap (iAirportPair, *lYieldDatePeriod_ptr);
      stdair::FacBomManager::
        linkWithParent (iAirportPair, *lYieldDatePeriod_ptr);
    }
    // Sanity check.
    assert (lYieldDatePeriod_ptr != NULL);

    stdair::DatePeriod& lDateRange = *lYieldDatePeriod_ptr;
    // Generate the point_of_sale-channel object corresponding to
    // the given yieldRule.
    createPOSChannel (lDateRange, iYieldRuleStruct);
    
  }

  // //////////////////////////////////////////////////////////////////////
  void YieldRuleGenerator::
  createPOSChannel (stdair::DatePeriod& iDatePeriod,
                    const YieldRuleStruct& iYieldRuleStruct) {

    // Create the point-of-sale-channel primary key.
    const stdair::CityCode_T& lPoS = iYieldRuleStruct.getPOS ();
    const stdair::ChannelLabel_T& lChannel = iYieldRuleStruct.getChannel ();
    const stdair::PosChannelKey lYieldPosChannelKey (lPoS, lChannel);

    // Check that the point_of_sale-channel object is not already existing.
    // If a point_of_sale-channel object with the same key has not already
    // been created, create it and link it to the date-period object.     
    stdair::PosChannel* lYieldPosChannel_ptr = stdair::BomManager::
      getObjectPtr<stdair::PosChannel> (iDatePeriod,
                                        lYieldPosChannelKey.toString());
    if (lYieldPosChannel_ptr == NULL) {
      lYieldPosChannel_ptr = &stdair::FacBom<stdair::PosChannel>::
        instance().create (lYieldPosChannelKey);
      stdair::FacBomManager::
        addToListAndMap (iDatePeriod, *lYieldPosChannel_ptr);
      stdair::FacBomManager::
        linkWithParent (iDatePeriod, *lYieldPosChannel_ptr);
    }
    // Sanity check.
    assert (lYieldPosChannel_ptr != NULL);

    stdair::PosChannel& lPosChannel = *lYieldPosChannel_ptr;
    // Generate the time-period object corresponding to the given
    // yieldRule.
    createTimeRange (lPosChannel, iYieldRuleStruct);

  }

  // //////////////////////////////////////////////////////////////////////
  void YieldRuleGenerator::
  createTimeRange (stdair::PosChannel& iPosChannel,
                   const YieldRuleStruct& iYieldRuleStruct) {
   
    // Create the yield time-period primary key.
    const stdair::Time_T& lTimeRangeStart
      = iYieldRuleStruct.getTimeRangeStart ();
    const stdair::Time_T& lTimeRangeEnd
      = iYieldRuleStruct.getTimeRangeEnd ();
    const stdair::TimePeriodKey lYieldTimePeriodKey (lTimeRangeStart,
                                                    lTimeRangeEnd);

    // Check that the time-period object is not already existing.
    // If a time-period object with the same key has not already been
    // created, create it and link it to the point_of_sale-channel object.      
    stdair::TimePeriod* lYieldTimePeriod_ptr = stdair::BomManager::
      getObjectPtr<stdair::TimePeriod> (iPosChannel, 
                                        lYieldTimePeriodKey.toString());
    if (lYieldTimePeriod_ptr == NULL) {
      lYieldTimePeriod_ptr = &stdair::FacBom<stdair::TimePeriod>::
        instance().create (lYieldTimePeriodKey);
      stdair::FacBomManager::
        addToListAndMap (iPosChannel, *lYieldTimePeriod_ptr);
      stdair::FacBomManager::
        linkWithParent (iPosChannel, *lYieldTimePeriod_ptr);
    }
    // Sanity check.
    assert (lYieldTimePeriod_ptr != NULL);

    stdair::TimePeriod& lTimeRange = *lYieldTimePeriod_ptr;
    // Generate the yield-features object corresponding to the given
    // yieldRule.
    createYieldFeatures (lTimeRange, iYieldRuleStruct);

  }

  // //////////////////////////////////////////////////////////////////////
  void YieldRuleGenerator::
  createYieldFeatures (stdair::TimePeriod& iTimePeriod,
                      const YieldRuleStruct& iYieldRuleStruct) {
  
    // Create the yield-features primary key.
    const stdair::TripType_T& lTripType = iYieldRuleStruct.getTripType ();
    stdair::CabinCode_T lCabinCode = iYieldRuleStruct.getCabinCode ();
    const stdair::YieldFeaturesKey lYieldFeaturesKey (lTripType, lCabinCode);

    // Check that the yield features object is not already existing.
    // If a yield features object with the same key has not already been
    // created, create it and link it to the time-period object.     
    stdair::YieldFeatures* lYieldFeatures_ptr = stdair::BomManager::
      getObjectPtr<stdair::YieldFeatures > (iTimePeriod,
                                            lYieldFeaturesKey.toString());
    if (lYieldFeatures_ptr == NULL) {
      lYieldFeatures_ptr = &stdair::FacBom<stdair::YieldFeatures>::
        instance().create (lYieldFeaturesKey);
      stdair::FacBomManager::
        addToListAndMap (iTimePeriod, *lYieldFeatures_ptr);
      stdair::FacBomManager::
        linkWithParent (iTimePeriod, *lYieldFeatures_ptr);
    }
    // Sanity check.
    assert (lYieldFeatures_ptr != NULL);

    stdair::YieldFeatures& lYieldFeatures = *lYieldFeatures_ptr;
    // Generate the airline-class list object corresponding to the
    // given yieldRule
    createAirlineClassList (lYieldFeatures, iYieldRuleStruct);

  }

  // //////////////////////////////////////////////////////////////////////
  void YieldRuleGenerator::
  createAirlineClassList (stdair::YieldFeatures& iYieldFeatures,
                          const YieldRuleStruct& iYieldRuleStruct) {

    // Create the AirlineClassList primary key.
    const unsigned int lAirlineListSize =
      iYieldRuleStruct.getAirlineListSize();
    const unsigned int lClassCodeListSize =
      iYieldRuleStruct.getClassCodeListSize();
    assert (lAirlineListSize == lClassCodeListSize);
    const stdair::AirlineClassListKey
      lAirlineClassListKey (iYieldRuleStruct.getAirlineList() ,
                            iYieldRuleStruct.getClassCodeList());
    const stdair::Yield_T& lYield = iYieldRuleStruct.getYield ();

    // Create the airline class list object and link it to the yieldures
    // object.    
    stdair::AirlineClassList* lAirlineClassList_ptr =
      &stdair::FacBom<stdair::AirlineClassList>::instance().
      create(lAirlineClassListKey);
    lAirlineClassList_ptr->setYield (lYield);
    stdair::FacBomManager::addToListAndMap (iYieldFeatures,
                                            *lAirlineClassList_ptr); 
    stdair::FacBomManager::linkWithParent (iYieldFeatures,
                                           *lAirlineClassList_ptr);
  }
        
}

