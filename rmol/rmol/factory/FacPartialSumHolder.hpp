#ifndef __RMOL_FAC_FACPARTIALSUMHOLDER_HPP
#define __RMOL_FAC_FACPARTIALSUMHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/factory/FacBomAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class PartialSumHolder;

  /** Factory for PartialSum. */
  class FacPartialSumHolder : public FacBomAbstract {
  public:

    /** Provide the unique instance.
        <br> The singleton is instantiated when first used
        @return FacPartialSumHolder& */
    static FacPartialSumHolder& instance();

    /** Destructor.
        <br> The Destruction put the _instance to NULL
        in order to be clean for the next FacPartialSumHolder::instance() */
    virtual ~FacPartialSumHolder();

    /** Create a new PartialSumHolder object.
        <br>This new object is added to the list of instantiated objects.
        @return PartialSumHolder& The newly created object. */
    PartialSumHolder& create ();
    

  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacPartialSumHolder () {}

  private:
    /** The unique instance.*/
    static FacPartialSumHolder* _instance;

  };
}
#endif // __RMOL_FAC_FACPARTIALSUMHOLDER_HPP
