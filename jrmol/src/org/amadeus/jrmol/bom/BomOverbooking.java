package org.amadeus.jrmol.bom;

import org.amadeus.jrmol.basic.BasConst;
import org.amadeus.jrmol.field.FldDistributionParameters;

/**
 * Class representing an overbooking for a given bucket.
 */
public class BomOverbooking extends BomAbstract {

	/** 
	 * Overbooking percentage.
	 */
	private double _overbookingPercentage = BasConst.DEFAULT_OVERBOOKING_PERCENTAGE;

	/** 
	 * Capacity.
	 */
	private int _capacity = BasConst.DEFAULT_OVERBOOKING_CAPACITY;

	/** 
	 * Net Bookings.
	 */
	private int _netBookings = BasConst.DEFAULT_OVERBOOKING_NET_BOOKINGS;

	/** 
	 * Load Factor.
	 */
	private double _loadFactor = BasConst.DEFAULT_OVERBOOKING_LOAD_FACTOR;

	/**
	 * Price over denied cost.
	 */
	private double _priceOverDeniedCost = BasConst.DEFAULT_OVERBOOKING_DENIED_COST;

	/**
	 * Maximum booking limit TODO
	 */
	private double _maximumBookingLimit = BasConst.DEFAULT_OVERBOOKING_CAPACITY * 1.2;

	/**
	 * Probability that to deny one or more passengers.
	 */
	private final double _serviceLevel1 = BasConst.DEFAULT_OVERBOOKING_SERVICE_LEVEL_1; 

	/**
	 * Fraction of passengers who will be denied to board.
	 */
	private final double _serviceLevel2 = BasConst.DEFAULT_OVERBOOKING_SERVICE_LEVEL_2;

	/**
	 * Type of service level.
	 */
	private final int SERVICE_LEVEL_TYPE = BasConst.DEFAULT_OVERBBOKING_SERVICE_LEVEL_TYPE;

	/**
	 * Cancellation deviation.
	 */
	private final double CANCELLATIONS_DEVIATION = BasConst.DEFAULT_OVERBOOKING_CANCELLATIONS_DEVIATION;
	
	/**
	 * No-Show Distribution Parameters.
	 */
	private FldDistributionParameters _noShowDistributionParameters = null;

	/** 
	 * Cancellation Distribution Parameters.
	 */
	private FldDistributionParameters _cancellationDistributionParameters = null;

	/** 
	 * Remaining Cancellation Distribution Parameters.
	 */
	private FldDistributionParameters _remainingCancellationDistributionParameters = null;

	/** 
	 * Demand Distribution Parameters.
	 */
	private FldDistributionParameters _demandDistributionParameters = null;

	/** 
	 * Default Constructor.
	 */
	public BomOverbooking() {
		_noShowDistributionParameters = new FldDistributionParameters(BasConst.DEFAULT_OVERBOOKING_MEAN,
				BasConst.DEFAULT_OVERBOOKING_STANDARD_DEVIATION);

		_cancellationDistributionParameters = new FldDistributionParameters(BasConst.DEFAULT_OVERBOOKING_MEAN,
				BasConst.DEFAULT_OVERBOOKING_STANDARD_DEVIATION);

		_remainingCancellationDistributionParameters = new FldDistributionParameters(BasConst.DEFAULT_OVERBOOKING_MEAN,
				BasConst.DEFAULT_OVERBOOKING_STANDARD_DEVIATION);

		_demandDistributionParameters = new FldDistributionParameters(BasConst.DEFAULT_OVERBOOKING_MEAN,
				BasConst.DEFAULT_OVERBOOKING_STANDARD_DEVIATION);
	}

	/** 
	 * Default Copy Constructor.
	 */
	public BomOverbooking(final BomOverbooking iOverbooking) {
		_noShowDistributionParameters = new FldDistributionParameters(iOverbooking.getNoShowDistributionParameters());

		_cancellationDistributionParameters = new FldDistributionParameters(iOverbooking.getCancellationDistributionParameters());

		_remainingCancellationDistributionParameters = new FldDistributionParameters(iOverbooking.getRemainingCancellationDistributionParameters());

		_demandDistributionParameters = new FldDistributionParameters(iOverbooking.getDemandDistributionParameters());

	}

	/** 
	 * Get the Cancellation Distribution Parameters.
	 */
	public final FldDistributionParameters getCancellationDistributionParameters () {
		return _cancellationDistributionParameters;
	}

	/** 
	 * Get the capacity.
	 */
	public final int getCapacity() {
		return _capacity;
	}

	/** 
	 * Get the Demand Distribution Parameters.
	 */
	public final FldDistributionParameters getDemandDistributionParameters() {
		return _demandDistributionParameters;
	}

	/**
	 * Get the load factor.
	 */
	public final double getLoadFactor() {
		return _loadFactor;
	}

	/** 
	 * Get the net bookings.
	 */
	public final int getNetBookings() {
		return _netBookings;
	}

	/** 
	 * Get the No-Show Distribution Parameters.
	 */
	public final FldDistributionParameters getNoShowDistributionParameters() {
		return _noShowDistributionParameters;
	}

	/** 
	 * Gets the overbooking percentage.
	 */
	public final double getOverbookingPercentage() {
		return _overbookingPercentage;
	}

	/**
	 * Get the Remaining Cancellation Distribution Parameters.
	 */
	public final FldDistributionParameters getRemainingCancellationDistributionParameters() {
		return _remainingCancellationDistributionParameters;
	}

	/** 
	 * Set the Cancellation Distribution Parameters. 
	 */
	public final void setCancellationDistributionParameters (final FldDistributionParameters iCancellationDistributionParameters) {
		_cancellationDistributionParameters = iCancellationDistributionParameters;
	}

	/**
	 * Set the price over denied cost
	 */
	public final double getPriceOverDeniedCost() {
		return _priceOverDeniedCost;
	}

	/**
	 * Set the capacity.
	 */
	public final void setCapacity(final int iCapacity) {
		_capacity = iCapacity;
	}

	/**
	 * Set the Demand Distribution Parameters.
	 */
	public final void setDemandDistributionParameters(final FldDistributionParameters iDemandDistributionParameters) {
		_demandDistributionParameters = iDemandDistributionParameters;
	}

	/** 
	 * Set the load factor. 
	 */
	public final void setLoadFactor(final double iLoadFactor) {
		_loadFactor = iLoadFactor;
	}

	/**
	 * Set the net bookings.
	 */
	public final void setNetBookings(final int iNetBookings) {
		_netBookings = iNetBookings;
	}

	/** 
	 * Set the No-Show Distribution Parameters.
	 */
	public final void setNoShowDistributionParameters (final FldDistributionParameters iNoShowDistributionParameters) {
		_noShowDistributionParameters = iNoShowDistributionParameters;
	}

	/** 
	 * Set the overbooking percentage.
	 */
	public final void setOverbookingPercentage(final double iOverbookingPercentage) {
		_overbookingPercentage = iOverbookingPercentage;
	}

	/** 
	 * Set the Remaining Cancellation Distribution Parameters.
	 */
	public final void setRemainingCancellationDistributionParameters(final FldDistributionParameters iRemainingCancellationDistributionParameters) {
		_remainingCancellationDistributionParameters = 
			iRemainingCancellationDistributionParameters;
	}

	/**
	 * Set the price over denied cost
	 */
	public final void setPriceOverDeniedCost(final double iPriceOverDeniedCost) {
		_priceOverDeniedCost = iPriceOverDeniedCost;
	}
}
