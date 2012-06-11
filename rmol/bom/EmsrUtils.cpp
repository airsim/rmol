// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <cmath>
// Boost Math
#include <boost/math/distributions/normal.hpp>
// StdAir
#include <stdair/stdair_maths_types.hpp>
#include <stdair/bom/VirtualClassStruct.hpp>
// RMOL
#include <rmol/bom/EmsrUtils.hpp>
#include <rmol/basic/BasConst_General.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  void EmsrUtils::computeAggregatedVirtualClass
  (stdair::VirtualClassStruct& ioAggregatedVirtualClass,
   stdair::VirtualClassStruct& ioCurrentVirtualClass) {
    // Retrieve the demand mean, demand standard deviation and average
    // yield of the classes/buckets.
    const stdair::MeanValue_T lAggregatedMean =
      ioAggregatedVirtualClass.getMean();
    const stdair::MeanValue_T lCurrentMean = ioCurrentVirtualClass.getMean();
    const stdair::StdDevValue_T lAggregatedSD =
      ioAggregatedVirtualClass.getStdDev();
    const stdair::StdDevValue_T lCurrentSD = ioCurrentVirtualClass.getStdDev();
    const stdair::Yield_T lAggregatedYield =
      ioAggregatedVirtualClass.getYield();
    const stdair::Yield_T lCurrentYield = ioCurrentVirtualClass.getYield();

    // Compute the new demand mean, new demand standard deviation and
    // new average yield for the new aggregated class/bucket.
    const stdair::MeanValue_T lNewMean = lAggregatedMean + lCurrentMean;
    const stdair::StdDevValue_T lNewSD =
      std::sqrt (lAggregatedSD*lAggregatedSD + lCurrentSD*lCurrentSD);
    stdair::Yield_T lNewYield = lCurrentYield;
    if (lNewMean > 0) {
      lNewYield = (lAggregatedYield*lAggregatedMean +
                   lCurrentYield*lCurrentMean) / lNewMean;
    } 
    // Set the new yield range for the new aggregated class/bucket.
    ioAggregatedVirtualClass.setYield(lNewYield);

    // Set the new demand for the new aggregated class/bucket.
    ioAggregatedVirtualClass.setMean (lNewMean);
    ioAggregatedVirtualClass.setStdDev (lNewSD);
  }

  // ////////////////////////////////////////////////////////////////////
  const stdair::ProtectionLevel_T EmsrUtils::
  computeProtectionLevel (stdair::VirtualClassStruct& ioAggregatedVirtualClass,
                          stdair::VirtualClassStruct& ioNextVirtualClass) {
    // Retrive the mean & standard deviation of the aggregated
    // class/bucket and the average yield of all the two
    // classes/buckets.
    const stdair::MeanValue_T lMean = ioAggregatedVirtualClass.getMean();
    const stdair::StdDevValue_T lSD = ioAggregatedVirtualClass.getStdDev();
    const stdair::Yield_T lAggreatedYield = ioAggregatedVirtualClass.getYield();
    const stdair::Yield_T lNextYield = ioNextVirtualClass.getYield();
    assert (lAggreatedYield != 0);
    
    // Compute the yield ratio between the higher bucket and the current one
    const double lYieldRatio = lNextYield / lAggreatedYield;
         
    /** Compute the protection for the aggregated class/bucket.
        <br>Note: The inverse cdf is the quantile function (see also
        http://en.wikipedia.org/wiki/Quantile_function). */
    boost::math::normal lNormalDistribution (lMean, lSD);
    const stdair::ProtectionLevel_T lProtection =
      boost::math::quantile (boost::math::complement (lNormalDistribution,
                                                      lYieldRatio));
    
    return lProtection;
  }

  // ////////////////////////////////////////////////////////////////////
  const double EmsrUtils::
  computeEmsrValue (double iCapacity,
                    stdair::VirtualClassStruct& ioVirtualClass){
    // Retrieve the average yield, mean and standard deviation of the
    // demand of the class/bucket.
    const stdair::MeanValue_T lMean = ioVirtualClass.getMean();
    const stdair::StdDevValue_T lSD = ioVirtualClass.getStdDev();
    const stdair::Yield_T lYield = ioVirtualClass.getYield();

    // Compute the EMSR value = lYield * Pr (demand >= iCapacity).
    boost::math::normal lNormalDistribution (lMean, lSD);
    const double emsrValue =
      lYield * boost::math::cdf (boost::math::complement (lNormalDistribution,
                                                          iCapacity));

    return emsrValue;
  }
}
