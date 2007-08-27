// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <string>
// Boost Spirit (Parsing)
//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/core.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
// LATUS Common
#include <latus/com/basic/BasConst_WorldSchedule.hpp>
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/factory/FacWorldSchedule.hpp>
// LATUS TSP
#include <latus/tsp/command/ScheduleParserHelper.hpp>
#include <latus/tsp/command/ScheduleParser.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    COM::WorldSchedule& ScheduleParser::
    generateInventories (const std::string& iFilename) {
      COM::WorldSchedule& oWorldSchedule =
        COM::FacWorldSchedule::instance().
        create (COM::DEFAULT_WORLD_SCHEDULE_UPDATE_DATE);

      // Initialise the Flight-Period file parser.
      FlightPeriodFileParser lFlightPeriodParser (oWorldSchedule, iFilename);

      // Parse the CSV-formatted schedule input file, and generate the
      // corresponding Inventories for the airlines.
      lFlightPeriodParser.generateInventories ();

      return oWorldSchedule;
    }

  }
}
