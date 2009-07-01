#ifndef __STDAIR_BOM_PRINTBOMCONTENT_HPP
#define __STDAIR_BOM_PRINTBOMCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STDAIR 
#include <stdair/bom/BomStructureList.hpp>

namespace stdair {
  
  /** . */
  struct PrintBomContent {

  public:
    /** Dump a BomContent object into an output stream. */
    template <typename BOM_STRUCTURE, typename BOM_CONTENT>
    void printBomContent (const BomStructureList_T::value_type& iIte) const {
      std::ostringstream& str = getStringStream();
      unsigned short& idx = getIndex();
      
      const BomStructure* lBomStructure_ptr = iIte.second;
      
      const BOM_STRUCTURE* lStructure_ptr =
      dynamic_cast<const BOM_STRUCTURE*> (lBomStructure_ptr);
      
      if (lStructure_ptr != NULL) {
        // Get the content out of the structure/holder
        const BOM_CONTENT& lContent =
          lStructure_ptr->BomStructure::getContent<BOM_CONTENT>();
        str << "[" << idx << "]: " << lContent.toString();
        ++idx;
      }    
    }

    ////////////// Getters /////////////
    /** Get the stringstream. */
    std::ostringstream& getStringStream () const {
      assert (_str != NULL);
      return *_str;
    }

    /** Get the index. */
    unsigned short& getIndex () const {
      assert (_idx != NULL);
      return *_idx;
    }

    /** Constructors. */
    PrintBomContent ();
    PrintBomContent (std::ostringstream&, unsigned short&);

  private:
    ///////////// Attributes //////////////
    /** Output stream. */
    std::ostringstream* _str;

    /** Index of the object. */
    unsigned short* _idx;
  };

}
#endif // __STDAIR_BOM_PRINTBOMCONTENT_HPP

