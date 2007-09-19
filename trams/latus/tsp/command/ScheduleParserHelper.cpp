// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// Boost Spirit (Parsing)
//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute.hpp>
#include <boost/spirit/utility/functor_parser.hpp>
#include <boost/spirit/utility/loops.hpp>
#include <boost/spirit/utility/chset.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/spirit/actor/push_back_actor.hpp>
#include <boost/spirit/actor/assign_actor.hpp>
// LATUS Common
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS TSP
#include <latus/tsp/command/ScheduleParserHelper.hpp>
#include <latus/tsp/command/InventoryGenerator.hpp>

namespace LATUS {

  namespace TSP {

    namespace ScheduleParserHelper {
      
      // //////////////////////////////////////////////////////////////////////
      //
      //  Semantic actions
      //
      // //////////////////////////////////////////////////////////////////////

      ParserSemanticAction::
      ParserSemanticAction (FlightPeriodStruct_T& ioFlightPeriod)
        : _flightPeriod (ioFlightPeriod) {
      }      

      // //////////////////////////////////////////////////////////////////////
      storeAirlineCode::
      storeAirlineCode (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeAirlineCode::operator() (iterator_t iStr,
                                         iterator_t iStrEnd) const { 
        const std::string lAirlineCode (iStr, iStrEnd);
        _flightPeriod._airlineCode = lAirlineCode;
        
        // std::cout << "Airline code: " << lAirlineCode << std::endl;
        
        // As that's the beginning of a new flight, the list of legs
        // must be reset
        _flightPeriod._legList.clear();
      }

      // //////////////////////////////////////////////////////////////////////
      storeFlightNumber::
      storeFlightNumber (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeFlightNumber::operator() (unsigned int iNumber) const { 
        _flightPeriod._flightNumber = iNumber;
        // std::cout << "Flight number: " << iNumber << std::endl;
      }

      // //////////////////////////////////////////////////////////////////////
      storeDateRangeStart::
      storeDateRangeStart (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeDateRangeStart::operator() (iterator_t iStr,
                                            iterator_t iStrEnd) const {
        _flightPeriod._dateRangeStart = _flightPeriod.getDate();
        // std::cout << "Date Range Start: "
        // << _flightPeriod._dateRangeStart << std::endl;
        
        // Reset the number of seconds
        _flightPeriod._itSeconds = 0;
      }
      
      // //////////////////////////////////////////////////////////////////////
      storeDateRangeEnd::
      storeDateRangeEnd (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeDateRangeEnd::operator() (iterator_t iStr,
                                          iterator_t iStrEnd) const {
        _flightPeriod._dateRangeEnd = _flightPeriod.getDate();
        // std::cout << "Date Range End: "
        // << _flightPeriod._dateRangeEnd << std::endl;

        // Transform the date pair (i.e., the date range) into a date period
        _flightPeriod._dateRange =
          COM::DatePeriod_T (_flightPeriod._dateRangeStart,
                             _flightPeriod._dateRangeEnd);
        
        // Reset the number of seconds
        _flightPeriod._itSeconds = 0;
      }

      // //////////////////////////////////////////////////////////////////////
      storeDow::storeDow (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeDow::operator() (iterator_t iStr, iterator_t iStrEnd) const {
        std::string lDow (iStr, iStrEnd);
        _flightPeriod._dow = lDow;
        // std::cout << "DOW: " << lDow << std::endl;
      }
      
      // //////////////////////////////////////////////////////////////////////
      storeLegBoardPoint::
      storeLegBoardPoint (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeLegBoardPoint::operator() (iterator_t iStr,
                                           iterator_t iStrEnd) const {
        std::string lBoardPoint (iStr, iStrEnd);
        // std::cout << "Board point: " << lBoardPoint << std::endl;

        // If a leg has already been parsed, add it to the FlightPeriod
        if (_flightPeriod._legAlreadyDefined == true) {
          _flightPeriod._legList.push_back (_flightPeriod._itLeg);
        } else {
          _flightPeriod._legAlreadyDefined = true;
        }
        
        // Set the (new) board point
        _flightPeriod._itLeg._boardPoint = lBoardPoint;
      
        // As that's the beginning of a new leg, the list of cabins
        // must be reset
        _flightPeriod._itLeg._cabinList.clear();

        // Add the airport code if it is not already stored in the airport lists
        _flightPeriod.addAirport (lBoardPoint);
      }

      // //////////////////////////////////////////////////////////////////////
      storeLegOffPoint::
      storeLegOffPoint (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeLegOffPoint::operator() (iterator_t iStr,
                                         iterator_t iStrEnd) const {
        std::string lOffPoint (iStr, iStrEnd);
        _flightPeriod._itLeg._offPoint = lOffPoint;
        // std::cout << "Off point: " << lOffPoint << std::endl;

        // Add the airport code if it is not already stored in the airport lists
        _flightPeriod.addAirport (lOffPoint);
      }

      // //////////////////////////////////////////////////////////////////////
      storeBoardTime::
      storeBoardTime (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeBoardTime::operator() (iterator_t iStr,
                                       iterator_t iStrEnd) const {
        _flightPeriod._itLeg._boardTime = _flightPeriod.getTime();
        
        // Reset the number of seconds
        _flightPeriod._itSeconds = 0;

        // Reset the date off-set
        _flightPeriod._dateOffSet = 0;
      }

      // //////////////////////////////////////////////////////////////////////
      void storeOffTime::operator() (iterator_t iStr,
                                     iterator_t iStrEnd) const {
        _flightPeriod._itLeg._offTime = _flightPeriod.getTime();
        
        // Reset the number of seconds
        _flightPeriod._itSeconds = 0;

        // As the board date off set is optional, it can be set only afterwards,
        // based on the staging date off-set value (_flightPeriod._dateOffSet).
        const COM::DateOffSet_T lDateOffSet (_flightPeriod._dateOffSet);
        _flightPeriod._itLeg._boardDateOffSet = lDateOffSet;
      }

      // //////////////////////////////////////////////////////////////////////
      storeOffTime::
      storeOffTime (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      storeElapsedTime::
      storeElapsedTime (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeElapsedTime::operator() (iterator_t iStr,
                                           iterator_t iStrEnd) const {
        _flightPeriod._itLeg._elapsed = _flightPeriod.getTime();
        
        // Reset the number of seconds
        _flightPeriod._itSeconds = 0;

        // As the board date off set is optional, it can be set only afterwards,
        // based on the staging date off-set value (_flightPeriod._dateOffSet).
        const COM::DateOffSet_T lDateOffSet (_flightPeriod._dateOffSet);
        _flightPeriod._itLeg._offDateOffSet = lDateOffSet;
      }

      // //////////////////////////////////////////////////////////////////////
      storeLegCabinCode::
      storeLegCabinCode (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeLegCabinCode::operator() (char iChar) const { 
        _flightPeriod._itLegCabin._cabinCode = iChar; 
        // std::cout << "Cabin code: " << iChar << std::endl;
      }

      // //////////////////////////////////////////////////////////////////////
      storeCapacity::
      storeCapacity (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeCapacity::operator() (double iReal) const { 
        _flightPeriod._itLegCabin._capacity = iReal; 
        // std::cout << "Capacity: " << iReal << std::endl;

        // The capacity is the last (according to the arrival order
        // within the schedule input file) detail of the leg cabin. Hence,
        // when a capacity is parsed, it means that the full cabin
        // details have already been parsed as well: the cabin can
        // thus be added to the leg.
        _flightPeriod._itLeg._cabinList.push_back (_flightPeriod._itLegCabin);
      }

      // //////////////////////////////////////////////////////////////////////
      storeSegmentSpecificity::
      storeSegmentSpecificity (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeSegmentSpecificity::operator() (char iChar) const {
        if (iChar == '0') {
          _flightPeriod._areSegmentDefinitionsSpecific = false;
        } else {
          _flightPeriod._areSegmentDefinitionsSpecific = true;
        }

        // Do a few sanity checks: the two lists should get exactly the same
        // content (in terms of airport codes). The only difference is that one
        // is a STL set, and the other a STL vector.
        assert (_flightPeriod._airportList.size()
                == _flightPeriod._airportOrderedList.size());
        assert (_flightPeriod._airportList.size() >= 2);
        
        // Since all the legs have now been parsed, we get all the airports
        // and the segments may be built.
        _flightPeriod.buildSegments();
      }
      
      // //////////////////////////////////////////////////////////////////////
      storeSegmentBoardPoint::
      storeSegmentBoardPoint (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeSegmentBoardPoint::operator() (iterator_t iStr,
                                               iterator_t iStrEnd) const {
        std::string lBoardPoint (iStr, iStrEnd);
        _flightPeriod._itSegment._boardPoint = lBoardPoint;
        // std::cout << "Board point: " << lBoardPoint << std::endl;
      }

      // //////////////////////////////////////////////////////////////////////
      storeSegmentOffPoint::
      storeSegmentOffPoint (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeSegmentOffPoint::operator() (iterator_t iStr,
                                         iterator_t iStrEnd) const {
        std::string lOffPoint (iStr, iStrEnd);
        _flightPeriod._itSegment._offPoint = lOffPoint;
        // std::cout << "Off point: " << lOffPoint << std::endl;
      }

      // //////////////////////////////////////////////////////////////////////
      storeSegmentCabinCode::
      storeSegmentCabinCode (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeSegmentCabinCode::operator() (char iChar) const { 
        _flightPeriod._itSegmentCabin._cabinCode = iChar; 
        // std::cout << "Cabin code: " << iChar << std::endl;
      }

      // //////////////////////////////////////////////////////////////////////
      storeClasses::
      storeClasses (FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeClasses::operator() (iterator_t iStr,
                                     iterator_t iStrEnd) const {
        std::string lClasses (iStr, iStrEnd);
        _flightPeriod._itSegmentCabin._classes = lClasses;
        // std::cout << "Classes: " << lClasses << std::endl;

        // The list of classes is the last (according to the arrival order
        // within the schedule input file) detail of the segment cabin. Hence,
        // when a list of classes is parsed, it means that the full segment
        // cabin details have already been parsed as well: the segment cabin
        // can thus be added to the segment.
        if (_flightPeriod._areSegmentDefinitionsSpecific == true) {
          _flightPeriod.addSegmentCabin (_flightPeriod._itSegment,
                                         _flightPeriod._itSegmentCabin);
        } else {
          _flightPeriod.addSegmentCabin (_flightPeriod._itSegmentCabin);
        }
      }

      // //////////////////////////////////////////////////////////////////////
      doEndFlight::
      doEndFlight (COM::WorldSchedule& ioWorldSchedule,
                   FlightPeriodStruct_T& ioFlightPeriod)
        : ParserSemanticAction (ioFlightPeriod),
          _worldSchedule (ioWorldSchedule) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      // void doEndFlight::operator() (char iChar) const {
      void doEndFlight::operator() (iterator_t iStr,
                                      iterator_t iStrEnd) const {
        // std::cout << "End of Flight-Period " << std::endl;

        assert (_flightPeriod._legAlreadyDefined == true);
        _flightPeriod._legList.push_back (_flightPeriod._itLeg);
        
        // The lists of legs and cabins must be reset
        _flightPeriod._legAlreadyDefined = false;
        _flightPeriod._itLeg._cabinList.clear();
        
        // DEBUG: Display the result
        LATUS_LOG_DEBUG ("FlightPeriod: " << _flightPeriod.describe());

        // Create the FlightDate BOM objects, and potentially the intermediary
        // objects (e.g., Inventory).
        InventoryGenerator::createFlightDates (_worldSchedule, _flightPeriod);
      }

      
      // ///////////////////////////////////////////////////////////////////////
      //
      //  Utility Parsers
      //
      // ///////////////////////////////////////////////////////////////////////
      /** 1-digit-integer parser */
      typedef boost::spirit::int_parser<int, 10, 1, 1> int1_p_t;
      int1_p_t int1_p;
    
      /** 2-digit-integer parser */
      typedef boost::spirit::uint_parser<int, 10, 2, 2> uint2_p_t;
      uint2_p_t uint2_p;
    
      /** 4-digit-integer parser */
      typedef boost::spirit::uint_parser<int, 10, 4, 4> uint4_p_t;
      uint4_p_t uint4_p;
    
      /** Up-to-4-digit-integer parser */
      typedef boost::spirit::uint_parser<int, 10, 1, 4> uint1_4_p_t;
      uint1_4_p_t uint1_4_p;

      /** Sequence of (capital) alphabetic characters: chset_p("A-Z") */
      boost::spirit::chset<char_t> alpha_cap_set_p ("A-Z");
      
      /** Sequence of (capital) alpha-numeric characters: chset_p("0-9A-Z") */
      boost::spirit::chset<char_t> alpha_cap_num_set_p ("0-9A-Z");
      
      /** (Repeating) sequence of a given number of characters:
          repeat_p(min, max) */
      typedef boost::spirit::impl::loop_traits<boost::spirit::chset<char_t>,
                                               unsigned int,
                                               unsigned int>::type repeat_p_t;

      /** Airline Code Parser: repeat_p(2,3)[chset_p("0-9A-Z")] */
      repeat_p_t airline_code_p (alpha_cap_num_set_p.derived(), 2, 3);
      
      /** Flight Number Parser: limit_d(0u, 9999u)[uint1_4_p] */
      boost::spirit::bounded<uint1_4_p_t,
                             unsigned int> flight_number_p (uint1_4_p.derived(),
                                                            0u, 9999u);

      /** Year Parser: limit_d(2000u, 2099u)[uint4_p] */
      boost::spirit::bounded<uint4_p_t, unsigned int> year_p (uint4_p.derived(),
                                                              2000u, 2099u);
      
      /** Month Parser: limit_d(1u, 12u)[uint2_p] */
      boost::spirit::bounded<uint2_p_t,
                             unsigned int> month_p (uint2_p.derived(), 1u, 12u);

      /** Day Parser: limit_d(1u, 31u)[uint2_p] */
      boost::spirit::bounded<uint2_p_t, unsigned int> day_p (uint2_p.derived(),
                                                             1u, 31u);

      /** Sequence of bits (0 or 1): chset_p("0-1") */
      boost::spirit::chset<char_t> bit_set_p ("0-1");
      
      /** DOW (Day-Of-the-Week) Parser: repeat_p(7)[chset_p("0-1")] */
      repeat_p_t dow_p (bit_set_p.derived(), 7, 7);

      /** Airport Parser: repeat_p(3)[chset_p("0-9A-Z")] */
      repeat_p_t airport_p (alpha_cap_num_set_p.derived(), 3, 3);
      
      /** Hour Parser: limit_d(0u, 23u)[uint2_p] */
      boost::spirit::bounded<uint2_p_t,
                             unsigned int> hours_p (uint2_p.derived(), 0u, 23u);

      /** Minute Parser: limit_d(0u, 59u)[uint2_p] */
      boost::spirit::bounded<uint2_p_t,
                             unsigned int> minutes_p (uint2_p.derived(),
                                                      0u, 59u);

      /** Second Parser: limit_d(0u, 59u)[uint2_p] */
      boost::spirit::bounded<uint2_p_t,
                             unsigned int> seconds_p (uint2_p.derived(),
                                                      0u, 59u);

      /** Cabin Code Parser: chset_p("A-Z") */
      boost::spirit::chset<char_t> cabin_code_p ("A-Z");
      
      /** Class Code List Parser: repeat_p(1,26)[chset_p("A-Z")] */
      repeat_p_t class_code_list_p (alpha_cap_set_p.derived(), 1, 26);


      /////////////////////////////////////////////////////////////////////////
      //
      //  (Boost Spirit) Grammar Definition
      //
      /////////////////////////////////////////////////////////////////////////

      // //////////////////////////////////////////////////////////////////////
      FlightPeriodParser::
      FlightPeriodParser (COM::WorldSchedule& ioWorldSchedule,
                          FlightPeriodStruct_T& ioFlightPeriod) 
        : _worldSchedule (ioWorldSchedule), _flightPeriod (ioFlightPeriod) {
      }

      // //////////////////////////////////////////////////////////////////////
      template<typename ScannerT>
      FlightPeriodParser::definition<ScannerT>::
      definition (FlightPeriodParser const& self) {

        flight_period_list = *( boost::spirit::comment_p("//")
                              | boost::spirit::comment_p("/*", "*/")
                              | flight_period )
          ;
      
        flight_period = flight_key
          >> +( ';' >> leg )
          >> +( ';' >> segment )
          >> flight_period_end[doEndFlight(self._worldSchedule,
                                           self._flightPeriod)]
          ;

        flight_period_end =
          boost::spirit::ch_p(';')
          ;
      
        flight_key = airline_code
          >> ';' >> flight_number
          >> ';' >> date[storeDateRangeStart(self._flightPeriod)]
          >> ';' >> date[storeDateRangeEnd(self._flightPeriod)]
          >> ';' >> dow[storeDow(self._flightPeriod)]
          ;

        airline_code =
          boost::spirit::lexeme_d[
                   (airline_code_p)[storeAirlineCode(self._flightPeriod)]
                                  ]
              ;
        
        flight_number =
          boost::spirit::lexeme_d[
                   (flight_number_p)[storeFlightNumber(self._flightPeriod)]
                                  ]
          ;

        date =
          boost::spirit::lexeme_d[
              (year_p)[boost::spirit::assign_a(self._flightPeriod._itYear)]
              >> '-'
              >> (month_p)[boost::spirit::assign_a(self._flightPeriod._itMonth)]
              >> '-'
              >> (day_p)[boost::spirit::assign_a(self._flightPeriod._itDay)]
                                  ]
          ;

        dow = boost::spirit::lexeme_d[ dow_p ]
          ;
      
        leg = leg_key >> ';' >> leg_details >> +( ';' >> leg_cabin_details )
          ;
	 
        leg_key =
          (airport_p)[storeLegBoardPoint(self._flightPeriod)]
          >> ';'
          >> (airport_p)[storeLegOffPoint(self._flightPeriod)]
          ;
	 
        leg_details =
          time[storeBoardTime(self._flightPeriod)]
            >> !(date_offset)
            >> ';'
            >> time[storeOffTime(self._flightPeriod)]
            >> !(date_offset)
            >> ';'
            >> time[storeElapsedTime(self._flightPeriod)]
          ;
        
        time =
          boost::spirit::lexeme_d[
           (hours_p)[boost::spirit::assign_a(self._flightPeriod._itHours)]
           >> ':'
           >> (minutes_p)[boost::spirit::assign_a(self._flightPeriod._itMinutes)]
           >> !(':' >> (seconds_p)[boost::spirit::assign_a(self._flightPeriod._itSeconds)])
          ]
          ;

        date_offset =
          boost::spirit::ch_p('/')
          >> (int1_p)[boost::spirit::assign_a(self._flightPeriod._dateOffSet)]
          ;          
        
        leg_cabin_details =
          (cabin_code_p)[storeLegCabinCode(self._flightPeriod)]
          >> ';' >> (boost::spirit::ureal_p)[storeCapacity(self._flightPeriod)]
          ;
        
        segment_key =
          (airport_p)[storeSegmentBoardPoint(self._flightPeriod)]
          >> ';'
          >> (airport_p)[storeSegmentOffPoint(self._flightPeriod)]
          ;
	 
        segment =
          general_segments | specific_segments
          ;

        general_segments =
          boost::spirit::ch_p('0')[storeSegmentSpecificity(self._flightPeriod)]
          >> +(';' >> segment_cabin_details)
          ;

        specific_segments =
          boost::spirit::ch_p('1')[storeSegmentSpecificity(self._flightPeriod)]
          >> +(';' >> segment_key >> full_segment_cabin_details)
          ;

        full_segment_cabin_details =
          +(';' >> segment_cabin_details)
          ;
        
        segment_cabin_details =
          (cabin_code_p)[storeSegmentCabinCode(self._flightPeriod)]
          >> ';' >> (class_code_list_p)[storeClasses(self._flightPeriod)]
          ;
        
        // BOOST_SPIRIT_DEBUG_NODE (FlightPeriodParser);
        BOOST_SPIRIT_DEBUG_NODE (flight_period_list);
        BOOST_SPIRIT_DEBUG_NODE (flight_period);
        BOOST_SPIRIT_DEBUG_NODE (flight_period_end);
        BOOST_SPIRIT_DEBUG_NODE (flight_key);
        BOOST_SPIRIT_DEBUG_NODE (airline_code);
        BOOST_SPIRIT_DEBUG_NODE (flight_number);
        BOOST_SPIRIT_DEBUG_NODE (date);
        BOOST_SPIRIT_DEBUG_NODE (dow);
        BOOST_SPIRIT_DEBUG_NODE (leg);
        BOOST_SPIRIT_DEBUG_NODE (leg_key);
        BOOST_SPIRIT_DEBUG_NODE (leg_details);
        BOOST_SPIRIT_DEBUG_NODE (time);
        BOOST_SPIRIT_DEBUG_NODE (date_offset);
        BOOST_SPIRIT_DEBUG_NODE (leg_cabin_details);
        BOOST_SPIRIT_DEBUG_NODE (segment);
        BOOST_SPIRIT_DEBUG_NODE (segment_key);
        BOOST_SPIRIT_DEBUG_NODE (general_segments);
        BOOST_SPIRIT_DEBUG_NODE (specific_segments);
        BOOST_SPIRIT_DEBUG_NODE (full_segment_cabin_details);
        BOOST_SPIRIT_DEBUG_NODE (segment_cabin_details);
      }

      // //////////////////////////////////////////////////////////////////////
      template<typename ScannerT>
      boost::spirit::rule<ScannerT> const&
      FlightPeriodParser::definition<ScannerT>::start() const {
        return flight_period_list;
      }
    
    }


    /////////////////////////////////////////////////////////////////////////
    //
    //  Entry class for the file parser
    //
    /////////////////////////////////////////////////////////////////////////

    // //////////////////////////////////////////////////////////////////////
    FlightPeriodFileParser::
    FlightPeriodFileParser (COM::WorldSchedule& ioWorldSchedule,
                            const std::string& iFilename)
      : _worldSchedule (ioWorldSchedule), _filename (iFilename) {
      init();
    }

    // //////////////////////////////////////////////////////////////////////
    void FlightPeriodFileParser::init() {
      // Open the file
      _startIterator = ScheduleParserHelper::iterator_t (_filename);

      // Check the filename exists and can be open
      if (!_startIterator) {
        std::cerr << "The file " << _filename << " can not be open."
                  << std::endl;
      }

      // Create an EOF iterator
      _endIterator = _startIterator.make_end();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FlightPeriodFileParser::generateInventories () {

      LATUS_LOG_DEBUG ("Parsing schedule input file: " << _filename);

      // Initialise the parser (grammar) with the helper/staging structure.
      ScheduleParserHelper::FlightPeriodParser lFPParser (_worldSchedule,
                                                          _flightPeriod);
      
      // Launch the parsing of the file and, thanks to the doEndFlight
      // call-back structure, the building of the whole WorldSchedule BOM
      // (i.e., including Inventory, FlightDate, LegDate, SegmentDate, etc.)
      boost::spirit::parse_info<ScheduleParserHelper::iterator_t> info =
        boost::spirit::parse (_startIterator, _endIterator, lFPParser, 
                              boost::spirit::space_p);

      if (info.full) {
        LATUS_LOG_DEBUG ("Parsing of schedule input file: " << _filename
                         << " succeeded.");
        
      } else {
        // TODO: decide whether to throw an exception
        LATUS_LOG_ERROR ("Parsing of schedule input file: " << _filename
                         << " failed.");
      }
     }
    
  }
}
