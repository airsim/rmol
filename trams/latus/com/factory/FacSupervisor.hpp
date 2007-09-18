#ifndef __LATUS_COM_FAC_FACSUPERVISOR_HPP
#define __LATUS_COM_FAC_FACSUPERVISOR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class FacBomAbstract;
    class FacServiceAbstract;
    class ServiceContextManager;

    /** Singleton class to register and clean all Factories. */
    class FacSupervisor {
    public:

      /** Define the pool (list) of factories. */
      typedef std::vector<FacBomAbstract*> BomFactoryPool_T;
      typedef std::vector<FacServiceAbstract*> ServiceFactoryPool_T;

      /** Provides the unique instance.
          <br>The singleton is instantiated when first used.
          @return FacSupervisor& */
      static FacSupervisor& instance();

      /** Register a newly instantiated concrete factory for the Bom layer.
          <br>When a concrete Factory is firstly instantiated
          this factory have to register itself to the FacSupervisor.
          @param FacAbstract& the concrete Factory to register. */
      void registerBomFactory (FacBomAbstract*);

      /** Register a newly instantiated concrete factory for the Service layer.
          <br>When a concrete Factory is firstly instantiated
          this factory have to register itself to the FacSupervisor.
          @param FacServiceAbstract& the concrete Factory to register. */
      void registerServiceFactory (FacServiceAbstract*);

      /** Register a newly instantiated concrete factory for the
          ServiceContextManager object. In fact, as the
          ServiceContextManager object follows the singleton pattern, the
          concrete factory is the ServiceContextManager object itself.
          <br>When a concrete Factory is firstly instantiated
          this factory have to register itself to the FacSupervisor.
          @param FacServiceAbstract& the concrete Factory to
          register. */
      void registerServiceContextManager (ServiceContextManager*);

      /** Clean all the BOM created object.
          <br>Call the clean method of all the instantiated  factories
          for the Bom layer. */
      void cleanBomLayer();

      /** Clean all Service created object.
          <br>Call the clean method of all the instantiated  factories
          for the Service layer. */
      void cleanServiceLayer();

      /** Delete the ServiceContextManager object. */
      void cleanServiceContextManager();

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
      FacSupervisor ();
      FacSupervisor (const FacSupervisor&);


    private:
      /** The unique instance.*/
      static FacSupervisor* _instance;

      /** ServiceContextManager (singleton) instance. */
      ServiceContextManager* _serviceContextManager;
      
      /** List of instantiated factories for the Bom layer. */
      BomFactoryPool_T _bomPool;

      /** List of instantiated factories for the Service layer. */
      ServiceFactoryPool_T _svcPool;
    
    };
    
  }
}  
#endif // __LATUS_COM_FAC_FACSUPERVISOR_HPP
