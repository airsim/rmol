#ifndef __LATUS_COM_FAC_FACTRAVELSOLUTION_HPP
#define __LATUS_COM_FAC_FACTRAVELSOLUTION_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct TravelSolutionKey_T;
    class TravelSolution;
    
    /** Factory for TravelSolution objects. */
    class FacTravelSolution : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacTravelSolution& */
      static FacTravelSolution& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacTravelSolution::instance() */
      virtual ~FacTravelSolution();

      /** Create a new TravelSolution object.
          <br>This new object is added to the list of instantiated objects.
          @return TravelSolution& The newly created object. */
      TravelSolution& create (const TravelSolutionKey_T&);

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacTravelSolution () {}

    private:
      /** The unique instance.*/
      static FacTravelSolution* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACTRAVELSOLUTION_HPP
