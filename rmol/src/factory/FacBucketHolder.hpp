#ifndef __RMOL_FACBUCKETHOLDER_HPP
#define __RMOL_FACBUCKETHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include "FacAbstract.hpp"
#include "BucketHolder.hpp"

namespace RMOL {

  /** Factory for Bucket. */
  class FacBucketHolder : public FacAbstract {
  public:

    /** Provide the unique instance.
        <br> The singleton is instantiated when first used
        @return FacBucketHolder& */
    static FacBucketHolder& instance();

    /** Destructor.
        <br> The Destruction put the _instance to NULL
        in order to be clean for the next FacBucketHolder::instance() */
    virtual ~FacBucketHolder();

    /** Create a new BucketHolder object.
        <br>This new object is added to the list of instantiated objects.
        @return BucketHolder& The newly created object. */
    BucketHolder& create (const double iCabinCapacity);
    

  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacBucketHolder () {}

  private:
    /** The unique instance.*/
    static FacBucketHolder* _instance;

  };
}
#endif // __RMOL_FACBUCKETHOLDER_HPP
