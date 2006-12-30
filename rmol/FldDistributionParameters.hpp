#ifndef __RMOL_FLDDISTRIBUTIONPARAMETERS_HPP
#define __RMOL_FLDDISTRIBUTIONPARAMETERS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////


namespace RMOL {

  /** Class wrapping the parameters of a distribution:
      mean and standard deviation. */
  class FldDistributionParameters {
  public:
    /** Constructors. */
    FldDistributionParameters ();
    FldDistributionParameters (const FldDistributionParameters&);
    FldDistributionParameters (const double iMean,
                               const double iStandardDeviation);

    // Getters
    /** Getter for the mean value. */
    double getMean() const {
      return _mean;
    }
    /** Getter for the standard deviation value. */
    double getStandardDeviation() const {
      return _standardDeviation;
    }
    /** Getter for the variance value. */
    double getVariance() const;
    
    /** Destructors. */
    virtual ~FldDistributionParameters();
    
  private:
    /** Mean. */
    double _mean;
    
    /** Standard Deviation.
        Note that the variance is defined as the square of
        the standard deviation. */
    double _standardDeviation;

  };
}
#endif
