// STL
#include <cassert>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
// Boost Python
#include <boost/python.hpp>
// Boost Accumulators
#include <boost/accumulators/accumulators.hpp>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/config/rmol-paths.hpp>

// Aliases for namespaces
namespace ba = boost::accumulators;

// //////// Specific type definitions ///////
typedef unsigned int NbOfRuns_T;

// /////////////////////////////////////////////////////
namespace RMOL {

  /**
   * @brief Wrapper structure around the C++ API, so as to expose a Python API.
   */
  struct RMOLer {
  public:
    /**
     * Wrapper around the optimisation use case.
     */
    std::string rmol (const int& iRandomDraws, const short& iMethod,
                      const double& iCapacity) {
      std::ostringstream oStream;

      // Sanity check
      if (_logOutputStream == NULL) {
        oStream << "The log filepath is not valid." << std::endl;
        return oStream.str();
      }
      assert (_logOutputStream != NULL);
      
      try {

        // DEBUG
        *_logOutputStream << "Optimisation for " << iRandomDraws << " draws, "
                          << "capacity of " << iCapacity
                          << ", and with the following method: "
                          << iMethod << std::endl;
      
        if (_rmolService == NULL) {
          oStream << "The RMOL service has not been initialised, "
                  << "i.e., the init() method has not been called "
                  << "correctly on the RMOLer object. Please "
                  << "check that all the parameters are not empty and "
                  << "point to actual files.";
          *_logOutputStream << oStream.str();
          return oStream.str();
        }
        assert (_rmolService != NULL);

        switch (iMethod) {
        case 0: {
          // Calculate the optimal protections by the Monte Carlo
          // Integration approach
          _rmolService->optimize<OptimizationType::OPT_MC> (iRandomDraws);
          break;
        }
        case 1: {
          // Calculate the optimal protections by DP.
          _rmolService->optimize<OptimizationType::OPT_DP>();
          break;
        }
        case 2: {
          // Calculate the Bid-Price Vector by EMSR
          _rmolService->optimize<OptimizationType::HEUR_EMSR>();
          break;
        }
        case 3: {
          // Calculate the protections by EMSR-a
          _rmolService->optimize<OptimizationType::HEUR_EMSRA>();
          break;
        }
        case 4: {
          // Calculate the protections by EMSR-b
          _rmolService->optimize<OptimizationType::HEUR_EMSRB>();
          break;
        }
        default: {
          _rmolService->optimize<OptimizationType::OPT_MC> (iRandomDraws);
        }
        }
        
        // DEBUG
        *_logOutputStream << "End of the optimisation." << std::endl;

        // DEBUG
        *_logOutputStream << "RMOL output: "
                          << oStream.str() << std::endl;

      } catch (const stdair::RootException& eRMOLError) {
        oStream << "RMOL error: "  << eRMOLError.what() << std::endl;
        
      } catch (const std::exception& eStdError) {
        oStream << "Error: "  << eStdError.what() << std::endl;
        
      } catch (...) {
        oStream << "Unknown error" << std::endl;
      }

      //
      oStream << "RMOL has completed the generation of the booking "
              << "requests. See the log file for more details." << std::endl;

      return oStream.str();
    }

  public:
    /** Default constructor. */
    RMOLer() : _rmolService (NULL), _logOutputStream (NULL) {
    }
    
    /** Default copy constructor. */
    RMOLer (const RMOLer& iRMOLer)
      : _rmolService (iRMOLer._rmolService),
        _logOutputStream (iRMOLer._logOutputStream) {
    }

    /** Default constructor. */
    ~RMOLer() {
      _rmolService = NULL;
      _logOutputStream = NULL;
    }
    
    /**
     * Wrapper around the search use case.
     */
    bool init (const std::string& iLogFilepath,
               const short& iCapacity, const bool isBuiltin,
               const stdair::Filename_T& iInputFilename) {
      bool isEverythingOK = true;

      try {
        
        // Check that the file path given as input corresponds to an actual file
        const bool isWriteable = (iLogFilepath.empty() == false);
        // stdair::BasFileMgr::isWriteable (iLogFilepath);
        if (isWriteable == false) {
          isEverythingOK = false;
          return isEverythingOK;
        }
        
        // Set the log parameters
        _logOutputStream = new std::ofstream;
        assert (_logOutputStream != NULL);
        
        // Open and clean the log outputfile
        _logOutputStream->open (iLogFilepath.c_str());
        _logOutputStream->clear();
        
        // DEBUG
        *_logOutputStream << "Python wrapper initialisation" << std::endl;
        const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG,
                                               *_logOutputStream);
        
        // Initialise the context
        _rmolService = new RMOL_Service (lLogParams);
        assert (_rmolService != NULL);

        // Check wether or not a (CSV) input file should be read
        if (isBuiltin == true) {
          // Create sample BOM objects
          _rmolService->buildSampleBom();

        } else {
          // Create the RMOL objects from the input CSV file
          _rmolService->parseAndLoad (iCapacity, iInputFilename);
        }

        // DEBUG
        *_logOutputStream << "Python wrapper initialised" << std::endl;
        
      } catch (const stdair::RootException& eRMOLError) {
        *_logOutputStream << "RMOL error: "  << eRMOLError.what()
                          << std::endl;
        
      } catch (const std::exception& eStdError) {
        *_logOutputStream << "Error: "  << eStdError.what() << std::endl;
        
      } catch (...) {
        *_logOutputStream << "Unknown error" << std::endl;
      }
      
      return isEverythingOK;
    }

  private:
    /** Handle on the RMOL services (API). */
    RMOL_Service* _rmolService;
    std::ofstream* _logOutputStream;
  };

}

// /////////////////////////////////////////////////////////////
BOOST_PYTHON_MODULE(pyrmol) {
  boost::python::class_<RMOL::RMOLer> ("RMOLer")
    .def ("rmol", &RMOL::RMOLer::rmol)
    .def ("init", &RMOL::RMOLer::init);
}
