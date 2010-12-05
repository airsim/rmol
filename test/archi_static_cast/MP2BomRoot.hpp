#ifndef __MYPROVIDER_BOMROOT_HPP
#define __MYPROVIDER_BOMROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
// StdAir 
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BomRootKey.hpp>
// Aichi TEST
#include <test/archi_static_cast/MP2Types.hpp>

namespace myprovider {
  
  /** Class representing the actual attributes for the Bom root. */
  class BomRoot : public stdair::BomAbstract {
    template <typename BOM> friend class FacBom;
    class FacBomManager;
    class BomManager;
    
  public:
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef stdair::BomRootKey Key_T;

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

  public:
    // Attributes
    /** The key of both structure and  objects. */
    Key_T _key;

    /** The list of children holders. */
    HolderMap_T _holderMap;
  };
  
}  
#endif // __MYPROVIDER_BOMROOT_HPP
