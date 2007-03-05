package org.amadeus.jrmol.command;

import org.amadeus.jrmol.bom.BomBucketHolder;

public abstract class CmdCalculateAll {

	/** 
	 * Re-calculate the following values for the buckets/classes:
	 * - the optimal revenue (from the prices and protections);
	 * - the protections;
	 * - the booking limits and cumulated booking limits.
	 */
	public static final void calculate(BomBucketHolder ioBucketHolder) {
		// Re-calculate the booking limits
		CmdCalculateProtectionsAndBookingLimits.calculate(ioBucketHolder);

		// Re-calculate the Optimal Revenue
		CmdCalculateMeanDemandAndOptimalRevenue.calculate(ioBucketHolder);
	}
	
}
