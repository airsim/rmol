// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_LEGCABINTYPES_HPP
#define __STDAIR_BOM_LEGCABINTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class LegCabin;
  
  /** Define the LegCabin structure. */
  typedef Structure<LegCabin> LegCabinStructure_T;
  
  /** Define the LegCabin holder. */
  typedef BomChildrenHolderImp<LegCabin> LegCabinHolder_T;

 /** Define the leg-cabin list. */
  typedef BomList_T<LegCabin> LegCabinList_T;

  /** Define the leg-cabin map. */
  typedef BomMap_T<LegCabin> LegCabinMap_T;

}
#endif // __STDAIR_BOM_LEGCABINTYPES_HPP

