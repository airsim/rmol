#ifndef __MYPROVIDER_INVENTORY_HPP
#define __MYPROVIDER_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/InventoryKey.hpp>
// Archi TEST
#include <test/archi_static_cast/MP2Types.hpp>

namespace myprovider {

  class Inventory : public stdair::BomAbstract {
    template <typename BOM> friend class FacBom;
    class BomManager;

  public :
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef stdair::InventoryKey Key_T;

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
    const stdair::AirlineCode_T& getAirlineCode () const {
      return _key.getAirlineCode();
    }

  protected:
    /** Default constructors. */
    Inventory (const Key_T&);
    Inventory (const Inventory&);
    /** Destructor. */
    ~Inventory();

  public:
    // Attributes
    /** The key of both structure and  objects. */
    Key_T _key;

    /** The list of children holders. */
    HolderMap_T _holderMap;
  };
  
}
#endif // __MYPROVIDER_INVENTORY_HPP
