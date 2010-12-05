// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <fstream>
// CPPUNIT
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/XmlOutputter.h>
// RMOL Test Common
#include <test/com/CppUnitCore.hpp>
#include <test/com/XmlOutputterHookForCC.hpp>

namespace RMOL {
  
  // //////////////////////////////////////////////////////////////////////
  CppUnitCore::CppUnitCore (const char* resultFileName) :
    _resultFileName (resultFileName) {
  }
		
  // //////////////////////////////////////////////////////////////////////
  int CppUnitCore::main (int argc, char* argv[]) {
    return maincore();
  }
		
  // //////////////////////////////////////////////////////////////////////
  int CppUnitCore::maincore() {
    // Create a test runner to execute the test cases you have
    // defined (in other source code).
    CppUnit::TextTestRunner runner;

    // Add the test cases you defined previously in a test suite to
    // the runner and execute them.
    runner.addTest (CppUnit::TestFactoryRegistry::getRegistry().makeTest());

    // Specify the progress listener
    CppUnit::BriefTestProgressListener progressListener;
    runner.eventManager().addListener (&progressListener);

    // Run the test suite
    bool wasSuccessful = runner.run();

    // Specify XML output and generate the XML Output.	
    std::ofstream outputFile (_resultFileName);
    CppUnit::XmlOutputter outputter (&runner.result(), outputFile);

    XmlOutputterHookForCC hook;
    outputter.addHook (&hook);

    // Here the write method of the outputer is not called
    // automatically, because you can attach only one outputter to
    // the runner and we want to keep the text one for the console
    outputter.write();

    outputFile.close();

    return wasSuccessful ? 0 : 1;
  }

}
