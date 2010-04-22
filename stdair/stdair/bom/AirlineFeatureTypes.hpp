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
  template <typename CONTENT> class Structure;
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
  class AirlineFeature;
  
  /** Define the airline feature structure. */
  typedef Structure<AirlineFeature> AirlineFeatureStructure_T;

  /** Define the airline feature holder. */
  typedef BomChildrenHolderImp<AirlineFeature> AirlineFeatureHolder_T;

  /** Define the airline feature list. */
  typedef BomList_T<AirlineFeature> AirlineFeatureList_T;

  /** Define the airline feature map. */
  typedef BomMap_T<AirlineFeature> AirlineFeatureMap_T;

}
#endif // __STDAIR_BOM_AIRLINEFEATURETYPES_HPP

