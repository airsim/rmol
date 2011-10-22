#ifndef __RMOL_CPPUNITCORE_HPP
#define __RMOL_CPPUNITCORE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

// /////////////// MACROS /////////////////
#define CPPUNIT_MAIN() \
int main (int argc, char* argv[]) {  \
  std::string xmlOutputFile (__FILE__);            \
  xmlOutputFile.resize (xmlOutputFile.length()-4); \
  xmlOutputFile.append("_results.xml");            \
  return RMOL::CppUnitCore (xmlOutputFile.c_str()).main(argc, argv); \
}
// /////////// (END OF)  MACROS /////////////

namespace RMOL {
  
  /** Class to handle CPPUnit functions. */
  class CppUnitCore {
  public:
    /** Constructor .*/
    CppUnitCore (const char* resultFileName);
    
    /** The main to use for all CPPUnit test.*/
    int main(int argc, char* argv[]);
      
    /** In case user want to do parse the argument it can just use
        the maincore. */
    int maincore();
      
  protected:
    const char* _resultFileName;
  };
  
}
#endif // __RMOL_CPPUNITCORE_HPP
