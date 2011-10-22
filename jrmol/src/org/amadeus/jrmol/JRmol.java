package org.amadeus.jrmol;

import org.amadeus.jrmol.bom.BomBucketHolder;
import org.amadeus.jrmol.command.CmdOptimizeProtectionsByMcIntegration;
import org.amadeus.jrmol.service.SrvContext;

/** 
 * Interface for the RMOL Services.
 */
public class JRmol {

	/** 
	 * Service Context.
	 */
	private SrvContext _context = null;
	
	/** 
	 * Constructor.
	 */
	public JRmol(final double iResourceCapacity) {
		initContext(iResourceCapacity);
	}

	/** 
	 * Add a bucket to the context.
	 */
	public void addBucket(final double iYieldRange, final double iDemandMean, final double iDemandStandardDev) {
	    assert (_context != null);
	    
	    _context.addBucket(iYieldRange, iDemandMean, iDemandStandardDev);
	}
	
	/** 
	 * Read the input data from a file.
	 */
	public void readFromInputFile(final String iInputFileName) {
		// TODO
	}
	
	/** 
	 * Optimize by MC integration.
	 */
	public void optimalOptimizeByMCIntegration(final int K) {
	    assert(_context != null);
	    
	    final double iCapacity = _context.getCapacity();
	    BomBucketHolder ioBucketHolder = _context.getBucketHolder();
	    
	    assert(ioBucketHolder != null);

	    CmdOptimizeProtectionsByMcIntegration.optimize(K, iCapacity, ioBucketHolder);

	    // Display
	    System.out.println(ioBucketHolder);
	}

	/** 
	 * Initialiser.
	 */
	private void initContext(final double iResourceCapacity) {
		_context = new SrvContext(iResourceCapacity);
	}
}
