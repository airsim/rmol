#ifndef __LATUS_COM_FAC_FACFLIGHTDATE_HPP
#define __LATUS_COM_FAC_FACFLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct FlightDateKey_T;
    class FlightDate;
    class LegDate;
    class SegmentDate;
    
    /** Factory for FlightDate objects. */
    class FacFlightDate : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacFlightDate& */
      static FacFlightDate& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacFlightDate::instance() */
      virtual ~FacFlightDate();

      /** Create a new FlightDate object.
          <br>This new object is added to the list of instantiated objects.
          @return FlightDate& The newly created object. */
      FlightDate& create (const FlightDateKey_T&);

      /** Initialise the link between a FlightDate and a LegDate.
          @param FlightDate&
          @param LegDate&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithLegDate (FlightDate&, LegDate&);

      /** Initialise the link between a FlightDate and a SegmentDate.
          @param FlightDate&
          @param SegmentDate&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithSegmentDate (FlightDate&, SegmentDate&);
    
      /** Create the routing between the legs and segments for the given
          FlightDate object. */
      static void createRouting (FlightDate& ioFlightDate);


    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacFlightDate () {}

    private:
      /** The unique instance.*/
      static FacFlightDate* _instance;
    };
    
  }
}
#endif // __LATUS_COM_FAC_FACFLIGHTDATE_HPP
