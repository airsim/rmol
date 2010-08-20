// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/STDAIR_Service.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/factory/FacBomManager.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/config/stdair-paths.hpp>

// //////// Constants //////
/** Default name and location for the log file. */
const std::string K_STDAIR_DEFAULT_LOG_FILENAME ("stdair.log");

/** Default name and location for the (CSV) input file. */
const std::string K_STDAIR_DEFAULT_INPUT_FILENAME ("../../test/samples/stdair01.csv");

/** Default for the input type. It can be either built-in or provided by an
    input file. That latter must then be given with the -i option. */
const bool K_STDAIR_DEFAULT_BUILT_IN_INPUT = false;

/** Early return status (so that it can be differentiated from an error). */
const int K_STDAIR_EARLY_RETURN_STATUS = 99;

// ///////// Parsing of Options & Configuration /////////
// A helper function to simplify the main part.
template<class T> std::ostream& operator<< (std::ostream& os,
                                            const std::vector<T>& v) {
  std::copy (v.begin(), v.end(), std::ostream_iterator<T> (std::cout, " ")); 
  return os;
}

/** Read and parse the command line options. */
int readConfiguration (int argc, char* argv[], bool& ioIsBuiltin,
                       stdair::Filename_T& ioInputFilename,
                       std::string& ioLogFilename) {
  // Default for the built-in input
  ioIsBuiltin = K_STDAIR_DEFAULT_BUILT_IN_INPUT;
  
  // Declare a group of options that will be allowed only on command line
  boost::program_options::options_description generic ("Generic options");
  generic.add_options()
    ("prefix", "print installation prefix")
    ("version,v", "print version string")
    ("help,h", "produce help message");
    
  // Declare a group of options that will be allowed both on command
  // line and in config file
  boost::program_options::options_description config ("Configuration");
  config.add_options()
    ("builtin,b",
     "The sample BOM tree can be either built-in or parsed from an input file. That latter must then be given with the -i/--input option")
    ("input,i",
     boost::program_options::value< std::string >(&ioInputFilename)->default_value(K_STDAIR_DEFAULT_INPUT_FILENAME),
     "(CVS) input file for the demand distributions")
    ("log,l",
     boost::program_options::value< std::string >(&ioLogFilename)->default_value(K_STDAIR_DEFAULT_LOG_FILENAME),
     "Filename for the logs")
    ;

  // Hidden options, will be allowed both on command line and
  // in config file, but will not be shown to the user.
  boost::program_options::options_description hidden ("Hidden options");
  hidden.add_options()
    ("copyright",
     boost::program_options::value< std::vector<std::string> >(),
     "Show the copyright (license)");
        
  boost::program_options::options_description cmdline_options;
  cmdline_options.add(generic).add(config).add(hidden);

  boost::program_options::options_description config_file_options;
  config_file_options.add(config).add(hidden);
  boost::program_options::options_description visible ("Allowed options");
  visible.add(generic).add(config);
        
  boost::program_options::positional_options_description p;
  p.add ("copyright", -1);
        
  boost::program_options::variables_map vm;
  boost::program_options::
    store (boost::program_options::command_line_parser (argc, argv).
           options (cmdline_options).positional(p).run(), vm);

  std::ifstream ifs ("stdair.cfg");
  boost::program_options::store (parse_config_file (ifs, config_file_options),
                                 vm);
  boost::program_options::notify (vm);
    
  if (vm.count ("help")) {
    std::cout << visible << std::endl;
    return K_STDAIR_EARLY_RETURN_STATUS;
  }

  if (vm.count ("version")) {
    std::cout << PACKAGE_NAME << ", version " << PACKAGE_VERSION << std::endl;
    return K_STDAIR_EARLY_RETURN_STATUS;
  }

  if (vm.count ("prefix")) {
    std::cout << "Installation prefix: " << PREFIXDIR << std::endl;
    return K_STDAIR_EARLY_RETURN_STATUS;
  }

  if (vm.count ("builtin")) {
    ioIsBuiltin = true;
  }
  const std::string isBuiltinStr = (ioIsBuiltin == true)?"yes":"no";
  std::cout << "The BOM should be built-in? " << isBuiltinStr << std::endl;

  if (ioIsBuiltin == false) {
    if (vm.count ("input")) {
      ioInputFilename = vm["input"].as< std::string >();
      std::cout << "Input filename is: " << ioInputFilename << std::endl;
    }
  }

  if (vm.count ("log")) {
    ioLogFilename = vm["log"].as< std::string >();
    std::cout << "Log filename is: " << ioLogFilename << std::endl;
  }

  return 0;
}

// //////////////////////////////////////////////////////////////////////
void buildSampleBom() {

  try {

    // DEBUG
    STDAIR_LOG_DEBUG ("StdAir will build the BOM tree from built-in specifications.");

    // Create the bom root.
    stdair::BomRoot& lBomRoot =
      stdair::FacBom<stdair::BomRoot>::instance().create();

    // Create the inventories.
    stdair::InventoryKey lBAKey ("BA");
    stdair::Inventory& lBAInv =
      stdair::FacBom<stdair::Inventory>::instance().create (lBAKey);
    stdair::FacBomManager::addToList (lBomRoot, lBAInv);
    stdair::InventoryKey lAFKey ("AF");
    stdair::Inventory& lAFInv =
      stdair::FacBom<stdair::Inventory>::instance().create (lAFKey);
    stdair::FacBomManager::addToList (lBomRoot, lAFInv);

    // Display the BOM root.
    const stdair::InventoryList_T& lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory* lInv_ptr = *itInv;
      assert (lInv_ptr != NULL);
      STDAIR_LOG_DEBUG (lInv_ptr->describeKey());
    }

  } catch (const std::exception& stde) {
    STDAIR_LOG_ERROR ("Standard exception: " << stde.what());
  }
}

// ///////// M A I N ////////////
int main (int argc, char* argv[]) {

  try {
    
    // Built-in
    bool isBuiltin;
    
    // Input file name
    stdair::Filename_T lInputFilename;

    // Output log File
    std::string lLogFilename;
    
    // Call the command-line option parser
    const int lOptionParserStatus =
      readConfiguration (argc, argv, isBuiltin, lInputFilename, lLogFilename);

    if (lOptionParserStatus == K_STDAIR_EARLY_RETURN_STATUS) {
      return 0;
    }

    // Set the log parameters
    std::ofstream logOutputFile;
    // Open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();

    const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
    stdair::STDAIR_Service stdairService (lLogParams);

    // DEBUG
    STDAIR_LOG_DEBUG ("Welcome to stdair");

    // Check wether or not a (CSV) input file should be read
    if (isBuiltin == true) {
      // Build a sample BOM tree
      buildSampleBom();
      
    } else {
      // Read the input file
      //stdairService.readFromInputFile (lInputFilename);

      // DEBUG
      STDAIR_LOG_DEBUG ("StdAir will parse " << lInputFilename
                        << " and build the corresponding BOM tree.");
    }

    // Close the Log outputFile
    logOutputFile.close();

  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
