#ifndef __RMOL_BOM_BUCKET_HPP
#define __RMOL_BOM_BUCKET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/field/FldYieldRange.hpp>
#include <rmol/field/FldDistributionParameters.hpp>
#include <rmol/bom/BomAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class Demand;

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
  class Bucket : public BomAbstract {
    /** Friend Classes
        <br>Those classes need to access the internal attributes of this object
        in order to construct and initialise it.*/
    friend class FacBucket;
    friend class FacBucketHolder;
    
  public:
    // ///////// Getters ////////
    /** Getter for the yield range. */
    const FldYieldRange& getYieldRange() const {
      return _yieldRange;
    }
    /** Getter for the protection. */
    double getProtection() const {
      return _protection;
    }
    /** Getter for the cumulated protection. */
    double getCumulatedProtection() const {
      return _cumulatedProtection;
    }
    /** Getter for the booking limit. */
    double getCumulatedBookingLimit() const {
      return _cumulatedBookingLimit;
    }
    /** Getter for the booking limit. */
    double getBookingLimit() const {
      return _bookingLimit;
    }

    /** Getter for the distribution parameters of the demand. */
    const FldDistributionParameters& getDistributionParameters() const;
    
    /** Getter for the demand mean. */
    const double getMean() const;
    
    /** Getter for the demand standard deviation. */
    const double getStandardDeviation() const;
    
    /** Getter for the upper yield. */
    const double getUpperYield() const;
    
    /** Getter for the average yield. */
    const double getAverageYield() const;
    
    /** Getter for the lower yield. */
    const double getLowerYield() const;

    /** Getter for the genrated demand vector. */
    const GeneratedDemandVector_T& getGeneratedDemandVector () const {
      return *_generatedDemandVector;
    }


    // ///////// Setters ////////
    /** Setter for the protection. */
    void setProtection (const double iProtection) {
      _protection = iProtection;
    }
    
    /** Setter for the cumulated protection. */
    void setCumulatedProtection (const double iProtection) {
      _cumulatedProtection = iProtection;
    }
    
    /** Setter for the booking limit. */
    void setBookingLimit (const double iBookingLimit) {
      _bookingLimit = iBookingLimit;
    }
    
    /** Setter for the cumulated booking limit. */
    void setCumulatedBookingLimit (const double iBookingLimit) {
      _cumulatedBookingLimit = iBookingLimit;
    }

    /** Set the demand. */
    void setDemand (Demand& iDemand);

    /** Set the yield range. */
    void setYieldRange (const double iYield);

    /** Set the demand mean and standard deviation. */
    void setDemandParameters (const double, const double);

    /** Set the generated demand vector. */
    void setGeneratedDemandVector (GeneratedDemandVector_T*);

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
    /** Constructors.
	<br>Protected to force the use of the Factory. */
    Bucket ();
    Bucket (const Bucket&);
    Bucket (const FldYieldRange&);
    /** Destructors. */
    virtual ~Bucket();

    /** Getter for the demand. */
    Demand& getDemand() const;

  private:
    /** Demand, defined by (mean, standard deviation) and yield range. */
    Demand* _demand;

    /** Yield range, defined by upper and average yield. */
    FldYieldRange _yieldRange;
    
    /** Protection. */
    double _protection;

    /** Cumulated Protection. */
    double _cumulatedProtection;

    /** Booking limit. */
    double _bookingLimit;

    /** Cumulated Booking limit. */
    double _cumulatedBookingLimit;

    /** Generated demand vector. */
    GeneratedDemandVector_T* _generatedDemandVector;
  };
}
#endif // __RMOL_BOM_BUCKET_HPP
