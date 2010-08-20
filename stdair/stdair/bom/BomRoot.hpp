#ifndef __STDAIR_BOM_BOMROOT_HPP
#define __STDAIR_BOM_BOMROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BomRootKey.hpp>

namespace stdair {
  /** Class representing the actual attributes for the Bom root. */
  class BomRoot : public BomAbstract {
    template <typename BOM> friend class FacBom;
    
  public:
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BomRootKey Key_T;

  public:
    // /////////// Getters //////////////
    /** Get the BomRoot key. */
    const Key_T& getKey() const {
      return _key;
    }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return _key.toString(); }
    
  protected:
    /** Default constructors. */
    BomRoot ();
    BomRoot (const BomRoot&);
    BomRoot (const Key_T& iKey);
    /** Destructor. */
    ~BomRoot();

  protected:
    // Attributes
    /** The key of both structure and  objects. */
    Key_T _key; 
  };

}
#endif // __STDAIR_BOM_BOMROOT_HPP
