// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <cmath>
// RMOL
#include <rmol/bom/BucketHolder.hpp>
//#include <rmol/bom/Resource.hpp>
#include <rmol/bom/MCOptimiser.hpp>
#include <rmol/factory/FacPartialSumHolder.hpp>
#include <rmol/factory/FacPartialSumHolderHolder.hpp>
#include <rmol/command/Optimiser.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void Optimiser::
  optimalOptimisationByMCIntegration (const int K, 
				      const ResourceCapacity_T iCabinCapacity,
				      BucketHolder& ioBucketHolder) {
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
    for (short j=0 ; j <= nbOfClasses - 1; j++) {
      PartialSumHolder& aPartialSumList = 
	FacPartialSumHolder::instance().create ();

      FacPartialSumHolderHolder::instance().
	addPartialSumHolder (aPartialSumHolderHolder, aPartialSumList);
    }

    // Call the class performing the actual algorithm
    MCOptimiser::optimalOptimisationByMCIntegration (K, iCabinCapacity, 
						     ioBucketHolder,
						     aPartialSumHolderHolder);
  }

}
