package org.amadeus.jrmol.bom;

import java.util.Random;

import org.amadeus.jrmol.field.FldDistributionParameters;

/**
 * Gaussian Distribution-based Utilities.
 */
public class BomGaussian extends BomAbstract {
	
	/**
	 * Gaussian distribution characteristics
	 */
	private FldDistributionParameters _params = null;
	
	public BomGaussian() {
		_params = new FldDistributionParameters();
	}
	
	public BomGaussian(final BomGaussian iGaussian) {
		_params = new FldDistributionParameters(iGaussian.getDistributionParameters());
	}

	public BomGaussian(final FldDistributionParameters iDistributionParameters) {
		_params = new FldDistributionParameters(iDistributionParameters.getMean(), iDistributionParameters.getStandardDeviation());
	}

	/** 
	 * Get for the parameters for the Gaussian distribution (i.e.,
	 * mean and standard deviation).
	 */
	public final FldDistributionParameters getDistributionParameters() {
		return _params;
	}
	
	/** 
	 * Set the parameters for the Gaussian distribution (i.e.,
	 * mean and standard deviation).
	 */
	public final void setDistributionParameters(final FldDistributionParameters iDistributionParameters) {
		_params = iDistributionParameters;
	}
}
