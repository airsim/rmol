// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <cassert>
// STL
#include <sstream>
#include <algorithm>
// STDAIR
#include <stdair/bom/FlightDate.hpp>
// RMOL 
#include <rmol/bom/Inventory.hpp>
#include <rmol/bom/FlightDate.hpp>
#include <rmol/bom/SegmentDate.hpp>
#include <rmol/bom/LegDate.hpp>
#include <rmol/service/Logger.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  FlightDate::FlightDate (BomStructure_T& ioFlightStructure)
    : _flightDateStructure (ioFlightStructure) {
  }

  // ////////////////////////////////////////////////////////////////////
  FlightDate::~FlightDate () {
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  // //////////////////////////////////////////////////////////////////////
  void FlightDate::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string FlightDate::toString() const {
    std::ostringstream oStr;
    
    // First, put the key of that level
    oStr << describeShortKey() << std::endl;

    return oStr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeKey() const {
    return _flightDateStructure.describeKey();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string FlightDate::describeShortKey() const {
    return _flightDateStructure.describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_const_iterator FlightDate::segmentDateListConstIteratorBegin () const {
    return _flightDateStructure.segmentDateListConstIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_const_iterator FlightDate::segmentDateListConstIteratorEnd () const {
    return _flightDateStructure.segmentDateListConstIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::segment_date_list_const_reverse_iterator FlightDate::segmentDateListConstIteratorRBegin () const {
    return _flightDateStructure.segmentDateListConstIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::segment_date_list_const_reverse_iterator FlightDate::segmentDateListConstIteratorREnd () const {
    return _flightDateStructure.segmentDateListConstIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_iterator FlightDate::segmentDateListIteratorBegin () const {
    return _flightDateStructure.segmentDateListIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_iterator FlightDate::segmentDateListIteratorEnd () const {
    return _flightDateStructure.segmentDateListIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_reverse_iterator FlightDate::segmentDateListIteratorRBegin () const {
    return _flightDateStructure.segmentDateListIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_list_reverse_iterator FlightDate::segmentDateListIteratorREnd () const {
    return _flightDateStructure.segmentDateListIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_const_iterator FlightDate::segmentDateMapConstIteratorBegin () const {
    return _flightDateStructure.segmentDateMapConstIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_const_iterator FlightDate::segmentDateMapConstIteratorEnd () const {
    return _flightDateStructure.segmentDateMapConstIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::segment_date_map_const_reverse_iterator FlightDate::segmentDateMapConstIteratorRBegin () const {
    return _flightDateStructure.segmentDateMapConstIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::segment_date_map_const_reverse_iterator FlightDate::segmentDateMapConstIteratorREnd () const {
    return _flightDateStructure.segmentDateMapConstIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_iterator FlightDate::segmentDateMapIteratorBegin () const {
    return _flightDateStructure.segmentDateMapIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_iterator FlightDate::segmentDateMapIteratorEnd () const {
    return _flightDateStructure.segmentDateMapIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_reverse_iterator FlightDate::segmentDateMapIteratorRBegin () const {
    return _flightDateStructure.segmentDateMapIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  segment_date_map_reverse_iterator FlightDate::segmentDateMapIteratorREnd () const {
    return _flightDateStructure.segmentDateMapIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_const_iterator FlightDate::legDateListConstIteratorBegin () const {
    return _flightDateStructure.legDateListConstIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_const_iterator FlightDate::legDateListConstIteratorEnd () const {
    return _flightDateStructure.legDateListConstIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::leg_date_list_const_reverse_iterator FlightDate::legDateListConstIteratorRBegin () const {
    return _flightDateStructure.legDateListConstIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::leg_date_list_const_reverse_iterator FlightDate::legDateListConstIteratorREnd () const {
    return _flightDateStructure.legDateListConstIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_iterator FlightDate::legDateListIteratorBegin () const {
    return _flightDateStructure.legDateListIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_iterator FlightDate::legDateListIteratorEnd () const {
    return _flightDateStructure.legDateListIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_reverse_iterator FlightDate::legDateListIteratorRBegin () const {
    return _flightDateStructure.legDateListIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_list_reverse_iterator FlightDate::legDateListIteratorREnd () const {
    return _flightDateStructure.legDateListIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_const_iterator FlightDate::legDateMapConstIteratorBegin () const {
    return _flightDateStructure.legDateMapConstIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_const_iterator FlightDate::legDateMapConstIteratorEnd () const {
    return _flightDateStructure.legDateMapConstIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::leg_date_map_const_reverse_iterator FlightDate::legDateMapConstIteratorRBegin () const {
    return _flightDateStructure.legDateMapConstIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::leg_date_map_const_reverse_iterator FlightDate::legDateMapConstIteratorREnd () const {
    return _flightDateStructure.legDateMapConstIteratorREnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_iterator FlightDate::legDateMapIteratorBegin () const {
    return _flightDateStructure.legDateMapIteratorBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_iterator FlightDate::legDateMapIteratorEnd () const {
    return _flightDateStructure.legDateMapIteratorEnd ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_reverse_iterator FlightDate::legDateMapIteratorRBegin () const {
    return _flightDateStructure.legDateMapIteratorRBegin ();
  }

  // //////////////////////////////////////////////////////////////////////
  FlightDate::
  leg_date_map_reverse_iterator FlightDate::legDateMapIteratorREnd () const {
    return _flightDateStructure.legDateMapIteratorREnd ();
  }

}

