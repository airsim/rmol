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
  LegDateContent::LegDateContent (const Key_T& iKey) \
    : _key (iKey),
      _distance (DEFAULT_DISTANCE_VALUE),
      _capacity (DEFAULT_CABIN_CAPACITY) {
  }

  // ////////////////////////////////////////////////////////////////////
  LegDateContent::~LegDateContent () {
  }

  // ////////////////////////////////////////////////////////////////////
  const Duration_T LegDateContent::getTimeOffset() const {
    // TimeOffset = (OffTime - BoardingTime) + (OffDate - BoardingDate) * 24
    //              - ElapsedTime
    Duration_T oTimeOffset = (_offTime - _boardingTime);
    const DateOffset_T& lDateOffset = getDateOffset();
    const Duration_T lDateOffsetInHours (lDateOffset.days() * 24, 0, 0);
    oTimeOffset += lDateOffsetInHours - _elapsedTime;
    return oTimeOffset;
  }
  
  // ////////////////////////////////////////////////////////////////////
  void LegDateContent::setElapsedTime(const Duration_T& iElapsedTime) {
    // Set Elapsed time
    _elapsedTime = iElapsedTime;
    // Update distance according to the mean plane speed
    updateDistanceFromElapsedTime ();
  }

  // ////////////////////////////////////////////////////////////////////
  void LegDateContent::updateDistanceFromElapsedTime () {
    const double lElapseInHours =
      static_cast<const double>(_elapsedTime.hours());
    const long int lDistance =
      static_cast<const long int>(DEFAULT_FLIGHT_SPEED*lElapseInHours);
    _distance = lDistance;
  }
  
}

