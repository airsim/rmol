#ifndef __RMOL_FAC_FACOVERBOOKING_HPP
#define __RMOL_FAC_FACOVERBOOKING_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/factory/FacBomAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class FldOverbookingPolicy;
  class Overbooking;

  /** Factory for Overbooking. */
  class FacOverbooking : public FacBomAbstract {
  public:

    /** Provide the unique instance.
        <br> The singleton is instantiated when first used
        @return FacOverbooking& */
    static FacOverbooking& instance();

    /** Destructor.
        <br> The Destruction put the _instance to NULL
        in order to be clean for the next FacOverbooking::instance() */
    virtual ~FacOverbooking();

    /** Create a new Overbooking object.
        <br>This new object is added to the list of instantiated objects.
        @return Overbooking& The newly created object. */
    Overbooking& create (const FldOverbookingPolicy&);
    
  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacOverbooking () {}

  private:
    /** The unique instance.*/
    static FacOverbooking* _instance;

  };
}
#endif // __RMOL_FAC_FACOVERBOOKING_HPP
