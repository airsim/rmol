package org.amadeus.jrmol.bom;

import java.util.Vector;

/** 
 * Holder of a BucketList object (for memory allocation and
 * recollection purposes).
 */
public class BomBucketHolder extends BomAbstract {

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
		_bucketList = new Vector<BomBucket>();
	}

	/** 
	 * Add an element (bucket/class).
	 */
	public final void addBucket(final BomBucket iBucket) {
		_bucketList.add(iBucket);
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
	 * Get the total mean demand. 
	 */
	public final double getTotalMeanDemand() {
		return _totalMeanDemand;
	}
	
	/**
	 * Get the iterator over buckets.
	 */
	public final BomBucketHolderIterator iterator() {
		return new BomBucketHolderIterator();
	}

	/**
	 * Sets the demand factor.
	 */
	public final void setDemandFactor(final double iDemandFactor) {
		_demandFactor = iDemandFactor;
	}
	
	/**
	 * Sets the optimal revenue.
	 */
	public final void setOptimalRevenue(final double iOptimalRevenue) {
		_optimalRevenue = iOptimalRevenue;
	}
	
	/**
	 * Sets the total mean demand.
	 */
	public final void setTotalMeanDemand(final double iTotalMeanDemand) {
		_totalMeanDemand = iTotalMeanDemand;
	}

	/**
	 * Get the size of list of buckets/classes.
	 */
	public final int size() {
		return _bucketList.size();
	}

	@Override
	public final String toString() {
		String aDoubleFormat = "%1$ 16.2f";
		String aStringFormat = "%1$16s";
		String out = "";
		int j = 0;

		// Generate a CSV (Comma Separated Values) output
		out += String.format("%1$5s", "Class") + ";"
			+ String.format(aStringFormat, "Price") + ";"
			+ String.format(aStringFormat, "Mean") + ";"
			+ String.format(aStringFormat, "Std Dev") + ";"
			+ String.format(aStringFormat, "Protection") + ";"
			+ String.format(aStringFormat, "Cum. Protection") + ";"
			+ String.format(aStringFormat, "Cum. Bkg Limit") + ";\n";

		for (BomBucket currentBucket : _bucketList) {
			final double pj = currentBucket.getYieldRange().getUpperYield();
			final double mj = currentBucket.getDemand().getDistributionParameters().getMean();
			final double sj = currentBucket.getDemand().getDistributionParameters().getStandardDeviation();
			final double proj = currentBucket.getProtection();
			final double yj = currentBucket.getCumulatedProtection();
			final double bj = currentBucket.getCumulatedBookingLimit();

			out += String.format("%1$5d", j) + ";"
			+ String.format(aDoubleFormat, pj) + ";" 
			+ String.format(aDoubleFormat, mj) + ";" 
			+ String.format(aDoubleFormat, sj) + ";" 
			+ String.format(aDoubleFormat, proj) + ";" 
			+ String.format(aDoubleFormat, yj) + ";"
			+ String.format(aDoubleFormat, bj) + ";\n";

			j++;
		}

		out += "\nCabin Capacity = " + _cabinCapacity
		+ "; Total Mean Demand = " + _totalMeanDemand
		+ "; Demand Factor = " + _demandFactor
		+ "; Optimal Revenue = " + String.format("%1$.2f", _optimalRevenue) + "\n";

		return out;
	}
}
