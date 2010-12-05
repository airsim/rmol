// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_AIRLINEFEATURETYPES_HPP
#define __STDAIR_BOM_AIRLINEFEATURETYPES_HPP

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
  class AirlineFeature;

  /** Define the airline feature list. */
  typedef std::list<AirlineFeature*> AirlineFeatureList_T;

  /** Define the airline feature map. */
  typedef std::map<const MapKey_T, AirlineFeature*> AirlineFeatureMap_T;

}
#endif // __STDAIR_BOM_AIRLINEFEATURETYPES_HPP

