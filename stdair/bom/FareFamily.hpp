#ifndef __STDAIR_BOM_FAREFAMILY_HPP
#define __STDAIR_BOM_FAREFAMILY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/FareFamilyKey.hpp>
#include <stdair/bom/FareFamilyTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for a family fare. */
  class FareFamily : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FareFamilyKey Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the family fare key. */
    const Key_T& getKey() const { return _key; }
    
    /** Get the family fare code (part of the primary key). */
    const FamilyCode_T& getFamilyCode() const { return _key.getFamilyCode(); }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const { return _holderMap; }

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
    
    /** Get a string describing the key. */
    const std::string describeKey() const { return _key.toString(); }

  protected:
    /** Default constructors. */
    FareFamily (const Key_T&);
    FareFamily (const FareFamily&);
    /** Destructor. */
    ~FareFamily();

  public:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;
    
  };

}
#endif // __STDAIR_BOM_FAREFAMILY_HPP

