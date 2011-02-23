#ifndef __RMOL_BOM_DEMAND_HPP
#define __RMOL_BOM_DEMAND_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// STDAIR
#include <stdair/basic/StructAbstract.hpp>
// RMOL
#include <rmol/basic/DistributionParameters.hpp>
#include <rmol/basic/YieldRange.hpp>

namespace RMOL {

  /** Class modelling the demand. It holds:
      - Demand parameters: mean and standard deviation.
      - Yield range: upper yield and average yield. */
  struct Demand : public stdair::StructAbstract {
    
  public:
    // ///////// Getters ////////
    /** Getter for the demand distribution parmaters (i.e., mean and
        standard deviation). */
    const DistributionParameters& getDistributionParameters() const {
      return _distributionParameters;
    }

    /** Getter for the average yield per unit of demand. */
    const YieldRange& getYieldRange() const { return _yieldRange; }
    
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

    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describe() const;

  public:
    /** Constructors.
	<br>Protected to force the use of the Factory. */
    Demand ();
    Demand (const Demand&);
    Demand (const DistributionParameters&, const YieldRange&);
    /** Destructors. */
    ~Demand();

  private:
    /** Yield range, i.e., upper and lower yields, as well as average yield
        (average revenue per unit of demand). */
    YieldRange _yieldRange;

    /** Distribution parameters (i.e., mean and standard deviation). */
    DistributionParameters _distributionParameters;
  };
}
#endif // __RMOL_BOM_DEMAND_HPP
