#ifndef __STDAIR_BOM_AIRLINEFEATURESETSTRUCTURE_HPP
#define __STDAIR_BOM_AIRLINEFEATURESETSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR 
#include <stdair/bom/BomStopStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>
#include <stdair/bom/AirlineFeatureStructure.hpp>
#include <stdair/bom/AirlineFeatureKey.hpp>

namespace stdair {
  // Forward declarations.
  template <typename BOM> struct BomMap_T;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by a specific AirlineFeatureSet class. */
  template <typename BOM_CONTENT>
  class AirlineFeatureSetStructure : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    friend class BomStructure;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BOM_CONTENT Content_T;

    /** Definition allowing to retrieve the  children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::ContentChild_T ContentChild_T;
    
    /** Definition allowing to retrieve the  key type of the
        ContentChild_T. */
    typedef AirlineFeatureKey_T ChildKey_T;

    /** Define the map of ContentChild_T. */
    typedef BomMap_T<ContentChild_T> ChildrenMap_T;
    
  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef typename BOM_CONTENT::BomKey_T BomKey_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<AirlineFeatureStructure<ContentChild_T>, BomStopStructure> ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<BomStopContent> DefaultChildrenBomHolder_T;
    
    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

  public:
    // /////////// Getters /////////////
    /** Get the AirlineFeatureSet key. */
    const BomKey_T& getKey () const {
      assert (_content != NULL);
      return _content->getKey ();
    }
    
    /** Get the holder of airline features. */
    const ChildrenBomHolder_T& getChildrenHolder() const {
      assert (_childrenHolder != NULL);
      return *_childrenHolder;
    }

    /** Get the holder of airline features. */
    void getChildrenHolder (ChildrenBomHolder_T*& ioChildrenHolder) {
      ioChildrenHolder = _childrenHolder;
    }
    
    /** Retrieve, if existing, the airline feature corresponding to the
        given key.
        <br>If not exissting, return the NULL pointer. */
    ContentChild_T* getContentChild (const ChildKey_T& iKey) const {
      ContentChild_T* oContentChild_ptr = NULL;
      
      ChildrenMap_T lChildrenMap (getChildrenHolder());
      const MapKey_T lMapKey = iKey.toString();
      
      typename ChildrenMap_T::iterator itContentChild =
        lChildrenMap.find (lMapKey);
      
      if (itContentChild != lChildrenMap.end()) {
        oContentChild_ptr = itContentChild->second;
        assert (oContentChild_ptr != NULL);
      }
      
      return oContentChild_ptr;
    }
    
  private: 
    /////////////// Setters ////////////////
    /** Default children holder setter. */
    void setChildrenHolder (DefaultChildrenBomHolder_T&) { }
    
    /** Set the  children holder. */
    void setChildrenHolder (ChildrenBomHolder_T& ioChildrenHolder) {
      _childrenHolder = &ioChildrenHolder;
    }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << toString() << std::endl;
    }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeShortKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return getKey().describe(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return getKey().toString(); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    AirlineFeatureSetStructure () : _content (NULL), _childrenHolder (NULL) { };
    AirlineFeatureSetStructure (const AirlineFeatureSetStructure&);

    /** Destructor. */
    ~AirlineFeatureSetStructure () { }

  private:
    // Attributes
    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** Holder of inventories. */
    ChildrenBomHolder_T* _childrenHolder;
  };

}
#endif // __STDAIR_BOM_AIRLINEFEATURESETSTRUCTURE_HPP

