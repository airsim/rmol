#ifndef __STDAIR_BOM_OPTIMIZERSTRUCT_HPP
#define __STDAIR_BOM_OPTIMIZERSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  /** Utility structure for parsing optimizer setting. */
  struct OptimizerStruct_T {
  public:      
    // /////////// Getters ////////////////
    /** Get the optimizer mode. */
    const OptimizerMode_T& getOptimizerMode() const {
      return _optimizerMode;
    } 

    /** Get the sell-up usage flag for optimizer. */
    const SellupFlagForOptimizer_T& getSellupFlagForOptimizer() const {
      return _sellupFlagForOptimizer;
    }

    /** Get the sell-up probability vector. */
    const SellupProbabilityVector_T& 
    getSellupProbabilityVectorForOptimizer() const {
      return _sellupProbabilityVectorForOptimizer;
    }
    
    // ///////// Display Methods //////////
    /** Display the structure. */
    const std::string describe() const;

    /** Display sell-up probability vector. */
    const std::string describeSellupProbabilityVector() const;

  public:
    /** Constructor. */
    OptimizerStruct_T (const OptimizerMode_T&,
                       const SellupFlagForOptimizer_T&,
                       const SellupProbabilityVector_T&);
    /** Default copy constructor. */
    OptimizerStruct_T (const OptimizerStruct_T&);

    /** Defaut destructor. */
    ~OptimizerStruct_T ();
  private:
    /** Default constructor. */
    OptimizerStruct_T ();
      
      
  private:
    // /////////////// Attributes //////////
    /** Attributes. */
    OptimizerMode_T _optimizerMode;
    SellupFlagForOptimizer_T _sellupFlagForOptimizer;
    SellupProbabilityVector_T _sellupProbabilityVectorForOptimizer;
  };

}
#endif //__STDAIR_BOM_OPTIMIZERSTRUCT_HPP
