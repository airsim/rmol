#ifndef __STDAIR_BOM_NETWORKCONTENT_HPP
#define __STDAIR_BOM_NETWORKCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/NetworkKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline network. */
  class NetworkContent : public BomContent {
  public :
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef NetworkKey_T Key_T;

  public:
    // ////////// Getters ////////////
    /** Get the network key. */
    const Key_T& getKey() const {
      return _key;
    }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { _key.toString(); }

  protected:
    /** Default constructors. */
    NetworkContent (const Key_T&);
    NetworkContent (const NetworkContent&);
    /** Destructor. */
    virtual ~NetworkContent();

  protected:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;
  };

}
#endif // __STDAIR_BOM_NETWORKCONTENT_HPP

