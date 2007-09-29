// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/bom/Network.hpp>
#include <latus/com/bom/NetworkDate.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS TSP
#include <latus/tsp/command/ScheduleParser.hpp>
#include <latus/tsp/command/NetworkGenerator.hpp>
#include <latus/tsp/service/LATUS_TSP.hpp>

namespace LATUS {
  
  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    LATUS_TSP::LATUS_TSP () {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_TSP::~LATUS_TSP () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_TSP::generateInventories () {
      // Retrieve the schedule input filename from the TSP specific
      // service context
      const std::string& lScheduleInputFilename = getScheduleInputFilename ();

      // Parse the schedule input file, and generate the Inventories
      COM::WorldSchedule& lWorldSchedule =
        ScheduleParser::generateInventories (lScheduleInputFilename);

      // Store the WorldSchedule within the TSP specific service context
      setWorldSchedule (lWorldSchedule);

      // DEBUG
      LATUS_LOG_DEBUG ("Generated WorldSchedule:");
      lWorldSchedule.display();

      // From the WorldSchedule (full) BOM, create the Network (full) BOM.
      COM::Network& lNetwork = NetworkGenerator::createNetwork (lWorldSchedule);

      // Store the Network within the TSP specific service context
      setNetwork (lNetwork);

      // DEBUG
      LATUS_LOG_DEBUG ("Generated Network:");
      lNetwork.display();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LATUS_TSP::getTravelSolutions (const COM::AirportCode_T& iOrigin,
                                        const COM::AirportCode_T& iDestination,
                                        const COM::DateTime_T& iDate,
                                        COM::TravelSolutionBlock& ioTSolutions) {

      // DEBUG
      LATUS_LOG_DEBUG ("Travel Solutions for: "
                       << iOrigin << "-" << iDestination << " / " << iDate);
      
      // Retrieve the Network
      const COM::Network& lNetwork = getNetwork();

      // Retrieve the NetworkDate for that departure date.
      const COM::NetworkDate* lNetworkDate_ptr =
        lNetwork.getNetworkDate (iDate);

      // If there is no NetworkDate for that departure date, there is no
      // travel solution, and there is therefore nothing more to be done
      // (the list of Travel Solutions stay empty).
      if (lNetworkDate_ptr == NULL) {
        return;
      }
      assert (lNetworkDate_ptr != NULL);

      // Retrieve the AirportDate for that origin.
      COM::AirportDate* lAirportDate_ptr =
        lNetworkDate_ptr->getAirportDate (iOrigin);
      
      // If there is no AirportDate for that departure date, there is no
      // travel solution, and there is therefore nothing more to be done
      // (the list of Travel Solutions stay empty).
      if (lAirportDate_ptr == NULL) {
        return;
      }
      assert (lAirportDate_ptr != NULL);

      ioTSolutions.setAirportDate(lAirportDate_ptr);

      // Retrieve all the outbound paths from the airport-date, i.e., all the
      // travel solutions from the origin airport to the destination airport
      // for that departure date.
      lAirportDate_ptr->createTravelSolutionList (iDestination, ioTSolutions);
    }
    
  }
}
