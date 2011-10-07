// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
// StdAir
#include <stdair/basic/BasFileMgr.hpp>
// AirRAC
#include <airrac/command/YieldParserHelper.hpp>
#include <airrac/command/YieldParser.hpp>

namespace AIRRAC {

  // //////////////////////////////////////////////////////////////////////
  void YieldParser::generateYieldStore (const YieldFilePath& iYieldFilename,
                                        stdair::BomRoot& ioBomRoot) {

    const stdair::Filename_T lFilename = iYieldFilename.name();

    // Check that the file path given as input corresponds to an actual file
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (lFilename);
    if (doesExistAndIsReadable == false) {
      STDAIR_LOG_ERROR ("The yield input file, '" << lFilename
                        << "', can not be retrieved on the file-system");
      throw YieldInputFileNotFoundException ("The yield file '" + lFilename
                                             + "' does not exist or can not "
                                             "be read");
    }

    // Initialise the yield file parser.
    YieldFileParser lYieldParser (ioBomRoot, lFilename);

    // Parse the CSV-formatted yield store input file, and generate the
    // corresponding Yield-related objects.
    lYieldParser.generateYieldStore();
  }
}
