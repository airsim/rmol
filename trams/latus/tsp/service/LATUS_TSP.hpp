#ifndef __LATUS_TSP_SVC_LATUS_TSP_HPP
#define __LATUS_TSP_SVC_LATUS_TSP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/TravelSolutionBlock.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {
  
  namespace TSP {

    /** Service (Interface) class for the Tspentory module. */
    class LATUS_TSP : public COM::LATUS_ServiceAbstract {
      // Only FacTspService_Service may instantiate LATUS_TSP
      friend class FacTspService;
    public:
      /** Parses the CSV file describing the airline schedules for the
          simulator, and generates the inventories accordingly.
          The schedule file name is stored within the (TSP-specific)
          ServiceContext object. */
      static void generateInventories ();


      /** Calculate and return the travel solutions corresponding to a given
          product demand.
          @return The vector of availabilities per class/bucket. */
      static void getTravelSolutions (const COM::AirportCode_T& iOrigin,
                                      const COM::AirportCode_T& iDestination,
                                      const COM::DateTime_T& iDate,
                                      COM::TravelSolutionBlock&);


    private:
      /** Constructors. */
      LATUS_TSP ();
      /** Destructor. */
      ~LATUS_TSP();

    };
  }
}
#endif // __LATUS_TSP_SVC_LATUS_TSP_HPP
