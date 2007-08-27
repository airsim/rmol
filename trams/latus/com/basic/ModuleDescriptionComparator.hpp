#ifndef __LATUS_COM_BAS_MODULEDESCRIPTIONCOMPARATOR_HPP
#define __LATUS_COM_BAS_MODULEDESCRIPTIONCOMPARATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/ModuleDescription.hpp>

namespace LATUS {

  namespace COM {

    /** Comparator function object, to get ModuleDescription as a key within
        STL maps. */
    class ModuleDescriptionComparator {
    public:
      bool operator() (const ModuleDescription& iModule1,
                       const ModuleDescription& iModule2) const {
        typedef const std::pair<const ModuleDescription::EN_ModuleType,
          const std::string> ModuleTypeNamePair_T;
        ModuleTypeNamePair_T lModulePair1 (iModule1.getType(),
                                           iModule1.getName());
        ModuleTypeNamePair_T lModulePair2 (iModule2.getType(),
                                           iModule2.getName());
        return (lModulePair1 < lModulePair2);
      }
      
    };

  }
}
#endif // __LATUS_COM_BAS_MODULEDESCRIPTIONCOMPARATOR_HPP
