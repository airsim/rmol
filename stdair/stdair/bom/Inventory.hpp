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
  class AirlineFeature;
  class BookingClass;
  struct FlightDateKey_T;
  struct InventoryKey_T;
  
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

    /** Definition allowing to retrieve the specific BookingClass type. */
    typedef BookingClass BookingClassContent_T;
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
    
    /** Get the airline feature. */
    const AirlineFeature* getAirlineFeature () const {
      return _airlineFeature;
    }
    
    /** Retrieve, if existing, the FlightDate corresponding to the
        given flight number and flight date (FlightDate key).
        <br>If not existing, return the NULL pointer. */
    FlightDate* getFlightDate (const FlightDateKey_T&) const;
    
  public:
    // /////////// Setters ////////////
    /** Set the airline feature. */
    void setAirlineFeature (const AirlineFeature* ioAirlineFeaturePtr) {
      _airlineFeature = ioAirlineFeaturePtr;
    }

  public:
    // /////////// Business methods //////////
    /** Return the BookingClass corresponding to a given key.
        <br>When no BookingClass, matching the given key, can be found,
        the NULL pointer is returned.
        <br>Otherwise, a pointer is returned on the BookingClass object. */
    // BookingClass* getBookingClass (const std::string&) const;
    
    /** Clean the list of classes. */
   //  void cleanClassList();
    
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _inventoryStructure;
    }
    
    /** Retrieve, if existing, the FlightDate corresponding to the
        given FlightDate key (InventoryKey + flight number).
        <br>If not existing, return the NULL pointer.
        <br>Note that the string must be formed thanks to the
        FlightDateKey::describeShort() method, as that latter is used when
        inserting the FlightDate within the Inventory dedicated list. */
   //  FlightDate*
//     getFlightDateInternal (const std::string& iFlightDateKey) const;
    
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
    
    /** The feature set of the correspondent airline. */
    const AirlineFeature* _airlineFeature;
  };

}
#endif // __STDAIR_BOM_INVENTORY_HPP

