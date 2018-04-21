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
//>       XMLData.cpp
//
//$Summary
//       file implementing functions of class XMLData
//
//$Description
//       Definition module of class XMLData
//
//$Content
//>       static dataNameToXPointer()
//>       static xpointerToDataName()
//>       static setStringAttributeValue()
//>       static setRealAttributeValue()
//>       static setIntAttributeValue()
//>       class XMLData
//>         XMLData()
//>         ~XMLData()
//>         moveDown()
//>         moveUp()
//>         readFile()
//>         writeFile()
//>         writeMemoryStructure()
//>         getDataType()
//>         size()
//>         dataExists()
//>         getComment()
//>         setComment()
//>         createStringData()
//>         createIntData()
//>         createRealData()
//>         createTable()
//>         createStructure()
//>         createReference()
//>         getStringData()
//>         getIntData()
//>         getRealData()
//>         getReference()
//>         setStringData()
//>         setIntData()
//>         setRealData()
//>         deleteData()
//>         includeFile()
//>         deleteIncludedFile()
//>         canMoveUp()
//>         writeReferencedFiles()
//>         getElementType()
//>         testCurrentDataNotATable()
//>         testCurrentDataIsATable()
//>         ignoreNode()
//
//$History
//       $Log: XMLData.cpp,v $
//       Revision 1.3  2005/02/25 07:55:07  chope
//       replaced the acceptNode method by ignoreNode
//
//       Revision 1.1  2005/02/04 10:19:17  chope
//       initial version
//
//
//$Version
//       $Id: XMLData.cpp,v 1.3 2005/02/25 07:55:07 chope Exp $
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI
//       Copyright (C) CNES 2000-2005
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_STL
# include <string>
#endif

#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/PlatformUtils.hpp>
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
#include "club/XMLData.h"
#include "XMLSharedStrings.h"
#include "XMLDataStrings.h"

//-----------------------------------------------------------------------------
// string dataNameToXPointer (const string& dataName,
//                            const string& fileName)
// Convert a data name into XPointer reference.
// In
//      dataName : a complete data name
//      filename : the file containing dataName
// Out
//      the xpointer notation according to dataName and fileName
//-----------------------------------------------------------------------------

static string dataNameToXPointer (const string& dataName,
                                  const string& fileName) throw (ClubErreurs)
{
  string result = fileName + "#xpointer(";
  string data = dataName;
  string rest;
  string currentData;

  while (hasMoreSubDataNames (data, &rest))
  {
    currentData = getFirstElementName (data);

    if (isDataNameAnIndex (currentData))
    {
      result += "/*[@index='";
      result += intToString (getIndexValue (currentData));
      result += "']";
    }
    else
    {
      result += "/*[@name='";
      result += currentData;
      result += "']";
    }

    data = rest;
  }
  result += ")";

  return result;
}

//-----------------------------------------------------------------------------
// string xpointerToDataName (const string& xpointer, string* dataName,
//                            string* fileName)
//                            const string& fileName)
// Convert a XPointer reference into a data name.
// xpointer reference model is :
// <fileName> "#xpointer(" [ "/*[@name='" <dataName> "']"  | "/*[@index='" <index> "']" ] + ")"
// In
//      the xpointer notation
// Out
//      dataName : the complete data name
//      filename : the file containing dataName
// Exception
//       ClubErreurs::xpointer_syntax_error
//-----------------------------------------------------------------------------

static void xpointerToDataName (const string& xpointer, string* dataName,
                                string* fileName) throw (ClubErreurs)
{
  string xptr = xpointer;

  // Search for the file name. If not found then throw an exception.
  int indexChar = xptr.find_first_of ("#");
  if (indexChar == -1)
    throw ClubErreurs (ClubErreurs::xpointer_syntax_error, xpointer.c_str ());

  *fileName = fileName->assign (xptr, 0, indexChar);
  xptr = xptr.assign (xptr, indexChar+1, xptr.size () - indexChar- 1);

  //search for the xpointer notation. If not found then throw an exception.
  string toFind = "xpointer(";
  int toFindSize  = toFind.size ();
  if (xptr.find (toFind) != 0)
    throw ClubErreurs (ClubErreurs::xpointer_syntax_error, xpointer.c_str ());

  xptr = xptr.assign (xptr, toFindSize, xptr.size () - toFindSize);

  *dataName = "";

  bool nameConstruction = true;
  while (nameConstruction)
  {
    // Search for a data name. If not found then search for an index.
    toFind = "/*[@name='";
    toFindSize = toFind.size ();

    if (xptr.find (toFind) == 0)
    {
      xptr = xptr.assign (xptr, toFindSize, xptr.size () - toFindSize);
      indexChar = xptr.find_first_of ("'");

      if (indexChar == -1)
        throw ClubErreurs (ClubErreurs::xpointer_syntax_error,
                           xpointer.c_str ());

      string name;
      name = name.assign (xptr, 0, indexChar);

      // Constructs the resulting data name.
      if (*dataName == "")
        *dataName = name;
      else
        *dataName += "." + name;

      xptr = xptr.assign (xptr, indexChar, xptr.size () - indexChar);
    }
    else
    {
      // As we have not found a data name then we search for an index.
      toFind = "/*[@index='";
      toFindSize = toFind.size ();

      if (xptr.find (toFind) == 0)
      {
        xptr = xptr.assign (xptr, toFindSize, xptr.size () - toFindSize);
        indexChar = xptr.find_first_of ("'");

        //if "'" is not found then throw an exception.
        if (indexChar < 0 || (unsigned int) indexChar > xptr.size ())
          throw ClubErreurs (ClubErreurs::xpointer_syntax_error,
                             xpointer.c_str ());

        // Constructs the resulting data name.
        string index;
        index = index.assign (xptr, 0, indexChar);
        *dataName += "[" + index + "]";

        xptr = xptr.assign (xptr, indexChar, xptr.size () - indexChar);
      }
      else
        nameConstruction = false;
    }

    toFind = "']";
    toFindSize = toFind.size ();

    if (xptr.find (toFind) == 0)
      xptr = xptr.assign (xptr, toFindSize, xptr.size () - toFindSize);
  }
}

//-----------------------------------------------------------------------------
// void setStringAttributeValue (const DOMElement* element,
//                               const XMLCh* attributeName,
//                               const string& attributeValue)
// Updates or creates the string value of element
// In
//      element : DOMelement whose int attribute value must be set
//      attributeName : name of attribute whose value must be set
//      attributeValue : int value of attributeName
//-----------------------------------------------------------------------------

static void setStringAttributeValue (DOMElement* element,
                                     const XMLCh* attributeName,
                                     const string& attributeValue)
{
  ArrayJanitor<XMLCh> janitor (XMLString::transcode(attributeValue.c_str (),
                                                    XMLPlatformUtils::fgMemoryManager),
                               XMLPlatformUtils::fgMemoryManager);
  element->setAttribute (attributeName, janitor.get());
}

//-----------------------------------------------------------------------------
// void setRealAttributeValue (const DOMElement* element,
//                             const XMLCh* attributeName,
//                             double value)
// Updates or creates a real value of element
// In
//      element : DOMelement whose real attribute value must be set
//      attributeName : name of attribute whose value must be set
//      value : real value of attributeName
//-----------------------------------------------------------------------------

static void setRealAttributeValue (DOMElement* element,
                                   const XMLCh* attributeName,
                                   double value)
{
  string valueStr = doubleToString (value);
  setStringAttributeValue (element, attributeName, valueStr);
}

//-----------------------------------------------------------------------------
// void setIntAttributeValue (const DOMElement* element,
//                            const XMLCh* attributeName,
//                            int value)
// Updates or creates an int value of element
// In
//      element : DOMelement whose int attribute value must be set
//      attributeName : name of attribute whose value must be set
//      value : int value of attributeName
//-----------------------------------------------------------------------------

static void setIntAttributeValue (DOMElement* element,
                                  const XMLCh* attributeName, int value)
{
  string valueStr = intToString (value);
  setStringAttributeValue (element, attributeName, valueStr);
}

//-----------------------------------------------------------------------------
// XMLData::XMLData ()
// Creates a XMLData
// Exception
//      ClubErreurs::xml_error thrown if an error has occurred while
//      parser initialization
//-----------------------------------------------------------------------------

XMLData::XMLData () throw (ClubErreurs)
  : XMLFile (CLUB_DATA_TAG, DATA_DTD_PUB_ID, DATA_DTD_SYS_ID),
    units_ (0), currentElement_ (0)
{
  currentElement_ = document_->getDocumentElement ();
  currentElement_->setAttribute (VERSION_ATTRIBUTE, VERSION_VALUE);
}

//-----------------------------------------------------------------------------
// XMLData::XMLData (const string& fileName)
// Creates a XMLData
// In
//      fileName     : name of file to be read
// Exception
//      ClubErreurs::xml_error thrown if an error has occurred while
//      parser initialization
//-----------------------------------------------------------------------------

XMLData::XMLData (const string& fileName)
  throw (ClubErreurs)
  : XMLFile(fileName), units_ (0), currentElement_ (0)
{
  currentElement_ = document_->getDocumentElement ();
  currentElement_->setAttribute (VERSION_ATTRIBUTE, VERSION_VALUE);
}

//-----------------------------------------------------------------------------
// XMLData::XMLData (const XMLData& data)
// Copy constructor, NOT used
//-----------------------------------------------------------------------------

