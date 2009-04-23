// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <cmath>
#include <iomanip>
// RMOL
#include <rmol/bom/BucketHolder.hpp>
//#include <rmol/bom/Resource.hpp>
#include <rmol/bom/MCOptimiser.hpp>
#include <rmol/bom/Emsr.hpp>
#include <rmol/bom/DPOptimiser.hpp>
#include <rmol/field/FldYieldRange.hpp>
#include <rmol/field/FldDistributionParameters.hpp>
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
  }

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  optimalOptimisationByDP (const ResourceCapacity_T iCabinCapacity,
                           BucketHolder& ioBucketHolder) {
    BidPriceVector_T lBidPriceVector;
    DPOptimiser::optimalOptimisationByDP (iCabinCapacity,
                                          ioBucketHolder,
                                          lBidPriceVector);
    std::cout << "BVP: ";
    unsigned int size = lBidPriceVector.size();

    for (unsigned int i = 0; i < size; ++i) {
      const double bidPrice = lBidPriceVector.at(i);
      std::cout << std::fixed << std::setprecision (2) << bidPrice << " ";
    }
    std::cout << std::endl;
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
  heuristicOptimisationByEmsrA (const ResourceCapacity_T iCabinCapacity,
                                BucketHolder& ioBucketHolder) {
    Emsr::heuristicOptimisationByEmsrA (iCabinCapacity, ioBucketHolder);
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  heuristicOptimisationByEmsrB (const ResourceCapacity_T iCabinCapacity,
                                BucketHolder& ioBucketHolder) {
    
    // Create the aggregated class/bucket.
    FldYieldRange aYieldRange = FldYieldRange::FldYieldRange (0);
    FldDistributionParameters aDistribParams =
      FldDistributionParameters::FldDistributionParameters (0,0);
    Demand& aDemand =
      FacDemand::instance().create (aDistribParams, aYieldRange);
    Bucket& aBucket = FacBucket::instance().create (aYieldRange, aDemand);
    
    Emsr::heuristicOptimisationByEmsrB (iCabinCapacity,
                                        ioBucketHolder,
                                        aBucket);
  }
}
