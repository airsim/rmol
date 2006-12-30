#ifndef __RMOL_BUCKET_HPP
#define __RMOL_BUCKET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include "FldYieldRange.hpp"
#include "Demand.hpp"

namespace RMOL {

  /** Class counting the number of seats sold for a given yield range,
      and the characteristics of the corresponding demand.
      <br>
      <br>Usually, a bucket corresponds to booking/reservation/fare class,
      and is defined by a yield range on a given resource (like, e.g.,
      the cabin of a given flight-date).
      <br>
      <br>The demand is that of the corresponding booking/fare class.
      If no yield range is provided (in the constructor), it is supposed
      to be that of the demand. However, it is possible that the yield 
      range of the bucket be distinct from the one of the demand.
      <br>
      <br>The demand may not be defined. In those cases, the protections
      and/or booking class limits are usually calculated and set
      by an external system.
      <br>
      <br>The protection is the number of seats that should be protected
      from the lower buckets/classes. The bucket protections are nested 
      for a given cabin. Indeed, if C is the cabin capacity, n the number
      of classes/buckets and y(j) the protections:
      y(1) <= y(2) <= ... <= y(n), where y(n) = C (and y(0)=0).
      <br>
      <br>The booking limit is the maximal number of bookings/seats 
      allowed for that bucket/class.
      <br>
      <br>The set of booking limits is complementary to the set of 
      protections. Indeed, if b(j) are the booking limits:
      <br>b(j) = C - y(j-1),
      <br>Hence: b(n) <= b(n-1) <= ... <= b(1), where b(1)=C
  */
  class Bucket {
  public:
    /** Constructors. */
    Bucket ();
    Bucket (const Bucket&);
    Bucket (const FldYieldRange&);
    Bucket (const FldYieldRange&, const Demand&);
    Bucket (const Demand&);
    
    // Getters
    /** Getter for the yield range. */
    const FldYieldRange& getYieldRange() const {
      return _yieldRange;
    }
    /** Getter for the demand. */
    const Demand& getDemand() const {
      return _demand;
    }
    /** Getter for the protection. */
    double getProtection() const {
      return _protection;
    }
    /** Getter for the booking limit. */
    double getBookingLimit() const {
      return _bookingLimit;
    }
    /** Getter for the upper yield. */
    const double getUpperYield() const;
    /** Getter for the average yield. */
    const double getAverageYield() const;
    /** Getter for the lower yield. */
    const double getLowerYield() const;

    // Setters
    /** Setter for the protection. */
    void setProtection (const double iProtection) {
      _protection = iProtection;
    }
    /** Setter for the booking limit. */
    void setBookingLimit (const double iBookingLimit) {
      _bookingLimit = iBookingLimit;
    }

    /** Destructors. */
    virtual ~Bucket();

  private:
    /** Yield range, defined by upper and average yield. */
    const FldYieldRange _yieldRange;

    /** Demand, defined by (mean, standard deviation) and yield range. */
    const Demand _demand;

    /** Protection. */
    double _protection;

    /** Booking limit. */
    double _bookingLimit;
  };
}
#endif
