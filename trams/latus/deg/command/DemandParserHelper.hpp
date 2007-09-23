#ifndef __LATUS_DEG_CMD_DEMANDPARSERHELPER_HPP
#define __LATUS_DEG_CMD_DEMANDPARSERHELPER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost Spirit (Parsing)
#include <boost/spirit/core.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
// LATUS Common
#include <latus/com/command/CmdAbstract.hpp>
// LATUS DEG
#include <latus/deg/bom/DemandStruct.hpp>

namespace LATUS {

  // Forward declarations
  namespace COM {
    class WholeDemand;
  }
  
  namespace DEG {

    namespace DemandParserHelper {
      
      // ///////////////////////////////////////////////////////////////////////
      //
      //  Definition of Basic Types
      //
      // ///////////////////////////////////////////////////////////////////////
      // For a file, the parsing unit is the character (char). For a string,
      // it is a "char const *".
      // typedef char const* iterator_t;
      typedef char char_t;
    
      // The types of iterator, scanner and rule are then derived from
      // the parsing unit.
      typedef boost::spirit::file_iterator<char_t> iterator_t;
      typedef boost::spirit::scanner<iterator_t> scanner_t;
      typedef boost::spirit::rule<scanner_t> rule_t;

      
      // ///////////////////////////////////////////////////////////////////////
      //
      //  Semantic actions
      //
      // ///////////////////////////////////////////////////////////////////////
      /** Generic Semantic Action (Actor / Functor) for the Demand Parser. */
      struct ParserSemanticAction {
        /** Actor Constructor. */
        ParserSemanticAction (DemandStruct_T&);
        /** Actor Context. */
        DemandStruct_T& _demand;
      };
      
      /** Store the start of the departure date. */
      struct storeDepartureDate : public ParserSemanticAction {
        /** Actor Constructor. */
        storeDepartureDate (DemandStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the parsed origin. */
      struct storeOrigin : public ParserSemanticAction {
        /** Actor Constructor. */
        storeOrigin (DemandStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };
  
      /** Store the parsed destination. */
      struct storeDestination : public ParserSemanticAction {
        /** Actor Constructor. */
        storeDestination (DemandStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the parsed WTP. */
      struct storeWTPValue : public ParserSemanticAction {
        /** Actor Constructor. */
        storeWTPValue (DemandStruct_T&);
        /** Actor Function (functor). */
        void operator() (double iReal) const;
      };
  
      /** Store the parsed currency. */
      struct storeCurrency : public ParserSemanticAction {
        /** Actor Constructor. */
        storeCurrency (DemandStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
      };

      /** Store the parsed demand mean value. */
      struct storeDemandMean : public ParserSemanticAction {
        /** Actor Constructor. */
        storeDemandMean (DemandStruct_T&);
        /** Actor Function (functor). */
        void operator() (double iReal) const;
      };
  
      /** Store the parsed demand standard deviation value. */
      struct storeDemandStdDev : public ParserSemanticAction {
        /** Actor Constructor. */
        storeDemandStdDev (DemandStruct_T&);
        /** Actor Function (functor). */
        void operator() (double iReal) const;
      };
  
      /** Mark the end of the demand parsing. */
      struct doEndDemand : public ParserSemanticAction {
        /** Actor Constructor. */
        doEndDemand (COM::WholeDemand&, DemandStruct_T&);
        /** Actor Function (functor). */
        void operator() (iterator_t iStr, iterator_t iStrEnd) const;
        /** Actor Specific Context. */
        COM::WholeDemand& _wholeDemand;
      };
  

      /////////////////////////////////////////////////////////////////////////
      //
      //  (Boost Spirit) Grammar Definition
      //
      /////////////////////////////////////////////////////////////////////////
      /**
         Origin; Destination; DepartureDate; Price; DemandMean; DemandStDev;
         NCE; MIA; 2007-06-20; 1000.0; 10.1; 2.5;
         
         Grammar:
         Demand              ::= Origin ';' Destination ';' DepartureDate
                                 ';' Price ';' DemandMean ';' DemandStDev
                                 EndOfDemand
         EndOfDemand         ::= ';'
      */

      /** Grammar for the Demand parser. */
      struct DemandDetailsParser : 
        public boost::spirit::grammar<DemandDetailsParser> {

        DemandDetailsParser (COM::WholeDemand&, DemandStruct_T&);

        template <typename ScannerT>
        struct definition {
          definition (DemandDetailsParser const& self);

          // Instantiation of rules
          boost::spirit::rule<ScannerT> demand_list, comments, demand, date,
            demand_end;

          /** Entry point of the parser. */
          boost::spirit::rule<ScannerT> const& start() const;
        };

        // Parser Context
        COM::WholeDemand& _wholeDemand;
        DemandStruct_T& _demand;
      };

    }


    /////////////////////////////////////////////////////////////////////////
    //
    //  Entry class for the file parser
    //
    /////////////////////////////////////////////////////////////////////////
    /** Class wrapping the initialisation and entry point of the parser.
        <br>The seemingly redundancy is used to force the instantiation of
        the actual parser, which is a templatised Boost Spirit grammar.
        Hence, the actual parser is instantiated within that class object
        code. */
    class DemandFileParser : public COM::CmdAbstract {
    public:
      /** Constructor. */
      DemandFileParser (COM::WholeDemand& ioWholeDemand,
                        const std::string& iFilename);

      /** Parse the input file and generate the Demands. */
      void generateDemands ();
      
    private:
      /** Initialise. */
      void init();
      
    private:
      // Attributes
      /** File-name of the CSV-formatted demand input file. */
      std::string _filename;

      /** Start iterator for the parser. */
      DemandParserHelper::iterator_t _startIterator;
      
      /** End iterator for the parser. */
      DemandParserHelper::iterator_t _endIterator;
      
      /** WholeDemand. */
      COM::WholeDemand& _wholeDemand;

      /** Flight-Period Structure. */
      DemandStruct_T _demand;
    };
    
  }
}
#endif // __LATUS_DEG_CMD_DEMANDPARSERHELPER_HPP
