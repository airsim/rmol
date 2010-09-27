// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <cmath>
// Boost Math
#include <boost/math/distributions/normal.hpp>
// RMOL
#include <rmol/bom/EmsrUtils.hpp>
#include <rmol/bom/Bucket.hpp>
#include <rmol/basic/BasConst_General.hpp>

namespace RMOL {
  // ////////////////////////////////////////////////////////////////////
  void EmsrUtils::computeAggregatedBucket (Bucket& ioAggregatedBucket,
                                              Bucket& ioCurrentBucket) {
    // Retrieve the demand mean, demand standard deviation and average
    // yield of the classes/buckets.
    const double lAggregatedMean = ioAggregatedBucket.getMean();
    const double lCurrentMean = ioCurrentBucket.getMean();
    const double lAggregatedSD = ioAggregatedBucket.getStandardDeviation();
    const double lCurrentSD = ioCurrentBucket.getStandardDeviation();
    const double lAggregatedAverageYield = ioAggregatedBucket.getAverageYield();
    const double lCurrentAverageYield = ioCurrentBucket.getAverageYield();

    // Compute the new demand mean, new demand standard deviation and
    // new average yield for the new aggregated class/bucket.
    const double lNewMean = lAggregatedMean + lCurrentMean;
    const double lNewSD =
      sqrt(lAggregatedSD*lAggregatedSD + lCurrentSD*lCurrentSD);
    double lNewAverageYield = lCurrentAverageYield;
    if (lNewMean > 0) {
      lNewAverageYield = (lAggregatedAverageYield*lAggregatedMean +
                          lCurrentAverageYield*lCurrentMean)/lNewMean;
    } 
    // Set the new yield range for the new aggregated class/bucket.
    ioAggregatedBucket.setYieldRange(lNewAverageYield);

    // Set the new demand for the new aggregated class/bucket.
    ioAggregatedBucket.setDemandParameters (lNewMean, lNewSD);
  }

  // ////////////////////////////////////////////////////////////////////
  const double EmsrUtils::computeProtectionLevel (Bucket& ioAggregatedBucket,
                                                  Bucket& ioNextBucket) {
    // Retrive the mean & standard deviation of the aggregated
    // class/bucket and the average yield of all the two
    // classes/buckets.
    const double lMean = ioAggregatedBucket.getMean();
    const double lSD = ioAggregatedBucket.getStandardDeviation();
    const double lAggreatedYield = ioAggregatedBucket.getAverageYield();
    const double lNextYield = ioNextBucket.getAverageYield();
    assert (lAggreatedYield != 0);
    
    // Compute the yield ratio between the higher bucket and the current one
    const double lYieldRatio = lNextYield / lAggreatedYield;
         
    /** Compute the protection for the aggregated class/bucket.
        <br>Note: The inverse cdf is the quantile function (see also
        http://en.wikipedia.org/wiki/Quantile_function). */
    boost::math::normal lNormalDistribution (lMean, lSD);
    const double lProtection =
      boost::math::quantile (boost::math::complement (lNormalDistribution,
                                                      lYieldRatio));
    
    return lProtection;
  }

  // ////////////////////////////////////////////////////////////////////
  const double EmsrUtils::
  computeProtectionLevelwithSellup (Bucket& iHigherBucket, Bucket& iBucket,
                                    double iSellupFactor) {
    // Retrieve the mean and the standard deviation of the higher 
    // class(es)/bucket(s) depending EMSR-a or EMSR-b
    // and the average yield of each input classes/buckets
    const double lMean = iHigherBucket.getMean();
    const double lSD = iHigherBucket.getStandardDeviation();
    const double lHigherBucketYield = iHigherBucket.getAverageYield();
    const double lBucketYield = iBucket.getAverageYield();
    assert (lHigherBucketYield > DEFAULT_EPSILON);
    assert (1-iSellupFactor > DEFAULT_EPSILON);

    // Compute the yield ratio
    const double lYieldRatio = (lHigherBucketYield - lBucketYield)
      / (lHigherBucketYield * (1 - iSellupFactor));
         
    /** Compute the protection for the for the higher class/bucket.
        <br>Note: The inverse cdf is the quantile function (see also
        http://en.wikipedia.org/wiki/Quantile_function). */
    boost::math::normal lNormalDistribution (lMean, lSD);
    const double lProtectionLevel = boost::math::quantile (lNormalDistribution,
                                                           lYieldRatio);

    return lProtectionLevel;
  }

  // ////////////////////////////////////////////////////////////////////
  const double EmsrUtils::computeEmsrValue (double iCapacity,
                                            Bucket& ioBucket) {
    // Retrieve the average yield, mean and standard deviation of the
    // demand of the class/bucket.
    const double lMean = ioBucket.getMean();
    const double lSD = ioBucket.getStandardDeviation();
    const double lYield = ioBucket.getAverageYield();

    // Compute the EMSR value = lYield * Pr (demand >= iCapacity).
    boost::math::normal lNormalDistribution (lMean, lSD);
    const double emsrValue =
      lYield * boost::math::cdf (boost::math::complement (lNormalDistribution,
                                                          iCapacity));

    return emsrValue;
  }
}
