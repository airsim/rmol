// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <cmath>
// RMOL
#include <rmol/factory/FacPartialSumHolder.hpp>
#include <rmol/bom/VariateList.hpp>
#include <rmol/bom/Gaussian.hpp>
#include <rmol/bom/EmsrUtils.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void EmsrUtils::
  heuristicOptimisationByEmsrA (       const double iCabinCapacity,
                                       BucketHolder& ioBucketHolder) {

    // Number of classes/buckets: n
    const short nbOfClasses = ioBucketHolder.getSize();
    for (int s=1 ; s <=iCabinCapacity ; s++){
      double maxEmsrValue=0.0;
      int highestBucket=1;
      
      for(ioBucketHolder.begin(); ioBucketHolder.hasNotReachedEnd(); ioBucketHolder.iterate()){
        Bucket& currentBucket = ioBucketHolder.getCurrentBucket();

        // Compute EMSR value of the seat #s for class j
        double emsrForsj=0;
        /** Evaluate if this class j has the highest EMSR value for seat #s.
            If so, maxEMSRValue is the EMSR value of j, and j becomes temporarily the highest class.
        */ 
        if(emsrForsj>=maxEMSRValue){
          maxemsrvalue=emsrForsj;
          ioBucketHolder.tag();
        }

      }
      
      Bucket& theHighestBucket=ioBucketHolder.getTaggedBucket();
      theHighestBucket._protection+=1.0;
    }

    
  }

}
