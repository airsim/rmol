// C
#include <assert.h>
// STL
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
// Boost Spirit (Parsing)
//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute.hpp>
#include <boost/spirit/utility/functor_parser.hpp>
#include <boost/spirit/utility/loops.hpp>
#include <boost/spirit/utility/chset.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/spirit/actor/push_back_actor.hpp>
#include <boost/spirit/actor/assign_actor.hpp>
// LATUS
#include <latus/LATUS_Service.hpp>

// Type definitions
typedef char char_t;
//typedef char const* iterator_t;
typedef boost::spirit::file_iterator<char_t> iterator_t;
typedef boost::spirit::scanner<iterator_t> scanner_t;
typedef boost::spirit::rule<scanner_t> rule_t;

/** Cabin-Details. */
struct Cabin_T {
  // Attributes
  std::string _cabinCode;
  double _capacity;

  void display() const {
    std::cout << "        " << _cabinCode << " " << _capacity << ", ";
  }
};

/** List of Cabin-Detail strucutres. */
typedef std::vector<Cabin_T> CabinList_T;

/** Leg. */
struct Leg_T {
  // Attributes
  std::string _boardPoint;
  boost::posix_time::time_duration _boardTime;
  std::string _offPoint;
  boost::posix_time::time_duration _offTime;
  boost::posix_time::time_duration _elapsed;
  CabinList_T _cabinList;

  void display() const {
    std::cout << "    " << _boardPoint << " / " << _boardTime
              << " -- " << _offPoint << " / " << _offTime
              << " --> " << _elapsed
              << std::endl;
    for (CabinList_T::const_iterator itCabin = _cabinList.begin();
	 itCabin != _cabinList.end(); itCabin++) {
      const Cabin_T& lCabin = *itCabin;
      lCabin.display();
    }
    std::cout << std::endl;
  }
};

/** List of Leg strucutres. */
typedef std::vector<Leg_T> LegList_T;

/** Flight-Period. */
struct FlightPeriod_T {
  // Attributes
  std::string _airlineCode;
  unsigned int _flightNumber;
  boost::gregorian::date _dateRangeStart;
  boost::gregorian::date _dateRangeEnd;
  std::string _dow;
  LegList_T _legList;
  
  FlightPeriod_T () : _legAlreadyDefined (false), _itSeconds (0) {}

  /** Set the date from the staging details. */
  boost::gregorian::date getDate() const {
    return boost::gregorian::date (_itYear, _itMonth, _itDay);
  }

  /** Set the time from the staging details. */
  boost::posix_time::time_duration getTime() const {
    return boost::posix_time::hours (_itHours)
      + boost::posix_time::minutes (_itMinutes)
      + boost::posix_time::seconds (_itSeconds);
  }
  
  void display() const {
    std::cout << _airlineCode << _flightNumber
              << ", " << _dateRangeStart << " - " << _dateRangeEnd
              << " - " << _dow
              << std::endl;
    
    for (LegList_T::const_iterator itLeg = _legList.begin();
	 itLeg != _legList.end(); itLeg++) {
      const Leg_T& lLeg = *itLeg;
      lLeg.display();
    }
    //std::cout << "[Debug] - Staging Leg: ";
    //_itLeg.display();
    //std::cout << "[Debug] - Staging Cabin: ";
    //_itCabin.display();
  }

  /** Staging Leg (resp. Cabin) structure, gathering the result of the iteration
      on one leg (resp. cabin). */
  bool _legAlreadyDefined;
  Leg_T _itLeg;
  Cabin_T _itCabin;

  /** Staging Date. */
  unsigned int _itYear;
  unsigned int _itMonth;
  unsigned int _itDay;

  /** Staging Time. */
  unsigned int _itHours;
  unsigned int _itMinutes;
  unsigned int _itSeconds;
};

///////////////////////////////////////////////////////////////////////////////
//
//  Semantic actions
//
///////////////////////////////////////////////////////////////////////////////
namespace {
  
  /** Store the parsed airline code. */
  struct store_airline_code {
    store_airline_code (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}
    
