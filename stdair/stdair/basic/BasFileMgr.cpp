// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost (STL Extension)
// Boost Filesystem (http://www.boost.org/doc/libs/1_41_0/libs/filesystem/doc/index.htm)
#include <boost/filesystem.hpp>
// StdAir
#include <stdair/basic/BasFileMgr.hpp>

namespace boostfs = boost::filesystem;

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  bool BasFileMgr::doesExistAndIsReadable (const std::string& iFilepath) {
    bool oFine = false;
    
    boostfs::path lPath (iFilepath);

    if (boostfs::exists (lPath) == true && boostfs::is_regular (lPath) == true) {
      oFine = true;
    }

    return true;
  }
  
}
