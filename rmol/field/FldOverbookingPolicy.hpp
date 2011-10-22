#ifndef __RMOL_FIELD_FLDOVERBOOKING_POLICY_HPP
#define __RMOL_FIELD_FLDOVERBOOKING_POLICY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// RMOL
#include <rmol/field/FldAbstract.hpp>

namespace RMOL {

  /** Class wrapping the policy for the overbooking calculation. */
  class FldOverbookingPolicy : public FldAbstract {
  public:
    typedef enum {
      HEUR = 0,    // Heuristic
      RISK,        // Risk-Based
      SL1,         // Service-Level 1
      SL2,         // Service-Level 2
      HYBRID,      // Hybrid
      LAST_VALUE
    } EN_Policy;

    /** Get the label (BOM type) as a string. */
    static const std::string& getLabel (const EN_Policy&);
    
    // Getters
    /** Getter for the mean value. */
    EN_Policy getPolicy() const {
      return _policy;
    }
    
    // Setters
    /** Setter for the mean value. */
    void setPolicy (const EN_Policy& iPolicy) {
      _policy = iPolicy;
    }
    

    /** Constructors. */
    FldOverbookingPolicy (const FldOverbookingPolicy&);
    FldOverbookingPolicy (const EN_Policy iPolicy = HEUR);

    /** Destructors. */
    virtual ~FldOverbookingPolicy();


    // ///////// Display methods ////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream&) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream&);

    
  private:
    // ///////// Attributes //////////
    /** Overbooking Calculation Policy. */
    EN_Policy _policy;

    /** Labels for the policy enumeration (for nice output reason). */
    static const std::string _labels[LAST_VALUE];
  };
}
#endif // __RMOL_FIELD_FLDOVERBOOKING_POLICY_HPP
