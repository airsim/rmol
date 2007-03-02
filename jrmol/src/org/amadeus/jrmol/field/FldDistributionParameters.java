package org.amadeus.jrmol.field;

/** 
 * Class wrapping the parameters of a distribution:
 * mean and standard deviation.
 */
public class FldDistributionParameters {
	
	/** 
	 * Mean.
	 */
	private double _mean = 0.0;

	/** 
	 * Standard Deviation.
     * Note that the variance is defined as the square of
     * the standard deviation.
     */
	private double _standardDeviation = 1.0;
	
	public FldDistributionParameters() {}
	
	public FldDistributionParameters(final FldDistributionParameters iDistributionParameters) {
		_mean = iDistributionParameters.getMean();
		_standardDeviation = iDistributionParameters.getStandardDeviation();
	}
	
	public FldDistributionParameters(final double iMean, final double iStandardDeviation) {
		_mean = iMean;
		_standardDeviation = iStandardDeviation;
	}

	/** 
	 * Getter for the mean value.
	 */
	public double getMean() {
		return _mean;
	}
	
	/**
	 * Getter for the standard deviation value.
	 */
	public double getStandardDeviation() {
		return _standardDeviation;
	}
	
	/** 
	 * Getter for the variance value.
	 */
	public double getVariance() {
		return Math.pow(_standardDeviation, 2);
	}

	/** 
	 * Setter for the mean value.
	 */
	public void setMean(final double iMean) {
		_mean = iMean;
	}
	
	/** 
	 * Setter for the standard deviation value.
	 */
	public void setStandardDeviation(final double iStandardDeviation) {
		_standardDeviation = iStandardDeviation;
	}
	
	public String toString() {
		String out = "";
		
		out += "<FldDistributionParameters mean=\"" + _mean + "\" _standardDeviation=\"" + _standardDeviation + "\"/>";
		return out;
	}
}
