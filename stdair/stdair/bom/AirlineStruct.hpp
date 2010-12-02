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
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/basic/StructAbstract.hpp>

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
    /** Default constructor. */
    AirlineStruct ();
    /** Default copy constructor. */
    AirlineStruct (const AirlineStruct&);
    /** Destructor. */
    ~AirlineStruct ();

    
  private:
    // ///////////////////// Attributes //////////////////////
    /** Airline code. */
    AirlineCode_T _code;

    /** Airline name. */
    std::string _name;
  };
  
}
#endif // __STDAIR_BOM_AIRLINESTRUCT_HPP
