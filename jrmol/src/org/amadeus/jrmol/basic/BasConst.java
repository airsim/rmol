package org.amadeus.jrmol.basic;

public abstract class BasConst {

	/**
	 * Default mean value for a distribution parameter field.
	 */
	public static final double DEFAULT_DISTRIBUTION_PARAMETERS_MEAN = 0.0;
	
	/**
	 * Default standard deviation value for a distribution parameter
	 * field.
	 */
	public static final double DEFAULT_DISTRIBUTION_PARAMETERS_DEVIATION = 1.0;

	/**
	 * Default upper field value for a yield range.
	 */
	public static final double DEFAULT_YIELD_RANGE_UPPER_FIELD = Double.MAX_VALUE;

	/**
	 * Default average field value for a yield range.
	 */
	public static final double DEFAULT_YIELD_RANGE_AVERAGE_FIELD = Double.MAX_VALUE;

	/**
	 * Default lower field value for a yield range.
	 */
	public static final double DEFAULT_YIELD_RANGE_LOWER_FIELD = Double.MIN_VALUE;
	
	/** 
	 * Default value for the number of draws within the Monte-Carlo
	 * Integration algorithm.
	 */
	public static final int DEFAULT_NUMBER_OF_DRAWS_FOR_MC_SIMULATION = 100000;

	/** 
	 * Default value for the load factor used for overbooking calculation.
	 */
	public static final double DEFAULT_OVERBOOKING_LOAD_FACTOR = 0.0;

	/** 
	 * Default value for the capacity used for overbooking calculation.
	 */
	public static final int DEFAULT_OVERBOOKING_CAPACITY = 1;

	/**
	 * Default value for the net bookings used for overbooking calculation.
	 */
	public static final int DEFAULT_OVERBOOKING_NET_BOOKINGS = 0;

	/**
	 * Default value for the overbooking used for overbooking calculation.
	 */
	public static final double DEFAULT_OVERBOOKING_PERCENTAGE = 0.0;

	/** 
	 * Default value for the mean used for overbooking calculation.
	 */
	public static final double DEFAULT_OVERBOOKING_MEAN = 0.0;

	/** 
	 * Default value for the standard deviation used for overbooking
	 * calculation.
	 */
	public static final double DEFAULT_OVERBOOKING_STANDARD_DEVIATION = 1.0;

	/**
	 * Default value for price over denied cost
	 */
	public static final double DEFAULT_OVERBOOKING_DENIED_COST = 0.5;

	/**
	 * Default probability that to deny one or more passengers.
	 */
	public static final double DEFAULT_OVERBOOKING_SERVICE_LEVEL_1 = 0.0001; 

	/**
	 * Default probability of passengers who will be denied to board.
	 */
	public static final double DEFAULT_OVERBOOKING_SERVICE_LEVEL_2 = 0.0001;

	/**
	 * Default type of service level.
	 */
	public static final int DEFAULT_OVERBBOKING_SERVICE_LEVEL_TYPE = 2;

	/**
	 * Default cancellation deviation.
	 */
	public static final double DEFAULT_OVERBOOKING_CANCELLATIONS_DEVIATION = 0.05;
	
}
