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
#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute.hpp>
#include <boost/spirit/utility/functor_parser.hpp>
#include <boost/spirit/actor/push_back_actor.hpp>
#include <boost/spirit/actor/assign_actor.hpp>
// LATUS
#include <latus/LATUS_Service.hpp>

#define BOOST_SPIRIT_DEBUG        // define this for debug output

// Type definitions
/** List of numbers. */
typedef std::vector<double> NumberList_T;

using namespace boost::spirit;

/** Cabin-Details. */
struct Cabin_T {
  std::string _cabinCode;
  double _capacity;
  void display() const {
    std::cout << _cabinCode << ", " << _capacity << std::endl;
  }
};

/** Leg-Cabin. */
struct LegCabin_T {
  std::string _boardPoint;
  std::string _offPoint;
  Cabin_T _cabinDetails;
  void display() const {
    std::cout << _boardPoint << "-" << _offPoint << std::endl;
    _cabinDetails.display();
  }
};

/** List of Leg-Cabin strucutres. */
typedef std::vector<LegCabin_T> LegCabinList_T;

/** Flight-Period. */
struct FlightPeriod_T {
  void display() const {
    std::cout << _airlineCode << _flightNumber << std::endl;
    for (LegCabinList_T::const_iterator itLegCabin = _legCabinList.begin();
	 itLegCabin != _legCabinList.end(); itLegCabin++) {
      const LegCabin_T& lLegCabin = *itLegCabin;
      lLegCabin.display();
    }
    std::cout << "[Debug] - Staging Cabin: ";
    _itCabin.display();
  }
  std::string _airlineCode;
  unsigned int _flightNumber;
  LegCabinList_T _legCabinList;
  /** Staging Leg-Cabin structure (gathering the result of the iteration
      on one leg-cabin). */
  LegCabin_T _itLegCabin;
  Cabin_T _itCabin;
};

