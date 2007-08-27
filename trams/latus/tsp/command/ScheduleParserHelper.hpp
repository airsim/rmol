#ifndef __LATUS_TSP_CMD_SCHEDULEPARSERHELPER_HPP
#define __LATUS_TSP_CMD_SCHEDULEPARSERHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
// Boost Spirit (Parsing)
#include <boost/spirit/core.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
// LATUS Common
#include <latus/com/command/CmdAbstract.hpp>
// LATUS TSP
#include <latus/tsp/bom/FlightPeriodStruct.hpp>

namespace LATUS {

  // Forward declarations
  namespace COM {
    class WorldSchedule;
  }
  
  namespace TSP {

    namespace ScheduleParserHelper {
      
      // ///////////////////////////////////////////////////////////////////////
      //
      //  Definition of Basic Types
      //
      // ///////////////////////////////////////////////////////////////////////
      // For a file, the parsing unit is the character (char). For a string,
      // it is a "char const *".
      // typedef char const* iterator_t;
      typedef char char_t;
    
      // The types of iterator, scanner and rule are then derived from
      // the parsing unit.
      typedef boost::spirit::file_iterator<char_t> iterator_t;
      typedef boost::spirit::scanner<iterator_t> scanner_t;
      typedef boost::spirit::rule<scanner_t> rule_t;

      
      // ///////////////////////////////////////////////////////////////////////
      //
      //  Semantic actions
      //
      // ///////////////////////////////////////////////////////////////////////
      /** Generic Semantic Action (Actor / Functor) for the Schedule Parser. */
      struct ParserSemanticAction {
        /** Actor Constructor. */
        ParserSemanticAction (FlightPeriodStruct_T&);
        /** Actor Context. */
        FlightPeriodStruct_T& _flightPeriod;
      };
      
      /** Store the parsed airline code. */
      struct storeAirlineCode : public ParserSemanticAction {
        /** Actor Constructor. */
        storeAirlineCode (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };
  
      /** Store the parsed flight number. */
      struct storeFlightNumber : public ParserSemanticAction {
        /** Actor Constructor. */
        storeFlightNumber (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (unsigned int iNumber) const;
      };
  
