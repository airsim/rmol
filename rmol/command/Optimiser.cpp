// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/basic/BasConst_General.hpp>
#include <rmol/bom/MCOptimiser.hpp>
#include <rmol/bom/Emsr.hpp>
#include <rmol/bom/DPOptimiser.hpp>
#include <rmol/command/Optimiser.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::
  optimalOptimisationByMCIntegration (const stdair::NbOfSamples_T& K,
                                      stdair::LegCabin& ioLegCabin) {
    // Retrieve the segment-cabin
    const stdair::SegmentCabinList_T lSegmentCabinList =
      stdair::BomManager::getList<stdair::SegmentCabin> (ioLegCabin);
    stdair::SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
    assert (itSC != lSegmentCabinList.end());
    const stdair::SegmentCabin* lSegmentCabin_ptr = *itSC;
    assert (lSegmentCabin_ptr != NULL);
    
    // Retrieve the class list.
    const stdair::BookingClassList_T lBookingClassList =
      stdair::BomManager::getList<stdair::BookingClass> (*lSegmentCabin_ptr);
    stdair::RandomGeneration lSeedGenerator (stdair::DEFAULT_RANDOM_SEED);

    // Generate the demand samples for the booking classes.
    for (stdair::BookingClassList_T::const_iterator itBC =
           lBookingClassList.begin(); itBC != lBookingClassList.end(); ++itBC) {
      stdair::RandomSeed_T lRandomSeed =
        lSeedGenerator.generateUniform01 () * 1e9;
      stdair::BookingClass* lBookingClass_ptr = *itBC;
      assert (lBookingClass_ptr != NULL);
      lBookingClass_ptr->generateDemandSamples (K, lRandomSeed);

      // DEBUG
      //STDAIR_LOG_DEBUG ("Generating " << K << " demand samples for the class "
      //                   << lBookingClass_ptr->describeKey());
    }   
    
    // Call the class performing the actual algorithm
    MCOptimiser::optimalOptimisationByMCIntegration (ioLegCabin);
  }

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::optimalOptimisationByDP (stdair::LegCabin& ioLegCabin) {
    DPOptimiser::optimalOptimisationByDP (ioLegCabin);
  }

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::heuristicOptimisationByEmsr (stdair::LegCabin& ioLegCabin) {
    Emsr::heuristicOptimisationByEmsr (ioLegCabin);
  }

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::heuristicOptimisationByEmsrA (stdair::LegCabin& ioLegCabin) {
    Emsr::heuristicOptimisationByEmsrA (ioLegCabin);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void Optimiser::heuristicOptimisationByEmsrB (stdair::LegCabin& ioLegCabin) {
    Emsr::heuristicOptimisationByEmsrB (ioLegCabin);
  }

  // ////////////////////////////////////////////////////////////////////
  bool Optimiser::optimise (stdair::FlightDate& ioFlightDate,
                            const stdair::OptimisationMethod& iOptimisationMethod) {
    bool optimiseSucceeded = false;
    // Browse the leg-cabin list and build the virtual class list for
    // each cabin.
    const stdair::LegDateList_T& lLDList =
      stdair::BomManager::getList<stdair::LegDate> (ioFlightDate);
    for (stdair::LegDateList_T::const_iterator itLD = lLDList.begin();
         itLD != lLDList.end(); ++itLD) {
      stdair::LegDate* lLD_ptr = *itLD;
      assert (lLD_ptr != NULL);
      const bool isSucceeded = optimise(*lLD_ptr, iOptimisationMethod);
      // If at least one leg date is optimised, the optimisation is succeeded.
      if (isSucceeded == true) {
        optimiseSucceeded = true;
        // Do not return now because all leg dates need to be optimised.
      }
    }
    return optimiseSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  bool Optimiser::
  optimise (stdair::LegDate& ioLegDate,
            const stdair::OptimisationMethod& iOptimisationMethod) {
    bool optimiseSucceeded = false;
    // Browse the leg-cabin list 
    const stdair::LegCabinList_T& lLCList =
      stdair::BomManager::getList<stdair::LegCabin> (ioLegDate);
    for (stdair::LegCabinList_T::const_iterator itLC = lLCList.begin();
         itLC != lLCList.end(); ++itLC) {
      stdair::LegCabin* lLC_ptr = *itLC;
      assert (lLC_ptr != NULL);
      const bool isSucceeded = optimise(*lLC_ptr, iOptimisationMethod);
      // If at least one leg cabin is optimised, the optimisation is succeeded.
      if (isSucceeded == true) {
        optimiseSucceeded = true;
        // Do not return now because all leg cabins need to be optimised.
      }
    }
    return optimiseSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  bool Optimiser::
  optimise (stdair::LegCabin& ioLegCabin,
            const stdair::OptimisationMethod& iOptimisationMethod) {
    bool optimiseSucceeded = false;
    //
    // Build the virtual class list.
    bool hasVirtualClass = 
      buildVirtualClassListForLegBasedOptimisation (ioLegCabin);
    if (hasVirtualClass == true) {
      switch (iOptimisationMethod.getMethod()) {
      case stdair::OptimisationMethod::LEG_BASED_MC: {
        // Number of samples generated for the Monte Carlo integration.
        // It is important that number is greater than 100 (=10000 here).
        const stdair::NbOfSamples_T lNbOfSamples =
          DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION;
        optimalOptimisationByMCIntegration (lNbOfSamples, ioLegCabin);
        optimiseSucceeded = true;
        break;
      }
      case stdair::OptimisationMethod::LEG_BASED_EMSR_B: {
        heuristicOptimisationByEmsrB (ioLegCabin);
        optimiseSucceeded = true;
        break;
      }
      default: {
        assert (false);
          break;
      }
      }
    }
  
    return optimiseSucceeded;
  }

  // ////////////////////////////////////////////////////////////////////
  bool Optimiser::
  buildVirtualClassListForLegBasedOptimisation (stdair::LegCabin& ioLegCabin) {
    // The map holding all virtual classes to be created.
    stdair::VirtualClassMap_T lVirtualClassMap;
    bool isNotEmpty = false;

    // Retrieve the segment-cabin
    const stdair::SegmentCabinList_T& lSegmentCabinList =
      stdair::BomManager::getList<stdair::SegmentCabin> (ioLegCabin);
    stdair::SegmentCabinList_T::const_iterator itSC = lSegmentCabinList.begin();
    assert (itSC != lSegmentCabinList.end());
    const stdair::SegmentCabin* lSegmentCabin_ptr = *itSC;
    assert (lSegmentCabin_ptr != NULL);
    
    // Retrieve the class list.
    const stdair::BookingClassList_T lBookingClassList =
      stdair::BomManager::getList<stdair::BookingClass> (*lSegmentCabin_ptr);

    // Generate the demand samples for the booking classes.
    for (stdair::BookingClassList_T::const_iterator itBC =
           lBookingClassList.begin(); itBC != lBookingClassList.end(); ++itBC) {
      stdair::BookingClass* lBookingClass_ptr = *itBC;
      assert (lBookingClass_ptr != NULL);

      // If the demand forecast of the class is zero, there no need to create
      // a virtual class.
      // TODO: use float utils
      const stdair::NbOfRequests_T& lMean = lBookingClass_ptr->getMean();
      const stdair::StdDevValue_T& lStdDev = lBookingClass_ptr->getStdDev();
      if (lMean > 0.0) {
        const stdair::Yield_T& lYield = lBookingClass_ptr->getAdjustedYield();
        // TODO: use float utils
        assert (lYield >= 0.0);
        const stdair::Yield_T lRoundedYieldDouble = std::floor(lYield +0.5);
        const stdair::YieldLevel_T lRoundedYieldLevel = 
          static_cast<stdair::YieldLevel_T>(lRoundedYieldDouble);
        if (lRoundedYieldLevel > 0) {
          // If there is already a virtual class with this yield, add the current
          // booking class to its list and sum the two demand distributions.
          // Otherwise, create a new virtual class.
          stdair::VirtualClassMap_T::iterator itVCMap = 
            lVirtualClassMap.find(lRoundedYieldLevel);
          if (itVCMap == lVirtualClassMap.end()) {
            stdair::BookingClassList_T lBookingClassList;
            lBookingClassList.push_back(lBookingClass_ptr);
            stdair::VirtualClassStruct lVirtualClass (lBookingClassList);
            lVirtualClass.setYield (lRoundedYieldLevel);
            lVirtualClass.setMean (lMean);
            lVirtualClass.setStdDev (lStdDev);

            lVirtualClassMap.insert (stdair::VirtualClassMap_T::
                                  value_type (lRoundedYieldLevel, lVirtualClass));
          } else {
            stdair::VirtualClassStruct& lVirtualClass = itVCMap->second;
            const stdair::MeanValue_T& lVCMean = lVirtualClass.getMean();
            const stdair::StdDevValue_T& lVCStdDev = lVirtualClass.getStdDev();
            const stdair::MeanValue_T lNewMean = lVCMean + lMean;
            const stdair::StdDevValue_T lNewStdDev = 
              std::sqrt(lVCStdDev * lVCStdDev + lStdDev * lStdDev);
            lVirtualClass.setMean (lNewMean);
            lVirtualClass.setStdDev (lNewStdDev);

            lVirtualClass.addBookingClass(*lBookingClass_ptr);
          }
        }
      }
    }

    // Browse the virtual class map from high to low yield.
    ioLegCabin.emptyVirtualClassList();
    for (stdair::VirtualClassMap_T::reverse_iterator itVC =
           lVirtualClassMap.rbegin(); itVC != lVirtualClassMap.rend(); ++itVC) {
      stdair::VirtualClassStruct& lVC = itVC->second;
      
      ioLegCabin.addVirtualClass (lVC);
      if (isNotEmpty == false) {
        isNotEmpty = true;
      }
    }
    return isNotEmpty;
  }
  
  // ////////////////////////////////////////////////////////////////////
  double Optimiser::
  optimiseUsingOnDForecast (stdair::FlightDate& ioFlightDate,
                            const bool& iReduceFluctuations) {
    double lMaxBPVariation = 0.0;
    // Check if the flight date holds a list of leg dates.
    // If so, retieve it and optimise the cabins.
    const bool hasLegDateList =
      stdair::BomManager::hasList<stdair::LegDate> (ioFlightDate);
    if (hasLegDateList == true) {
      STDAIR_LOG_DEBUG ("Optimisation for the flight date: "
                        << ioFlightDate.toString());
      const stdair::LegDateList_T& lLDList =
        stdair::BomManager::getList<stdair::LegDate> (ioFlightDate);
      for (stdair::LegDateList_T::const_iterator itLD = lLDList.begin();
           itLD != lLDList.end(); ++itLD) {
        stdair::LegDate* lLD_ptr = *itLD;
        assert (lLD_ptr != NULL);

        //
        const stdair::LegCabinList_T& lLCList =
          stdair::BomManager::getList<stdair::LegCabin> (*lLD_ptr);
        for (stdair::LegCabinList_T::const_iterator itLC = lLCList.begin();
             itLC != lLCList.end(); ++itLC) {
          stdair::LegCabin* lLC_ptr = *itLC;
          assert (lLC_ptr != NULL);
          MCOptimiser::optimisationByMCIntegration (*lLC_ptr);
          const stdair::BidPrice_T& lCurrentBidPrice =
            lLC_ptr->getCurrentBidPrice();
          const stdair::BidPrice_T& lPreviousBidPrice =
            lLC_ptr->getPreviousBidPrice();
          assert (lPreviousBidPrice != 0);
          const double lBPVariation =
            std::abs((lCurrentBidPrice - lPreviousBidPrice)/lPreviousBidPrice);
          lMaxBPVariation = std::max(lMaxBPVariation, lBPVariation);
        }
      }
    }
    return lMaxBPVariation;
  }

}
