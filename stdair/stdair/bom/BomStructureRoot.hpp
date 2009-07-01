#ifndef __STDAIR_BOM_BOMSTRUCTUREROOT_HPP
#define __STDAIR_BOM_BOMSTRUCTUREROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/BomStructureRootKey.hpp>
#include <stdair/bom/InventoryList.hpp>

namespace stdair {

  // Forward declaration
  //
  
  /** Wrapper class aimed at holding the actual content, modeled
      by a specific BomContentRoot class. */
  class BomStructureRoot : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;

  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BomStructureRootKey BomKey_T;

    /** Definition allowing to retrieve the associated children BOM type. */
    typedef InventoryList_T ChildrenBomList_T;
    
  public:

    // /////////// Getters /////////////
    /** Get the BomStructureRoot key. */
    const BomKey_T& getKey() const {
      return _key;
    }

    /** Get the list of inventories. */
    const ChildrenBomList_T& getInventoryList() const {
      return _childrenList;
    }
    

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomStructureRoot ();
    BomStructureRoot (const BomStructureRoot&);
    BomStructureRoot (const BomKey_T&);

    /** Destructor. */
    virtual ~BomStructureRoot();

  private:
    // Attributes
    /** The key of both the structure and content objects. */
    BomKey_T _key;
    
    /** List of inventories. */
    ChildrenBomList_T _childrenList;
  };

}
#endif // __STDAIR_BOM_BOMSTRUCTUREROOT_HPP

