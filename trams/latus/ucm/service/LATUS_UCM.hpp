#ifndef __LATUS_UCM_SVC_LATUS_UCM_HPP
#define __LATUS_UCM_SVC_LATUS_UCM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/TravelSolutionBlock.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {

  namespace UCM {

    /** Service (Interface) class for the User Choice (UC) module. */
    class LATUS_UCM : public COM::LATUS_ServiceAbstract {
    public:

      /** Choose a product from a given list of products.
          @return The vector of Travel Solutions (TS). */
      static void chooseTravelSolution (COM::TravelSolutionBlock& ioTSLB);
    private:
      /** Constructors. */
      LATUS_UCM ();
      LATUS_UCM (const LATUS_UCM&);
      
      /** Destructor. */
      ~LATUS_UCM();
    };

  }
}
#endif // __LATUS_UCM_SVC_LATUS_UCM_HPP
