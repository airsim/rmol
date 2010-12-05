#ifndef __RMOL_BOM_BUCKETHOLDER_HPP
#define __RMOL_BOM_BUCKETHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/bom/BomAbstract.hpp>
#include <rmol/bom/BucketList.hpp>

namespace RMOL {

  /** Holder of a BucketList object (for memory allocation and
      recollection purposes). */
  class BucketHolder : public BomAbstract {
    /** Friend Classes
        <br>Those classes need to access the internal attributes of this object
        in order to construct and initialise it.*/
    friend class FacBucketHolder;
    
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

    /** Get the cumulated protection of the previous bucket. If the
        current bucket is the first one, the function returns 0.0. */
    const double getPreviousCumulatedProtection () const;

    /** Fill up the vector of cumulated booking limits and the vector
        of cumulated protection levels. */
    void fillup (ProtectionLevelVector_T&, BookingLimitVector_T&) const;
    
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

    const double getLowestAverageYield ();

  public:
    // ///////// Display methods ////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream&) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream&);

    /** Get the serialised version of the Place object. */
    std::string toString() const;

    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;
    
    /** Display the full Place context. */
    const std::string display() const;

    /** Display a short Place context. */
    const std::string shortDisplay() const;


  private:
    /** Constructor.
	<br>Protected to force the use of the Factory. */
    BucketHolder ();

    /** Constructor.
	<br>Set the cabin capacity.
	<br>Protected to force the use of the Factory. */
    BucketHolder (const double iCabinCapacity);

    /** Destructor. */
    virtual ~BucketHolder();


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
#endif // __RMOL_BOM_BUCKETHOLDER_HPP
