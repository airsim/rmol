#ifndef __STDAIR_BOM_BOMROOTSTRUCTURE_HPP
#define __STDAIR_BOM_BOMROOTSTRUCTURE_HPP

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
#include <stdair/bom/InventoryStructure.hpp>
#include <stdair/bom/NetworkStructure.hpp>

namespace stdair {
  /** Wrapper class aimed at holding the actual content, modeled
      by a specific BomContentRoot class. */
  template <typename BOM_CONTENT>
  class BomRootStructure : public BomStructure {
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

    /** Definition allowing to retrieve the second children type of the
        BOM_CONTENT. */
    typedef typename BOM_CONTENT::SecondContentChild_T SecondContentChild_T;

  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef typename BOM_CONTENT::BomKey_T BomKey_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<InventoryStructure<ContentChild_T>, 
                               NetworkStructure<SecondContentChild_T> > ChildrenBomTypeList_T;
    
    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<BomStopContent> DefaultChildrenBomHolder_T;

    /** Definition allowing to retrive the  children bom holder type. */
    typedef BomChildrenHolderImp<ContentChild_T> ChildrenBomHolder_T;

     /** Definition allowing to retrive the second children bom holder type. */
    typedef BomChildrenHolderImp<SecondContentChild_T> SecondChildrenBomHolder_T;

    /** Define the children demand stream type. */
    typedef typename BOM_CONTENT::DemandStreamContent_T DemandStream_T;
    
    /** Define the children demand stream holder type. */
    typedef BomChildrenHolderImp<DemandStream_T> DemandStreamHolder_T;
    
    /** Define the map of demand stream. */
    typedef BomMap_T<DemandStream_T> DemandStreamMap_T;


  public:
    // /////////// Getters /////////////
    /** Get the BomRootStructure key. */
    const BomKey_T& getKey () const {
      assert (_content != NULL);
      return _content->getKey ();
    }
    
    /** Get the holder of inventories. */
    const ChildrenBomHolder_T& getChildrenHolder() const {
      assert (_childrenHolder != NULL);
      return *_childrenHolder;
    }

    /** Get the holder of networks. */
    const SecondChildrenBomHolder_T& getSecondChildrenHolder() const {
      assert (_secondChildrenHolder != NULL);
      return *_secondChildrenHolder;
    }

    /** Get the holder of inventories. */
    void getChildrenHolder (ChildrenBomHolder_T*& ioChildrenHolder) {
      ioChildrenHolder = _childrenHolder;
    }

    /** Get the holder of networks. */
    void getChildrenHolder (SecondChildrenBomHolder_T*& ioChildrenHolder) {
      ioChildrenHolder = _secondChildrenHolder;
    }

    /** Get the holder of demand streams. */
    const DemandStreamHolder_T& getDemandStreamHolder() const {
      assert (_demandStreamHolder);
      return *_demandStreamHolder;
    }

    /** Get the holder of demand streams. */
    void getDemandStreamHolder (DemandStreamHolder_T*& ioDemandStreamHolder) {
      ioDemandStreamHolder = _demandStreamHolder;
    }

  private: 
    /////////////// Setters ////////////////
    /** Default children holder setter. */
    void setChildrenHolder (DefaultChildrenBomHolder_T&) { }
    
    /** Set the  children holder. */
    void setChildrenHolder (ChildrenBomHolder_T& ioChildrenHolder) {
      _childrenHolder = &ioChildrenHolder;
    }

    /** Set the network children holder. */
    void setChildrenHolder (SecondChildrenBomHolder_T& ioChildrenHolder) {
      _secondChildrenHolder = &ioChildrenHolder;
    }

    /** Set the  demand stream holder. */
    void setDemandStreamHolder (DemandStreamHolder_T& ioDemandStreamHolder) {
      _demandStreamHolder = &ioDemandStreamHolder;
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
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return getKey().toString(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return getKey().toString(); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomRootStructure () : _content (NULL), _childrenHolder (NULL),
                          _secondChildrenHolder (NULL),
                          _demandStreamHolder (NULL) { };
    BomRootStructure (const BomRootStructure&);

    /** Destructor. */
    ~BomRootStructure () { }

  private:
    // Attributes
    /** The actual functional (Business Object) content. */
    BOM_CONTENT* _content;

    /** Holder of inventories. */
    ChildrenBomHolder_T* _childrenHolder;
    
    /** Holder of networks. */
    SecondChildrenBomHolder_T* _secondChildrenHolder;

    /** Holder of demand streams. */
    DemandStreamHolder_T* _demandStreamHolder;
  };

}
#endif // __STDAIR_BOM_BOMROOTSTRUCTURE_HPP

