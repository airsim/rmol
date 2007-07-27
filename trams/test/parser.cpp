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
#include <boost/spirit/core.hpp>
#include <boost/spirit/actor/push_back_actor.hpp>
// LATUS
#include <latus/LATUS_Service.hpp>

#define BOOST_SPIRIT_DEBUG        // define this for debug output

// Type definitions
/** List of numbers. */
typedef std::vector<double> NumberList_T;

using namespace boost::spirit;

///////////////////////////////////////////////////////////////////////////////
//
//  Semantic actions
//
///////////////////////////////////////////////////////////////////////////////
namespace {
  void do_int(char const* str, char const* end) {
    std::string s (str, end);
    std::cout << "PUSH(" << s << ')' << std::endl;
  }

  void do_leg(char const*, char const*) { std::cout << "LEG\n"; }
  void do_ac(char const*, char const*) { std::cout << "AIRLINE_CODE\n"; }
  void do_fn(char const*, char const*) { std::cout << "FLIGHT_NUMBER\n"; }
  void do_year(char const*, char const*) { std::cout << "YEAR\n"; }
  void do_month(char const*, char const*) { std::cout << "MONTH\n"; }
  void do_day(char const*, char const*) { std::cout << "DAY\n"; }
  void do_dow(char const*, char const*) { std::cout << "DOW\n"; }
  void do_airport(char const*, char const*) { std::cout << "AIRPORT_CODE\n"; }

  void do_add(char const*, char const*)    { std::cout << "ADD\n"; }
  void do_subt(char const*, char const*)   { std::cout << "SUBTRACT\n"; }
  void do_mult(char const*, char const*)   { std::cout << "MULTIPLY\n"; }
  void do_div(char const*, char const*)    { std::cout << "DIVIDE\n"; }
  void do_neg(char const*, char const*)    { std::cout << "NEGATE\n"; }
}

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
        Leg          ::= LegKey ';' LegDetails ';' CabinDetails
        FlightPeriod ::= FlightKey ';' Leg (';' Leg)*
    */

struct calculator : public boost::spirit::grammar<calculator> {
  template <typename ScannerT>
  struct definition {
    definition (calculator const& /*self*/) {
    /*
      first = (

               flight_period =
               flight_key
               >> +(   (';' >> leg)[&do_leg]
                   )
               ,

               flight_key =
               lexeme_d[(+alpha_p)[&do_ac]]
               >> ';' >> lexeme_d[(+digit_p)[&do_fn]]
               >> ';' >> date
               >> ';' >> date
               >> ';' >> lexeme_d[(+digit_p)[&do_dow]]
               ,

               date =
               lexeme_d[(+digit_p)[&do_year]]
               >> '-' >> lexeme_d[(+digit_p)[&do_month]]
               >> '-' >> lexeme_d[(+digit_p)[&do_day]]
               ,
               
               leg =
               leg_key
               ,

               leg_key =
               lexeme_d[(+alpha_p)[&do_airport]]
               );
      
      BOOST_SPIRIT_DEBUG_NODE(first);
      BOOST_SPIRIT_DEBUG_NODE(flight_period);
      BOOST_SPIRIT_DEBUG_NODE(flight_key);
      BOOST_SPIRIT_DEBUG_NODE(date);
      BOOST_SPIRIT_DEBUG_NODE(leg);
      BOOST_SPIRIT_DEBUG_NODE(leg_key);
*/
    }
    
    boost::spirit::subrule<0>  flight_period;
    boost::spirit::subrule<1>  flight_key;
    boost::spirit::subrule<2>  date;
    boost::spirit::subrule<3>  leg;
    boost::spirit::subrule<4>  leg_key;
    
    boost::spirit::rule<ScannerT> first;
    boost::spirit::rule<ScannerT> const& start() const { return first; }
  };
};

// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {
    

    // String to be parsed
    //    std::string lToBeParsed ("BA;9;2007-04-20;2007-04-30;3;LHR;BKK;22:00;15:15;11:15;C;12;M;300;BKK;SYD;18:10;06:05;08:55;C;20;M;250");
    std::string lToBeParsed ("BA;9;2007-04-20;2007-04-30;3;LHR;BKK;BKK;SYD");
    //std::string lToBeParsed ("1+2");

    // Read the command-line parameters
    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> lToBeParsed;
    }

    std::cout << "String to be parsed: " << lToBeParsed << std::endl;
    
    calculator calc;    //  Our parser
    boost::spirit::parse_info<> info =
      boost::spirit::parse (lToBeParsed.c_str(), calc, boost::spirit::space_p);

    if (info.full) {
      std::cout << "-------------------------" << std::endl;
      std::cout << "Parsing succeeded: " << std::endl;
      std::cout << "-------------------------" << std::endl;
      
    } else {
      std::cout << "-------------------------" << std::endl;
      std::cout << "Parsing failed" << std::endl;
      std::cout << "-------------------------" << std::endl;
    }
     
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;
}
