// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include "DemandGeneratorList.hpp"

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  DemandGeneratorList::DemandGeneratorList () {
    const ParameterList_T aParameterList;
    init (aParameterList);
  }
  
  // //////////////////////////////////////////////////////////////////////
  DemandGeneratorList::
  DemandGeneratorList (const DemandGeneratorList& iDemandGeneratorList) {
    // TODO: copy the distribution parameters of the input generator list
    const ParameterList_T aParameterList;
    init (aParameterList);
  }
  
  // //////////////////////////////////////////////////////////////////////
  DemandGeneratorList::
  DemandGeneratorList (const ParameterList_T& iParameterList) {
    init (iParameterList);
  }
  
  // //////////////////////////////////////////////////////////////////////
  DemandGeneratorList::~DemandGeneratorList () {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void DemandGeneratorList::init (const ParameterList_T& iParameterList) {

    for (ParameterList_T::const_iterator itParams = iParameterList.begin();
         itParams != iParameterList.end(); itParams++) {
      const FldDistributionParameters& aParams = *itParams;
      const double aMean = aParams.getMean();
      const double aStandardDeviation = aParams.getStandardDeviation();
      
      const Gaussian gaussianGenerator (aMean, aStandardDeviation);
      
      _demandGeneratorList.push_back (gaussianGenerator);
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  void DemandGeneratorList::
  generateVariateList (VariateList_T& ioVariateList) const {

    // Iterate on the (number of) buckets
    DemandGeneratorList_T::const_iterator itGenerator =
      _demandGeneratorList.begin();
    for ( ; itGenerator != _demandGeneratorList.end(); itGenerator++) {
      const Gaussian& gaussianGenerator = *itGenerator;

      // Generate a random variate following the Gaussian distribution
      const double generatedVariate = gaussianGenerator.generateVariate ();
      ioVariateList.push_back (generatedVariate);
    }
  }

}
