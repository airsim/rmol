#ifndef __MYPROVIDER_TYPES_HPP
#define __MYPROVIDER_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <typeinfo>
#include <map>

// Forward declarations
namespace stdair {
  class BomAbstract;
}

namespace myprovider {
  typedef std::map<const std::type_info*, stdair::BomAbstract*> HolderMap_T;  
}  
#endif // __MYPROVIDER_TYPES_HPP
