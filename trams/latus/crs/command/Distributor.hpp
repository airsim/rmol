#ifndef __LATUS_CRS_CMD_DISTRIBUTOR_HPP
#define __LATUS_CRS_CMD_DISTRIBUTOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/TravelSolution.hpp>
#include <latus/com/command/CmdAbstract.hpp>

namespace LATUS {

  namespace COM {
    // Forward declarations
    class WorldSchedule;
  }

  namespace CRS {

    /** Class wrapping the distribution methods. */
    class Distributor : COM::CmdAbstract {
      // Only LATUS_CRS can instantiate Distributor
      friend class LATUS_CRS;
    public:
      // /////////// GETTERS //////////
      /** Get a reference on the (child) WorldSchedule object. */
      COM::WorldSchedule* getWorldSchedule() const {
        return _worldSchedule;
      }

      /** Get a reference on the (child) WorldSchedule object. */
      COM::WorldSchedule& getWorldScheduleRef() const {
        assert (_worldSchedule != NULL);
        return *_worldSchedule;
      }

      // /////////// SETTERS //////////

      
      // ////////// Main Methods ///////////      
      /** Calculate and return the availabilities corresponding to a given
          product.
          @return the list of associated class and the availability value. */
      void provideAvailabilities (COM::TravelSolution& lTS,
                                  const COM::SeatNumber_T& lSN);

      /** Register the sell of a given number of travellers on a given
          Travel Solution.
          <br>The party size may be a floating number, so as to cope with
          overbooking. */
      bool sell (const COM::TravelSolution& lTS,
                 const COM::BookingNumber_T& lPS);


      // ///////// DISPLAY METHODS /////////
      /** Display the BOM objects. */
      void display () const;

      
    private:
      /** Constructors. */
      Distributor (const std::string& iInputFileName);
      
      /** Destructor. */
      virtual ~Distributor();

    private:
      /** Build the BOM thanks to the input file.
          <br>The BOM is composed of objects. */
      bool init ();

    private:
      // Filename of the input file (for test purposes)
      std::string _inputFileName;

      // BOM (the WorldSchedule class is the entry point to the BOM)
      COM::WorldSchedule* _worldSchedule;
    };

  }
}
#endif // __LATUS_CRS_CMD_DISTRIBUTOR_HPP
