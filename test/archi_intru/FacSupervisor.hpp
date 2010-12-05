#ifndef __INTRUSIVE_SVC_FACSUPERVISOR_HPP
#define __INTRUSIVE_SVC_FACSUPERVISOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>

namespace stdair {

  // Forward declarations
  class FacAbstract;
  class FacRelationShipRootAbstract;

  /** Singleton class to register and clean all Factories. */
  class FacSupervisor {
  public:
    /** Define the pool (list) of factories. */
    typedef std::list<FacAbstract*> FactoryPool_T;
    typedef std::list<FacRelationShipRootAbstract*> FacRelationShipRootPool_T;
    
    /** Provide the unique (static) instance of the FacSupervisor object.
        <br>The singleton is instantiated when first used.
        @return FacSupervisor& */
    static FacSupervisor& instance();

    /** Register a newly instantiated concrete factory for the
        Bom layer.
        <br>When a concrete Factory is firstly instantiated
        this factory have to register itself to the FacSupervisor
        @param FacBom* The concrete Factory to register. */
    void registerFacBom (FacAbstract*);

    /** Register a newly instantiated concrete relation ship factory. */
    void registerFacRelationShipRoot (FacRelationShipRootAbstract*);

    /** Clean all registered object.
        <br>Call the clean method of all the instantiated factories
        for the BomStructure layer. */
    void cleanBomLayer();

    /** Clean all registered relation ships. */
    void cleanFacRelationShipRoots();

    /** Clean the static instance.
        <br>As the static instance (singleton) is deleted, all the other
        registered objects will be deleted in turn. */
    static void cleanAll ();

    /** Destructor.
        <br>That destructors is applied on the static instance. It then
        deletes in turn all the other registered objects. */
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
    /** List of instantiated factories for the BOM layer. */
    FactoryPool_T _facPool;
    /** List of instantiated relation ships. */
    FacRelationShipRootPool_T _facRelationShipRootPool;
  };
}  
#endif // __INTRUSIVE_SVC_FACSUPERVISOR_HPP
