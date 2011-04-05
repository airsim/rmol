#ifndef __RMOL_RMOL_TYPES_HPP
#define __RMOL_RMOL_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
#include <list>
// Boost
#include <boost/shared_ptr.hpp>
// StdAir
#include <stdair/stdair_exceptions.hpp>

namespace RMOL {

  // Forward declarations
  class RMOL_Service;

  // ///////// Exceptions ///////////
  /**
   * @brief Overbooking-related exception.
   */
  class OverbookingException : public stdair::RootException {
  public:
    /** Constructor. */
    OverbookingException (const std::string& iWhat)
      : stdair::RootException (iWhat) {}
  };

  /**
   * @brief Unconstraining-related exception.
   */
  class UnconstrainingException : public stdair::RootException {
  public:
    /** Constructor. */
    UnconstrainingException (const std::string& iWhat)
      : stdair::RootException (iWhat) {}
  };

  /**
   * @brief Forecast-related exception.
   */
  class ForecastException : public stdair::RootException {
  public:
    /** Constructor. */
    ForecastException (const std::string& iWhat)
      : stdair::RootException (iWhat) {}
  };

  /**
   * @brief Optimisation-related exception.
   */
  class OptimisationException : public stdair::RootException {
  public:
    /** Constructor. */
    OptimisationException (const std::string& iWhat)
      : stdair::RootException (iWhat) {}
  };


  // //////// Type definitions /////////
  /**
   * Pointer on the RMOL Service handler.
   */
  typedef boost::shared_ptr<RMOL_Service> RMOL_ServicePtr_T;

}
#endif // __RMOL_RMOL_TYPES_HPP
