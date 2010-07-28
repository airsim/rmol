// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/field/FldYieldRange.hpp>
#include <rmol/field/FldDistributionParameters.hpp>
#include <rmol/bom/StudyStatManager.hpp>
#include <rmol/bom/BucketHolder.hpp>
//#include <rmol/bom/Resource.hpp>
#include <rmol/bom/MCOptimiser.hpp>
#include <rmol/bom/Emsr.hpp>
#include <rmol/bom/DPOptimiser.hpp>
#include <rmol/factory/FacPartialSumHolder.hpp>
#include <rmol/factory/FacPartialSumHolderHolder.hpp>
#include <rmol/factory/FacDemand.hpp>
#include <rmol/factory/FacBucket.hpp>
#include <rmol/command/Optimiser.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  optimalOptimisationByMCIntegration (const int K, 
                                      const ResourceCapacity_T iCabinCapacity,
                                      BucketHolder& ioBucketHolder,
                                      BidPriceVector_T& ioBidPriceVector) {
    // Retrieve the BucketHolder
    // BucketHolder& ioBucketHolder = ioResource.getBucketHolder();

    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();

    // Create a holder for the list of Partial Sum Lists
    PartialSumHolderHolder& aPartialSumHolderHolder =
      FacPartialSumHolderHolder::instance().create();

    /** 
	Instanciate the list of PartialSumHolder objects.
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    for (short j = 0 ; j <= nbOfClasses; ++j) {
      PartialSumHolder& aPartialSumList = 
	FacPartialSumHolder::instance().create ();

      FacPartialSumHolderHolder::instance().
	addPartialSumHolder (aPartialSumHolderHolder, aPartialSumList);
    }

    // Call the class performing the actual algorithm
    MCOptimiser::optimalOptimisationByMCIntegration (K, iCabinCapacity, 
                                                     ioBucketHolder,
                                                     aPartialSumHolderHolder,
                                                     ioBidPriceVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  optimalOptimisationByMCIntegration (const int K, 
                                      const ResourceCapacity_T iCabinCapacity,
                                      BucketHolder& ioBucketHolder,
                                      BidPriceVector_T& ioBidPriceVector,
                                      StudyStatManager& ioStudyStatManager) {
    stdair::BasChronometer lMCIntegrationBasChrono;
    lMCIntegrationBasChrono.start();
    // Retrieve the BucketHolder
    // BucketHolder& ioBucketHolder = ioResource.getBucketHolder();

    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();

    // Create a holder for the list of Partial Sum Lists
    PartialSumHolderHolder& aPartialSumHolderHolder =
      FacPartialSumHolderHolder::instance().create();

    /** 
	Instanciate the list of PartialSumHolder objects.
        Iterate on the classes/buckets, from 1 to n-1.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    for (short j = 0 ; j <= nbOfClasses; ++j) {
      PartialSumHolder& aPartialSumList = 
	FacPartialSumHolder::instance().create ();

      FacPartialSumHolderHolder::instance().
	addPartialSumHolder (aPartialSumHolderHolder, aPartialSumList);
    }

    // Call the class performing the actual algorithm
    MCOptimiser::optimalOptimisationByMCIntegration (K, iCabinCapacity, 
                                                     ioBucketHolder,
                                                     aPartialSumHolderHolder,
                                                     ioBidPriceVector,
                                                     ioStudyStatManager);
    const double lMCIntegrationTime = lMCIntegrationBasChrono.elapsed();
    ioStudyStatManager.addMeasure ("MCIntegrationRunningTime",
                                   lMCIntegrationTime);
  }

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  optimalOptimisationByDP (const ResourceCapacity_T iCabinCapacity,
                           BucketHolder& ioBucketHolder) {
    BidPriceVector_T lBidPriceVector;
    DPOptimiser::optimalOptimisationByDP (iCabinCapacity,
                                          ioBucketHolder,
                                          lBidPriceVector);

    // DEBUG
    std::ostringstream ostr;
    // Store current formatting flags of the stream
    std::ios::fmtflags oldFlags = ostr.flags();

    ostr << "BPV: " << std::fixed << std::setprecision (2);
    
    unsigned int i = 0;

    for (BidPriceVector_T::const_iterator itBP = lBidPriceVector.begin();
         itBP != lBidPriceVector.end(); ++itBP, ++i) {
      const double bidPrice = *itBP;
      ostr << "[" << i << "]: " << bidPrice << ", ";
    }

    // Reset formatting flags of stream
    ostr.flags (oldFlags);

    // DEBUG
    STDAIR_LOG_DEBUG (ostr.str());
  }

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  heuristicOptimisationByEmsr (const ResourceCapacity_T iCabinCapacity,
                               BucketHolder& ioBucketHolder,
                               BidPriceVector_T& ioBidPriceVector) {
    Emsr::heuristicOptimisationByEmsr (iCabinCapacity,
                                       ioBucketHolder,
                                       ioBidPriceVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  heuristicOptimisationByEmsr (const ResourceCapacity_T iCabinCapacity,
                               BucketHolder& ioBucketHolder,
                               BidPriceVector_T& ioBidPriceVector,
                               StudyStatManager& ioStudyStatManager) {
    stdair::BasChronometer lEMRSBasChrono;
    lEMRSBasChrono.start();
    Emsr::heuristicOptimisationByEmsr (iCabinCapacity,
                                       ioBucketHolder,
                                       ioBidPriceVector);
    const double lEMRSTime = lEMRSBasChrono.elapsed();
    ioStudyStatManager.addMeasure ("EMSRRunningTime", lEMRSTime);
  }

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  heuristicOptimisationByEmsrA (const ResourceCapacity_T iCabinCapacity,
                                BucketHolder& ioBucketHolder) {
    Emsr::heuristicOptimisationByEmsrA (iCabinCapacity, ioBucketHolder);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Optimiser::heuristicOptimisationByEmsrAwithSellup 
  (const ResourceCapacity_T iCabinCapacity, 
   BucketHolder& ioBucketHolder,
   SellupProbabilityVector_T& iSellupProbabilityVector) {
    Emsr::heuristicOptimisationByEmsrAwithSellup (iCabinCapacity, 
                                                ioBucketHolder, 
                                                iSellupProbabilityVector);
  }

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  heuristicOptimisationByEmsrB (const ResourceCapacity_T iCabinCapacity,
                                BucketHolder& ioBucketHolder) {
    
    // Create the aggregated class/bucket.
    FldYieldRange aYieldRange = FldYieldRange (0);
    FldDistributionParameters aDistribParams = FldDistributionParameters (0,0);
    Demand& aDemand = FacDemand::instance().create(aDistribParams, aYieldRange);
    Bucket& aBucket = FacBucket::instance().create (aYieldRange, aDemand);
    
    Emsr::heuristicOptimisationByEmsrB(iCabinCapacity, ioBucketHolder, aBucket);
  }

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  legOptimisationByMC (const ResourceCapacity_T iCabinCapacity,
                       BucketHolder& ioBucketHolder,
                       BidPriceVector_T& ioBidPriceVector) {
    MCOptimiser::legOptimisationByMC (iCabinCapacity, ioBucketHolder,
                                      ioBidPriceVector);
  }
  
}
