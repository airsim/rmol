#ifndef __LATUS_COM_FAC_FACLEGDATE_HPP
#define __LATUS_COM_FAC_FACLEGDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct LegDateKey_T;
    class LegDate;
    class LegCabin;
    class SegmentDate;
    
    /** Factory for LegDate objects. */
    class FacLegDate : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacLegDate& */
      static FacLegDate& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacLegDate::instance() */
      virtual ~FacLegDate();

      /** Create a new LegDate object.
          <br>This new object is added to the list of instantiated objects.
          @return LegDate& The newly created object. */
      LegDate& create (const LegDateKey_T&);

      /** Initialise the link between a LegDate and a LegCabin.
          @param LegDate&
          @param LegCabin&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithLegCabin (LegDate&, LegCabin&);

      /** Initialise the link between a LegDate and a SegmentDate.
          <br>That method creates links in both directions. For the
          SegmentDate->LegDate direction, the corresponding method is
          called on FacSegmentDate.
          @param LegDate&
          @param SegmentDate&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithSegmentDate (LegDate&, SegmentDate&);

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacLegDate () {}

    private:
      /** The unique instance.*/
      static FacLegDate* _instance;
    };
    
  }
}
#endif // __LATUS_COM_FAC_FACLEGDATE_HPP
