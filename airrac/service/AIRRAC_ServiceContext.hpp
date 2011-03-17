#ifndef __AIRRAC_SVC_AIRRACSERVICECONTEXT_HPP
#define __AIRRAC_SVC_AIRRACSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_service_types.hpp>
// Airrac
#include <airrac/AIRRAC_Types.hpp>
#include <airrac/service/ServiceAbstract.hpp>

namespace AIRRAC {

  /** Class holding the context of the Airrac services. */
  class AIRRAC_ServiceContext : public ServiceAbstract {
    friend class FacAirracServiceContext;
  public:
    // ///////// Getters //////////
    /** Get the pointer on the STDAIR service handler. */
    stdair::STDAIR_ServicePtr_T getSTDAIR_Service () const {
      return _stdairService;
    }
        
    // ///////////////// Setters ///////////////////
    /** Set the pointer on the STDAIR service handler. */
    void setSTDAIR_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr) {
      _stdairService = ioSTDAIR_ServicePtr;
    } 

    // ///////// Display Methods //////////
    /** Display the short AIRRAC_ServiceContext content. */
    const std::string shortDisplay() const;
    
    /** Display the full AIRRAC_ServiceContext content. */
    const std::string display() const;
    
  private:
    // /////// Construction / initialisation ////////
    /** Constructors. */
    AIRRAC_ServiceContext ();
    AIRRAC_ServiceContext (const YieldID_T&);
    AIRRAC_ServiceContext (const AIRRAC_ServiceContext&);

    /** Destructor. */
    ~AIRRAC_ServiceContext();

  private:
    // //////////// Attributes //////////////////
    /** Standard Airline (StdAir) Service Handler. */
    stdair::STDAIR_ServicePtr_T _stdairService;
  };

}
#endif // __AIRRAC_SVC_AIRRACSERVICECONTEXT_HPP
