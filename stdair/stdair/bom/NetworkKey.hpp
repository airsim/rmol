#ifndef __STDAIR_BOM_NETWORKKEY_HPP
#define __STDAIR_BOM_NETWORKKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/BomRootKey.hpp>

namespace stdair {
  /** Key of network. */
  struct NetworkKey_T : public BomKey_T {
    friend struct NetworkDateKey_T;

  public:
    // /////////// Typedefs ////////////
    /** Definition allowing to retrieve the parent key type. */
    typedef BomRootKey_T ParentKey_T;
    
  private:
    // /////////// Default constructor //////////
    NetworkKey_T () { };
    
  public:
    // /////////// Construction ///////////
    /** Constructors. */
    NetworkKey_T (const NetworkID_T& iNetworkID);
    NetworkKey_T (const NetworkKey_T&);

    /** Destructor. */
    ~NetworkKey_T ();
    
    // /////////// Getters //////////
    /** Get the network ID. */
    const NetworkID_T& getNetworkID() const;

    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;
    
    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);
      
   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-date. */
    const std::string toString() const;

    /** Display of the key. */
    const std::string describe() const;

    // /////////// Setters /////////////
    /** Set the parent key. */
    void setParentKey (const ParentKey_T& iParentKey) const { }

  private:
    // Attributes
    /** Network ID. */
    NetworkID_T _networkID;
  };

}
#endif // __STDAIR_BOM_NETWORKKEY_HPP
