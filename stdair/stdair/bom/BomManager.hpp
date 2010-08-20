#ifndef __STDAIR_BOM_BOMMANAGER_HPP
#define __STDAIR_BOM_BOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// STDAIR
#include <stdair/bom/RelationShip.hpp>

namespace stdair {
  
  /** Utility class for StdAir objects. */
  class BomManager {
  public:
    /** Get the list of BOM objects within the given parent. */
    template <typename CHILD, typename PARENT>
    static std::list<CHILD*>& getList (const PARENT&);
    template <typename CHILD, typename PARENT>
    static std::map<const MapKey_T, CHILD*>& getMap (const PARENT&);

    /** Getter of the PARENT given the CHILD. */
    template <typename PARENT, typename CHILD>
    static PARENT& getParent (const CHILD&);

    /** Return the CHILD pointer corresponding to the given string key.
        If such a CHILD does not exist, return NULL. */
    template <typename CHILD, typename PARENT>
    static CHILD* getChildPtr (const PARENT&, const MapKey_T&);

    /** Return the CHILD corresponding the the given string key. */
    template <typename CHILD, typename PARENT>
    static CHILD& getChild (const PARENT&, const MapKey_T&);
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT> std::list<CHILD*>& BomManager::
  getList (const PARENT& iParent) {
    return RelationShip<PARENT, CHILD>::instance().getChildrenList (iParent);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT> std::map<const MapKey_T, CHILD*>&
  BomManager::getMap (const PARENT& iParent) {
    return RelationShip<PARENT, CHILD>::instance().getChildrenMap (iParent);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  PARENT& BomManager::getParent (const CHILD& iChild) {
    return RelationShip<PARENT, CHILD>::instance().getParent (iChild);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT>
  CHILD* BomManager::getChildPtr (const PARENT& iParent, const MapKey_T& iKey) {
    return RelationShip<PARENT, CHILD>::instance().getChildPtr (iParent, iKey);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT>
  CHILD& BomManager::getChild (const PARENT& iParent, const MapKey_T& iKey) {
    return RelationShip<PARENT, CHILD>::instance().getChild (iParent, iKey);
  }
}

#endif // __STDAIR_BOM_BOMMANAGER_HPP