XMLData::XMLData (const XMLData& data)
  : XMLFile (CLUB_DATA_TAG, DATA_DTD_PUB_ID, DATA_DTD_SYS_ID),
    units_ (0), currentElement_ (0)
{
}

//-----------------------------------------------------------------------------
// XMLData::~XMLData()
// Destructs a XMLData instance
//-----------------------------------------------------------------------------

XMLData::~XMLData ()
{
}

//-----------------------------------------------------------------------------
// void XMLData::moveDown (const string& relativeDataName)
// Move to child (of current data) named relativeDataName
// In
//      relativeDataName : relative data name of child to move to.
// Exception
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::undefined_table_or_structure
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::xml_error
//      ClubErreurs::xpointer_syntax_error
//-----------------------------------------------------------------------------

void XMLData::moveDown (const string& relativeDataName) throw (ClubErreurs)
{
  // checking if relativeDataName is an index
  if (isDataNameAnIndex (relativeDataName))
  {
    // call moveDown (int index)
    moveDown (getIndexValue (relativeDataName));
  }
  else
  {
    // search for the child named relativeDataName
    DOMElement* element = getChildElement (NAME_ATTRIBUTE,
                                           relativeDataName,
                                           currentElement_);
    if (element == 0)
      throw ClubErreurs (ClubErreurs::undefined_table_or_structure,
                         getAbsoluteDataName (relativeDataName).c_str ());

    int elementType = getElementType (element);

    // if the child is a reference then load the referenced data if necessary
    // and call moveDown () again.
    if (elementType == ReferenceType && ! hasChildElements (element))
    {
      string xpointer = getString (element, REFERENCE_ATTRIBUTE);
      string fileName;
      string referencedData;
      xpointerToDataName (xpointer, &referencedData, &fileName);
      XMLData xf (findFile (fileName,
                            toString (document_->getDocumentURI ())));
      xf.moveTo  (referencedData);

      DOMNodeList* list = xf.currentElement_->getChildNodes();
      for (XMLSize_t i = 0; i < list->getLength (); ++i)
      {
        DOMNode* child = list->item (i);
        try
        {
          element->appendChild (document_->importNode (child, true));
        }
        catch (DOMException de)
        {
          throw ClubErreurs (ClubErreurs::xml_error,
                             toString (de.msg).c_str ());
        }
      }
    }

    // if the child found is not a structure or a table, cannot move down
    if (elementType != ReferenceType && elementType != StructureType &&
        elementType != TableType)
    {
      throw ClubErreurs (ClubErreurs::undefined_table_or_structure,
                         getAbsoluteDataName (relativeDataName).c_str ());
    }
    else
    {
      currentElement_ = element;
      UniqDataFile::moveDown (relativeDataName);
    }
  }
}

//-----------------------------------------------------------------------------
// void XMLData::moveDown (int index)
// Move to child (of current data) whose index is "index". The current data
// must be a table.
// In
//      index : index of child data (first value is "1")
// Exception
//      ClubErreurs::undefined_table_or_structure
//      ClubErreurs::undefined_index if index does not exist
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::xpointer_syntax_error
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::moveDown (int index) throw (ClubErreurs)
{
  testCurrentDataNotATable ();

  string indexStr = intToString (index);
  string relativeDataName = "[" + indexStr + "]";

  // search for the child whose index is indexStr
  DOMElement* element = getChildElement (INDEX_ATTRIBUTE,
                                         indexStr,
                                         currentElement_);
  if (element == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  int elementType = getElementType (element);
  if (elementType == ReferenceType && ! hasChildElements (element))
  {
    string xpointer = getString (element, REFERENCE_ATTRIBUTE);
    string fileName;
    string referencedData;

    xpointerToDataName (xpointer, &referencedData, &fileName);
    XMLData xf (findFile (fileName,
                          toString (document_->getDocumentURI ())));
    xf.moveTo (referencedData);

    DOMNodeList* list = xf.currentElement_->getChildNodes ();
    for (XMLSize_t i = 0; i < list->getLength (); ++i)
    {
      DOMNode* child = list->item (i);
      try
      {
        element->appendChild (document_->importNode (child, true));
      }
      catch (DOMException de)
      {
        throw ClubErreurs (ClubErreurs::xml_error,
                           toString (de.msg).c_str ());
      }
    }
  }

  // if the child found is not a structure or a table, cannot move down
  if (elementType != ReferenceType && elementType != StructureType &&
      elementType != TableType)
  {
    throw ClubErreurs (ClubErreurs::undefined_table_or_structure,
                       getAbsoluteDataName (relativeDataName).c_str ());
  }
  else
  {
    currentElement_ = element;
    UniqDataFile::moveDown (index);
  }

}

//-----------------------------------------------------------------------------
// void XMLData::moveUp ()
// Move to parent node of current data
// Exception
//      ClubErreurs::move_up_forbidden
//      ClubErreurs:malformed_data if parent node is not an element node
//-----------------------------------------------------------------------------

void XMLData::moveUp () throw (ClubErreurs)
{
  // check if moving up is allowed
  if (canMoveUp ())
  {
    DOMNode* parentNode = currentElement_->getParentNode ();

    if (parentNode->getNodeType () != DOMNode::ELEMENT_NODE)
      throw ClubErreurs (ClubErreurs::malformed_data,
                         getCurrentData ().c_str ());
    else
    {
      DOMElement* parent = (DOMElement *) parentNode;

      // move to parent node
      currentElement_ = parent;
      UniqDataFile::moveUp ();
    }
  }
  else
    throw ClubErreurs(ClubErreurs::move_up_forbidden);
}

//-----------------------------------------------------------------------------
// void XMLData::readFile (const string& fileName)
// Load a file in memory
// In
//      fileName : name of file to load.
// Exception
//      ClubErreurs::variable_environnement if the XML/DTD path environment
//      variable is not set
//      ClubErreurs::file_error if parsing has failed
//      ClubErreurs::missing_tag if tag "club-data" is not found
//-----------------------------------------------------------------------------

void XMLData::readFile (const string& fileName) throw (ClubErreurs)
{
  // let the base class perform raw read
  XMLFile::readFile (fileName);

  // select the top level element
  currentElement_ = getChildElement (CLUB_DATA_TAG, document_);

  // expand all included files
  DOMNodeList* list = currentElement_->getChildNodes ();
  for (XMLSize_t i = 0; i < list->getLength (); ++i)
    if (list->item (i)->getNodeType () == DOMNode::ELEMENT_NODE)
    {
      DOMElement* child = (DOMElement *) list->item (i);
      if (XMLString::compareString (child->getTagName (), INCLUDE_TAG) == 0)
        includeFile (getString (child, INCLUDED_FILE_ATTRIBUTE));
    }

}

//-----------------------------------------------------------------------------
// void XMLData::writeFile (const string& fileName)
// Write the DOM in a file (also writes referenced files)
// In
//      fileName : name of file to write.
// Exception
//      ClubErreurs::ouverture_fichier if file opening has failed
//-----------------------------------------------------------------------------
void XMLData::writeFile (const string& fileName) throw (ClubErreurs)
{
  ClubErreurs e;
  try
  {
    LocalFileFormatTarget target (fileName.c_str());

    // we need two embedded try/catch blocs because exceptions can be thrown
    // during the 'write' call, and also during the implicit call to 'target'
    // destructor because it flushes its output. The problem is that this call
    // to the destructor can occur during the stack unwinding as the exception
    // already thrown at 'write' level is done, then the destructor attempts
    // another time the same write that has just failed, and a new exception
    // is thrown. The C++ standard says that in this case, terminate() is
    // called. In order to prevent this, we catch the first exception INSIDE
    // the scope of the 'target' variable, and hence before the destructor is
    // called. When the destructor throws the new exception, no other one is
    // flying around, we handle one exception at a time. The outer try/catch
    // bloc is here to handle this second exception.
    try
    {
      write (&target);
      writeReferencedFiles (document_->getDocumentElement ());
    }
    catch (ClubErreurs ce)
    {
      e = ce;
    }

  }
  catch (XMLException &xe)
  {
    if (! e.existe ())
    {
      if ((xe.getCode () == XMLExcepts::File_CouldNotOpenFile)
          || (xe.getCode () == XMLExcepts::File_CouldNotWriteToFile))
        e = ClubErreurs(ClubErreurs::ouverture_fichier, fileName.c_str());
      else
        e = ClubErreurs(ClubErreurs::message_simple,
                        toString(xe.getMessage()).c_str());
    }
  }

  // an exception has been caught, either at first or second level
  if (e.existe ())
    throw e;

}

//-----------------------------------------------------------------------------
// void XMLData::writeMemoryStructure ()
// Write the DOM used by this instance in cout (used for debugging).
// Exceptions
//      ClubErreurs::undefined_node_type if the node's type is not recognized
//-----------------------------------------------------------------------------

void XMLData::writeMemoryStructure () throw (ClubErreurs)
{
  StdOutFormatTarget target;
  write (&target);
}

//-----------------------------------------------------------------------------
// UniqDataFile::DataType XMLData::getDataType (const string& childDataName)
// Returns the type of data named childDataName
// In
//      childDataName : name of data.
// Out
//      type of element (value of enum UniqDataFile::DataType)
// Exception
//       ClubErreurs::undefined_data
//       ClubErreurs::string_to_int_conversion
//       ClubErreurs::undefined_index
//       ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

UniqDataFile::DataType XMLData::getDataType (const string& childDataName)
  throw (ClubErreurs)
{

  // search for data named childDataName
  DOMElement* element = 0;
  if (isDataNameAnIndex (childDataName))
  {
    int index = getIndexValue (childDataName);
    testUndefinedIndex (index);
    element = getChildElement (INDEX_ATTRIBUTE,
                               intToString (index),
                               currentElement_);
  }
  else
  {
    element = getChildElement (NAME_ATTRIBUTE,
                               childDataName,
                               currentElement_);
  }

  if (element == 0)
    throw ClubErreurs (ClubErreurs::undefined_data,
                       getAbsoluteDataName (childDataName).c_str ());

  return getElementType (element);

}


//-----------------------------------------------------------------------------
// UniqDataFile::DataType XMLData::getDataType (int index)
// Returns the type of data named childDataName. The current data must be a
// table.
// In
//      index : index of the element in the table.
// Out
//      type of element (value of enum UniqDataFile::DataType)
// Exception
//       ClubErreurs::undefined_index if data does not exist
//       ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

UniqDataFile::DataType XMLData::getDataType (int index)
  throw (ClubErreurs)
{
  string indexStr = "[" + intToString (index) + "]";
  return getDataType (indexStr);
}

//-----------------------------------------------------------------------------
// int XMLData::size ()
// Returns the number of children of current data (current data must be a table
// Out
//      number of children of current data
// Exception
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

int XMLData::size () throw (ClubErreurs)
{
  int result = 0;

  // check if current data is a table
  if (getElementType (currentElement_) == TableType)
  {
    // counts children (only of type ELEMENT_NODE) of current data
    DOMNodeList* list = currentElement_->getChildNodes ();
    for (XMLSize_t i = 0; i < list->getLength (); ++i)
    {
      DOMNode* child = list->item (i);
      if (child->getNodeType () == DOMNode::ELEMENT_NODE)
        result++;
    }
    return result;
  }
  else
    throw ClubErreurs (ClubErreurs::current_data_not_a_table,
                       getCurrentData ().c_str ());
}

//-----------------------------------------------------------------------------
// bool XMLData::dataExists (const string& childDataName)
// Checks whether childDataName exists
// In
//      childDataName : name of child
// out
//      true if childDataName exists, false otherwise
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::string_to_int_conversion_error
//-----------------------------------------------------------------------------

bool XMLData::dataExists (const string& childDataName) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    return dataExists (getIndexValue (childDataName));
  }
  else
  {
    //search for a DOMElement whose name attribute is childDataName.
    return (getChildElement (NAME_ATTRIBUTE,
                             childDataName,
                             currentElement_) != 0);
  }
}

