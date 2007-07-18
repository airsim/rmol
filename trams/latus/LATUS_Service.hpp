#ifndef __LATUS_SVC_LATUS_SERVICE_HPP
#define __LATUS_SVC_LATUS_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS
#include <latus/LatusTypes.hpp>

namespace LATUS {

  /** Forward declaration. */
  namespace SIM {
    class LATUS_SIM;
  }

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

    /** Set the input filename (for test purposes). */
    void setInputFilename (const std::string&);

    /** Set the start date of the simulation. */
    void setStartDate (const boost::gregorian::date&);

    /** Set the end date of the simulation. */
    void setEndDate (const boost::gregorian::date&);

    /** Simulate. */
    void simulate () const;

  private:
    /** Default Constructors. */
    // LATUS_Service ();
    LATUS_Service (const LATUS_Service&);

    /** Initialiser. */
    void init ();
    
    /** Simulator (SIM) Service */
    SIM::LATUS_SIM* _simService;
    
  };
}
#endif // __LATUS_SVC_LATUS_SERVICE_HPP
