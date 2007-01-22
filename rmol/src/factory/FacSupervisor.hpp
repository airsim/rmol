#ifndef __RMOL_FAC_FACSUPERVISOR_HPP
#define __RMOL_FAC_FACSUPERVISOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

namespace RMOL {

  // Forward declarations
  class FacAbstract;

  /** Singleton class to register and clean all Factories. */
  class FacSupervisor {
  public:

    /** Define the pool (list) of factories. */
    typedef std::vector<FacAbstract*> FactoryPool_T;

    /** Provides the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacSupervisor& */
    static FacSupervisor& instance();

    /** Register a newly instantiated concrete factory
        <br>When a concrete Factory is firstly instantiated
        this factory have to register itself to the FacSupervisor
        @param FacAbstract& the concrete Factory to register. */
    void registerFactory (FacAbstract*);

    /** Clean all created object.
        <br>Call the clean method of all the instantiated  factories. */
    void clean();

    /** Clean the static instance.
        <br> The singleton is deleted.*/
    static void cleanFactory ();

    /** Destructor
        <br>The static instance is deleted (and reset to NULL)
        by the static cleanFactory() method. */
    ~FacSupervisor();


  protected:
    /** Default Constructor.
        <br>This constructor is protected 
        to ensure the singleton pattern. */
    FacSupervisor () {}
    FacSupervisor (const FacSupervisor&) {}


  private:
    /** The unique instance.*/
    static FacSupervisor* _instance;

    /** List of instantiated factories. */
    FactoryPool_T _pool;
    
  };
}  
#endif
