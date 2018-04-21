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
//>       XMLFile.cpp
//
//$Summary
//       file implementing functions of class XMLFile
//
//$Description
//       Definition module of class XMLFile
//
//$Content
//>       static setUp()
//>       static tearDown()
//>       class XMLFile
//>         XMLFile()
//>         ~XMLFile()
//>         toString()
//>         hasChildElements()
//>         getChildElement()
//>         getString()
//>         getInt()
//>         getDouble()
//>         readFile()
//>         write()
//>         findFile()
//>         handleError()
//>         resolveEntity()
//
//$History
//       $Log: XMLFile.cpp,v $
//       Revision 1.18  2005/02/25 07:50:17  chope
//       removed the error and fatalError methods
//
//       Revision 1.17  2005/02/21 13:23:24  chope
//       ajout des fonctions setUp et tearDown,
//       détection d'une erreur supplémentaire (missing_attribute) (DM-ID 242)
//
//       Revision 1.16  2005/02/04 10:06:43  chope
//       refonte complète et séparation en trois classes (DM-ID 242)
//
//       Revision 1.15  2003/12/08 14:21:36  club
//       DM-ID 32 : Mise en conformite avec Xerces 2.x
//
//       Revision 1.14  2003/02/13 16:59:01  club
//       Correction d'une fuite mémoire
//
//       Revision 1.13  2003/02/06 14:18:31  club
//       DM-ID 18 Modification d'un include et correction de catch
//
//       Revision 1.12  2003/02/03 14:25:24  club
//       DM-ID 12 Mise à jour d'un include selon la norme C++ & mise
//       à jour du code en conséquence
//
//       Revision 1.11  2003/02/03 14:19:35  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//       & correction du passage par référence d'un objet ClubErreurs
//
//       Revision 1.10  2002/06/27 14:53:38  club
//       mise en conformité avec Xerces 1.7
//
//       Revision 1.9  2000/11/10 15:28:51  club
//       élimination de l'inclusion conditionnelle des en-têtes de Xerces,
//       l'ensemble du fichier est compilé de façon conditionnelle.
//       élimination des transformations entre ',' et '.' à la lecture
//       et à l'écriture.
//
//       Revision 1.8  2000/10/27 15:29:42  club
//       Correction de setDTDPath vis à vis de la version 1.3 de Xerces
//
//       Revision 1.7  2000/10/26 15:49:54  club
//       modification de l'implémentation de la méthode setDTDPath suite au
//       passage à Xerces version 1.3
//
//       Revision 1.6  2000/10/26 08:26:03  club
//       Mise à jour vis à vis de la version 1.3 de Xerces (ajout de l'include
//       <util/XMLUniDefs.hpp>).
//
//       Revision 1.5  2000/10/25 09:31:42  club
//       modification des include du standard C++ : suppression de ".h" dans
//       le nom du fichier inclus.
//
//       Revision 1.4  2000/10/24 14:21:02  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 1.3  2000/10/24 08:33:31  club
//       modification des include standard du C : utilisation de cNAME
//       au lieu de NAME.h (pour permettre la compilation avec le Sun
//       Workshop 5.0)
//
//       Revision 1.2  2000/10/18 09:16:46  club
//       suppression de l'exception missing_tag et remplacement par
//       malformed_data.
//       amélioration du code de la méthode setDTDPath
//
//       Revision 1.1  2000/10/16 15:43:51  club
//       Initial revision.
//
//$Version
//       $Id: XMLFile.cpp,v 1.18 2005/02/25 07:50:17 chope Exp $
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI
//       Copyright (C) CNES 2000
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_STL
# include <string>
#endif

#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/IOException.hpp>

#ifdef HAVE_SSTREAM
# include <sstream>
#endif

#ifdef HAVE_FSTREAM
# include <fstream>
#endif
#include <sys/stat.h>

#include "club/ClubErreurs.h"
#include "club/XMLFile.h"
#include "XMLSharedStrings.h"
#include "XMLFileStrings.h"

static int instanceCount = 0;
static XMLTranscoder *transcoder = 0;

// initialize platform resources if there is no instance yet
static void setUp ()
{
  if (instanceCount++ == 0)
  {
    const char* lang = getenv (CL_VAR_LANG);
    if (lang != NULL)
      XMLPlatformUtils::Initialize(lang);
    else
      XMLPlatformUtils::Initialize();
    XMLTransService* ts = XMLPlatformUtils::fgTransService;
    XMLTransService::Codes resValue = XMLTransService::Ok;
    transcoder = ts->makeNewTranscoderFor (XMLUni::fgISO88591EncodingString,
                                           resValue, 16 * 1024);
  }
}

// release platform resources if there is no instance anymore
static void tearDown ()
{
  if (--instanceCount == 0)
  {
    if (transcoder != 0)
    {
      delete transcoder;
      transcoder = 0;
    }
    XMLPlatformUtils::Terminate();
  }
}

