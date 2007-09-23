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
      WorldSchedule& create (const DateTime_T& iUpdateDate);

      /** Initialise the link between a WorldSchedule and a Schedule.
          @param WorldSchedule&
          @param Inventory&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithInventory (WorldSchedule&, Inventory&);

      /** Create the routing between the legs and segments for all the
          Inventories of the given WorldSchedule object. */
      static void createRouting (WorldSchedule&);
      

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
