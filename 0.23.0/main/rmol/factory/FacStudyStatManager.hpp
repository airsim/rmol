#ifndef __RMOL_FAC_FACSTUDYSTATMANAGER_HPP
#define __RMOL_FAC_FACSTUDYSTATMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL 
#include <rmol/factory/FacBomAbstract.hpp>

namespace RMOL {

  /** Factory for StudyStatManager objects. */
  class FacStudyStatManager : public FacBomAbstract {
  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used
        @return FacStudyStatManager& */
    static FacStudyStatManager& instance();
    
    /** Destructor.
        <br>The Destruction put the _instance to NULL
        in order to be clean for the next FacStudyStatManager::instance() */
    virtual ~FacStudyStatManager();
    
    /** Create a new FacStudyStatManager object.
        <br>This new object is added to the list of instantiated objects.
        @return StudyStatManager& The newly created object. */
    StudyStatManager& create ();
    
  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacStudyStatManager () {}
    
  private:
    /** The unique instance.*/
    static FacStudyStatManager* _instance;
  };
  
}
#endif // __RMOL_FAC_FACSTUDYSTATMANAGER_HPP
