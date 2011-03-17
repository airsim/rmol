// //////////////////////////////////////////////////////////////////////
#ifndef __AIRRAC_BOM_YIELDRULEFEATURESTYPES_HPP
#define __AIRRAC_BOM_YIELDRULEFEATURESTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// STDAIR
#include <stdair/bom/key_types.hpp>

namespace AIRRAC {

  // Forward declarations.
  class YieldRuleFeatures;
  
  /** Define the yield-rule list. */
  typedef std::list<YieldRuleFeatures*> YieldRuleFeaturesList_T;

  /** Define the yield-rule map. */
  typedef std::map<const stdair::MapKey_T, YieldRuleFeatures*> YieldRuleFeaturesMap_T;

  /** Define the list of pair<MapKey_T, YieldRule>. */
  typedef std::pair<stdair::MapKey_T, YieldRuleFeatures*> YieldRuleFeaturesWithKey_T;
  typedef std::list<YieldRuleFeaturesWithKey_T> YieldRuleFeaturesDetailedList_T;
}
#endif // __AIRRAC_BOM_YIELDRULEFEATURESTYPES_HPP

