#ifndef __RMOL_RMOL_TYPES_HPP
#define __RMOL_RMOL_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <vector>
// Boost
#include <boost/shared_ptr.hpp>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/stdair_rm_types.hpp>
#include <stdair/stdair_exceptions.hpp>

// Forward declarations.
namespace stdair {
  class BookingClass;
}


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
   * @brief Empty nesting structure in unconstrainer exception.
   */
  class EmptyNestingStructException : public UnconstrainingException {
  public:
    /** Constructor. */
    EmptyNestingStructException (const std::string& iWhat)
      : UnconstrainingException (iWhat) {}
  };

  /**
   * @brief Missing a DCP in unconstrainer exception.
   */
  class MissingDCPException : public UnconstrainingException {
  public:
    /** Constructor. */
    MissingDCPException (const std::string& iWhat)
      : UnconstrainingException (iWhat) {}
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

  /**
   * @brief Policy-related exception.
   */
  class PolicyException : public stdair::RootException {
  public:
    /** Constructor. */
    PolicyException (const std::string& iWhat)
      : stdair::RootException (iWhat) {}
  };


  /**
   * @brief Convex Hull-related exception.
   */
  class ConvexHullException : public PolicyException {
  public:
    /** Constructor. */
    ConvexHullException (const std::string& iWhat)
      : PolicyException (iWhat) {}
  };

  /**
   * @brief Empty convex hull exception.
   */
  class EmptyConvexHullException : public ConvexHullException {
  public:
    /** Constructor. */
    EmptyConvexHullException (const std::string& iWhat)
      : ConvexHullException (iWhat) {}
  };

  /**
   * @brief Missing policy NULL in convex hull exception.
   */
  class FirstPolicyNotNullException : public ConvexHullException {
  public:
    /** Constructor. */
    FirstPolicyNotNullException (const std::string& iWhat)
      : ConvexHullException (iWhat) {}
  };

  /**
   * @brief Yield convex hull exception.
   */
  class YieldConvexHullException : public ConvexHullException {
  public:
    /** Constructor. */
    YieldConvexHullException (const std::string& iWhat)
      : ConvexHullException (iWhat) {}
  };

  
  /**
   * @brief Fare Family-related exception.
   */
  class FareFamilyException : public stdair::RootException { 
  public:
    /** Constructor. */
    FareFamilyException (const std::string& iWhat) 
      : stdair::RootException (iWhat) {}
  };

  /**
   * @brief Empty Booking Class List of Fare Family exception.
   */
  class EmptyBookingClassListException : public FareFamilyException {
  public:
    /** Constructor. */
    EmptyBookingClassListException (const std::string& iWhat)
      : FareFamilyException (iWhat) {}
  };

  /**
   * @brief Missing Booking Class in Fare Family exception.
   */
  class MissingBookingClassInFareFamilyException : public FareFamilyException {
  public:
    /** Constructor. */
    MissingBookingClassInFareFamilyException (const std::string& iWhat)
      : FareFamilyException (iWhat) {}
  };

  /**
   * @brief Fare Family demand exception.
   */
  class FareFamilyDemandVectorSizeException : public FareFamilyException {
  public:
    /** Constructor. */
    FareFamilyDemandVectorSizeException (const std::string& iWhat)
      : FareFamilyException (iWhat) {}
  };


  // //////// Type definitions /////////
  /**
   * Pointer on the RMOL Service handler.
   */
  typedef boost::shared_ptr<RMOL_Service> RMOL_ServicePtr_T;
  
    /** Define the vector of censorship flags. */
  typedef std::vector<stdair::Flag_T> FlagVector_T;

  /** Define the map between booking class and demand. */
  typedef std::map<stdair::BookingClass*, stdair::MeanStdDevPair_T> BookingClassMeanStdDevPairMap_T;
}
#endif // __RMOL_RMOL_TYPES_HPP