///////////////////////////////////////////////////////////////////////////////
//
//  Semantic actions
//
///////////////////////////////////////////////////////////////////////////////
namespace {
  void do_leg (char const* iStr, char const* iStrEnd) { 
    std::string lYearStr (iStr, iStrEnd);
    std::cout << "LEG: " << lYearStr << std::endl; 
  }
  void do_legkey (char const* iStr, char const* iStrEnd) { 
    std::string lYearStr (iStr, iStrEnd);
    std::cout << "LEGKEY: " << lYearStr << std::endl; 
  }
  void do_airline (char const* iStr, char const* iStrEnd) { 
    std::string lYearStr (iStr, iStrEnd);
    std::cout << "AIRLINE_CODE: " << lYearStr << std::endl; 
  }
  void do_boardPoint (char const* iStr, char const* iStrEnd) { 
    std::string lBoardPoint (iStr, iStrEnd);
    std::cout << "Board Point: " << lBoardPoint << std::endl; 
  }
  void do_offPoint (char const* iStr, char const* iStrEnd) { 
    std::string lOffPoint (iStr, iStrEnd);
    std::cout << "Off Point: " << lOffPoint << std::endl; 
  }
  void do_flightNumber (unsigned int iNumber) { 
    std::cout << "Flight Number: " << iNumber << std::endl; 
  }
  void do_dow (char const* iStr, char const* iStrEnd) { 
    std::string lYearStr (iStr, iStrEnd);
    std::cout << "DOW: " << lYearStr << std::endl; 
  }
  void do_boardDate (char const* iStr, char const* iStrEnd) { 
    std::string lBoardDate (iStr, iStrEnd);
    std::cout << "Board Date: " << lBoardDate << std::endl; 
  }
  void do_offDate (char const* iStr, char const* iStrEnd) { 
    std::string lOffDate (iStr, iStrEnd);
    std::cout << "Off Date: " << lOffDate << std::endl; 
  }
  void do_boardTime (char const* iStr, char const* iStrEnd) { 
    std::string lBoardTime (iStr, iStrEnd);
    std::cout << "Board Time: " << lBoardTime << std::endl; 
  }
  void do_offTime (char const* iStr, char const* iStrEnd) { 
    std::string lOffTime (iStr, iStrEnd);
    std::cout << "Off Time: " << lOffTime << std::endl; 
  }
  void do_elapsed (char const* iStr, char const* iStrEnd) { 
    std::string lElapsed (iStr, iStrEnd);
    std::cout << "Elpased: " << lElapsed << std::endl; 
  }
  void do_cabin (char iChar) { 
    std::cout << "Cabin Code: " << iChar << std::endl; 
  }
  void do_capacity (double iReal) { 
    std::cout << "Capacity: " << iReal << std::endl; 
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Cabin Parser
//
///////////////////////////////////////////////////////////////////////////////
struct FlightPeriodClosure : 
  boost::spirit::closure<FlightPeriodClosure, FlightPeriod_T> {
  member1 val;
};

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
               BKK; SYD; 18:10; 06:05; 08:55; C; 20; M; 250

       Grammar:
        DOW          ::= int
        FlightKey    ::= AirlineCode ';' FlightNumber ';' Date ';' Date ';' DOW
        LegKey       ::= Airport ';' Airport
        LegDetails   ::= Time ';' Time ';' Elapsed
        CabinDetails ::= CabinCode ';' Capacity
        Leg          ::= LegKey ';' LegDetails (';' CabinDetails)+
        FlightPeriod ::= FlightKey (';' Leg)+
    */

struct FlightPeriodParser : 
  public boost::spirit::grammar<FlightPeriodParser> {
  FlightPeriodParser (FlightPeriod_T& ioFlightPeriod) 
  : _flightPeriod (ioFlightPeriod) {
  }

  template <typename ScannerT>
  struct definition {
    definition (FlightPeriodParser const& self) {
      first = 
	// flight_period[self.val = phoenix::arg1]
	(

	 flight_period =
	 flight_key
	 >> +( ';' >> leg )
	 ,

	 flight_key =
	 (+alpha_p)[assign_a(self._flightPeriod._airlineCode)]
	 >> ';' >> (uint_p)[assign_a(self._flightPeriod._flightNumber)]
	 >> ';' 
	 >> ((+digit_p) >> '-' >> (+digit_p) >> '-' 
	     >> (+digit_p))[&do_boardDate]
	 >> ';' 
	 >> ((+digit_p) >> '-' >> (+digit_p) >> '-' 
	     >> (+digit_p))[&do_offDate]
	 >> ';' >> (+digit_p)[&do_dow]
	 ,

	 leg =
	 leg_key
	 >> ';' >> leg_details
	 >> +( ';' >> cabin_details )
	 ,
	 
	 leg_key =
	 (+alpha_p)[assign_a(self._flightPeriod._itLegCabin._boardPoint)]
	 >> ';' 
	 >> (+alpha_p)[assign_a(self._flightPeriod._itLegCabin._offPoint)]
	 ,
	 
	 leg_details =
	 ((+digit_p) >> ':' >> (+digit_p) >> ':' 
	  >> (+digit_p))[&do_boardTime]
	 >> ';' 
	 >> ((+digit_p) >> ':' >> (+digit_p) >> ':' 
	     >> (+digit_p))[&do_offTime]
	 >> ';'
	 >> ((+digit_p) >> ':' >> (+digit_p) >> ':' 
	     >> (+digit_p))[&do_elapsed]
	 ,

	 cabin_details =
	 // cabin_parser_p[assign_a(self._flightPeriod._itCabin)]
	 (alpha_p)[&do_cabin]
	 >> ';' >> (ureal_p)[&do_capacity]
	 );
    }
    
    boost::spirit::subrule<0> flight_period;
    boost::spirit::subrule<1> flight_key;
    boost::spirit::subrule<2> leg;
    boost::spirit::subrule<3> leg_key;
    boost::spirit::subrule<4> leg_details;
    boost::spirit::subrule<5> cabin_details;
    
    boost::spirit::rule<ScannerT> first;
    boost::spirit::rule<ScannerT> const& start() const { return first; }
  };

  FlightPeriod_T& _flightPeriod;
};

// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {
    

    // String to be parsed
    std::string lToBeParsed ("BA; 9; 2007-04-20; 2007-04-30; 3; LHR; BKK; 22:00:00; 15:15:00; 11:15:00; C; 12.0; M; 300.0; BKK; SYD; 18:10:00; 06:05:00; 08:55:00; C; 20.0; M; 250.0");

    // Read the command-line parameters
    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> lToBeParsed;
    }

    std::cout << "String to be parsed: " << lToBeParsed << std::endl;

    // Instantiate the structure that will hold the result of the parsing.
    FlightPeriod_T lFlightPeriod;
    FlightPeriodParser lFlightPeriodParser (lFlightPeriod);
    boost::spirit::parse_info<> info =
      boost::spirit::parse (lToBeParsed.c_str(), lFlightPeriodParser, 
			    boost::spirit::space_p);

    std::cout << "-------------------------" << std::endl;
    if (info.full) {
      std::cout << "Parsing succeeded" << std::endl;
      
    } else {
      std::cout << "Parsing failed" << std::endl;
    }
    std::cout << "-------------------------" << std::endl;

    // Display the result
    lFlightPeriod.display();
     
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;
}
