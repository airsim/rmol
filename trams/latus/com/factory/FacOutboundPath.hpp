#ifndef __LATUS_COM_FAC_FACOUTBOUNDPATH_HPP
#define __LATUS_COM_FAC_FACOUTBOUNDPATH_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct OutboundPathKey_T;
    class OutboundPath;
    class SegmentDate;
    
    /** Factory for OutboundPath objects. */
    class FacOutboundPath : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacOutboundPath& */
      static FacOutboundPath& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacOutboundPath::instance() */
      virtual ~FacOutboundPath();

      /** Create a new OutboundPath object.
          <br>This new object is added to the list of instantiated objects.
          @return OutboundPath& The newly created object. */
      OutboundPath& create (const OutboundPathKey_T&);

      /** Initialise the link between a OutboundPath and a SegmentDate.
          @param OutboundPath&
          @param SegmentDate&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithSegmentDate (OutboundPath&, const SegmentDate&);

      /** Clone the links, existing between a reference OutboundPath and its
          SegmentDate objects, to another OutboundPath.
          @param OutboundPath&
          @param const OutboundPath& The reference OutboundPath object.
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void cloneSegmentDateLinks (OutboundPath&, const OutboundPath&);
      
    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacOutboundPath () {}

    private:
      /** The unique instance.*/
      static FacOutboundPath* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACOUTBOUNDPATH_HPP
