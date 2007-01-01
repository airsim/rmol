// STL
#include <iostream>
#include <sstream>
// RMOL
#include <rmol/FacSupervisor.hpp>
#include <rmol/FacBucketHolder.hpp>
#include <rmol/MCUtils.hpp>


// M A I N
int main (int argc, char* argv[]) {
  // Number of random draws to be generated (best if greater than 100)
  int K = 100;
  // Cabin Capacity (it must be greater then 100 here)
  double cabinCapacity = 100.0;
  
  if (argv[1] != NULL) {
    std::istringstream istr (argv[1]);
    istr >> K;
  }
  
  if (argv[2] != NULL) {
    std::istringstream istr (argv[2]);
    istr >> cabinCapacity;
  }
  

  // STEP 0.
  // List of demand distribution parameters (mean and standard deviation)
  RMOL::BucketHolder& aBucketHolder = 
    RMOL::FacBucketHolder::instance().create (cabinCapacity);

  // Class/bucket 1: N (20, 9), p1 = 100
  const RMOL::FldYieldRange aYieldRange1 (100.0);
  const RMOL::FldDistributionParameters aDistribParams1 (20, 9);
  const RMOL::Demand aDemand1 (aDistribParams1, aYieldRange1);
  RMOL::Bucket aBucket1 (aYieldRange1, aDemand1);
  aBucketHolder.addBucket (aBucket1);

  // Class/bucket 2: N (45, 12), p2 = 70
  const RMOL::FldYieldRange aYieldRange2 (70.0);
  const RMOL::FldDistributionParameters aDistribParams2 (45, 12);
  const RMOL::Demand aDemand2 (aDistribParams2, aYieldRange2);
  RMOL::Bucket aBucket2 (aYieldRange2, aDemand2);
  aBucketHolder.addBucket (aBucket2);

  // Class/bucket 3: no need to define a demand distribution, p3 = 42
  const RMOL::FldYieldRange aYieldRange3 (42.0);
  RMOL::Bucket aBucket3 (aYieldRange3);
  aBucketHolder.addBucket (aBucket3);
  
  // Calculate the optimal protections by the Monte Carlo Integration approach
  RMOL::MCUtils::optimialOptimisationByMCIntegration (K, cabinCapacity,
						      aBucketHolder);
  
  // Display
  aBucketHolder.display();

  // Clean operations
  RMOL::FacSupervisor::cleanFactory();
  
  return 0;	
}
