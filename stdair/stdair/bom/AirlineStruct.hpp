#ifndef __STDAIR_BOM_AIRLINESTRUCT_HPP
#define __STDAIR_BOM_AIRLINESTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
#include <vector>
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/StructAbstract.hpp>

namespace stdair {

  /** Structure holding parameters describing an airline. */
  struct AirlineStruct : public StructAbstract {
  public:
    // /////////// Getters ///////////////
    /** Get the airline code. */
    const AirlineCode_T& getAirlineCode() const {
      return _code;
    }

    /** Get the airline name. */
    const std::string& getAirlineName() const {
      return _name;
    }

    // /////////// Setters ///////////////
    /** Set the airline code. */
    void setAirlineCode (const AirlineCode_T& iAirlineCode) {
      _code = iAirlineCode;
    }

    /** Set the airline name. */
    void setAirlineName (const std::string& iAirlineName) {
      _name = iAirlineName;
    }


  public:
    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;

  
  public:
    // //////////// Constructors & Destructor ///////////////
    /** Main constructor. */
    AirlineStruct (const AirlineCode_T&, const std::string& iAirlineName);
    /** Destructor. */
    ~AirlineStruct ();
    /** Default copy constructor. */
    AirlineStruct (const AirlineStruct&);
    /** Default constructor, not to be used. */
    AirlineStruct ();
    
  private:
    // ///////////////////// Attributes //////////////////////
    /** Airline code. */
    AirlineCode_T _code;

    /** Airline name. */
    std::string _name;
  };
  
}
#endif // __STDAIR_BOM_AIRLINESTRUCT_HPP
