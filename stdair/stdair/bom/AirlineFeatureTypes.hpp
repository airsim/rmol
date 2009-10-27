// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_AIRLINEFEATURETYPES_HPP
#define __STDAIR_BOM_AIRLINEFEATURETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>

namespace stdair {

  // Forward declarations.
  template <typename BOM_CONTENT> class AirlineFeatureStructure;
  class AirlineFeature;
  
  /** Define the AirlineFeature structure. */
  typedef AirlineFeatureStructure<AirlineFeature> AirlineFeatureStructure_T;
  
  /** Define the segment-cabin structure list. */
  typedef std::vector<AirlineFeatureStructure_T*> AirlineFeatureStructureList_T;

  /** Define the segment-cabin structure map. */
  typedef std::map<const std::string, AirlineFeatureStructure_T*> AirlineFeatureStructureMap_T;

}
#endif // __STDAIR_BOM_AIRLINEFEATURETYPES_HPP

