#ifndef __RMOL_BOM_RESOURCE_HPP
#define __RMOL_BOM_RESOURCE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// RMOL
#include <rmol/bom/BomAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class BucketHolder;

  /** Holder of a BucketList object (for memory allocation and
      recollection purposes). */
  class Resource : public BomAbstract {
    /** Friend Classes
        <br>Those classes need to access the internal attributes of this object
        in order to construct and initialise it.*/
    friend class FacResource;
    
  public:
    // ////// Getters //////
    /** Get the cabin capacity. */
    const double getCabinCapacity () const {
      return _cabinCapacity;
    }
    /** Get the total mean demand. */
    const double getTotalMeanDemand () const {
      return _totalMeanDemand;
    }
    /** Get the demand factor. */
    const double getDemandFactor () const {
      return _demandFactor;
    }
    /** Get the optimal revenue. */
    const double getOptimalRevenue () const {
      return _optimalRevenue;
    }

    /** Get the size of list of buckets/classes. */
    const short getSize () const;

    /** Dump a Business Object into an output stream.
        @param ostream& the output stream
        @return ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Display on standard output. */
    void display () const;

    /** Destructor. */
    virtual ~Resource();

    /** Get the current element (bucket/class). */
    Bucket& getCurrentBucket () const;

    /** Get the next element (bucket/class). */
    Bucket& getNextBucket () const;

    /** Get the tagged element (bucket/class). */
    Bucket& getTaggedBucket () const;

    /** Initialise the internal iterators on Buckets:
	The current iterator is set on the first Bucket,
	the next iterator is set on the second bucket. */
    void begin ();

    /** Iterate for one element (bucket/class): 
	increment both internal iterators on Buckets. */
    void iterate ();

    /** States whether or not the end of the (bucket/class) list has
        been reached. */
    bool hasNotReachedEnd () const;

    /** Tag one element (bucket/class) for later direct access. */
    void tag ();

    /** Re-calculate the following values for the buckets/classes:
        - the optimal revenue (from the prices and protections);
        - the protections;
        - the booking limits and cumulated booking limits. */
    void recalculate ();

  private:
    /** Constructor.
	<br>Protected to force the use of the Factory. */
    Resource ();

    /** Constructor.
	<br>Set the cabin capacity.
	<br>Protected to force the use of the Factory. */
    Resource (const double iCabinCapacity);

    /** Add an element (bucket/class).
        <br>Note that the Bucket object may be altered by subsequent
        operations.
	<br>Protected to force the use of the Factory. */
    void addBucket (Bucket&);

  private:
    /** The capacity of the cabin associated to the bucket/class list. */
    const double _cabinCapacity;

    /** The list of (N) buckets/classes. */
    BucketList_T _bucketList;

    /** Iterator for the current bucket/class. */
    BucketList_T::iterator _itCurrentBucket;
    BucketList_T::iterator _itNextBucket;
    BucketList_T::iterator _itTaggedBucket;

    /** Total mean demand. */
    double _totalMeanDemand;

    /** Demand factor: ratio between total mean demand and capacity. */
    double _demandFactor;

    /** Optimal revenue, defined as the sum, for each bucket/class,
        of the price times the protection. */
    double _optimalRevenue;

  protected:
    /** Re-calculate the protections and booking limits
        (from cumulated protections). */
    void calculateProtectionAndBookingLimits ();
    
    /** Re-calculate the total mean demand and optimal revenue
        (from the demand, prices and protections). */
    void calculateMeanDemandAndOptimalRevenue ();

  };
}
#endif // __RMOL_BOM_RESOURCE_HPP
