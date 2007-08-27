// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/OutboundPathKey.hpp>
#include <latus/com/bom/OutboundPath.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacOutboundPath.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacOutboundPath* FacOutboundPath::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacOutboundPath::~FacOutboundPath () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacOutboundPath& FacOutboundPath::instance () {

      if (_instance == NULL) {
        _instance = new FacOutboundPath();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    OutboundPath& FacOutboundPath::create (const OutboundPathKey_T& iKey) {
      OutboundPath* aOutboundPath_ptr = NULL;

      aOutboundPath_ptr = new OutboundPath (iKey);
      assert (aOutboundPath_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aOutboundPath_ptr);

      return *aOutboundPath_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacOutboundPath::
    initLinkWithSegmentDate (OutboundPath& ioOutboundPath,
                             const SegmentDate& ioSegmentDate) {
      // Link the OutboundPath to the SegmentDate
      ioOutboundPath._segmentDateLightList.push_back (&ioSegmentDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void FacOutboundPath::
    cloneSegmentDateLinks (OutboundPath& ioOutboundPath,
                           const OutboundPath& iReferenceOutboundPath) {
      // Clone the list of SegmentDate pointers.
      ioOutboundPath._segmentDateLightList =
        iReferenceOutboundPath._segmentDateLightList;
    }
    
  }
}
