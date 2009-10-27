// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/AirlineFeature.hpp>
#include <stdair/bom/AirlineFeatureList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureList_T::
  AirlineFeatureList_T (const AirlineFeatureHolder_T& iAirlineFeatureHolder)
    : _airlineFeatureHolder (iAirlineFeatureHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureList_T::
  AirlineFeatureList_T (const AirlineFeatureList_T& iAFList)
    : _airlineFeatureHolder (iAFList._airlineFeatureHolder) {
  }

  // ////////////////////////////////////////////////////////////////////
  AirlineFeatureList_T::~AirlineFeatureList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureList_T::iterator AirlineFeatureList_T::begin () const {
    return _airlineFeatureHolder.listBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureList_T::iterator AirlineFeatureList_T::end () const {
    return _airlineFeatureHolder.listEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureList_T::reverse_iterator AirlineFeatureList_T::rbegin () const {
    return _airlineFeatureHolder.listRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  AirlineFeatureList_T::reverse_iterator AirlineFeatureList_T::rend () const {
    return _airlineFeatureHolder.listREnd ();
  }

}

