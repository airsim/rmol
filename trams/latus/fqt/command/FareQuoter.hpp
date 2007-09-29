#ifndef __LATUS_FQT_CMD_FAREQUOTER_HPP
#define __LATUS_FQT_CMD_FAREQUOTER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/TravelSolutionBlock.hpp>
// LATUS Command
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  namespace FQT {

    /** Class holding the code for the Fare Quotation Use-Case. */
    class FareQuoter : COM::CmdAbstract {
    public:

      /** Calculate and return the price quotations corresponding to a given
          list of products.
          @return The vector of Travel Solutions (TS). */
      static void quoteTravelSolutions (COM::TravelSolutionBlock& iTSL);

    private:
      /** Constructors. */
      FareQuoter();
      FareQuoter (const FareQuoter&);
      
      /** Destructor. */
      ~FareQuoter();
    };

  }
}
#endif // __LATUS_FQT_CMD_FAREQUOTER_HPP
