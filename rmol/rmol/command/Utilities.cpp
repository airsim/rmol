
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
//STL
#include <algorithm>
#include <numeric>
#include <math.h>
#include <assert.h>
// RMOL
#include <rmol/command/Utilities.hpp>

namespace RMOL {

  // /////////////////////////////////////////////////////////////////////
  void Utilities::getMinimumElement (double oMinValue,
                                     std::vector<double>& iVector) {

    assert(!iVector.empty());
    std::vector<double>::iterator pos = min_element (iVector.begin(), 
                                                     iVector.end());
    oMinValue = *pos;

  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::getMean (double oMean, std::vector<double>& iVector) {
    assert(!iVector.empty());
    double lSum = std::accumulate(iVector.begin(), iVector.end(),0);
    oMean = lSum/iVector.size();

  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::getStandardDeviation (double oSD, std::vector<double>& iVector,
                                 double iMean) {
    assert(iMean > 0);

    const unsigned int lSize = iVector.size();
    assert(lSize > 0);

    double lSD = 0;    
    for (unsigned int j = 0; j < lSize; j++) {
      const double lElement = iVector.at(j);
      lSD += (lElement - iMean) * (lElement - iMean);
    }
    lSD /= (lSize - 1);
    oSD = sqrt(lSD);
  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::AddAValueToAVector (std::vector<double>& ioVector, 
                                  double iValue){
    const unsigned int lSize = ioVector.size();
    assert(lSize > 0); 
    
    for (unsigned int j = 0; j < lSize; j++) {
      ioVector[j] = ioVector.at(j) + iValue;
    }    
  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::MultiplyAValueToAVector (std::vector<double>& ioVector, 
                                           double iValue) {
    const unsigned int lSize = ioVector.size();
    assert(lSize > 0); 
    
    for (unsigned int j = 0; j < lSize; j++) {
      ioVector[j] = ioVector.at(j) * iValue;    
    }
  }

  // /////////////////////////////////////////////////////////////////////
    static void AddTwoVectors (std::vector<double>& ioVector, 
                               std::vector<double>& iVector) {
      // std::transform (ioVector.begin(), ioVector.end(), iVector.begin(), iVector.end(),)
    }


}
