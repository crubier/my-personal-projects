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
//>       XMLUnits.cpp
//
//$Summary
//       file implementing functions of class XMLUnits
//
//$Description
//       Definition module of class XMLUnits
//
//$Content
//>       class XMLUnits
//>         XMLUnits()
//>         ~XMLUnits()
//>         convert()
//>         toString()
//>         parseHexaChar()
//>         parseDeciChar()
//>         parsePredefinedEntityChar()
//>         removeCharReferences()
//>         cacheSymbol()
//
//$History
//       $Log: XMLUnits.cpp,v $
//       Revision 1.3  2005/02/25 07:44:31  chope
//       removed the acceptNode method
//
//       Revision 1.1  2005/02/04 10:19:18  chope
//       initial version
//
//
//$Version
//       $Id: XMLUnits.cpp,v 1.3 2005/02/25 07:44:31 chope Exp $
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI
//       Copyright (C) CNES 2000
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#if STDC_HEADERS
# include <cmath>
#endif

#ifdef HAVE_SSTREAM
# include <sstream>
#endif

#ifdef HAVE_FSTREAM
# include <fstream>
#endif
#include <sys/stat.h>

#include "club/ClubErreurs.h"
#include "club/XMLUnits.h"
#include "XMLSharedStrings.h"
#include "XMLUnitsStrings.h"

// Unicode values for some specific characters
// we handle through predefined entities
static const XMLCh DEG_CODE   = 0x00B0;
static const XMLCh MICRO_CODE = 0x00B5;
static const XMLCh OHM_CODE   = 0x2126;

// this constructor is NOT used
XMLUnits::XMLUnits (const XMLUnits & other)
  : XMLFile (CLUB_UNIT_TAG, UNITS_DTD_PUB_ID, UNITS_DTD_SYS_ID)
{
}

// Create an instance by loading a file
XMLUnits::XMLUnits (const string& fileName)
  throw (ClubErreurs)
  : XMLFile (fileName)
{
  // build Unit instances from the XML document
  DOMNodeList* list1 = document_->getDocumentElement()->getChildNodes ();
  for (XMLSize_t i = 0; i < list1->getLength (); ++i)
    if (list1->item (i)->getNodeType () == DOMNode::ELEMENT_NODE)
    {
      DOMElement* referenceElement = (DOMElement *) list1->item (i);

      int dimLength            = getInt (referenceElement, DIM_LENGTH_ATTRIBUTE);
      int dimMass              = getInt (referenceElement, DIM_MASS_ATTRIBUTE);
      int dimTime              = getInt (referenceElement, DIM_TIME_ATTRIBUTE);
      int dimElectricCurrent   = getInt (referenceElement, DIM_ELECTRIC_CURRENT_ATTRIBUTE);
      int dimTemperature       = getInt (referenceElement, DIM_TEMPERATURE_ATTRIBUTE);
      int dimAmountOfSubstance = getInt (referenceElement, DIM_AMOUNT_OF_SUBSTANCE_ATTRIBUTE);
      int dimLuminousIntensity = getInt (referenceElement, DIM_LUMINOUS_INTENSITY_ATTRIBUTE);
      int dimPlanarAngle       = getInt (referenceElement, DIM_PLANAR_ANGLE_ATTRIBUTE);
      int dimSolidAngle        = getInt (referenceElement, DIM_SOLID_ANGLE_ATTRIBUTE);

      // insert reference unit in the map
      const XMLCh* symbol = referenceElement->getAttribute (SYMBOL_ATTRIBUTE);
      if (units_.count (symbol) != 0)
        throw ClubErreurs (ClubErreurs::redefined_unit,
                           toString (symbol).c_str ());
      Unit unit (symbol,
                 dimLength, dimMass, dimTime, dimElectricCurrent,
                 dimTemperature, dimAmountOfSubstance,
                 dimLuminousIntensity, dimPlanarAngle, dimSolidAngle,
                 0.0, 1.0);
      units_.insert (UnitsMap::value_type (symbol, unit));

      // insert associated alternate units in the map
      DOMNodeList* list2 = referenceElement->getChildNodes ();
      for (XMLSize_t j = 0; j < list2->getLength (); ++j)
        if (list2->item (j)->getNodeType () == DOMNode::ELEMENT_NODE)
        {
          DOMElement* alternateElement = (DOMElement *) list2->item (j);
          if (alternateElement != 0)
          {
            symbol = alternateElement->getAttribute (SYMBOL_ATTRIBUTE);
            if (units_.count (symbol) != 0)
              throw ClubErreurs (ClubErreurs::redefined_unit,
                                 toString (symbol).c_str ());
            Unit unit (symbol,
                       dimLength, dimMass, dimTime, dimElectricCurrent,
                       dimTemperature, dimAmountOfSubstance,
                       dimLuminousIntensity, dimPlanarAngle, dimSolidAngle,
                       getDouble (alternateElement, OFFSET_ATTRIBUTE),
                       getDouble (alternateElement, FACTOR_ATTRIBUTE));
            units_.insert (UnitsMap::value_type (symbol, unit));
          }
        }

    }
}

