#ifndef __RMOL_BOM_FLIGHTDATE_HPP
#define __RMOL_BOM_FLIGHTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR
#include <stdair/bom/BomStructureList.hpp>
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BomIterator.hpp>
// RMOL 
#include <rmol/bom/FlightDateTypes.hpp>
#include <rmol/bom/SegmentDateTypes.hpp>
#include <rmol/bom/LegDateTypes.hpp>

// Forward declarations
namespace stdair {
  class FacBomContent;
  class BomStructure;
}
  
namespace RMOL {

  // Forward declarations
  class Inventory;
  
  /** Class representing the actual functional/business content for a
      flight-date. */
  class FlightDate : public stdair::BomContent {
    friend class stdair::FacBomContent;

  public:
    // Type definitions
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the types which require to be specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef Inventory ParentBomContent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef FlightDateStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef FlightDateKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef SegmentDate ContentChild_T;

        /** Definition allowing to retrieve the associated second
         BOM content child type. */
    typedef LegDate SecondContentChild_T;

    public:
    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the segment-date list iterators. */
    typedef stdair::BomConstIterator_T<SegmentDate,
                                       SegmentDateStructureList_T::const_iterator> segment_date_list_const_iterator;
    typedef stdair::BomConstIterator_T<SegmentDate,
                                       SegmentDateStructureList_T::const_reverse_iterator> segment_date_list_const_reverse_iterator;
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureList_T::const_iterator> segment_date_list_iterator;
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureList_T::const_reverse_iterator> segment_date_list_reverse_iterator;

    /** Define the segment-date map iterators. */
    typedef stdair::BomConstIterator_T<SegmentDate,
                                       SegmentDateStructureMap_T::const_iterator> segment_date_map_const_iterator;
    typedef stdair::BomConstIterator_T<SegmentDate,
                                       SegmentDateStructureMap_T::const_reverse_iterator> segment_date_map_const_reverse_iterator;
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureMap_T::const_iterator> segment_date_map_iterator;
    typedef stdair::BomIterator_T<SegmentDate,
                                  SegmentDateStructureMap_T::const_reverse_iterator> segment_date_map_reverse_iterator;

    /** Define the leg-date list iterators. */
    typedef stdair::BomConstIterator_T<LegDate,
                                       LegDateStructureList_T::const_iterator> leg_date_list_const_iterator;
    typedef stdair::BomConstIterator_T<LegDate,
                                       LegDateStructureList_T::const_reverse_iterator> leg_date_list_const_reverse_iterator;
    typedef stdair::BomIterator_T<LegDate,
                                  LegDateStructureList_T::const_iterator> leg_date_list_iterator;
    typedef stdair::BomIterator_T<LegDate,
                                  LegDateStructureList_T::const_reverse_iterator> leg_date_list_reverse_iterator;

    /** Define the leg-date map iterators. */
    typedef stdair::BomConstIterator_T<LegDate,
                                       LegDateStructureMap_T::const_iterator> leg_date_map_const_iterator;
    typedef stdair::BomConstIterator_T<LegDate,
                                       LegDateStructureMap_T::const_reverse_iterator> leg_date_map_const_reverse_iterator;
    typedef stdair::BomIterator_T<LegDate,
                                  LegDateStructureMap_T::const_iterator> leg_date_map_iterator;
    typedef stdair::BomIterator_T<LegDate,
                                  LegDateStructureMap_T::const_reverse_iterator> leg_date_map_reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
  
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;

  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _flightDateStructure;
    }

  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal const iterator on segment date:
        return the const iterator at the begining of the list. */
    segment_date_list_const_iterator segmentDateListConstIteratorBegin () const;
    
    /** Initialise the internal const iterator on segment date:
        return the const iterator at the end of the list. */
    segment_date_list_const_iterator segmentDateListConstIteratorEnd () const;

    /** Initialise the internal const reverse iterator on segment date:
        return the const reverse iterator at the rbegining of the list. */
    segment_date_list_const_reverse_iterator segmentDateListConstIteratorRBegin () const;
    
    /** Initialise the internal const reverse iterator on segment date:
        return the const reverse iterator at the end of the list. */
    segment_date_list_const_reverse_iterator segmentDateListConstIteratorREnd () const;

    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the list. */
    segment_date_list_iterator segmentDateListIteratorBegin () const;
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the list. */
    segment_date_list_iterator segmentDateListIteratorEnd () const;

    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the list. */
    segment_date_list_reverse_iterator segmentDateListIteratorRBegin () const;
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the end of the list. */
    segment_date_list_reverse_iterator segmentDateListIteratorREnd () const;

