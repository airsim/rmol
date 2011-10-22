#ifndef __RMOL_FAC_FACPARTIALSUMHOLDERHOLDER_HPP
#define __RMOL_FAC_FACPARTIALSUMHOLDERHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/factory/FacBomAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class PartialSumHolderHolder;

  /** Factory for PartialSum. */
  class FacPartialSumHolderHolder : public FacBomAbstract {
  public:

    /** Provide the unique instance.
        <br> The singleton is instantiated when first used
        @return FacPartialSumHolderHolder& */
    static FacPartialSumHolderHolder& instance();

    /** Destructor.
        <br>The Destruction put the _instance to NULL in order to be clean 
	for the next FacPartialSumHolderHolder::instance() */
    virtual ~FacPartialSumHolderHolder();

    /** Create a new PartialSumHolderHolder object.
        <br>This new object is added to the list of instantiated objects.
        @return PartialSumHolderHolder& The newly created object. */
    PartialSumHolderHolder& create ();

    /** Add a PartialSumHolder (child) in the internal list of a 
	PartialSumHolderHolder (parent).*/
    void addPartialSumHolder (PartialSumHolderHolder&, PartialSumHolder&);    

  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacPartialSumHolderHolder () {}

  private:
    /** The unique instance.*/
    static FacPartialSumHolderHolder* _instance;

  };
}
#endif // __RMOL_FAC_FACPARTIALSUMHOLDERHOLDER_HPP