    void operator() (iterator_t iStr, iterator_t iStrEnd) const { 
      std::string lAirlineCode (iStr, iStrEnd);
      _flightPeriod._airlineCode = lAirlineCode;
      // std::cout << "Airline code: " << lAirlineCode << std::endl;

      // As that's the beginning of a new flight, the list of legs must be reset
      _flightPeriod._legList.clear();
    }
    
    FlightPeriod_T& _flightPeriod;
  };
  
  /** Store the parsed flight number. */
  struct store_flight_number {
    store_flight_number (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}

    void operator() (unsigned int iNumber) const { 
      _flightPeriod._flightNumber = iNumber;
      // std::cout << "Flight number: " << iNumber << std::endl;
    }
    
    FlightPeriod_T& _flightPeriod;
  };
  
  /** Store the start of the date range. */
  struct store_date_range_start {
    store_date_range_start (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}
    
    void operator() (iterator_t iStr, iterator_t iStrEnd) const {
      _flightPeriod._dateRangeStart = _flightPeriod.getDate();
      // std::cout << "Date Range Start: "
      // << _flightPeriod._dateRangeStart << std::endl;
      
      // Reset the number of seconds
      _flightPeriod._itSeconds = 0;
    }
    
    FlightPeriod_T& _flightPeriod;
  };

  /** Store the end of the date range. */
  struct store_date_range_end {
    store_date_range_end (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}
    
    void operator() (iterator_t iStr, iterator_t iStrEnd) const {
      _flightPeriod._dateRangeEnd = _flightPeriod.getDate();
      // std::cout << "Date Range End: "
      // << _flightPeriod._dateRangeEnd << std::endl;
      
      // Reset the number of seconds
      _flightPeriod._itSeconds = 0;
    }
    
    FlightPeriod_T& _flightPeriod;
  };

  /** Store the DOW (day of the Week). */
  struct store_dow {
    store_dow (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}

    void operator() (iterator_t iStr, iterator_t iStrEnd) const {
      std::string lDow (iStr, iStrEnd);
      _flightPeriod._dow = lDow;
      // std::cout << "DOW: " << lDow << std::endl;
    }
    
    FlightPeriod_T& _flightPeriod;
  };

  /** Store the parsed board point. */
  struct store_board_point {
    store_board_point (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}

    void operator() (iterator_t iStr, iterator_t iStrEnd) const {
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
      
      // As that's the beginning of a new leg, the list of cabins must be reset
      _flightPeriod._itLeg._cabinList.clear();
    }
    
    FlightPeriod_T& _flightPeriod;
  };
  
  /** Store the parsed off point. */
  struct store_off_point {
    store_off_point (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}

    void operator() (iterator_t iStr, iterator_t iStrEnd) const {
      std::string lOffPoint (iStr, iStrEnd);
      _flightPeriod._itLeg._offPoint = lOffPoint;
      // std::cout << "Off point: " << lOffPoint << std::endl;
    }
    
    FlightPeriod_T& _flightPeriod;
  };

  /** Store the board time. */
  struct store_board_time {
    store_board_time (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}
    
    void operator() (iterator_t iStr, iterator_t iStrEnd) const {
      _flightPeriod._itLeg._boardTime = _flightPeriod.getTime();
      
      // Reset the number of seconds
      _flightPeriod._itSeconds = 0;
    }
    
    FlightPeriod_T& _flightPeriod;
  };

  /** Store the off time. */
  struct store_off_time {
    store_off_time (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}
    
    void operator() (iterator_t iStr, iterator_t iStrEnd) const {
      _flightPeriod._itLeg._offTime = _flightPeriod.getTime();
      
      // Reset the number of seconds
      _flightPeriod._itSeconds = 0;
    }
    
    FlightPeriod_T& _flightPeriod;
  };

  /** Store the elapsed time. */
  struct store_elapsed_time {
    store_elapsed_time (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}
    
    void operator() (iterator_t iStr, iterator_t iStrEnd) const {
      _flightPeriod._itLeg._elapsed = _flightPeriod.getTime();
      
      // Reset the number of seconds
      _flightPeriod._itSeconds = 0;
    }
    
    FlightPeriod_T& _flightPeriod;
  };

