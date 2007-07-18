#ifndef __LATUS_DEG_SVC_LATUS_DEG_HPP
#define __LATUS_DEG_SVC_LATUS_DEG_HPP

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

  namespace DEG {

    // TODO: Add the (GSL) random seed in the service context, so that
    // it is not re-set at each new simulation
    
    /** Class wrapping the services offered by the DEG module. */
    class LATUS_DEG : public COM::LATUS_ServiceAbstract {
      // Only FacDegService_Service may instantiate LATUS_DEG
      friend class FacDegService;
    public:
      /** Set the input file name (for test purposes). */
      void setInputFilename (const std::string&);

      /** Set the start date of the simulation. */
      void setStartDate (const boost::gregorian::date&);

      /** Set the end date of the simulation. */
      void setEndDate (const boost::gregorian::date&);

      /** Main entry point: generate an event. */
      void generateEvent () const;
      
    private:
      /** Default Constructors. */
      LATUS_DEG (const std::string& iModuleName);
      /** Destructor. */
      ~LATUS_DEG();

      /** Initialiser. */
      void initSpecificContext ();
      
    private:
      // Attributes
    };
  }
}
#endif // __LATUS_DEG_SVC_LATUS_DEG_HPP
