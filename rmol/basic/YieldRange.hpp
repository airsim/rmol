#ifndef __RMOL_BAS_YIELDRANGE_HPP
#define __RMOL_BAS_YIELDRANGE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// STDAIR
#include <stdair/basic/StructAbstract.hpp>

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
  struct YieldRange : public stdair::StructAbstract {
  public:
    /** Constructors. */
    YieldRange ();
    YieldRange (const YieldRange&);
    YieldRange (const double iUpperYield);
    YieldRange (const double iUpperYield, const double iAverageYield);
    YieldRange (const double iUpperYield, const double iAverageYield,
                const double iLowerYield);
    
    /** Constructors. */
    virtual ~YieldRange();
    
    // /////////// Getters ////////////
    /** Getter for the upper yield of the range. */
    double getUpperYield() const { return _upperYield; }
    /** Getter for the average yield of the range. */
    double getAverageYield() const { return _averageYield; }
    /** Getter for the lower yield of the range. */
    double getLowerYield() const { return _lowerYield; }
    
    // //////// Setters /////////
    /** Setter for the upper yield of the range. */
    void setUpperYield (const double iUpperYield) {
      _upperYield = iUpperYield;
    }
    /** Setter for the average yield of the range. */
    void setAverageYield (const double iAverageYield) {
      _averageYield = iAverageYield;
    }
    /** Setter for the lower yield of the range. */
    void setLowerYield (const double iLowerYield) {
      _lowerYield = iLowerYield;
    }
    
    // ///////// Display methods ////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream&) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream&);

    /** Display demand distribution */
    const std::string describe() const;
    
  private:
    // ////////// Attributes /////////
    /** Upper yield. */
    double _upperYield;

    /** Average yield. */
    double _averageYield;

    /** Lower yield (most often, not used). */
    double _lowerYield;
  };
}
#endif // __RMOL_BAS_YIELDRANGE_HPP
