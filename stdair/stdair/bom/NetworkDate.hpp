#ifndef __STDAIR_BOM_NETWORKDATE_HPP
#define __STDAIR_BOM_NETWORKDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/NetworkDateContent.hpp>
#include <stdair/bom/NetworkDateTypes.hpp>
#include <stdair/bom/AirportDateTypes.hpp>

namespace stdair {
  // Forward declarations
  class Network;
  class AirportDate;
  
  /** Class representing the actual functional/business content for
      a network-date. */
  class NetworkDate : public NetworkDateContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef NetworkDateStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef Network Parent_T;

    /** Define the list of children holder types. */
    typedef boost::fusion::map<
      boost::fusion::pair<AirportDate, AirportDateHolder_T*>
      > ChildrenHolderMap_T;
    // //////////////////////////////////////////////////////////////////

  public:
    // /////////// Getters /////////////
    /** Get a list or map of a children type for iteration methods. */
    AirportDateList_T getAirportDateList () const;
    AirportDateMap_T getAirportDateMap () const;

    /** Retrieve, if existing, the AirportDate corresponding to the
        given airport-code.
        <br>If not existing, return the NULL pointer. */
    AirportDate* getAirportDate (const AirportCode_T&) const;

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
    
  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    NetworkDate (const Key_T&, Structure_T&);
    /** Destructor. */
    ~NetworkDate();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    NetworkDate ();
    NetworkDate (const NetworkDate&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;

  };

}
#endif // __STDAIR_BOM_NETWORKDATE_HPP

