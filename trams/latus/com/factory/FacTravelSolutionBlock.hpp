#ifndef __LATUS_COM_FAC_FACTRAVELSOLUTIONBLOCK_HPP
#define __LATUS_COM_FAC_FACTRAVELSOLUTIONBLOCK_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Factory for TravelSolution objects. */
    class FacTravelSolutionBlock : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacTravelSolutionBlock& */
      static FacTravelSolutionBlock& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacTravelSolutionBlock::instance() */
      virtual ~FacTravelSolutionBlock();

      /** Create a new TravelSolutionBlock object.
          <br>This new object is added to the list of instantiated objects.
          @return TravelSolutionBlock& The newly created object. */
      TravelSolutionBlock& create (const TravelSolutionBlockKey_T&);

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacTravelSolutionBlock () {}

    private:
      /** The unique instance.*/
      static FacTravelSolutionBlock* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACTRAVELSOLUTIONBLOCK_HPP
