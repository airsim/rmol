#ifndef __LATUS_COM_FAC_FACSEGMENTDATE_HPP
#define __LATUS_COM_FAC_FACSEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>


namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct SegmentDateKey_T;
    class SegmentDate;
    class SegmentCabin;
    
    /** Factory for SegmentDate objects. */
    class FacSegmentDate : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacSegmentDate& */
      static FacSegmentDate& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacSegmentDate::instance() */
      virtual ~FacSegmentDate();

      /** Create a new SegmentDate object.
          <br>This new object is added to the list of instantiated objects.
          @return SegmentDate& The newly created object. */
      SegmentDate& create (const SegmentDateKey_T&);

      /** Initialise the link between a SegmentDate and a SegmentCabin.
          @param SegmentDate&
          @param SegmentCabin&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithSegmentCabin (SegmentDate&, SegmentCabin&);

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacSegmentDate () {}

    private:
      /** The unique instance.*/
      static FacSegmentDate* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACSEGMENTDATE_HPP
