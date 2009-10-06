// //////////////////////////////////////////////////////////////////////
#ifndef __RMOL_BOM_LEGDATETYPES_HPP
#define __RMOL_BOM_LEGDATETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// Forward declarations.
namespace stdair {
  template <typename BOM_CONTENT> class LegDate;
  template <typename BOM_CONTENT> class LegDateKey;
}

namespace RMOL {

  // Forward declarations.
  class LegDate;
  
  /** Define the LegDate structure. */
  typedef stdair::LegDate<LegDate> LegDateStructure_T;
  
  /** Define the LegDate key. */
  typedef stdair::LegDateKey<LegDate> LegDateKey_T;
  
  /** Define the leg-date structure list. */
  typedef std::vector<LegDateStructure_T*> LegDateStructureList_T;

  /** Define the leg-date structure map. */
  typedef std::map<const std::string, LegDateStructure_T*> LegDateStructureMap_T;

}
#endif // __RMOL_BOM_LEGDATETYPES_HPP

