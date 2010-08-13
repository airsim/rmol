#ifndef __STDAIR_DBA_DBAAIRLINE_HPP
#define __STDAIR_DBA_DBAAIRLINE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// SOCI
#if defined(SOCI_HEADERS_BURIED)
#include <soci/core/soci.h>
#else // SOCI_HEADERS_BURIED
#include <soci.h>
#endif // SOCI_HEADERS_BURIED

// Forward declarations
namespace stdair {
  struct AirlineStruct;
}

namespace soci {

  /** Specify how the AirlineStruct struct can be converted to (resp. from)
      values stored into (resp. retrieved from) database, using the SOCI
      framework. */
  template <>
  struct type_conversion<stdair::AirlineStruct> {

    typedef values base_type;

    /** Fill an Airline object from the database values. */
    static void from_base (values const& iAirlineValues,
                           indicator /* ind */,
                           stdair::AirlineStruct& ioAirline);


    /** Fill the database values from an Airline object. */
    static void to_base (const stdair::AirlineStruct& iAirline,
                         values& ioAirlineValues,
                         indicator& ioIndicator);
  };
}
#endif // __STDAIR_DBA_DBAAIRLINE_HPP
