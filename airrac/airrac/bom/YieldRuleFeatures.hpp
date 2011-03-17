#ifndef __AIRRAC_BOM_YIELDRULEFEATURES_HPP
#define __AIRRAC_BOM_YIELDRULEFEATURES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/stdair_date_time_types.hpp>
// AIRRAC
#include <airrac/bom/YieldRuleFeaturesKey.hpp>
#include <airrac/bom/YieldRuleFeaturesTypes.hpp>

// Forward declaration
namespace stdair {
  template <typename BOM> class FacBom;
  class FacBomManager;
}

namespace AIRRAC {

  /** Class representing the actual attributes for a yield-rule. */
  class YieldRuleFeatures : public stdair::BomAbstract {
    template <typename BOM> friend class stdair::FacBom;
    friend class stdair::FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef YieldRuleFeaturesKey Key_T;
  
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return _key.toString(); }

  public:
    // ////////// Getters ////////////
    const Key_T& getKey() const { return _key; }
    stdair::BomAbstract* const getParent() const { return _parent; }
    const  stdair::HolderMap_T& getHolderMap() const { return _holderMap; }
    
    /** Get the cabin. */
    const stdair::CabinCode_T& getCabinCode() const {
      return _key.getCabinCode();
    }
    
    /** Get the yield. */
    const stdair::Yield_T& getYield() const {
      return _key.getYield();
    }
    
  protected:
    /** Default constructors. */
    YieldRuleFeatures (const Key_T&);
    YieldRuleFeatures (const YieldRuleFeatures&);
    /** Destructor. */
    ~YieldRuleFeatures();

  protected:
    // Attributes
    Key_T _key;
    stdair::BomAbstract* _parent;
    stdair::HolderMap_T _holderMap;

  };

}
#endif // __AIRRAC_BOM_YIELDRULEFEATURES_HPP

