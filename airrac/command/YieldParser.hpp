#ifndef __AIRRAC_CMD_YIELDPARSER_HPP
#define __AIRRAC_CMD_YIELDPARSER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/command/CmdAbstract.hpp>

// Forward declarations
namespace stdair {
  class BomRoot;
}

namespace AIRRAC {
  
  /** Class wrapping the parser entry point. */
  class YieldParser : public stdair::CmdAbstract {
  public:
    /** Parse the CSV file describing an airline yield store, and generates
        the corresponding data model in memory. It can then be used,
        for instance in a simulator.
        @param const stdair::Filename_T& The file-name of the CSV-formatted
               yield input file.
        @param stdair::BomRoot& Root of the BOM tree. */
    static void generateYieldStore (const stdair::Filename_T&,
                                    stdair::BomRoot&);
  };
}
#endif // __AIRRAC_CMD_YIELDPARSER_HPP
