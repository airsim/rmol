#ifndef __LATUS_COM_FAC_FACSEGMENTCABIN_HPP
#define __LATUS_COM_FAC_FACSEGMENTCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct SegmentCabinKey_T;
    class SegmentCabin;
    
    /** Factory for SegmentCabin objects. */
    class FacSegmentCabin : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacSegmentCabin& */
      static FacSegmentCabin& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacSegmentCabin::instance() */
      virtual ~FacSegmentCabin();

      /** Create a new SegmentCabin object.
          <br>This new object is added to the list of instantiated objects.
          @return SegmentCabin& The newly created object. */
      SegmentCabin& create (const SegmentCabinKey_T&);


    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacSegmentCabin () {}

    private:
      /** The unique instance.*/
      static FacSegmentCabin* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACSEGMENTCABIN_HPP
