#ifndef __INTRUSIVE_BOM_RELATIONSHIPHOLDER_HPP
#define __INTRUSIVE_BOM_RELATIONSHIPHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost.Intrusive
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/set.hpp>
// Local
#include <test/archi_intru/RelationShipHolderAbstract.hpp>
#include <test/archi_intru/IntrusiveHelper.hpp>

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
                             bi::set_member_hook<>,
                             &SECOND_BOM::_childSetHook> SecondBomSetMemberOption;
    typedef bi::set<SECOND_BOM, SecondBomSetMemberOption> SecondBomSet_T;
    // ///////////////////////////////////////////
    
  public:
    /** Key calculator. */
    static std::string keyCalculator (const std::string& iKey1,
                                      const std::string& iKey2) {
      return (iKey1 + "," + iKey2);
    }
    
    /** Constructor. */
    RelationShipHolder (FIRST_BOM& ioFirstBom, SECOND_BOM& ioSecondBom)
      : RelationShipHolderAbstract (keyCalculator (ioFirstBom.getKey(),
                                                   ioSecondBom.getKey())),
        _firstBom (ioFirstBom) {
    }
  private:
    /** Default constructors.
        <br>They are kept private, so as to forbid their use (only the
        public constructors should be used). */
    RelationShipHolder () {}
    RelationShipHolder (const RelationShipHolder&) {}
    /** Destructor. */
    ~RelationShipHolder() {}
    
  public:
    bi::list_member_hook<> _childListHook;
    bi::set_member_hook<> _childSetHook;

  public:
    /** Search for a child/sibling from the dedicated list of the
        parents/siblings. */
    SECOND_BOM* find (const std::string& iSecondBomKey) {
      SECOND_BOM* oSecondBom_ptr = NULL;
      
      typename SecondBomSet_T::iterator itSecondBom =
        _secondBomSet.find (iSecondBomKey, StrExpComp<SECOND_BOM>());
      if (itSecondBom == _secondBomSet.end()) {
        return oSecondBom_ptr;
      }
      oSecondBom_ptr = &*itSecondBom;

      return oSecondBom_ptr;
    }
    
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
    SecondBomSet_T _secondBomSet;
  };

}
#endif // __INTRUSIVE_BOM_RELATIONSHIPHOLDER_HPP
