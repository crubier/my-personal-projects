////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//        DEF
//
//$Project
//        CHOPE
//
//$Application
//        Club
//
//$Name
//>       Unit.cpp
//
//$Summary
//       file implementing functions of class Unit
//
//$Description
//       Definition module of class Unit
//
//$Content
//>       class Unit
//>         Unit()
//>         ~Unit()
//>         isCompatibleWith()
//>         fromReference()
//>         toReference()
//
//$History
//       $Log: Unit.cpp,v $
//       Revision 1.1  2005/02/21 13:28:38  chope
//       initial version
//
//
//$Version
//       $Id: Unit.cpp,v 1.1 2005/02/21 13:28:38 chope Exp $
//
//$Authors
//       L. Maisonobe  CSSI
//       Copyright (C) CNES 2005
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#ifdef HAVE_STL
# include <string>
# include <map>
#endif

#include <cmath>

#include <club/Unit.h>

Unit::Unit ()
  : symbol_ (0),
    dimLength_ (0), dimMass_ (0), dimTime_ (0), dimElectricCurrent_ (0),
    dimTemperature_ (0), dimAmountOfSubstance_ (0), dimLuminousIntensity_ (0),
    dimPlanarAngle_ (0), dimSolidAngle_ (0),
    offset_ (0.0), factor_ (1.0)
{
}

Unit::Unit (const XMLCh* symbol,
            int dimLength, int dimMass, int dimTime,
            int dimElectricCurrent, int dimTemperature,
            int dimAmountOfSubstance, int dimLuminousIntensity,
            int dimPlanarAngle, int dimSolidAngle,
            double offset, double factor)
  : symbol_ (symbol),
    dimLength_ (dimLength), dimMass_ (dimMass), dimTime_ (dimTime),
    dimElectricCurrent_ (dimElectricCurrent),
    dimTemperature_ (dimTemperature),
    dimAmountOfSubstance_ (dimAmountOfSubstance),
    dimLuminousIntensity_ (dimLuminousIntensity),
    dimPlanarAngle_ (dimPlanarAngle), dimSolidAngle_ (dimSolidAngle),
    offset_ (offset), factor_ (factor)
{
}

Unit::Unit (const XMLCh* symbol,
            const Unit& unit1, int exponent1,
            const Unit& unit2, int exponent2)
  : symbol_ (symbol)
{

  // combine dimensions
  dimLength_            = exponent1 * unit1.dimLength_
                        + exponent2 * unit2.dimLength_;
  dimMass_              = exponent1 * unit1.dimMass_
                        + exponent2 * unit2.dimMass_;
  dimTime_              = exponent1 * unit1.dimTime_
                        + exponent2 * unit2.dimTime_;
  dimElectricCurrent_   = exponent1 * unit1.dimElectricCurrent_
                        + exponent2 * unit2.dimElectricCurrent_;
  dimTemperature_       = exponent1 * unit1.dimTemperature_
                        + exponent2 * unit2.dimTemperature_;
  dimAmountOfSubstance_ = exponent1 * unit1.dimAmountOfSubstance_
                        + exponent2 * unit2.dimAmountOfSubstance_;
  dimLuminousIntensity_ = exponent1 * unit1.dimLuminousIntensity_
                        + exponent2 * unit2.dimLuminousIntensity_;
  dimPlanarAngle_       = exponent1 * unit1.dimPlanarAngle_
                        + exponent2 * unit2.dimPlanarAngle_;
  dimSolidAngle_        = exponent1 * unit1.dimSolidAngle_
                        + exponent2 * unit2.dimSolidAngle_;

  // compute conversion parameters. Note that offset is always null
  // for combined unit, because multiplicative combination has a
  // meaning of difference ratios or difference multiplications. As an
  // example, the "Celsius degree per meter" unit represents a
  // temperature gradient related to temperature differences for a
  // given position difference. This implies that 1 Celsius degree per
  // meter converts to 1.8 Fahrenheit degree per meter, despite the
  // thermodynamic temperature of 1 Celsius degree converts to 33.8
  // Fahrenheit degree
  offset_ = 0.0;
  factor_ = pow (unit1.factor_, exponent1) * pow (unit2.factor_, exponent2);

}

Unit::Unit (const Unit &u)
  : symbol_ (u.symbol_),
    dimLength_ (u.dimLength_), dimMass_ (u.dimMass_), dimTime_ (u.dimTime_),
    dimElectricCurrent_ (u.dimElectricCurrent_),
    dimTemperature_ (u.dimTemperature_),
    dimAmountOfSubstance_ (u.dimAmountOfSubstance_),
    dimLuminousIntensity_ (u.dimLuminousIntensity_),
    dimPlanarAngle_ (u.dimPlanarAngle_), dimSolidAngle_ (u.dimSolidAngle_),
    offset_ (u.offset_), factor_ (u.factor_)
{
}

Unit& Unit::operator = (const Unit& u)
{
  if (this != &u) // protection against x = x
    {
      symbol_               = u.symbol_;
      dimLength_            = u.dimLength_;
      dimMass_              = u.dimMass_;
      dimTime_              = u.dimTime_;
      dimElectricCurrent_   = u.dimElectricCurrent_;
      dimTemperature_       = u.dimTemperature_;
      dimAmountOfSubstance_ = u.dimAmountOfSubstance_;
      dimLuminousIntensity_ = u.dimLuminousIntensity_;
      dimPlanarAngle_       = u.dimPlanarAngle_;
      dimSolidAngle_        = u.dimSolidAngle_;
      offset_               = u.offset_;
      factor_               = u.factor_;
    }
  return *this;
}

bool Unit::isCompatibleWith(const Unit& u) const
{
  return (dimLength_            == u.dimLength_)
      && (dimMass_              == u.dimMass_)
      && (dimTime_              == u.dimTime_)
      && (dimElectricCurrent_   == u.dimElectricCurrent_)
      && (dimTemperature_       == u.dimTemperature_)
      && (dimAmountOfSubstance_ == u.dimAmountOfSubstance_)
      && (dimLuminousIntensity_ == u.dimLuminousIntensity_)
      && (dimPlanarAngle_       == u.dimPlanarAngle_)
      && (dimSolidAngle_        == u.dimSolidAngle_);
}

double Unit::fromReference (double value) const
{
  return (value - offset_) / factor_;
}

double Unit::toReference (double value) const
{
  return (value *  factor_) + offset_;
}
