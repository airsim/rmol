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
	 * Getter for the parameters for the Gaussian distribution (i.e.,
	 * mean and standard deviation).
	 */
	public final FldDistributionParameters getDistributionParameters() {
		return _params;
	}

	/**
	 * Getter for the mean value.
	 */
	public final double getMean() {
		return _params.getMean();
	}

	/**
	 * Getter for the standard deviation value.
	 */
	public final double getStandardDeviation() {
		return _params.getStandardDeviation();
	}

	/** 
	 * Getter for the variance value. 
	 */
	public final double getVariance() {
		return _params.getVariance();
	}

	/** 
	 * Generate a Gaussian random variate (following the Gaussian
	 * distribution).
	 */
	public final double generateVariate() {
		return getMean() + getStandardDeviation() * _rand.nextGaussian();
	}
}
