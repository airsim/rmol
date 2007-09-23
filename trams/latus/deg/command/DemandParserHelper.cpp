// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// Boost Spirit (Parsing)
//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute.hpp>
#include <boost/spirit/utility/loops.hpp>
#include <boost/spirit/utility/chset.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/spirit/actor/assign_actor.hpp>
// LATUS Common
#include <latus/com/bom/WholeDemand.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS DEG
#include <latus/deg/command/DemandParserHelper.hpp>
#include <latus/deg/command/DemandGenerator.hpp>

namespace LATUS {

  namespace DEG {

    namespace DemandParserHelper {
      
      // //////////////////////////////////////////////////////////////////////
      //
      //  Semantic actions
      //
      // //////////////////////////////////////////////////////////////////////

      // //////////////////////////////////////////////////////////////////////
      ParserSemanticAction::ParserSemanticAction (DemandStruct_T& ioDemand)
        : _demand (ioDemand) {
      }      

      // //////////////////////////////////////////////////////////////////////
      storeDepartureDate::storeDepartureDate (DemandStruct_T& ioDemand)
        : ParserSemanticAction (ioDemand) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeDepartureDate::operator() (iterator_t iStr,
                                           iterator_t iStrEnd) const {
        _demand._departureDate = _demand.getDate();
        // std::cout << "Departure Date: "
        // << _demand._departureDate << std::endl;
      }
      
      // //////////////////////////////////////////////////////////////////////
      storeOrigin::storeOrigin (DemandStruct_T& ioDemand)
        : ParserSemanticAction (ioDemand) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeOrigin::operator() (iterator_t iStr,
                                    iterator_t iStrEnd) const {
        std::string lOrigin (iStr, iStrEnd);
        // std::cout << "Origin: " << lOrigin << std::endl;

        // Set the origin
        _demand._origin = lOrigin;
      }

      // //////////////////////////////////////////////////////////////////////
      storeDestination::storeDestination (DemandStruct_T& ioDemand)
        : ParserSemanticAction (ioDemand) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeDestination::operator() (iterator_t iStr,
                                    iterator_t iStrEnd) const {
        std::string lDestination (iStr, iStrEnd);
        // std::cout << "Destination: " << lDestination << std::endl;

        // Set the destination
        _demand._destination = lDestination;
      }

      // //////////////////////////////////////////////////////////////////////
      storeWTPValue::
      storeWTPValue (DemandStruct_T& ioDemand)
        : ParserSemanticAction (ioDemand) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeWTPValue::operator() (double iReal) const { 
        _demand._wtp = iReal; 
        // std::cout << "WTP: " << iReal << std::endl;
      }

      // //////////////////////////////////////////////////////////////////////
      storeCurrency::storeCurrency (DemandStruct_T& ioDemand)
        : ParserSemanticAction (ioDemand) {
      }

      // //////////////////////////////////////////////////////////////////////
      void storeCurrency::operator() (iterator_t iStr,
                                      iterator_t iStrEnd) const {
        std::string lCurrency (iStr, iStrEnd);
        // std::cout << "Currency: " << lCurrency << std::endl;

        // Set the currency
        _demand._currency = lCurrency;
      }

      // //////////////////////////////////////////////////////////////////////
      storeDemandMean::storeDemandMean (DemandStruct_T& ioDemand)
        : ParserSemanticAction (ioDemand) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeDemandMean::operator() (double iReal) const { 
        _demand._demandMean = iReal; 
        // std::cout << "Demand Mean: " << iReal << std::endl;
      }

      // //////////////////////////////////////////////////////////////////////
      storeDemandStdDev::storeDemandStdDev (DemandStruct_T& ioDemand)
        : ParserSemanticAction (ioDemand) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void storeDemandStdDev::operator() (double iReal) const { 
        _demand._demandStdDev = iReal; 
        // std::cout << "Demand StdDev: " << iReal << std::endl;
      }

      // //////////////////////////////////////////////////////////////////////
      doEndDemand::
      doEndDemand (COM::WholeDemand& ioWholeDemand, DemandStruct_T& ioDemand)
        : ParserSemanticAction (ioDemand), _wholeDemand (ioWholeDemand) {
      }
    
      // //////////////////////////////////////////////////////////////////////
      void doEndDemand::operator() (iterator_t iStr,
                                    iterator_t iStrEnd) const {
        // std::cout << "End of Flight-Period " << std::endl;

        // DEBUG: Display the result
        LATUS_LOG_DEBUG ("Demand: " << _demand.describe());

        // Create the WholeDemand BOM objects, and potentially the intermediary
        // objects (e.g., WholeDemandDate and ClassPath).
        DemandGenerator::createDemands (_wholeDemand, _demand);
      }

      
      // ///////////////////////////////////////////////////////////////////////
      //
      //  Utility Parsers
      //
      // ///////////////////////////////////////////////////////////////////////
      /** 2-digit-integer parser */
      typedef boost::spirit::uint_parser<int, 10, 2, 2> uint2_p_t;
      uint2_p_t uint2_p;
    
      /** 4-digit-integer parser */
      typedef boost::spirit::uint_parser<int, 10, 4, 4> uint4_p_t;
      uint4_p_t uint4_p;
    
      /** Sequence of (capital) alpha-numeric characters: chset_p("0-9A-Z") */
      boost::spirit::chset<char_t> alpha_cap_num_set_p ("0-9A-Z");
      
      /** Sequence of (capital) alphabetical characters: chset_p("A-Z") */
      boost::spirit::chset<char_t> alpha_cap_set_p ("A-Z");
      
