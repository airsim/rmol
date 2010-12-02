#ifndef __STDAIR_BOM_INVENTORY_HPP
#define __STDAIR_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/InventoryKey.hpp>
#include <stdair/bom/InventoryTypes.hpp>

namespace stdair {
  // Forward declarations.
  class AirlineFeature;
  
  /**
   * @brief Class representing the actual attributes for an airline inventory
   */
  class Inventory : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public :
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef InventoryKey Key_T;

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
    const AirlineCode_T& getAirlineCode() const { return _key.getAirlineCode();}
    BomAbstract* const getParent() const { return _parent; }
    const HolderMap_T& getHolderMap() const { return _holderMap; }
    
  public:
    // /////////// Setters ////////////
    /** Set the airline feature. */
    void setAirlineFeature (const AirlineFeature* ioAirlineFeaturePtr) {
      _airlineFeature = ioAirlineFeaturePtr;
    }

  protected:
    /** Default constructors. */
    Inventory (const Key_T&);
    Inventory (const Inventory&);
    /** Destructor. */
    ~Inventory();

  protected:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    const AirlineFeature* _airlineFeature;
    HolderMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_INVENTORY_HPP

