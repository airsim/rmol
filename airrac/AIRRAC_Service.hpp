#ifndef __AIRRAC_SVC_AIRRAC_SERVICE_HPP
#define __AIRRAC_SVC_AIRRAC_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_service_types.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>
// AirRAC
#include <airrac/AIRRAC_Types.hpp>

// Forward declarations.
namespace stdair {
  struct BasLogParams;
  struct BasDBParams;
}

namespace AIRRAC {

  /// Forward declaration
  class AIRRAC_ServiceContext;

  /**
   * @brief Interface for the AIRRAC Services.
   */
  class AIRRAC_Service {  
  public:
    // ////////////////// Constructors and Destructors //////////////////

    /**
     * Constructor.
     *
     * The initAirracService() method is called; see the corresponding
     * documentation for more details.
     *
     * A reference on an output stream is given, so that log outputs
     * can be directed onto that stream.
     *
     * @param const stdair::BasLogParams& Parameters for the output log stream.
     */
    AIRRAC_Service (const stdair::BasLogParams&);
    
    /**
     * Constructor.
     *
     * The initAirracService() method is called; see the corresponding
     * documentation for more details.
     *
     * A reference on an output stream is given, so that log outputs
     * can be directed onto that stream.
     *
     * @param const stdair::BasLogParams& Parameters for the output log stream.
     * @param const stdair::BasDBParams& Parameters for the database access.
     */
    AIRRAC_Service (const stdair::BasLogParams&, const stdair::BasDBParams&);
    
    /**
     * Constructor.
     *
     * The initAirracService() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, as no reference on any output stream is given,
     * it is assumed that the StdAir log service has already been
     * initialised with the proper log output stream by some other
     * methods in the calling chain (for instance, when the AIRRAC_Service
     * is itself being initialised by another library service such as
     * SIMCRS_Service).
     *
     * @param stdair::STDAIR_ServicePtr_T Reference on the STDAIR service.
     */
    AIRRAC_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr);

    /**
     * Constructor.
     *
     * The initAirracService() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, a reference on an output stream is given, so that log
     * outputs can be directed onto that stream.
     *
     * @param const stdair::BasLogParams& Parameters for the output log stream.
     * @param const stdair::Filename_T& Filename of the input yield file.
     */
    AIRRAC_Service (const stdair::BasLogParams&,
                    const stdair::Filename_T& iYieldInputFilename);

    /**
     * Constructor.
     *
     * The initAirracService() method is called; see the corresponding
     * documentation for more details.
     *
     * A reference on an output stream is given, so that log outputs
     * can be directed onto that stream.
     *
     * Moreover, database connection parameters are given, so that a
     * session can be created on the corresponding database.
     *
     * @param const stdair::BasLogParams& Parameters for the output log stream.
     * @param const stdair::BasDBParams& Parameters for the database access.
     * @param const stdair::Filename_T& Filename of the input yield file.
     */
    AIRRAC_Service (const stdair::BasLogParams&, const stdair::BasDBParams&,
                    const stdair::Filename_T& iYieldInputFilename);

