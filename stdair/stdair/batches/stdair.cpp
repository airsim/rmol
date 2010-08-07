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
#include <stdair/bom/BomSource.hpp>
#include <stdair/bom/BomList.hpp>
#include <stdair/factory/FacBomContent.hpp>
#include <stdair/service/Logger.hpp>
#include <stdair/config/stdair-paths.hpp>

// //////// Type definitions ///////
typedef std::vector<std::string> WordList_T;


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
    
    // Step 0.0: initialisation
    // Create the root of the Bom tree (i.e., a BomRoot object)
    stdair::BomRoot& lBomRoot =
      stdair::FacBomContent::instance().create<stdair::BomRoot>();
    
    // Step 0.1: Inventory level
    // Create an Inventory (BA)
    const stdair::AirlineCode_T lAirlineCode ("BA");
    stdair::InventoryKey_T lInventoryKey (lAirlineCode);

    stdair::Inventory& lInventory =
      stdair::FacBomContent::instance().create<stdair::Inventory>(lInventoryKey);
    stdair::FacBomContent::linkWithParent (lInventory, lBomRoot);

    // Display the inventory
    STDAIR_LOG_DEBUG ("Inventory: " << lInventory.toString());
    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA15/10-JUN-2010)
    const stdair::FlightNumber_T lFlightNumber = 15;
    const stdair::Date_T lDate (2010, 6, 10);
    stdair::FlightDateKey_T lFlightDateKey (lFlightNumber, lDate);

    stdair::FlightDate& lFlightDate = stdair::FacBomContent::
      instance().create<stdair::FlightDate> (lFlightDateKey);
    stdair::FacBomContent::linkWithParent (lFlightDate, lInventory);
    
    // Display the flight-date
    STDAIR_LOG_DEBUG ("FlightDate: " << lFlightDate.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (LHR-SYD)
    const stdair::AirportCode_T lLHR ("LHR");
    const stdair::AirportCode_T lSYD ("SYD");
    stdair::SegmentDateKey_T lSegmentDateKey (lLHR, lSYD);

    stdair::SegmentDate& lLHRSYDSegment =
      stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lSegmentDateKey);
    stdair::FacBomContent::linkWithParent (lLHRSYDSegment, lFlightDate);

    // Display the segment-date
    STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());


    // Create a second SegmentDate (LHR-BKK)
    const stdair::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = stdair::SegmentDateKey_T (lLHR, lBKK);

    stdair::SegmentDate& lLHRBKKSegment =
      stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lSegmentDateKey);
    stdair::FacBomContent::linkWithParent (lLHRBKKSegment, lFlightDate);

    // Display the segment-date
    STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


    // Create a third SegmentDate (BKK-SYD)
    lSegmentDateKey = stdair::SegmentDateKey_T (lBKK, lSYD);

    stdair::SegmentDate& lBKKSYDSegment =
      stdair::FacBomContent::
      instance().create<stdair::SegmentDate> (lSegmentDateKey);
    stdair::FacBomContent::linkWithParent (lBKKSYDSegment, lFlightDate);

    // Display the segment-date
    STDAIR_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment.toString());

    
    // Step 0.4: Leg-date level
    // Create a first LegDate (LHR)
    stdair::LegDateKey_T lLegDateKey (lLHR);

    stdair::LegDate& lLHRLeg =
      stdair::FacBomContent::instance().create<stdair::LegDate> (lLegDateKey);
    stdair::FacBomContent::linkWithParent<stdair::LegDate>(lLHRLeg, lFlightDate);

    // Display the leg-date
    STDAIR_LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
    // Create a second LegDate (BKK)
    lLegDateKey = stdair::LegDateKey_T (lBKK);

    stdair::LegDate& lBKKLeg =
      stdair::FacBomContent::instance().create<stdair::LegDate> (lLegDateKey);
    stdair::FacBomContent::linkWithParent (lBKKLeg, lFlightDate);

    // Display the leg-date
    STDAIR_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) of the Segment LHR-BKK;
    const stdair::CabinCode_T lY ("Y");
    stdair::SegmentCabinKey_T lYSegmentCabinKey (lY);

    stdair::SegmentCabin& lLHRBKKSegmentYCabin =
      stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lYSegmentCabinKey);
    stdair::FacBomContent::
      linkWithParent (lLHRBKKSegmentYCabin, lLHRBKKSegment);

    // Display the segment-cabin
    STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRBKKSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment BKK-SYD;
    stdair::SegmentCabin& lBKKSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lYSegmentCabinKey);
    stdair::FacBomContent::
      linkWithParent (lBKKSYDSegmentYCabin, lBKKSYDSegment);
     
    // Display the segment-cabin
    STDAIR_LOG_DEBUG ("SegmentCabin: " << lBKKSYDSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment LHR-SYD;
    stdair::SegmentCabin& lLHRSYDSegmentYCabin =
      stdair::FacBomContent::
      instance().create<stdair::SegmentCabin> (lYSegmentCabinKey);
    stdair::FacBomContent::
      linkWithParent (lLHRSYDSegmentYCabin, lLHRSYDSegment);
      
    // Display the segment-cabin
    STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRSYDSegmentYCabin.toString());

    
    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) of the Leg LHR-BKK;
    stdair::LegCabinKey_T lYLegCabinKey (lY);

    stdair::LegCabin& lLHRLegYCabin =
      stdair::FacBomContent::instance().create<stdair::LegCabin> (lYLegCabinKey);
    stdair::FacBomContent::linkWithParent (lLHRLegYCabin, lLHRLeg);

    // Display the leg-cabin
    STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Create a LegCabin (Y) of the Leg BKK-SYD;
    stdair::LegCabin& lBKKLegYCabin =
      stdair::FacBomContent::instance().create<stdair::LegCabin> (lYLegCabinKey);
    stdair::FacBomContent::linkWithParent (lBKKLegYCabin, lBKKLeg);

    // Display the leg-cabin
    STDAIR_LOG_DEBUG ("LegCabin: " << lBKKLegYCabin.toString());

    // Step 0.7: booking class level
    // Create a BookingClass (Q) of the Segment LHR-BKK, cabin Y;
    const stdair::ClassCode_T lQ ("Q");
    stdair::BookingClassKey_T lQBookingClassKey (lQ);

    stdair::BookingClass& lLHRBKKSegmentYCabinQClass =
      stdair::FacBomContent::
      instance().create<stdair::BookingClass> (lQBookingClassKey);
    stdair::FacBomContent::
      linkWithParent (lLHRBKKSegmentYCabinQClass, lLHRBKKSegmentYCabin);

    // Display the booking class
    STDAIR_LOG_DEBUG ("BookingClass: "
		      << lLHRBKKSegmentYCabinQClass.toString());

    // Browse the BomRoot and display the created objects.
    STDAIR_LOG_DEBUG ("Browse the BomRoot");
    
    const stdair::InventoryList_T& lInventoryList = lBomRoot.getInventoryList();
    for (stdair::InventoryList_T::iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory& lCurrentInventory = *itInv;
      STDAIR_LOG_DEBUG ("Inventory: " << lCurrentInventory.toString());
      
      const stdair::FlightDateMap_T& lFlightDateMap = 
        lCurrentInventory.getFlightDateMap ();
      for (stdair::FlightDateMap_T::iterator itFlightDate = 
             lFlightDateMap.begin();
           itFlightDate != lFlightDateMap.end(); ++itFlightDate) {
        const stdair::FlightDate* lCurrentFlightDate = itFlightDate->second;
        STDAIR_LOG_DEBUG ("FlightDate: " << lCurrentFlightDate->describeKey());
      }
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
