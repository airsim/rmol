// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_LEGCABINTYPES_HPP
#define __STDAIR_BOM_LEGCABINTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  // Forward declarations.
  class LegCabin;

 /** Define the leg-cabin list. */
  typedef std::list<LegCabin*> LegCabinList_T;

  /** Define the leg-cabin map. */
  typedef std::map<const MapKey_T, LegCabin*> LegCabinMap_T;

}
#endif // __STDAIR_BOM_LEGCABINTYPES_HPP

