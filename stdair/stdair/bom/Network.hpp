#ifndef __STDAIR_BOM_NETWORK_HPP
#define __STDAIR_BOM_NETWORK_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Fusion
#if BOOST_VERSION >= 103500
#include <boost/fusion/include/map.hpp>
#else // BOOST_VERSION >= 103500
#include <boost/mpl/map.hpp>
#endif // BOOST_VERSION >= 103500
// StdAir 
#include <stdair/bom/NetworkContent.hpp>
#include <stdair/bom/NetworkTypes.hpp>
#include <stdair/bom/NetworkDateTypes.hpp>

namespace stdair {
  // Forward declarations
  class BomRoot;
  class NetworkDate;
  
  /** Class representing the actual functional/business content for
      a network. */
  class Network : public NetworkContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef NetworkStructure_T Structure_T;
    
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef BomRoot Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;

    /** Define the list of children holder types. */
#if BOOST_VERSION >= 103500
    typedef boost::fusion::map<
      boost::fusion::pair<NetworkDate, NetworkDateHolder_T*>
      > ChildrenHolderMap_T;
#else // BOOST_VERSION >= 103500
    typedef boost::mpl::map< > ChildrenHolderMap_T;
#endif // BOOST_VERSION >= 103500
    // //////////////////////////////////////////////////////////////////

  public:
    // /////////// Getters /////////////
    /** Get a list or map of a children type for iteration methods. */
    NetworkDateList_T getNetworkDateList () const;
    NetworkDateMap_T getNetworkDateMap () const;

    /** Retrieve, if existing, the NetworkDate corresponding to the
        given Date .
        <br>If not existing, return the NULL pointer. */
    NetworkDate* getNetworkDate (const Date_T&) const;

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
    Network (const Key_T&, Structure_T&);
    /** Destructor. */
    ~Network();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    Network ();
    Network (const Network&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_NETWORK_HPP

