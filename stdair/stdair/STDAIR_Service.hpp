#ifndef __STDAIR_SVC_STDAIR_SERVICE_HPP
#define __STDAIR_SVC_STDAIR_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/basic/BasLogParams.hpp>

namespace stdair {

  // Forward declarations
  class BomRoot;

  
  /** Interface for the STDAIR Services. */
  class STDAIR_Service {
  public:
    // ////////// Constructors and destructors //////////
    /** Constructor.
        <br>The init() method is called; see the corresponding documentation
        for more details.
        <br>Moreover, a reference on an output stream is given, so
        that log outputs can be directed onto that stream.       
        @param const stdair::BasLogParams& Parameters for the output log
               stream. */
    STDAIR_Service (const BasLogParams&);

    /** Destructor. */
    ~STDAIR_Service();

    
    // ///////////////// Getters ///////////////////
    /** Get a reference on the BomRoot object.
        <br>If the service context has not been initialised, that
        method throws an exception (failing assertion). */
    BomRoot& getBomRoot () const {
      return _bomRoot;
    }

    
  private:
    // /////// Construction and Destruction helper methods ///////
    /** Default constructor. */
    STDAIR_Service ();
    /** Default copy constructor. */
    STDAIR_Service (const STDAIR_Service&);

    /** Initialise the log. */
    void logInit (const BasLogParams&);

    /** Initialise.
        <br>The static instance of the log service (Logger object) is created.
        <br>The static instance of the FacSupervisor object, itself referencing
        all the other objects (factories and BOM), is created.
        <br>As those two objects are static, there is no need to store them
        in any service context. However, some lock mechanism may be needed
        in order to secure the access to the corresponding resources. */
    void init ();

    /** Finalise. */
    void finalise ();

    
  private:
    // /////////////// Attributes ///////////////
    /** Root of the BOM tree. */
    BomRoot& _bomRoot;
  };
}
#endif // __STDAIR_SVC_STDAIR_SERVICE_HPP
