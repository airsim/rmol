// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// SOCI
#if defined(SOCI_HEADERS_BURIED)
#include <soci/core/soci.h>
#include <soci/backends/mysql/soci-mysql.h>
#else // SOCI_HEADERS_BURIED
#include <soci.h>
#include <mysql/soci-mysql.h>
#endif // SOCI_HEADERS_BURIED
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_exceptions.hpp>
#include <stdair/bom/AirlineStruct.hpp>
#include <stdair/dbadaptor/DbaAirline.hpp>
#include <stdair/command/DBManagerForAirlines.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  void DBManagerForAirlines::
  prepareSelectStatement (DBSession_T& ioSociSession,
                          DBRequestStatement_T& ioSelectStatement,
                          AirlineStruct& ioAirline) {
  
    try {
    
      // Instanciate a SQL statement (no request is performed at that stage)
      /**
         select code, name
         from airlines;
      */

      ioSelectStatement = (ioSociSession.prepare
                           << "select iata_code, name "
                           << "from airlines ", soci::into (ioAirline));

      // Execute the SQL query
      ioSelectStatement.execute();

    } catch (std::exception const& lException) {
      throw SQLDatabaseException (lException.what());
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void DBManagerForAirlines::
  prepareSelectOnAirlineCodeStatement (DBSession_T& ioSociSession,
                                       DBRequestStatement_T& ioSelectStatement,
                                       const AirlineCode_T& iAirlineCode,
                                       AirlineStruct& ioAirline) {
  
    try {
    
      // Instanciate a SQL statement (no request is performed at that stage)
      /**
         select code, name
         from airlines
         where code = iAirlineCode;
      */

      ioSelectStatement = (ioSociSession.prepare
                           << "select iata_code, name "
                           << "from airlines "
                           << "where iata_code = :airline_code ",
                           soci::into (ioAirline), soci::use (iAirlineCode));

      // Execute the SQL query
      ioSelectStatement.execute();

    } catch (std::exception const& lException) {
      throw SQLDatabaseException (lException.what());
    }
  }

  // //////////////////////////////////////////////////////////////////////
  bool DBManagerForAirlines::
  iterateOnStatement (DBRequestStatement_T& ioStatement,
                      AirlineStruct& ioAirline) {
    bool hasStillData = false;
  
    try {

      // Retrieve the next row of Airline object
      hasStillData = ioStatement.fetch();
      
    } catch (std::exception const& lException) {
      throw SQLDatabaseException (lException.what());
    }

    return hasStillData;
  }

  // //////////////////////////////////////////////////////////////////////
  void DBManagerForAirlines::updateAirlineInDB (DBSession_T& ioSociSession,
                                                const AirlineStruct& iAirline) {
    try {
      // Begin a transaction on the database
      ioSociSession.begin();

      // Retrieve the airline code
      const std::string& lAirlineCode = iAirline.getAirlineCode();
      
      // Retrieve the airline name
      const std::string& lAirlineName = iAirline.getAirlineName();
      
      // Instanciate a SQL statement (no request is performed at that stage)
      DBRequestStatement_T lUpdateStatement =
        (ioSociSession.prepare
         << "update airlines "
         << "set name = :name "
         << "where iata_code = :iata_code",
         soci::use (lAirlineName), soci::use (lAirlineCode));
      
      // Execute the SQL query
      lUpdateStatement.execute (true);
      
      // Commit the transaction on the database
      ioSociSession.commit();
        
      // Debug
      // STDAIR_LOG_DEBUG ("[" << lAirlineCode << "] " << iAirline);
      
    } catch (std::exception const& lException) {
      throw SQLDatabaseException (lException.what());
    }
  }

  // //////////////////////////////////////////////////////////////////////
  bool DBManagerForAirlines::retrieveAirline (DBSession_T& ioSociSession,
                                   const AirlineCode_T& iAirlineCode,
                                   AirlineStruct& ioAirline) {
    bool oHasRetrievedAirline = false;
      
    try {
      // Prepare the SQL request corresponding to the select statement
      DBRequestStatement_T lSelectStatement (ioSociSession);
      prepareSelectOnAirlineCodeStatement (ioSociSession, lSelectStatement,
                                           iAirlineCode, ioAirline);
      
      // const bool shouldDoReset = true;
      bool hasStillData = iterateOnStatement (lSelectStatement, ioAirline);
      if (hasStillData == true) {
        oHasRetrievedAirline = true;
      }

      // Sanity check
      // const bool shouldNotDoReset = false;
      hasStillData = iterateOnStatement (lSelectStatement, ioAirline);
      
      // Debug
      // STDAIR_LOG_DEBUG ("[" << iDocID << "] " << ioAirline);
      
    } catch (std::exception const& lException) {
      throw SQLDatabaseException (lException.what());
    }

    return oHasRetrievedAirline;
  }

}
