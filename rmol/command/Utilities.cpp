
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
// StdAir
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/command/Utilities.hpp>

namespace RMOL {

  // /////////////////////////////////////////////////////////////////////
  void Utilities::updateMinimumElement (double& oMinValue,
                                        std::vector<double>& iVector) {

    assert(!iVector.empty());
    std::vector<double>::iterator pos = std::min_element (iVector.begin(), 
                                                          iVector.end());
    oMinValue = *pos;

  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::sumUpElements (double& oSum, std::vector<double>& iVector) 
  {
    const unsigned int lSize = iVector.size();
    if (lSize > 0) {
      oSum = std::accumulate(iVector.begin(), iVector.end(), 0.0);
    }
    else {STDAIR_LOG_ERROR ("There is no element to sum up.");}
  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::updateMean (double& oMean, std::vector<double>& iVector) {
    assert(!iVector.empty());
    double lSum = std::accumulate(iVector.begin(), iVector.end(),0);
    oMean = lSum/iVector.size();

  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::updateSquaredError (double& oSquaredError, 
                               std::vector<double>& iVector,
                               double& iMean) {
    if (iMean < 0) {
      STDAIR_LOG_ERROR ("Negative mean is not expected.");

    } else {
      const unsigned int lSize = iVector.size();

      if (lSize > 0) {
        oSquaredError = 0.0;

        for (unsigned int j = 0; j < lSize; j++) {
          const double lError = iVector.at(j) - iMean;
          oSquaredError += lError * lError;
        }

      } else {
        STDAIR_LOG_ERROR ("No value to compute the squared error");
      }
    }
  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::updateStandardDeviation (double& oSD, 
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
    oSD = std::sqrt (lSD);
  }

  // /////////////////////////////////////////////////////////////////////
  void Utilities::updateMeanAndStandardDeviation 
                                          (std::vector<double>& ioMean_SD,
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
  void appendAVectorToAnother (std::vector<double>& ioVector,
                               std::vector<double>& iVector) {
    ioVector.insert(ioVector.end(), iVector.begin(), iVector.end());
  }

  // // /////////////////////////////////////////////////////////////////////
  // static void overwriteAVectorWithAnotherFromAPosition 
  //                       (std::vector<double>& ioVector,
  //                        std::vector<double>& iVector, 
  //                        std::vector<double>::iterator fromThisPosition) {
  //   ioVector.insert(ioVector.end(), iVector.begin(), iVector.end());
  // }

  // /////////////////////////////////////////////////////////////////////
  std::string Utilities::vectorToString (std::vector<double>& iVector) {
    std::ostringstream oStr;
    for (unsigned int k = 0; k < iVector.size(); k++) {
      oStr << iVector.at(k) << " ";
    }
    return oStr.str() + "\n";
  }
}
