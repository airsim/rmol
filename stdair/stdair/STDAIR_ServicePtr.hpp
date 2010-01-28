#ifndef __STDAIR_SVC_STDAIR_SERVICEPTR_HPP
#define __STDAIR_SVC_STDAIR_SERVICEPTR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>

namespace stdair {

  // Forward declarations
  class STDAIR_Service;
  
  /** Pointer on the STDAIR Service handler. */
  typedef boost::shared_ptr<STDAIR_Service> STDAIR_ServicePtr_T;
  
}
#endif // __STDAIR_SVC_STDAIR_SERVICEPTR_HPP
