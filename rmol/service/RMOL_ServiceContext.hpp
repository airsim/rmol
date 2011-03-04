#ifndef __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP
#define __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost
#include <boost/shared_ptr.hpp>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_service_types.hpp>
#include <stdair/service/ServiceAbstract.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations
namespace stdair {
  class STDAIR_Service;
  class LegCabin;
}

namespace RMOL {

  /** Pointer on the STDAIR Service handler. */
  typedef boost::shared_ptr<stdair::STDAIR_Service> STDAIR_ServicePtr_T;
  
  /** Inner class holding the context for the RMOL Service object. */
  class RMOL_ServiceContext : public stdair::ServiceAbstract {
    /** The RMOL_Service class should be the sole class to get access to
        ServiceContext content: general users do not want to bother
        with a context interface. */
    friend class RMOL_Service;
    friend class FacRmolServiceContext;
    
  private:
    // /////// Construction / initialisation ////////
    /** Constructors. */
    RMOL_ServiceContext ();
    RMOL_ServiceContext (const RMOL_ServiceContext&);
        
    /** Destructor. */
    ~RMOL_ServiceContext();

  private:    
    /** Set the pointer on the STDAIR service handler. */
    void setSTDAIR_Service (STDAIR_ServicePtr_T ioSTDAIR_ServicePtr) {
      _stdairService = ioSTDAIR_ServicePtr;
    }

    /** Read the input data from a file. */
    void readFromInputFile (const std::string& iInputFileName);

    /** Clear the context (cabin capacity, bucket holder). */
    void reset ();
    
    /** Get the pointer on the STDAIR service handler. */
    stdair::STDAIR_ServicePtr_T getSTDAIR_ServicePtr () const {
      return _stdairService;
    }

    /** Get the STDAIR service handler. */
    stdair::STDAIR_Service& getSTDAIR_Service () const {
      assert (_stdairService != NULL);
      return *_stdairService;
    }

    /** Get the leg-cabin sample for optimisation. */
    stdair::LegCabin& getLegCabinSample () const;
    
  private:
    // ///////////// Children ////////////
    /** Standard Airline (StdAir) Service Handler. */
    STDAIR_ServicePtr_T _stdairService;
  };

}
#endif // __RMOL_SVC_RMOL_SERVICE_CONTEXT_HPP
