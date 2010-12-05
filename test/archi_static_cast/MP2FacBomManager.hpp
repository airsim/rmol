#ifndef __MYPROVIDER_FACBOMMANAGER_HPP
#define __MYPROVIDER_FACBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <typeinfo>
// Local
#include <test/archi_static_cast/MP2Types.hpp>
#include <test/archi_static_cast/MP2FacBom.hpp>

namespace myprovider {
  
  /** Utility class for STDAIR objects. */
  class FacBomManager {
  public:    
    /** Add a child object to the dedicated container of the parent object. */
    template <typename PARENT, typename CHILD>
    static void addToList (PARENT&, CHILD&);
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename PARENT, typename CHILD> void FacBomManager::
  addToList (PARENT& ioParent, CHILD& ioChild) {
    HolderMap_T::const_iterator itHolder =
      ioParent._holderMap.find (&typeid (CHILD));

    if (itHolder == ioParent._holderMap.end()) {
      BomHolder<CHILD>& lHolder =
        FacBom<BomHolder<CHILD> >::instance().create();
      lHolder._bomList.push_back (&ioChild);
      ioParent._holderMap.insert (typename HolderMap_T::
                                  value_type (&typeid(CHILD), &lHolder));
    } else {
      BomHolder<CHILD>* lHolder_ptr =
        static_cast<BomHolder<CHILD>* > (itHolder->second);
      assert (lHolder_ptr != NULL);
      lHolder_ptr->_bomList.push_back (&ioChild);
    }
  }

}

#endif // __MYPROVIDER_FACBOMMANAGER_HPP
