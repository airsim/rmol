#ifndef __RMOL_FLDYIELDRANGE_HPP
#define __RMOL_FLDYIELDRANGE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////


namespace RMOL {

  /** Class representing a range of yields.
      <br>Typically, bookings are priced according to rules (e.g., fare rules),
      leading to slight variations of revenues for a given product.
      The "yield range" captures the extent of revenues earned for a given
      product.
      <br>When no average and lower yields are defined, they are assumed 
      to be equal to the upper yield.
      <br>Note that the lower yield is generally not defined, as it
      corresponds to the upper yield of the lower yield range.
  */
  class FldYieldRange {
  public:
    /** Constructors. */
    FldYieldRange ();
    FldYieldRange (const FldYieldRange&);
    FldYieldRange (const double iUpperYield);
    FldYieldRange (const double iUpperYield, const double iAverageYield);
    FldYieldRange (const double iUpperYield, const double iAverageYield,
		   const double iLowerYield);
    
    /** Constructors. */
    virtual ~FldYieldRange();
    
    // Getters
    /** Getter for the upper yield of the range. */
    double getUpperYield() const {
      return _upperYield;
    }
    /** Getter for the average yield of the range. */
    double getAverageYield() const {
      return _averageYield;
    }
    /** Getter for the lower yield of the range. */
    double getLowerYield() const {
      return _lowerYield;
    }
    
  private:
    /** Upper yield. */
    double _upperYield;

    /** Average yield. */
    double _averageYield;

    /** Lower yield (most often, not used). */
    double _lowerYield;
  };
}
#endif // __RMOL_FLDYIELDRANGE_HPP
