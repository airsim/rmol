#ifndef __STDAIR_BOM_INVENTORY_HPP
#define __STDAIR_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/InventoryContent.hpp>
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/bom/FlightDateTypes.hpp>

namespace stdair {
  // Forward declarations
  class BomRoot;
  class FlightDate;
  class AirlineFeature;
  struct FlightDateKey_T;
  
  /** Class representing the actual functional/business content for
      an airline inventory. */
  class Inventory : public InventoryContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef InventoryStructure_T Structure_T;
    
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef BomRoot Parent_T;

    /** Define the list of children holder types. */
    typedef boost::fusion::map<
      boost::fusion::pair<FlightDate, FlightDateHolder_T*>
      > ChildrenHolderMap_T;
    // //////////////////////////////////////////////////////////////////

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

  public:
    // /////////// Getters /////////////
    /** Get a list or map of a children type for iteration methods. */
    FlightDateList_T getFlightDateList () const;
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

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    Inventory (const Key_T&, Structure_T&);
    /** Destructor. */
    ~Inventory();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    Inventory ();
    Inventory (const Inventory&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
    
    /** The feature set of the correspondent airline. */
    const AirlineFeature* _airlineFeature;
  };

}
#endif // __STDAIR_BOM_INVENTORY_HPP

