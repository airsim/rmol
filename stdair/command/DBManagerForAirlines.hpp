#ifndef __DSIM_CMD_DBMANAGERFORAIRLINES_HPP
#define __DSIM_CMD_DBMANAGERFORAIRLINES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_db.hpp>
#include <stdair/command/CmdAbstract.hpp>

namespace stdair {

  // Forward declarations
  struct AirlineStruct;

  /** Class building the Business Object Model (BOM) from data retrieved
      from the database. */
  class DBManagerForAirlines : public CmdAbstract {
  public:
    /** Update the fields of the database row
        corresponding to the given BOM object.
        @parameter DBSession_T&
        @parameter AirlineStruct& . */
    static void updateAirlineInDB (DBSession_T&, const AirlineStruct&);

    /** Retrieve, from the (MySQL) database, the row corresponding to
        the given BOM code, and fill the given BOM object with that retrieved
        data.
        @parameter DBSession_T&
        @parameter const AirlineCode_T&
        @parameter AirlineStruct& . */
    static bool retrieveAirline (DBSession_T&, const AirlineCode_T&,
                                 AirlineStruct&);

    
  public:
    /** Prepare (parse and put in cache) the SQL statement.
        @parameter DBSession_T&
        @parameter DBRequestStatement_T&
        @parameter AirlineStruct& . */
    static void prepareSelectStatement (DBSession_T&, DBRequestStatement_T&,
                                        AirlineStruct&);

    /** Iterate on the SQL statement.
        <br>The SQL has to be already prepared.
        @parameter DBRequestStatement_T&
        @parameter AirlineStruct& . */
    static bool iterateOnStatement (DBRequestStatement_T&, AirlineStruct&);

    
  private:
    /** Prepare (parse and put in cache) the SQL statement.
        @parameter DBSession_T&
        @parameter DBRequestStatement_T&
        @parameter const AirlineCode_T&
        @parameter AirlineStruct&  */
    static void prepareSelectOnAirlineCodeStatement (DBSession_T&,
                                                     DBRequestStatement_T&,
                                                     const AirlineCode_T&,
                                                     AirlineStruct&);

    
  private:
    // /////////////////// Constructors and Destructors //////////////
    /** Default constructors. As all the methods are static, there is no
        need to use those constructors. */
    DBManagerForAirlines () {}
    DBManagerForAirlines (const DBManagerForAirlines&) {}
    /** Destructor. */
    ~DBManagerForAirlines () {}
  };
  
}
#endif // __DSIM_CMD_DBMANAGERFORAIRLINES_HPP
