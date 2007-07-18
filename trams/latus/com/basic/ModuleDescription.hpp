#ifndef __LATUS_COM_BAS_MODULEDESCRIPTION_HPP
#define __LATUS_COM_BAS_MODULEDESCRIPTION_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace LATUS {

  namespace COM {

    /** Wrapper class describing (mainly type and name) a specific module. */
    class ModuleDescription {
    public:

      typedef enum {
        COM = 0,  // Common
        SIM,      // Simulator (coordinator)
        DEG,      // Discrete-Event (Demand) Generator
        UCM,      // User Choice Model
        CRS,      // Central Reservation System
        TSP,      // Travel Solution Provider
        AVS,      // Availability Server
        INV,      // Inventory
        RMS,      // Revenue Management System
        LAST_VALUE
      } EN_ModuleType;

      /** Strings for input/output (display and parsing). */
      static const std::string _labels[LAST_VALUE];

      /** Constructor. */
      ModuleDescription (const EN_ModuleType, const std::string& iName);

      /** Get the type. */
      EN_ModuleType getType() const {
        return _type;
      }
      
      /** Get the name. */
      const std::string& getName() const {
        return _name;
      }
      
    private:
      /** Module type. */
      const EN_ModuleType _type;

      /** Module name. */
      const std::string _name;
    };
    
  }
}
#endif // __LATUS_COM_BAS_MODULEDESCRIPTION_HPP
