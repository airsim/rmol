// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/LegDateStructure.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/LegCabinList.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegCabinList_T::
  LegCabinList_T (const LegDateStructure_T& iLegDateStructure)
    : _legDateStructure (iLegDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinList_T::
  LegCabinList_T (const LegCabinList_T& iSCList)
    : _legDateStructure (iSCList._legDateStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegCabinList_T::~LegCabinList_T () {
  }

  // //////////////////////////////////////////////////////////////////////
  LegCabinList_T::iterator LegCabinList_T::begin () const {
    return _legDateStructure.legCabinListBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  LegCabinList_T::iterator LegCabinList_T::end () const {
    return _legDateStructure.legCabinListEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  LegCabinList_T::reverse_iterator LegCabinList_T::rbegin () const {
    return _legDateStructure.legCabinListRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  LegCabinList_T::reverse_iterator LegCabinList_T::rend () const {
    return _legDateStructure.legCabinListREnd ();
  }

}

