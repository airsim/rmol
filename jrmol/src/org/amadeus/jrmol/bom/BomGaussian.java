package org.amadeus.jrmol.bom;

import java.util.Random;

import org.amadeus.jrmol.field.FldDistributionParameters;

/**
 * Gaussian Distribution-based Utilities.
 */
public class BomGaussian extends BomAbstract {
	
	/**
	 * Random number generator
	 */
	private Random _rand = null;
	
	/**
	 * Gaussian distribution characteristics
	 */
	private FldDistributionParameters _params = null;
	
	public BomGaussian() {
		_rand = new Random(System.currentTimeMillis());
		_params = new FldDistributionParameters();
	}
	
	public BomGaussian(final BomGaussian iGaussian) {
		_rand = new Random(System.currentTimeMillis());
		_params = new FldDistributionParameters(iGaussian.getDistributionParameters());
	}

	public BomGaussian(final FldDistributionParameters iDistributionParameters) {
		_rand = new Random(System.currentTimeMillis());
		_params = new FldDistributionParameters(iDistributionParameters.getMean(), iDistributionParameters.getStandardDeviation());
	}

	/** 
	 * Generate a Gaussian random variate (following the Gaussian
	 * distribution).
	 */
	public final double generateVariate() {
		return _params.getMean() + _params.getStandardDeviation() * _rand.nextGaussian();
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
