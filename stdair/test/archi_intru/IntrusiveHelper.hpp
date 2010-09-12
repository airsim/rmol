#ifndef __INTRUSIVE_BOM_INTRUSIVEHELPER_HPP
#define __INTRUSIVE_BOM_INTRUSIVEHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iosfwd>
#include <sstream>
#include <string>

/** The disposer object function. */
template <typename NODE>
struct delete_disposer {
  void operator() (NODE* oNODE_ptr) {
    delete oNODE_ptr; oNODE_ptr = NULL;
  }
};

// These compare (STL strings) keys of NODE objects
template <typename NODE>
struct StrExpComp {
  bool operator() (const std::string& iKey, const NODE& iBom) const {
    return (iKey < iBom.getKey());
  }

  bool operator() (const NODE& iBom, const std::string& iKey) const {
    return (iBom.getKey() < iKey);
  }
};

template <typename NODE>
struct StrExpEqual {
   bool operator() (const std::string& iKey, const NODE& iBom) const {
     return (iKey == iBom.getKey());
   }

   bool operator() (const NODE& iBom, const std::string& iKey) const {
     return (iBom.getKey() == iKey);
   }
};

#endif // __INTRUSIVE_BOM_INTRUSIVEHELPER_HPP
