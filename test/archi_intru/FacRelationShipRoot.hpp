#ifndef __INTRUSIVE_FAC_FACRELATIONSHIPROOT_HPP
#define __INTRUSIVE_FAC_FACRELATIONSHIPROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost.Intrusive
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/set.hpp>
// Local
#include <test/archi_intru/FacSupervisor.hpp>
#include <test/archi_intru/FacRelationShipRootAbstract.hpp>
#include <test/archi_intru/RelationShipHolder.hpp>
#include <test/archi_intru/RelationShipHolderSet.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

namespace stdair {

  /** Class holding the list of all the relationship objects of a given type. */
  template <typename FIRST_BOM, typename SECOND_BOM>
  class FacRelationShipRoot : public FacRelationShipRootAbstract {
  public:
    // ///////////////////////////////////////////
    /** Type definition for the specific relationship class. */
    typedef RelationShipHolder<FIRST_BOM, SECOND_BOM> RelationShipHolder_T;

    /** Type definition for the specific relationship holder (set) class. */
    typedef RelationShipHolderSet<FIRST_BOM,
                                  SECOND_BOM> RelationShipHolderHolder_T;
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
    /** Constructor. */
    FacRelationShipRoot() : _relationShipHolderSet ("DefaultRSHSet") {}
  private:
    /** Default constructors.
        <br>They are kept private, so as to forbid their use (only the
        public constructors should be used). */
    FacRelationShipRoot (const FacRelationShipRoot&) {}
    /** Destructor. */
    ~FacRelationShipRoot() {}
    
  public:
    /** Add a child/sibling to the dedicated list of the parent/sibling. */
    static void addToList (FIRST_BOM& ioFirstBom, SECOND_BOM& ioSecondBom) {
      instance().addToListImpl (ioFirstBom, ioSecondBom);
    }
    
    /** Add a child/sibling to the dedicated list of the parent/sibling. */
    void addToListImpl (FIRST_BOM& ioFirstBom, SECOND_BOM& ioSecondBom) {
      RelationShipHolder_T* lRS_ptr = new RelationShipHolder_T (ioFirstBom,
                                                                ioSecondBom);
      _relationShipHolderSet.addToList (*lRS_ptr);
    }
    
    /** Search for a child/sibling from the dedicated list of the
        parents/siblings. */
    static SECOND_BOM* find (const FIRST_BOM& iFirstBom,
                             const std::string& iSecondBomKey) {
      SECOND_BOM* oSecondBom_ptr =
        instance().findImpl (iFirstBom, iSecondBomKey);
      return oSecondBom_ptr;
    }
    
    /** Search for a child/sibling from the dedicated list of the
        parents/siblings. */
    SECOND_BOM* findImpl (const FIRST_BOM& iFirstBom,
                          const std::string& iSecondBomKey) {
      SECOND_BOM* oSecondBom_ptr =
        _relationShipHolderSet.find (iFirstBom, iSecondBomKey);
      return oSecondBom_ptr;
    }
    
  private:
    /** Set of relationship holder objects. */
    RelationShipHolderHolder_T _relationShipHolderSet;

  private:
    /** The unique instance. */
    static FacRelationShipRoot* _instance;
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename FIRST_BOM, typename SECOND_BOM>
  FacRelationShipRoot<FIRST_BOM, SECOND_BOM>*
  FacRelationShipRoot<FIRST_BOM, SECOND_BOM>::_instance = NULL;
  
}
#endif // __INTRUSIVE_FAC_FACRELATIONSHIPROOT_HPP
