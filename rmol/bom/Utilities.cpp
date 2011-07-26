
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
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/Utilities.hpp>
#include <rmol/bom/GuillotineBlockHelper.hpp>

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

  // ////////////////////////////////////////////////////////////////////
  stdair::DCPList_T Utilities::
  buildRemainingDCPList (const stdair::DTD_T& iDTD) {
    stdair::DCPList_T oDCPList;

    const stdair::DCPList_T lWholeDCPList = stdair::DEFAULT_DCP_LIST;
    stdair::DCPList_T::const_iterator itDCP = lWholeDCPList.begin();
    while (itDCP != lWholeDCPList.end()) {
      const stdair::DCP_T& lDCP = *itDCP;
      if (iDTD >= lDCP) {
        break;
      }
      ++itDCP;
    }
    assert (itDCP != lWholeDCPList.end());

    oDCPList.push_back (iDTD);
    ++itDCP;
    for (; itDCP != lWholeDCPList.end(); ++itDCP) {
      oDCPList.push_back (*itDCP);
    }
    
    return oDCPList;
  }

  // ////////////////////////////////////////////////////////////////////
  stdair::NbOfSegments_T Utilities::
  getNbOfDepartedSimilarSegments (const stdair::SegmentCabin& iSegmentCabin,
                                  const stdair::Date_T& iEventDate) {
    stdair::DTD_T lDTD = 0;
    // Retrieve the guillotine block.
    const stdair::GuillotineBlock& lGuillotineBlock =
      iSegmentCabin.getGuillotineBlock();
    return GuillotineBlockHelper::
      getNbOfSegmentAlreadyPassedThisDTD (lGuillotineBlock, lDTD, iEventDate);
  }

}
