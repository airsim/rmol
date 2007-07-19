#ifndef __LATUS_COM_FAC_FACWORLDSCHEDULE_HPP
#define __LATUS_COM_FAC_FACWORLDSCHEDULE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class WorldSchedule;
    class Inventory;
    
    /** Factory for WorldSchedule objects. */
    class FacWorldSchedule : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacWorldSchedule& */
      static FacWorldSchedule& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacWorldSchedule::instance() */
      virtual ~FacWorldSchedule();

      /** Create a new WorldSchedule object.
          <br>This new object is added to the list of instantiated objects.
          @param const boost::gregorian::date& Creation/update date.
          @return WorldSchedule& The newly created object. */
      WorldSchedule& create (const boost::gregorian::date& iUpdateDate);

      /** Initialise the link between a WorldSchedule and a Schedule.
          @param WorldSchedule&
          @param Inventory&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithInventory (WorldSchedule&, Inventory&);

      /** Create a new LegCabin object with the given parameters.
          <br>This new object is added to the list of instantiated objects.
          <br>Any missing intermediary object (Inventory and/or FlightDate)
          will be created and added to the corresponding children list. */
      static void createLegCabin (WorldSchedule&,
                                  const AirlineCode_T&, const FlightNumber_T&,
                                  const AirportCode_T&, const AirportCode_T&,
                                  const DateTime_T&, const CabinCode_T&);
      

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacWorldSchedule () {}

    private:
      /** The unique instance.*/
      static FacWorldSchedule* _instance;
    };

  }

}

#endif // __LATUS_COM_FAC_FACWORLDSCHEDULE_HPP