    /** Initialise the internal const iterator on segment date:
        return the const iterator at the begining of the map. */
    segment_date_map_const_iterator segmentDateMapConstIteratorBegin () const;
    
    /** Initialise the internal const iterators on segment date:
        return the const iterator at the end of the map. */
    segment_date_map_const_iterator segmentDateMapConstIteratorEnd () const;

    /** Initialise the internal const reverse iterator on segment date:
        return the const reverse iterator at the rbegining of the map. */
    segment_date_map_const_reverse_iterator segmentDateMapConstIteratorRBegin () const;
    
    /** Initialise the internal const reverse iterator on segment date:
        return the const reverse iterator at the end of the map. */
    segment_date_map_const_reverse_iterator segmentDateMapConstIteratorREnd () const;

    /** Initialise the internal iterator on segment date:
        return the iterator at the begining of the map. */
    segment_date_map_iterator segmentDateMapIteratorBegin () const;
    
    /** Initialise the internal iterator on segment date:
        return the iterator at the end of the map. */
    segment_date_map_iterator segmentDateMapIteratorEnd () const;

    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the rbegining of the map. */
    segment_date_map_reverse_iterator segmentDateMapIteratorRBegin () const;
    
    /** Initialise the internal reverse iterator on segment date:
        return the reverse iterator at the end of the map. */
    segment_date_map_reverse_iterator segmentDateMapIteratorREnd () const;

    /** Initialise the internal const iterator on leg date:
        return the const iterator at the begining of the list. */
    leg_date_list_const_iterator legDateListConstIteratorBegin () const;
    
    /** Initialise the internal const iterator on leg date:
        return the const iterator at the end of the list. */
    leg_date_list_const_iterator legDateListConstIteratorEnd () const;

    /** Initialise the internal const reverse iterator on leg date:
        return the const reverse iterator at the rbegining of the list. */
    leg_date_list_const_reverse_iterator legDateListConstIteratorRBegin () const;
    
    /** Initialise the internal const reverse iterator on leg date:
        return the const reverse iterator at the end of the list. */
    leg_date_list_const_reverse_iterator legDateListConstIteratorREnd () const;

    /** Initialise the internal iterator on leg date:
        return the iterator at the begining of the list. */
    leg_date_list_iterator legDateListIteratorBegin () const;
    
    /** Initialise the internal iterator on leg date:
        return the iterator at the end of the list. */
    leg_date_list_iterator legDateListIteratorEnd () const;

    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rbegining of the list. */
    leg_date_list_reverse_iterator legDateListIteratorRBegin () const;
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the end of the list. */
    leg_date_list_reverse_iterator legDateListIteratorREnd () const;

    /** Initialise the internal const iterator on leg date:
        return the const iterator at the begining of the map. */
    leg_date_map_const_iterator legDateMapConstIteratorBegin () const;
    
    /** Initialise the internal const iterators on leg date:
        return the const iterator at the end of the map. */
    leg_date_map_const_iterator legDateMapConstIteratorEnd () const;

    /** Initialise the internal const reverse iterator on leg date:
        return the const reverse iterator at the rbegining of the map. */
    leg_date_map_const_reverse_iterator legDateMapConstIteratorRBegin () const;
    
    /** Initialise the internal const reverse iterator on leg date:
        return the const reverse iterator at the end of the map. */
    leg_date_map_const_reverse_iterator legDateMapConstIteratorREnd () const;

    /** Initialise the internal iterator on leg date:
        return the iterator at the begining of the map. */
    leg_date_map_iterator legDateMapIteratorBegin () const;
    
    /** Initialise the internal iterator on leg date:
        return the iterator at the end of the map. */
    leg_date_map_iterator legDateMapIteratorEnd () const;

    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the rbegining of the map. */
    leg_date_map_reverse_iterator legDateMapIteratorRBegin () const;
    
    /** Initialise the internal reverse iterator on leg date:
        return the reverse iterator at the end of the map. */
    leg_date_map_reverse_iterator legDateMapIteratorREnd () const;

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    FlightDate ();
    FlightDate (const FlightDate&);
    FlightDate (BomStructure_T&);

    /** Destructor. */
    virtual ~FlightDate();

  private:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _flightDateStructure;
  };

}
#endif // __RMOL_BOM_FLIGHTDATE_HPP

