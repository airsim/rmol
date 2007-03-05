package org.amadeus.jrmol.bom;

import java.util.Vector;

import org.amadeus.jrmol.field.FldDistributionParameters;

/** 
 * Wrapper around a set of Gaussian Random Generators.
 */
public class BomDemandGeneratorList extends BomAbstract {

	private class GaussianList extends Vector<BomGaussian> {}

	private GaussianList _demandGeneratorList = null;

	public BomDemandGeneratorList() {
		Vector<FldDistributionParameters> aDistributionParametersList = new Vector<FldDistributionParameters>();
		init(aDistributionParametersList);
	}

	public BomDemandGeneratorList(final BomDemandGeneratorList iDemandGeneratorList) {
		Vector<FldDistributionParameters> aDistributionParametersList = new Vector<FldDistributionParameters>();
		init(aDistributionParametersList);
	}

	public BomDemandGeneratorList(final Vector<FldDistributionParameters> iDistributionParametersList) {
		init(iDistributionParametersList);
	}

	/** Initialise the Random Genrators. */
	private void init(final Vector<FldDistributionParameters> iDistributionParametersList) {
	    for (FldDistributionParameters aParams : iDistributionParametersList) {	      
	      final BomGaussian gaussianGenerator = new BomGaussian(aParams);
	      
	      _demandGeneratorList.add(gaussianGenerator);
	    }
	}

	public void generateVariateList(final Vector<Double> iVariateList) {

	    // Iterate on the (number of) classes/buckets, n
	    for (BomGaussian gaussianGenerator : _demandGeneratorList) {

	      // Generate a random variate following the Gaussian distribution
	      final double generatedVariate = gaussianGenerator.generateVariate();
	      
	      iVariateList.add(generatedVariate);
	    }
	}
}
