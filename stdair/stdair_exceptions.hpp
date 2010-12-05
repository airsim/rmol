#ifndef __STDAIR_STDAIR_EXCEPTIONS_HPP
#define __STDAIR_STDAIR_EXCEPTIONS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace stdair {

  /**
     Root of the stdair exceptions.
     <br>All the stdair exceptions inherit from that root, allowing to
     catch them and to spot them easily when arising in code wrapping
     the stdair library.
   */
  class RootException : public std::exception { 
  public:
    /** Constructors. */
    RootException (const std::string& iWhat) : _what (iWhat) {}
    RootException () : _what ("No further details") {}
    
    /** Destructor. */
    virtual ~RootException() throw() {}
    
    /** Give the details of the exception. */
    const char* what() const throw() {
      return _what.c_str();
    }
    
  protected:
    /** Details for the exception. */
    std::string _what;
  };
  
  // ////////////////////////////////////////////////////////////////////
  class FileNotFoundException : public RootException { 
  public:
    /** Constructor. */
    FileNotFoundException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedLogServiceException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedLogServiceException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedDBSessionManagerException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedDBSessionManagerException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedServiceException : public RootException {
  public:
    /** Constructor. */
    NonInitialisedServiceException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedContainerException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedContainerException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class NonInitialisedRelationShipException : public RootException { 
  public:
    /** Constructor. */
    NonInitialisedRelationShipException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class MemoryAllocationException : public RootException { 
  public:
    /** Constructor. */
    MemoryAllocationException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class ObjectLinkingException : public RootException { 
  public:
    /** Constructor. */
    ObjectLinkingException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class ParserException : public RootException { 
  public:
    /** Constructor. */
    ParserException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class DocumentNotFoundException : public RootException {
  public:
    /** Constructor. */
    DocumentNotFoundException (const std::string& iWhat) 
      : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class CodeConversionException : public ParserException {  
  public:
    /** Constructor. */
    CodeConversionException (const std::string& iWhat)
      : ParserException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class CodeDuplicationException : public ParserException { 
  public:
    /** Constructor. */
    CodeDuplicationException (const std::string& iWhat)
      : ParserException(iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class ObjectCreationgDuplicationException : public ParserException {
  public:
    /** Constructor. */
    ObjectCreationgDuplicationException (const std::string& iWhat) 
      : ParserException (iWhat) {} 
  };
  
  // ////////////////////////////////////////////////////////////////////
  class ObjectNotFoundException : public RootException {
  public:
    /** Constructor. */
    ObjectNotFoundException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class SQLDatabaseException : public RootException {
  public:
    /** Constructor. */
    SQLDatabaseException (const std::string& iWhat) : RootException (iWhat) {}
  };
  
  // ////////////////////////////////////////////////////////////////////
  class SQLDatabaseConnectionImpossibleException : public SQLDatabaseException {
  public:
    /** Constructor. */
    SQLDatabaseConnectionImpossibleException (const std::string& iWhat)
      : SQLDatabaseException (iWhat) {}
  };
  
} // end of stdair namespace

// ////////////////////////////////////////////////////////////////////
#define CATCH_ALL_EXCEPTIONS                                            \
  catch (const stdair::FileNotFoundException& ex) {                     \
    std::cerr << "FileNotFoundException" << ex.what() << std::endl;     \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedLogServiceException& ex) {       \
    std::cerr << "NonInitialisedLogServiceException"                    \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedDBSessionManagerException& ex) { \
    std::cerr << "NonInitialisedDBSessionManagerException"              \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedServiceException& ex) {          \
    std::cerr << "NonInitialisedServiceException"                       \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedContainerException& ex) {        \
    std::cerr << "NonInitialisedContainerException"                     \
              << ex.what() <<std::endl;                                 \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::NonInitialisedRelationShipException& ex) {     \
    std::cerr << "NonInitialisedRelationShipException"                  \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::MemoryAllocationException& ex) {               \
    std::cerr << "MemoryAllocationException" << ex.what() << std::endl; \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::ObjectLinkingException& ex) {                  \
    std::cerr << "ObjectLinkingException" << ex.what() << std::endl;    \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::CodeConversionException& ex) {                 \
    std::cerr << "CodeConversionException" << ex.what() << std::endl;   \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::CodeDuplicationException& ex) {                \
    std::cerr << "CodeDuplicationException" << ex.what() << std::endl;  \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::ObjectCreationgDuplicationException& ex) {     \
    std::cerr << "ObjectCreationgDuplicationException"                  \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::ObjectNotFoundException& ex) {                 \
    std::cerr << "ObjectNotFoundException" << ex.what() << std::endl;   \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::DocumentNotFoundException& ex) {               \
    std::cerr << "DocumentNotFoundException" << ex.what() << std::endl; \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::SQLDatabaseConnectionImpossibleException& ex) {\
    std::cerr << "SQLDatabaseConnectionImpossibleException"             \
              << ex.what() << std::endl;                                \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::SQLDatabaseException& ex) {                    \
    std::cerr << "SQLDatabaseException" << ex.what() << std::endl;      \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::ParserException& ex) {                         \
    std::cerr << "ParserException" << ex.what() << std::endl;           \
    return -1;                                                          \
                                                                        \
  } catch (const stdair::RootException& ex) {                           \
    std::cerr << "RootException" << ex.what() <<std::endl;              \
    return -1;                                                          \
                                                                        \
  } catch (const std::exception& stde) {                                \
    std::cerr << "Standard exception: " << stde.what() << std::endl;    \
    return -1;                                                          \
                                                                        \
  } catch (...) {                                                       \
    return -1;                                                          \
  } 

#endif // __STDAIR_STDAIR_EXCEPTIONS_HPP
