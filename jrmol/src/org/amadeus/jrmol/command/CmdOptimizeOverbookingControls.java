package org.amadeus.jrmol.command;

//import org.amadeus.jrmol.bom.BomOverbooking;
//import org.amadeus.jrmol.field.FldDistributionParameters;
//import org.amadeus.jrmol.field.FldOverbookingPolicy;

/** 
 * Class holding the algorithms for the optimisation of the
 * overbooking controls.
 */
public abstract class CmdOptimizeOverbookingControls {
//
//	/** 
//	 * Overbooking Calculation Policy.
//	 */
//	private static FldOverbookingPolicy _policy = null;
//
//	/**
//	 * Overbooking. 
//	 */
//	private static BomOverbooking _overbooking = null;
//	
//	/** 
//	 * This function return the OB% with its standard deviation
//	 * following the given choice of method.
//	 */
//	public static final FldDistributionParameters optimizeOverbooking() {
//
//		switch (_policy.getPolicy().ordinal()) {
//
//		case FldOverbookingPolicy.Policy.HEURISTIC.ordinal(): 
//			return calculateHeuristic(); 
//			
//		case FldOverbookingPolicy.Policy.RISK_BASED.ordinal():  
//			return calculateRiskBased();
//			
//		case FldOverbookingPolicy.Policy.SERVICE_LEVEL_1.ordinal(): 
//			return calculateServiceLevel1();
//
//		case FldOverbookingPolicy.Policy.SERVICE_LEVEL_2.ordinal(): 
//			return calculateServiceLevel2();
//		
//		case FldOverbookingPolicy.Policy.HYBRID.ordinal(): 
//			return calculateHybridPolicy();
//			
//		default: 
//			return calculateHeuristic();
//		
//		}
//		
//	}
//
//	/**
//	 * This function calculates the OB% by the heuristic method.
//	 */
//	private static FldDistributionParameters calculateHeuristic() {
//	    FldDistributionParameters overbookingPercentage = new FldDistributionParameters();
//
//	    final double theCancellationsPercentage = _overbooking.getRemainingCancellationDistributionParameters().getMean() * _overbooking.getNetBookings() / _overbooking.getCapacity();
//
//	    // Overbooking average percentage
//	    final double theNoShow = _overbooking.getNoShowDistributionParameters().getMean();
//	    final double theOverbookingMean = (theNoShow + theCancellationsPercentage) / (1.0 - (theNoShow + theCancellationsPercentage));
//	    overbookingPercentage.setMean(theOverbookingMean);
//
//	    // Overbooking deviation (heuristic)
//	    final double theNoShowStandardDeviation = _overbooking.getNoShowDistributionParameters().getStandardDeviation();
//	    final double theNoShowVariance = Math.pow(theNoShowStandardDeviation, 2);
//
//	    final double theCancellationStandardDeviation = _overbooking.getCancellationDistributionParameters().getStandardDeviation();
//	    final double theCancellationVariance = Math.pow(theCancellationStandardDeviation, 2);
//
//	    final double theOverbookingStandardDeviation = Math.sqrt(theNoShowVariance + theCancellationVariance);
//	    overbookingPercentage.setStandardDeviation(theOverbookingStandardDeviation);
//
//	    return overbookingPercentage;
//	}
//
//	/**
//	 * This function calculates the OB% by the cost-based method.
//	 */
//	private static FldDistributionParameters calculateRiskBased() {
//		
//	    // take the Overbooking average and deviation by Heuristic method
//	    // in order to calculate some parameters ? show rate for example
//	    FldDistributionParameters overbookingPercentage = calculateHeuristic();
//
//	    // Show rate = shows/net booking;
//	    const double lBookingLimit = calculateBookingLimit ();
//
//	    const double lOBMean = lBookingLimit / _capacity - 1.0;
//	    resultOBPercentage.setMean (lOBMean);
//		
//	    return resultOBPercentage;
//	}
//
//	/** 
//	 * This function calculates the OB% by the service level policies.
//	 */
//	public FldDistributionParameters calculateServiceLevel() {
//
//	}
//
//	/**
//	 * This function calculates the OB% by the Hybrid policy
//	 */
//	public FldDistributionParameters calculateHybridPolicy() {
//
//	}
//
//	/** 
//	 * Gets the overbooking calculation policy.
//	 */
//	public final FldOverbookingPolicy getPolicy() {
//		return _policy;
//	}
//
//	/** 
//	 * Sets the overbooking calculation policy.
//	 */
//	public final void setPolicy(FldOverbookingPolicy iPolicy) {
//		_policy = iPolicy;
//	}
//
//	private double calculateBookingLimit() {
//
//	}
//
//	private double probabilityNormal(const int, const double, const double) {
//
//	}
//
//	private double binomialProbability_F_b_s(const double, const int, const int) {
//
//	}
//
//	private double serviceLevel1(const double, const int, const int) {
//
//	}
//
//	private double fractionServiceLevel2(const double ,  const int , const int) {
//
//	}
}