// constructor
XMLFile::XMLFile (const XMLCh* type, const XMLCh* pubID, const XMLCh* sysId)
  throw (ClubErreurs)
  : document_(0), showing_ (DOMNodeFilter::SHOW_ALL)
{
  try
  {
    setUp ();

    // request an implementation with core features
    DOMImplementation* impl =
    DOMImplementationRegistry::getDOMImplementation(CORE_FEATURE);

    // create new DOMDocument
    document_ =
      impl->createDocument (0, type,
                            impl->createDocumentType (type, pubID, sysId));
  }
  catch (XMLException& xe)
  {
    throw ClubErreurs (ClubErreurs::xml_error,
                       toString (xe.getMessage ()).c_str ());
  }
  catch (DOMException de)
  {
    throw ClubErreurs (ClubErreurs::xml_error, toString (de.msg).c_str ());
  }

}


// constructor from a filename to load
XMLFile::XMLFile (const string& fileName)
  throw (ClubErreurs)
  : document_(0), showing_ (DOMNodeFilter::SHOW_ALL)
{
  try
  {
    setUp ();
    readFile (fileName);
  }
  catch (XMLException& toCatch)
  {
      cout << "exception caught at initialization" << endl;
    throw ClubErreurs (ClubErreurs::xml_error,
                       toString (toCatch.getMessage ()).c_str ());
  }
}


// virtual destructor
XMLFile::~XMLFile ()
{

  // release instance resources
  if (document_ != 0)
    document_->release();

  tearDown ();

}

// convert a XML string into a STL string
string XMLFile::toString (const XMLCh* s) const
{
  if (s == NULL)
    return "";
  if (transcoder == 0)
  {
    ArrayJanitor<char> janitor (XMLString::transcode (s, XMLPlatformUtils::fgMemoryManager),
                                XMLPlatformUtils::fgMemoryManager);
    return string (janitor.get ());
  }
  else
  {
    unsigned int len = XMLString::stringLen (s) + 1;
    ArrayJanitor<unsigned char> janitor (new unsigned char [len]);
    unsigned int charsEaten = 0;
    transcoder->transcodeTo (s, len - 1, janitor.get (), len - 1,
                             charsEaten, XMLTranscoder::UnRep_RepChar);
    janitor.get () [len - 1] = '\0';
    return string((char *) janitor.get ());
  }
}

// check whether an element has child elements.
bool XMLFile::hasChildElements (const DOMElement* element) const
{
  DOMNodeList* list = element->getChildNodes ();
  for (XMLSize_t i = 0; i < list->getLength (); ++i)
    if (list->item (i)->getNodeType () == DOMNode::ELEMENT_NODE)
      return true;
  return false;
}


// search for a child node by name
DOMElement* XMLFile::getChildElement (const XMLCh*   elementName,
                                      const DOMNode* node) const
  throw (ClubErreurs)
{

  DOMNodeList* list = node->getChildNodes ();
  for (XMLSize_t i = 0; i < list->getLength (); ++i)
  {
    if (list->item (i)->getNodeType () == DOMNode::ELEMENT_NODE)
    {
      DOMElement* element = (DOMElement *) list->item (i);
      if (XMLString::compareString (element->getTagName (), elementName) == 0)
        return element;
    }
  }

  throw ClubErreurs (ClubErreurs::missing_tag, toString (elementName).c_str());

}

// search for a child node by attribute value
DOMElement* XMLFile::getChildElement (const XMLCh*   attributeName,
                                      const XMLCh*   attributeValue,
                                      const DOMNode* node) const
{

  DOMNodeList* list = node->getChildNodes ();
  for (XMLSize_t i = 0; i < list->getLength (); ++i)
    if (list->item (i)->getNodeType () == DOMNode::ELEMENT_NODE)
    {
      DOMElement* child = (DOMElement *) list->item (i);
      if (XMLString::compareString (child->getAttribute(attributeName),
                                    attributeValue) == 0)
        return child;
    }

  return 0;

}

// search for a child node by attribute value
DOMElement* XMLFile::getChildElement (const XMLCh*   attributeName,
                                      const string&  attributeValue,
                                      const DOMNode* node) const
{
  ArrayJanitor<XMLCh> janitor (XMLString::transcode(attributeValue.c_str (),
                                                    XMLPlatformUtils::fgMemoryManager),
                               XMLPlatformUtils::fgMemoryManager);
  return getChildElement (attributeName, janitor.get (), node);
}

// get the string value of an attribute
string XMLFile::getString (const DOMElement* element,
                           const XMLCh* attributeName) const
  throw (ClubErreurs)
{
  DOMAttr* node = element->getAttributeNode (attributeName);
  if (node == NULL)
    throw ClubErreurs (ClubErreurs::missing_attribute,
                       toString (attributeName).c_str (),
                       toString (element->getTagName ()).c_str ());
  return toString(node->getValue ());
}

// get the int value of an attribute
int XMLFile::getInt (const DOMElement* element,
                     const XMLCh* attributeName) const
  throw (ClubErreurs)
{
  return atoi (getString (element, attributeName).c_str ());
}

// get the double value of an attribute
double XMLFile::getDouble (const DOMElement* element,
                           const XMLCh* attributeName) const
  throw (ClubErreurs)
{
  return atof (getString (element, attributeName).c_str ());
}


