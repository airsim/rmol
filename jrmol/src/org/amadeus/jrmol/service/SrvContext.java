package org.amadeus.jrmol.service;

import org.amadeus.jrmol.bom.BomBucket;
import org.amadeus.jrmol.bom.BomBucketHolder;
import org.amadeus.jrmol.bom.BomDemand;
import org.amadeus.jrmol.field.FldDistributionParameters;
import org.amadeus.jrmol.field.FldYieldRange;

public class SrvContext {

	/** 
	 * Internal pointer on BucketHolder.
	 */
	private BomBucketHolder _bucketHolder = null;

	/** 
	 * Resource Capacity.
	 */
	private double _capacity = 0.0;

	public SrvContext(final double iResourceCapacity) {
		init(iResourceCapacity);
	}

	private void init (final double iResourceCapacity) {
		_capacity = iResourceCapacity;
		_bucketHolder = new BomBucketHolder(iResourceCapacity);
	}

	/** 
	 * Add a bucket to the BucketHolder.
	 */
	public void addBucket(final double iYieldRange, final double iDemandMean, final double iDemandStandardDev) {
	    final FldYieldRange aYieldRange = new FldYieldRange(iYieldRange);
	    final FldDistributionParameters aDistribParams = new FldDistributionParameters(iDemandMean, iDemandStandardDev);
	    
	    final BomDemand aDemand = new BomDemand(aDistribParams, aYieldRange);
	    BomBucket aBucket = new BomBucket(aYieldRange, aDemand);

	    assert (_bucketHolder != null);
	    
	    _bucketHolder.addBucket(aBucket);
	}

	/** 
	 * Get the internal BucketHolder.
	 */
	public final BomBucketHolder getBucketHolder() {
		return _bucketHolder;
	}

	/** 
	 * Get the capacity.
	 */
	public final double getCapacity() {
		return _capacity;
	}

	/** 
	 * Read the input data from a file.
	 */
	public void readFromInputFile (final String iInputFileName) {
		// TODO
	}

	/** 
	 * Set the BucketHolder.
	 */
	public void setBucketHolder(BomBucketHolder ioBucketHolderPtr) {
		_bucketHolder = ioBucketHolderPtr;
	}
}
