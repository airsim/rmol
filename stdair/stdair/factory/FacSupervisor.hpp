#ifndef __STDAIR_FAC_FACSUPERVISOR_HPP
#define __STDAIR_FAC_FACSUPERVISOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

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
    
    /** Provides the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacSupervisor& */
    static FacSupervisor& instance();

    /** Register a newly instantiated concrete factory for the BomStructure layer.
        <br>When a concrete Factory is firstly instantiated
        this factory have to register itself to the FacSupervisor
        @param FacBomStructure& the concrete Factory to register. */
    void registerBomStructureFactory (FacBomStructure*);

    /** Register a newly instantiated concrete factory for the BomContent layer.
        <br>When a concrete Factory is firstly instantiated
        this factory have to register itself to the FacSupervisor
        @param FacBomContent& the concrete Factory to register. */
    void registerBomContentFactory (FacBomContent*);

    /** Clean all created object.
        <br>Call the clean method of all the instantiated  factories
        for the BomStructure layer. */
    void cleanBomStructureLayer();

    /** Clean all created object.
        <br>Call the clean method of all the instantiated  factories
        for the BomContent layer. */
    void cleanBomContentLayer();

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

    /** List of instantiated factories for the BomStructure layer. */
    BomStructureFactoryPool_T _facBomStructurePool;

    /** List of instantiated factories for the BomContent layer. */
    BomContentFactoryPool_T _facBomContentPool;
  };
}  
#endif // __STDAIR_FAC_FACSUPERVISOR_HPP
