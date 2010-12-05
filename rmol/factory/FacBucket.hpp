#ifndef __RMOL_FAC_FACBUCKET_HPP
#define __RMOL_FAC_FACBUCKET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/factory/FacBomAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class FldYieldRange;
  class Bucket;
  class Demand;

  /** Factory for Bucket. */
  class FacBucket : public FacBomAbstract {
  public:

    /** Provide the unique instance.
        <br> The singleton is instantiated when first used
        @return FacBucket& */
    static FacBucket& instance();

    /** Destructor.
        <br> The Destruction put the _instance to NULL
        in order to be clean for the next FacBucket::instance() */
    virtual ~FacBucket();

    /** Create a new Bucket object.
        <br>This new object is added to the list of instantiated objects.
        @return Bucket& The newly created object. */
    Bucket& create (const FldYieldRange&);
    
    /** Create a new Bucket object.
        <br>This new object is added to the list of instantiated objects.
        @return Bucket& The newly created object. */
    Bucket& create (const FldYieldRange&, Demand&);

    /** Create the link between a Bucket (parent) and a Demand (child). */
    static void createDemandLink (Bucket&, Demand&);

  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacBucket () {}

  private:
    /** The unique instance.*/
    static FacBucket* _instance;

  };
}
#endif // __RMOL_FAC_FACBUCKET_HPP
