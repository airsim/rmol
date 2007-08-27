#ifndef __LATUS_SIM_SVC_LATUS_SIM_HPP
#define __LATUS_SIM_SVC_LATUS_SIM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {

  namespace SIM {

    // TODO: Add the (GSL) random seed in the service context, so that
    // it is not re-set at each new simulation
    
    /** Class wrapping the services offered by the SIM module. */
    class LATUS_SIM : public COM::LATUS_ServiceAbstract {
      // Only FacSimService_Service may instantiate LATUS_SIM
      friend class FacSimService;
    public:
      /** Set the number of simulation runs. */
      void setSimulationRunNumber (const int);

      /** Set the demand input file name (for test purposes). */
      void setDemandInputFilename (const std::string&);

      /** Set the start date of the simulation. */
      void setStartDate (const boost::gregorian::date&);

      /** Set the end date of the simulation. */
      void setEndDate (const boost::gregorian::date&);

      /** Main entry point. */
      static void simulate (const std::string& iModuleName);
      
    private:
      /** Constructors. */
      LATUS_SIM();
      /** Destructor. */
      ~LATUS_SIM();
      
    private:
      // Attributes
    };
  }
}
#endif // __LATUS_SIM_SVC_LATUS_SIM_HPP
