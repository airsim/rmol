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
  class STDAIR_Service;
  struct BookingRequestStruct;
  struct BasLogParams;
  struct BasDBParams;
  struct BookingRequestStruct;
}

namespace AIRRAC {

  // Forward declaration
  class AIRRAC_ServiceContext;

  
  /** Interface for the AIRRAC Services. */
  class AIRRAC_Service {
  public:
    // /////////// Business Methods /////////////
    /** Calculate/retrieve a yield. */
    void calculateYields (stdair::TravelSolutionList_T&);
    // /////////// Business Methods /////////////    
   
  public:
    // ////////////////// Constructors and Destructors //////////////////    
    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>A reference on an output stream is given, so that log
        outputs can be directed onto that stream.
        <br>Moreover, database connection parameters are given, so that a
        session can be created on the corresponding database.
        @param const stdair::BasLogParams& Parameters for the output log stream.
        @param const stdair::BasDBParams& Parameters for the database access.
        @param const stdair::Filename_T& Filename of the input yield file. */
    AIRRAC_Service (const stdair::BasLogParams&, const stdair::BasDBParams&,
                    const stdair::Filename_T& iYieldInputFilename);

    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, a reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        @param const stdair::BasLogParams& Parameters for the output log stream.
        @param const stdair::Date_T& Date for the beginning of analysis.
        @param const stdair::Filename_T& Filename of the input yield file. */
    AIRRAC_Service (const stdair::BasLogParams&,
                    const stdair::Filename_T& iYieldInputFilename);

    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, as no reference on any output stream is given,
        it is assumed that the StdAir log service has already been
        initialised with the proper log output stream by some other
        methods in the calling chain (for instance, when the AIRRAC_Service
        is itself being initialised by another library service such as
        SIMCRS_Service).
        @param stdair::STDAIR_ServicePtr_T Reference on the STDAIR service.
        @param const stdair::Filename_T& Filename of the input yield file. */
    AIRRAC_Service (stdair::STDAIR_ServicePtr_T ioSTDAIR_ServicePtr,
                    const stdair::Filename_T& iYieldInputFilename);

    /** Destructor. */
    ~AIRRAC_Service();


  private:
    // /////// Construction and Destruction helper methods ///////
    /** Default constructor. */
    AIRRAC_Service ();
    /** Default copy constructor. */
    AIRRAC_Service (const AIRRAC_Service&);

    /** Initialise the (AIRRAC) service context (i.e., the
        AIRRAC_ServiceContext object). */
    void initServiceContext ();

    /** Initialise the STDAIR service (including the log service).
        <br>A reference on the root of the BOM tree, namely the BomRoot object,
        is stored within the service context for later use.
        @param const stdair::BasLogParams& Parameters for the output log stream.
        @param const stdair::BasDBParams& Parameters for the database access. */
    void initStdAirService (const stdair::BasLogParams&,
                            const stdair::BasDBParams&);
    
    /** Initialise the STDAIR service (including the log service).
        <br>A reference on the root of the BOM tree, namely the BomRoot object,
        is stored within the service context for later use.
        @param const stdair::BasLogParams& Parameters for the output log
               stream. */
    void initStdAirService (const stdair::BasLogParams&);
    
    /** Initialise.
        <br>The CSV file, describing the airline yields for the
        simulator, is parsed and the inventories are generated accordingly.
        @param const stdair::Filename_T& Filename of the input yield file. */
    void init (const stdair::Filename_T& iYieldInputFilename); 

    /** Finalise. */
    void finalise ();

    
  private:
    // ///////// Service Context /////////
    /** AirRAC context. */
    AIRRAC_ServiceContext* _airracServiceContext;
  };
}
#endif // __AIRRAC_SVC_AIRRAC_SERVICE_HPP
