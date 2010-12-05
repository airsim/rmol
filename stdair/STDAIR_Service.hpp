/**
 * @brief Handle on the StdAir library context
 * @author Anh Quan Nguyen <quannaus@users.sourceforge.net>
 * @date 20/01/2010
 * @detail StdAir aims at providing a clean API, and the corresponding
 *         C++ implementation, for the basis of Airline IT Business Object
 *         Model (BOM), that is, to be used by several other Open Source
 *         projects, such as RMOL and OpenTREP<br>
 *         Install the StdAir library for Airline IT Standard C++ fundaments.
 */
#ifndef __STDAIR_STDAIR_HPP
#define __STDAIR_STDAIR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/basic/BasLogParams.hpp>
#include <stdair/basic/BasDBParams.hpp>
#include <stdair/stdair_service_types.hpp>

namespace stdair {

  /// Forward declarations
  class BomRoot;
  
  /**
   * @brief Interface for the STDAIR Services
   */
  class STDAIR_Service {
  public:
    // ////////// Constructors and destructors //////////
    /**
     * @brief Default constructor.
     */
    STDAIR_Service ();

    /**
     * @brief Constructor.
     * <br>The init() method is called; see the corresponding
     * documentation for more details.
     * <br>Moreover, a reference on an output stream is given, so
     * that log outputs can be directed onto that stream.       
     * @param[in] const BasLogParams& Parameters for the output log stream.
     */
    STDAIR_Service (const BasLogParams&);

    /**
     * @brief Constructor.
     * <br>The init() method is called; see the corresponding
     * documentation for more details.
     * <br>A reference on an output stream is given, so
     * that log outputs can be directed onto that stream.       
     * <br>Moreover, database connection parameters are given, so
     * that database requests can use the corresponding access.
     * @param[in] const BasLogParams& Parameters for the output log stream.
     * @param[in] const BasDBParams& Parameters for the database session.
     */
    STDAIR_Service (const BasLogParams&, const BasDBParams&);

    /**
     * @brief Destructor.
     */
    ~STDAIR_Service();
    
    // ///////////////// Getters ///////////////////
    /**
     * @brief Get a reference on the BomRoot object.
     * <br>If the service context has not been initialised, that
     * method throws an exception (failing assertion).
     * @param[out] BomRoot& Reference on the BomRoot.
     */
    BomRoot& getBomRoot () const {
      return _bomRoot;
    }
    
  private:
    // /////// Construction and Destruction helper methods ///////
    /**
     * @brief Default copy constructor.
     * @param[in] const STDAIR_Service& Reference on the STDAIR_Service handler
     *            to be copied.
     */
    STDAIR_Service (const STDAIR_Service&);
    
    /**
     * @brief Initialise the log.
     * @param[in] const BasLogParams& Parameters for the output log stream.
     */
    void logInit (const BasLogParams&);
    
    /**
     * @brief Initialise the database session.
     * @param[in] const BasDBParams& Parameters for the database session.
     */
    void dbInit (const BasDBParams&);
    
    /**
     * @brief Initialise.
     * <br>The static instance of the log service (Logger object) is created.
     * <br>The static instance of the database session manager
     * (DBSessionManager object) is created.
     * <br>The static instance of the FacSupervisor object, itself referencing
     * all the other objects (factories and BOM), is created.
     * <br>As those three objects are static, there is no need to store them
     * in any service context. However, some lock mechanism may be needed
     * in order to secure the access to the corresponding resources.
     */
    void init ();
    
    /**
     * @brief Finalise.
     */
    void finalise ();
    
  private:
    // /////////////// Attributes ///////////////
    /**
     * @brief Root of the BOM tree.
     */
    BomRoot& _bomRoot;
  };
}
#endif // __STDAIR_STDAIR_HPP
