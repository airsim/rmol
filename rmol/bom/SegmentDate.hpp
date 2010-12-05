#ifndef __RMOL_BOM_SEGMENTDATE_HPP
#define __RMOL_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <bom/SegmentDate.hpp>

namespace RMOL {

  /** Class modelling an airline-related SegmentDate. */
  class SegmentDate 
  //: public stdair::SegmentDate
  {
  public:

    /** Compute and update the censorship flag for all the booking classes
        of the given segment-date. */
    void updateCensorshipFlag ();
    
    /** Same method, but on an object provided by a third party (e.g.,
        an external library). */
    // WHEN STDAIR IS ENABLED, PLEASE ADD stdair:: to BOM types
    static void updateCensorshipFlag (SegmentDate& ioSegmentDate);
    
  private:
    
  };
  
}
#endif // __RMOL_BOM_SEGMENTDATE_HPP
