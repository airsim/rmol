// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
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
  void MCUtils::calculatePartialSum (const VariateList_T& iRandomVariatesDraw,
                                     PartialSumList_T& ioPartialSumList) {
    /** Calculate the partial sums:
        S(j,k) = d(1,k) + d(2,k) + ... + d(j,k),
        for j=1 to n-1 and the current k.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets. */
    // Iterate on the number of classes/buckets (from 1 to n-1)
    RMOL::PartialSumList_T::iterator itPartialSum = ioPartialSumList.begin();
    for (short j=1; itPartialSum != ioPartialSumList.end();
         itPartialSum++, j++) {
      // Retrieve the partial sum S(j,k)
      double& sjk = *itPartialSum;

      /** Iterate on the number of demand variates summing up in the
          partial sum:
          S(j,k) = Sum [d(i,k)], for i=1 to j, and the current j and k. */
      RMOL::VariateList_T::const_iterator itVariate =
        iRandomVariatesDraw.begin();
      for (short i=1; i <= j; itVariate++, i++) {
        // Retrieve d(i,k)
        const double dik = *itVariate;

        // Add-up d(i,k) to s(j,k)
        sjk += dik;
      }
    }
  }
  
}
