#ifndef __LATUS_COM_BOM_TRAVELSOLUTIONBLOCK_HPP
#define __LATUS_COM_BOM_TRAVELSOLUTIONBLOCK_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/TravelSolutionList.hpp>
#include <latus/com/bom/TravelSolutionBlockKey.hpp>

namespace LATUS {

   // Forward declarations
  namespace CRS {
    class LATUS_CRS;
  }
  
  namespace COM {

    /** Class wrapping the travels solutions. */
    class TravelSolutionBlock : public BomAbstract {
      friend class FacTravelSolutionBlock;
      friend class AirportDate;
      friend class CRS::LATUS_CRS;
    public:
      // /////////// Getters //////////////
      /** Get the AirportDate (parent class). */
      AirportDate* getAirportDate() const {
        return _airportDate;
      }

      /** Get the primary key. */
      const TravelSolutionBlockKey_T& getPrimaryKey() const {
        return _key;
      }

      /** Get the number of travel solutions. */
      const TravelSolutionNumber_T& getTravelSolutionNumber() const {
        return _travelSolutionNumber;
      }

      /** Get the destination (part of the primary key). */
      const AirportCode_T& getDestination() const {
        return _key.destination;
      }

       /** Get the list of travel solutions. */
      TravelSolutionList_T& getTravelSolutionList() {
        return _travelSolutionList;
      }

      // ///////// Setters //////////
      /** Set the AirportDate (parent class). */
      void setAirportDate (AirportDate* ioAirportDatePtr) {
        _airportDate = ioAirportDatePtr;
      }

       /** Calculation of the number of  travel solutions. */
      void incrementTravelSolutionNumber () {
        _travelSolutionNumber +=1;
      }
     
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
      TravelSolutionBlock (const TravelSolutionBlockKey_T&); 

      /** Default constructors. */
      TravelSolutionBlock ();
      TravelSolutionBlock (const TravelSolutionBlock&);
      
      /** Destructor. */
      virtual ~TravelSolutionBlock();


    private:

      // Parent
      /** AirportDate associated to this travel solution block. */
      AirportDate* _airportDate;

      // Primary Key
      /**  Key is composed of the origin airportDateKey, destination airport code
           and the travel solution number. */
      TravelSolutionBlockKey_T _key;

      /*Number of travel solutions.*/
      TravelSolutionNumber_T _travelSolutionNumber;


      /** TravelSolutionList_T which is a STL multimap linking
          TravelSolution Keys and Travel Solutions. */
      TravelSolutionList_T _travelSolutionList;
      
    };

  }
}
#endif // __LATUS_COM_BOM_TRAVELSOLUTIONBLOCK_HPP
