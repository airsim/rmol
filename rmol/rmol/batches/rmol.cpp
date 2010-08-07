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
// StdAir
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/RMOL_Service.hpp>
#include <rmol/config/rmol-paths.hpp>


// //////// Constants //////
/** Default name and location for the log file. */
const std::string K_RMOL_DEFAULT_LOG_FILENAME ("rmol.log");

/** Default for the input type. It can be either built-in or provided by an
    input file. That latter must then be given with the -i/--input option. */
const bool K_RMOL_DEFAULT_BUILT_IN_INPUT = false;

/** Default name and location for the (CSV) input file. */
const std::string K_RMOL_DEFAULT_INPUT_FILENAME ("../../test/samples/rm01.csv");

/** Default number of random draws to be generated (best if over 100). */
const int K_RMOL_DEFAULT_RANDOM_DRAWS = 100000;

/** Default value for the capacity of the resource (e.g., a flight cabin). */
const double K_RMOL_DEFAULT_CAPACITY = 500.0;

/** Default probability that a demand group buys the next higher fare products 
when the products which they came for are not available. */
// const std::vector<double> K_RMOL_DEFAULT_SELLUP_PROBABILITY;

/** Default name and location for the Revenue Management method to be used.
    <br>
    <ul>
      <li>0 = Monte-Carlo</li>
      <li>1 = Dynamic Programming</li> 
      <li>2 = EMSR</li>
      <li>3 = EMSR-a</li>
      <li>4 = EMSR-b</li>
      <li>5 = EMSR-a with sell up</li>
    </ul> */
const short K_RMOL_DEFAULT_METHOD = 0;

/** Fill a vector of default sell-up probability values. */
void initDefaultValuesForSellupProbabilityVector (RMOL::SellupProbabilityVector_T& ioSellUpProbabilityVector) {
  // Add default values only when the given vector is empty
  if (ioSellUpProbabilityVector.empty() == true) {
    ioSellUpProbabilityVector.push_back (0.2);
  }
}


// ///////// Parsing of Options & Configuration /////////
// A helper function to simplify the main part.
template<class T> std::ostream& operator<< (std::ostream& os,
                                            const std::vector<T>& v) {
  std::copy (v.begin(), v.end(), std::ostream_iterator<T> (std::cout, " ")); 
  return os;
}

/** Early return status (so that it can be differentiated from an error). */
const int K_RMOL_EARLY_RETURN_STATUS = 99;

