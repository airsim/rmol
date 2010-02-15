#ifndef __STDAIR_BOM_DEMANDSTREAMTYPES_HPP
#define __STDAIR_BOM_DEMANDSTREAMTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// Boost
#include <boost/shared_ptr.hpp>
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  // Forward declaration
  class DemandStream;

  /** Type definition for the hashed key of the DemandStreamKey object. */
  typedef std::string DemandStreamKeyStr_T;
  
  /** Define a map of demand strams. */
  typedef std::map<const DemandStreamKeyStr_T, DemandStream*> DemandStreamList_T;
  
  /** Type definition for a reference on a list of DemandStream objects. */
  typedef boost::shared_ptr<DemandStreamList_T> DemandStreamListPtr_T;
}
#endif // __STDAIR_BOM_DEMANDSTREAMTYPES_HPP
