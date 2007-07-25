#ifndef __RMOL_BOM_MAFORECAST_HPP
#define __RMOL_BOM_MAFORECAST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
// RMOL Bom
#include <rmol/bom/BomAbstract.hpp>

namespace RMOL {

  // Type definitions
  /** Data type. */
  typedef double DataType_T;
  /** List of values for input and output data. */
  typedef std::vector<DataType_T> DataList_T;
  /** Time / position for the time-series (abscissa). */
  typedef unsigned long TimeAbscissa_T;

  
  /** Support Class for Moving-Average Forecast methods. */
  class MAForecast : public BomAbstract {
  public:

    /** Transform a data set/vector so as to smooth the variations
        thanks to a moving average algorithm.
        <br>The algorithm is derived from:
        <a href="http://www.ivorix.com/en/products/tech/smooth/sma.html">
        Smoothing Time Series (by Ivorix)</a>. */
    static bool smoothByMovingAverage (const DataList_T& iInputData,
                                       DataList_T& ioOutputData,
                                       const TimeAbscissa_T& iSpan);
  };

}
#endif // __RMOL_BOM_MAFORECAST_HPP