      /** Store the start of the date range. */
      struct storeDateRangeStart : public ParserSemanticAction {
        /** Actor Constructor. */
        storeDateRangeStart (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the end of the date range. */
      struct storeDateRangeEnd : public ParserSemanticAction {
        /** Actor Constructor. */
        storeDateRangeEnd (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the DOW (day of the Week). */
      struct storeDow : public ParserSemanticAction {
        /** Actor Constructor. */
        storeDow (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the parsed leg board point. */
      struct storeLegBoardPoint : public ParserSemanticAction {
        /** Actor Constructor. */
        storeLegBoardPoint (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };
  
      /** Store the parsed leg off point. */
      struct storeLegOffPoint : public ParserSemanticAction {
        /** Actor Constructor. */
        storeLegOffPoint (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the board time. */
      struct storeBoardTime : public ParserSemanticAction {
        /** Actor Constructor. */
        storeBoardTime (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the date off-set. */
      struct storeDateOffSet : public ParserSemanticAction {
        /** Actor Constructor. */
        storeDateOffSet (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (int iDateOffSet) const;
      };

      /** Store the off time. */
      struct storeOffTime : public ParserSemanticAction {
        /** Actor Constructor. */
        storeOffTime (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the elapsed time. */
      struct storeElapsedTime : public ParserSemanticAction {
        /** Actor Constructor. */
        storeElapsedTime (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the parsed leg cabin code. */
      struct storeLegCabinCode : public ParserSemanticAction {
        /** Actor Constructor. */
        storeLegCabinCode (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (char iChar) const;
      };
  
      /** Store the parsed capacity. */
      struct storeCapacity : public ParserSemanticAction {
        /** Actor Constructor. */
        storeCapacity (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (double iReal) const;
      };
  
      /** Store whether or not the segment definitions are specific.
          Specific means that there is a definition for each segment.
          General (not specific) means that a single definition defines
          all the segments. */
      struct storeSegmentSpecificity : public ParserSemanticAction {
        /** Actor Constructor. */
        storeSegmentSpecificity (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (char iChar) const;
      };
  
      /** Store the parsed segment board point. */
      struct storeSegmentBoardPoint : public ParserSemanticAction {
        /** Actor Constructor. */
        storeSegmentBoardPoint (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };
  
      /** Store the parsed segment off point. */
      struct storeSegmentOffPoint : public ParserSemanticAction {
        /** Actor Constructor. */
        storeSegmentOffPoint (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the parsed segment cabin code. */
      struct storeSegmentCabinCode : public ParserSemanticAction {
        /** Actor Constructor. */
        storeSegmentCabinCode (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (char iChar) const;
      };
  
      /** Store the parsed list of class codes. */
      struct storeClasses : public ParserSemanticAction {
        /** Actor Constructor. */
        storeClasses (FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Mark the end of the flight-period parsing. */
      struct doEndFlight : public ParserSemanticAction {
        /** Actor Constructor. */
        doEndFlight (COM::WorldSchedule&, FlightPeriodStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
        /** Actor Specific Context. */
        COM::WorldSchedule& _worldSchedule;
      };
  

      /////////////////////////////////////////////////////////////////////////
      //
      //  (Boost Spirit) Grammar Definition
      //
      /////////////////////////////////////////////////////////////////////////
      /**
         AirlineCode; FlightNumber; DateRangeStart; DateRangeEnd; DOW;
         (list) BoardPoint; OffPoint; BoardTime; DateOffSet; OffTime;
                ElapsedTime;
         (list) CabinCode; Capacity;
         SegmentSpecificty (0 or 1);
           (list) (optional BoardPoint; OffPoint); CabinCode; Classes
         BA; 9; 2007-04-20; 2007-04-30; 0000011;
           LHR; BKK; 22:00; +1; 15:15; 11:15; C; 12; M; 300;
           BKK; SYD; 18:10; +1; 06:05; 08:55; C; 20; M; 250;
           0; C; CDIU; M; YHBKLMNOPQRSTVWX;
         BA; 9; 2007-04-20; 2007-04-30; 1111100;
           LHR; SIN; 22:00; +1; 15:15; 11:15; C; 15; M; 310;
           SIN; SYD; 18:10; +1; 06:05; 08:55; C; 25; M; 260;
           1; LHR; SIN; C; CDIU; M; YHBKLMNOPQRSTVWX;
              SIN; SYD; C; CDIU; M; YHBKLMNOPQRSTVWX;
              LHR; SYD; C; CDIU; M; YHBKLMNOPQRSTVWX;
         
         Grammar:
         DOW                 ::= int
         FlightKey           ::= AirlineCode ';' FlightNumber
                                 ';' DateRangeStart ';' DateRangeEnd ';' DOW
         LegKey              ::= BoardPoint ';' OffPoint
         LegDetails          ::= BoardTime ';' DateOffSet ';' OffTime
                                 ';' Elapsed
         LegCabinDetails     ::= CabinCode ';' Capacity
         Leg                 ::= LegKey ';' LegDetails (';' CabinDetails)+
         SegmentKey          ::= BoardPoint ';' OffPoint
         SegmentCabinDetails ::= CabinCode ';' Classes
         FullSegmentCabinDetails::= (';' SegmentCabinDetails)+
         GeneralSegments     ::= '0' (';' SegmentCabinDetails)+
         SpecificSegments    ::= '1' (';' SegmentKey
                                      ';' FullSegmentCabinDetails)+
         Segment             ::= GeneralSegment | SpecificSegment
         FlightPeriod        ::= FlightKey (';' Leg)+
                                 (';' Segment)+ ';' EndOfFlight
         EndOfFlight         ::= ';'
      */

      /** Grammar for the Flight-Period parser. */
      struct FlightPeriodParser : 
        public boost::spirit::grammar<FlightPeriodParser> {

        FlightPeriodParser (COM::WorldSchedule&, FlightPeriodStruct_T&);

        template <typename ScannerT>
        struct definition {
          definition (FlightPeriodParser const& self);

          // Instantiation of rules
          boost::spirit::rule<ScannerT> flight_period_list, flight_period,
            flight_period_end, flight_key, airline_code, flight_number,
            date, dow, leg, leg_key, leg_details, time, leg_cabin_details,
            segment, segment_key, full_segment_cabin_details,
            segment_cabin_details, general_segments, specific_segments;

          /** Entry point of the parser. */
          boost::spirit::rule<ScannerT> const& start() const;
        };

        // Parser Context
        COM::WorldSchedule& _worldSchedule;
        FlightPeriodStruct_T& _flightPeriod;
      };

    }


    /////////////////////////////////////////////////////////////////////////
    //
    //  Entry class for the file parser
    //
    /////////////////////////////////////////////////////////////////////////
    /** Class wrapping the initialisation and entry point of the parser.
        <br>The seemingly redundancy is used to force the instantiation of
        the actual parser, which is a templatised Boost Spirit grammar.
        Hence, the actual parser is instantiated within that class object
        code. */
    class FlightPeriodFileParser : public COM::CmdAbstract {
    public:
      /** Constructor. */
      FlightPeriodFileParser (COM::WorldSchedule& ioWorldSchedule,
                              const std::string& iFilename);

      /** Parse the input file and generate the Inventories. */
      void generateInventories ();
      
    private:
      /** Initialise. */
      void init();
      
    private:
      // Attributes
      /** File-name of the CSV-formatted schedule input file. */
      std::string _filename;

      /** Start iterator for the parser. */
      ScheduleParserHelper::iterator_t _startIterator;
      
      /** End iterator for the parser. */
      ScheduleParserHelper::iterator_t _endIterator;
      
      /** WorldSchedule. */
      COM::WorldSchedule& _worldSchedule;

      /** Flight-Period Structure. */
      FlightPeriodStruct_T _flightPeriod;
    };
    
  }
}
#endif // __LATUS_TSP_CMD_SCHEDULEPARSERHELPER_HPP
