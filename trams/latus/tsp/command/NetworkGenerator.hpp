#ifndef __LATUS_TSP_CMD_NETWORKGENERATOR_HPP
#define __LATUS_TSP_CMD_NETWORKGENERATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  // Forward declarations
  namespace COM {
    class Network;
    class NetworkDate;
    class AirportDate;
    class WorldSchedule;
    class Inventory;
    class FlightDate;
    class SegmentDate;
  }
  
  namespace TSP {

    /** Class handling the generation / instantiation of the Network BOM. */
    class NetworkGenerator : public COM::CmdAbstract {
      friend class LATUS_TSP;
    private:
      /** Generate the full Network BOM corresponding to the given
          WorldSchedule. */
      static COM::Network& createNetwork (const COM::WorldSchedule&);

      /** Generate the AirportDate and OutboundPath objects corresponding to
          the given WorldSchedule, and add them to the given Network. */
      static void createNetwork (COM::Network&, const COM::WorldSchedule&);

      /** Generate the AirportDate and OutboundPath objects corresponding to
          the given Inventory, and add them to the given Network. */
      static void createSinglePaths (COM::Network&, const COM::Inventory&);

      /** Generate the AirportDate and OutboundPath objects corresponding to
          the given FlightDate, and add them to the given Network. */
      static void createSinglePaths (COM::Network&, const COM::FlightDate&);

      /** Generate the AirportDate and OutboundPath objects corresponding to
          the given SegmentDate, and add them to the given Network. */
      static void createSinglePaths (COM::Network&, const COM::SegmentDate&);

      /** Generate the AirportDate and OutboundPath objects corresponding to
          the given SegmentDate, and add them to the given NetworkDate. */
      static void createSinglePaths (COM::NetworkDate&,
                                     const COM::SegmentDate&);

      /** Generate the OutboundPath object corresponding to
          the given SegmentDate, and add them to the given AirportDate. */
      static void createSinglePaths (COM::AirportDate&,
                                     const COM::SegmentDate&);

      /** Generate the i-fixed-length list of OutboundPath objects for the
          given number of segments (i). */
      static void createNetwork (COM::Network&, const COM::SegmentNumber_T&);

      /** Generate the i-fixed-length list of OutboundPath objects for the
          given number of segments (i). */
      static void createNetwork (COM::NetworkDate&,
                                 const COM::SegmentNumber_T&);

      /** Generate the i-fixed-length list of OutboundPath objects for the
          given number of segments (i). */
      static void createNetwork (COM::AirportDate&,
                                 const COM::SegmentNumber_T&);
    };

  }
}
#endif // __LATUS_TSP_CMD_NETWORKGENERATOR_HPP
