#ifndef __LATUS_SIM_SVC_LATUS_SIM_HPP
#define __LATUS_SIM_SVC_LATUS_SIM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {

  namespace SIM {

    // TODO: Add the (GSL) random seed in the service context, so that
    // it is not re-set at each new simulation
    
    /** Class wrapping the services offered by the SIM module. */
    class LATUS_SIM : public COM::LATUS_ServiceAbstract {
    public:
      /** Main entry point. */
      static void simulate ();
      
    private:
      /** Constructors. */
      LATUS_SIM();
      /** Destructor. */
      ~LATUS_SIM();
    };
    
  }
}
#endif // __LATUS_SIM_SVC_LATUS_SIM_HPP
