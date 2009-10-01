#ifndef __STDAIR_BOM_BOMCHILDRENHOLDER_HPP
#define __STDAIR_BOM_BOMCHILDRENHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <vector>
#include <string>
#include <map>
//STDAIR 
#include <stdair/bom/BomStructure.hpp>

namespace stdair {
  
  /** Class aimed at holding a list and a map of children BOM
      structure of a dedicated type. */
  class BomChildrenHolder : public BomStructure {
    friend class FacBomStructure;
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return std::string (""); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return std::string (""); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return std::string (""); }

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomChildrenHolder () { }
    BomChildrenHolder (const BomChildrenHolder&);

    /** Destructor. */
    ~BomChildrenHolder() { }
    
  };
  
}
#endif // __STDAIR_BOM_BOMCHILDRENHOLDER_HPP

