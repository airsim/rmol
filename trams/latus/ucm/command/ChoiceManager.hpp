#ifndef __LATUS_UCM_CMD_CHOICEMANAGER_HPP
#define __LATUS_UCM_CMD_CHOICEMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/TravelSolutionBlock.hpp>
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  namespace UCM {

    /** Class holding the code for the User Choice Use-Case. */
    class ChoiceManager : COM::CmdAbstract {
    public:

      /** Choose a product from a given list of products.
          @return The vector of Travel Solutions (TS). */
      static void chooseTravelSolution (COM::TravelSolutionBlock& loTSB);

    private:
      /** Constructors. */
      ChoiceManager ();
      ChoiceManager (const ChoiceManager&);
      
      /** Destructor. */
      ~ChoiceManager ();
    };

  }
}
#endif // __LATUS_UCM_CMD_CHOICEMANAGER_HPP
