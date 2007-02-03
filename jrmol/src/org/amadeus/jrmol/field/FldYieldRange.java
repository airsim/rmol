package org.amadeus.jrmol.field;

/** 
 * Class representing a range of yields.
 * <br>Typically, bookings are priced according to rules (e.g., fare rules),
 * leading to slight variations of revenues for a given product.
 * The "yield range" captures the extent of revenues earned for a given
 * product.
 * <br>When no average and lower yields are defined, they are assumed
 * to be equal to the upper yield.
 * <br>Note that the lower yield is generally not defined, as it
 * corresponds to the upper yield of the lower yield range.
 */
public class FldYieldRange {
	
	/** 
	 * Upper yield.
	 */
	private double _upperYield = Double.MAX_VALUE;

	/** 
	 * Average yield.
	 */
	private double _averageYield = Double.MAX_VALUE;

	/** 
	 * Lower yield (most often, not used). 
	 */
	private double _lowerYield = Double.MIN_VALUE;
	
	public FldYieldRange() {}
	
	public FldYieldRange(final FldYieldRange iYieldRange) {
		_upperYield = iYieldRange.getUpperYield();
		_averageYield = iYieldRange.getAverageYield();
	}
	
	public FldYieldRange(final double iUpperYield) {
		_upperYield = iUpperYield;
		_averageYield = iUpperYield;
		_lowerYield = iUpperYield;
	}
	
	public FldYieldRange(final double iUpperYield, final double iAverageYield) {
		_upperYield = iUpperYield;
		_averageYield = iAverageYield;
	}
	
	public FldYieldRange(final double iUpperYield, final double iAverageYield, final double iLowerYield) {
		_upperYield = iUpperYield;
		_averageYield = iAverageYield;
		_lowerYield = iLowerYield;
	}

	/** 
	 * Getter for the upper yield of the range.
	 */
	public double getUpperYield() {
		return _upperYield;
	}
	
	/** 
	 * Getter for the average yield of the range.
	 */
	public double getAverageYield() {
		return _averageYield;
	}
	
	/** 
	 * Getter for the lower yield of the range.
	 */
	public double getLowerYield() {
		return _lowerYield;
	}

	/** 
	 * Setter for the upper yield of the range.
	 */
	public void setUpperYield(final double iUpperYield) {
		_upperYield = iUpperYield;
	}
	
	/**
	 * Setter for the average yield of the range.
	 */
	public void setAverageYield(final double iAverageYield) {
		_averageYield = iAverageYield;
	}
	
	/**
	 * Setter for the lower yield of the range.
	 */
	public void setLowerYield(final double iLowerYield) {
		_lowerYield = iLowerYield;
	}
	
	@Override
	public String toString() {
		String out = "";
		
		out += "<FldYieldRange upperYield=\"" + _upperYield + "\" averageYield=\"" + _averageYield + "\" lowerYield=\"" + _lowerYield + "\"/>";
		
		return out;
	}
}
