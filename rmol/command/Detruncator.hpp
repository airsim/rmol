#ifndef __RMOL_COMMAND_DETRUNCATOR_HPP
#define __RMOL_COMMAND_DETRUNCATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_inventory_types.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>

// Forward declarations.
namespace stdair {
  class GuillotineBlock;
  class SegmentCabin;
}

namespace RMOL {
  // Forward declarations.
  struct HistoricalBookingHolder;
  
  /** Class wrapping the principal unconstraining algorithms and 
      some accessory algorithms. */
  class Detruncator {
  public:
    /**
     * Unconstrain booking figures between two DCP's.
     */
    static void unconstrainUsingAdditivePickUp (const stdair::SegmentCabin&, 
			     BookingClassUnconstrainedDemandVectorMap_T&,
                             UnconstrainedDemandVector_T&,
			     const stdair::DCP_T&, const stdair::DCP_T&,
                             const stdair::Date_T&);
       
    /**
     * Unconstrain booking figures between two DCP's.
     */
    static void unconstrainUsingMultiplicativePickUp
    (const stdair::SegmentCabin&, BookingClassUnconstrainedDemandVectorMap_T&,
     UnconstrainedDemandVector_T&, const stdair::DCP_T&, const stdair::DCP_T&,
     const stdair::Date_T&, const stdair::NbOfSegments_T&);

    /**
     * Retrieve unconstrained demand figures for the first DCP.
     */
    static void retrieveUnconstrainedDemandForFirstDCP
    (const stdair::SegmentCabin&, 
     BookingClassUnconstrainedDemandVectorMap_T&,
     UnconstrainedDemandVector_T&, const stdair::DCP_T&,
     const stdair::NbOfSegments_T&, const stdair::NbOfSegments_T&);

    /**
     * Unconstrain the product-oriented booking figures for a given class ou
     * Q-equivalent class. */
    static void unconstrainUsingMultiplicativePickUp (HistoricalBookingHolder&);
    
  private:
    /**
     * Unconstrain the product-oriented booking figures for a given class ou
     * Q-equivalent class. */
    static void unconstrainUsingAdditivePickUp (const stdair::GuillotineBlock&,
                                                UnconstrainedDemandVector_T&,
                                                const stdair::DCP_T&,
                                                const stdair::DCP_T&,
                                                const stdair::NbOfSegments_T&,
                                                const stdair::BlockIndex_T&);
    /**
     * Unconstrain the product-oriented booking figures for a given class ou
     * Q-equivalent class. */
    static void unconstrainUsingAdditivePickUp (const stdair::GuillotineBlock&,
                                                UnconstrainedDemandVector_T&,
                                                const stdair::DCP_T&,
                                                const stdair::DCP_T&,
                                                const stdair::NbOfSegments_T&,
                                                const stdair::BlockIndex_T&,
                                                const stdair::SegmentCabin&,
                                                const stdair::Date_T&);
    
    /**
     * Unconstrain the product-oriented booking figures for a given class ou
     * Q-equivalent class. */
    static void unconstrainUsingMultiplicativePickUp
    (const stdair::GuillotineBlock&, UnconstrainedDemandVector_T&,
     const stdair::DCP_T&, const stdair::DCP_T&,
     const stdair::NbOfSegments_T&, const stdair::BlockIndex_T&,
     const stdair::NbOfSegments_T&);

    /**
     * Unconstrain the product-oriented booking figures for a given class ou
     * Q-equivalent class. */
    static void unconstrainUsingMultiplicativePickUp
    (const stdair::GuillotineBlock&, UnconstrainedDemandVector_T&,
     const stdair::DCP_T&, const stdair::DCP_T&,
     const stdair::NbOfSegments_T&, const stdair::BlockIndex_T&,
     const stdair::NbOfSegments_T&,
     const stdair::SegmentCabin&, const stdair::Date_T&);
    
    /**
     * Retrieve unconstrained demand figures for the first DCP.
     */
    static void retrieveUnconstrainedDemandForFirstDCP
    (const stdair::GuillotineBlock&, UnconstrainedDemandVector_T&,
     const stdair::DCP_T&, const stdair::BlockIndex_T&,
     const stdair::NbOfSegments_T&, const stdair::NbOfSegments_T&);    
  };
}
#endif // __RMOL_COMMAND_DETRUNCATOR_HPP


