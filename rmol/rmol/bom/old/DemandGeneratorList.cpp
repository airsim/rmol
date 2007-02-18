// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/bom/DemandGeneratorList.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  DemandGeneratorList::DemandGeneratorList () {
    const DistributionParameterList_T aDistributionParameterList;
    init (aDistributionParameterList);
  }
  
  // //////////////////////////////////////////////////////////////////////
  DemandGeneratorList::
  DemandGeneratorList (const DemandGeneratorList& iDemandGeneratorList) {
    // TODO: copy the distribution parameters of the input generator list
    const DistributionParameterList_T aDistributionParameterList;
    init (aDistributionParameterList);
  }
  
  // //////////////////////////////////////////////////////////////////////
  DemandGeneratorList::
  DemandGeneratorList (const DistributionParameterList_T& iDistributionParameterList) {
    init (iDistributionParameterList);
  }
  
  // //////////////////////////////////////////////////////////////////////
  DemandGeneratorList::~DemandGeneratorList () {
  }
  
  // //////////////////////////////////////////////////////////////////////
  void DemandGeneratorList::
  init (const DistributionParameterList_T& iDistributionParameterList) {

    DistributionParameterList_T::const_iterator itParams = 
      iDistributionParameterList.begin();
    for ( ; itParams != iDistributionParameterList.end(); itParams++) {
      const FldDistributionParameters& aParams = *itParams;
      
      const Gaussian gaussianGenerator (aParams);
      
      _demandGeneratorList.push_back (gaussianGenerator);
    }
  }
  
  // //////////////////////////////////////////////////////////////////////
  void DemandGeneratorList::
  generateVariateList (VariateList_T& ioVariateList) const {

    // Iterate on the (number of) classes/buckets, n
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
