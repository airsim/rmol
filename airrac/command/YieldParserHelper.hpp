#ifndef __AIRRAC_CMD_YIELDPARSERHELPER_HPP
#define __AIRRAC_CMD_YIELDPARSERHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
//#define BOOST_SPIRIT_DEBUG
// StdAir
#include <stdair/basic/BasParserTypes.hpp>
#include <stdair/command/CmdAbstract.hpp>
// Airrac
#include <airrac/AIRRAC_Types.hpp>
#include <airrac/bom/YieldRuleStruct.hpp>

// Forward declarations
namespace stdair {
  class BomRoot;
}

namespace AIRRAC {

  namespace YieldParserHelper {

    // ///////////////////////////////////////////////////////////////////
    //  Semantic actions
    // ///////////////////////////////////////////////////////////////////
    /** Generic Semantic Action (Actor / Functor) for the Yield Parser. */
    struct ParserSemanticAction {
      /** Actor Constructor. */
      ParserSemanticAction (YieldRuleStruct&);
      /** Actor Context. */
      YieldRuleStruct& _yieldRule;
    };

    /** Store the parsed yield Id. */
    struct storeYieldId : public ParserSemanticAction {
      /** Actor Constructor. */
      storeYieldId (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (unsigned int,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed origin. */
    struct storeOrigin : public ParserSemanticAction {
      /** Actor Constructor. */
      storeOrigin (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed destination. */
    struct storeDestination : public ParserSemanticAction {
      /** Actor Constructor. */
      storeDestination (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

     /** Store the parsed start of the date range. */
    struct storeDateRangeStart : public ParserSemanticAction {
      /** Actor Constructor. */
      storeDateRangeStart (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed end of the date range. */
    struct storeDateRangeEnd : public ParserSemanticAction {
      /** Actor Constructor. */
      storeDateRangeEnd (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed start range time. */
    struct storeStartRangeTime : public ParserSemanticAction {
      /** Actor Constructor. */
      storeStartRangeTime (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed end start range time. */
    struct storeEndRangeTime : public ParserSemanticAction {
      /** Actor Constructor. */
      storeEndRangeTime (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed customer point_of_sale. */
    struct storePOS : public ParserSemanticAction {
      /** Actor Constructor. */
      storePOS (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the cabin code. */
    struct storeCabinCode : public ParserSemanticAction {
      /** Actor Constructor. */
      storeCabinCode  (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (char,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the channel distribution. */
    struct storeChannel : public ParserSemanticAction {
      /** Actor Constructor. */
      storeChannel (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

     /** Store the parsed yield value. */
    struct storeYield : public ParserSemanticAction {
      /** Actor Constructor. */
      storeYield (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (double,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const; 
    };
    
    /** Store the parsed airline code. */
    struct storeAirlineCode : public ParserSemanticAction {
      /** Actor Constructor. */
      storeAirlineCode (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
    };

    /** Store the parsed class. */
    struct storeClass : public ParserSemanticAction {
      /** Actor Constructor. */
      storeClass (YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (std::vector<char>,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const; 
    };
    
    /** Mark the end of the yield-rule parsing. */
    struct doEndYield : public ParserSemanticAction {
      /** Actor Constructor. */
      doEndYield (stdair::BomRoot&, YieldRuleStruct&);
      /** Actor Function (functor). */
      void operator() (boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type,
                       boost::spirit::qi::unused_type) const;
      /** Actor Specific Context. */
      stdair::BomRoot& _bomRoot;
    };
  
    /////////////////////////////////////////////////////////////////////////
    //
    //  (Boost Spirit) Grammar Definition
    //
    /////////////////////////////////////////////////////////////////////////
    /**
     // Yields: yieldID; OriginCity; DestinationCity; DateRangeStart;
     DateRangeEnd; DepartureTimeRangeStart; DepartureTimeRangeEnd; Yield; AirlineCode; Class

     1; LHR; JFK; 2008-06-01; 2009-12-31; 00:00; 23:59; 4200.0; BA; A;

     YieldID                 (Integer)
     OriginCity              (3-char airport code)
     DestinationCity         (3-char airport code)
     DateRangeStart          (yyyy-mm-dd)
     DateRangeEnd            (yyyy-mm-dd)
     DepartureTimeRangeStart (hh:mm)
     DepartureTimeRangeEnd   (hh:mm)
     Yield                   (Double)
     AirlineCodeList         (List of 2-char airline code)
     ClassList               (List of 1-char class code)
    
     */

    /** Grammar for the Yield-Rule parser. */
    struct YieldRuleParser : 
      public boost::spirit::qi::grammar<stdair::iterator_t, 
                                        boost::spirit::ascii::space_type> {

      YieldRuleParser (stdair::BomRoot&, YieldRuleStruct&);

      // Instantiation of rules
      boost::spirit::qi::rule<stdair::iterator_t,
                              boost::spirit::ascii::space_type>
      start, comments, yield_rule, yield_id, origin, destination, dateRangeStart,
        dateRangeEnd, date, timeRangeStart, timeRangeEnd, time, point_of_sale,
        cabinCode, channel, yield, segment, yield_rule_end;
      
      // Parser Context
      stdair::BomRoot& _bomRoot;
      YieldRuleStruct& _yieldRule;
    };

  }
  
  /////////////////////////////////////////////////////////////////////////
  //
  //  Entry class for the file parser
  //
  /////////////////////////////////////////////////////////////////////////
  /** Class wrapping the 
      initialisation and entry point of the parser.
      <br>The seemingly redundancy is used to force the instantiation of
      the actual parser, which is a templatised Boost Spirit grammar.
      Hence, the actual parser is instantiated within that class object
      code. */
  class YieldFileParser : public stdair::CmdAbstract {
  public:
    /** Constructor. */
    YieldFileParser (stdair::BomRoot&,
                     const stdair::Filename_T& iYieldInputFilename);

    /** Parse the yield store input file. */
    bool generateYieldStore ();
      
  private:
    /** Initialise. */
    void init();
      
  private:

    // Attributes
    /** File-name of the CSV-formatted yield input file. */
    stdair::Filename_T _filename;
      
    /** Root of the BOM tree. */
    stdair::BomRoot& _bomRoot;

    /** Yield Structure. */
    YieldRuleStruct _yieldRule;
  };
  
}
#endif // __AIRRAC_CMD_YIELDPARSERHELPER_HPP
