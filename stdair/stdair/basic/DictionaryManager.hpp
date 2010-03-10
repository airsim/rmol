// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_DICTIONARYMANAGER_HPP
#define __STDAIR_BOM_DICTIONARYMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {
  
  /** Class wrapper of dictionary business methods. */
  class DictionaryManager {
  public:
    // //////////// Business methods /////////////////
    /** Convert from key to value. */
    static const Probability_T keyToValue (const DictionaryKey_T);
    
    /** Convert from value to key. */
    static const DictionaryKey_T valueToKey (const Probability_T);

  };
}
#endif // __STDAIR_BOM_DICTIONARYMANAGER_HPP
