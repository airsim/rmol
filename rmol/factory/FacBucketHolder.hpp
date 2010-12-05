#ifndef __RMOL_FAC_FACBUCKETHOLDER_HPP
#define __RMOL_FAC_FACBUCKETHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/factory/FacBomAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class BucketHolder;
  class Bucket;

  /** Factory for Bucket. */
  class FacBucketHolder : public FacBomAbstract {
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
    
    /** Add a Bucket (child) in the internal list of a BucketHolder (parent).*/
    void addBucket (BucketHolder& ioBucketHolder, Bucket& ioBucket);

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
#endif // __RMOL_FAC_FACBUCKETHOLDER_HPP
