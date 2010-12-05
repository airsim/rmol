#ifndef __INTRUSIVE_BOM_BOMROOT_HPP
#define __INTRUSIVE_BOM_BOMROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
// Boost.Intrusive
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/set.hpp>
// Local
#include <test/archi_intru/BomAbstract.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

namespace stdair {

  /** BomRoot. */
  class BomRoot : public BomAbstract {
    template <typename BOM> friend class FacBom;
    template <typename NODE> friend struct delete_disposer;
  public:
    /** Constructors. */
    BomRoot (const std::string& iKey) : BomAbstract (iKey)  {}
    BomRoot (const int idx) : BomAbstract (idx) {}
  private:
    /** Default constructors.
        <br>They are kept private, so as to forbid their use (only the
        public constructors should be used). */
    BomRoot () {}
    BomRoot (const BomRoot&) {}
    /** Destructor. */
    ~BomRoot() {}

  public:
    bi::list_member_hook<> _childListHook;
    bi::set_member_hook<> _childSetHook;

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