//-----------------------------------------------------------------------------
// bool XMLData::dataExists (int index)
// Checks whether data whose index attribute is "index" exists. Current data
// must be a table
// In
//      index : value of index attribute
// out
//      true if child exists, false otherwise
// Exception
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

bool XMLData::dataExists (int index) throw (ClubErreurs)
{
  testCurrentDataNotATable ();
  return (getChildElement (INDEX_ATTRIBUTE,
                           intToString (index),
                           currentElement_) != 0);
}

//-----------------------------------------------------------------------------
// string XMLData::getComment (const string& childDataName)
// Returns comments of childDataName
// In
//      childDataName : Name of child whose comments must be returned
// Out
//      comments of childDataName
// Exception
//      ClubErreurs::undefined_data if childDataName does not exist
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::string_to_int_conversion_error
//-----------------------------------------------------------------------------

string XMLData::getComment (const string& childDataName) throw (ClubErreurs)
{
  if (isDataNameAnIndex(childDataName))
  {
    // childDataName is an index, call getComment (int index)
    return getComment (getIndexValue (childDataName));
  }
  else
  {
    // search for child named childDataName
    DOMElement* element = getChildElement (NAME_ATTRIBUTE,
                                           childDataName,
                                           currentElement_);
    if (element == 0)
      throw ClubErreurs (ClubErreurs::undefined_data,
                         getAbsoluteDataName (childDataName).c_str ());
    return getString (element, COMMENT_ATTRIBUTE);

  }

}

//-----------------------------------------------------------------------------
// string XMLData::getComment (int index)
// Returns comments of child whose index attribute is "index". Current data
// must be a table.
// In
//      index : index of child data (first value is "1")
// Out
//      comments of childDataName
// Exception
//      ClubErreurs::undefined_index if child does not exist
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

