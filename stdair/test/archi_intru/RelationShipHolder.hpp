#ifndef __INTRUSIVE_BOM_RELATIONSHIPHOLDER_HPP
#define __INTRUSIVE_BOM_RELATIONSHIPHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Local
#include <test/archi_intru/RelationShipHolderAbstract.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

namespace stdair {

  /** Class holding relationship objects between either a parent Bom and its
      children or a Bom object and its siblings. */
  template <typename FIRST_BOM, typename SECOND_BOM>
  class RelationShipHolder : public RelationShipHolderAbstract {
  public:
    // ///////////////////////////////////////////
    /** Type definition for a list of either children or siblings. */
    typedef bi::member_hook <SECOND_BOM,
                             bi::list_member_hook<>,
                             &SECOND_BOM::_childListHook> SecondBomListMemberOption;
    typedef bi::list<SECOND_BOM, SecondBomListMemberOption> SecondBomList_T;
    // ///////////////////////////////////////////
    
  public:
    RelationShipHolder (FIRST_BOM& ioFirstBom, SECOND_BOM& ioSecondBom)
      : _firstBom (ioFirstBom) {
    }
    
  public:
    bi::list_member_hook<> _childListHook;
    bi::set_member_hook<> _childSetHook;
    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) {}

    /** Get the serialised version of the Business Object. */
    std::string toString() const { return _key; };
    
  private:
    /** Relationship, holding a list of children or siblings for a
        given parent/Bom object. */
    FIRST_BOM& _firstBom;
    SecondBomList_T _secondBomList;
  };

}
#endif // __INTRUSIVE_BOM_RELATIONSHIPHOLDER_HPP
