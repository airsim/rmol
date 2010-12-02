#ifndef __STDAIR_SVC_DBSESSIONMANAGER_HPP
#define __STDAIR_SVC_DBSESSIONMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_db.hpp>

namespace stdair {
  
  // Forward declarations
  struct BasDBParams;

  /** Class holding the database session.
      <br>Note that the database access is handled by the SOCI library. */
  class DBSessionManager {
    // Friend classes
    friend class FacSupervisor;
    friend class STDAIR_Service;

  public:
    /** Return the static DBSessionManager instance. */
    static DBSessionManager& instance();

    /** Retrieve the database session handler, held by the static instance
        of DBSessionManager. */
    DBSession_T& getDBSession() const;
    
    
  private:
    /** Default constructors are private so that only the required 
        constructor can be used. */
    DBSessionManager (const BasDBParams&);
    /** Default constructor. It must not be used. */
    DBSessionManager ();
    /** Default copy constructor. It must not be used. */
    DBSessionManager (const DBSessionManager&);
    /** Destructor. */
    ~DBSessionManager ();

    /** Initialise the (MySQL) database connection for the static
        DBSessionManager instance. */
    void dbInit (const BasDBParams&);
    
    /** Close the (MySQL) database connection attached to the static
        DBSessionManager instance. */
    void dbFinalise ();
    

  private:
    /** Initialise the static DBSessionManager instance.
        <br>The (MySQL) database connection is initialised. */
    static void init (const BasDBParams&);
    
    /** Delete the static DBSessionManager instance.*/
    static void clean();

    
  private:
    /** Instance object.*/
    static DBSessionManager* _instance;

    /** Database session handler. */
    DBSession_T* _dbSession;
  };

}
#endif // __STDAIR_SVC_DBSESSIONMANAGER_HPP
