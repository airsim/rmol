#ifndef __STDAIR_BOM_NETWORK_HPP
#define __STDAIR_BOM_NETWORK_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/NetworkStructure.hpp>
#include <stdair/bom/NetworkTypes.hpp>
#include <stdair/bom/NetworkDateTypes.hpp>
#include <stdair/bom/NetworkContent.hpp>

namespace stdair {
  // Forward declarations
  class FacBomContent;
  struct NetworkDateKey_T;
  struct NetworkKey_T;
  
  /** Class representing the actual functional/business content for
      a network. */
  class Network : public NetworkContent {
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
    typedef NetworkStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef NetworkKey_T BomKey_T;

    /** Definition allowing to retrieve the associated  BOM content child
        type. */
    typedef NetworkDate ContentChild_T;
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
    /** Get a NetworkDateList_T for iteration methods. */
    NetworkDateList_T getNetworkDateList () const;

    /** Get a NetworkDateMap_T for iteration methods. */
    NetworkDateMap_T getNetworkDateMap () const;
    
    /** Retrieve, if existing, the NetworkDate corresponding to the
        given network number and network date (NetworkDate key).
        <br>If not existing, return the NULL pointer. */
    NetworkDate* getNetworkDate (const NetworkDateKey_T&) const;
 

  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _networkStructure;
    }
    

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    Network ();
    Network (const Network&);
    Network (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~Network();

  protected:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _networkStructure;
  };

}
#endif // __STDAIR_BOM_NETWORK_HPP

