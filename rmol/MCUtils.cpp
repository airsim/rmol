// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include "VariateList.hpp"
#include "MCUtils.hpp"

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  void MCUtils::
  initialiseDemandSimulation (const double iNbOfDraws,
                              DemandSimulation_T& ioDemandSimulation) {
    for (short k=1; k <= iNbOfDraws; k++) {
      // Preparation of the demand variates (for the current k)
      RMOL::VariateList_T aRandomVariateList;
      ioDemandSimulation.push_back (aRandomVariateList);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void MCUtils::initialisePartialSums (const double iNbOfClasses,
                                       const double iNbOfDraws,
                                       DemandSimulationPartialSum_T& ioDSPS) {

    /** Preparation of the partial sums of demand (for all the classes).
        Initialse with 0 values, so that the lists/vectors have
        the correct size. */
    for (short i=1; i <= iNbOfClasses; i++) {
      RMOL::PartialSumList_T aPartialSumList;
    
      for (short k=1; k <= iNbOfDraws; k++) {
        aPartialSumList.push_back (0.0);
      }
      
      ioDSPS.push_back (aPartialSumList);
    }
    
  }

  // //////////////////////////////////////////////////////////////////////
  void MCUtils::
  calculatePartialSum (const short k, const VariateList_T& iRandomVariatesDraw,
		       DemandSimulationPartialSum_T& ioDemandSimulationPartialSumList) {

    /** 
	Calculate the partial sums:
	S(j,k) = d(1,k) + d(2,k) + ... + d(j,k), for a given k, and j=1 to n-1.
	Note that n-1 corresponds to the size of the parameter list,
	i.e., n corresponds to the number of classes/buckets.
    */

    // Iterate on the number of classes/buckets, n, from 1 to n-1.
    DemandSimulationPartialSum_T::iterator itDrawPartialSumVector =
      ioDemandSimulationPartialSumList.begin();
    VariateList_T::const_iterator itVariate= iRandomVariatesDraw.begin();
    for (short j=1; itVariate != iRandomVariatesDraw.end(); 
	 itVariate++, itDrawPartialSumVector++, j++) {
      const double djk = *itVariate;
      
      /** Calculate/update the partial sums: S(j,k) += d(j,k)
	  for a given j (between 1 and n-1) and a given k (from 1 to K).
	  Eventually, at the end of the loop:
	  S(j,k) = d(1,k) + d(2,k) + ... + d(j,k),
	  Note that n-1 corresponds to the size of the parameter list,
	  i.e., n corresponds to the number of classes/buckets.
      */
      if (j >= k) {
	PartialSumList_T& aPartialSumVector = *itDrawPartialSumVector;
	// Retrieve the partial sum S(j,k)
	double& sjk = aPartialSumVector.at (k);

	// Add-up d(j,k) to S(j,k)
	sjk += djk;
      }
    }
  }

}