      /** (Repeating) sequence of a given number of characters:
          repeat_p(min, max) */
      typedef boost::spirit::impl::loop_traits<boost::spirit::chset<char_t>,
                                               unsigned int,
                                               unsigned int>::type repeat_p_t;

      /** Currency Parser: repeat_p(3)[chset_p("A-Z")] */
      repeat_p_t currency_p (alpha_cap_set_p.derived(), 3, 3);
      
      /** Year Parser: limit_d(2000u, 2099u)[uint4_p] */
      boost::spirit::bounded<uint4_p_t, unsigned int> year_p (uint4_p.derived(),
                                                              2000u, 2099u);
      
      /** Month Parser: limit_d(1u, 12u)[uint2_p] */
      boost::spirit::bounded<uint2_p_t,
                             unsigned int> month_p (uint2_p.derived(), 1u, 12u);

      /** Day Parser: limit_d(1u, 31u)[uint2_p] */
      boost::spirit::bounded<uint2_p_t, unsigned int> day_p (uint2_p.derived(),
                                                             1u, 31u);

      /** Airport Parser: repeat_p(3)[chset_p("0-9A-Z")] */
      repeat_p_t airport_p (alpha_cap_num_set_p.derived(), 3, 3);
      

      /////////////////////////////////////////////////////////////////////////
      //
      //  (Boost Spirit) Grammar Definition
      //
      /////////////////////////////////////////////////////////////////////////

      // //////////////////////////////////////////////////////////////////////
      DemandDetailsParser::
      DemandDetailsParser (COM::WholeDemand& ioWholeDemand,
                           DemandStruct_T& ioDemand) 
        : _wholeDemand (ioWholeDemand), _demand (ioDemand) {
      }

      // //////////////////////////////////////////////////////////////////////
      template<typename ScannerT>
      DemandDetailsParser::definition<ScannerT>::
      definition (DemandDetailsParser const& self) {

        demand_list = *( comments | demand )
          ;
      
        comments = boost::spirit::comment_p("//")
          | boost::spirit::comment_p("/*", "*/")
          ;
        
        demand =
          (airport_p)[storeOrigin(self._demand)]
          >> ';' >> (airport_p)[storeDestination(self._demand)]
          >> ';' >> date[storeDepartureDate(self._demand)]
          >> ';' >> (boost::spirit::ureal_p)[storeWTPValue(self._demand)]
          >> ';' >> (currency_p)[storeCurrency(self._demand)]
          >> ';' >> (boost::spirit::ureal_p)[storeDemandMean(self._demand)]
          >> ';' >> (boost::spirit::ureal_p)[storeDemandStdDev(self._demand)]
          >> demand_end[doEndDemand(self._wholeDemand, self._demand)]
          ;

        demand_end = boost::spirit::ch_p(';')
          ;
      
        date = boost::spirit::lexeme_d[
              (year_p)[boost::spirit::assign_a(self._demand._itYear)]
              >> '-'
              >> (month_p)[boost::spirit::assign_a(self._demand._itMonth)]
              >> '-'
              >> (day_p)[boost::spirit::assign_a(self._demand._itDay)]
                                       ]
          ;

        
        // BOOST_SPIRIT_DEBUG_NODE (DemandDetailsParser);
        BOOST_SPIRIT_DEBUG_NODE (demand_list);
        BOOST_SPIRIT_DEBUG_NODE (comments);
        BOOST_SPIRIT_DEBUG_NODE (demand);
        BOOST_SPIRIT_DEBUG_NODE (date);
        BOOST_SPIRIT_DEBUG_NODE (demand_end);
      }

      // //////////////////////////////////////////////////////////////////////
      template<typename ScannerT>
      boost::spirit::rule<ScannerT> const&
      DemandDetailsParser::definition<ScannerT>::start() const {
        return demand_list;
      }
    }


    /////////////////////////////////////////////////////////////////////////
    //
    //  Entry class for the file parser
    //
    /////////////////////////////////////////////////////////////////////////

    // //////////////////////////////////////////////////////////////////////
    DemandFileParser::DemandFileParser (COM::WholeDemand& ioWholeDemand,
                                        const std::string& iFilename)
      : _wholeDemand (ioWholeDemand), _filename (iFilename) {
      init();
    }

    // //////////////////////////////////////////////////////////////////////
    void DemandFileParser::init() {
      // Open the file
      _startIterator = DemandParserHelper::iterator_t (_filename);

      // Check the filename exists and can be open
      if (!_startIterator) {
        std::cerr << "The file " << _filename << " can not be open."
                  << std::endl;
      }

      // Create an EOF iterator
      _endIterator = _startIterator.make_end();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void DemandFileParser::generateDemands () {

      LATUS_LOG_DEBUG ("Parsing demand input file: " << _filename);

      // Initialise the parser (grammar) with the helper/staging structure.
      DemandParserHelper::DemandDetailsParser lFPParser (_wholeDemand, _demand);
      
      // Launch the parsing of the file and, thanks to the doEndFlight
      // call-back structure, the building of the whole WholeDemand BOM
      // (i.e., including Inventory, FlightDate, LegDate, SegmentDate, etc.)
      boost::spirit::parse_info<DemandParserHelper::iterator_t> info =
        boost::spirit::parse (_startIterator, _endIterator, lFPParser, 
                              boost::spirit::space_p);

      if (info.full) {
        LATUS_LOG_DEBUG ("Parsing of demand input file: " << _filename
                         << " succeeded.");
        
      } else {
        // TODO: decide whether to throw an exception
        LATUS_LOG_ERROR ("Parsing of demand input file: " << _filename
                         << " failed.");
      }
     }
    
  }
}
