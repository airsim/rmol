// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/DemandStream.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/factory/FacSupervisor.hpp>
#include <stdair/factory/FacBomContent.hpp>

namespace stdair {
  
  FacBomContent* FacBomContent::_instance = NULL;

  // ////////////////////////////////////////////////////////////////////
  FacBomContent& FacBomContent::instance () {

    if (_instance == NULL) {
      _instance = new FacBomContent();
      assert (_instance != NULL);

      FacSupervisor::instance().registerBomContentFactory (_instance);
    }
    return *_instance;
  }

  // //////////////////////////////////////////////////////////////////////
  FacBomContent::~FacBomContent() {
    clean ();
  }

  // //////////////////////////////////////////////////////////////////////
  void FacBomContent::clean() {
    for (BomContentPool_T::iterator itBom = _contentPool.begin();
	 itBom != _contentPool.end(); itBom++) {
      BomContent* currentBom_ptr = *itBom;
      assert (currentBom_ptr != NULL);

      delete currentBom_ptr; currentBom_ptr = NULL;
    }

    // Empty the pool of Factories
    _contentPool.clear();

    // Reset the static instance
    _instance = NULL;
  }

  // ////////////////////////////////////////////////////////////////////
  DemandStream& FacBomContent::
  createDemandStream (const DemandStreamKey_T& iKey,
                      const DemandCharacteristics& iDemandCharacteristics,
                      const DemandDistribution& iDemandDistribution,
                      const RandomSeed_T& iNumberOfRequestsSeed,
                      const RandomSeed_T& iRequestDateTimeSeed,
                      const RandomSeed_T& iDemandCharacteristicsSeed) {
    DemandStream* aDemandStream_ptr = NULL;

    aDemandStream_ptr = new DemandStream (iKey, iDemandCharacteristics,
                                          iDemandDistribution,
                                          iNumberOfRequestsSeed,
                                          iRequestDateTimeSeed,
                                          iDemandCharacteristicsSeed);
    assert (aDemandStream_ptr != NULL);

    // The new object is added to the BOM pool
    _contentPool.push_back (aDemandStream_ptr);

    return *aDemandStream_ptr;
  }
  
}
