// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <cmath>
// RMOL Bom
#include <rmol/bom/MAForecast.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  bool MAForecast::smoothByMovingAverage (const DataList_T& iInputData,
                                          DataList_T& ioOutputData,
                                          const TimeAbscissa_T& iSpan) {

    const TimeAbscissa_T lInputDateSize = iInputData.size();
    if (iSpan == 0 || iSpan >= lInputDateSize) {
      return false;
    }

    ioOutputData.clear();
    ioOutputData.reserve (lInputDateSize);

    const DataType_T lFirstDataElement = iInputData.at(0);
    ioOutputData.push_back (lFirstDataElement);

    DataType_T sum = 0;
    for (TimeAbscissa_T x = 1; x != lInputDateSize; x++) {
      const TimeAbscissa_T p = std::min (x, iSpan);

      if ( p <= iSpan ) {
        sum = 0;

        for (TimeAbscissa_T y = 0; y != p; y++) {
          sum += iInputData.at(x-y);
        }
        
      } else {
        // save cpu cycles: add current
        // value and subtract least recent
        sum = sum - iInputData.at(x-p) + iInputData.at(x);
      }

      ioOutputData.push_back (sum / p);
    }

    return true;
  }    

}
