///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Project
//       CHOPE
//
//$Application
//       Club
//
//$Name
//>       Unit.h
//
//$Summary
//       Definition file of class Unit
//
//$Description
//       Declaration module of class Unit
//
//$Content
//>       class Unit
//$History
//       $Log: Unit.h,v $
//       Revision 1.1  2005/02/21 13:18:29  chope
//       initial version
//
//
//$Version
//       $Id: Unit.h,v 1.1 2005/02/21 13:18:29 chope Exp $
//
//$Authors
//       L. Maisonobe CSSI
//       Copyright (C) 2005 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_Unit_h
#define club_Unit_h

#include <club/ClubConfig.h>

#include <xercesc/util/XMLUniDefs.hpp>
XERCES_CPP_NAMESPACE_USE

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Name
//>       class Unit
//$Summary
//        Unit is a single unit definition (used by XMLUnits).
//
//$Description
//        This class holds the definition for one unit and provides
//        conversion services between this unit to an associated
//        reference unit.
//
//$Usage
//>     construction :
//        with the conversion parameters and dimensions,
//        or from two combined units
//>     usage :
//>       const XMLCh* getSymbol             ()
//          get the symbol of the unit
//>       bool isCompatibleWith              ()
//          check if this unit is compatible with (can be converted to)
//          another one
//>       void fromReference                 ()
//          convert a scalar value from the reference unit to this one
//>       void toReference                   ()
//          convert a scalar value from this unit to the reference one
//
//$Authors
//       L. Maisonobe CSSI
//       Copyright (C) CNES 2005
//$<>
///////////////////////////////////////////////////////////////////////////////


class Unit
{
  public :

  // constructors
  Unit ();

  Unit (const XMLCh* symbol,
        int dimLength, int dimMass, int dimTime, int dimElectricCurrent,
        int dimTemperature, int dimAmountOfSubstance, int dimLuminousIntensity,
        int dimPlanarAngle, int dimSolidAngle,
        double offset, double factor);

  Unit (const XMLCh* symbol,
        const Unit& unit1, int exponent1,
        const Unit& unit2, int exponent2);

  Unit (const Unit &u);

  // affectation
  Unit& operator = (const Unit& u);

  // symbol handling
  const XMLCh* getSymbol () const { return symbol_; }
  void setSymbol (const XMLCh* symbol) { symbol_ = symbol; }

  // conversion methods
  bool   isCompatibleWith (const Unit& u) const;
  double fromReference (double value) const;
  double toReference (double value) const;

private :

  // symbol (can be used as a key) for the unit
  const XMLCh* symbol_;

  // unit dimensions
  int dimLength_;
  int dimMass_;
  int dimTime_;
  int dimElectricCurrent_;
  int dimTemperature_;
  int dimAmountOfSubstance_;
  int dimLuminousIntensity_;
  int dimPlanarAngle_;
  int dimSolidAngle_;

  // conversion parameters with the reference unit
  double offset_;
  double factor_;

};

#endif