// delete an instance
XMLUnits::~XMLUnits ()
{
}

// convert a value from one unit to another one
double XMLUnits::convert (double value, const XMLCh* fromUnit,
                          const XMLCh* toUnit) const
  throw (ClubErreurs)
{

  // cache the unit if not aleady known
  cacheSymbol (fromUnit);
  cacheSymbol (toUnit);

  // check if the conversion is allowed
  Unit from = units_ [fromUnit];
  Unit to   = units_ [toUnit];
  if (! from.isCompatibleWith (to))
    throw ClubErreurs (ClubErreurs::incompatible_units,
                       toString (fromUnit).c_str (),
                       toString (toUnit).c_str ());

  // perform the conversion
  return to.fromReference (from.toReference (value));

}

// convert a XML string into a STL string
string XMLUnits::toString (const XMLCh* s) const
{

  // since &deg; and &micro; can be represented in ISO-8859-1
  // we look only for &ohm; replacement
  int nbOhm = -1;
  for (const XMLCh* cursor = s; cursor != 0;)
  {
    int next = XMLString::indexOf (cursor, OHM_CODE);
    cursor = (next >= 0) ? (cursor + next + 1) : 0;
    ++nbOhm;
  }

  if (nbOhm == 0)
    return XMLFile::toString (s);

  // we need to get rid of the ohm characters before transcoding
  int len = XMLString::stringLen (s) + (nbOhm * 4) + 1;
  XMLCh *work =
    (XMLCh*) XMLPlatformUtils::fgMemoryManager->allocate(len * sizeof(XMLCh));
  ArrayJanitor<XMLCh> janitor (work, XMLPlatformUtils::fgMemoryManager);
  XMLString::copyString (work, s);

  // replace all ohm characters
  for (XMLCh* cursor = work; cursor != 0;)
  {
    int next = XMLString::indexOf (cursor, OHM_CODE);
    if (next >= 0)
    {
      cursor += next;

      // shift the end of the string
      for (XMLCh* ptr = cursor + XMLString::stringLen (cursor); ptr != cursor; --ptr)
        *(ptr + 4) = *ptr;

      // replace the single character by an entity reference
      *cursor++ = chAmpersand;
      *cursor++ = chLatin_o;
      *cursor++ = chLatin_h;
      *cursor++ = chLatin_m;
      *cursor++ = chSemiColon;

    }
    else
      cursor = 0;
  }

  // convert the string
  return XMLFile::toString (work);

}

XMLCh XMLUnits::parseHexaChar (const XMLCh* s, int start, int end) const
  throw (ClubErreurs)
{
  if (end <= start)
    throw ClubErreurs (ClubErreurs::entity_syntax_error,
                       XMLFile::toString (s).c_str ());

  // start with a 0 code
  XMLCh character = 0;

  // parse the hexadecimal character code
  while (start < end)
  {
    if (XMLString::isHex (s [start]))
    {
      if (XMLString::isDigit (s [start]))
        character = character * 16 + (s [start] - chDigit_0);
      else if ((s [start] - chLatin_A) < 6)
        character = character * 16 + (s [start] - chLatin_A + 10);
      else
        character = character * 16 + (s [start] - chLatin_a + 10);
      ++start;
    }
    else
      throw ClubErreurs (ClubErreurs::entity_syntax_error,
                         XMLFile::toString (s).c_str ());
  }

  return character;

}

XMLCh XMLUnits::parseDeciChar (const XMLCh* s, int start, int end) const
  throw (ClubErreurs)
{
  if (end <= start)
    throw ClubErreurs (ClubErreurs::entity_syntax_error,
                       XMLFile::toString (s).c_str ());

  // start with a 0 code
  XMLCh character = 0;

  // parse the decimal character code
  while (start < end)
  {
    if (XMLString::isDigit (s [start]))
    {
      character = character * 16 + (s [start] - chDigit_0);
      ++start;
    }
    else
      throw ClubErreurs (ClubErreurs::entity_syntax_error,
                         XMLFile::toString (s).c_str ());
  }

  return character;

}

XMLCh XMLUnits::parsePredefinedEntityChar (XMLCh* s, int start, int end) const
  throw (ClubErreurs)
{
  if (end <= start)
    throw ClubErreurs (ClubErreurs::entity_syntax_error,
                       XMLFile::toString (s).c_str ());

  XMLCh character = chNull;
  XMLCh endChar = s [end];
  s [end] = chNull;
  if (XMLString::compareString (s + start, DEG_ENTITY) == 0)
    character = DEG_CODE;
  else if (XMLString::compareString (s + start, MICRO_ENTITY) == 0)
    character = MICRO_CODE;
  else if (XMLString::compareString (s + start, OHM_ENTITY) == 0)
    character = OHM_CODE;
  else
  {
    ArrayJanitor<XMLCh> janitor (XMLString::replicate (s + start,
                                                       XMLPlatformUtils::fgMemoryManager),
                                 XMLPlatformUtils::fgMemoryManager);
    s [end] = endChar;
    ClubErreurs e (ClubErreurs::unknown_general_entity,
                   XMLFile::toString (janitor.get ()).c_str (),
                   XMLFile::toString (s).c_str ());
    throw e;
  }

  s [end] = endChar;
  return character;

}

// remove character references in a XML string
void XMLUnits::removeCharReferences (XMLCh* s) const
  throw (ClubErreurs)
{
  // loop over all references
  for (int start = XMLString::indexOf (s, chAmpersand);
       start >= 0;
       start = XMLString::indexOf (s, chAmpersand)) {

    // we have found a reference start, look for its end
    int end = start + 1 + XMLString::indexOf (s + start + 1, chSemiColon);
    if (end < (start + 2))
      throw ClubErreurs (ClubErreurs::entity_syntax_error,
                         XMLFile::toString (s).c_str ());

    // replace the '&' character by the desired character
    if (s [start + 1] == chPound)
    {
      if (s [start + 2] == chLatin_x)
        s [start] = parseHexaChar (s, start + 3, end);
      else
        s [start] = parseDeciChar (s, start + 2, end);
    }
    else
      s [start] = parsePredefinedEntityChar (s, start + 1, end);

    // remove the rest of the character or entity reference
    int delta = end - start;
    do
    {
      ++start;
      s [start] = s [start + delta];
    } while (s [start] != chNull);

  }

}

// analyze and cache a unit symbol
void XMLUnits::cacheSymbol (const XMLCh* symbol) const
  throw (ClubErreurs)
{

  // is the unit already cached ?
  if (units_.count (symbol) != 0)
    return;

  Unit unit;
  bool first     = true;
  bool numerator = true;
  ArrayJanitor<XMLCh> janitor (XMLString::replicate (symbol,
                                                     XMLPlatformUtils::fgMemoryManager),
                               XMLPlatformUtils::fgMemoryManager);
  removeCharReferences (janitor.get ());
  XMLCh *start = janitor.get ();
  while (*start != chNull)
  {

    // get the next basic unit specifier
    XMLCh *end = XMLString::findAny (start, SPECIAL_CHARS_LIST);
    if (end == 0)
      end = start + XMLString::stringLen (start);
    XMLCh endChar = *end;
    *end = chNull;
    if (units_.count (start) == 0)
      throw ClubErreurs (ClubErreurs::undefined_unit,
                         toString (start).c_str ());
    const Unit& basic = units_ [start];
    *end = endChar;

    int exponent = 1;
    if ((*end == chCaret)
        || ((*end == chAsterisk) && (*(end + 1) == chAsterisk)))
    { // there is an exponent specifier
      start = end + ((*end == chCaret) ? 1 : 2);
      end = start + (((*start == chPlus) || (*start == chDash)) ? 1 : 0);
      while (XMLString::isDigit (*end))
        ++end;
      endChar  = *end;
      *end     = chNull;
      exponent = XMLString::parseInt (start);
      *end     = endChar;
    }

    if (first && (exponent == 1))
    { // up to now, this is a standalone unit (perhaps with a
      // disguised name, as when character references are used),
      // we do not use composition because it removes offsets
      unit = basic;
    }
    else
    { // compose the basic unit with the current state
      unit = Unit (0, unit, 1, basic, numerator ? exponent : -exponent);
    }
    first = false;

    // prepare handling of next basic unit
    switch (*end)
    {
      case chNull:
        start = end;
        break;
      case chAsterisk:
        numerator = true;
        start     = end + 1;
        break;
      case chForwardSlash:
        numerator = false;
        start     = end + 1;
        break;
      default:
        throw ClubErreurs (ClubErreurs::unit_syntax_error,
                           toString (symbol).c_str ());
    }

  }

  // cache the compound unit
  unit.setSymbol (symbol);
  units_ [symbol] = unit;

}
