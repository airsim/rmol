#ifndef __RMOL_EMSRUTILS_HPP
#define __RMOL_EMSRUTILS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace RMOL {
  
  /** Forward declarations. */
  // Class Resource;
  class Bucket;
  
  class EmsrUtils {
  public:
    /** Compute the aggregated class/bucket of classes/buckets 1,..,j
        for EMSR-b algorithm. */
    static void computeAggregatedBucket (Bucket&, Bucket&);

    /** Compute the protection level using the Little-Wood formular. */
    static const double computeProtectionLevel (Bucket&, Bucket&);

    /** Compute the protection level with sell up factor */
    static const double computeProtectionLevelwithSellup (Bucket&, Bucket&, double);

    /** Compute the EMSR value of a class/bucket. */
    static const double computeEmsrValue (double, Bucket&);
  };
}
#endif // __RMOL_EMSRUTILS_HPP
