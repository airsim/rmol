#ifndef __INTRUSIVE_FAC_FACBOM_HPP
#define __INTRUSIVE_FAC_FACBOM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
// StdAir 
#include <test/archi_intru/FacAbstract.hpp>
#include <test/archi_intru/FacSupervisor.hpp>

namespace stdair {  

  /** Class for handling the memory related to BOM objects. */
  template <typename BOM>
  class FacBom : public FacAbstract {
    // Internal type definitions.
    typedef std::list<BOM*> BomPool_T;

  public:
    // ///////////// Business methods. ////////////
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacBom& */
    static FacBom& instance() {
      if (_instance == NULL) {
        _instance = new FacBom ();
        assert (_instance != NULL);
        
        FacSupervisor::instance().registerFacBom (_instance);
      }
      return *_instance;
    }

    /** Create a BOM object for a given key. */
    BOM& create (const std::string& iKey)  {
      BOM* oBom_ptr = new BOM (iKey);
      assert (oBom_ptr != NULL);
      _pool.push_back (oBom_ptr);
      return *oBom_ptr;
    }
    
    /** Create a BOM object for a given key. */
    BOM& create (const int& idx)  {
      BOM* oBom_ptr = new BOM (idx);
      assert (oBom_ptr != NULL);
      _pool.push_back (oBom_ptr);
      return *oBom_ptr;
    }
    
  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is . */
    FacBom() {}

  public:
    /** Destructor. */
    ~FacBom() { clean(); }

    /** Destroyed all the object instantiated by this factory. */
    void clean() {
      // Destroy all the objects
      for (typename BomPool_T::iterator itBom = _pool.begin();
           itBom != _pool.end(); ++itBom) {
        BOM* currentBom_ptr = *itBom;
        assert (currentBom_ptr != NULL);
        delete currentBom_ptr; currentBom_ptr = NULL;
      }
      
      // Empty the pool.
      _pool.clear();
      
      // Reset the static instance.
      _instance = NULL;
    }
    
  private:
    /** The unique instance.*/
    static FacBom* _instance;
    /** List of instantiated Business Objects*/
    BomPool_T _pool;
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> FacBom<BOM>* FacBom<BOM>::_instance = NULL;
  
}
#endif // __INTRUSIVE_FAC_FACBOM_HPP
