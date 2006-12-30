// C
#include <assert.h>
// STL
#include <iostream>
#include <sstream>
#include <cmath>
// GSL
#include <gsl/gsl_math.h>
//#include <gsl/gsl_statext.h>
// RMOL
#include <rmol/DemandGeneratorList.hpp>
#include <rmol/PartialSumList.hpp>
#include <rmol/BucketList.hpp>
#include <rmol/MCUtils.hpp>


// M A I N
int main (int argc, char* argv[]) {
  int K = 0;
  
  if (argv[1] != NULL) {
    std::istringstream istr (argv[1]);
    istr >> K;
  }
  
  if (argv[2] != NULL) {
    std::istringstream istr (argv[2]);
    // istr >> mean;
  }
  
  if (argv[3] != NULL) {
    std::istringstream istr (argv[3]);
    // istr >> variance;
  }

  // STEP 0.
  // List of demand distribution parameters (mean and standard deviation)
  RMOL::DistributionParameterList_T aDistributionParameterList;
  RMOL::BucketList_T aBucketList;

  // Class/bucket 1: N (20, 9), p1 = 100
  const RMOL::FldYieldRange aYieldRange1 (100.0);
  const RMOL::FldDistributionParameters aDistribParams1 (20, 9);
  const RMOL::Demand aDemand1 (aDistribParams1, aYieldRange1);
  aDistributionParameterList.push_back (aDistribParams1);
  RMOL::Bucket aBucket1 (aYieldRange1, aDemand1);
  aBucketList.push_back (aBucket1);

  // Class/bucket 2: N (45, 12), p2 = 70
  const RMOL::FldYieldRange aYieldRange2 (70.0);
  const RMOL::FldDistributionParameters aDistribParams2 (45, 12);
  const RMOL::Demand aDemand2 (aDistribParams2, aYieldRange2);
  aDistributionParameterList.push_back (aDistribParams2);
  RMOL::Bucket aBucket2 (aYieldRange2, aDemand2);
  aBucketList.push_back (aBucket2);

  // Class/bucket 3: no need to define a demand distribution, p3 = 42
  const RMOL::FldYieldRange aYieldRange3 (42.0);
  RMOL::Bucket aBucket3 (aYieldRange3);
  aBucketList.push_back (aBucket3);
  
  // Number of classes/buckets
  const short nbOfClasses = aDistributionParameterList.size();
  
  // Display head of CSV file (for reporting purposes)
  std::cout << "Event; ";
  for (short i=1; i <= nbOfClasses; i++) {
    std::cout << "Class " << i << "; ";
  }
  std::cout << std::endl;
  
  // Initialise the Demand Random Generator
  const RMOL::DemandGeneratorList aDemandGeneratorList (aDistributionParameterList);


  // STEP 1.
  /** 
      Preparation of the Demand Simulation run.
      Demand:                d(j,k), for j=1 to n-1 and k=1 to K.
      Partial Sum of demand: S(j,k), for j=1 to n-1 and k=1 to K.
  */

  // Demand collection structure: d(j,k)
  RMOL::DemandSimulation_T aDemandSimulation;
  RMOL::MCUtils::initialiseDemandSimulation (K, aDemandSimulation);

  // Partial sum (of demand) collection structure: S(j,k)
  RMOL::DemandSimulationPartialSum_T aDemandSimulationPartialSumList;
  RMOL::MCUtils::initialisePartialSums (nbOfClasses, K,
                                        aDemandSimulationPartialSumList);
  
  // STEP 2.
  /** 
      Generate and store K random demand vectors/lists d(j,k), for j=1 to n-1.
      Calculate and store n-1 partial sum vectors S(j,k), for k=1 to K.

      Note that that step may be further split in three successive loops
      (iterating each time on k), to give some more flexibility. 
      However, it would imply looping three times on K, which can be heavy 
      when K is big (10,000 for example).
   */

  // Iterate on the number of random draws, K.
  RMOL::DemandSimulation_T::iterator itDraw = aDemandSimulation.begin();
  for (short k=1 ; itDraw != aDemandSimulation.end(); itDraw++, k++) {
    RMOL::VariateList_T& aRandomVariatesDraw = *itDraw;
    
    /** Randomly generate the demand variates:
        d(j,k), for j=1 to n-1 and the current k.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets.
    */
    aDemandGeneratorList.generateVariateList (aRandomVariatesDraw);

    // Display
    std::cout << k << "; ";
    RMOL::VariateList_T::const_iterator itVariate= aRandomVariatesDraw.begin();
    for ( ; itVariate != aRandomVariatesDraw.end(); itVariate++) {
      const double djk = *itVariate;
      std::cout << djk << "; ";
    }
    std::cout << std::endl;

    /** 
	Calculate the partial sums:
	S(j,k) = d(1,k) + d(2,k) + ... + d(j,k), for a given k, and j=1 to n-1.
	Note that n-1 corresponds to the size of the parameter list,
	i.e., n corresponds to the number of classes/buckets.
    */
    RMOL::MCUtils::calculatePartialSum (k, aRandomVariatesDraw,
					aDemandSimulationPartialSumList);

  }

  // STEP 3.
  /**
     Sort the partial sum vectors S(j,k) on k for each given j.
  */
  RMOL::DemandSimulationPartialSum_T::iterator itPartialSumVector = 
    aDemandSimulationPartialSumList.begin();
  RMOL::BucketList_T::iterator itjBucket = aBucketList.begin();
  RMOL::BucketList_T::iterator itjp1Bucket = aBucketList.begin();
  if (itjp1Bucket != aBucketList.end()) {
    itjp1Bucket++;
  }
  for ( ; itPartialSumVector != aDemandSimulationPartialSumList.end(); 
	itPartialSumVector++, itjBucket++, itjp1Bucket++) {
    RMOL::PartialSumList_T& aPartialSumVector = *itPartialSumVector;

    /** 
	The STL implements the introsort algorithm, which has a worst case
	complexity of O (N log N): http://www.sgi.com/tech/stl/sort.html
    */
    std::sort (aPartialSumVector.begin(), aPartialSumVector.end());

    /** Retrieve Bucket(j) and Bucket(j+1). */
    RMOL::Bucket& jBucket = *itjBucket;
    const RMOL::Bucket& jp1Bucket = *itjp1Bucket;

    const double pj = jBucket.getAverageYield();
    const double pj1 = jp1Bucket.getAverageYield();

    // DEBUG
    // std::cout << "p(j) = " << pj << ", p(j+1) = " << pj1 << std::endl;

    /** 
	The optimal index is defined as:
	l = floor [p(j+1)/p(j) . K]
    */
    const double ldouble = std::floor (K * pj1 / pj);
    const short l = static_cast<short> (ldouble);
    assert (l >= 1 && l < K);

    // DEBUG
    // std::cout << "ldouble = " << ldouble << ", l = " << l << std::endl;

    /** 
	The optimal protection is defined as:
	y(j) = 1/2 [S(j,l) + S(j, l+1)]
    */
    const double sjl = aPartialSumVector.at (l);
    const double sjlp1 = aPartialSumVector.at (l+1);
    const double yj = (sjl + sjlp1) / 2;

    // DEBUG
    // std::cout << "S(j,l) = " << sjl << ", S(j,l+1) = " << sjlp1 << std::endl;

    // Set the protection for Bucket(j) (j ranging from 1 to n-1)
    jBucket.setProtection (yj);
  }
  
  // Set the protection of Bucket(n) to be equal to the capacity:
  // jBucket.setProtection (cabinCapacity);
  
  // Display
  RMOL::BucketList_T::iterator itBucket = aBucketList.begin();
  for (short j=1; itBucket != aBucketList.end(); itBucket++, j++) {
    const RMOL::Bucket& jBucket = *itBucket;

    const double yj = jBucket.getProtection();
    std::cout << "Protect[" << j << "] = " << yj << std::endl;
  }
  
  return 0;	
}
