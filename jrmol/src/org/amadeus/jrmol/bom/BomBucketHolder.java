package org.amadeus.jrmol.bom;

import java.util.Vector;

/** 
 * Holder of a BucketList object (for memory allocation and
 * recollection purposes).
 */
public class BomBucketHolder extends BomAbstract {

	/** 
	 * The capacity of the cabin associated to the bucket/class list.
	 */
	private double _cabinCapacity = 100.0;

	/** 
	 * The list of (N) buckets/classes.
	 */
	private Vector<BomBucket> _bucketList = null;
	
	/** 
	 * Total mean demand.
	 */
	private double _totalMeanDemand = 0.0;

	/** 
	 * Demand factor: ratio between total mean demand and capacity.
	 */
	private double _demandFactor = 0.0;

	/**
	 * Optimal revenue, defined as the sum, for each bucket/class,
	 * of the price times the protection.
	 */
	private double _optimalRevenue = 0.0;

	/** 
	 * Constructor.
	 * <br>Protected to force the use of the Factory.
	 */
	public BomBucketHolder() {
		_bucketList = new Vector<BomBucket>();
	}

	/**
	 * Constructor.
	 * <br>Set the cabin capacity.
	 * <br>Protected to force the use of the Factory. 
	 */
	public BomBucketHolder(final double iCabinCapacity) {
		_cabinCapacity = iCabinCapacity;
		_bucketList = new Vector<BomBucket>((int) iCabinCapacity);
	}

	/** 
	 * Add an element (bucket/class).
	 */
	public void addBucket(final BomBucket iBucket) {
		_bucketList.add(iBucket);
	}

	/** 
	 * Re-calculate the total mean demand and optimal revenue
	 * (from the demand, prices and protections).
	 */
	public void calculateMeanDemandAndOptimalRevenue() {
		_totalMeanDemand = 0.0;
		_optimalRevenue = 0.0;

		for (final BomBucket currentBucket : _bucketList) {

			// Mean Demand
			final double currentMeanDemand = currentBucket.getDemand().getDistributionParameters().getMean();
			_totalMeanDemand += currentMeanDemand;

			// Optimal Revenue
			final double currentPrice = currentBucket.getYieldRange().getAverageYield();
			final double currentProtection = currentBucket.getProtection();
			final double bucketOptimalRevenue = currentPrice * currentProtection;
			_optimalRevenue += bucketOptimalRevenue;
		}

		if (_cabinCapacity != 0.0) {
			_demandFactor = _totalMeanDemand / _cabinCapacity;
		}
	}

