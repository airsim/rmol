#ifndef __STDAIR_BOM_YIELDSTORE_HPP
#define __STDAIR_BOM_YIELDSTORE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/YieldStoreKey.hpp>
#include <stdair/bom/YieldStoreTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline YieldStore. */
  class YieldStore : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;

  public :
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef YieldStoreKey Key_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the key. */
    const std::string describeKey() const { return _key.toString(); }

  public:
    // ////////// Getters ////////////
    /** Get the YieldStore key. */
    const Key_T& getKey() const { return _key; }

    /** Get the airline code. */
    const AirlineCode_T& getAirlineCode () const {
      return _key.getAirlineCode();
    }
    
  protected:
    /** Default constructors. */
    YieldStore (const Key_T&);
    YieldStore (const YieldStore&);
    /** Destructor. */
    ~YieldStore();

  protected:
    // Attributes
    /** The key of both structure and  objects. */
    Key_T _key;
    BomAbstract* _parent;
  };

}
#endif // __STDAIR_BOM_YIELDSTORE_HPP

