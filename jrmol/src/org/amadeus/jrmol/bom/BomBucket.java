package org.amadeus.jrmol.bom;

import org.amadeus.jrmol.field.FldDistributionParameters;
import org.amadeus.jrmol.field.FldYieldRange;

/** 
 * Class counting the number of seats sold for a given yield range,
 * and the characteristics of the corresponding demand.
 * <br>
 * <br>Usually, a bucket corresponds to booking/reservation/fare class,
 * and is defined by a yield range on a given resource (like, e.g.,
 * the cabin of a given flight-date).
 * <br>
 * <br>The demand is that of the corresponding booking/fare class.
 * If no yield range is provided (in the constructor), it is supposed
 * to be that of the demand. However, it is possible that the yield 
 * range of the bucket be distinct from the one of the demand.
 * <br>
 * <br>The demand may not be defined. In those cases, the protections
 * and/or booking class limits are usually calculated and set
 * by an external system.
 * <br>
 * <br>The protection is the number of seats that should be protected
 * from the lower buckets/classes. The bucket protections are nested 
 * for a given cabin. Indeed, if C is the cabin capacity, n the number
 * of classes/buckets and y(j) the protections:
 * y(1) <= y(2) <= ... <= y(n), where y(n) = C (and y(0)=0).
 * <br>
 * <br>The booking limit is the maximal number of bookings/seats 
 * allowed for that bucket/class.
 * <br>
 * <br>The set of booking limits is complementary to the set of 
 * protections. Indeed, if b(j) are the booking limits:
 * <br>b(j) = C - y(j-1),
 * <br>Hence: b(n) <= b(n-1) <= ... <= b(1), where b(1)=C
 */
public class BomBucket extends BomAbstract {

	/** 
	 * Yield range, defined by upper and average yield.
	 */
	private FldYieldRange _yieldRange = null;

	/** 
	 * Demand, defined by (mean, standard deviation) and yield range.
	 */
	private BomDemand _demand = null;

	/** 
	 * Protection.
	 */
	private double _protection = 0.0;

	/**
	 * Cumulated Protection.
	 */
	private double _cumulatedProtection = 0.0;

	/**
	 * Booking limit.
	 */
	private double _bookingLimit = 0.0;

	/** 
	 * Cumulated Booking limit.
	 */
	private double _cumulatedBookingLimit = 0.0;

	public BomBucket() {}

	public BomBucket(final BomBucket iBucket) {
		_yieldRange = new FldYieldRange(iBucket.getYieldRange());
		_demand = new BomDemand(iBucket.getDemand());
		_protection =  iBucket.getProtection();
		_cumulatedProtection = iBucket.getCumulatedProtection();
		_bookingLimit = iBucket.getBookingLimit();
		_cumulatedBookingLimit = iBucket.getCumulatedBookingLimit();
	}

	public BomBucket(final FldYieldRange iYieldRange) {
		_yieldRange = new FldYieldRange(iYieldRange);
		_demand = new BomDemand();
	}

	public BomBucket(final FldYieldRange iYieldRange, final BomDemand iDemand) {
		_yieldRange = new FldYieldRange(iYieldRange);
		_demand = new BomDemand(iDemand);
	}

	public BomBucket(final BomDemand iDemand) {
		_yieldRange = new FldYieldRange(iDemand.getYieldRange());
		_demand = new BomDemand(iDemand);
	}

	/** 
	 * Getter for the yield range.
	 */
	public final FldYieldRange getYieldRange() {
		return _yieldRange;
	}

	/** 
	 * Getter for the demand. 
	 */
	public final BomDemand getDemand() {
		return _demand;
	}

	/** 
	 * Getter for the protection.
	 */
	public double getProtection() {
		return _protection;
	}

	/** 
	 * Getter for the cumulated protection.
	 */
	public double getCumulatedProtection() {
		return _cumulatedProtection;
	}

	/** 
	 * Getter for the booking limit.
	 */
	public double getCumulatedBookingLimit() {
		return _cumulatedBookingLimit;
	}

	/** 
	 * Getter for the booking limit.
	 */
	public double getBookingLimit() {
		return _bookingLimit;
	}

	/** 
	 * Getter for the distribution parameters of the demand.
	 */
	public final FldDistributionParameters getDistributionParameters() {
		return _demand.getDistributionParameters();
	}

	/**
	 * Getter for the demand mean.
	 */
	public final double getMean() {
		return _demand.getMean();
	}

	/** 
	 * Getter for the demand standard deviation.
	 */
	public final double getStandardDeviation() {
		return _demand.getStandardDeviation();
	}

	/**
	 * Getter for the upper yield.
	 */
	public final double getUpperYield() {
		return _yieldRange.getUpperYield();
	}

	/** 
	 * Getter for the average yield.
	 */
	public final double getAverageYield() {
		return _yieldRange.getAverageYield();
	}

	/** 
	 * Getter for the lower yield.
	 */
	public final double getLowerYield() {
		return _yieldRange.getLowerYield();
	}

	/** 
	 * Setter for the protection.
	 */
	public void setProtection(final double iProtection) {
		_protection = iProtection;
	}

	/** 
	 * Setter for the cumulated protection.
	 */
	public void setCumulatedProtection(final double iProtection) {
		_cumulatedProtection = iProtection;
	}

	/**
	 * Setter for the booking limit.
	 */
	public void setBookingLimit(final double iBookingLimit) {
		_bookingLimit = iBookingLimit;
	}

	/** 
	 * Setter for the cumulated booking limit.
	 */
	public void setCumulatedBookingLimit(final double iBookingLimit) {
		_cumulatedBookingLimit = iBookingLimit;
	}
}
