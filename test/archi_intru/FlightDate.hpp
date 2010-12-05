#ifndef __INTRUSIVE_BOM_FLIGHTDATE_HPP
#define __INTRUSIVE_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// Boost.Intrusive
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/set.hpp>
// Local
#include <test/archi_intru/BomAbstract.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

namespace stdair {

  /** FlightDate. */
  class FlightDate : public BomAbstract {
    template <typename BOM> friend class FacBom;
    template <typename NODE> friend struct delete_disposer;
  public:
    /** Constructors. */
    FlightDate (const std::string& iKey) : BomAbstract (iKey)  {}
    FlightDate (const int idx) : BomAbstract (idx) {}
    /** Destructor.
        <br>Note: it should be private, but there is still a compilation bug. */
    ~FlightDate() {}
  private:
    /** Default constructors.
        <br>They are kept private, so as to forbid their use (only the
        public constructors should be used). */
    FlightDate () {}
    FlightDate (const FlightDate&) {}

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
  
  // ///////////////// Type definitions /////////////
  /** Standard (STL) list (vector) of BOM FlightDate objects (pointers). */
  typedef std::vector<stdair::FlightDate*> FlightDateVector_T;

  /** (Boost.Intrusive) List of child-type FlightDate objects. */
  typedef bi::member_hook <FlightDate, bi::list_member_hook<>,
                           &FlightDate::_childListHook> FlightDateListMemberOption;
  typedef bi::list<FlightDate, FlightDateListMemberOption> FlightDateChildList;

  /** (Boost.Intrusive) Set of child-type FlightDate objects. */
  typedef bi::member_hook <FlightDate, bi::set_member_hook<>,
                           &FlightDate::_childSetHook> FlightDateSetMemberOption;
  typedef bi::set<FlightDate, FlightDateSetMemberOption> FlightDateChildSet;
  
}
#endif // __INTRUSIVE_BOM_FLIGHTDATE_HPP
