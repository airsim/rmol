#ifndef __INTRUSIVE_BOM_BOMROOT_HPP
#define __INTRUSIVE_BOM_BOMROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
// 
#include <test/archi_intru/BomAbstract.hpp>

namespace stdair {

  /** BomRoot. */
  class BomRoot : public BomAbstract {
  public:
    BomRoot (const std::string& iKey) : BomAbstract (iKey)  {}
    BomRoot (const int idx) : BomAbstract (idx) {}

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

    /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return _key; }
  };

}
#endif // __INTRUSIVE_BOM_BOMROOT_HPP
