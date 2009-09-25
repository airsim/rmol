
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
//STL
#include <algorithm>
#include <string>
#include <sstream>
#include <numeric>
#include <math.h>
#include <assert.h>
#include <functional>
// RMOL
#include <rmol/command/Utilities.hpp>

namespace RMOL {

  // /////////////////////////////////////////////////////////////////////
  void Utilities::getMinimumElement (double& oMinValue,
                                     std::vector<double>& iVector) {

    assert(!iVector.empty());
    std::vector<double>::iterator pos = min_element (iVector.begin(), 
                                                     iVector.end());
    oMinValue = *pos;

  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::getMean (double& oMean, std::vector<double>& iVector) {
    assert(!iVector.empty());
    double lSum = std::accumulate(iVector.begin(), iVector.end(),0);
    oMean = lSum/iVector.size();

  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::getStandardDeviation (double& oSD, 
                                        std::vector<double>& iVector,
                                        double& iMean) {
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
  void Utilities::getMeanAndStandardDeviation (std::vector<double>& ioMean_SD,
                                           std::vector<double>& iVector) {
    const unsigned int lSize = iVector.size();
    assert(lSize > 0);

    ioMean_SD.clear();

    // Mean
    double lMean = 0;
    for (unsigned int k = 0; k < lSize; k++) {
      lMean += iVector.at(k);
    }
    lMean /= lSize;
    ioMean_SD.push_back(lMean);

    //Standard Deviation
    double lSD = 0;
    for (unsigned int j = 0; j < lSize; j++) {
      const double lDeviation = iVector.at(j) - lMean;
      lSD += lDeviation * lDeviation;
    }
    lSD /= (lSize - 1);
    ioMean_SD.push_back(sqrt(lSD));
  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::addAValueToAVector (std::vector<double>& ioVector, 
                                      double iValue){
    const unsigned int lSize = ioVector.size();
    assert(lSize > 0); 
    
    for (unsigned int j = 0; j < lSize; j++) {
      ioVector[j] = ioVector.at(j) + iValue;
    }    
  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::multiplyAValueToAVector (std::vector<double>& ioVector, 
                                           double iValue) {
    const unsigned int lSize = ioVector.size();
    assert(lSize > 0); 
    
    for (unsigned int j = 0; j < lSize; j++) {
      ioVector[j] = ioVector.at(j) * iValue;    
    }
  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::addTwoVectors (std::vector<double>& ioVector, 
                                 std::vector<double>& iVector) {
    unsigned int lSize = ioVector.size();
    // assert(lSize == iVector.size());

    for (unsigned int k = 0; k < lSize; k++) {
      ioVector.at(k) = ioVector.at(k) + iVector.at(k);
    }
  }
  // /////////////////////////////////////////////////////////////////////
  std::string Utilities::vectorToString (std::vector<double>& iVector) {
    std::ostringstream oStr;
    for (unsigned int k = 0; k < iVector.size(); k++) {
      oStr << iVector.at(k) << ", ";
    }
    return oStr.str() + "\n";
  }
}
