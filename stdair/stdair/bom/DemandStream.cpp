// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iosfwd>
#include <ostream>
#include <sstream>
// Boost
#include <boost/math/distributions/normal.hpp>
// Math
#include <math.h>
// STDAIR
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/DemandCharacteristics.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/basic/RandomGenerationContext.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/DemandStream.hpp>
#include <stdair/service/Logger.hpp>


namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  DemandStream::DemandStream(const DemandStreamKey_T& iKey,
                             const DemandCharacteristics& iDemandCharacteristics,
                             const DemandDistribution& iDemandDistribution,
                             const RandomSeed_T& iNumberOfRequestsSeed,
                             const RandomSeed_T& iRequestDateTimeSeed,
                             const RandomSeed_T& iDemandCharacteristicsSeed)
    : _key (iKey),
      _demandCharacteristics (iDemandCharacteristics),
      _demandDistribution (iDemandDistribution),
      _totalNumberOfRequestsToBeGenerated (0),
      _numberOfRequestsRandomGenerator (iNumberOfRequestsSeed),
      _requestDateTimeRandomGenerator (iRequestDateTimeSeed),
      _demandCharacteristicsRandomGenerator (iDemandCharacteristicsSeed) {
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  DemandStream::~DemandStream () {
  }

  // //////////////////////////////////////////////////////////////////////
  void DemandStream::init() {
    // Generate the number of requests
    const RealNumber_T lMu = _demandDistribution.getMeanNumberOfRequests ();
    const RealNumber_T lSigma =
      _demandDistribution.getStandardDeviationNumberOfRequests ();
    const RealNumber_T lRealNumberOfRequestsToBeGenerated =
      _numberOfRequestsRandomGenerator.generateNormal (lMu, lSigma);
    Count_T lIntegerNumberOfRequestsToBeGenerated = 0;
    if (lRealNumberOfRequestsToBeGenerated < 0.5) {
    	lIntegerNumberOfRequestsToBeGenerated = 0;
    } else {
    	lIntegerNumberOfRequestsToBeGenerated =
          static_cast<Count_T> (lRealNumberOfRequestsToBeGenerated + 0.5);
    }
    _totalNumberOfRequestsToBeGenerated = lIntegerNumberOfRequestsToBeGenerated;
  }
  
  // //////////////////////////////////////////////////////////////////////
  bool DemandStream::generateNext (BookingRequestStruct& ioRequest) {
    // Check whether enough requests have already been generated
    const Count_T lNbOfRequestsGeneratedSoFar =
      _randomGenerationContext.getNumberOfRequestsGeneratedSoFar ();
    const Count_T lRemainingNumberOfRequestsToBeGenerated =
      _totalNumberOfRequestsToBeGenerated - lNbOfRequestsGeneratedSoFar;

    if (lRemainingNumberOfRequestsToBeGenerated <= 0) {
      return false;
    }
      // DEBUG
      STDAIR_LOG_DEBUG ("Here");

    // Origin
    ioRequest.setOrigin (_demandCharacteristics.getOrigin ());

    // Preferred departure date
    const Date_T lPreferredDepartureDate =
      _demandCharacteristics.getPreferredDepartureDate ();
    ioRequest.setPreferredDepartureDate (lPreferredDepartureDate);

    // Request datetime, determined from departure date and arrival pattern
    // Sequential generation
    const Probability_T lCumulativeProbabilitySoFar =
      _randomGenerationContext.getCumulativeProbabilitySoFar ();

    const Probability_T lVariate =
      _requestDateTimeRandomGenerator.generateUniform01 ();

    const Probability_T lCumulativeProbabilityThisRequest =
      1.0 - (1.0 - lCumulativeProbabilitySoFar) * pow(1 - lVariate, 1.0 / static_cast<float> (lRemainingNumberOfRequestsToBeGenerated));

    const FloatDuration_T lNumberOfDaysBetweenDepartureAndThisRequest =
      _demandCharacteristics.getArrivalPattern().getValue (lCumulativeProbabilityThisRequest);

    // convert the number of days in number of seconds + number of milliseconds
    const FloatDuration_T lNumberOfSeconds =
      lNumberOfDaysBetweenDepartureAndThisRequest*static_cast<float> (SECONDS_IN_ONE_DAY);

    const IntDuration_T lIntNumberOfSeconds = floor(lNumberOfSeconds);

    const FloatDuration_T lNumberOfMilliseconds =
      (lNumberOfSeconds - lIntNumberOfSeconds) * static_cast<float> (MILLISECONDS_IN_ONE_SECOND);

    const IntDuration_T lIntNumberOfMilliseconds =
      floor(lNumberOfMilliseconds) + 1; // +1 is a trick to ensure that the next event is strictly later than the current one

    const Duration_T lDifferenceBetweenDepartureAndThisRequest =
      boost::posix_time::seconds(lIntNumberOfSeconds) + boost::posix_time::millisec(lIntNumberOfMilliseconds);

    const Time_T lHardcodedReferenceDepartureTime = boost::posix_time::hours(8);
    
const DateTime_T lDepartureDateTime =
      boost::posix_time::ptime(lPreferredDepartureDate, lHardcodedReferenceDepartureTime);

    const DateTime_T lDateTimeThisRequest =
      lDepartureDateTime + lDifferenceBetweenDepartureAndThisRequest;
    ioRequest.setRequestDateTime (lDateTimeThisRequest);

    // Update random generation context
    _randomGenerationContext.setCumulativeProbabilitySoFar (lCumulativeProbabilityThisRequest);
    _randomGenerationContext.incrementGeneratedRequestsCounter ();
   
    return true;
    
  }

}
