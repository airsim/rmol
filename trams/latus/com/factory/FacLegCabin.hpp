#ifndef __LATUS_COM_FAC_FACLEGCABIN_HPP
#define __LATUS_COM_FAC_FACLEGCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct LegCabinKey_T;
    class LegCabin;
    class SegmentCabin;
    
    /** Factory for LegCabin objects. */
    class FacLegCabin : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacLegCabin& */
      static FacLegCabin& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacLegCabin::instance() */
      virtual ~FacLegCabin();

      /** Create a new LegCabin object.
          <br>This new object is added to the list of instantiated objects.
          @return LegCabin& The newly created object. */
      LegCabin& create (const LegCabinKey_T&);

      /** Initialise the link between a LegCabin and a SegmentCabin.
          <br>That method creates links in both directions. For the
          SegmentCabin->LegCabin direction, the corresponding method is
          called on FacSegmentCabin.
          @param LegCabin&
          @param SegmentCabin&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithSegmentCabin (LegCabin&, SegmentCabin&);


    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacLegCabin () {}

    private:
      /** The unique instance.*/
      static FacLegCabin* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACLEGCABIN_HPP
