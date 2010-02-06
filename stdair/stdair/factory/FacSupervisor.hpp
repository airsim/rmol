#ifndef __STDAIR_FAC_FACSUPERVISOR_HPP
#define __STDAIR_FAC_FACSUPERVISOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <vector>
// StdAir
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  // Forward declarations
  class FacBomStructure;
  class FacBomContent;

  /** Singleton class to register and clean all Factories. */
  class FacSupervisor {
  public:

    /** Define the pool (list) of factories. */
    typedef std::vector<FacBomStructure*> BomStructureFactoryPool_T;
    typedef std::vector<FacBomContent*> BomContentFactoryPool_T;
    
    /** Provide the unique (static) instance of the FacSupervisor object.
        <br>The singleton is instantiated when first used.
        @return FacSupervisor& */
    static FacSupervisor& instance();

    /** Register a newly instantiated concrete factory for the
        BomStructure layer.
        <br>When a concrete Factory is firstly instantiated
        this factory have to register itself to the FacSupervisor
        @param FacBomStructure* The concrete Factory to register. */
    void registerBomStructureFactory (FacBomStructure*);

    /** Register a newly instantiated concrete factory for the
        BomContent layer.
        <br>When a concrete Factory is firstly instantiated
        this factory have to register itself to the FacSupervisor
        @param FacBomContent* The concrete Factory to register. */
    void registerBomContentFactory (FacBomContent*);

    /** Clean all registered object.
        <br>Call the clean method of all the instantiated factories
        for the BomStructure layer. */
    void cleanBomStructureLayer();

    /** Clean all the registered object.
        <br>Call the clean method of all the instantiated factories
        for the BomContent layer. */
    void cleanBomContentLayer();

    /** Delete the static instance of the Logger object. */
    static void cleanLoggerService();

    /** Delete the static instance of the DBSessionManager object. */
    static void cleanDBSessionManager();

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

    /** List of instantiated factories for the BomStructure layer. */
    BomStructureFactoryPool_T _facBomStructurePool;

    /** List of instantiated factories for the BomContent layer. */
    BomContentFactoryPool_T _facBomContentPool;
  };
}  
#endif // __STDAIR_FAC_FACSUPERVISOR_HPP
