#include <iostream>
#include <sstream>
#include <cmath>
// GSL
#include <gsl/gsl_math.h>
//#include <gsl/gsl_statext.h>
// RMOL
#include <rmol/DemandGeneratorList.hpp>
#include <rmol/PartialSumList.hpp>
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
  RMOL::ParameterList_T aParameterList;
  // Class/bucket 1: N (20, 9)
  aParameterList.push_back (RMOL::FldDistributionParameters (20, 9));
  // Class/bucket 2: N (45, 12)
  aParameterList.push_back (RMOL::FldDistributionParameters (45, 12));
  // Class/bucket 3: no need to define a demand distribution
  
  // Number of classes/buckets
  const short nbOfClasses = aParameterList.size();
  
  // Display head of CSV file (for reporting purposes)
  std::cout << "Event; ";
  for (short i=1; i <= nbOfClasses; i++) {
    std::cout << "Class " << i << "; ";
  }
  std::cout << std::endl;
  
  // Initialise the Demand Random Generator
  const RMOL::DemandGeneratorList aDemandGeneratorList (aParameterList);


  // STEP 1.
  /** Preparation of the Demand Simulation run.
      Demand:                d(j,k), for j=1 to n-1 and k=1 to K.
      Partial Sum of demand: S(j,k), for j=1 to n-1 and k=1 to K.*/

  // Demand collection structure
  RMOL::DemandSimulation_T aDemandSimulation;
  RMOL::MCUtils::initialiseDemandSimulation (K, aDemandSimulation);

  // Partial sum (of demand) collection structure: S(j,k)
  RMOL::DemandSimulationPartialSum_T aDemandSimulationPartialSumList;
  RMOL::MCUtils::initialisePartialSums (nbOfClasses, K,
                                        aDemandSimulationPartialSumList);
  
  // STEP 2.
  // Iterate on the number of random draws (demand "vectors").
  RMOL::DemandSimulation_T::iterator itDraw = aDemandSimulation.begin();
  RMOL::DemandSimulationPartialSum_T::iterator itDrawPartialSumList =
    aDemandSimulationPartialSumList.begin();
  for (short k=1 ; itDraw != aDemandSimulation.end();
       itDraw++, itDrawPartialSumList++, k++) {
    RMOL::VariateList_T& aRandomVariatesDraw = *itDraw;
    
    /** Randomly generate the demand variates:
        d(j,k), for j=1 to n-1 and the current k.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets. */
    aDemandGeneratorList.generateVariateList (aRandomVariatesDraw);

    // Display
    std::cout << k << "; ";
    // Iterate on the number of classes/buckets (from 1 to n-1)
    RMOL::VariateList_T::const_iterator itVariate= aRandomVariatesDraw.begin();
    for (short j=1; itVariate != aRandomVariatesDraw.end(); itVariate++, j++) {
      const double djk = *itVariate;
      std::cout << djk << "; ";
    }
    std::cout << std::endl;

    /** Calculate the partial sums:
        S(j,k) = d(1,k) + d(2,k) + ... + d(j,k),
        for j=1 to n-1 and the current k.
        Note that n-1 corresponds to the size of the parameter list,
        i.e., n corresponds to the number of classes/buckets. */
    RMOL::PartialSumList_T& aPartialSumList = *itDrawPartialSumList;
    RMOL::MCUtils::calculatePartialSum (aRandomVariatesDraw, aPartialSumList);
  }
  
  return 0;	
}
