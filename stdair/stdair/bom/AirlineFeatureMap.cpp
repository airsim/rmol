// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/AirlineFeatureMap.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T::
  AirlineFeatureMap_T (const AirlineFeatureHolder_T& iAirlineFeatureHolder)
    : _airlineFeatureHolder (iAirlineFeatureHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T::
  AirlineFeatureMap_T (const AirlineFeatureMap_T& iAFMap)
    : _airlineFeatureHolder (iAFMap._airlineFeatureHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T::~AirlineFeatureMap_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T::iterator AirlineFeatureMap_T::begin () const {
    return _airlineFeatureHolder.mapBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T::iterator AirlineFeatureMap_T::end () const {
    return _airlineFeatureHolder.mapEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T::reverse_iterator AirlineFeatureMap_T::rbegin () const {
    return _airlineFeatureHolder.mapRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T::reverse_iterator AirlineFeatureMap_T::rend () const {
    return _airlineFeatureHolder.mapREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureMap_T::
  iterator AirlineFeatureMap_T::find (const MapKey_T& iKey) const {
    return _airlineFeatureHolder.find (iKey);
  }

}