    /**
     * Constructor.
     *
     * The initAirracService() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, as no reference on any output stream is given,
     * it is assumed that the StdAir log service has already been
     * initialised with the proper log output stream by some other
     * methods in the calling chain (for instance, when the AIRRAC_Service
     * is itself being initialised by another library service such as
     * SIMCRS_Service).
     *
     * @param stdair::STDAIR_ServicePtr_T Reference on the STDAIR service.
     * @param const stdair::Filename_T& Filename of the input yield file.
     */
    AIRRAC_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr,
                    const stdair::Filename_T& iYieldInputFilename);

    /**
     * Parse the yield input file, and load them into memory.
     *
     * The CSV files, describing the airline schedule and the O&Ds for
     * the simulator, are parsed and instantiated in memory accordingly.
     *
     * @param const stdair::Filename_T& Filename of the input yield file.
     */
    void parseAndLoad (const stdair::Filename_T& iYieldInputFilename);


    /**
     * Destructor.
     */
    ~AIRRAC_Service();


  public:
    // /////////// Business Methods /////////////
    /**
     * Calculate/retrieve a yield.
     */
    void calculateYields (stdair::TravelSolutionList_T&);

    /**
     * Build a sample BOM tree.
     *
     * For now, no object is created: the BOM tree remains empty. In
     * the future, it will hold a sample yield store.
     */
    void buildSampleBom();

    /**
     * Build a sample list of travel solutions.
     *
     * As of now (March 2011), that list is made of the following
     * travel solutions:
     * <ul>
     *  <li>BA9</li>
     *  <li>LHR-SYD</li>
     *  <li>2011-06-10</li>
     *  <li>Q</li>
     *  <li>WTP: 900</li>
     *  <li>Change fee: 20; Non refundable; Saturday night stay</li>
     * </ul>
     *
     * @param TravelSolutionList_T& Sample list of travel solution structures.
     *        It should be given empty. It is altered with the returned sample.
     */
    void buildSampleTravelSolutions (stdair::TravelSolutionList_T&);


  public:
    // //////////////// Display support methods /////////////////
    /**
     * Recursively display (dump in the returned string) the objects
     * of the BOM tree.
     *
     * @return std::string Output string in which the BOM tree is
     *        logged/dumped.
     */
    std::string csvDisplay() const;

    /**
     * Display (dump in the returned string) the full list of travel
     * solution structures.
     *
     * @return std::string Output string in which the list of travel
     *        solutions is logged/dumped.
     */
    std::string csvDisplay (const stdair::TravelSolutionList_T&) const;


  private:
    // /////// Construction and Destruction helper methods ///////
    /**
     * Default constructor.
     */
    AIRRAC_Service();

    /**
     * Copy constructor.
     */
    AIRRAC_Service (const AIRRAC_Service&);

    /**
     * Initialise the (AIRRAC) service context (i.e., the
     * AIRRAC_ServiceContext object).
     */
    void initServiceContext();

    /**
     * Initialise the STDAIR service (including the log service).
     *
     * A reference on the root of the BOM tree, namely the BomRoot object,
     * is stored within the service context for later use.
     *
     * @param const stdair::BasLogParams& Parameters for the output log stream.
     * @param const stdair::BasDBParams& Parameters for the database access.
     */
    stdair::STDAIR_ServicePtr_T initStdAirService (const stdair::BasLogParams&,
                                                   const stdair::BasDBParams&);
    
    /**
     * Initialise the STDAIR service (including the log service).
     *
     * A reference on the root of the BOM tree, namely the BomRoot object,
     * is stored within the service context for later use.
     *
     * @param const stdair::BasLogParams& Parameters for the output log stream.
     */
    stdair::STDAIR_ServicePtr_T initStdAirService (const stdair::BasLogParams&);

    /**
     * Attach the STDAIR service (holding the log and database services) to
     * the AIRRAC_Service.
     *
     * @param stdair::STDAIR_ServicePtr_T Reference on the STDAIR service.
     * @param const bool State whether or not AirRAC owns the STDAIR service
     *        resources.
     */
    void addStdAirService (stdair::STDAIR_ServicePtr_T,
                           const bool iOwnStdairService);
    
    /**
     * Initialise.
     *
     * Nothing is being done at that stage. The buildSampleBom() method may
     * be called later.
     */
    void initAirracService();

    /**
     * Initialise.
     *
     * The CSV file, describing the airline yield data store, is parsed
     * and instantiated in memory accordingly.
     *
     * @param const stdair::Filename_T& Filename of the input yield file.
     */
    void initAirracService (const stdair::Filename_T& iYieldInputFilename);

    /**
     * Finalise.
     */
    void finalise();
    

  private:
    // ///////// Service Context /////////
    /**
     * AirRAC service context.
     */
    AIRRAC_ServiceContext* _airracServiceContext;
  };
}
#endif // __AIRRAC_SVC_AIRRAC_SERVICE_HPP
