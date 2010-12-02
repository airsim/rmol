#ifndef __STDAIR_STDAIR_DB_HPP
#define __STDAIR_STDAIR_DB_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

// Forward declarations
namespace soci {
  class session;
  class statement;
}

namespace stdair {

  // //////// Type definitions /////////
  /** Database session handler. */
  typedef soci::session DBSession_T;
  
  /** Database request statement handler. */
  typedef soci::statement DBRequestStatement_T;
  
  /** Define the name of an database connection. */
  typedef std::string DBConnectionName_T;
  
}
#endif // __STDAIR_STDAIR_DB_HPP
