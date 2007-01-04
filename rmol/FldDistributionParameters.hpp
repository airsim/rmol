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
    
    // Setters
    /** Setter for the mean value. */
    void setMean (const double iMean) {
      _mean = iMean;
    }
    /** Setter for the standard deviation value. */
    void setStandardDeviation (const double iStandardDeviation) {
      _standardDeviation = iStandardDeviation;
    }
    
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
