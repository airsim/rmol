// STL
#include <iostream>
#include <sstream>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>


// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {

    typedef boost::gregorian::date DateTime_T;
    typedef boost::gregorian::date_duration DateOffSet_T;
    typedef boost::posix_time::time_duration Duration_T;
    
    const DateTime_T lDate1 (2007, 01, 01);
    const DateTime_T lDate2 (2007, 01, 02);
    const DateOffSet_T lDateDiff = lDate2 - lDate1;
    const Duration_T lDateDiffInHours (lDateDiff.days()*24, 0, 0);

    std::cout << "Date1: " << lDate1 << " - Date2: " << lDate2
              << " => DateDiff (in h): " << lDateDiffInHours << std::endl;
    
    const Duration_T lTime1 (12, 0, 0);
    const Duration_T lTime2 (14, 2, 1);
    const Duration_T lTimeDiff = lTime2 - lTime1;
    const Duration_T lTimeDiffInc = lTimeDiff + lDateDiffInHours;
    const Duration_T lTimeDiffDec = lTimeDiff - lDateDiffInHours;
    
    std::cout << "Time1: " << lTime1 << " - Time2: " << lTime2
              << " => TimeDiff: " << lTimeDiff
              << "; TimeDiff + DateDiff: " << lTimeDiffInc
              << "; TimeDiff - DateDiff: " << lTimeDiffDec << std::endl;
    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;
}
