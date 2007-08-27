// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacServiceContext.hpp>
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/LATUS_Service_Internal.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS General
#include <latus/LATUS_Service.hpp>

namespace LATUS {

  // //////////////////////////////////////////////////////////////////////
  LATUS_Service::LATUS_Service () {
    // Initialise
    init ();
  }

  // //////////////////////////////////////////////////////////////////////
  LATUS_Service::~LATUS_Service () {
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::init () {
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setLogParameters (const LOG::EN_LogLevel iLogLevel,
                                        std::ostream& ioLogStream) {
    COM::LATUS_Service_Internal::instance().
      setLogParameters (iLogLevel, ioLogStream);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setSimulationRunNumber (const int iSimulationRunNumber) {
    COM::LATUS_Service_Internal::instance().
      setSimulationRunNumber (iSimulationRunNumber);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::
  setScheduleInputFilename (const std::string& iInputFilename) {
    COM::LATUS_Service_Internal::instance().
      setScheduleInputFilename (iInputFilename);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::
  setDemandInputFilename (const std::string& iInputFilename) {
    COM::LATUS_Service_Internal::instance().
      setDemandInputFilename (iInputFilename);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setStartDate (const boost::gregorian::date& iStartDate) {
    COM::LATUS_Service_Internal::instance().setStartDate (iStartDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setEndDate (const boost::gregorian::date& iEndDate) {
    COM::LATUS_Service_Internal::instance().setEndDate (iEndDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::simulate () const {
    COM::LATUS_Service_Internal::instance().simulate();
  }

}
