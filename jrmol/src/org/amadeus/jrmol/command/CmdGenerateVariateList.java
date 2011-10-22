package org.amadeus.jrmol.command;

import java.util.Vector;

import org.amadeus.jrmol.bom.BomGaussian;
import org.amadeus.jrmol.field.FldDistributionParameters;

public abstract class CmdGenerateVariateList {

	private static Vector<BomGaussian> _demandGeneratorList = null;
	
	static {
		init(new Vector<FldDistributionParameters>());
	}
	
	/**
	 * Inits demand generator.
	 */
	private static final void init(final Vector<FldDistributionParameters> iDistributionParametersList) {
		if (_demandGeneratorList == null) {
			_demandGeneratorList = new Vector<BomGaussian>();
		}
		
	    for (FldDistributionParameters aParams : iDistributionParametersList) {
	      final BomGaussian gaussianGenerator = new BomGaussian(aParams);
	      
	      _demandGeneratorList.add(gaussianGenerator);
	    }
	}
	
	/**
	 * Generates a variate list.
	 */
	public static final void generateVariateList(final Vector<FldDistributionParameters> iDistributionParametersList, final Vector<Double> iVariateList) {
		if (iDistributionParametersList != null) {
			_demandGeneratorList = null;
			init(iDistributionParametersList);
		}
		
	    // Iterate on the (number of) classes/buckets, n
	    for (BomGaussian gaussianGenerator : _demandGeneratorList) {

	      // Generate a random variate following the Gaussian distribution
	      final double generatedVariate = CmdGenerateVariate.generate(gaussianGenerator);
	      
	      iVariateList.add(generatedVariate);
	    }
	}
	
	/**
	 * Generates a variate list.
	 */
	public static final void generateVariateList(final Vector<Double> iVariateList) {
		generateVariateList(null, iVariateList);
	}
}
