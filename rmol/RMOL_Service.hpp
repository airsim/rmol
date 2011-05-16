#ifndef __RMOL_SVC_RMOL_SERVICE_HPP
#define __RMOL_SVC_RMOL_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_service_types.hpp>
// RMOL
#include <rmol/RMOL_FORECASTER_Types.hpp>
#include <rmol/RMOL_UNCONSTRAINER_Types.hpp>
#include <rmol/RMOL_UTILITY_Types.hpp>

/// Forward declarations
namespace stdair {
  struct BasLogParams;
  struct BasDBParams;
}

namespace RMOL {

  /// Forward declarations
  class RMOL_ServiceContext;

  /**
   * @brief Interface for the RMOL Services.
   */
  class RMOL_Service {
  public:
    // ////////// Constructors and destructors //////////
    /**
     * Constructor.
     *
     * The initRmolService() method is called; see the corresponding
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
     * @param const stdair::CabinCapacity& Capacity of the cabin of the
     *        sample BOM tree.
     * @param const stdair::Filename_T& Filename of the input demand file.
     */
    RMOL_Service (const stdair::BasLogParams&, const stdair::BasDBParams&,
                  const stdair::CabinCapacity_T&,
                  const stdair::Filename_T& iInputFileName);

    /**
     * Constructor.
     *
     * The initRmolService() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, a reference on an output stream is given, so
     * that log outputs can be directed onto that stream.
     *
     * @param const stdair::BasLogParams& Parameters for the output log
     *        stream.
     * @param const stdair::CabinCapacity& Capacity of the cabin of the
     *        sample BOM tree.
     * @param const stdair::Filename_T& Filename of the input demand file.
     */
    RMOL_Service (const stdair::BasLogParams&, const stdair::CabinCapacity_T&,
                  const stdair::Filename_T& iInputFileName);

    /**
     * Constructor.
     *
     * The initRmolService() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, a reference on an output stream is given, so
     * that log outputs can be directed onto that stream.
     *
     * @param const stdair::BasLogParams& Parameters for the output log
     *        stream.
     * @param const stdair::BasDBParams& Parameters for the database access.
     * @param stdair::CabinCapacity& Capacity of the cabin.
     */
    RMOL_Service (const stdair::BasLogParams&, const stdair::BasDBParams&,
                  const stdair::CabinCapacity_T&);

    /**
     * Constructor.
     *
     * The initRmolService() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, a reference on an output stream is given, so
     * that log outputs can be directed onto that stream.
     *
     * @param const stdair::BasLogParams& Parameters for the output log
     *        stream.
     * @param stdair::CabinCapacity& Capacity of the cabin.
     */
    RMOL_Service (const stdair::BasLogParams&, const stdair::CabinCapacity_T&);

    /**
     * Constructor.
     *
     * The initRmolService() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, as no reference on any output stream is given,
     * it is assumed that the StdAir log service has already been
     * initialised with the proper log output stream by some other
     * methods in the calling chain (for instance, when the RMOL_Service
     * is itself being initialised by another library service such as
     * AIRINV_Service).
     *
     * @param STDAIR_ServicePtr_T the shared pointer of stdair service.
     * @param const stdair::CabinCapacity& Capacity of the cabin of the
     *        sample BOM tree.
     * @param const stdair::Filename_T& Filename of the input demand file.
     */
    RMOL_Service (stdair::STDAIR_ServicePtr_T, const stdair::CabinCapacity_T&,
                  const stdair::Filename_T& iInputFileName);
        
    /**
     * Constructor.
     *
     * The initRmolService() method is called; see the corresponding
     * documentation for more details.
     *
     * Moreover, as no reference on any output stream is given,
     * it is assumed that the StdAir log service has already been
     * initialised with the proper log output stream by some other
     * methods in the calling chain (for instance, when the RMOL_Service
     * is itself being initialised by another library service such as
     * AIRINV_Service).
     *
     * @param STDAIR_ServicePtr_T the shared pointer of stdair service.
     */
    RMOL_Service (stdair::STDAIR_ServicePtr_T);
        
