#ifndef __AIRRAC_SVC_AIRRACSERVICECONTEXT_HPP
#define __AIRRAC_SVC_AIRRACSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_service_types.hpp>
#include <stdair/service/ServiceAbstract.hpp>
// Airrac
#include <airrac/AIRRAC_Types.hpp>

/// Forward declarations
namespace stdair {
  class STDAIR_Service;
}

namespace AIRRAC {

  /**
   * @brief Inner class holding the context for the AIRRAC Service object.
   */
  class AIRRAC_ServiceContext : public stdair::ServiceAbstract {
    /**
     * The AIRRAC_Service class should be the sole class to get access to
     * ServiceContext content: general users do not want to bother
     * with a context interface.
     */
    friend class AIRRAC_Service;
    friend class FacAirracServiceContext;
    
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
    stdair::STDAIR_Service& getSTDAIR_Service() const {
      assert (_stdairService != NULL);
      return *_stdairService;
    }
    
    /**
     * State whether or not RMOL owns the STDAIR service resources.
     */
    const bool getOwnStdairServiceFlag() const {
      return _ownStdairService;
    }


  private:   
    // ///////////////// Setters ///////////////////
    /**
     * Set the pointer on the STDAIR service handler.
     */
    void setSTDAIR_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr,
                            const bool iOwnStdairService) {
      _stdairService = ioSTDAIR_ServicePtr;
      _ownStdairService = iOwnStdairService;
    }


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
     * Default constructor.
     */
    AIRRAC_ServiceContext();

    /**
     * Copy constructor.
     */
    AIRRAC_ServiceContext (const AIRRAC_ServiceContext&);

    /**
     * Destructor.
     */
    ~AIRRAC_ServiceContext();

    /**
     * Clear the context.
     */
    void reset();


  private:
    // //////////// Attributes //////////////////
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
#endif // __AIRRAC_SVC_AIRRACSERVICECONTEXT_HPP
