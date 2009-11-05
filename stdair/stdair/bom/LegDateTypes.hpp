// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_LEGDATETYPES_HPP
#define __STDAIR_BOM_LEGDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename BOM_CONTENT> class LegDateStructure;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class LegDate;
  
  /** Define the LegDate structure. */
  typedef LegDateStructure<LegDate> LegDateStructure_T;
  
  /** Define the leg-date structure list. */
  typedef std::vector<LegDateStructure_T*> LegDateStructureList_T;

  /** Define the leg-date structure map. */
  typedef std::map<const std::string, LegDateStructure_T*> LegDateStructureMap_T;
  
 /** Define the leg-date list. */
  typedef BomList_T<LegDate> LegDateList_T;

  /** Define the leg-date map. */
  typedef BomMap_T<LegDate> LegDateMap_T;
}
#endif // __STDAIR_BOM_LEGDATETYPES_HPP

