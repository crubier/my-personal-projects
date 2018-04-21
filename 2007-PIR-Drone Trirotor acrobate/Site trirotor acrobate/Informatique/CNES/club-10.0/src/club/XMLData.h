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
//>       XMLData.h
//
//$Summary
//       Definition file of class XMLData
//
//$Description
//       Declaration module of class XMLData
//
//$Content
//>       class XMLData
//$History
//       $Log: XMLData.h,v $
//       Revision 1.3  2005/02/25 07:41:57  chope
//       put the getReference, includeFile and deleteIncludedFile as private
//
//       Revision 1.2  2005/02/21 13:15:02  chope
//       déplacement du corps du constructeur par copie et de l'affectation dans le fichier .cpp
//
//       Revision 1.1  2005/02/04 10:05:37  chope
//       initial version
//
//
//$Version
//       $Id: XMLData.h,v 1.3 2005/02/25 07:41:57 chope Exp $
//
//$Authors
//       L. Maisonobe CSSI
//       Copyright (C) 2005 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_XMLData_h
#define club_XMLData_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include <string>

#include "club/UniqDataFile.h"
#include "club/ClubErreurs.h"
#include <club/XMLFile.h>
#include <club/XMLUnits.h>

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Name
//>       class XMLData
//$Summary
//        XMLData is a XML file management class.
//
//$Description
//        This class is useful for writing and reading XML file. It contains
//        a lot of functions to create, update or delete datas in a XML file.
//        Those functions use the XML parser Xerces and give a comprehensive
//        abstraction to manage easily a XML file. Thus users don't have to
//        act directly on the DOM.
//        XMLFile derives from UniqDataFile and thus implements all virtual
//        methods of UniqDataFile.
//
//$Usage
//>     construction :
//        with no argument, with a file name.
//>     usage :
//>       virtual void moveDown                      () 2 signatures -
//          move data pointer on a child of current data
//>       virtual void moveUp                        ()
//          move data pointer on the mother of current data
//>       virtual void readFile                      ()
//          load a file in memory
//>       virtual void writeFile                     ()
//          write the DOM in a file
//>       virtual UniqDataFile::DataType getDataType () 2 signatures -
//          return the type of a child of current data
//>       virtual int size                           ()
//          return the number of elements of a table data
//>       virtual bool dataExists                    () 2 signatures -
//          check whether a data exists
//>       virtual string getComment                  () 2 signatures -
//          return comments of a data
//>       virtual void setComment                    () 2 signatures -
//          update or create comment attribute of a data
//>       virtual void createStringData              () 2 signatures -
//          create a string parameter
//>       virtual void createIntData                 () 2 signatures -
//          create an integer parameter
//>       virtual void createRealData                () 2 signatures -
//          create a double parameter
//>       virtual void createTable                   () 2 signatures -
//          create a table data
//>       virtual void createStructure               () 2 signatures -
//          create a structure
//>       virtual void createReference               () 2 signatures -
//          create a reference
//>       virtual string getStringData               () 2 signatures -
//          read a string parameter
//>       virtual int getIntData                     () 2 signatures -
//          read an integer parameter
//>       virtual double getRealData                 () 2 signatures -
//          read a double parameter
//>       virtual double getReference                () 2 signatures -
//          read a reference
//>       virtual void setStringData                 () 2 signatures -
//          update a string parameter
//>       virtual void setIntData                    () 2 signatures -
//          update an integer parameter
//>       virtual void setRealData                   () 2 signatures -
//          update a double parameter
//>       virtual void deleteData                    () 2 signatures -
//          delete a data and its children
//>       virtual void writeMemoryStructure          ()
//          write all the memory DOM in the standard output
//>       virtual bool canMoveUp                     ()
//          check if we can go up in the data structure
//
//$Authors
//       L. Maisonobe CSSI
//       Copyright (C) CNES 2005
//$<>
///////////////////////////////////////////////////////////////////////////////


class XMLData : public UniqDataFile, XMLFile
{

public :


  // CONSTRUCTOR & DESTRUCTOR

  // Create a XMLData.
  XMLData () throw (ClubErreurs);

  XMLData (const string& fileName)
    throw (ClubErreurs);

  // Destruct a XMLData instance.
  virtual ~XMLData ();


  // DATA POINTER MANAGEMENT

  // Move data pointer on a child of current data
  virtual void moveDown (const string& relativeDataName) throw (ClubErreurs);

  // Move data pointer on an element of current data.
  // Current data must be a table.
  virtual void moveDown (int index) throw (ClubErreurs);

  // Move data pointer on the mother of current data.
  virtual void moveUp   () throw (ClubErreurs);

  // FILE MANAGEMENT

  // Load a file in memory
  virtual void readFile   (const string& fileName) throw (ClubErreurs);

  // Write a XML file
  virtual void writeFile  (const string& fileName) throw (ClubErreurs);

  // DATA INFORMATION

  // Return the type of a child of current data.
  virtual UniqDataFile::DataType getDataType (const string& childDataName)
    throw (ClubErreurs);

  // Return the type of a child of current data (only for tables).
  virtual UniqDataFile::DataType getDataType (int index)
    throw (ClubErreurs);

  // Return the number of elements (only for tables).
  virtual int     size       () throw (ClubErreurs) ;

  // Check whether a child data exists
  virtual bool    dataExists (const string& childDataName) throw (ClubErreurs);

  // Check whether a child data exists. Current data must be a table.
  virtual bool    dataExists (int index) throw (ClubErreurs);

