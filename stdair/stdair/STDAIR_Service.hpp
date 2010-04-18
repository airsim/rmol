#ifndef __STDAIR_SVC_STDAIR_SERVICE_HPP
#define __STDAIR_SVC_STDAIR_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>
// StdAir
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>

namespace stdair {

  // Forward declarations
  class BomRoot;
  class YieldStore;
  class Inventory;
  
  /** Interface for the STDAIR Services. */
  class STDAIR_Service {
  public:
    // ////////// Constructors and destructors //////////
    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, a reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        @param const BasLogParams& Parameters for the output log stream. */
    STDAIR_Service (const BasLogParams&);

    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>A reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        <br>Moreover, database connection parameters are given, so
        that database requests can use the corresponding access.
        @param const BasLogParams& Parameters for the output log stream.
        @param const BasDBParams& Parameters for the database session. */
    STDAIR_Service (const BasLogParams&, const BasDBParams&);

    /** Destructor. */
    ~STDAIR_Service();

    
    /** Retrieve the Inventory corresponding to the given airline code
        (Inventory key).
        <br>If not existing, a ObjectNotFoundException exception is thrown. */
    Inventory& getInventory (const AirlineCode_T& iAirlineCode) const;

    /** Retrieve the Yield Store corresponding to the given airline code
        (YieldStore key).
        <br>If not existing, a ObjectNotFoundException exception is thrown. */
    YieldStore& getYieldStore (const AirlineCode_T& iAirlineCode) const;

    
    // ///////////////// Getters ///////////////////
    /** Get a reference on the BomRoot object.
        <br>If the service context has not been initialised, that
        method throws an exception (failing assertion). */
    BomRoot& getBomRoot () const {
      return _bomRoot;
    }

  public:
    // /////// Construction and Destruction helper methods ///////
    /** Retrieve the Inventory corresponding to the given airline code
        (Inventory key).
        <br>If not existing, a ObjectNotFoundException exception is thrown. */
    Inventory& createInventory (const AirlineCode_T& iAirlineCode) const;

    /** Retrieve the YieldStore corresponding to the given airline code
        (YieldStore key).
        <br>If not existing, a ObjectNotFoundException exception is thrown. */
    YieldStore& createYieldStore (const AirlineCode_T& iAirlineCode) const;

    /** Add the airline-specific AirlineFeature object to its AirlineFeatureSet
        parent. */
    void addAirlineFeature (const AirlineCode_T& iAirlineCode) const;

    
  private:
    // /////// Construction and Destruction helper methods ///////
    /** Default constructor. */
    STDAIR_Service ();
    /** Default copy constructor. */
    STDAIR_Service (const STDAIR_Service&);

    /** Initialise the log. */
    void logInit (const BasLogParams&);

    /** Initialise the database session. */
    void dbInit (const BasDBParams&);

    /** Initialise.
        <br>The static instance of the log service (Logger object) is created.
        <br>The static instance of the database session manager
        (DBSessionManager object) is created.
        <br>The static instance of the FacSupervisor object, itself referencing
        all the other objects (factories and BOM), is created.
        <br>As those three objects are static, there is no need to store them
        in any service context. However, some lock mechanism may be needed
        in order to secure the access to the corresponding resources. */
    void init ();

    /** Initialise the AirlineFeatureSet object, and attach it to the
        BomRoot. */
    void initAirlineFeatureSet ();
    
    /** Initialise the DemandStreamList object, and attach it to the
        BomRoot. */
    void initDemandStreamList ();

    /** Finalise. */
    void finalise ();

    
  private:
    // /////////////// Attributes ///////////////
    /** Root of the BOM tree. */
    BomRoot& _bomRoot;
  };
}
#endif // __STDAIR_SVC_STDAIR_SERVICE_HPP
