#ifndef __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP
#define __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#include <vector>
// StdAir
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/BookingClassTypes.hpp>

namespace stdair {

  // Forward declarations
  class OutboundPath;
  
  /** Structure holding the elements of a travel solution. */
  struct TravelSolutionStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get the OutboundPath. */
    OutboundPath& getOutboundPath() const;

    /** Get the list of booking classes. */
    const BookingClassSTLList_T& getBookingClassList () const {
      return _bookingClassList;
    }

  public:
    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;

    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;

  
  public:
    // //////////// Constructors & Destructor ///////////////
    /** Main constructor. */
    TravelSolutionStruct (OutboundPath&, const BookingClassSTLList_T&);
    /** Destructor. */
    ~TravelSolutionStruct ();
    /** Default copy constructor. */
    TravelSolutionStruct (const TravelSolutionStruct&);
    /** Default constructor, not to be used. */
    TravelSolutionStruct ();
    
  private:
    // ///////////////////// Attributes //////////////////////
    /** The outbound path associated to this solution.*/
    OutboundPath* _outboundPath_ptr;

    /** The list of booking classes which make the travel solution. */
    BookingClassSTLList_T _bookingClassList;
  };

}
#endif // __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP
