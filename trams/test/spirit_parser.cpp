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

// Type definitions
/** List of numbers. */
typedef std::vector<double> NumberList_T;

///////////////////////////////////////////////////////////////////////////////
//
//  Comma separated list parser
//
///////////////////////////////////////////////////////////////////////////////
bool parse_numbers (const std::string& iInputString, NumberList_T& ioNbList) {
  /** Grammar:
      expression ::= real (',' real)*
   */

  const bool hasParsingSucceeded =
    boost::spirit::parse (iInputString.c_str(),
    (
    //  Begin grammar
    boost::spirit::real_p[boost::spirit::push_back_a(ioNbList)]
      >> *(','
      >> boost::spirit::real_p[boost::spirit::push_back_a(ioNbList)])
    //  End grammar
    )
                          ,
                          boost::spirit::space_p).full;
  
  return hasParsingSucceeded;
}

// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {

    // String to be parsed
    std::string lToBeParsed ("10.5, 9.8, 7.456, 2.34");

    // Read the command-line parameters
    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> lToBeParsed;
    }

    std::cout << "String to be parsed: " << lToBeParsed << std::endl;
    
    NumberList_T lNbList;
    const bool hasParsingSucceeded = parse_numbers (lToBeParsed, lNbList);
    
    if (hasParsingSucceeded == true) {
      std::cout << "-------------------------" << std::endl;
      std::cout << "Parsing succeeded: " << std::endl;

      short i = 0;
      for (NumberList_T::const_iterator itNb = lNbList.begin();
           itNb != lNbList.end(); itNb++, i++) {
        const double lNumber = *itNb;
        std::cout << "[" << i << "]: " << lNumber << std::endl;
      }

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