  /** Store the parsed cabin code. */
  struct store_cabin_code {
    store_cabin_code (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}
    
    void operator() (char iChar) const { 
      _flightPeriod._itCabin._cabinCode = iChar; 
      // std::cout << "Cabin code: " << iChar << std::endl;
    }

    FlightPeriod_T& _flightPeriod;
  };
  
  /** Store the parsed capacity. */
  struct store_capacity {
    store_capacity (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}
    
    void operator() (double iReal) const { 
      _flightPeriod._itCabin._capacity = iReal; 
      // std::cout << "Capacity: " << iReal << std::endl;

      // The capacity is the last (according to arrival order) detail
      // of the cabin. Hence, when a capacity is parsed, it means that
      // the full cabin details have already been parsed as well: the
      // cabin can thus be added to the leg.
      _flightPeriod._itLeg._cabinList.push_back (_flightPeriod._itCabin);
    }

    FlightPeriod_T& _flightPeriod;
  };
  
  /** Mark the end of the flight-period parsing. */
  struct do_end_flight {
    do_end_flight (FlightPeriod_T& ioFlightPeriod)
      : _flightPeriod (ioFlightPeriod) {}
    
    // void operator() (char iChar) const {
    void operator() (iterator_t iStr, iterator_t iStrEnd) const {
      // std::cout << "End of Flight-Period " << std::endl;

      assert (_flightPeriod._legAlreadyDefined == true);
      _flightPeriod._legList.push_back (_flightPeriod._itLeg);
      
      // The lists of legs and cabins must be reset
      _flightPeriod._legAlreadyDefined = false;
      _flightPeriod._itLeg._cabinList.clear();

      // Display the result
      _flightPeriod.display();
    }

    FlightPeriod_T& _flightPeriod;
  };
}

// /////////// Utilities /////////////
/** 2-digit-integer parser */
boost::spirit::uint_parser<int, 10, 2, 2> uint2_p;
/** 4-digit-integer parser */
boost::spirit::uint_parser<int, 10, 4, 4> uint4_p;
/** Up-to-4-digit-integer parser */
boost::spirit::uint_parser<int, 10, 1, 4> uint1_4_p;

///////////////////////////////////////////////////////////////////////////////
//
//  Our calculator grammar (using subrules)
//
///////////////////////////////////////////////////////////////////////////////
    /**
       AirlineCode; FlightNumber; DateRangeStart; DateRangeEnd; DOW;
        (list) BoardPoint; OffPoint; BoardTime; OffTime; ElapsedTime;
                 (list)  CabinCode; Capacity;
       BA; 9; 2007-04-20; 2007-04-30; 0000011;
               LHR; BKK; 22:00; 15:15; 11:15; C; 12; M; 300;
               BKK; SYD; 18:10; 06:05; 08:55; C; 20; M; 250;
       BA; 9; 2007-04-20; 2007-04-30; 1111100;
               LHR; SIN; 22:00; 15:15; 11:15; C; 15; M; 310;
               SIN; SYD; 18:10; 06:05; 08:55; C; 25; M; 260;

       Grammar:
        DOW          ::= int
        FlightKey    ::= AirlineCode ';' FlightNumber
                         ';' DateRangeStart ';' DateRangeEnd ';' DOW
        LegKey       ::= BoardPoint ';' OffPoint
        LegDetails   ::= BoardTime ';' OffTime ';' Elapsed
        CabinDetails ::= CabinCode ';' Capacity
        Leg          ::= LegKey ';' LegDetails (';' CabinDetails)+
        FlightPeriod ::= FlightKey (';' Leg)+ EndOfFlight
        EndOfFlight  ::= ';'
    */

using namespace boost::spirit;

