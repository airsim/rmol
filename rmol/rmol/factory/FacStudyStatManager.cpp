// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// StdAir
//#include <stdair/service/Logger.hpp>
// RMOL 
#include <rmol/bom/StudyStatManager.hpp>
#include <rmol/factory/FacSupervisor.hpp>
#include <rmol/factory/FacStudyStatManager.hpp>

namespace RMOL {
  
  FacStudyStatManager* FacStudyStatManager::_instance = NULL;
  
  // //////////////////////////////////////////////////////////////////////
  FacStudyStatManager::~FacStudyStatManager () {
    _instance = NULL;
  }
  
  // //////////////////////////////////////////////////////////////////////
  FacStudyStatManager& FacStudyStatManager::instance () {
    
    if (_instance == NULL) {
      _instance = new FacStudyStatManager();
      assert (_instance != NULL);
      
      FacSupervisor::instance().registerBomFactory (_instance);
    }
    return *_instance;
  }
  
  // //////////////////////////////////////////////////////////////////////
  StudyStatManager& FacStudyStatManager::create () {
    StudyStatManager* aStudyStatManager_ptr = NULL;
    aStudyStatManager_ptr = new StudyStatManager ();
    assert (aStudyStatManager_ptr != NULL);
    
    // The new object is added to the Bom pool
    _pool.push_back (aStudyStatManager_ptr);
    
    return *aStudyStatManager_ptr;
  }

}
