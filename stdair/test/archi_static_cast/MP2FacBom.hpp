#ifndef __MYPROVIDER_FACBOM_HPP
#define __MYPROVIDER_FACBOM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>

namespace myprovider {  

  /** Base class for Factory layer. */
  template <typename BOM>
  class FacBom {
    // Internal type definitions.
    typedef std::list<BOM*> BomPool_T;
    typedef typename BOM::Key_T Key_T;

  public:
    // ///////////// Business methods. ////////////
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacBom& */
    static FacBom& instance();

    /** Create a BOM object, given a key or not. */
    BOM& create ();
    BOM& create (const Key_T&);
    
  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is . */
    FacBom() {}

  public:
    /** Destructor. */
    ~FacBom() { clean(); }
    /** Destroyed all the object instantiated by this factory. */
    void clean();
    
  private:
    /** The unique instance.*/
    static FacBom* _instance;
    /** List of instantiated Business Objects*/
    BomPool_T _pool;
  };

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> FacBom<BOM>* FacBom<BOM>::_instance = NULL;
  
  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> FacBom<BOM>& FacBom<BOM>::instance () {
    if (_instance == NULL) {
      _instance = new FacBom ();
      assert (_instance != NULL);
    }
    return *_instance;
  }

  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> void FacBom<BOM>::clean () {
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
  
  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> BOM& FacBom<BOM>::create () {
    Key_T lKey;
    return instance().create (lKey);
  }
  
  // ////////////////////////////////////////////////////////////////////
  template <typename BOM> BOM& FacBom<BOM>::
  create (const Key_T& iKey) {
    BOM* oBom_ptr = new BOM (iKey);
    assert (oBom_ptr != NULL);
    _pool.push_back (oBom_ptr);
    return *oBom_ptr;
  }
  
}
#endif // __MYPROVIDER_FACBOM_HPP