// load a XML file
void XMLFile::readFile (const string& fileName) throw (ClubErreurs)
{
  // get a parser
  DOMImplementation* impl =
    DOMImplementationRegistry::getDOMImplementation(LS_FEATURE);
  DOMBuilder* parser =
    ((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

  if (getenv (CL_VAR_XMLPATH) == NULL)
    throw ClubErreurs (ClubErreurs::variable_environnement, CL_VAR_XMLPATH);

  // configure the parser
  if (parser->canSetFeature (XMLUni::fgDOMValidation, true))
    parser->setFeature(XMLUni::fgDOMValidation, true);
  parser->setEntityResolver (this);
  parser->setErrorHandler (this);

  // try to parse file
  try
  {
    document_ = parser->parseURI (fileName.c_str ());
  }
  catch (XMLException& e)
  {
    throw ClubErreurs (ClubErreurs::file_error, fileName.c_str (),
                       toString (e.getMessage ()).c_str ());
  }

}

// write the document into a target
void XMLFile::write (XMLFormatTarget *target) throw (ClubErreurs)
{
  try {
    // get a writer
    DOMImplementationLS* impl = (DOMImplementationLS*)
      DOMImplementationRegistry::getDOMImplementation(LS_FEATURE);
    DOMWriter* writer = impl->createDOMWriter();
    Janitor<DOMWriter> janitor (writer);

    // configure the writer
    writer->setEncoding(UTF8_ENCODING);
    if (writer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
      writer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);
    writer->setFilter (this);
    writer->setErrorHandler (this);

    // write the document
    document_->normalize();
    writer->writeNode (target, *document_);
  }
  catch (XMLException& xe)
  {
    throw ClubErreurs(ClubErreurs::message_simple,
                      toString(xe.getMessage()).c_str());
  }
}

// find a file using a specific research algorithm
string XMLFile::findFile (const string& name, const string& baseURI)
  throw (ClubErreurs)
{
  struct stat buf;

  // is the name already absolute ?
  if (name[0] == '/')
    return name;

  // is it relative to the base URI ?
  if (baseURI.size () > 0)
  {
    string absolute = (baseURI.find ("file://") == 0)
                    ? baseURI.substr (7): baseURI;
    string::size_type index = absolute.rfind('/');
    if (index != string::npos)
    {
      absolute.replace(index + 1, absolute.size () - (index + 1), name);
      if (stat (absolute.c_str (), &buf) == 0)
        return absolute;
    }
  }

  // is it relative to one of the DTD/XML path directory ?
  const char * varenv = getenv (CL_VAR_XMLPATH);
  if (varenv == NULL)
    throw ClubErreurs (ClubErreurs::variable_environnement, CL_VAR_XMLPATH);

  // walk through the path parts
  string svarenv (varenv);
  string::size_type start = 0;
  while (start < svarenv.size ())
  {

    string::size_type end = svarenv.find(':', start);
    if (end == string::npos)
      end = svarenv.size ();

    // build the absolute path
    string absolute = svarenv.substr(start, end - start);
    if (absolute [absolute.size () - 1] != '/')
      absolute += '/';
    absolute += name;

    // check the file
    if (stat(absolute.c_str (), &buf) == 0)
      return absolute;

    // prepare next attempt
    start = end + 1;

  }

  // return the name itself :-(
  return name;

}

// Handle a DOM error
bool XMLFile::handleError (const DOMError& toCatch)
  throw (ClubErreurs)
{
  ostringstream tab;
  tab << "DOM Error at file \""
      << toString (toCatch.getLocation()->getURI ())
      << "\", line "
      << toCatch.getLocation()->getLineNumber ()
      << ", column "
      << toCatch.getLocation()->getColumnNumber ()
      << "\n   Message: "
      << toString (toCatch.getMessage ())
      << "\n";
  string message = tab.str();
  throw ClubErreurs (ClubErreurs::xml_error, message.c_str ());

  // unreached
  return false;

}

// resolve an external entity
DOMInputSource *XMLFile::resolveEntity (const XMLCh *const publicId,
                                        const XMLCh *const systemId,
                                        const XMLCh *const baseURI)
{

  string fileName = "";
  if (publicId != NULL)
    if (XMLString::compareString(publicId, DATA_DTD_PUB_ID) == 0)
      fileName = findFile ("club-data.dtd", "");
    else if (XMLString::compareString(publicId, UNITS_DTD_PUB_ID) == 0)
      fileName = findFile ("club-units.dtd", "");
  if ((fileName.size () == 0) && (systemId != NULL))
    fileName = findFile (toString (systemId), toString (baseURI));

  struct stat buf;
  if ((fileName.size () > 0) && (stat(fileName.c_str (), &buf) == 0))
  {
    // we have found the external entity
    ArrayJanitor<XMLCh> janitor (XMLString::transcode(fileName.c_str (),
                                                      XMLPlatformUtils::fgMemoryManager),
                                 XMLPlatformUtils::fgMemoryManager);
    return new Wrapper4InputSource(new LocalFileInputSource (janitor.get ()));
  }

  return NULL;

}
