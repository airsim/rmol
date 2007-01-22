#ifndef __RMOL_BUCKETHOLDER_HPP
#define __RMOL_BUCKETHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// RMOL
#include "BomAbstract.hpp"
#include "BucketList.hpp"

namespace RMOL {

  /** Holder of a BucketList object (for memory allocation and
      recollection purposes). */
  class BucketHolder : public BomAbstract {
    /** Friend Classes
        <br>Those classes need to access the internal attributes of this object
        in order to construct and initialise it.*/
    friend class FacBucketHolder;
    
  public:
    /** Destructor. */
    ~BucketHolder();

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

    /** Get the current element (bucket/class). */
    Bucket& getCurrentBucket ();

    /** Get the next element (bucket/class). */
    Bucket& getNextBucket ();

    /** Add an element (bucket/class). */
    void addBucket (const Bucket& iBucket);

    /** Initialise the internal iterators on Buckets:
	The current iterator is set on the first Bucket,
	the next iterator is set on the second bucket. */
    void begin ();

    /** Iterate for one element (bucket/class): 
	increment both internal iterators on Buckets. */
    void iterate ();

    /** Re-calculate the following values for the buckets/classes:
        - the optimal revenue (from the prices and protections);
        - the protections;
        - the booking limits and cumulated booking limits. */
    void recalculate ();

  private:
    /** Constructor.
	<br>Protected to force the use of the Factory. */
    BucketHolder ();

    /** Constructor.
	<br>Set the cabin capacity.
	<br>Protected to force the use of the Factory. */
    BucketHolder (const double iCabinCapacity);

    /** The capacity of the cabin associated to the bucket/class list. */
    const double _cabinCapacity;

    /** The list of (N) buckets/classes. */
    BucketList_T _bucketList;

    /** Iterator for the current bucket/class. */
    BucketList_T::iterator _itCurrentBucket;
    BucketList_T::iterator _itNextBucket;

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
#endif // __RMOL_BUCKETHOLDER_HPP
