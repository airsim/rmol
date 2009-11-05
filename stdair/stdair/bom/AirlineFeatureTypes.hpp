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
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class AirlineFeature;
  
  /** Define the airline feature structure. */
  typedef AirlineFeatureStructure<AirlineFeature> AirlineFeatureStructure_T;
  
  /** Define the airline feature structure list. */
  typedef std::vector<AirlineFeatureStructure_T*> AirlineFeatureStructureList_T;

  /** Define the airline feature structure map. */
  typedef std::map<const std::string, AirlineFeatureStructure_T*> AirlineFeatureStructureMap_T;

  /** Define the airline feature list. */
  typedef BomList_T<AirlineFeature> AirlineFeatureList_T;

  /** Define the airline feature map. */
  typedef BomMap_T<AirlineFeature> AirlineFeatureMap_T;

}
#endif // __STDAIR_BOM_AIRLINEFEATURETYPES_HPP

