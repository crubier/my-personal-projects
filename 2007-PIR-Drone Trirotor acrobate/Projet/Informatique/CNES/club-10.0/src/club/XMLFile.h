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
//>       XMLFile.h
//
//$Summary
//       Definition file of class XMLFile
//
//$Description
//       Declaration module of class XMLFile
//
//$Content
//>       class XMLFile
//$History
//       $Log: XMLFile.h,v $
//       Revision 1.11  2005/02/25 07:36:58  chope
//       the acceptNode is noz implemented in this class
//       added a ignoreNode method with a default implementation
//       removed the unused warning, error, fatalError and resetErrors methods
//
//       Revision 1.10  2005/02/21 13:07:09  chope
//       remplacement de méthodes statiques par des méthodes d'instance virtuelles
//
//       Revision 1.9  2005/02/04 09:52:33  chope
//       refonte complète et séparation en trois classes (DM-ID 242)
//
//       Revision 1.8  2003/12/08 14:21:54  club
//       DM-ID 32 : Mise en conformite avec Xerces 2.x
//
//       Revision 1.7  2003/02/06 14:58:36  club
//       DM-ID 18 Correction d'une ambiguité au niveau des constructeurs
//
//       Revision 1.6  2002/12/09 15:59:47  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.5  2002/06/27 14:57:47  club
//       mise en conformité avec Xerces 1.7
//
//       Revision 1.4  2000/10/25 09:31:44  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.3  2000/10/24 14:18:16  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.2  2000/10/17 14:07:35  club
//       suppression des méthodes mises en commentaire.
//
//       Revision 1.1  2000/10/16 15:36:05  club
//       Initial revision.
//
//$Version
//       $Id: XMLFile.h,v 1.11 2005/02/25 07:36:58 chope Exp $
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI
//       Copyright (C) 2000-2005 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_XMLFile_h
#define club_XMLFile_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include <string>

#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Name
//>       class XMLFile
//$Summary
//        XMLFile is a base class for XML files.
//
//$Description
//        This class provides generic services for XML files, it is used
//        as the base class for both XMLData and XMLUnits
//
//$Usage
//>     construction :
//        from document definition or from a file name
//>     usage :
//>       no public method, everything is either protected or private
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI
//       L. Maisonobe CSSI
//       Copyright (C) CNES 2000-2005
//$<>
///////////////////////////////////////////////////////////////////////////////


class XMLFile : private DOMErrorHandler, DOMEntityResolver, DOMWriterFilter
{

  protected :

  // Create a XMLFile.
  XMLFile (const XMLCh* type, const XMLCh* pubID, const XMLCh* sysId)
    throw (ClubErreurs);

  XMLFile (const string& fileName)
    throw (ClubErreurs);

  // Destruct a XMLFile instance.
  virtual ~XMLFile ();

  // convert a XML string into a STL string
  virtual string toString (const XMLCh* s) const;

  // handle child elements
  bool hasChildElements (const DOMElement* element) const;
  DOMElement* getChildElement (const XMLCh*   elementName,
                               const DOMNode* node) const
    throw (ClubErreurs);
  DOMElement* getChildElement (const XMLCh*   attributeName,
                               const XMLCh*   attributeValue,
                               const DOMNode* node) const;
  DOMElement* getChildElement (const XMLCh*   attributeName,
                               const string&  attributeValue,
                               const DOMNode* node) const;

  // handle attributes
  string getString (const DOMElement* element,
                    const XMLCh* attributeName) const
    throw (ClubErreurs);
  int    getInt    (const DOMElement* element,
                    const XMLCh* attributeName) const
    throw (ClubErreurs);
  double getDouble (const DOMElement* element,
                    const XMLCh* attributeName) const
    throw (ClubErreurs);

  static string findFile (const string& name, const string& baseURI)
    throw (ClubErreurs);

  // Load a file in memory
  virtual void readFile (const string& fileName) throw (ClubErreurs);

  // Write the document
  virtual void write (XMLFormatTarget *target) throw (ClubErreurs);

  virtual bool ignoreNode (const DOMNode* node) const { return false; }

  // document
  DOMDocument* document_;

private :

  // OTHERS CONSTRUCTORS
  // N.B.: these constructors are private because
  // we don't want any call for them
  XMLFile (const XMLFile & other) {}
  XMLFile & operator = (const XMLFile & other) { return *this; }

  // Implementation of the error handler interface
  bool handleError (const DOMError& domError) throw (ClubErreurs);

  // Implementation of the entity resolver interface
  DOMInputSource *resolveEntity (const XMLCh *const publicId,
                                 const XMLCh *const systemId,
                                 const XMLCh *const baseURI);

  // Implementation of the writer filter interface
  unsigned long getWhatToShow () const { return showing_; }
  void          setWhatToShow (unsigned long showing) { showing_ = showing; }
  short         acceptNode (const DOMNode* node) const
  {
    return ignoreNode (node)
           ? DOMNodeFilter::FILTER_REJECT : DOMNodeFilter::FILTER_ACCEPT;
  }


  // writer filter setting
  unsigned long showing_;

};

#endif
