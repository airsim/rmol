package org.amadeus.jrmol.field;

/** 
 * Class wrapping the policy for the overbooking calculation.
 */
public class FldOverbookingPolicy {

	/** 
	 * Overbooking Calculation Policy.
	 */
	private Policy _policy = Policy.HEURISTIC;

	public static enum Policy {
		HEURISTIC,       // Heuristic
		RISK_BASED,      // Risk-Based
		SERVICE_LEVEL_1, // Service-Level 1
		SERVICE_LEVEL_2, // Service-Level 2
		HYBRID,          // Hybrid
		LAST_VALUE
	};

	/** 
	 * Constructors.
	 */
	public FldOverbookingPolicy(final FldOverbookingPolicy iFldOverbookingPolicy) {
		_policy = iFldOverbookingPolicy.getPolicy();
	}

	public FldOverbookingPolicy(final Policy iPolicy) {
		_policy = iPolicy;
	}

	public FldOverbookingPolicy() {

	}

	/** 
	 * Getter for the mean value.
	 */
	public final Policy getPolicy() {
		return _policy;
	}

	/** 
	 * Setter for the mean value.
	 */
	public void setPolicy(final Policy iPolicy) {
		_policy = iPolicy;
	}
}
