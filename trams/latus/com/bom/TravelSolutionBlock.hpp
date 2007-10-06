#ifndef __LATUS_COM_BOM_TRAVELSOLUTIONBLOCK_HPP
#define __LATUS_COM_BOM_TRAVELSOLUTIONBLOCK_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/TravelSolutionList.hpp>
#include <latus/com/bom/WTP.hpp>
#include <latus/com/bom/TravelSolutionBlockKey.hpp>

namespace LATUS {

   // Forward declarations
  namespace CRS {
    class LATUS_CRS;
  }
  
  namespace COM {

    // Forward declarations
    class TravelSolution;
    class AirportDate;

    /** Class wrapping the travels solutions. */
    class TravelSolutionBlock : public BomAbstract {
      friend class FacTravelSolutionBlock;
      friend class CRS::LATUS_CRS;
    public:
      // /////////// Getters //////////////
      /** Get the AirportDate. */
      AirportDate* getAirportDate() const {
        return _airportDate_ptr;
      }

      /** Get the Willingness To Pay. */
      const WTP* getWTP() const {
        return _wTP_ptr;
      }

      /** Get the primary key. */
      const TravelSolutionBlockKey_T& getPrimaryKey() const {
        return _key;
      }

      /** Get the number of travel solutions. */
      const TravelSolutionNumber_T& getTravelSolutionNumber() const {
        return _travelSolutionNumber;
      }

      /** Get the origin (part of the primary key). */
      const AirportCode_T& getOrigin() const {
        return _key.origin;
      }
      
      /** Get the destination (part of the primary key). */
      const AirportCode_T& getDestination() const {
        return _key.destination;
      }

       /** Get the departure date (part of the primary key). */
      const DateTime_T& getDepartureDate() const {
        return _key.dateTime;
      }

       /** Get the number of seats required by the demand. */
      const SeatNumber_T& getSeatNumber() const {
        return _key.seatNumber;
      }

       /** Get the list of travel solutions. */
      TravelSolutionList_T& getTravelSolutionList() {
        return _travelSolutionList;
      }

      // ///////// Setters //////////
      /** Set the AirportDate. */
      void setAirportDate (AirportDate* ioAirportDatePtr) {
        _airportDate_ptr = ioAirportDatePtr;
      }
      
       /** Calculation of the number of  travel solutions. */
      void incrementTravelSolutionNumber () {
        _travelSolutionNumber +=1;
      }

      // ///////// Busines methods //////////
      /** Get the Best travel solution for the demand. */
      TravelSolution* getBestTravelSolution (const SeatNumber_T&) const;
      
      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;


      /** Display the full TravelSolutionBlock context. */
      void display() const;
      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      TravelSolutionBlock (const TravelSolutionBlockKey_T&, const WTP*); 

      /** Default constructors. */
      TravelSolutionBlock ();
      TravelSolutionBlock (const TravelSolutionBlock&);
      
      /** Destructor. */
      virtual ~TravelSolutionBlock();


    private:

      // Parent
      /** AirportDate associated to this travel solution block. */
      AirportDate* _airportDate_ptr;

      // Primary Key
      /**  Key is composed of the origin airportDateKey, destination airport code
           and the travel solution number. */
      TravelSolutionBlockKey_T _key;

      /** The pointer on the willingness to pay object. */
      const WTP* _wTP_ptr;

      /* Number of travel solutions.*/
      TravelSolutionNumber_T _travelSolutionNumber;


      /** TravelSolutionList_T which is a STL multimap linking
          TravelSolution Keys and Travel Solutions. */
      TravelSolutionList_T _travelSolutionList;
      
    };

  }
}
#endif // __LATUS_COM_BOM_TRAVELSOLUTIONBLOCK_HPP
