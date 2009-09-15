#ifndef __RMOL_XMLOUTPUTTERHOOKFORCC_HPP
#define __RMOL_XMLOUTPUTTERHOOKFORCC_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <cppunit/XmlOutputterHook.h>
 
namespace RMOL {

  /** Helper class to translate CPPUnit test output into something ANT can
      understand (for CruiseControl). */
  class XmlOutputterHookForCC : public CppUnit::XmlOutputterHook {
  public:

    /** Call-back for the beginning of a document. */
    virtual void beginDocument(CppUnit::XmlDocument* document);
				
    /** Call-back for a failed test. */
    virtual void failTestAdded (CppUnit::XmlDocument *document,
                                CppUnit::XmlElement *testElement,
                                CppUnit::Test *test, 
                                CppUnit::TestFailure *failure);
				
    /** Call-back for a successful test. */
    virtual void successfulTestAdded (CppUnit::XmlDocument *document, 
                                      CppUnit::XmlElement *testElement, 
                                      CppUnit::Test *test);
			
    /** Call-back for a new test. */
    virtual void testAdded (CppUnit::XmlDocument *document, 
                            CppUnit::XmlElement *testElement, 
                            CppUnit::Test *test);
  };
		
}
#endif // __RMOL_XMLOUTPUTTERHOOKFORCC_HPP
