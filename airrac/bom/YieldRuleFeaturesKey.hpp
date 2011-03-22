#ifndef __AIRRAC_BOM_YIELDRULEKEY_HPP
#define __AIRRAC_BOM_YIELDRULEKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// AIRRAC
#include <stdair/bom/KeyAbstract.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_date_time_types.hpp>

namespace AIRRAC  {
  /** Key of yield-rule. */
  struct YieldRuleFeaturesKey : public stdair::KeyAbstract {

  private:
    // /////////// Default constructor //////////
    YieldRuleFeaturesKey () { };
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    YieldRuleFeaturesKey (const stdair::CabinCode_T&, const stdair::Yield_T&);
    YieldRuleFeaturesKey (const YieldRuleFeaturesKey&);
    /** Destructor. */
    ~YieldRuleFeaturesKey ();

    /** Get the cabin. */
    const stdair::CabinCode_T& getCabinCode() const {
      return _cabinCode;
    }  

    /** Get the yield. */
    const stdair::Yield_T& getYield() const {
      return _yield;
    }
    
    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object. */
    const std::string toString() const;

  private:
    // Attributes
    /** Cabin code. */
    stdair::CabinCode_T _cabinCode;
 
    /** Yield value.*/
    stdair::Yield_T _yield;

  };

}
#endif // __AIRRAC_BOM_YIELDRULEKEY_HPP
