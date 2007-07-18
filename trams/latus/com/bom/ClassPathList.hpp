#ifndef __LATUS_COM_BOM_CLASSPATHLIST_HPP
#define __LATUS_COM_BOM_CLASSPATHLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class ClassPath;

    /** List of ClassPath objects (for each class-path/combination). */
    typedef std::map<std::string, ClassPath*> ClassPathList_T;
  }

}
#endif // __LATUS_COM_BOM_CLASSPATHLIST_HPP
