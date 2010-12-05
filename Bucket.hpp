#ifndef __RMOL_BUCKET_HPP
#define __RMOL_BUCKET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include "FldYieldRange.hpp"
#include "FldDemand.hpp"

namespace RMOL {

  /** Class counting the number of seats sold for a given yield range,
      and the characteristics of the corresponding demand.

      Usually, a bucket corresponds to booking/reservation/fare class,
      and is defined by a yield range on a given resource (like, e.g.,
      the cabin of a given flight-date). */
  class Bucket {
  public:
    /** Constructors. */
    Bucket ();
    Bucket (const Bucket&);
    Bucket (const FldYieldRange&, const FldDemand&);
    
    // Getters
    /** Getter for the yield range. */
    FldYieldRange getYieldRange() const {
      return _yieldRange;
    }
    /** Getter for the demand. */
    FldDemand getDemand() const {
      return _demand;
    }

    /** Destructors. */
    virtual ~Bucket();

  private:
    const FldYieldRange _yieldRange;
    const FldDemand _demand;
  };
}
#endif
