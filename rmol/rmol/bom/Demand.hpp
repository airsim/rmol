#ifndef __RMOL_BOM_DEMAND_HPP
#define __RMOL_BOM_DEMAND_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/field/FldDistributionParameters.hpp>
#include <rmol/field/FldYieldRange.hpp>
#include <rmol/bom/BomAbstract.hpp>

namespace RMOL {

  /** Class modelling the demand. It holds:
      - Demand parameters: mean and standard deviation.
      - Yield range: upper yield and average yield. */
  class Demand : public BomAbstract {
    /** Friend Classes
        <br>Those classes need to access the internal attributes of this object
        in order to construct and initialise it.*/
    friend class FacDemand;
    
  public:
    // ///////// Getters ////////
    /** Getter for the demand distribution parmaters (i.e., mean and
        standard deviation). */
    const FldDistributionParameters& getDistributionParameters() const {
      return _distributionParameters;
    }
    /** Getter for the average yield per unit of demand. */
    const FldYieldRange& getYieldRange() const {
      return _yieldRange;
    }
    
    /** Getter for the upper yield of the range. */
    double getUpperYield() const;
    
    /** Getter for the average yield of the range. */
    double getAverageYield() const;
    
    /** Getter for the lower yield of the range. */
    double getLowerYield();
    
    /** Getter for the mean value. */
    double getMean() const;
    
    /** Getter for the standard deviation value. */
    double getStandardDeviation() const;
    
    /** Getter for the variance value. */
    double getVariance() const;

    
    // ///////// Setters ////////
    /** Set the mean value. */
    void setMean (const double);

    /** set the standard deviation. */
    void setSD (const double);

    
  public:
    // ///////// Display methods ////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream&) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream&);

    /** Get the serialised version of the Place object. */
    std::string toString() const;

    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;
    
    /** Display the full Place context. */
    const std::string display() const;

    /** Display a short Place context. */
    const std::string shortDisplay() const;

  private:
    /** Constructors.
	<br>Protected to force the use of the Factory. */
    Demand ();
    Demand (const Demand&);
    Demand (const FldDistributionParameters&, const FldYieldRange&);
    /** Destructors. */
    ~Demand();

  private:
    /** Yield range, i.e., upper and lower yields, as well as average yield
        (average revenue per unit of demand). */
    FldYieldRange _yieldRange;

    /** Distribution parameters (i.e., mean and standard deviation). */
    FldDistributionParameters _distributionParameters;
  };
}
#endif // __RMOL_BOM_DEMAND_HPP
