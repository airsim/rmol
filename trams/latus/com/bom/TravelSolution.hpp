#ifndef __LATUS_COM_BOM_TRAVELSOLUTION_HPP
#define __LATUS_COM_BOM_TRAVELSOLUTION_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/TravelSolutionKey.hpp>
#include <latus/com/bom/ClassStruct.hpp>

namespace LATUS {

 namespace COM {

   // Forward declarations
   class OutboundPath;
   class TravelSolutionBlock;
   
   /** Class wrapping the Travel-Solution specific attributes and methods. */
   class TravelSolution : public BomAbstract {
     friend class FacTravelSolution;
     friend class AirportDate;
   public:
     // /////////// Getters //////////////
      /** Get the fare associated to the current travel solution. */
      const Fare_T& getFare () const {
        return _fare;
      }

       /** Get the availability of the current travel solution . */
      const Availability_T& getTSAvailability () const {
        return _tSAvailability;
      }

      /** Get the primary key. */
      const TravelSolutionKey_T& getPrimaryKey() const {
        return getTravelSolutionKey();
      }

      /** Get the travel solution key. */
      const TravelSolutionKey_T& getTravelSolutionKey() const {
        return _key;
      }

      /** Get the outboundpath associated to this travel solution. */
      OutboundPath* getOutboundPath() const {
        return _outboundPath_ptr;
      }

      // ///////// Setters //////////
      /** Set the OutboundPath. */
      void setOutboundPath (OutboundPath* ioOutboundPathPtr) {
        _outboundPath_ptr = ioOutboundPathPtr;
      }

      /** Set the OutboundPath. */
      void setTSAvailability (const Availability_T& tsAvailable) {
        _tSAvailability = tsAvailable;
      }

     // ///////// Business method //////////
     /** Method building the cheapest solution .*/
     bool buildCheapestAvailableSolution (const SeatNumber_T& lSN);
     
     /** Method computing availabilities from the cheapest travel solution .*/
     void calculateAvailabilities ();

     /** Method updating the required inventory. */ 
     bool sell (const BookingNumber_T&) const;

     /** Method computing the fare of the travel solution. */
     void fareQuote();
      

      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full travel solution context. */
      void display() const;

        private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      TravelSolution (const TravelSolutionKey_T&);

      /** Default constructors. */
      TravelSolution ();
      TravelSolution (const TravelSolution&);

      /** Destructor. */
      virtual ~TravelSolution();
     
   private:

      // Primary Key
      /** TravelSolution Key is composed of the destination airport, elapsed
          time, number of segments and number of airlines. */
      TravelSolutionKey_T _key;

      /** The outbound path associated to this solution.*/
     OutboundPath* _outboundPath_ptr;
     
      /** Value of the travel solution associated to the outbound path. */
      Fare_T _fare;

      /** Availability of the travel solution . */
      Availability_T _tSAvailability;

      /** ClassStruct vector describing the cheapest solution
          corresponding to the current travel solution. */
      ClassStructList_T _classStructList;
   };
   
 }
}
#endif // __LATUS_COM_BOM_TRAVELSOLUTION_HPP
