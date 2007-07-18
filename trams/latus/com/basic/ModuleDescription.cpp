// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/ModuleDescription.hpp>

namespace LATUS {
  
  namespace COM {
    
    // //////////////////////////////////////////////////////////////////////
    const std::string ModuleDescription::
    _labels[ModuleDescription::LAST_VALUE] =
      {"COM", "SIM", "DEG", "UCM", "CRS", "TSP", "AVS", "INV", "RMS"};

    // //////////////////////////////////////////////////////////////////////
    ModuleDescription::ModuleDescription (const EN_ModuleType iModuleType,
                                          const std::string& iName) :
      _type (iModuleType), _name (iName) {
    }
    
  }
  
}