/** Read and parse the command line options. */
int readConfiguration(int argc, char* argv[], 
                      int& ioRandomDraws, double& ioCapacity, 
                      RMOL::SellupProbabilityVector_T& ioSellupProbabilityVector,
                      short& ioMethod, bool& ioIsBuiltin,
                      std::string& ioInputFilename, std::string& ioLogFilename){

  // Default for the built-in input
  ioIsBuiltin = K_RMOL_DEFAULT_BUILT_IN_INPUT;
  
  // Initialise the sell-up probability vector with default values
  initDefaultValuesForSellupProbabilityVector (ioSellupProbabilityVector);
    
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
    ("draws,d",
     boost::program_options::value<int>(&ioRandomDraws)->default_value(K_RMOL_DEFAULT_RANDOM_DRAWS), 
     "Number of to-be-generated random draws")
    ("capacity,c",
     boost::program_options::value<double>(&ioCapacity)->default_value(K_RMOL_DEFAULT_CAPACITY), 
     "Resource capacity (e.g., for a flight leg)")
    ("sellup,s",
     boost::program_options::value< std::vector<double> >(&ioSellupProbabilityVector)->multitoken(),
     "Sell-up proability vector (e.g. j-th element implies the sell up probability of class j+1 to class j where class 1 yields the highest value")
    ("method,m",
     boost::program_options::value<short>(&ioMethod)->default_value(K_RMOL_DEFAULT_METHOD), 
     "Revenue Management method to be used (0 = Monte-Carlo, 1 = Dynamic Programming, 2 = EMSR, 3 = EMSR-a, 4 = EMSR-b, 5 = EMSR-a with sell up probability)")
    ("builtin,b",
     "The cabin set up can be either built-in or parsed from an input file. That latter must then be given with the -i/--input option")
    ("input,i",
     boost::program_options::value< std::string >(&ioInputFilename)->default_value(K_RMOL_DEFAULT_INPUT_FILENAME),
     "(CVS) input file for the demand distributions")
    ("log,l",
     boost::program_options::value< std::string >(&ioLogFilename)->default_value(K_RMOL_DEFAULT_LOG_FILENAME),
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

  std::ifstream ifs ("rmol.cfg");
  boost::program_options::store (parse_config_file (ifs, config_file_options),
                                 vm);
  boost::program_options::notify (vm);
    
  if (vm.count ("help")) {
    std::cout << visible << std::endl;
    return K_RMOL_EARLY_RETURN_STATUS;
  }

  if (vm.count ("version")) {
    std::cout << PACKAGE_NAME << ", version " << PACKAGE_VERSION << std::endl;
    return K_RMOL_EARLY_RETURN_STATUS;
  }

  if (vm.count ("prefix")) {
    std::cout << "Installation prefix: " << PREFIXDIR << std::endl;
    return K_RMOL_EARLY_RETURN_STATUS;
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

  std::cout << "The number of random draws is: " << ioRandomDraws << std::endl;
  std::cout << "The resource capacity is: " << ioCapacity << std::endl;
  std::cout << "The Revenue Management method is: " << ioMethod << std::endl;
  std::cout << "The sell-up probability vector is: " << std::endl;
  unsigned short idx = 0;
  for (RMOL::SellupProbabilityVector_T::const_iterator itValue =
         ioSellupProbabilityVector.begin();
       itValue != ioSellupProbabilityVector.end(); ++itValue, ++idx) {
    std::cout << "[" << idx << "] " << *itValue << "; ";
  }
  std::cout << std::endl;
  
  return 0;
}


// ///////// M A I N ////////////
int main (int argc, char* argv[]) {
  try {
    
    // Number of random draws to be generated (best if greater than 100)
    int lRandomDraws = 0;
    
    // Cabin Capacity (it must be greater then 100 here)
    double lCapacity = 0.0;

    /** Default probability that a demand group buys the next higher
        fare products when the products which they came for are not
        available. */
    RMOL::SellupProbabilityVector_T lSellupProbabilityVector;
    // lSellupProbabilityVector.push_back (0.2);

    // Methods of optimisation (0 = Monte-Carlo, 1 = Dynamic Programming, 
    // 2 = EMSR, 3 = EMSR-a, 4 = EMSR-b, 5 = EMSR-a with sell up probability)
    short lMethod = 0;   
    
    // Built-in
    bool isBuiltin;
    
    // Input file name
    std::string lInputFilename;

    // Output log File
    std::string lLogFilename;

    // Call the command-line option parser
    const int lOptionParserStatus = 
      readConfiguration (argc, argv, lRandomDraws, lCapacity,
                         lSellupProbabilityVector, lMethod,
                         isBuiltin, lInputFilename, lLogFilename);

    if (lOptionParserStatus == K_RMOL_EARLY_RETURN_STATUS) {
      return 0;
    }

    // Set the log parameters
    std::ofstream logOutputFile;
    // Open and clean the log outputfile
    logOutputFile.open (lLogFilename.c_str());
    logOutputFile.clear();
    
    // Initialise the list of classes/buckets
    const stdair::BasLogParams lLogParams (stdair::LOG::DEBUG, logOutputFile);
    const stdair::AirlineCode_T lAirlineCode ("BA");
    RMOL::RMOL_Service rmolService (lLogParams, lAirlineCode, lCapacity);
    rmolService.setUpStudyStatManager();
    
    if (isBuiltin == true) {
      // No input file has been provided. So, process a sample.

      // DEBUG
      STDAIR_LOG_DEBUG ("rmol will build the BOM tree from built-in specifications.");
      
      // STEP 0.
      // List of demand distribution parameters (mean and standard deviation)
      
      // Class/bucket 1: p1 = 110, N (15, 9)
      rmolService.addBucket (110.0, 15, 9);
      
      // Class/bucket 2: p2 = 75, N (40, 12)
      rmolService.addBucket (75.0, 40, 12);
      
      // Class/bucket 3: p3 = 48, no need to define a demand distribution
      //                 (it can be considered very big)
      rmolService.addBucket (48.0, 0, 0);
      
    } else {
      // DEBUG
      STDAIR_LOG_DEBUG ("rmol will parse " << lInputFilename
                        << " and build the corresponding BOM tree.");
      
      // Parse the input file
      rmolService.readFromInputFile (lInputFilename);
    }
    
    switch (lMethod) {
    case 0: {
      // Calculate the optimal protections by the Monte Carlo
      // Integration approach
      rmolService.optimalOptimisationByMCIntegration (lRandomDraws);
      break;
    }
    case 1: {
      // Calculate the optimal protections by DP.
      rmolService.optimalOptimisationByDP ();
      break;
    }
    case 2: {
      // Calculate the Bid-Price Vector by EMSR
      rmolService.heuristicOptimisationByEmsr ();
      break;
    }
    case 3: {
      // Calculate the protections by EMSR-a
      rmolService.heuristicOptimisationByEmsrA ();
      break;
    }
    case 4: {
      // Calculate the protections by EMSR-b
      rmolService.heuristicOptimisationByEmsrB ();
      break;
    }
    case 5: {
      // Calculate the protections by EMSR-a with sell up probability
      rmolService.heuristicOptimisationByEmsrAwithSellup 
        (lSellupProbabilityVector);
      break;
    }
    case 6: {
      // Calculate the optimal protections by the Monte Carlo
      // Integration approach
      rmolService.buildContextForMC (lRandomDraws);
      rmolService.legOptimisationByMC ();
      break;
    }
    default: {
      rmolService.optimalOptimisationByMCIntegration (lRandomDraws);
    }
    }
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;	
}
