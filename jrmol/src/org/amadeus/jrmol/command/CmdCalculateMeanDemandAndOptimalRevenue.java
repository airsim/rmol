package org.amadeus.jrmol.command;

import org.amadeus.jrmol.bom.BomBucket;
import org.amadeus.jrmol.bom.BomBucketHolder;
import org.amadeus.jrmol.bom.BomBucketHolder.BomBucketHolderIterator;

public abstract class CmdCalculateMeanDemandAndOptimalRevenue {
	
	/** 
	 * Re-calculate the total mean demand and optimal revenue
	 * (from the demand, prices and protections).
	 */
	public static final void calculate(BomBucketHolder ioBucketHolder) {
		double aTotalMeanDemand = 0.0;
		double aOptimalRevenue = 0.0;
		double aDemandFactor = 0.0;
		
		BomBucketHolderIterator aBucketHolderIterator = ioBucketHolder.iterator();
		
		for (int i = 0; i < ioBucketHolder.size(); i++, aBucketHolderIterator.iterate()) {
			BomBucket aCurrentBucket = aBucketHolderIterator.getCurrentBucket();
			
			// Mean Demand
			final double currentMeanDemand = aCurrentBucket.getDemand().getDistributionParameters().getMean();
			aTotalMeanDemand += currentMeanDemand;

			// Optimal Revenue
			final double currentPrice = aCurrentBucket.getYieldRange().getAverageYield();
			final double currentProtection = aCurrentBucket.getProtection();
			final double bucketOptimalRevenue = currentPrice * currentProtection;
			aOptimalRevenue += bucketOptimalRevenue;
		}

		if (ioBucketHolder.getCabinCapacity() != 0.0) {
			aDemandFactor = aTotalMeanDemand / ioBucketHolder.getCabinCapacity();
		}
		
		ioBucketHolder.setOptimalRevenue(aOptimalRevenue);
		ioBucketHolder.setDemandFactor(aDemandFactor);
		ioBucketHolder.setTotalMeanDemand(aTotalMeanDemand);
	}
}
