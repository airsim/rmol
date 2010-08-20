#ifndef __STDAIR_FAC_FACBOMMANAGER_HPP
#define __STDAIR_FAC_FACBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// STDAIR
#include <stdair/bom/RelationShip.hpp>
#include <stdair/factory/FacBom.hpp>

namespace stdair {
  
  /** Utility class for STDAIR objects. */
  class FacBomManager {
  public:
    /** Create a BOM. */
    template <typename BOM>
    static BOM& create (const typename BOM::Key_T&);
    
    /** Add a child object to the dedicated container of the parent object. */
    template <typename PARENT, typename CHILD>
    static void addToList (const PARENT&, CHILD&);
    template <typename PARENT, typename CHILD>
    static void addToMap (const PARENT&, CHILD&);
    template <typename PARENT, typename CHILD>
    static void addToMap (const PARENT&, CHILD&, const MapKey_T&);
    template <typename PARENT, typename CHILD>
    static void addToListAndMap (const PARENT&, CHILD&);
    template <typename PARENT, typename CHILD>
    static void addToListAndMap (const PARENT&, CHILD&, const MapKey_T&);

    /** Link the CHILD with the PARENT. */
    template <typename PARENT, typename CHILD>
    static void linkWithParent (PARENT&, const CHILD&);

    /** Clone the list of children between two objects. */
    template <typename CHILD, typename PARENT>
    static void cloneChildrenList (const PARENT&, const PARENT&);
    
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> BOM& FacBomManager::
  create (const typename BOM::Key_T& iKey) {
    return FacBom<BOM>::instance().create (iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void FacBomManager::
  addToList (const PARENT& iParent, CHILD& ioChild) {
    RelationShip<PARENT, CHILD>::instance().addChildToTheList (iParent, ioChild);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void FacBomManager::
  addToMap (const PARENT& iParent, CHILD& ioChild) {
    RelationShip<PARENT, CHILD>::instance().addChildToTheMap (iParent, ioChild);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void FacBomManager::
  addToMap (const PARENT& iParent, CHILD& ioChild, const MapKey_T& iKey) {
    RelationShip<PARENT, CHILD>::instance().addChildToTheMap (iParent,
                                                              ioChild, iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void FacBomManager::
  addToListAndMap (const PARENT& iParent, CHILD& ioChild) {
    RelationShip<PARENT, CHILD>::instance().addChildToTheList (iParent, ioChild);
    RelationShip<PARENT, CHILD>::instance().addChildToTheMap (iParent, ioChild);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void FacBomManager::
  addToListAndMap (const PARENT& iParent, CHILD& ioChild, const MapKey_T& iKey) {
    RelationShip<PARENT, CHILD>::instance().addChildToTheList (iParent, ioChild);
    RelationShip<PARENT, CHILD>::instance().addChildToTheMap (iParent,
                                                              ioChild, iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void FacBomManager::
  linkWithParent (PARENT& ioParent, const CHILD& iChild) {
    RelationShip<PARENT, CHILD>::instance().linkWithParent (ioParent, iChild);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT> void FacBomManager::
  cloneChildrenList (const PARENT& iP1, const PARENT& iP2) {
    const std::list<CHILD*>& lList =
      RelationShip<PARENT, CHILD>::instance().getChildrenList (iP2);
    RelationShip<PARENT, CHILD>::instance()._parentChildrenList[&iP1] = lList;
  }

}

#endif // __STDAIR_FAC_FACBOMMANAGER_HPP
