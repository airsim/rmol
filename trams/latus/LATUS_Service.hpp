#ifndef __LATUS_SVC_LATUS_SERVICE_HPP
#define __LATUS_SVC_LATUS_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS
#include <latus/LatusTypes.hpp>

namespace LATUS {

  // Internal interface implementing that external one
  class LATUS_Service_Internal;

  
  /** Interface for the LATUS Services. */
  class LATUS_Service {
  public:
    /** Constructor. */
    LATUS_Service ();

    /** Destructor. */
    ~LATUS_Service();

    /** Set the logger parameters (level and stream). */
    void setLogParameters (const LOG::EN_LogLevel iLogLevel,
                           std::ostream& ioLogStream);

    /** Set the number of simulations to be run. */
    void setSimulationRunNumber (const int);

    /** Set the demand input filename (for test purposes). */
    void setDemandInputFilename (const std::string&);

    /** Set the schedule input filename (for test purposes). */
    void setScheduleInputFilename (const std::string&);

    /** Set the start date of the simulation. */
    void setStartDate (const boost::gregorian::date&);

    /** Set the end date of the simulation. */
    void setEndDate (const boost::gregorian::date&);


  public:
    /** Simulate. */
    void simulate () const;

    
  private:
    /** Initialiser. */
    void init ();
  };
}
#endif // __LATUS_SVC_LATUS_SERVICE_HPP
