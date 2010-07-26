/**
 * @ingroup BomContent
 */
#ifndef __STDAIR_BOM_INVENTORYCONTENT_HPP
#define __STDAIR_BOM_INVENTORYCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/InventoryKey.hpp>

namespace stdair {

  /**
   * @brief Class representing the actual attributes for an airline inventory
   */
  class InventoryContent : public BomContent {
  public :
    
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef InventoryKey_T Key_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

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

  protected:
    /** Default constructors. */
    InventoryContent (const Key_T&);
    InventoryContent (const InventoryContent&);
    /** Destructor. */
    ~InventoryContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;
  };

}
#endif // __STDAIR_BOM_INVENTORYCONTENT_HPP

