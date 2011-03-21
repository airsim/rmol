#ifndef __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP
#define __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_service_types.hpp>
#include <stdair/service/ServiceAbstract.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

/// Forward declarations
namespace stdair {
  class STDAIR_Service;
  class LegCabin;
}

namespace RMOL {

  /**
   * @brief Inner class holding the context for the RMOL Service object.
   */
  class RMOL_ServiceContext : public stdair::ServiceAbstract {
    /**
     * The RMOL_Service class should be the sole class to get access to
     * ServiceContext content: general users do not want to bother
     * with a context interface.
     */
    friend class RMOL_Service;
    friend class FacRmolServiceContext;
    
  private:
    // ///////// Getters //////////
    /**
     * Get the pointer on the STDAIR service handler.
     */
    stdair::STDAIR_ServicePtr_T getSTDAIR_ServicePtr() const {
      return _stdairService;
    }

    /**
     * Get the STDAIR service handler.
     */
    stdair::STDAIR_Service& getSTDAIR_Service() const;

    /**
     * State whether or not RMOL owns the STDAIR service resources.
     */
    const bool getOwnStdairServiceFlag() const {
      return _ownStdairService;
    }


  private:    
    // ///////// Setters //////////
    /**
     * Set the pointer on the STDAIR service handler.
     */
    void setSTDAIR_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr,
                            const bool iOwnStdairService) {
      _stdairService = ioSTDAIR_ServicePtr;
      _ownStdairService = iOwnStdairService;
    }

    /**
     * Clear the context (cabin capacity, bucket holder).
     */
    void reset();


  private:
    // ///////// Display Methods //////////
    /**
     * Display the short STDAIR_ServiceContext content.
     */
    const std::string shortDisplay() const;
    
    /**
     * Display the full STDAIR_ServiceContext content.
     */
    const std::string display() const;

    /**
     * Display of the structure.
     */
    const std::string describe() const;


  private:
    // /////// Construction / initialisation ////////
    /**
     * Constructor.
     */
    RMOL_ServiceContext();
    /**
     * Copy constructor.
     */
    RMOL_ServiceContext (const RMOL_ServiceContext&);
        
    /**
     * Destructor.
     */
    ~RMOL_ServiceContext();


  private:
    // ///////////// Children ////////////
    /**
     * Standard Airline (StdAir) Service Handler.
     */
    stdair::STDAIR_ServicePtr_T _stdairService;

    /**
     * State whether or not RMOL owns the STDAIR service resources.
     */
    bool _ownStdairService;
  };

}
#endif // __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP
