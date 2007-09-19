// //////////////////////////////////////////////////////////////////////
// Copyright of this program is the property of AMADEUS, without
// whose written permission reproduction in whole or in part is prohibited.
//
// Package name: Common
// Layer   name: basic
//
// File name   : BasConst_ClassStruct.hpp
//
// Purpose     : 
//
// Language    : C++
//
// //////////////////////////////////////////////////////////////////////
#ifndef __LATUS_COM_BAS_BASCONST_CLASSSTRUCT_HPP
#define __LATUS_COM_BAS_BASCONST_CLASSSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>

namespace LATUS {

  namespace COM {

    // //////// (Segment-)Class-related BOM ///////
    /** Default booking number for ClassStruct_T. */
    extern const BookingNumber_T DEFAULT_CLASS_BOOKING_NUMBER;
    
    /** Default availability for ClassStruct_T. */
    extern const Availability_T DEFAULT_CLASS_AVAILABILITY;

    /** Default boolean for booking Constraint availability for ClassStruct_T. */
    extern const BookingConstraint_T DEFAULT_CLASS_BOOKING_CONSTRAINT;

    /** Default booking constraint value for ClassStruct_T. */
    extern const BookingConstraintValue_T DEFAULT_CLASS_BOOKING_CONSTRAINT_VALUE;

    /** Default over-booking rate for ClassStruct_T. */
    extern const OverbookingRate_T DEFAULT_CLASS_OVERBOOKING_RATE;

  }
}
#endif // __LATUS_COM_BAS_BASCONST_CLASSSTRUCT_HPP
