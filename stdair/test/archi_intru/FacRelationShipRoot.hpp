#ifndef __INTRUSIVE_FAC_FACRELATIONSHIPHOLDER_HPP
#define __INTRUSIVE_FAC_FACRELATIONSHIPHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost.Intrusive
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/set.hpp>
// Local
#include <test/archi_intru/FacSupervisor.hpp>
#include <test/archi_intru/FacRelationShipRootAbstract.hpp>
#include <test/archi_intru/RelationShipHolder.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

namespace stdair {

  /** Class holding the list of all the relationship objects of a given type. */
  template <typename FIRST_BOM, typename SECOND_BOM>
  class FacRelationShipRoot : public FacRelationShipRootAbstract {
  public:
    // ///////////////////////////////////////////
    /** Type definition for the specific relationship. */
    typedef RelationShipHolder<FIRST_BOM, SECOND_BOM> RelationShipHolder_T;
    
    /** Type definition for a list of relationship holder objects. */
    typedef bi::member_hook <RelationShipHolder_T,
                             bi::list_member_hook<>,
                             &RelationShipHolder_T::_childListHook> RSHolderListMemberOption;
    typedef bi::list<RelationShipHolder_T,
                     RSHolderListMemberOption> RelationShipHolderList_T;
    /** Type definition for a set of relationship holder objects. */
    typedef bi::member_hook <RelationShipHolder_T,
                             bi::set_member_hook<>,
                             &RelationShipHolder_T::_childSetHook> RSHolderSetMemberOption;
    typedef bi::set<RelationShipHolder_T,
                    RSHolderSetMemberOption> RelationShipHolderSet_T;
    // ///////////////////////////////////////////

  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacRelationShipRoot& */
    static FacRelationShipRoot& instance () {
      if (_instance == NULL) {
        _instance = new FacRelationShipRoot ();
        assert (_instance != NULL);
        
        FacSupervisor::instance().registerFacRelationShipRoot (_instance);
      }
      return *_instance;
    }
    
  public:
    /** Add a child/sibling to the dedicated list of the parent/sibling. */
    static void addToList (FIRST_BOM& ioFirstBom, SECOND_BOM& ioSecondBom) {
      instance().addToListImpl (ioFirstBom, ioSecondBom);
    }
    
    /** Add a child/sibling to the dedicated list of the parent/sibling. */
    void addToListImpl (FIRST_BOM& ioFirstBom, SECOND_BOM& ioSecondBom) {
      RelationShipHolder_T* lRS_ptr = new RelationShipHolder_T (ioFirstBom,
                                                                ioSecondBom);
      _relationShipHolderList.push_back (*lRS_ptr);
      _relationShipHolderSet.insert (*lRS_ptr);
    }
    
  private:
    /** List of relationship holder objects. */
    RelationShipHolderList_T _relationShipHolderList;
    /** Set of relationship holder objects. */
    RelationShipHolderSet_T _relationShipHolderSet;

  private:
    /** The unique instance. */
    static FacRelationShipRoot* _instance;
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename FIRST_BOM, typename SECOND_BOM>
  FacRelationShipRoot<FIRST_BOM, SECOND_BOM>*
  FacRelationShipRoot<FIRST_BOM, SECOND_BOM>::_instance = NULL;
  
}
#endif // __INTRUSIVE_FAC_FACRELATIONSHIPHOLDER_HPP
