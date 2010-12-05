// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#include <vector>
// StdAir
#include <stdair/bom/OptimizerStruct.hpp>

namespace stdair {

  // ///////////////////////////////////////////////////////////////////    
  OptimizerStruct::OptimizerStruct () {
  }
  
  // ///////////////////////////////////////////////////////////////////    
  OptimizerStruct::OptimizerStruct 
  (const OptimizerMode_T& iOptimizerMode,
   const SellupFlagForOptimizer_T& iSellupFlagForOptimizer,
   const SellupProbabilityVector_T& iSellupProbabilityVectorForOptimizer) 
    : _optimizerMode(iOptimizerMode),
      _sellupFlagForOptimizer(iSellupFlagForOptimizer),
      _sellupProbabilityVectorForOptimizer(iSellupProbabilityVectorForOptimizer){
  }

  // ///////////////////////////////////////////////////////////////////    
  OptimizerStruct::OptimizerStruct 
  (const OptimizerStruct& iOptimizerStruct) 
    : _optimizerMode(iOptimizerStruct._optimizerMode),
      _sellupFlagForOptimizer(iOptimizerStruct._sellupFlagForOptimizer),
      _sellupProbabilityVectorForOptimizer(iOptimizerStruct._sellupProbabilityVectorForOptimizer) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  OptimizerStruct::~OptimizerStruct () {
  }

  // ////////////////////////////////////////////////////////////////////
  void OptimizerStruct::
  init (const OptimizerMode_T& iOptimizerMode,
        const SellupFlagForOptimizer_T& iSellupFlagForOptimizer,
        const SellupProbabilityVector_T& iSellupProbabilityVectorForOptimizer) {
    _optimizerMode = iOptimizerMode;
    _sellupFlagForOptimizer = iSellupFlagForOptimizer;
    _sellupProbabilityVectorForOptimizer = iSellupProbabilityVectorForOptimizer;
  }
        
  // ////////////////////////////////////////////////////////////////////
  const std::string OptimizerStruct::describe() const {
    std::ostringstream ostr;
    ostr << _optimizerMode 
         << "," << _sellupFlagForOptimizer 
         << "," << describeSellupProbabilityVector();
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string OptimizerStruct::describeSellupProbabilityVector() const {
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
