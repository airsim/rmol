package org.amadeus.jrmol.command;

import java.util.Vector;

import org.amadeus.jrmol.bom.BomBucket;
import org.amadeus.jrmol.bom.BomBucketHolder;
import org.amadeus.jrmol.bom.BomGaussian;
import org.amadeus.jrmol.bom.BomPartialSumHolder;
import org.amadeus.jrmol.bom.BomBucketHolder.BomBucketHolderIterator;
import org.amadeus.jrmol.field.FldDistributionParameters;

public abstract class CmdOptimizeProtectionsByMcIntegration {

	/** 
	 * Calculate the optimal protections for the set of buckets/classes
	 * given in input, and update those buckets accordingly.
	 * <br>The Monte Carlo Integration algorithm (see The Theory and 
	 * Practice of Revenue Management, by Kalyan T. Talluri and 
	 * Garret J. van Ryzin, Kluwer Academic Publishers, for the details) 
	 * is used. Hence, K is the number of random draws to perform.
	 * 100 is a minimum for K, as statistics must be drawn from those
	 * random generations.
	 * <br>The cabin capacity is used to a double to allow for some
	 * overbooking.
	 */
	public static final void optimize(final int K, final double iCabinCapacity, BomBucketHolder ioBucketHolder) {

		// Number of classes/buckets: n
		final int nbOfClasses = ioBucketHolder.size();

		/** 
		 * Initialise the partial sum vector representing the last step within
		 * the algorithm below.
		 * <br>At the beginning of the algorithm, the partial sums need to be
		 * null. Then, the generated demand (variates) will be added 
		 * incrementally.
		 */
		BomPartialSumHolder previousPartialSumList = new BomPartialSumHolder(K);

		for (int k = 1; k <= K; k++) {
			previousPartialSumList.addPartialSum(0.0);
		}

		/** 
		 * Iterate on the classes/buckets, from 1 to n-1.
		 * Note that n-1 corresponds to the size of the parameter list,
		 * i.e., n corresponds to the number of classes/buckets.
		 */
		BomBucketHolderIterator aBucketHolderIterator = ioBucketHolder.iterator();

		int Kj = K;
		int lj = 0;
		for (int j = 1 ; j <= nbOfClasses - 1; j++, aBucketHolderIterator.iterate()) {
			
			/** Retrieve Bucket(j) (current) and Bucket(j+1) (next). */
			BomBucket currentBucket = aBucketHolderIterator.getCurrentBucket();
			BomBucket nextBucket = aBucketHolderIterator.getNextBucket();

			// STEP 1.
			/** 
			 * Initialise the random generator with the distribution parameters of
			 * the demand for the current class/bucket, j.
			 */
			final FldDistributionParameters aDistribParams = currentBucket.getDemand().getDistributionParameters();
			final BomGaussian gaussianDemandGenerator = new BomGaussian(aDistribParams);

			/**
			 * Iterate on the random draws: generate random variates, d(j,k)
			 * for the current class/bucket demand, j, and for k = 1 to Kj.
			 */
			Vector<Double> aVariateList = new Vector<Double>();
			BomPartialSumHolder currentPartialSumList =	new BomPartialSumHolder(Kj);
			for (int k = 1; k <= Kj; k++) {
				final double djk = CmdGenerateVariate.generate(gaussianDemandGenerator);
				aVariateList.add(djk);

				/** 
				 * Calculate the partial sums:
				 * <br>
				 * S(j,k)= d(1,k) + d(2,k) + ... + d(j,k),for a given k and j=1 to n-1
				 * Note that n-1 corresponds to the size of the parameter list,
				 * i.e., n corresponds to the number of classes/buckets.
				 * <br>
				 * Hence: S(j,k) = S'(j-1, l+k) + d(j,k). 
				 */
				final double spjm1lpk = previousPartialSumList.getPartialSum(lj + k - 1);
				final double sjk = spjm1lpk + djk;
				currentPartialSumList.addPartialSum(sjk);
			}

			// STEP 2.
			/**
			 * Sort the partial sum vectors S(j,k) on k, for the current j.
			 */
			currentPartialSumList.sort();

			/** 
			 * Retrieve the prices for Bucket(j) and Bucket(j+1).
			 */
			final double pj = currentBucket.getYieldRange().getAverageYield();
			final double pj1 = nextBucket.getYieldRange().getAverageYield();

			/** 
			 * Consistency check: the yield/price of a higher class/bucket
			 * (with the j index lower) must be higher.
			 */
			assert(pj > pj1);

			/** 
			 * The optimal index is defined as:
			 * lj = floor {[p(j)-p(j+1)]/p(j) . K}
			 */
			final double ljdouble = Math.floor(Kj * (pj - pj1) / pj);
			lj = (int) ljdouble;

			/** 
			 * Consistency check.
			 */
			assert(lj >= 1 && lj < Kj);

			/** 
			 * Update Kj for the next loop.
			 */
			Kj = Kj - lj;

			/** 
			 * The optimal protection is defined as:
			 * y(j) = 1/2 [S(j,lj) + S(j, lj+1)]
			 */
			final double sjl = currentPartialSumList.getPartialSum(lj - 1);
			final double sjlp1 = currentPartialSumList.getPartialSum(lj + 1 - 1);
			final double yj = (sjl + sjlp1) / 2;

			// Set the cumulated protection for Bucket(j) (j ranging from 1 to n-1)
			currentBucket.setCumulatedProtection(yj);

			/** 
			 * S'(j,k) = S(j,k).
			 */
			previousPartialSumList = currentPartialSumList;
		}

		// Set the protection of Bucket(n) to be equal to the capacity
		BomBucket currentBucket = aBucketHolderIterator.getCurrentBucket();
		currentBucket.setCumulatedProtection(iCabinCapacity);

		/**
		 * Re-calculate the values (protections, bkg limits and cumulated
		 * booking limits, the optimal revenue.
		 */
		CmdCalculateAll.calculate(ioBucketHolder);
	}
}
