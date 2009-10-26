#ifndef __STDAIR_BOM_INVENTORY_HPP
#define __STDAIR_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/InventoryStructure.hpp>
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/bom/FlightDateTypes.hpp>
#include <stdair/bom/InventoryContent.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct InventoryKey_T;
  struct FlightDateList_T;
  struct FlightDateMap_T;
  
  /** Class representing the actual functional/business content for
      an airline inventory. */
  class Inventory : public InventoryContent {
    friend class FacBomContent;

  public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef BomRoot Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef InventoryStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef InventoryKey_T BomKey_T;

    /** Definition allowing to retrieve the associated  BOM content child
        type. */
    typedef FlightDate ContentChild_T;
    // /////////////////////////////////////////////////////////////////////////

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

  public:
    // /////////// Getters /////////////
    /** Get a FlightDateList_T for iteration methods. */
    FlightDateList_T getFlightDateList () const;

    /** Get a FlightDateMap_T for iteration methods. */
    FlightDateMap_T getFlightDateMap () const;
    
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _inventoryStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    Inventory ();
    Inventory (const Inventory&);
    Inventory (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~Inventory();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _inventoryStructure;
  };

}
#endif // __STDAIR_BOM_INVENTORY_HPP

