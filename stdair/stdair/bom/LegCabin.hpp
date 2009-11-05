#ifndef __STDAIR_BOM_LEGCABIN_HPP
#define __STDAIR_BOM_LEGCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabinStructure.hpp>
#include <stdair/bom/LegCabinContent.hpp>
#include <stdair/bom/LegCabinTypes.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct LegCabinKey_T;
  
  /** Class representing the actual functional/business content for a
      leg-date. */
  class LegCabin : public LegCabinContent {
    friend class FacBomContent;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef LegDate Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef LegCabinStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef LegCabinKey_T BomKey_T;

  public:
//     // ////// Getters from the parent class ///////
//     /** Get the airline code (from the LegDate parent). */
//     const AirlineCode_T& getAirlineCode() const;
      
//     /** Get the flight number (from the LegDate parent). */
//     const FlightNumber_T& getFlightNumber() const;

//     /** Get the flight-date (from the LegDate parent). */
//     const Date_T& getFlightDateDate() const;
      
//     /** Get the board point (from the LegDate parent). */
//     const AirportCode_T& getBoardPoint () const;

//     /** Get the off point (from the LegDate parent). */
//     const AirportCode_T& getOffPoint () const;

//     /** Get the distance. */
//     const Distance_T& getDistance() const;

//     /** Get the board date (from the LegDate parent). */
//     const Date_T& getBoardDate () const;

//     /** Get the board time (from the LegDate parent). */
//     const Duration_T& getBoardTime () const;

//     /** Get the off date (from the LegDate parent). */
//     const Date_T& getOffDate () const;

//     /** Get the off time (from the LegDate parent). */
//     const Duration_T& getOffTime () const;

  public:
    // ///////// Setters //////////
    /** Set the off cabin. */
    void setCapacity (const CabinCapacity_T&, const AnalysisStatus_T&);

//     /** Reset the sold seat counter to its initial state. */
//     void reset();
    
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
    
//     /** Display the full LegCabin context. */
//     const std::string display() const;
    
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _legCabinStructure;
    }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    LegCabin ();
    LegCabin (const LegCabin&);
    LegCabin (const BomKey_T& iKey, BomStructure_T&);

    /** Destructor. */
    virtual ~LegCabin();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _legCabinStructure;
    
    /** List of crossing SegmentCabin objects. */
    //SegmentCabinMap_T _segmentCabinList;
  };

}
#endif // __STDAIR_BOM_LEGCABIN_HPP

