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
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/FlightDateTypes.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegDateTypes.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/LegCabinTypes.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
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

/** Early return status (so that it can be differentiated from an
    error). */
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

    // ///////////// Step 0.0: Initialisation ////////////
    // Create the root of the Bom tree (i.e., a BomRoot object)
    stdair::BomRoot& lBomRoot =
      stdair::FacBom<stdair::BomRoot>::instance().create();

    // Step 0.1: Inventory level
    // Create an Inventory for BA
    const stdair::InventoryKey lBAKey ("BA");
    stdair::Inventory& lBAInv =
      stdair::FacBom<stdair::Inventory>::instance().create (lBAKey);
    stdair::FacBomManager::addToList (lBomRoot, lBAInv);

    // Create an Inventory for AF
    const stdair::InventoryKey lAFKey ("AF");
    stdair::Inventory& lAFInv =
      stdair::FacBom<stdair::Inventory>::instance().create (lAFKey);
    stdair::FacBomManager::addToList (lBomRoot, lAFInv);

    // ////// BA ///////    
    // Step 0.2: Flight-date level
    // Create a FlightDate (BA15/10-JUN-2010) for BA's Inventory
    stdair::FlightNumber_T lFlightNumber = 15;
    stdair::Date_T lDate (2010, 6, 10);
    stdair::FlightDateKey lFlightDateKey (lFlightNumber, lDate);

    stdair::FlightDate& lBA15_20100610_FD =
      stdair::FacBom<stdair::FlightDate>::instance().create (lFlightDateKey);
    stdair::FacBomManager::addToList (lBAInv, lBA15_20100610_FD);
    
    // Display the flight-date
    // STDAIR_LOG_DEBUG ("FlightDate: " << lBA15_20100610_FD.toString());
    
    // Step 0.3: Segment-date level
    // Create a first SegmentDate (LHR-SYD) for BA's Inventory
    const stdair::AirportCode_T lLHR ("LHR");
    const stdair::AirportCode_T lSYD ("SYD");
    stdair::SegmentDateKey lSegmentDateKey (lLHR, lSYD);

    stdair::SegmentDate& lLHRSYDSegment =
      stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
    stdair::FacBomManager::addToList (lBA15_20100610_FD, lLHRSYDSegment);

    // Display the segment-date
    // STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRSYDSegment.toString());

    // Create a second SegmentDate (LHR-BKK) for BA's Inventory
    const stdair::AirportCode_T lBKK ("BKK");
    lSegmentDateKey = stdair::SegmentDateKey (lLHR, lBKK);

    stdair::SegmentDate& lLHRBKKSegment =
      stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
    stdair::FacBomManager::addToList (lBA15_20100610_FD, lLHRBKKSegment);

    // Display the segment-date
    // STDAIR_LOG_DEBUG ("SegmentDate: " << lLHRBKKSegment.toString());


    // Create a third SegmentDate (BKK-SYD) for BA's Inventory
    lSegmentDateKey = stdair::SegmentDateKey (lBKK, lSYD);

    stdair::SegmentDate& lBKKSYDSegment =
      stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
    stdair::FacBomManager::addToList (lBA15_20100610_FD, lBKKSYDSegment);

    // Display the segment-date
    // STDAIR_LOG_DEBUG ("SegmentDate: " << lBKKSYDSegment.toString());

    // Step 0.4: Leg-date level
    // Create a first LegDate (LHR) for BA's Inventory
    stdair::LegDateKey lLegDateKey (lLHR);

    stdair::LegDate& lLHRLeg =
      stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
    stdair::FacBomManager::addToList (lBA15_20100610_FD, lLHRLeg);

    // Display the leg-date
    // STDAIR_LOG_DEBUG ("LegDate: " << lLHRLeg.toString());
    
    // Create a second LegDate (BKK)
    lLegDateKey = stdair::LegDateKey (lBKK);

    stdair::LegDate& lBKKLeg =
      stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
    stdair::FacBomManager::addToList (lBA15_20100610_FD, lBKKLeg);

    // Display the leg-date
    // STDAIR_LOG_DEBUG ("LegDate: " << lBKKLeg.toString());

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) for the Segment LHR-BKK of BA's Inventory
    const stdair::CabinCode_T lY ("Y");
    stdair::SegmentCabinKey lYSegmentCabinKey (lY);

    stdair::SegmentCabin& lLHRBKKSegmentYCabin =
      stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
    stdair::FacBomManager::addToList (lLHRBKKSegment, lLHRBKKSegmentYCabin);

    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRBKKSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment BKK-SYD;
    stdair::SegmentCabin& lBKKSYDSegmentYCabin =
      stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
    stdair::FacBomManager::addToList (lBKKSYDSegment, lBKKSYDSegmentYCabin);
     
    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lBKKSYDSegmentYCabin.toString());

    // Create a SegmentCabin (Y) of the Segment LHR-SYD;
    stdair::SegmentCabin& lLHRSYDSegmentYCabin =
      stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
    stdair::FacBomManager::addToList (lLHRSYDSegment, lLHRSYDSegmentYCabin);
      
    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lLHRSYDSegmentYCabin.toString());

    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) for the Leg LHR-BKK on BA's Inventory
    stdair::LegCabinKey lYLegCabinKey (lY);

    stdair::LegCabin& lLHRLegYCabin =
      stdair::FacBom<stdair::LegCabin>::instance().create (lYLegCabinKey);
    stdair::FacBomManager::addToList (lLHRLeg, lLHRLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Create a LegCabin (Y) for the Leg BKK-SYD
    stdair::LegCabin& lBKKLegYCabin =
      stdair::FacBom<stdair::LegCabin>::instance().create (lYLegCabinKey);
    stdair::FacBomManager::addToList (lBKKLeg, lBKKLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lBKKLegYCabin.toString());

    // Step 0.7: booking class level
    // Create a BookingClass (Q) for the Segment LHR-BKK, cabin Y on BA's Inv
    const stdair::ClassCode_T lQ ("Q");
    stdair::BookingClassKey lQBookingClassKey (lQ);

    stdair::BookingClass& lLHRBKKSegmentYCabinQClass =
      stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
    stdair::FacBomManager::addToList (lLHRBKKSegmentYCabin,
                                      lLHRBKKSegmentYCabinQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lLHRBKKSegmentYCabinQClass.toString());

    // Create a BookingClass (Q) for the Segment BKK-LHR, cabin Y
    stdair::BookingClass& lBKKSYDSegmentYCabinQClass =
      stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
    stdair::FacBomManager::addToList (lBKKSYDSegmentYCabin,
                                      lBKKSYDSegmentYCabinQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lLHRBKKSegmentYCabinQClass.toString());

    // Create a BookingClass (Q) for the Segment LHR-SYD, cabin Y
    stdair::BookingClass& lLHRSYDSegmentYCabinQClass =
      stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
    stdair::FacBomManager::addToList (lLHRSYDSegmentYCabin,
                                      lLHRSYDSegmentYCabinQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lLHRBKKSegmentYCabinQClass.toString());

    
    // ////// AF ///////    
    // Step 0.2: Flight-date level
    // Create a FlightDate (AF102/20-MAR-2010) for AF's Inventory
    lFlightNumber = 102;
    lDate = stdair::Date_T (2010, 3, 20);
    lFlightDateKey = stdair::FlightDateKey (lFlightNumber, lDate);

    stdair::FlightDate& lAF102_20100320_FD =
      stdair::FacBom<stdair::FlightDate>::instance().create (lFlightDateKey);
    stdair::FacBomManager::addToList (lAFInv, lAF102_20100320_FD);
    
    // Display the flight-date
    // STDAIR_LOG_DEBUG ("FlightDate: " << lAF102_20100320_FD.toString());

    // Step 0.3: Segment-date level
    // Create a SegmentDate (CDG-SFO) for AF's Inventory
    const stdair::AirportCode_T lCDG ("CDG");
    const stdair::AirportCode_T lSFO ("SFO");
    lSegmentDateKey = stdair::SegmentDateKey (lCDG, lSFO);

    stdair::SegmentDate& lCDGSFOSegment =
      stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
    stdair::FacBomManager::addToList (lAF102_20100320_FD, lCDGSFOSegment);

    // Display the segment-date
    // STDAIR_LOG_DEBUG ("SegmentDate: " << lCDGSFOSegment.toString());

    // Step 0.4: Leg-date level
    // Create a LegDate (CDG) for AF's Inventory
    lLegDateKey = stdair::LegDateKey (lCDG);

    stdair::LegDate& lCDGLeg =
      stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
    stdair::FacBomManager::addToList (lAF102_20100320_FD, lCDGLeg);

    // Display the leg-date
    // STDAIR_LOG_DEBUG ("LegDate: " << lCDGLeg.toString());

    // Step 0.5: segment-cabin level
    // Create a SegmentCabin (Y) for the Segment CDG-SFO of AF's Inventory
    stdair::SegmentCabin& lCDGSFOSegmentYCabin =
      stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
    stdair::FacBomManager::addToList (lCDGSFOSegment, lCDGSFOSegmentYCabin);

    // Display the segment-cabin
    // STDAIR_LOG_DEBUG ("SegmentCabin: " << lCDGSFOSegmentYCabin.toString());

    // Step 0.6: leg-cabin level
    // Create a LegCabin (Y) for the Leg CDG-SFO on AF's Inventory
    stdair::LegCabin& lCDGLegYCabin =
      stdair::FacBom<stdair::LegCabin>::instance().create (lYLegCabinKey);
    stdair::FacBomManager::addToList (lCDGLeg, lCDGLegYCabin);

    // Display the leg-cabin
    // STDAIR_LOG_DEBUG ("LegCabin: " << lLHRLegYCabin.toString());

    // Step 0.7: booking class level
    // Create a BookingClass (Q) for the Segment CDG-SFO, cabin Y on AF's Inv
    stdair::BookingClass& lCDGSFOSegmentYCabinQClass =
      stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
    stdair::FacBomManager::addToList (lCDGSFOSegmentYCabin,
                                      lCDGSFOSegmentYCabinQClass);

    // Display the booking class
    // STDAIR_LOG_DEBUG ("BookingClass: "
    //                   << lCDGSFOSegmentYCabinQClass.toString());

    
    // /////////// Step 1.0: Display the BOM tree //////////
    // 1.1. Inventory level
    const stdair::InventoryList_T& lInventoryList =
      stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
    for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
         itInv != lInventoryList.end(); ++itInv) {
      const stdair::Inventory* lInv_ptr = *itInv;
      assert (lInv_ptr != NULL);

      // STDAIR_LOG_DEBUG ("Inventory: " << lInv_ptr->describeKey());
      STDAIR_LOG_DEBUG (lInv_ptr->describeKey());

      // 1.2. FlightDate level
      const stdair::FlightDateList_T& lFlightDateList =
        stdair::BomManager::getList<stdair::FlightDate> (*lInv_ptr);
      for (stdair::FlightDateList_T::const_iterator itFD=lFlightDateList.begin();
         itFD != lFlightDateList.end(); ++itFD) {
        const stdair::FlightDate* lFD_ptr = *itFD;
        assert (lFD_ptr != NULL);

        // STDAIR_LOG_DEBUG ("FlightDate: " << lFD_ptr->toString());
        STDAIR_LOG_DEBUG ("  " << lFD_ptr->toString());

        // 1.4. LegDate level
        const stdair::LegDateList_T& lLegDateList =
          stdair::BomManager::getList<stdair::LegDate> (*lFD_ptr);
        for (stdair::LegDateList_T::const_iterator itLD =
               lLegDateList.begin();
             itLD != lLegDateList.end(); ++itLD) {
          const stdair::LegDate* lLD_ptr = *itLD;
          assert (lFD_ptr != NULL);
          
          // STDAIR_LOG_DEBUG ("LegDate: " << lLD_ptr->toString());
          STDAIR_LOG_DEBUG ("    " << lLD_ptr->toString());

          // 1.6. LegCabin level
          const stdair::LegCabinList_T& lLegCabinList =
            stdair::BomManager::getList<stdair::LegCabin> (*lLD_ptr);
          for (stdair::LegCabinList_T::const_iterator itLC =
                 lLegCabinList.begin();
               itLC != lLegCabinList.end(); ++itLC) {
            const stdair::LegCabin* lLC_ptr = *itLC;
            assert (lFD_ptr != NULL);
            
            // STDAIR_LOG_DEBUG ("LegCabin: " << lLC_ptr->toString());
            STDAIR_LOG_DEBUG ("    " << lLC_ptr->toString());
          }
        }

        // 1.3. SegmentDate level
        const stdair::SegmentDateList_T& lSegmentDateList =
          stdair::BomManager::getList<stdair::SegmentDate> (*lFD_ptr);
        for (stdair::SegmentDateList_T::const_iterator itSD =
               lSegmentDateList.begin();
             itSD != lSegmentDateList.end(); ++itSD) {
          const stdair::SegmentDate* lSD_ptr = *itSD;
          assert (lFD_ptr != NULL);
          
          // STDAIR_LOG_DEBUG ("SegmentDate: " << lSD_ptr->toString());
          STDAIR_LOG_DEBUG ("    " << lSD_ptr->toString());

          // 1.5. SegmentCabin level
          const stdair::SegmentCabinList_T& lSegmentCabinList =
            stdair::BomManager::getList<stdair::SegmentCabin> (*lSD_ptr);
          for (stdair::SegmentCabinList_T::const_iterator itSC =
                 lSegmentCabinList.begin();
               itSC != lSegmentCabinList.end(); ++itSC) {
            const stdair::SegmentCabin* lSC_ptr = *itSC;
            assert (lFD_ptr != NULL);
            
            // STDAIR_LOG_DEBUG ("SegmentCabin: " << lSC_ptr->toString());
            STDAIR_LOG_DEBUG ("    " << lSC_ptr->toString());

            // 1.7. BookingClass level
            const stdair::BookingClassList_T& lBookingClassList =
              stdair::BomManager::getList<stdair::BookingClass> (*lSC_ptr);
            for (stdair::BookingClassList_T::const_iterator itBC =
                   lBookingClassList.begin();
                 itBC != lBookingClassList.end(); ++itBC) {
              const stdair::BookingClass* lBC_ptr = *itBC;
              assert (lFD_ptr != NULL);
              
              // STDAIR_LOG_DEBUG ("BookingClass: " << lBC_ptr->toString());
              STDAIR_LOG_DEBUG ("    " << lBC_ptr->toString());
            }
          }
        }
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
