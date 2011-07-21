#ifndef __AIRRAC_CMD_YIELDRULEGENERATOR_HPP
#define __AIRRAC_CMD_YIELDRULEGENERATOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/command/CmdAbstract.hpp>
// AirRAC
#include <airrac/AIRRAC_Types.hpp>

namespace stdair {
  class BomRoot;
  class YieldRule; 
  class AirportPair;
  class DatePeriod;
  class PosChannel;
  class TimePeriod;
  class YieldFeatures;
  class AirlineClassList;
}

namespace AIRRAC {

  // Forward declarations
  struct YieldRuleStruct;
  namespace YieldParserHelper {
    struct doEndYield;
  }
    
  /** Class handling the generation / instantiation of the Yield BOM. */
  class YieldRuleGenerator : public stdair::CmdAbstract {
    // Only the following class may use methods of YieldGenerator.
    // Indeed, as those methods build the BOM, it is not good to expose
    // them public.
    friend class YieldFileParser;
    friend struct YieldParserHelper::doEndYield;
    friend class YieldParser;
    
  private:

    /** 
     * Generate the airport pair object corresponding to the given
     * yieldRule and add them to the given BomRoot.
     *
     * @param stdair::BomRoot&      Boom root node to attach an airport pair
     * object.
     * @param const YieldRuleStruct& Parsed yield rule to add to the BomRoot.
     */
    static void createAirportPair (stdair::BomRoot&,
                                   const YieldRuleStruct&);

    /**
     * Generate the date-period object corresponding to the given
     * yieldRule.  
     *
     * @param stdair::AirportPair&  Airport Pair node to attach a date period
     * object.
     * @param const YieldRuleStruct& Parsed yield rule to add to the BomRoot.
     */
    static void createDateRange (stdair::AirportPair&,
                                 const YieldRuleStruct&);
    
    /**
     * Generate the point_of_sale-channel object corresponding to
     * the given yieldRule.
     *
     * @param stdair::DatePeriod&   Date Period node to attach a pos-channel
     * object.
     * @param const YieldRuleStruct& Parsed yield rule to add to the BomRoot.
     */
    static void createPOSChannel (stdair::DatePeriod&,
                                  const YieldRuleStruct&);
    
    /**
     * Generate the time-period object corresponding to the given
     * yieldRule.
     *
     * @param stdair::PosChannel&   Pos-Channel node to attach a time period
     * object.
     * @param const YieldRuleStruct& Parsed yield rule to add to the BomRoot.
     */
    static void createTimeRange (stdair::PosChannel&,
                                 const YieldRuleStruct&);

    /**
     * Generate the yield-features object corresponding to the given
     * yieldRule.
     *
     * @param stdair::TimePeriod&   Time Period node to attach a yield features
     * object.
     * @param const YieldRuleStruct& Parsed yield rule to add to the BomRoot.
     */
    static void createYieldFeatures (stdair::TimePeriod&,
                                    const YieldRuleStruct&);

    /**
     * Generate the airline-class list object corresponding to the
     * given yieldRule.
     *
     * @param stdair::YieldFeatures& Yield Features node to attach an
     * airline-class list object.
     * @param const YieldRuleStruct& Parsed yield rule to add to the BomRoot.
     */
    static void createAirlineClassList (stdair::YieldFeatures&,
                                        const YieldRuleStruct&);

    
  };

}
#endif // __AIRRAC_CMD_YIELDRULEGENERATOR_HPP
