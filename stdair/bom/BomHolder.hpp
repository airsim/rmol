#ifndef __STDAIR_BOM_BOMHOLDER_HPP
#define __STDAIR_BOM_BOMHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <list>
#include <map>
// StdAir 
#include <stdair/bom/key_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BomHolderKey.hpp>

namespace stdair {
  
  /** Class representing the holders of BOM. */
  template <typename BOM>
  class BomHolder : public stdair::BomAbstract {
    template <typename> friend class FacBom;
    friend class FacBomManager;
    
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */    
    typedef stdair::BomHolderKey Key_T;
    
    // Definition of diffrent container types.
    typedef std::list<BOM*> BomList_T;
    typedef std::map<const MapKey_T, BOM*> BomMap_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return ""; }
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return ""; }
    
  protected:
    /** Default constructors. */
    BomHolder ();
    BomHolder (const BomHolder&);
    BomHolder (const Key_T& iKey) : _key (iKey) { }
    /** Destructor. */
    ~BomHolder() { };

  public:
    // Attributes
    Key_T _key;
    BomList_T _bomList;
    BomMap_T _bomMap;
  };
  
}  
#endif // __STDAIR_BOM_BOMHOLDER_HPP