/** Grammar for the Flight-Period parser. */
struct FlightPeriodParser : 
  public boost::spirit::grammar<FlightPeriodParser> {

  FlightPeriodParser (FlightPeriod_T& ioFlightPeriod) 
  : _flightPeriod (ioFlightPeriod) {
  }

  template <typename ScannerT>
  struct definition {
    definition (FlightPeriodParser const& self) {

      flight_period_list = *( flight_period )
        ;
      
      flight_period = flight_key
        >> +( ';' >> leg )
        >> flight_period_end[do_end_flight(self._flightPeriod)]
        ;

      flight_period_end =
        boost::spirit::ch_p(';')
        ;
      
      flight_key = airline_code
        >> ';' >> flight_number
        >> ';' >> date[store_date_range_start(self._flightPeriod)]
        >> ';' >> date[store_date_range_end(self._flightPeriod)]
        >> ';' >> dow[store_dow(self._flightPeriod)]
        ;

      airline_code =
        lexeme_d[ (repeat_p(2,3)[chset_p("0-9A-Z")])[store_airline_code(self._flightPeriod)] ]
        ;
      
      flight_number =
        lexeme_d[ limit_d(0u, 9999u)[uint1_4_p][store_flight_number(self._flightPeriod)] ]
        ;

      date =
        lexeme_d[ limit_d(2000u,2099u)[uint4_p][assign_a(self._flightPeriod._itYear)]
                  >> '-' >> limit_d(1u,12u)[uint2_p][assign_a(self._flightPeriod._itMonth)]
                  >> '-' >> limit_d(1u,31u)[uint2_p][assign_a(self._flightPeriod._itDay)] ]
        ;

      dow =
        lexeme_d[ repeat_p(7)[chset_p("0-1")] ]
        ;
      
      leg = leg_key >> ';' >> leg_details >> +( ';' >> cabin_details )
        ;
	 
      leg_key =
        (repeat_p(3)[chset_p("0-9A-Z")])[store_board_point(self._flightPeriod)]
        >> ';'
        >> (repeat_p(3)[chset_p("0-9A-Z")])[store_off_point(self._flightPeriod)]
        ;
	 
      leg_details =
        time[store_board_time(self._flightPeriod)]
        >> ';' 
        >> time[store_off_time(self._flightPeriod)]
        >> ';'
        >> time[store_elapsed_time(self._flightPeriod)]
        ;

      time = lexeme_d[ limit_d(0u,23u)[uint2_p][assign_a(self._flightPeriod._itHours)]
                       >> ':' >> limit_d(0u,59u)[uint2_p][assign_a(self._flightPeriod._itMinutes)]
                       >> !(':' >> limit_d(0u,59u)[uint2_p][assign_a(self._flightPeriod._itSeconds)]) ]
        ;

      cabin_details = (chset_p("A-Z"))[store_cabin_code(self._flightPeriod)]
        >> ';' >> (boost::spirit::ureal_p)[store_capacity(self._flightPeriod)]
        ;

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
      BOOST_SPIRIT_DEBUG_NODE (cabin_details);
    }
    
    boost::spirit::rule<ScannerT> flight_period_list, flight_period,
                   flight_period_end, flight_key, airline_code, flight_number,
                   date, dow, leg, leg_key, leg_details, time, cabin_details;

    boost::spirit::rule<ScannerT> const& start() const { return flight_period_list; }
  };

  FlightPeriod_T& _flightPeriod;
};

// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {
    
    // File to be parsed
    std::string lFilename ("../samples/world_schedule.csv");
    
    // Read the command-line parameters
    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> lFilename;
    }

    // Open the file
    iterator_t lFileIterator (lFilename);
    if (!lFileIterator) {
      std::cerr << "The file " << lFilename << " can not be open." << std::endl;
    }

    // Create an EOF iterator
    iterator_t lFileIteratorEnd = lFileIterator.make_end();
    
    // Instantiate the structure that will hold the result of the parsing.
    FlightPeriod_T lFlightPeriod;
    FlightPeriodParser lFlightPeriodParser (lFlightPeriod);
    boost::spirit::parse_info<iterator_t> info =
      boost::spirit::parse (lFileIterator, lFileIteratorEnd,
                            lFlightPeriodParser, 
                            boost::spirit::space_p);

    std::cout << "-------------------------" << std::endl;
    if (info.full) {
      std::cout << "Parsing succeeded" << std::endl;
      
    } else {
      std::cout << "Parsing failed" << std::endl;
    }
    std::cout << "-------------------------" << std::endl;

  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;
}
