#ifndef __LATUS_TSP_CMD_INVENTORYGENERATOR_HPP
#define __LATUS_TSP_CMD_INVENTORYGENERATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  // Forward declarations
  namespace COM {
    class WorldSchedule;
    class Inventory;
    class FlightDate;
    class LegDate;
    class LegCabin;
    class SegmentDate;
    class SegmentCabin;
  }
  
  namespace TSP {

    // Forward declarations
    struct FlightPeriodStruct_T;
    namespace ScheduleParserHelper {
      struct doEndFlight;
    }
    
    /** Class handling the generation / instantiation of the Inventory BOM. */
    class InventoryGenerator : public COM::CmdAbstract {
      // Only the following class may use methods of InventoryGenerator.
      // Indeed, as those methods build the BOM, it is not good to expose
      // them publicly.
      friend class FlightPeriodFileParser;
      friend struct ScheduleParserHelper::doEndFlight;
    private:
      /** Generate the Flight-Date objects corresponding to the given
          Flight-Period, and add them to the given WorldSchedule. */
      static void createFlightDates (COM::WorldSchedule&,
                                     const FlightPeriodStruct_T&);
       /** Generate an Inventory. */
      static COM::Inventory& createInventory (COM::WorldSchedule&,
                                              const COM::AirlineCode_T&);
      
      /** Generate a FlightDate. */
      static void createFlightDate (COM::Inventory&,
                                    const COM::DateTime_T& iFlightDate,
                                    const FlightPeriodStruct_T&);
      
      /** Generate a LegDate. */
      static COM::LegDate& createLegDate (COM::FlightDate&,
                                          const COM::DateTime_T& iReferenceDate,
                                          const LegStruct_T& iLeg);

      /** Generate a LegCabin. */
      static void createLegCabin (COM::LegDate&, const LegCabinStruct_T&);
      
      /** Generate a SegmentDate. */
      static void createSegmentDate (COM::FlightDate&, const SegmentStruct_T&);
      
      /** Generate a SegmentCabin. */
      static void createSegmentCabin (COM::SegmentDate&,
                                      const SegmentCabinStruct_T&);
      
      /** Generate a Class. */
      static void createClass (COM::SegmentCabin&, const COM::ClassCode_T&);

    public:
      /** Create the routing between the legs and segments for all the
          Inventories of the given WorldSchedule object. */
      static void createRouting (COM::WorldSchedule&);

       /** Compute the number of available seats
          for all flights. */
      static void recalculateAvailabilities (COM::WorldSchedule&);
    };

  }
}
#endif // __LATUS_TSP_CMD_INVENTORYGENERATOR_HPP
