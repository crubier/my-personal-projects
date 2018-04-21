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
//>       XMLUnits.h
//
//$Summary
//       Definition file of class XMLUnits
//
//$Description
//       Declaration module of class XMLUnits
//
//$Content
//>       class XMLUnits
//$History
//       $Log: XMLUnits.h,v $
//       Revision 1.3  2005/02/25 07:34:22  chope
//       élimintation de la méthode acceptNode
//
//       Revision 1.2  2005/02/21 13:05:49  chope
//       ajout des méthodes parseXxxxChar et removeCharReferences
//       élimination de searchForUnitElement
//
//       Revision 1.1  2005/02/04 10:05:37  chope
//       initial version
//
//
//$Version
//       $Id: XMLUnits.h,v 1.3 2005/02/25 07:34:22 chope Exp $
//
//$Authors
//       L. Maisonobe CSSI
//       Copyright (C) 2005 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_XMLUnits_h
#define club_XMLUnits_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include <string>
#include <map>

#include "club/ClubErreurs.h"
#include <club/XMLFile.h>
#include <club/Unit.h>

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Name
//>       class XMLUnits
//$Summary
//        XMLUnits provides units conversion for XML data files.
//
//$Description
//        This class handles all units-related functions for XML files,
//        it could also be used directly. It handles conversions for
//        simple units ans compound units. The relations between units
//        can be simple factors or include an offset (like degree Celsius
//        and Fahrenheit).
//
//$Usage
//>     construction :
//        with a file name.
//>     usage :
//>       virtual void convert                 ()
//          convert a scalar value from one unit to another one
//
//$Authors
//       L. Maisonobe CSSI
//       Copyright (C) CNES 2005
//$<>
///////////////////////////////////////////////////////////////////////////////


class XMLUnits : public XMLFile
{

public :

  // Create a XMLUnits.
  XMLUnits (const string& fileName)
    throw (ClubErreurs);

  // Destruct a XMLUnits instance.
  virtual ~XMLUnits ();

  // delete included data from a given file.
  double convert (double value,
                  const XMLCh* fromUnit, const XMLCh* toUnit) const
    throw (ClubErreurs);

protected :

  // convert a XML string into a STL string
  virtual string toString (const XMLCh* s) const;

private :

  // comparator used for keys in the units map
  class Compare {
    public:
    bool operator() (const XMLCh* x, const XMLCh* y) const
    {
      return XMLString::compareString (x, y) < 0;
    }
  };

  // OTHERS CONSTRUCTORS
  // N.B.: these constructors are private because
  // we don't want any call for them
  XMLUnits (const XMLUnits & other);
  XMLUnits & operator = (const XMLUnits & other) { return *this; }

  // handle character references in a XML string
  XMLCh parseHexaChar (const XMLCh* s, int start, int end) const
    throw (ClubErreurs);
  XMLCh parseDeciChar (const XMLCh* s, int start, int end) const
    throw (ClubErreurs);
  XMLCh parsePredefinedEntityChar (XMLCh* s, int start, int end) const
    throw (ClubErreurs);
  void removeCharReferences (XMLCh* s) const
    throw (ClubErreurs);

  // analyze and cache a unit symbol
  void cacheSymbol (const XMLCh* symbol) const
   throw (ClubErreurs);

  // map containing all the units
  typedef map<const XMLCh*, Unit, Compare> UnitsMap;
  mutable UnitsMap units_;

};

#endif
