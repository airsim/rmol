#ifndef __INTRUSIVE_BOM_LEGDATE_HPP
#define __INTRUSIVE_BOM_LEGDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
// 
#include <test/archi_intru/BomAbstract.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

namespace stdair {

  /** LegDate. */
  class LegDate : public BomAbstract {
  public:
    LegDate (const std::string& iKey) : BomAbstract (iKey)  {}
    LegDate (const int idx) : BomAbstract (idx) {}
  private:
    /** Default constructors.
        <br>They are kept private, so as to forbid their use (only the
        public constructors should be used). */
    LegDate () {}
    LegDate (const LegDate&) {}

  public:
    bi::list_member_hook<> _childHook;
    bi::list_member_hook<> _siblingHook;

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

  /** List of child-type LegDate objects. */
  typedef bi::member_hook <LegDate, bi::list_member_hook<>,
                           &LegDate::_childHook> LegDateChildMemberOption;
  typedef bi::list<LegDate, LegDateChildMemberOption> LegDateChildren;

  /** List of sibling-type LegDate objects. */
  typedef bi::member_hook <LegDate, bi::list_member_hook<>,
                           &LegDate::_siblingHook> LegDateSiblingMemberOption;
  typedef bi::list<LegDate, LegDateSiblingMemberOption> LegDateSiblings;

}
#endif // __INTRUSIVE_BOM_LEGDATE_HPP