	/**
	 * Re-calculate the protections and booking limits
	 * (from cumulated protections).
	 */
	public void calculateProtectionAndBookingLimits() {
		// Number of classes/buckets: n
		final int nbOfClasses = getSize();

		/** 
		 * Iterate on the classes/buckets, from 1 to n-1.
		 * Note that n-1 corresponds to the size of the parameter list,
		 * i.e., n corresponds to the number of classes/buckets.
		 */
		BomBucketHolderIterator aBucketIterator = iterator();
		BomBucket firstBucket = aBucketIterator.getCurrentBucket();

		// Set the cumulated booking limit of Bucket(1) to be equal to the capacity
		firstBucket.setCumulatedBookingLimit(_cabinCapacity);

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
			nextBucket.setCumulatedBookingLimit(_cabinCapacity - yjm1);

			/** 
			 * Set the protection of Bucket(1) to be equal to
			 * the cumulated protection of that first Bucket.
			 */
			final double yj = nextBucket.getCumulatedProtection();
			nextBucket.setProtection (yj - yjm1);
		}
	}

	/** 
	 * Get the cabin capacity.
	 */
	public final double getCabinCapacity() {
		return _cabinCapacity;
	}

	/**
	 * Get the demand factor.
	 */
	public final double getDemandFactor() {
		return _demandFactor;
	}

	/**
	 * Get the optimal revenue.
	 */
	public final double getOptimalRevenue() {
		return _optimalRevenue;
	}

	/**
	 * Get the size of list of buckets/classes.
	 */
	public final int getSize() {
		return _bucketList.size();
	}

	/** 
	 * Get the total mean demand. 
	 */
	public final double getTotalMeanDemand() {
		return _totalMeanDemand;
	}

	public BomBucketHolderIterator iterator() {
		return new BomBucketHolderIterator();
	}
	
	/** 
	 * Re-calculate the following values for the buckets/classes:
	 * - the optimal revenue (from the prices and protections);
	 * - the protections;
	 * - the booking limits and cumulated booking limits.
	 */
	public void recalculate() {
		// Re-calculate the booking limits
		calculateProtectionAndBookingLimits();

		// Re-calculate the Optimal Revenue
		calculateMeanDemandAndOptimalRevenue();
	}

	@Override
	public String toString() {
		String out = "";
		int j = 0;

		// Generate a CSV (Comma Separated Values) output
		out += "Class; Price; Mean; Std Dev; Protection; Cum. Protection; Cum. Bkg Limit;\n";

		for (BomBucket currentBucket : _bucketList) {
			final double pj = currentBucket.getYieldRange().getUpperYield();
			final double mj = currentBucket.getDemand().getDistributionParameters().getMean();
			final double sj = currentBucket.getDemand().getDistributionParameters().getStandardDeviation();
			final double proj = currentBucket.getProtection();
			final double yj = currentBucket.getCumulatedProtection();
			final double bj = currentBucket.getCumulatedBookingLimit();

			out += j + "; " 
			+ pj + "; " 
			+ mj + "; " 
			+ sj + "; " 
			+ proj + "; " 
			+ yj + "; "
			+ bj + "\n";

			j++;
		}

		out += "Cabin Capacity = " + _cabinCapacity
		+ "; Total Mean Demand = " + _totalMeanDemand
		+ "; Demand Factor = " + _demandFactor
		+ "; Optimal Revenue = " + _optimalRevenue + "\n";

		return out;
	}

	public class BomBucketHolderIterator {
		/** 
		 * Current bucket/class index.
		 */
		private int _currentBucketIndex = 0;
	
		/** 
		 * Current bucket/class.
		 */
		private BomBucket _currentBucket = null;
	
		/** 
		 * Next bucket/class index.
		 */
		private int _nextBucketIndex = 0;
	
		/** 
		 * Next bucket/class.
		 */
		private BomBucket _nextBucket = null;
	
		public BomBucketHolderIterator() {
			init();
		}
		
		/** 
		 * Initialise the internal iterators on Buckets:
		 * The current iterator is set on the first Bucket,
		 * the next iterator is set on the second bucket. 
		 */
		private void init() {
			_currentBucketIndex = 0;
			_nextBucketIndex = 0;
		
			if (_bucketList.size() == 0) return;
		
			_currentBucket = _bucketList.get(_currentBucketIndex);
			_nextBucket = _currentBucket;
		
			if (_bucketList.size() == 1) return;
		
			_nextBucketIndex++;
			_nextBucket = _bucketList.get(_nextBucketIndex);
		}
	
		/**
		 * Get the current element (bucket/class).
		 */
		public BomBucket getCurrentBucket() {
			return _currentBucket;
		}
	
		/**
		 * Get the next element (bucket/class).
		 */
		public BomBucket getNextBucket() {
			return _nextBucket;
		}
	
		/** 
		 * Iterate for one element (bucket/class): 
		 * increment both internal iterators on Buckets.
		 */
		public void iterate() {
			if (_currentBucketIndex + 1 < _bucketList.size())
			{
				_currentBucketIndex++;
				_currentBucket = _bucketList.get(_currentBucketIndex);
			}
		
			if (_nextBucketIndex + 1 < _bucketList.size())
			{
				_nextBucketIndex++;
				_nextBucket = _bucketList.get(_nextBucketIndex);
			}
		}
		
		
	}
}
