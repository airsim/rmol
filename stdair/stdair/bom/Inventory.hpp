#ifndef __STDAIR_BOM_INVENTORY_HPP
#define __STDAIR_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
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
    /** Get the inventory key. */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the airline code. */
    const AirlineCode_T& getAirlineCode () const {
      return _key.getAirlineCode();
    }
    
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
    /** The key of both structure and  objects. */
    Key_T _key;
    
    /** The feature set of the correspondent airline. */
    const AirlineFeature* _airlineFeature;
  };

}
#endif // __STDAIR_BOM_INVENTORY_HPP