  // Return the comments for a given parameter.
  virtual string  getComment (const string& childDataName) throw (ClubErreurs);

  // Return the comments for a given parameter (only for tables).
  virtual string  getComment (int index) throw (ClubErreurs);

  // Set comments for a given parameter.
  virtual void    setComment (const string& childDataName,
                              const string& comment) throw (ClubErreurs);

  // Set comments for a given parameter (only for tables).
  virtual void    setComment (int index, const string& comment)
    throw (ClubErreurs);


  // PARAMETER CREATION

  // Create a string parameter.
  virtual void createStringData (const string& childDataName,
                                 const string& value) throw (ClubErreurs);

  // Create a string parameter (only for tables).
  virtual void createStringData (const string& value) throw (ClubErreurs);

  // Create an integer parameter.
  virtual void createIntData    (const string& childDataName, int value)
    throw (ClubErreurs);

  // Create an integer parameter (only for tables).
  virtual void createIntData    (int value) throw (ClubErreurs);

  // Create a double parameter.
  virtual void createRealData   (const string& childDataName, double value,
                                 const string& unit) throw (ClubErreurs);

  // Create a double parameter (only for tables).
  virtual void createRealData   (double value, const string& unit)
    throw (ClubErreurs);

  // Create a table.
  virtual void createTable      (const string& tableName,
                                 UniqDataFile::TableElementType tableType,
                                 const string& defaultUnit = "")
    throw (ClubErreurs);

  // Create a table (only for tables).
  virtual void createTable      (UniqDataFile::TableElementType tableType,
                                 const string& defaultUnit = "")
    throw (ClubErreurs);

  // Create a structure.
  virtual void createStructure  (const string& structureName)
    throw (ClubErreurs);

  // Create a structure (only for tables).
  virtual void createStructure  () throw (ClubErreurs);

  // Create a reference.
  virtual void createReference  (const string& childDataName,
                                 const string& referencedFileName,
                                 const string& referencedDataName)
    throw (ClubErreurs);

  // Create a reference (only for tables).
  virtual void createReference  (const string& referencedFileName,
                                 const string& referencedDataName)
    throw (ClubErreurs);

  // DATA READING

  // Read a string parameter.
  virtual string  getStringData (const string& childDataName)
    throw (ClubErreurs);

  // Read a string parameter (only for tables).
  virtual string  getStringData (int index) throw (ClubErreurs);

  // Read an integer parameter.
  virtual int     getIntData    (const string& childDataName)
    throw (ClubErreurs);

  // Read an integer parameter (only for tables).
  virtual int     getIntData    (int index) throw (ClubErreurs);

  // Read a real parameter.
  virtual double  getRealData   (const string& childDataName,
                                 const string& unit) throw (ClubErreurs);

  // Read a real parameter (only for tables).
  virtual double  getRealData   (int index, const string& unit)
    throw (ClubErreurs);


  // PARAMETER UPDATE

  // Update a string parameter.
  virtual void setStringData (const string& childDataName,
                              const string& value) throw (ClubErreurs);

  // Update a string parameter.
  virtual void setStringData (int index, const string& value)
    throw (ClubErreurs);

  // Update an integer parameter.
  virtual void setIntData    (const string& childDataName, int value)
    throw (ClubErreurs);

  // Update an integer parameter.
  virtual void setIntData    (int index, int value) throw (ClubErreurs);

  // Update a double parameter.
  virtual void setRealData   (const string& childDataName, double value,
                              const string& unit) throw (ClubErreurs);

  // Update a double parameter.
  virtual void setRealData   (int index, double value, const string& unit)
    throw (ClubErreurs);


  // DATA DELETION

  // Delete a data.
  virtual void deleteData (const string& dataName) throw (ClubErreurs);

  // Delete a data (only for tables).
  virtual void deleteData (int index) throw (ClubErreurs);

  // Write all the memory DOM in the standard output.
  virtual void writeMemoryStructure () throw (ClubErreurs);

  // Check if moving up is possible.
  virtual bool  canMoveUp    ();

protected:

  virtual bool ignoreNode (const DOMNode* node) const;

private:

  // OTHERS CONSTRUCTORS
  // N.B.: these constructors are private because
  // we don't want any call for them
  XMLData (const XMLData & other);
  XMLData & operator = (const XMLData & other) { return *this; }

  // Create a file inclusion.
  void includeFile (const string& fileName)
    throw (ClubErreurs);

  // delete included data from a given file.
  void deleteIncludedFile (const string& fileName)
    throw (ClubErreurs);

  // Write the referenced XML files in a element sub-tree
  void writeReferencedFiles (DOMElement* element) throw (ClubErreurs);

  // Read a reference.
  void getReference (const string& childDataName,
                     string* referencedFileName,
                     string* referencedDataName)
    throw (ClubErreurs);

  // Read a reference (only for tables).
  void getReference (int index,
                     string* referencedFileName,
                     string* referencedDataName)
    throw (ClubErreurs);

  // Return the element type.
  UniqDataFile::DataType getElementType (const DOMElement* element);

  // Throw ClubErreur::current_data_not_a_table if the given table
  // or structure does not exist
  void testCurrentDataNotATable () throw (ClubErreurs);

  // Throw ClubErreur::current_data_is_a_table if the current data
  // is a table
  void testCurrentDataIsATable () throw (ClubErreurs);

  // Units document
  const XMLUnits* units_;

  // Current element (data pointer)
  DOMElement*  currentElement_;

};

#endif
