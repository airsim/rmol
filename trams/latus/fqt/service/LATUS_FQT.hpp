#ifndef __LATUS_FQT_SVC_LATUS_FQT_HPP
#define __LATUS_FQT_SVC_LATUS_FQT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/TravelSolutionBlock.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {

  namespace FQT {

    /** Service (Interface) class for the Fare Quote (FQT) module. */
    class LATUS_FQT : public COM::LATUS_ServiceAbstract {
    public:

      /** Calculate and return the price quotations corresponding to a given
          list of products.
          @return The vector of Travel Solutions (TS). */
      static void quoteTravelSolutions (COM::TravelSolutionBlock& iTSB);


    private:
      /** Constructors. */
      LATUS_FQT ();
      /** Destructor. */
      ~LATUS_FQT();
    };

  }
}
#endif // __LATUS_FQT_SVC_LATUS_FQT_HPP
