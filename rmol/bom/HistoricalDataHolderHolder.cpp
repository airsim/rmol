// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// GSL Random Number Generation 
// (GSL Reference Manual, version 1.7, Chapter 19)
// #include <gsl/gsl_cdf.h>
// #include <gsl/gsl_randist.h>
// C
// #include <assert.h>
// #include <math.h>
// STL
#include <iostream>
#include <iomanip>
// #include <cmath>
// RMU
#include <rmol/bom/HistoricalDataHolder.hpp>
#include <rmol/bom/HistoricalDataHolderHolder.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////
  HistoricalDataHolderHolder::HistoricalDataHolderHolder () {
  }

  // //////////////////////////////////////////////////////////////////
  HistoricalDataHolderHolder::~HistoricalDataHolderHolder () {
    _historicalDataVectorVector.clear();
  }

  // //////////////////////////////////////////////////////////////////
  void HistoricalDataHolderHolder::toStream (std::ostream& ioOut) const {
    const short lSize = getNumberOfHistoricalDataHolder();

    ioOut << "Holder of HistoricalDataHolder: " << std::endl;

    for (short ite = 0; ite < lSize; ++ite) {
      const HistoricalDataHolder& lHistorialDataHolder =
                                    _historicalDataVectorVector.at(ite);
      lHistorialDataHolder.display();
    }
  }

  // //////////////////////////////////////////////////////////////////
  const std::string HistoricalDataHolderHolder::describe() const {
    std::ostringstream ostr;
    ostr << "Holder of HistoricalData structs.";
     
    return ostr.str();
  }
    
  // //////////////////////////////////////////////////////////////////
  void HistoricalDataHolderHolder::display() const {
    toStream (std::cout);
  }
    
}
