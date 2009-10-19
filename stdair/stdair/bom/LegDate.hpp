#ifndef __STDAIR_BOM_LEGDATE_HPP
#define __STDAIR_BOM_LEGDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/LegDateContent.hpp>
#include <stdair/bom/LegDateTypes.hpp>
#include <stdair/bom/LegCabinTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  class FlightDate;
  struct LegCabinList_T;
  struct LegCabinMap_T;

  /** Class representing the actual functional/business content for a
      leg-date. */
  class LegDate : public LegDateContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef FlightDate Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef LegDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef LegDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef LegCabin ContentChild_T;
    
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
    /** Get a LegCabinList_T for iteration methods. */
    LegCabinList_T getLegCabinList () const;

    /** Get a LegCabinMap_T for iteration methods. */
    LegCabinMap_T getLegCabinMap () const;

  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _legDateStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    LegDate ();
    LegDate (const LegDate&);
    LegDate (BomStructure_T&);

    /** Destructor. */
    virtual ~LegDate();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _legDateStructure;
  };

}
#endif // __STDAIR_BOM_LEGDATE_HPP

