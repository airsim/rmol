package org.amadeus.jrmol.basic;

public abstract class BasConst {

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
	public static final double DEFAULT_OVERBOOKING_OVERBOOKING_PERCENTAGE = 0.0;

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
	 * Default capacity for the RMOL_Service.
	 */
	public static final double DEFAULT_RMOL_SERVICE_CAPACITY = 1.0;
}