string XMLData::getComment (int index) throw (ClubErreurs)
{
  // search for child whose index attribute is index
  testCurrentDataNotATable ();
  DOMElement* element = getChildElement (INDEX_ATTRIBUTE,
                                         intToString (index),
                                         currentElement_);
  if (element == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  return getString (element, COMMENT_ATTRIBUTE);

}

//-----------------------------------------------------------------------------
// void XMLData::setComment (const string& childDataName,
//                           const string& comment)
// Sets comments of childDataName
// In
//      childDataName : name of child whose comments must be set
//      comment       : comment of childDataName
// Exception
//      ClubErreurs::undefined_data if childDataName does not exist
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::string_to_int_conversion_error
//-----------------------------------------------------------------------------

void XMLData::setComment (const string& childDataName, const string& comment)
  throw (ClubErreurs)
{
  if (isDataNameAnIndex(childDataName))
  {
    // childDataName is an index,
    // call setComment (int index, const string& comment)
    setComment (getIndexValue (childDataName), comment);
  }
  else
  {
    // search for child named childDataName
    DOMElement* element = getChildElement (NAME_ATTRIBUTE,
                                           childDataName,
                                           currentElement_);
    if (element == 0)
      throw ClubErreurs (ClubErreurs::undefined_data,
                         getAbsoluteDataName (childDataName).c_str ());
    setStringAttributeValue (element, COMMENT_ATTRIBUTE, comment);
  }
}

//-----------------------------------------------------------------------------
// void XMLData::setComment (int index, const string& comment)
// Sets comments of child whose index attribute is "index". Current data
// must be a table.
// In
//      index : index of child data (first value is "1")
//      comment       : comment of childDataName
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index;
//-----------------------------------------------------------------------------

void XMLData::setComment (int index, const string& comment)
  throw (ClubErreurs)
{
  testCurrentDataNotATable ();

  // search for child whose index attribute is index
  DOMElement* element = getChildElement (INDEX_ATTRIBUTE,
                                         intToString (index),
                                         currentElement_);
  if (element == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  setStringAttributeValue (element, COMMENT_ATTRIBUTE, comment);

}

//-----------------------------------------------------------------------------
// void XMLData::createStringData (const string& childDataName,
//                                 const string& value)
// Creates a child of type String named childDataName
// In
//      childDataName : name of string data
//      value : new value
// Exception
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::index_creation_forbidden if childDataName is an index name
//      ClubErreurs::data_already_defined
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createStringData (const string& childDataName,
                                const string& value) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    // childDataName is an index. cannot create a new DOMElement
    throw ClubErreurs (ClubErreurs::index_creation_forbidden,
                       getAbsoluteDataName (childDataName).c_str ());
  }
  else
  {
    // Check is current data is not a table.
    testCurrentDataIsATable ();

    // check if no data named childDataName exists
    testDataAlreadyDefined (childDataName);

    // try to create new DOMElement
    try
    {
      DOMElement* data = document_->createElement (STRING_DATA_TAG);
      currentElement_->appendChild (data);

      // set attribute values
      setStringAttributeValue (data, NAME_ATTRIBUTE,  childDataName);
      setStringAttributeValue (data, VALUE_ATTRIBUTE, value);
    }
    catch (DOMException de)
    {
      throw ClubErreurs (ClubErreurs::xml_error,
                         toString (de.msg).c_str ());
    }
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createStringData (const string& value)
// Creates new string data. Current data must be a table.
// In
//      value : new value
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::invalid_element_type
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createStringData (const string& value) throw (ClubErreurs)
{
  // check if current data is a table
  int length = size ();
  if (XMLString::compareString(currentElement_->getTagName (),
                               STRING_TABLE_TAG)
      != 0)
    throw ClubErreurs (ClubErreurs::invalid_element_type ,
                       getCurrentData ().c_str (),
                       toString (currentElement_->getTagName ()).c_str (),
                       toString (STRING_DATA_TAG).c_str ());

  // try to create new DOMElement
  try
  {
    DOMElement* data = document_->createElement (STRING_DATA_TAG);
    currentElement_->appendChild (data);

    // set attribute values
    setIntAttributeValue    (data, INDEX_ATTRIBUTE, length+1);
    setStringAttributeValue (data, VALUE_ATTRIBUTE, value);
  }
  catch (DOMException de)
  {
    throw ClubErreurs (ClubErreurs::xml_error,
                       toString (de.msg).c_str ());
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createIntData (const string& childDataName, int value)
// Creates a child of type Int named childDataName
// In
//      childDataName : name of string data
//      value : new value
// Exception
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::data_already_defined
//      ClubErreurs::index_creation_forbidden if childDataName is an index name
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createIntData (const string& childDataName, int value)
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    // childDataName is an index. cannot create a new DOMElement
    throw ClubErreurs (ClubErreurs::index_creation_forbidden,
                       getAbsoluteDataName (childDataName).c_str ());
  }
  else
  {
    // Check is current data is not a table.
    testCurrentDataIsATable ();

    // check if no data named childDataName exists
    testDataAlreadyDefined (childDataName);

    // try to create new DOMElement
    try
    {
      DOMElement* data = document_->createElement (INT_DATA_TAG);
      currentElement_->appendChild (data);

      // set attribute values
      setStringAttributeValue (data, NAME_ATTRIBUTE, childDataName);
      setIntAttributeValue    (data, VALUE_ATTRIBUTE, value);
    }
    catch (DOMException de)
    {
      throw ClubErreurs (ClubErreurs::xml_error,
                         toString (de.msg).c_str ());
    }
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createIntData (int value)
// Creates new int data. Current data must be a table.
// In
//      value : new value
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::invalid_element_type
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createIntData (int value) throw (ClubErreurs)
{
  // check if current data is a table
  int length = size ();
  if (XMLString::compareString(currentElement_->getTagName (), INT_TABLE_TAG)
      != 0)
    throw ClubErreurs (ClubErreurs::invalid_element_type ,
                       getCurrentData ().c_str (),
                       toString (currentElement_->getTagName ()).c_str (),
                       toString (INT_DATA_TAG).c_str ());

  // try to create new DOMElement
  try
  {
    DOMElement* data = document_->createElement (INT_DATA_TAG);
    currentElement_->appendChild (data);

    // set attribute values
    setIntAttributeValue (data, INDEX_ATTRIBUTE, length+1);
    setIntAttributeValue (data, VALUE_ATTRIBUTE, value);
  }
  catch (DOMException de)
  {
    throw ClubErreurs (ClubErreurs::xml_error,
                       toString (de.msg).c_str ());
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createRealData (const string& childDataName, double value,
//                               const string& unit)
// Creates a child of type Real named childDataName
// In
//      childDataName : name of string data
//      value : new value
//      unit  : unit of value
// Exception
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::data_already_defined
//      ClubErreurs::index_creation_forbidden if childDataName is an index name
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createRealData (const string& childDataName, double value,
                              const string& unit) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    // childDataName is an index. cannot create a new DOMElement
    throw ClubErreurs (ClubErreurs::index_creation_forbidden,
                       getAbsoluteDataName (childDataName).c_str ());
  }
  else
  {
    // Check is current data is not a table.
    testCurrentDataIsATable ();

    // check if no data named childDataName exists
    testDataAlreadyDefined (childDataName);

    // try to create new DOMElement
    try
    {
      DOMElement* data = document_->createElement (REAL_DATA_TAG);
      currentElement_->appendChild (data);

      // set attribute values
      setStringAttributeValue (data, NAME_ATTRIBUTE, childDataName);
      setRealAttributeValue   (data, VALUE_ATTRIBUTE, value);
      setStringAttributeValue (data, UNIT_ATTRIBUTE, unit);
    }
    catch (DOMException de)
    {
      throw ClubErreurs (ClubErreurs::xml_error,
                         toString (de.msg).c_str ());
    }
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createRealData (double value, const string& unit)
// Creates new string data. Current data must be a table.
// In
//      value : new value
//      unit  : unit of value
// Exception
//      ClubErreurs::invalid_element_type
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createRealData (double value, const string& unit)
  throw (ClubErreurs)
{
  // check if current data is a table
  int length = size ();
  if (XMLString::compareString(currentElement_->getTagName (),
                               REAL_TABLE_TAG)
      != 0)
    throw ClubErreurs (ClubErreurs::invalid_element_type ,
                       getCurrentData ().c_str (),
                       toString (currentElement_->getTagName ()).c_str (),
                       toString (REAL_DATA_TAG).c_str ());

  // try to create new DOMElement
  try
  {
    DOMElement* data = document_->createElement (REAL_DATA_TAG);
    currentElement_->appendChild (data);

    // set attribute values
    setIntAttributeValue    (data, INDEX_ATTRIBUTE, length+1);
    setRealAttributeValue   (data, VALUE_ATTRIBUTE, value);
    setStringAttributeValue (data, UNIT_ATTRIBUTE,  unit);
  }
  catch (DOMException de)
  {
    throw ClubErreurs (ClubErreurs::xml_error,
                       toString (de.msg).c_str ());
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createTable (const string& tableName,
//                            UniqDataFile::TableElementType tableType,
//                            const string& defaultUnit)
// Creates a child of type Table named tableName
// In
//      tableName : name of table data
//      tableType : type of table created (IntTable, StringTable, ...)
//      defaultUnit : default unit of tableName (optional)
// Exception
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::data_already_defined
//      ClubErreurs::index_creation_forbidden if tableName is an index name
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createTable (const string& tableName,
                           UniqDataFile::TableElementType tableType,
                           const string& defaultUnit) throw (ClubErreurs)
{
  if (isDataNameAnIndex (tableName))
  {
    // tableName is an index. cannot create a new DOMElement
    throw ClubErreurs (ClubErreurs::index_creation_forbidden,
                       getAbsoluteDataName (tableName).c_str ());
  }
  else
  {
     // Check is current data is not a table.
    testCurrentDataIsATable ();

   // check if no data named tableName exists
    testDataAlreadyDefined (tableName);

    // try to create new DOMElement
    try
    {
      DOMElement* data = 0;

      switch (tableType)
      {
        case UniqDataFile::IntTable :
          data = document_->createElement (INT_TABLE_TAG);
          break;

        case UniqDataFile::RealTable :
          data = document_->createElement (REAL_TABLE_TAG);
          // if needed, set default unit attribute value
          if (defaultUnit != "")
            setStringAttributeValue (data, DEFAULT_UNIT_ATTRIBUTE,
                                     defaultUnit);
          break;

        case UniqDataFile::StringTable :
          data = document_->createElement (STRING_TABLE_TAG);
          break;

        case UniqDataFile::TableTable :
          data = document_->createElement (TABLE_TABLE_TAG);
          break;

        case UniqDataFile::StructureTable :
          data = document_->createElement (STRUCTURE_TABLE_TAG);
          break;

        default :
          // this case never happens.
          break;
      }

      currentElement_->appendChild (data);

      // set name attribute value
      setStringAttributeValue (data, NAME_ATTRIBUTE, tableName);
    }
    catch (DOMException de)
    {
      throw ClubErreurs (ClubErreurs::xml_error,
                         toString (de.msg).c_str ());
    }
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createTable (UniqDataFile::TableElementType tableType,
//                            const string& defaultUnit)
// Creates new table. Current data must be a table.
// In
//      tableType : type of table created (IntTable, StringTable, ...)
//      defaultUnit : default unit of tableName (optional)
// Exception
//      ClubErreurs::invalid_element_type
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createTable (UniqDataFile::TableElementType tableType,
                           const string& defaultUnit)
  throw (ClubErreurs)
{
  // check if current data is a table
  int length = size ();

  // try to create new DOMElement
  try
  {
    DOMElement* data = 0;

    switch (tableType)
    {
      case UniqDataFile::IntTable :
        if (XMLString::compareString(currentElement_->getTagName (),
                                     TABLE_TABLE_TAG)
            != 0)
          throw ClubErreurs (ClubErreurs::invalid_element_type,
                             getCurrentData ().c_str(),
                             toString (currentElement_->getTagName ()).c_str (),
                             toString (INT_TABLE_TAG).c_str ());
        data = document_->createElement (INT_TABLE_TAG);
        break;

      case UniqDataFile::RealTable :
        if (XMLString::compareString(currentElement_->getTagName (),
                                     TABLE_TABLE_TAG)
            != 0)
          throw ClubErreurs (ClubErreurs::invalid_element_type,
                             getCurrentData ().c_str(),
                             toString (currentElement_->getTagName ()).c_str (),
                             toString (REAL_TABLE_TAG).c_str ());

        data = document_->createElement (REAL_TABLE_TAG);

        // set default unit attribute value
        if (defaultUnit != "")
          setStringAttributeValue (data, UNIT_ATTRIBUTE, defaultUnit);

        break;

      case UniqDataFile::StringTable :
        if (XMLString::compareString(currentElement_->getTagName (),
                                     TABLE_TABLE_TAG)
            != 0)
          throw ClubErreurs (ClubErreurs::invalid_element_type,
                             getCurrentData ().c_str(),
                             toString (currentElement_->getTagName ()).c_str (),
                             toString (STRING_TABLE_TAG).c_str ());

        data = document_->createElement (STRING_TABLE_TAG);
        break;

      case UniqDataFile::TableTable :
        if (XMLString::compareString(currentElement_->getTagName (),
                                     TABLE_TABLE_TAG)
            != 0)
          throw ClubErreurs (ClubErreurs::invalid_element_type,
                             getCurrentData ().c_str(),
                             toString (currentElement_->getTagName ()).c_str (),
                             toString (TABLE_TABLE_TAG).c_str ());

        data = document_->createElement (TABLE_TABLE_TAG);
        break;

      case UniqDataFile::StructureTable :
        if (XMLString::compareString(currentElement_->getTagName (),
                                     TABLE_TABLE_TAG)
            != 0)
          throw ClubErreurs (ClubErreurs::invalid_element_type,
                             getCurrentData ().c_str(),
                             toString (currentElement_->getTagName ()).c_str (),
                             toString (STRUCTURE_TABLE_TAG).c_str ());

        data = document_->createElement (STRUCTURE_TABLE_TAG);
        break;

      default :
        // this case never happens
        break;
    }

    currentElement_->appendChild (data);

    // set index attribute value
    setIntAttributeValue (data, INDEX_ATTRIBUTE, length+1);
  }
  catch (DOMException de)
  {
    throw ClubErreurs (ClubErreurs::xml_error,
                       toString (de.msg).c_str ());
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createStructure (const string& structureName)
// Creates a child of type Structure named structureName
// In
//      structureName : name of structure data
// Exception
//      ClubErreurs::index_creation_forbidden if structureName is an index name
//      ClubErreurs::xml_error
//      ClubErreurs::data_already_defined
//      ClubErreurs::current_data_is_a_table
//-----------------------------------------------------------------------------

void XMLData::createStructure (const string& structureName)
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (structureName))
  {
    // structureName is an index. cannot create a new DOMElement
    throw ClubErreurs (ClubErreurs::index_creation_forbidden,
                       getAbsoluteDataName (structureName).c_str ());
  }
  else
  {
    // Check is current data is not a table.
    testCurrentDataIsATable ();

    // check if no data named tableName exists
    testDataAlreadyDefined (structureName);

    // try to create new DOMElement
    try
    {
      DOMElement *data = document_->createElement (STRUCTURE_TAG);
      currentElement_->appendChild (data);

      // set name attribute value
      setStringAttributeValue (data, NAME_ATTRIBUTE, structureName);
    }
    catch (DOMException de)
    {
      throw ClubErreurs (ClubErreurs::xml_error,
                         toString (de.msg).c_str ());
    }
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createStructure ()
// Creates new structure. Current data must be a table.
// Exception
//      ClubErreurs::invalid_element_type
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createStructure () throw (ClubErreurs)
{
   // check if current data is a table
  int length = size ();

  if (XMLString::compareString(currentElement_->getTagName (),
                               STRUCTURE_TABLE_TAG)
      != 0)
    throw ClubErreurs (ClubErreurs::invalid_element_type ,
                       getCurrentData ().c_str (),
                       toString (currentElement_->getTagName ()).c_str (),
                       toString (STRUCTURE_TAG).c_str ());

  // try to create new DOMElement
  try
  {
    DOMElement *data = document_->createElement (STRUCTURE_TAG);
    currentElement_->appendChild (data);

    // set index attribute value
    setIntAttributeValue (data, INDEX_ATTRIBUTE, length+1);
  }
  catch (DOMException de)
  {
    throw ClubErreurs (ClubErreurs::xml_error,
                       toString (de.msg).c_str ());
  }
}




//-----------------------------------------------------------------------------
// void XMLData::createReference (const string& childDataName,
//                                const string& referencedFileName,
//                                const string& referencedDataName)
// Create new reference to another data.
// In
//      childDataName : name of child
//      referencedFileName : file containing the referenced data.
//      referencedDataName : the name of the referenced data.
// Exception
//      ClubErreur::data_already_defined if data exists
//      ClubErreurs::index_creation_forbidden if childDataName is an index name
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createReference (const string& childDataName,
                               const string& referencedFileName,
                               const string& referencedDataName)
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    // childDataName is an index. cannot create a new DOMElement
    throw ClubErreurs (ClubErreurs::index_creation_forbidden,
                       getAbsoluteDataName (childDataName).c_str ());
  }
  else
  {
    // check if no data named tableName exists
    testDataAlreadyDefined (childDataName);

    // Check is current data is not a table.
    testCurrentDataIsATable ();

    // try to create new DOMElement
    try
    {
      DOMElement* referenceData = document_->createElement (REFERENCE_TAG);
      currentElement_->appendChild (referenceData);

      // set name attribute value
      setStringAttributeValue (referenceData, NAME_ATTRIBUTE, childDataName);

      // set referenceData attribute value
      string xpointerName = dataNameToXPointer (referencedDataName,
                                                referencedFileName);
      setStringAttributeValue (referenceData, REFERENCE_ATTRIBUTE,
                               xpointerName);
    }
    catch (DOMException de)
    {
      throw ClubErreurs (ClubErreurs::xml_error,
                         toString (de.msg).c_str ());
    }
  }
}

//-----------------------------------------------------------------------------
// void XMLData::createReference (const string& referencedFileName,
//                                const string& referencedDataName)
// Create new reference. Current data must be a table.
// In
//      referencedFileName : file containing the referenced data.
//      referencedDataName : the name of the referenced data.
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------

void XMLData::createReference (const string& referencedFileName,
                               const string& referencedDataName)
  throw (ClubErreurs)
{
  // check if current data is a table
  int length = size ();

  // try to create new DOMElement
  try
  {
    DOMElement* referenceData = document_->createElement (REFERENCE_TAG);
    currentElement_->appendChild (referenceData);

    // set index attribute value
    setIntAttributeValue (referenceData, INDEX_ATTRIBUTE, length+1);

   // set reference attribute value
    string xpointerName = dataNameToXPointer (referencedDataName,
                                              referencedFileName);
    setStringAttributeValue (referenceData, REFERENCE_ATTRIBUTE,
                             xpointerName);
  }
  catch (DOMException de)
  {
    throw ClubErreurs (ClubErreurs::xml_error,
                       toString (de.msg).c_str());
  }
}

//-----------------------------------------------------------------------------
// string XMLData::getStringData (const string& childDataName)
// Reads the string attribute of data named childDataName
// In
//      childDataName : name of child
// Out
//      value of data
// Exception
//      ClubErreurs::undefined_parameter if data  does not exist
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::string_to_int_conversion_error
//
//      If data is a reference, those exceptions can be thrown :
//      ClubErreurs::xpointer_syntax_error if the reference is not compliant
//           to xpointer notation.
//      ClubErreurs::undefined_parameter if data  does not exist
//      ClubErreurs::undefined_table_or_structure if referenced data path
//              does not exist
//      ClubErreurs::file_error
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

string XMLData::getStringData (const string& childDataName)
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    // childDataName is an index
    return getStringData (getIndexValue (childDataName));
  }
  else
  {
    // search for child named childDataName
    DOMElement* stringData = getChildElement (NAME_ATTRIBUTE,
                                              childDataName,
                                              currentElement_);
    if (stringData == 0)
      throw ClubErreurs (ClubErreurs::undefined_parameter,
                         getAbsoluteDataName(childDataName).c_str());

    if (getElementType (stringData) == ReferenceType &&
        (stringData->getAttributeNode (VALUE_ATTRIBUTE) == 0))
    {
      string xpointer = getString (stringData, REFERENCE_ATTRIBUTE);
      string fileName;
      string referencedData;
      xpointerToDataName (xpointer, &referencedData, &fileName);

      string parentName = getParentName (referencedData);
      string childName  = getLastChildName (referencedData);
      XMLData xf (findFile (fileName,
                            toString (document_->getDocumentURI ())));
      xf.moveTo (parentName);

      setStringAttributeValue (stringData, VALUE_ATTRIBUTE,
                               xf.getStringData (childName));
    }

    return getString (stringData, VALUE_ATTRIBUTE);

  }
}

//-----------------------------------------------------------------------------
// string XMLData::getStringData (int index)
// Reads the string attribute of data whose index attribute is "index". Current
// data must be a table.
// In
//      index : value of index attribute
// Out
//      value of data
// Exception
//      ClubErreur::current_data_not_a_table
//      ClubErreur::undefined_index if data does not exist
//
//      If data is a reference, those exceptions can be thrown :
//      ClubErreurs::xpointer_syntax_error if the reference is not compliant
//           to xpointer notation.
//      ClubErreurs::undefined_parameter if data  does not exist
//      ClubErreurs::undefined_table_or_structure if referenced data path
//              does not exist
//      ClubErreurs::file_error
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

string XMLData::getStringData (int index) throw (ClubErreurs)
{
  // check if current data is a table
  if (getElementType (currentElement_) != TableType)
    throw ClubErreurs (ClubErreurs::current_data_not_a_table,
                       getCurrentData ().c_str ());

  // search for child whose index attribute is "index"
  DOMElement* stringData = getChildElement (INDEX_ATTRIBUTE,
                                            intToString (index),
                                            currentElement_);
  if (stringData == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  if (getElementType (stringData) == ReferenceType &&
      (stringData->getAttributeNode (VALUE_ATTRIBUTE) == 0))
  {
    string xpointer = getString (stringData, REFERENCE_ATTRIBUTE);
    string fileName;
    string referencedData;
    xpointerToDataName (xpointer, &referencedData, &fileName);

    string parentName = getParentName (referencedData);
    string childName  = getLastChildName (referencedData);
    XMLData xf (findFile (fileName,
                          toString (document_->getDocumentURI ())));
    xf.moveTo  (parentName);

    setStringAttributeValue (stringData, VALUE_ATTRIBUTE,
                             xf.getStringData (childName));
  }

  return getString (stringData, VALUE_ATTRIBUTE);

}

//-----------------------------------------------------------------------------
// int XMLData::getIntData (const string& childDataName)
// Reads the int attribute of data named childDataName
// In
//      childDataName : name of child
// Out
//      value of data
// Exception
//      ClubErreur::undefined_parameter if data does not exist
//      ClubErreurs::string_to_int_conversion_error
//
//      If data is a reference, those exceptions can be thrown :
//      ClubErreurs::xpointer_syntax_error if the reference is not compliant
//           to xpointer notation.
//      ClubErreurs::undefined_parameter if data  does not exist
//      ClubErreurs::undefined_table_or_structure if referenced data path
//              does not exist
//      ClubErreurs::file_error
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

int XMLData::getIntData (const string& childDataName) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
    // childDataName is an index
    return getIntData (getIndexValue (childDataName));
  else
  {

    // search for child named childDataName
    DOMElement* intData = getChildElement (NAME_ATTRIBUTE,
                                           childDataName,
                                           currentElement_);
    if (intData == 0)
      throw ClubErreurs (ClubErreurs::undefined_parameter,
                         getAbsoluteDataName (childDataName).c_str ());

    if (getElementType (intData) == ReferenceType &&
        (intData->getAttributeNode (VALUE_ATTRIBUTE) == 0))
    {
      string xpointer = getString (intData, REFERENCE_ATTRIBUTE);
      string fileName;
      string referencedData;
      xpointerToDataName (xpointer, &referencedData, &fileName);

      string parentName = getParentName (referencedData);
      string childName  = getLastChildName (referencedData);
      XMLData xf (findFile (fileName,
                            toString (document_->getDocumentURI ())));
      xf.moveTo  (parentName);

      setStringAttributeValue (intData, VALUE_ATTRIBUTE,
                               xf.getStringData (childName));
    }

    return getInt (intData, VALUE_ATTRIBUTE);

  }
}

//-----------------------------------------------------------------------------
// int XMLData::getIntData (int index)
// Reads the int attribute of data whose index attribute is "index".
// Current data must be a table.
// In
//      index : value of index attribute
// Out
//      value of data
// Exception
//      ClubErreur::current_data_not_a_table
//      ClubErreur::undefined_index if data does not exist
//      ClubErreurs::string_to_int_conversion_error
//
//      If data is a reference, those exceptions can be thrown :
//      ClubErreurs::xpointer_syntax_error if the reference is not compliant
//           to xpointer notation.
//      ClubErreurs::undefined_parameter if data  does not exist
//      ClubErreurs::undefined_table_or_structure if referenced data path
//              does not exist
//      ClubErreurs::file_error
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

int XMLData::getIntData (int index) throw (ClubErreurs)
{
  if (getElementType (currentElement_) != TableType)
    throw ClubErreurs (ClubErreurs::current_data_not_a_table,
                       getCurrentData ().c_str ());

  DOMElement* intData = getChildElement (INDEX_ATTRIBUTE,
                                         intToString (index),
                                         currentElement_);
  if (intData == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  if (getElementType (intData) == ReferenceType &&
      (intData->getAttributeNode (VALUE_ATTRIBUTE) == 0))
  {
    string xpointer = getString (intData, REFERENCE_ATTRIBUTE);
    string fileName;
    string referencedData;
    xpointerToDataName (xpointer, &referencedData, &fileName);

    string parentName = getParentName (referencedData);
    string childName  = getLastChildName (referencedData);
    XMLData xf (findFile (fileName,
                          toString (document_->getDocumentURI ())));
    xf.moveTo  (parentName);

    setStringAttributeValue (intData, VALUE_ATTRIBUTE,
                             xf.getStringData (childName));
  }

  return getInt (intData, VALUE_ATTRIBUTE);

}

//-----------------------------------------------------------------------------
// double XMLData::getRealData (const string& childDataName,
//                              const string& unit)
// Reads the real attribute of data named childDataName
// In
//      childDataName : name of child
//      unit : physical unit for value to return
// Out
//      value of data
// Exception
//      ClubErreurs::undefined_parameter if data does not exist
//      ClubErreurs::string_to_int_conversion_error
//      ClubErreurs::string_to_double_conversion_error
//      ClubErreurs::undefined_unit
//      ClubErreurs::malformed_data (see convert)
//
//      If data is a reference, those exceptions can be thrown :
//      ClubErreurs::xpointer_syntax_error if the reference is not compliant
//           to xpointer notation.
//      ClubErreurs::undefined_parameter if data  does not exist
//      ClubErreurs::undefined_table_or_structure if referenced data path
//              does not exist
//      ClubErreurs::file_error
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

double XMLData::getRealData (const string& childDataName,
                             const string& unit) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    // childDataName is an index
    return getRealData (getIndexValue (childDataName), unit);
  }
  else
  {
    // search for child named childDataName
    DOMElement* doubleData = getChildElement (NAME_ATTRIBUTE,
                                              childDataName,
                                              currentElement_);
    if (doubleData == 0)
      throw ClubErreurs (ClubErreurs::undefined_parameter,
                         getAbsoluteDataName (childDataName).c_str ());

    if (getElementType (doubleData) == ReferenceType &&
        (doubleData->getAttributeNode (VALUE_ATTRIBUTE) == 0))
    {
      string xpointer = getString (doubleData, REFERENCE_ATTRIBUTE);
      string fileName;
      string referencedData;
      xpointerToDataName (xpointer, &referencedData, &fileName);
      XMLData xf (findFile (fileName,
                            toString (document_->getDocumentURI ())));

      string parentName = getParentName (referencedData);
      string childName  = getLastChildName (referencedData);
      xf.moveTo  (parentName);

      setStringAttributeValue (doubleData, VALUE_ATTRIBUTE,
                               xf.getStringData (childName));

      DOMElement* element = getChildElement (NAME_ATTRIBUTE,
                                             childName,
                                             xf.currentElement_);
      if (element != 0)
      {
        setStringAttributeValue (doubleData, UNIT_ATTRIBUTE,
                                 getString (element, UNIT_ATTRIBUTE));
      }
    }

    // get value attribute of element found
    double value  = getDouble (doubleData, VALUE_ATTRIBUTE);
    const XMLCh* valueUnit = doubleData->getAttribute (UNIT_ATTRIBUTE);
    ArrayJanitor<XMLCh> janitor (XMLString::transcode (unit.c_str (),
                                                       XMLPlatformUtils::fgMemoryManager),
                                 XMLPlatformUtils::fgMemoryManager);
    if ((*(janitor.get ()) == chNull)
        || (XMLString::compareString (janitor.get (), valueUnit) == 0))
      return value;
    else
    {
      if (units_ == 0)
      {
        const XMLCh* fileName =
          document_->getDocumentElement()->getAttribute(UNITS_FILE_ATTRIBUTE);
        units_ = new XMLUnits (findFile (toString (fileName),
                                         toString (document_->getDocumentURI ())));
      }
      return units_->convert (value, valueUnit, janitor.get ());
    }
  }

}

//-----------------------------------------------------------------------------
// double XMLData::getRealData (int index, const string& unit)
// Reads the real attribute of data whose index attribute is "index". Current
// data must be a table.
// In
//      index : value of index attribute
//      unit  : physical unit for value to return
// Out
//      value of data
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index if data does not exist
//      ClubErreurs::string_to_double_conversion_error
//      ClubErreurs::undefined_unit
//      ClubErreurs::malformed_data (see convert)
//
//      If data is a reference, those exceptions can be thrown :
//      ClubErreurs::xpointer_syntax_error if the reference is not compliant
//           to xpointer notation.
//      ClubErreurs::undefined_parameter if data  does not exist
//      ClubErreurs::undefined_table_or_structure if referenced data path
//              does not exist
//      ClubErreurs::file_error
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

double XMLData::getRealData (int index, const string& unit) throw (ClubErreurs)
{
  // check if current data is a table
  if (getElementType (currentElement_) != TableType)
  {
    throw ClubErreurs (ClubErreurs::current_data_not_a_table,
                       getCurrentData ().c_str ());
  }

  // search for child whose index attribute is "index"
  DOMElement* doubleData = getChildElement (INDEX_ATTRIBUTE,
                                            intToString (index),
                                            currentElement_);
  if (doubleData == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  if (getElementType (doubleData) == ReferenceType &&
      (doubleData->getAttributeNode (VALUE_ATTRIBUTE) == 0))
  {
    string xpointer = getString (doubleData, REFERENCE_ATTRIBUTE);
    string fileName;
    string referencedData;
    xpointerToDataName (xpointer, &referencedData, &fileName);

    string parentName = getParentName (referencedData);
    string childName  = getLastChildName (referencedData);
    XMLData xf (findFile (fileName,
                          toString (document_->getDocumentURI ())));
    xf.moveTo  (parentName);

    setStringAttributeValue (doubleData, VALUE_ATTRIBUTE,
                             xf.getStringData (childName));

    DOMElement* element = getChildElement (NAME_ATTRIBUTE,
                                           childName,
                                           xf.currentElement_);
    if (element != 0)
    {
      setStringAttributeValue (doubleData, UNIT_ATTRIBUTE,
                               getString (element, UNIT_ATTRIBUTE));
    }
  }

  // get value attribute of element found
  double value  = getDouble (doubleData, VALUE_ATTRIBUTE);
  const XMLCh* valueUnit = doubleData->getAttribute (UNIT_ATTRIBUTE);
  ArrayJanitor<XMLCh> janitor (XMLString::transcode (unit.c_str (),
                                                     XMLPlatformUtils::fgMemoryManager),
                               XMLPlatformUtils::fgMemoryManager);
  if ((*(janitor.get ()) == chNull)
      || (XMLString::compareString (janitor.get (), valueUnit) == 0))
    return value;
  else
  {
    if (units_ == 0)
    {
      const XMLCh* fileName =
        document_->getDocumentElement()->getAttribute(UNITS_FILE_ATTRIBUTE);
      units_ = new XMLUnits (findFile (toString (fileName),
                                       toString (document_->getDocumentURI ())));
    }
    return units_->convert (value, valueUnit, janitor.get ());
  }

}


//-----------------------------------------------------------------------------
// void XMLData::getReference (const string& childDataName,
//                             string* referencedFileName,
//                             string* referencedDataName)
// Read the reference attribute of data whose name attribute is childDataName.
// In
//      childDataName : name of attribute
// Out
//      referencedFileName : file containing the referenced data
//      referencedDataName : name of the referenced data
// Exception
//      ClubErreurs::undefined_parameter if data does not exist
//      ClubErreurs::xpointer_syntax_error if the reference is not compliant
//           to xpointer notation.
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

void XMLData::getReference (const string& childDataName,
                            string* referencedFileName,
                            string* referencedDataName)
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    // childDataName is an index
    getReference (getIndexValue (childDataName), referencedFileName,
                  referencedDataName);
  }
  else
  {
    // search for child named childDataName
    DOMElement* referenceData = getChildElement (NAME_ATTRIBUTE,
                                                 childDataName,
                                                 currentElement_);
    if (referenceData == 0)
      throw ClubErreurs (ClubErreurs::undefined_parameter,
                         getAbsoluteDataName (childDataName).c_str ());

    // get value attribute of element found
    string xpointer = getString (referenceData, REFERENCE_ATTRIBUTE);
    xpointerToDataName (xpointer, referencedDataName, referencedFileName);

  }
}

//-----------------------------------------------------------------------------
// void XMLData::getReference (int index, string* referencedFileName,
//                             string* referencedDataName)
// Read the reference attribute of data whose name attribute is childDataName.
// Current data must be a table.
// In
//      index : value of index attribute
// Out
//      referencedFileName : file containing the referenced data
//      referencedDataName : name of the referenced data
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index if index does not exist
//      ClubErreurs::xpointer_syntax_error if the reference is not compliant
//           to xpointer notation.
//-----------------------------------------------------------------------------

void XMLData::getReference (int index, string* referencedFileName,
                            string* referencedDataName)
  throw (ClubErreurs)
{
  // check if current data is a table
  testCurrentDataNotATable ();

  // search for child whose index attribute is "index"
  DOMElement* referenceData = getChildElement (INDEX_ATTRIBUTE,
                                               intToString (index),
                                               currentElement_);
  if (referenceData == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  // get value attribute of element found
  string xpointer = getString (referenceData, REFERENCE_ATTRIBUTE);
  xpointerToDataName (xpointer, referencedDataName, referencedFileName);

}


//-----------------------------------------------------------------------------
// void XMLData::setStringData (const string& childDataName,
//                              const string& value)
// Updates or creates the value attribute of childDataName (childDataName must
// be a string data)
// In
//      childDataName : name of string data
//      value : new value
// Exception
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_parameter
//      ClubErreurs::string_to_int_coneversion_error
//-----------------------------------------------------------------------------

void XMLData::setStringData (const string& childDataName,
                             const string& value) throw (ClubErreurs)
{
  if (isDataNameAnIndex(childDataName))
  {
    // childDataName is an index
    setStringData (getIndexValue (childDataName), value);
  }
  else
  {
    // search for child named childDataName
    DOMElement* data = getChildElement (NAME_ATTRIBUTE,
                                        childDataName,
                                        currentElement_);
    if (data == 0)
      throw ClubErreurs (ClubErreurs::undefined_parameter,
                         getAbsoluteDataName (childDataName).c_str ());

    setStringAttributeValue (data, VALUE_ATTRIBUTE, value);

  }
}

//-----------------------------------------------------------------------------
// void XMLData::setStringData (int index, const string& value)
// Updates or creates the value attribute of a string data. Current data must
// be a table
// In
//      index : index of child
//      value : new value
// Exception
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

void XMLData::setStringData (int index, const string& value)
  throw (ClubErreurs)
{
  testCurrentDataNotATable ();

  // search for child whose index attribute is index
  DOMElement* data = getChildElement (INDEX_ATTRIBUTE,
                                      intToString (index),
                                      currentElement_);
  if (data == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  setStringAttributeValue (data, VALUE_ATTRIBUTE, value);

}

//-----------------------------------------------------------------------------
// void XMLData::setIntData (const string& childDataName, int value)
// Updates or creates the value attribute of childDataName (childDataName must
// be an int data)
// In
//      childDataName : name of int data
//      value : new value
// Exception
//      ClubErreurs::undefined_parameter
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::string_to_int_conversion_error
//-----------------------------------------------------------------------------

void XMLData::setIntData (const string& childDataName, int value)
  throw (ClubErreurs)
{
  if (isDataNameAnIndex(childDataName))
  {
    // childDataName is an index
    setIntData (getIndexValue (childDataName), value);
  }
  else
  {
    // search for child named childDataName
    DOMElement* data = getChildElement (NAME_ATTRIBUTE,
                                        childDataName,
                                        currentElement_);
    if (data == 0)
      throw ClubErreurs (ClubErreurs::undefined_parameter,
                         getAbsoluteDataName (childDataName).c_str ());

    setIntAttributeValue (data, VALUE_ATTRIBUTE, value);

  }
}

//-----------------------------------------------------------------------------
// void XMLData::setIntData (int index, int value))
// Updates or creates the value attribute of an int data. Current data must
// be a table
// In
//      index : index of child
//      value : new value
// Exception
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

void XMLData::setIntData (int index, int value) throw (ClubErreurs)
{
  testCurrentDataNotATable ();

  // search for child whose index attribute is index
  DOMElement* data = getChildElement (INDEX_ATTRIBUTE,
                                      intToString (index),
                                      currentElement_);
  if (data == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  setIntAttributeValue (data, VALUE_ATTRIBUTE, value);

}

//-----------------------------------------------------------------------------
// void XMLData::setRealData (const string& childDataName, double value,
//                            const string& unit)
// Updates or creates the value attribute of childDataName (childDataName must
// be a real data)
// In
//      childDataName : name of real data
//      value : new value
//      unit : unit of value
// Exception
//      ClubErreurs::undefined_parameter
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::string_to_int_conversion_error
//-----------------------------------------------------------------------------

void XMLData::setRealData (const string& childDataName, double value,
                           const string& unit) throw (ClubErreurs)
{
  if (isDataNameAnIndex(childDataName))
  {
    // childDataName is an index
    setRealData (getIndexValue (childDataName), value, unit);
  }
  else
  {
    // search for child named childDataName
    DOMElement* data = getChildElement (NAME_ATTRIBUTE,
                                        childDataName,
                                        currentElement_);
    if (data == 0)
      throw ClubErreurs (ClubErreurs::undefined_parameter,
                         getAbsoluteDataName (childDataName).c_str ());

    setRealAttributeValue   (data, VALUE_ATTRIBUTE, value);
    setStringAttributeValue (data, UNIT_ATTRIBUTE, unit);

  }
}

//-----------------------------------------------------------------------------
// void XMLData::setRealData (int index, int value, const string& unit)
// Updates or creates the value attribute of a real data. Current data must
// be a table
// In
//      index : index of child
//      value : new value
//      unit  : unit of value
// Exception
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

void XMLData::setRealData (int index, double value, const string& unit)
  throw (ClubErreurs)
{
  testCurrentDataNotATable ();

  // search for child whose index attribute is index
  DOMElement* data = getChildElement (INDEX_ATTRIBUTE,
                                      intToString (index),
                                      currentElement_);
  if (data == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  setRealAttributeValue   (data, VALUE_ATTRIBUTE, value);
  setStringAttributeValue (data, UNIT_ATTRIBUTE, unit);

}

//-----------------------------------------------------------------------------
// void XMLData::deleteData (const string& dataName)
// Deletes a data.
// In
//      dataName : name of data to delete
// Exception
//      ClubErreurs::undefined_data if no data named dataName exists
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::string_to_int_conversion_error
//-----------------------------------------------------------------------------

void XMLData::deleteData (const string& dataName) throw (ClubErreurs)
{
  if (isDataNameAnIndex (dataName))
  {
    // dataName is an index. Call deleteData (int index)
    deleteData (getIndexValue (dataName));
  }
  else
  {
    // search for child named dataName
    testCurrentDataIsATable ();
    DOMElement* data = getChildElement (NAME_ATTRIBUTE,
                                        dataName,
                                        currentElement_);
    if (data == 0)
      throw ClubErreurs (ClubErreurs::undefined_data,
                         getAbsoluteDataName (dataName).c_str ());

    // delete child
    currentElement_->removeChild (data);

  }
}

//-----------------------------------------------------------------------------
// void XMLData::deleteData (int index)
// Deletes a data. Current data must be a table.
// In
//      index : value of index attribute of data to delete
// Exception
//      ClubErreurs::undefined_index if no index equals to "index" exists
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

// Deletes a data (only for tables).
void XMLData::deleteData (int index) throw (ClubErreurs)
{
  // check if current data is a table
  int length = size ();

  // search for child whose index attribute equals to "index"
  DOMElement* deletedData = getChildElement (INDEX_ATTRIBUTE,
                                             intToString (index),
                                             currentElement_);
  if (deletedData == 0)
    throw ClubErreurs (ClubErreurs::undefined_index, index,
                       getCurrentData ().c_str ());

  // delete child
  currentElement_->removeChild (deletedData);

  // change index attribute value of child next to child deleted
  for (int i = index + 1; i <= length; i++)
    setIntAttributeValue (getChildElement (INDEX_ATTRIBUTE,
                                           intToString (i),
                                           currentElement_),
                          INDEX_ATTRIBUTE, i-1);

}


//-----------------------------------------------------------------------------
// void XMLData::includeFile (const string& fileName)
// Include a data file into the memory DOM as children of the Data tag.
// All included data have a INCLUDED_FROM attribute.
// If the file is already included then delete old data and include
// it once again.
// Data with the same name are overwritten.
// In
//      fileName : the name of the dataFile.
// Exception
//      Club_erreurs::missing_tag if club-data tag is not found
//-----------------------------------------------------------------------------

void XMLData::includeFile (const string& fileName) throw (ClubErreurs)
{
  // Search for the club-data tag in the instance.
  DOMElement* clubData = getChildElement (CLUB_DATA_TAG, document_);

  // load the file
  XMLData xf (findFile (fileName,
                        toString (document_->getDocumentURI ())));
  DOMElement* loadedData = getChildElement (CLUB_DATA_TAG, xf.document_);

  // If the file is already included then delete all included data.
  DOMElement* includeElement = getChildElement (INCLUDED_FILE_ATTRIBUTE,
                                                fileName, clubData);
  ArrayJanitor<XMLCh> janitor (XMLString::transcode(fileName.c_str(),
                                                    XMLPlatformUtils::fgMemoryManager),
                               XMLPlatformUtils::fgMemoryManager);
  if (includeElement != 0)
  {
    // Delete the data (but keep the include element)
    deleteIncludedFile (fileName);
  }
  else
  {
    // Create and append the include element.
    includeElement = document_->createElement (INCLUDE_TAG);
    includeElement->setAttribute (INCLUDED_FILE_ATTRIBUTE, janitor.get ());
    try
    {
      clubData->appendChild (includeElement);
    }
    catch (DOMException de)
    {
      throw ClubErreurs (ClubErreurs::xml_error, toString (de.msg).c_str ());
    }
  }

  // Replace or append included data.
  DOMNodeList* list = loadedData->getChildNodes ();
  for (XMLSize_t i = 0; i < list->getLength (); ++i)
  {
    if (list->item (i)->getNodeType () == DOMNode::ELEMENT_NODE)
    {
      DOMElement* child = (DOMElement *) list->item (i);
      child->setAttribute (INCLUDED_FROM_ATTRIBUTE, janitor.get ());
      try
      {
        // remove data with the same name.
        DOMElement* elementToRemove =
          getChildElement (NAME_ATTRIBUTE,
                           child->getAttribute (NAME_ATTRIBUTE),
                           clubData);
        if (elementToRemove != 0)
          clubData->replaceChild (document_->importNode (child, true),
                                  elementToRemove);
        else
          clubData->appendChild (document_->importNode (child, true));
      }
      catch (DOMException de)
      {
        throw ClubErreurs (ClubErreurs::xml_error,
                           toString (de.msg).c_str ());
      }
    }
  }
}


//-----------------------------------------------------------------------------
// void XMLData::deleteIncludedFile (const string& fileName)
// Delete all data included with the given file name.
// If no data is included from this file then do nothing.
// In
//      fileName : the name of the dataFile.
// Exception
//      Club_erreurs::missing_tag if club-data tag is not found.
//-----------------------------------------------------------------------------

void XMLData::deleteIncludedFile (const string& fileName)
    throw (ClubErreurs)
{
  // Search for the club-data tag in the instance.
  DOMElement* clubData = getChildElement (CLUB_DATA_TAG, document_);

  // Remove all data included from the file.
  DOMElement* elementToRemove;
  do {
    elementToRemove = getChildElement (INCLUDED_FROM_ATTRIBUTE,
                                       fileName, clubData);
    if (elementToRemove != 0)
      clubData->removeChild (elementToRemove);
  } while (elementToRemove != 0);

}

//-----------------------------------------------------------------------------
// bool XMLData::canMoveUp ()
// Check if moving up is allowed
// Out
//      true if parent node is not CLUB_DATA_TAG, false otherwise
//-----------------------------------------------------------------------------

bool XMLData::canMoveUp ()
{
  return XMLString::compareString(currentElement_->getTagName (),
                                  CLUB_DATA_TAG)
        != 0;
}

//-----------------------------------------------------------------------------
// void XMLData::writeReferencedFiles (DOMElement* element)
// Write the referenced XML files in a element sub-tree
// Exception
//      ClubErreurs::xml_error
//-----------------------------------------------------------------------------
void XMLData::writeReferencedFiles (DOMElement* element) throw (ClubErreurs)
{
  if (hasChildElements (element))
  {
    if (getElementType (element) == ReferenceType)
    {
      string xpointer = getString (element, REFERENCE_ATTRIBUTE);
      string fileName;
      string referencedData;
      xpointerToDataName (xpointer, &referencedData, &fileName);
      string absolute = findFile (fileName,
                                  toString (document_->getDocumentURI ()));
      XMLData xf (absolute);
      xf.moveTo  (referencedData);

      // remove childs existing in the file
      DOMNodeList* list = xf.currentElement_->getChildNodes();
      for (XMLSize_t i = 0; i < list->getLength (); ++i)
      {
        if (list->item (i)->getNodeType() == DOMNode::ELEMENT_NODE)
        {
          xf.currentElement_->removeChild (list->item (i));
          --i;
        }
      }

      // add childs from the DOM tree
      list = element->getChildNodes();
      for (XMLSize_t i = 0; i < list->getLength (); ++i)
      {
        if (list->item (i)->getNodeType() == DOMNode::ELEMENT_NODE)
        {
          DOMNode *node = xf.document_->importNode(list->item (i), true);
          xf.currentElement_->appendChild (node);
        }
      }

      // write the updated referenced file
      xf.writeFile (absolute);

    }
    else
    {
      // recurse down the tree
      DOMNodeList* list = element->getChildNodes();
      for (XMLSize_t i = 0; i < list->getLength (); ++i)
      {
        DOMNode* child = list->item (i);
        if (child->getNodeType () == DOMNode::ELEMENT_NODE)
        {
          writeReferencedFiles ((DOMElement *) child);
        }
      }
    }
  }
}

//-----------------------------------------------------------------------------
// UniqDataFile::DataType XMLData::getElementType (const DOMElement* element)
// Returns the type of element
// In
//      element : the DOMElement whose type is searched.
// Out
//      type of element (value of enum UniqDataFile::DataType)
//-----------------------------------------------------------------------------

UniqDataFile::DataType XMLData::getElementType (const DOMElement* element)
{
  const XMLCh *name = element->getTagName ();
  UniqDataFile::DataType result;
  if ((XMLString::compareString(name, TABLE_TABLE_TAG)     == 0) ||
      (XMLString::compareString(name, INT_TABLE_TAG)       == 0) ||
      (XMLString::compareString(name, REAL_TABLE_TAG)      == 0) ||
      (XMLString::compareString(name, STRING_TABLE_TAG)    == 0) ||
      (XMLString::compareString(name, STRUCTURE_TABLE_TAG) == 0))
  {
    result = TableType;
  }
  else if (XMLString::compareString(name, STRUCTURE_TAG) == 0)
  {
    result = StructureType;
  }
  else if ((XMLString::compareString(name, REAL_DATA_TAG)   == 0) ||
           (XMLString::compareString(name, INT_DATA_TAG)    == 0) ||
           (XMLString::compareString(name, STRING_DATA_TAG) == 0))
  {
    result = ParameterType;
  }
  else if (XMLString::compareString(name, REFERENCE_TAG) == 0)
  {
    result = ReferenceType;
  }
  else
  {
    result = UndeterminedType;
  }

  return result;
}


//-----------------------------------------------------------------------------
// void XMLData::testCurrentDataNotATable ()
// Check if current data is not a table
// Exception
//      current_data_not_a_table if current data is not a table
//-----------------------------------------------------------------------------

void XMLData::testCurrentDataNotATable ()
  throw (ClubErreurs)
{
  if (getElementType (currentElement_) != TableType)
    throw ClubErreurs (ClubErreurs::current_data_not_a_table,
                       getCurrentData ().c_str ());
}


//-----------------------------------------------------------------------------
// void XMLData::testCurrentDataIsATable ()
// Check if current data is a table
// Exception
//      current_data_is_a_table if current data is a table
//-----------------------------------------------------------------------------

void XMLData::testCurrentDataIsATable () throw (ClubErreurs)
{
   if (getElementType (currentElement_) == TableType)
    throw ClubErreurs (ClubErreurs::current_data_not_a_table,
                       getCurrentData ().c_str ());
}


bool XMLData::ignoreNode (const DOMNode* node) const
{
  if (node->getNodeType() != DOMNode::ELEMENT_NODE)
    return false;

  if (((DOMElement *) node)->hasAttribute (INCLUDED_FROM_ATTRIBUTE))
  {
    // don't write nodes included from another file
    return true;
  }

  if (node->getParentNode()->getNodeType () == DOMNode::ELEMENT_NODE)
  {
    DOMElement *parent = (DOMElement *) (node->getParentNode());
    if (XMLString::compareString (parent->getTagName (), REFERENCE_TAG) == 0)
      // don't write nodes belonging to a referenced file
      return true;
  }

  return false;

}
