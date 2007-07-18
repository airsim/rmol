#ifndef __LATUS_COM_SVC_SERVICE_CONTEXT_HPP
#define __LATUS_COM_SVC_SERVICE_CONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS
#include <latus/LatusTypes.hpp>
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/service/ServiceAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Inner class holding the context for the LATUS Service object. */
    class ServiceContext : public ServiceAbstract {
      /** The LATUS_Service class should be the sole class to get access to
          ServiceContext content: general users do not want to bother
          with a context interface. */
      friend class LATUS_ServiceAbstract;
      friend class ServiceContextManager;
      friend class FacServiceContext;
    public:
      // //////// GETTERS /////////
      /** Get the input filename. */
      const std::string& getInputFilename () const {
        return _inputFilename;
      }
      
      /** Get the number of simulations to be run. */
      const int getSimulationRunNumber () const {
        return _simulationRunNumber;
      }
      
      /** Get the start date of the simulation. */
      const boost::gregorian::date& getStartDate () const {
        return _startDate;
      }

      /** Get the end date of the simulation. */
      const boost::gregorian::date& getEndDate () const {
        return _endDate;
      }


      // //////// SETTERS /////////
      /** Set the input filename. */
      void setInputFilename (const std::string& iInputFilename) {
        _inputFilename = iInputFilename;
      }
      
      /** Set the number of simulations to be run. */
      void setSimulationRunNumber (const int iSimulationRunNumber) {
        _simulationRunNumber = iSimulationRunNumber;
      }
      
      /** Set the start date of the simulation. */
      void setStartDate (const boost::gregorian::date& iStartDate) {
        _startDate = iStartDate;
      }

      /** Set the end date of the simulation. */
      void setEndDate (const boost::gregorian::date& iEndDate) {
        _endDate = iEndDate;
      }


    private:
      /** Get the type of the module (normally, COM). */
      ModuleDescription::EN_ModuleType getModuleType() const;

      /** Get the name of the module (normally, COM). */
      const std::string& getModuleName() const;

      
    private:
      /** Constructors. */
      ServiceContext ();
      ServiceContext (const ServiceContext&);
      ServiceContext (const ModuleDescription&);
      void init ();
      
      /** Destructor. */
      ~ServiceContext();

    private:
      // Desccription (mainly, type and name) of the module (normally, COM)
      ModuleDescription _moduleDescription;
      
      // Input filename
      std::string _inputFilename;

      // Number of simulations to be run
      int _simulationRunNumber;

      // Simulation length (time length) / date range for the simulation
      boost::gregorian::date _startDate;
      boost::gregorian::date _endDate;
    };

  }
}
#endif // __LATUS_COM_SVC_SERVICE_CONTEXT_HPP
