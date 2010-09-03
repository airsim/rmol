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
    static std::list<std::pair<MapKey_T, CHILD*> >& getDetailedList (const PARENT&);
    template <typename CHILD, typename PARENT>
    static std::map<const MapKey_T, CHILD*>& getMap (const PARENT&);

    /** Get the map of parent and children holder. */
    template <typename PARENT, typename CHILD>
    static const std::map<const PARENT*, 
                          std::list<CHILD*> >& getParentChildrenList();
    template <typename PARENT, typename CHILD>
    static const std::map<const PARENT*,
                    std::map<const MapKey_T, CHILD*> >& getParentChildrenMap();

    /** Check if the list/map of children has been initialised. */
    template <typename CHILD, typename PARENT>    
    static bool hasList (const PARENT&);
    template <typename CHILD, typename PARENT>    
    static bool hasDetailedList (const PARENT&);
    template <typename CHILD, typename PARENT>    
    static bool hasMap (const PARENT&);

    /** Getter of the PARENT given the CHILD. */
    template <typename PARENT, typename CHILD>
    static PARENT& getParent (const CHILD&);

    /** Return the CHILD pointer corresponding to the given string key.
        If such a CHILD does not exist, return NULL. */
    template <typename CHILD, typename PARENT>
    static CHILD* getChildPtr (const PARENT&, const MapKey_T&);
    template <typename BOM>
    static  BOM* const getObjectPtr (const std::map<const MapKey_T, BOM*>&,
                                     const MapKey_T&);

    /** Return the CHILD corresponding the the given string key. */
    template <typename CHILD, typename PARENT>
    static CHILD& getChild (const PARENT&, const MapKey_T&);
    template <typename BOM>
    static BOM& getObject (const std::map<const MapKey_T, BOM*>&,
                           const MapKey_T&);
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT> std::list<CHILD*>& BomManager::
  getList (const PARENT& iParent) {
    return RelationShip<PARENT, CHILD>::instance().getChildrenList (iParent);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT>
  std::list<std::pair<MapKey_T, CHILD*> >& BomManager::
  getDetailedList (const PARENT& iParent) {
    return RelationShip<PARENT, CHILD>::
      instance().getChildrenDetailedList (iParent);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT> std::map<const MapKey_T, CHILD*>&
  BomManager::getMap (const PARENT& iParent) {
    return RelationShip<PARENT, CHILD>::instance().getChildrenMap (iParent);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> 
  const std::map<const PARENT*, std::list<CHILD*> >& BomManager::
  getParentChildrenList() {
    return RelationShip<PARENT, CHILD>::instance().getParentChildrenList();
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD>
  const std::map<const PARENT*, std::map<const MapKey_T, CHILD*> >& BomManager::
  getParentChildrenMap() {
    return RelationShip<PARENT, CHILD>::instance().getParentChildrenMap();
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT> 
  bool BomManager::hasList (const PARENT& iParent) {
    return RelationShip<PARENT, CHILD>::instance().hasChildrenList (iParent);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT> 
  bool BomManager::hasDetailedList (const PARENT& iParent) {
    return RelationShip<PARENT, CHILD>::
      instance().hasChildrenDetailedList (iParent);
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT> 
  bool BomManager::hasMap (const PARENT& iParent) {
    return RelationShip<PARENT, CHILD>::instance().hasChildrenMap (iParent);
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

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM>
  BOM* const BomManager::getObjectPtr (const std::map<const MapKey_T,BOM*>& iMap,
                                      const MapKey_T& iKey) {
    typename std::map<const MapKey_T, BOM*>::const_iterator it = iMap.find (iKey);
    if (it == iMap.end()) {
      return NULL;
    }
    BOM* const oBom_ptr = it->second;
    assert (oBom_ptr != NULL);
    return oBom_ptr;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM>
  BOM& BomManager::getObject (const std::map<const MapKey_T, BOM*>& iMap,
                              const MapKey_T& iKey) {
    typename std::map<const MapKey_T, BOM*>::const_iterator it = iMap.find (iKey);
    assert (it != iMap.end());
    BOM* const oBom_ptr = it->second;
    assert (oBom_ptr != NULL);
    return *oBom_ptr;
  }
}

#endif // __STDAIR_BOM_BOMMANAGER_HPP
