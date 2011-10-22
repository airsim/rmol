package org.amadeus.jrmol.command;

import java.util.Random;

import org.amadeus.jrmol.bom.BomGaussian;

public abstract class CmdGenerateVariate {

	/**
	 * Random number generator
	 */
	private static final Random _rand = new Random(System.currentTimeMillis());

	/** 
	 * Generate a Gaussian random variate (following the Gaussian
	 * distribution).
	 */
	public static final double generate(final BomGaussian iGaussian) {
		return iGaussian.getDistributionParameters().getMean() + iGaussian.getDistributionParameters().getStandardDeviation() * _rand.nextGaussian();
	}

}
