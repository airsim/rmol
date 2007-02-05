package org.amadeus.jrmol.bom;

import org.amadeus.jrmol.field.FldDistributionParameters;
import org.amadeus.jrmol.field.FldYieldRange;

/** 
 * Class modelling the demand. It holds:
 *  - Demand parameters: mean and standad deviation.
 *  - Yield range: upper yield and average yield.
 */
public class BomDemand extends BomAbstract {

	/** 
	 * Yield range, i.e., upper and lower yields, as well as average yield
	 * (average revenue per unit of demand).
	 */
	private FldYieldRange _yieldRange = null;

	/**
	 * Distribution parameters (i.e., mean and standard deviation).
	 */
	private FldDistributionParameters _distributionParameters = null;
	
	public BomDemand() {
		_yieldRange = new FldYieldRange();
		_distributionParameters = new FldDistributionParameters();
	}

	public BomDemand(final BomDemand iDemand) {
		_yieldRange = new FldYieldRange(iDemand.getYieldRange());
		_distributionParameters = new FldDistributionParameters(iDemand.getDistributionParameters());
	}

	public BomDemand(final FldDistributionParameters iDistributionParameters, final FldYieldRange iYieldRange) {
		_yieldRange = new FldYieldRange(iYieldRange);
		_distributionParameters = new FldDistributionParameters(iDistributionParameters);
	}

	/** 
	 * Getter for the demand distribution parmaters (i.e., mean and
	 * standard deviation).
	 */
	public final FldDistributionParameters getDistributionParameters() {
		return _distributionParameters;
	}
	
	/**
	 * Getter for the average yield per unit of demand.
	 */
	public final FldYieldRange getYieldRange() {
		return _yieldRange;
	}
	
	@Override
	public String toString() {
		String out = "";
		
		out += "<bombucket>";
		out += _yieldRange;
		out += _distributionParameters;
		out += "</bombucket>";
		
		return out;
	}
}
