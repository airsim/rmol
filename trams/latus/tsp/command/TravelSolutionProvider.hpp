#ifndef __LATUS_TSP_CMD_TRAVELSOLUTIONPROVIDER_HPP
#define __LATUS_TSP_CMD_TRAVELSOLUTIONPROVIDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/command/CmdAbstract.hpp>


namespace LATUS {

  // Forward declarations
  namespace COM {
    class AirportDate;
    class TravelSolutionBlock;
    class TravelSolution;
    class OutboundPathList;
  }
  
  namespace TSP {

    /** Class handling the generation / instantiation of the travel solution block and travel solutions. */
    class TravelSolutionProvider : public COM::CmdAbstract {
      friend class LATUS_TSP;
    private:
      /** Generate the travel solution block given the corresponding WTP and the given
          WorldSchedule. */
      static void provideTravelSolution (const COM::Network&,
                                         COM::TravelSolutionBlock& ioTSolutions);

      /** Creation of the travel solution set . */
      static void createTravelSolutions (const COM::OutboundPathList_T&,
                                         COM::TravelSolutionBlock& ioTS);
    };

  }
}
#endif // __LATUS_TSP_CMD_TRAVELSOLUTIONPROVIDER_HPP
