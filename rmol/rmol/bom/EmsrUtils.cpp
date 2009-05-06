// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 19)
#include <gsl/gsl_cdf.h>
// C
#include <math.h>
#include <assert.h>
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
    
    // Compute the protection for the aggregated class/bucket
    const double lProtection = 
      lMean + gsl_cdf_gaussian_Qinv (lNextYield/lAggreatedYield, lSD);
    
    return lProtection;
  }

  // ////////////////////////////////////////////////////////////////////
  const double EmsrUtils::computeProtectionLevelwithSellup (Bucket& iHigherBucket,
                                                            Bucket& iBucket,
                                                            double iSellupFactor){
    // Retrieve the mean and the standard deviation of the higher 
    // class(es)/bucket(s) depending EMSR-a or EMSR-b
    // and the average yield of each input classes/buckets
    const double lMean = iHigherBucket.getMean();
    const double lSD = iHigherBucket.getStandardDeviation();
    const double lHigherBucketYield = iHigherBucket.getAverageYield();
    const double lBucketYield = iBucket.getAverageYield();
    assert (lHigherBucketYield > DEFAULT_EPSILON);
    assert (1-iSellupFactor > DEFAULT_EPSILON);

    // compute the protection level for the higher class/bucket
    const double lProtectionLevel = 
      lMean + 
      gsl_cdf_gaussian_Pinv((lHigherBucketYield-lBucketYield)/
                            lHigherBucketYield*(1-iSellupFactor),lSD);
    
    return lProtectionLevel;
  }

  // ////////////////////////////////////////////////////////////////////
  const double EmsrUtils::computeEmsrValue (double iCapacity, Bucket& ioBucket) {
    // Retrive the average yield, mean and standard deviation of the
    // demand of the class/bucket.
    const double lMean = ioBucket.getMean();
    const double lSD = ioBucket.getStandardDeviation();
    const double lYield = ioBucket.getAverageYield();

    // Compute the EMSR value = lYield * Pr (demand >= iCapacity).
    const double emsrValue = lYield * gsl_cdf_gaussian_Q(iCapacity-lMean, lSD);

    return emsrValue;
  }
}
