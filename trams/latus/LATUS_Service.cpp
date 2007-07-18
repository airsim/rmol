// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/factory/FacServiceContext.hpp>
#include <latus/sim/factory/FacSimService.hpp>
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS Simulator
#include <latus/sim/service/LATUS_SIM.hpp>
// LATUS General
#include <latus/LATUS_Service.hpp>

namespace LATUS {

  // //////////////////////////////////////////////////////////////////////
  LATUS_Service::LATUS_Service (const LATUS_Service& iService) :
    _simService (NULL) {
    // Initialise
    init ();
  }

  // //////////////////////////////////////////////////////////////////////
  LATUS_Service::LATUS_Service () : _simService (NULL) {
    // Initialise
    init ();
  }

  // //////////////////////////////////////////////////////////////////////
  LATUS_Service::~LATUS_Service () {
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::init () {
    _simService = &SIM::FacSimService::instance().create ("SIM");
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setLogParameters (const LOG::EN_LogLevel iLogLevel,
                                        std::ostream& ioLogStream) {
    COM::Logger::instance().setLogParameters (iLogLevel, ioLogStream);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setSimulationRunNumber (const int iSimulationRunNumber) {
    assert (_simService != NULL);
    _simService->setSimulationRunNumber (iSimulationRunNumber);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setInputFilename (const std::string& iInputFilename) {
    assert (_simService != NULL);
    _simService->setInputFilename (iInputFilename);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setStartDate (const boost::gregorian::date& iStartDate) {
    assert (_simService != NULL);
    _simService->setStartDate (iStartDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::setEndDate (const boost::gregorian::date& iEndDate) {
    assert (_simService != NULL);
    _simService->setEndDate (iEndDate);
  }

  // //////////////////////////////////////////////////////////////////////
  void LATUS_Service::simulate () const {

    // Call the main entry of the Simulator Service
    assert (_simService != NULL);
    _simService->simulate ();
  }

}
