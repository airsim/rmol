#ifndef __INTRUSIVE_BOM_RELATIONSHIPHOLDERSET_HPP
#define __INTRUSIVE_BOM_RELATIONSHIPHOLDERSET_HPP

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
#include <test/archi_intru/RelationShipHolder.hpp>
#include <test/archi_intru/IntrusiveHelper.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

namespace stdair {

  /** Class holding relationship objects between either a parent Bom and its
      children or a Bom object and its siblings. */
  template <typename FIRST_BOM, typename SECOND_BOM>
  class RelationShipHolderSet : public RelationShipHolderAbstract {
    template <typename ONE, typename SECOND> friend class FacRelationShipRoot;
  public:
    // ///////////////////////////////////////////
    /** Type definition for the specific relationship class. */
    typedef RelationShipHolder<FIRST_BOM, SECOND_BOM> RelationShipHolder_T;
  
    /** Type definition for a list of relationship objects. */
    typedef bi::member_hook <RelationShipHolder_T,
                             bi::list_member_hook<>,
                             &RelationShipHolder_T::_childListHook> RSHListMemberOption;
    typedef bi::list<RelationShipHolder_T,
                     RSHListMemberOption> RelationShipHolderList_T;

    /** Type definition for a set of relationship objects. */
    typedef bi::member_hook <RelationShipHolder_T,
                             bi::set_member_hook<>,
                             &RelationShipHolder_T::_childSetHook> RSHSetMemberOption;
    typedef bi::set<RelationShipHolder_T,
                    RSHSetMemberOption> RelationShipHolderSet_T;
    // ///////////////////////////////////////////

  public:
    /** Constructor. */
    RelationShipHolderSet (const std::string& iKey)
      : RelationShipHolderAbstract (iKey) {
    }
  private:
    /** Default constructors.
        <br>They are kept private, so as to forbid their use (only the
        public constructors should be used). */
    RelationShipHolderSet ()
      : RelationShipHolderAbstract ("RelationShipHolderSet") {}
    RelationShipHolderSet (const RelationShipHolderSet&) {}
    /** Destructor. */
    ~RelationShipHolderSet() {}
    
  public:
    bi::list_member_hook<> _childListHook;
    bi::set_member_hook<> _childSetHook;

  public:
    /** Add a child/sibling to the dedicated list of the parent/sibling. */
    void addToList (RelationShipHolder_T& ioRelationShipHolder) {
      _relationShipHolderList.push_back (ioRelationShipHolder);
      _relationShipHolderSet.insert (ioRelationShipHolder);
    }
    
    /** Search for a child/sibling from the dedicated list of the
        parents/siblings. */
    SECOND_BOM* find (const FIRST_BOM& iFirstBom,
                      const std::string& iSecondBomKey) {
      SECOND_BOM* oSecondBom_ptr = NULL;
      RelationShipHolder_T* oRSH_ptr = NULL;
      
      typename RelationShipHolderSet_T::iterator itRSH =
        _relationShipHolderSet.find (iFirstBom.getKey(), StrExpComp<RelationShipHolder_T>());
      if (itRSH == _relationShipHolderSet.end()) {
        return oSecondBom_ptr;
      }
      oRSH_ptr = &*itRSH;

      // Calculate the RelationShipHolder key (usually, it is "key1,key2")
      const std::string& lRSHKey =
        RelationShipHolder_T::keyCalculator (iFirstBom.getKey(), iSecondBomKey);
      oSecondBom_ptr = oRSH_ptr->find (lRSHKey);

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
    RelationShipHolderList_T _relationShipHolderList;
    RelationShipHolderSet_T _relationShipHolderSet;
  };

}
#endif // __INTRUSIVE_BOM_RELATIONSHIPHOLDERSET_HPP
