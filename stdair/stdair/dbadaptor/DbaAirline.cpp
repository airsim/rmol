// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <exception>
#include <string>
// Stdair
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/AirlineStruct.hpp>
#include <stdair/dbadaptor/DbaAirline.hpp>
#include <stdair/service/Logger.hpp>

namespace soci {

  // //////////////////////////////////////////////////////////////////////
  void type_conversion<stdair::AirlineStruct>::
  from_base (values const& iAirlineValues, indicator /* ind */,
             stdair::AirlineStruct& ioAirline) {
    /*
      iata_code, name
    */
    ioAirline.setAirlineCode (iAirlineValues.get<std::string> ("iata_code"));
    // The city code will be set to the default value (empty string)
    // when the column is null
    ioAirline.setAirlineName (iAirlineValues.get<std::string> ("name", ""));
  }

  // //////////////////////////////////////////////////////////////////////
  void type_conversion<stdair::AirlineStruct>::
  to_base (const stdair::AirlineStruct& iAirline, values& ioAirlineValues,
           indicator& ioIndicator) {
    const indicator lNameIndicator =
      iAirline.getAirlineName().empty() ? i_null : i_ok;
    ioAirlineValues.set ("iata_code", iAirline.getAirlineCode());
    ioAirlineValues.set ("name", iAirline.getAirlineName(), lNameIndicator);
    ioIndicator = i_ok;
  }

}

namespace stdair {

}
