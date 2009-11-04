// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <sstream>
#include <vector>
// STDAIR
#include <stdair/bom/OptimizerStruct.hpp>

namespace stdair {
  // ///////////////////////////////////////////////////////////////////    
  OptimizerStruct_T::OptimizerStruct_T () {
  }
  
  // ///////////////////////////////////////////////////////////////////    
  OptimizerStruct_T::OptimizerStruct_T 
  (const OptimizerMode_T& iOptimizerMode,
   const SellupFlagForOptimizer_T& iSellupFlagForOptimizer,
   const SellupProbabilityVector_T& iSellupProbabilityVectorForOptimizer) 
    : _optimizerMode(iOptimizerMode),
      _sellupFlagForOptimizer(iSellupFlagForOptimizer),
      _sellupProbabilityVectorForOptimizer(iSellupProbabilityVectorForOptimizer){
  }

  // ///////////////////////////////////////////////////////////////////    
  OptimizerStruct_T::OptimizerStruct_T 
  (const OptimizerStruct_T& iOptimizerStruct) 
    : _optimizerMode(iOptimizerStruct._optimizerMode),
      _sellupFlagForOptimizer(iOptimizerStruct._sellupFlagForOptimizer),
      _sellupProbabilityVectorForOptimizer(iOptimizerStruct._sellupProbabilityVectorForOptimizer) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  OptimizerStruct_T::~OptimizerStruct_T () {
  }

  // ////////////////////////////////////////////////////////////////////
  void OptimizerStruct_T::
  init (const OptimizerMode_T& iOptimizerMode,
        const SellupFlagForOptimizer_T& iSellupFlagForOptimizer,
        const SellupProbabilityVector_T& iSellupProbabilityVectorForOptimizer) {
    _optimizerMode = iOptimizerMode;
    _sellupFlagForOptimizer = iSellupFlagForOptimizer;
    _sellupProbabilityVectorForOptimizer = iSellupProbabilityVectorForOptimizer;
  }
        
  // ////////////////////////////////////////////////////////////////////
  const std::string OptimizerStruct_T::describe() const {
    std::ostringstream ostr;
    ostr << _optimizerMode 
         << "," << _sellupFlagForOptimizer 
         << "," << describeSellupProbabilityVector();
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string OptimizerStruct_T::describeSellupProbabilityVector() const {
    std::ostringstream ostr;
    for (SellupProbabilityVector_T::const_iterator itValue = 
           _sellupProbabilityVectorForOptimizer.begin(); 
         itValue != _sellupProbabilityVectorForOptimizer.end(); 
         ++itValue ) {
      ostr << *itValue << " ";
    }
    ostr << "\n";
    return ostr.str();
  }

}
