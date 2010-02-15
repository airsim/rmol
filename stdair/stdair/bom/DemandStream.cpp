// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iosfwd>
#include <ostream>
#include <sstream>
#include <cmath>
// Boost
#include <boost/math/distributions/normal.hpp>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/DemandCharacteristics.hpp>
#include <stdair/basic/RandomGeneration.hpp>
#include <stdair/basic/RandomGenerationContext.hpp>
#include <stdair/bom/BookingRequestStruct.hpp>
#include <stdair/bom/DemandStream.hpp>
#include <stdair/service/Logger.hpp>


namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  DemandStream::
  DemandStream (const DemandStreamKey_T& iKey,
                const DemandCharacteristics& iDemandCharacteristics,
                const DemandDistribution& iDemandDistribution,
                const RandomSeed_T& iNumberOfRequestsSeed,
                const RandomSeed_T& iRequestDateTimeSeed,
                const RandomSeed_T& iDemandCharacteristicsSeed,
                BomStructure_T& ioDemandStreamStructure)
    : DemandStreamContent (iKey, iDemandCharacteristics,
                           iDemandDistribution, iNumberOfRequestsSeed,
                           iRequestDateTimeSeed, iDemandCharacteristicsSeed),
      _demandStreamStructure (ioDemandStreamStructure) {
  }

  // //////////////////////////////////////////////////////////////////////
  DemandStream::~DemandStream () {
  }
}
