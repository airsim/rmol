// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_LEGDATETYPES_HPP
#define __STDAIR_BOM_LEGDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class LegDate;
  
  /** Define the leg-date list. */
  typedef std::list<LegDate*> LegDateList_T;

  /** Define the leg-date map. */
  typedef std::map<const MapKey_T, LegDate*> LegDateMap_T;
}
#endif // __STDAIR_BOM_LEGDATETYPES_HPP

