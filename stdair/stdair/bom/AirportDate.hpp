#ifndef __STDAIR_BOM_AIRPORTDATE_HPP
#define __STDAIR_BOM_AIRPORTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/AirportDateContent.hpp>
#include <stdair/bom/AirportDateTypes.hpp>
#include <stdair/bom/OutboundPathTypes.hpp>

namespace stdair {
  // Forward declarations
  class NetworkDate;
  class OutboundPath;

  /** Class representing the actual functional/business content for a
      airport-date. */
  class AirportDate : public AirportDateContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef AirportDateStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef NetworkDate Parent_T;

    /** Define the list of children holder types. */
    typedef boost::fusion::map<
      boost::fusion::pair<OutboundPath, OutboundPathHolder_T*>
      > ChildrenHolderMap_T;
    // //////////////////////////////////////////////////////////////////
    
  public:
    // /////////// Getters /////////////
    /** Get a list or map of a children type for iteration methods. */
    OutboundPathList_T getOutboundPathList () const;
    OutboundPathMap_T getOutboundPathMap () const;

    /** Get the OutboundPathListList. */
    const OutboundPathListList_T& getOutboundPathListList () const {
      return _outboundPathListList;
    }
    
  public:
    // //////////// Business Methods //////////////
    /** Build the list of lists of outbound paths. **/
    void buildOutboundPathListList (stdair::OutboundPath&);    
       
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
    AirportDate (const Key_T&, Structure_T&);
    /** Destructor. */
    virtual ~AirportDate();
    /** Default constructors. */
    AirportDate ();
    AirportDate (const AirportDate&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;

    /** The list of lists of OutboundPaths, used uniquement for the
        construction of the main list of OutboundPaths in
        AirportDateStructure. */
    OutboundPathListList_T _outboundPathListList;

  };

}
#endif // __STDAIR_BOM_AIRPORTDATE_HPP

