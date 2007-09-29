#ifndef __LATUS_COM_BOM_TRAVELSOLUTION_HPP
#define __LATUS_COM_BOM_TRAVELSOLUTION_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/TravelSolutionKey.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

 namespace COM {

   // Forward declarations
   class OutboundPath;
   class TravelSolutionBlock;
   
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
        return _outboundPath;
      }

      // ///////// Setters //////////
      /** Set the OutboundPath. */
      void setOutboundPath (OutboundPath* ioOutboundPathPtr) {
        _outboundPath = ioOutboundPathPtr;
      }

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
     OutboundPath* _outboundPath;
     
      /** Value of the travel solution associated to the outbound path. */
      Fare_T _fare;

      /** Availability of the travel solutrion . */
      Availability_T _tSAvailability;

      /** Map associated each segment date to the class struct pointer
          corresponding to the current travel solution. */
     // TravelSolutionList_T tsMap;
   };
   
 }
}
#endif // __LATUS_COM_BOM_TRAVELSOLUTION_HPP
