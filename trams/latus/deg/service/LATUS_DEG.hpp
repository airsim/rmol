#ifndef __LATUS_DEG_SVC_LATUS_DEG_HPP
#define __LATUS_DEG_SVC_LATUS_DEG_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {

  namespace DEG {

    // TODO: Add the (GSL) random seed in the service context, so that
    // it is not re-set at each new simulation
    
    /** Class wrapping the services offered by the DEG module. */
    class LATUS_DEG : public COM::LATUS_ServiceAbstract {
      // Only FacDegService_Service may instantiate LATUS_DEG
      friend class FacDegService;
    public:
      /** Main entry point: generate an event. */
      void generateEvent () const;
      
    private:
      /** Default Constructors. */
      LATUS_DEG ();
      /** Destructor. */
      ~LATUS_DEG();

    private:
      // Attributes
    };
  }
}
#endif // __LATUS_DEG_SVC_LATUS_DEG_HPP
