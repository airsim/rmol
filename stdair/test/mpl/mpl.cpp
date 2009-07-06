// STL
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// MPL
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

// //////////////////////////////////////////////////////////////////
namespace STDAIR {

  /** BookingClass */
  struct BookingClass {
    std::string _classCode;
    /** Constructor. */
    BookingClass (const std::string& iClassCode)
      : _classCode (iClassCode) {
    }
    
    /** Display .*/
    std::string toString() const {
      std::ostringstream oStr;
      oStr << _classCode;
      return oStr.str();
    }
  };
  
  /** Cabin */
  struct Cabin {
    BookingClass _bookingClass;
    Cabin (const BookingClass& iBkgClass)
      : _bookingClass (iBkgClass) {
    }
    
    /** Display .*/
    std::string toString() const {
      std::ostringstream oStr;
      oStr << _bookingClass._classCode;
      return oStr.str();
    }

    /** Child type. */
    typedef BookingClass child;
  };

}

// /////////// M A I N ////////////////
int main (int argc, char* argv[]) {

  typedef boost::mpl::vector<STDAIR::BookingClass> MPL_BookingClass;
  typedef boost::mpl::push_back<MPL_BookingClass, STDAIR::Cabin>::type types;

  const STDAIR::BookingClass lA ("A");
  const STDAIR::Cabin lCabin (lA);

  // lCabin::type
  if (boost::is_same<STDAIR::BookingClass, STDAIR::Cabin::child>::value) {
    std::cout << "The type of the child of a Cabin is a BookingClass"
              <<  std::endl;

  } else {
    std::cout << "The type of " << lCabin.toString() << " is unknown"
              <<  std::endl;
  }
  
  if (boost::is_same<boost::mpl::at_c<types, 1>::type, STDAIR::Cabin>::value) {
    std::cout << "The 2nd type is STDAIR::Cabin" <<  std::endl;
    
  } else {
    std::cout << "Problem!" <<  std::endl;
  }

  BOOST_MPL_ASSERT ((boost::is_same<boost::mpl::at_c<types, 1>::type,
                     STDAIR::Cabin>::value));

  return 0;
}
