// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/AirlineFeatureSetStructure.hpp>
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/bom/BomMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureSet::
  AirlineFeatureSet (const BomKey_T& iKey,
                     BomStructure_T& ioAirlineFeatureSetStructure)
    : AirlineFeatureSetContent (iKey), 
      _bomStructure (ioAirlineFeatureSetStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureSet::~AirlineFeatureSet () {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string AirlineFeatureSet::display() const {
    // Store current formatting flags of std::cout
    std::ios::fmtflags oldFlags = std::cout.flags();
    std::ostringstream ostr;
    ostr << "Set of airline features" << std::endl;

    AirlineFeatureList_T lAirlineFeatureList = getAirlineFeatureList();
    for (AirlineFeatureList_T::iterator itAirlineFeature =
           lAirlineFeatureList.begin();
         itAirlineFeature != lAirlineFeatureList.end(); ++itAirlineFeature) {
      const AirlineFeature& lAirlineFeature = *itAirlineFeature;
      
      ostr << lAirlineFeature.describe ();
    }
    
    // Reset formatting flags of std::cout
    std::cout.flags (oldFlags);
     
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureList_T AirlineFeatureSet::getAirlineFeatureList () const {
    return _bomStructure.getChildrenHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T AirlineFeatureSet::getAirlineFeatureMap () const {
    return _bomStructure.getChildrenHolder();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeature* AirlineFeatureSet::
  getAirlineFeature (const AirlineFeatureKey_T& iKey) const {
    return _bomStructure.getContentChild (iKey);
  }
  
}
