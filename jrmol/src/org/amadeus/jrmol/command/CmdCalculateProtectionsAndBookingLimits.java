package org.amadeus.jrmol.command;

import org.amadeus.jrmol.bom.BomBucket;
import org.amadeus.jrmol.bom.BomBucketHolder;
import org.amadeus.jrmol.bom.BomBucketHolder.BomBucketHolderIterator;

public abstract class CmdCalculateProtectionsAndBookingLimits {

	/**
	 * Re-calculate the protections and booking limits
	 * (from cumulated protections).
	 */
	public static final void calculate(BomBucketHolder ioBucketHolder) {
		
		// Number of classes/buckets: n
		final int nbOfClasses = ioBucketHolder.size();

		/** 
		 * Iterate on the classes/buckets, from 1 to n-1.
		 * Note that n-1 corresponds to the size of the parameter list,
		 * i.e., n corresponds to the number of classes/buckets.
		 */
		BomBucketHolderIterator aBucketIterator = ioBucketHolder.iterator();
		BomBucket firstBucket = aBucketIterator.getCurrentBucket();

		// Set the cumulated booking limit of Bucket(1) to be equal to the capacity
		firstBucket.setCumulatedBookingLimit(ioBucketHolder.getCabinCapacity());

		/** 
		 * Set the protection of Bucket(1) to be equal to the cumulated protection
		 * of that first Bucket.
		 */
		firstBucket.setProtection (firstBucket.getCumulatedProtection());

		for (int j = 1; j <= nbOfClasses - 1; j++, aBucketIterator.iterate()) {
			/** 
			 * Retrieve Bucket(j) (current) and Bucket(j+1) (next).
			 */
			BomBucket currentBucket = aBucketIterator.getCurrentBucket();
			BomBucket nextBucket = aBucketIterator.getNextBucket();

			/**
			 * Set the cumulated booking limit for Bucket(j+1)
			 * (j ranging from 1 to n-1).
			 */
			final double yjm1 = currentBucket.getCumulatedProtection();
			nextBucket.setCumulatedBookingLimit(ioBucketHolder.getCabinCapacity() - yjm1);

			/** 
			 * Set the protection of Bucket(1) to be equal to
			 * the cumulated protection of that first Bucket.
			 */
			final double yj = nextBucket.getCumulatedProtection();
			nextBucket.setProtection (yj - yjm1);
		}
	}
}