    /**
     * Destructor.
     */
    ~RMOL_Service();


  public:
    // /////////// Business Methods /////////////
    /**
     * Single resource optimization using the Monte Carlo algorithm.
     */
    void optimalOptimisationByMCIntegration (const int K);

    /**
     * Single resource optimization using dynamic programming.
     */
    void optimalOptimisationByDP();

    /**
     * Single resource optimization using EMSR heuristic.
     */
    void heuristicOptimisationByEmsr();
    
    /**
     * Single resource optimization using EMSR-a heuristic.
     */
    void heuristicOptimisationByEmsrA();

    /**
     * Single resource optimization using EMSR-b heuristic.
     */
    void heuristicOptimisationByEmsrB();

    /**
     * Optimise (revenue management) an flight-date/network-date
     */
    void optimise (const stdair::AirlineCode_T&,
                   const stdair::KeyDescription_T&, const stdair::DateTime_T&);


    /**
     * Build a sample BOM tree, and attach it to the BomRoot instance.
     *
     * As for now, two sample BOM trees can be built.
     * <ul>
     *   <li>One BOM tree is based on two actual inventories (one for BA,
     *     another for AF). Each inventory contains one flight. One of
     *     those flights has two legs (and therefore three segments).</li>
     *   <li>The other BOM tree is fake, as a hook for RMOL to work. It has
     *     a single leg-cabin, which has the given capacity.</li>
     * </ul>
     *
     * @param const bool isForDemo Whether the sample BOM tree is for demo only.
     * @param const CabinCapacity_T Capacity of the cabin for RMOL optimisation.
     */
    void buildSampleBom (const bool isForDemo = true,
                         const stdair::CabinCapacity_T iCabinCapacity = 0);


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


  public:
    // //////// Initialisation support methods ///////////
    /**
     * Set up the StudyStatManager.
     */
    void setUpStudyStatManager();
    
    
  private:
    // /////// Construction and Destruction helper methods ///////
    /**
     * Default constructor.
     */
    RMOL_Service();

    /**
     * Copy constructor.
     */
    RMOL_Service (const RMOL_Service&);

    /**
     * Initialise the (RMOL) service context (i.e., the
     * RMOL_ServiceContext object).
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
     * the RMOL_Service.
     *
     * @param stdair::STDAIR_ServicePtr_T Reference on the STDAIR service.
     * @param const bool State whether or not AirInv owns the STDAIR service
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
    void initRmolService();

    /**
     * Initialise.
     *
     * The buildSampleBom() method is called, for RMOL and with the
     * given cabin capacity, in order to build a sample BOM tree. No
     * input file needs to be parsed here.
     *
     * @param const stdair::CabinCapacity& Capacity of the cabin of the
     *        sample BOM tree.
     */
    void initRmolService (const stdair::CabinCapacity_T&);

    /**
     * Initialise.
     *
     * <ol>
     *  <li>Firstly, the buildSampleBom() method is called, for RMOL and with
     *      the given cabin capacity, in order to build a sample BOM
     *      tree.
     *  </li>
     *  <li>Secondly, the filename of a CSV file is given as parameter.
     *      That file describes the problem to be optimised, i.e.:
     *      <ul>
     *        <li>the demand specifications for all the booking classes
     *            (mean and standard deviations for the demand distribution);
     *        </li>the yields corresponding to those booking classes.
     *      </ul>
     *      That CSV file is parsed and instantiated in memory accordingly.
     *      The capacity is that given above.
     *  </li>
     * </ol>
     *
     * @param const stdair::CabinCapacity& Capacity of the cabin of the
     *        sample BOM tree.
     * @param const stdair::Filename_T& Filename of the input demand file.
     */
    void initRmolService (const stdair::CabinCapacity_T&,
                          const stdair::Filename_T& iInputFilename);

    /**
     * Finalise.
     */
    void finalise();


  private:
    // ////////// Service Context //////////
    /**
     * Service Context.
     */
    RMOL_ServiceContext* _rmolServiceContext;
  };
}
#endif // __RMOL_SVC_RMOL_SERVICE_HPP
