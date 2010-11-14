#ifndef __MYPROVIDER_BOMHOLDER_HPP
#define __MYPROVIDER_BOMHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <list>
// StdAir 
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BomRootKey.hpp>

namespace myprovider {
  /** Class representing the holders of BOM. */
  template <typename BOM>
  class BomHolder : public stdair::BomAbstract {
    template <typename> friend class FacBom;
    friend class BomManager;
    
  public:
    typedef stdair::BomRootKey Key_T;
    // Definition of diffrent container types.
    typedef std::list<BOM*> BomList_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return ""; }
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return ""; }
    
  protected:
    /** Default constructors. */
    BomHolder ();
    BomHolder (const BomHolder&);
    BomHolder (const Key_T& iKey) : _key (iKey) { }
    /** Destructor. */
    ~BomHolder() { };

  public:
    // Attributes
    Key_T _key;
    BomList_T _bomList;
  };
  
}  
#endif // __MYPROVIDER_BOMHOLDER_HPP
