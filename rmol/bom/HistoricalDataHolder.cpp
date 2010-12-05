// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
//#include <iomanip>
#include <cmath>
// RMU
#include <rmol/bom/HistoricalDataHolder.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////
  HistoricalDataHolder::HistoricalDataHolder () {
  }

  // //////////////////////////////////////////////////////////////////
  HistoricalDataHolder::~HistoricalDataHolder () {
    _historicalDataVector.clear();
  }

  // //////////////////////////////////////////////////////////////////
  const double HistoricalDataHolder::getMean () const {
    double lResult = 0.0;
    const double& lSize = getNumberOfHistoricalData();

    for (short ite = 0; ite < lSize; ++ite) {
      const double& lHistoricalData = getHistoricalData(ite);
      lResult += (lHistoricalData);
    }

    lResult /= lSize;

    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  const double HistoricalDataHolder::getStandardDeviation
  (const double& iMean) const {
    double lResult = 0.0;
    const double& lSize = getNumberOfHistoricalData();

    for (short ite = 0; ite < lSize; ++ite) {
      const double& lHistorialData = getNumberOfHistoricalData();
      lResult += 
         (lHistorialData - iMean) * (lHistorialData - iMean);
    }

    lResult /= (lSize - 1);

    lResult = sqrt (lResult);

    return lResult;
  }

  // //////////////////////////////////////////////////////////////////
  void HistoricalDataHolder::toStream (std::ostream& ioOut) const {
    const double& lSize = getNumberOfHistoricalData();

    ioOut << "Historical Data Vector: " << std::endl;

    for (short ite = 0; ite < lSize; ++ite) {
      const double& lHistoricalData = getHistoricalData(ite);
      ioOut << lHistoricalData << " "
            << std::endl;
    }
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string HistoricalDataHolder::describe() const {
    std::ostringstream ostr;
    ostr << "Holder of historical data.";
     
    return ostr.str();
  }
    
  // //////////////////////////////////////////////////////////////////
  void HistoricalDataHolder::display() const {
    toStream (std::cout);
  }
    
}
