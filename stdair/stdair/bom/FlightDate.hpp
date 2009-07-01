#ifndef __STDAIR_BOM_FLIGHTDATE_HPP
#define __STDAIR_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/FlightDateKey.hpp>
#include <stdair/bom/BomStructureList.hpp>

namespace stdair {

  // Forward declaration
  class Inventory;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by an external specific FlightDate class (for instance,
      in the AIRSCHED library). */
  class FlightDate : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;

  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey BomKey_T;

    /** Definition allowing to retrieve the associated parent
        BOM structure type. */
    typedef Inventory ParentBomStructure_T;

    /** Definition allowing to retrieve the associated children BOM type. */
    typedef BomStructureList_T ChildrenBomList_T;

  public:
    // /////////// Getters /////////////
    /** Get the (parent) Inventory object. */
    ParentBomStructure_T* getInventoryPtr() const {
      return _parent;
    }
    
    /** Get the (parent) Inventory object. */
    ParentBomStructure_T& getInventory() const;
    
    /** Get the flight-date key. */
    const BomKey_T& getKey() const {
      return _key;
    }

    /** Get the list of leg-dates and segment-dates. */
    const BomStructureList_T& getChildrenList() const {
      return _childrenList;
    }
    
  private:
    // /////////// Setters /////////////
    /** Set the (parent) FlightDate object. */
    void setBomStructureRoot (ParentBomStructure_T& ioParent) {
      _parent = &ioParent;
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
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (const BomKey_T&);

    /** Destructor. */
    virtual ~FlightDate();

  private:
    // Attributes
    /** Parent root. */
    ParentBomStructure_T* _parent;

    /** The key of both the structure and content objects. */
    BomKey_T _key;
    
    /** List of leg-dates and segment-dates. */
    BomStructureList_T _childrenList;
  };

}
#endif // __STDAIR_BOM_FLIGHTDATE_HPP

