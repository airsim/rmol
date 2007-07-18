// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/service/ServiceContext.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS Inventory
#include <latus/deg/command/DemandEventGenerator.hpp>
#include <latus/deg/service/LATUS_DEG.hpp>

namespace LATUS {
  
  namespace DEG {

    // //////////////////////////////////////////////////////////////////////
    LATUS_DEG::LATUS_DEG (const std::string& iModuleName) :
      LATUS_ServiceAbstract(COM::ModuleDescription(COM::ModuleDescription::DEG,
                                                   iModuleName)) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LATUS_DEG::~LATUS_DEG () {
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_DEG::initSpecificContext () {
      
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_DEG::setInputFilename (const std::string& iInputFilename) {
      COM::ServiceContext& lServiceContext = getServiceContext();
      lServiceContext.setInputFilename (iInputFilename);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_DEG::setStartDate (const boost::gregorian::date& iStartDate) {
      COM::ServiceContext& lServiceContext = getServiceContext();
      lServiceContext.setStartDate (iStartDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_DEG::setEndDate (const boost::gregorian::date& iEndDate) {
      COM::ServiceContext& lServiceContext = getServiceContext();
      lServiceContext.setEndDate (iEndDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void LATUS_DEG::generateEvent () const {

    }

  }
  
}
