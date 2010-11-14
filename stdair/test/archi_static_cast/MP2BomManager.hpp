#ifndef __MYPROVIDER_BOMMANAGER_HPP
#define __MYPROVIDER_BOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <typeinfo>
// Archi TEST
#include <test/archi_static_cast/MP2Types.hpp>

namespace myprovider {
  
  /** Utility class for StdAir objects. */
  class BomManager {
  public:
    /** Get the list of BOM objects within the given parent. */
    template <typename CHILD, typename PARENT>
    static std::list<CHILD*>& getList (const PARENT&);
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename CHILD, typename PARENT> std::list<CHILD*>& BomManager::
  getList (const PARENT& iParent) {
    HolderMap_T::const_iterator itHolder =
      iParent._holderMap.find (&typeid (CHILD));
    assert (itHolder != iParent._holderMap.end());

    BomHolder<CHILD>* const  lHolder_ptr =
      static_cast<BomHolder<CHILD>* const > (itHolder->second);

    BomHolder<CHILD>& lHolder = *lHolder_ptr;
    
    return lHolder._bomList;
  }
}

#endif // __MYPROVIDER_BOMMANAGER_HPP
