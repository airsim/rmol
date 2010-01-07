// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/bom/LegDateContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  LegDateContent::LegDateContent (const BomKey_T& iKey) \
    : _key (iKey),
      _distance (DEFAULT_DISTANCE_VALUE),
      _capacity (DEFAULT_CABIN_CAPACITY),
      _legSoldSeat (DEFAULT_CLASS_NB_OF_BOOKINGS),
      _legLoadFactor (DEFAULT_REVENUE_VALUE) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateContent::~LegDateContent () {
  }

  // //////////////////////////////////////////////////////////////////////
  const Duration_T LegDateContent::getTimeOffSet() const {
    // TimeOffSet = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
    //              - ElapsedTime
    Duration_T oTimeOffSet = (_offTime - _boardingTime);
    const DateOffSet_T& lDateOffSet = getDateOffSet();
    const Duration_T lDateOffSetInHours (lDateOffSet.days() * 24, 0, 0);
    oTimeOffSet += lDateOffSetInHours - _elapsedTime;
    return oTimeOffSet;
  }
  
  // //////////////////////////////////////////////////////////////////////
  void LegDateContent::setElapsedTime(const Duration_T& iElapsedTime) {
    // Set Elapsed time
    _elapsedTime = iElapsedTime;
    // Update distance according to the mean plane speed
    updateDistanceFromElapsedTime ();
  }

  // //////////////////////////////////////////////////////////////////////
  void LegDateContent::updateDistanceFromElapsedTime () {
    const double lElapseInHours =
      static_cast<const double>(_elapsedTime.hours());
    const long int lDistance =
      static_cast<const long int>(DEFAULT_FLIGHT_SPEED*lElapseInHours);
    _distance = lDistance;
  }
  
}

