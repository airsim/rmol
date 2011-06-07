
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
#include <rmol/bom/Utilities.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  void Utilities::
  computeDistributionParameters (const UnconstrainedDemandVector_T& iVector,
                                 double& ioMean, double& ioStdDev) {
    ioMean = 0.0; ioStdDev = 0.0;
    unsigned int lNbOfSamples = iVector.size();
    assert (lNbOfSamples > 1);

    // Compute the mean
    for (UnconstrainedDemandVector_T::const_iterator itSample = iVector.begin();
         itSample != iVector.end(); ++itSample) {
      ioMean += *itSample;
    }
    ioMean /= lNbOfSamples;

    // Compute the standard deviation
    for (UnconstrainedDemandVector_T::const_iterator itSample = iVector.begin();
         itSample != iVector.end(); ++itSample) {
      const double& lSample = *itSample;
      ioStdDev += ((lSample - ioMean) * (lSample - ioMean));
    }
    ioStdDev /= (lNbOfSamples - 1);
    ioStdDev = sqrt (ioStdDev);

    // Sanity check
    if (ioStdDev == 0) {
      ioStdDev = 0.1;
    }
  }
}
