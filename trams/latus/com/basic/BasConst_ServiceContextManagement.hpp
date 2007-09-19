#ifndef __LATUS_COM_BAS_BASCONST_SERVICECONTEXTMANAGEMENT_HPP
#define __LATUS_COM_BAS_BASCONST_SERVICECONTEXTMANAGEMENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace LATUS {

  namespace COM {
    
    /** Default name for the Simulator (SIM) module. */
    extern const std::string DEFAULT_LATUS_SIM_MODULE_NAME;

    /** Default name for the Discrete Event Generator (DEG) module. */
    extern const std::string DEFAULT_LATUS_DEG_MODULE_NAME;

    /** Default name for the User Choice Model (UCM) module. */
    extern const std::string DEFAULT_LATUS_UCM_MODULE_NAME;

    /** Default name for the Central Reservation System (CRS) module. */
    extern const std::string DEFAULT_LATUS_CRS_MODULE_NAME;

    /** Default name for the Travel Service Provider (TSP) module. */
    extern const std::string DEFAULT_LATUS_TSP_MODULE_NAME;

    /** Default name for the Fare Quote (FQT) module. */
    extern const std::string DEFAULT_LATUS_FQT_MODULE_NAME;

    /** Default root name for the Inventory (INV) module. */
    extern const std::string DEFAULT_LATUS_INV_ROOT_MODULE_NAME;

    /** Default name for the Revenue Management System (RMS) module. */
    extern const std::string DEFAULT_LATUS_RMS_ROOT_MODULE_NAME;
  }
}
#endif // __LATUS_COM_BAS_BASCONST_SERVICECONTEXTMANAGEMENT_HPP
