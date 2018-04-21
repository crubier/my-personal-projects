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
//>       StructureFile.h
//
//$Summary
//       Definition file of class StructureFile
//
//$Description
//       Declaration module of class StructureFile
//
//$Content
//>       class StructureFile
//$History
//       $Log: StructureFile.h,v $
//       Revision 1.6  2005/02/04 09:56:37  chope
//       élimination de la méthode loadUnitFile (DM-ID 242)
//
//       Revision 1.5  2002/12/09 15:58:15  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.4  2000/10/25 09:31:44  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.3  2000/10/24 14:18:15  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.2  2000/10/18 09:05:34  club
//       suppression de la levée d'exception pour le destructeur.
//
//       Revision 1.1  2000/10/16 15:36:05  club
//       Initial revision.
//
//$Version
//       $Id: StructureFile.h,v 1.6 2005/02/04 09:56:37 chope Exp $
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI 
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_StructureFile_h
#define club_StructureFile_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <string>

#include "club/ClubErreurs.h"
#include "club/FichierStructure.h"
#include "club/UniqDataFile.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Name
//>       class StructureFile
//$Summary
//        StructureFile is a "FichierStructuré" management class.
//
//$Description
//        This class is usefull for reading FichierStructuré file. This class
//        is based on FichierStructure class and functions in StructureFile
//        call FichierStructure methods.
//        This class does not offer services for writing FichierStructuré files,
//        all this services throw a ClubErreurs::not_implemented_exception.
// 
//        StructureFile derives from UniqDataFile. Thus every virtual functions
//        of UniqDataFile must be implemented in StructureFile even though 
//        FichierStructure does not give an equivalent service.
//
//$Usage
//>     construction :
//        with no argument.
//>     usage :
//>       virtual void moveDown                      () 2 signatures - 
//          move data pointer on a child of current data
//>       virtual void moveUp                        () 
//          move data pointer on the mother of current data
//>       virtual void moveTo                        () 
//          move data pointer on any data 
//>       virtual void readFile                      () 
//          load a file in memory
//>       virtual void writeFile                     () 
//          write a file
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
//>       virtual void setStringData                 () 2 signatures - 
//          update a string parameter
//>       virtual void setIntData                    () 2 signatures - 
//          update an integer parameter
//>       virtual void setRealData                   () 2 signatures - 
//          update a double parameter
//>       virtual void deleteData                    () 2 signatures - 
//          delete a data and its children
//>       virtual void writeMemoryStructure          ()                   
//          write the memory structure in standard output
///
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI 
//       Copyright (C) CNES 2000
//$<>
///////////////////////////////////////////////////////////////////////////////


class StructureFile : public UniqDataFile 
{
public :
  
  // CONSTRUCTOR ET DESTRUCTOR
  
  // Build a new StructureFile by initializing current data
  StructureFile () : UniqDataFile ()
  {}

  // Destruct a StructureFile instance
  virtual ~StructureFile () 
  {}


  // DATA POINTER MANAGEMENT

  // Move data pointer on a child of current data
  virtual void moveDown (const string& childDataName) throw (ClubErreurs);

  // Move data pointer on an element of current data
  // Current data must be a table 
  virtual void moveDown (int index) throw (ClubErreurs);

  // Move data pointer on the mother of current data
  virtual void moveUp   () throw (ClubErreurs);

  // Move data pointer on another data
  virtual void moveTo   (const string& absoluteDataName) throw (ClubErreurs);

 
  // FILE MANAGEMENT

  // Load a file in memory
  virtual void readFile  (const string& fileName) throw (ClubErreurs);

  // Write a file
  virtual void writeFile (const string& fileName) throw (ClubErreurs); 


  // DATA INFORMATION
  
  // Return the type of a child of current data
  virtual DataType getDataType (const string& childDataName) 
    throw (ClubErreurs);

  // Return the type of a child of current data
  virtual DataType getDataType (int index) 
    throw (ClubErreurs);

  // Return the number of elements (only for tables)
  virtual int size () throw (ClubErreurs);

  // Check whether a child data exists
  virtual bool dataExists (const string& childDataName) throw (ClubErreurs);

  // Check whether a child data exists (only for tables)
  virtual bool dataExists (int index) throw (ClubErreurs);

  // Return the comments for a given parameter
  virtual string getComment (const string& childDataName) throw (ClubErreurs);

  // Return the comments for a given element (only for tables)
  virtual string getComment (int index) throw (ClubErreurs);

  // Update comments for a given parameter
  virtual void setComment (const string& childDataName,
                           const string& comment) throw (ClubErreurs);

  // Update comments for a given element (only fror tables)
  virtual void setComment (int index, const string& comment) 
    throw (ClubErreurs);


  // PARAMETER CREATION (not implemented)
  
  // Create a string parameter
  virtual void createStringData (const string& childDataName, 
                                 const string& value) throw (ClubErreurs);
  
  // Create a string parameter (only for tables)
  virtual void createStringData (const string& value) throw (ClubErreurs);

  // Create an integer parameter
  virtual void createIntData (const string& childDataName, int value) 
    throw (ClubErreurs);

  // Create an integer parameter (only for tables)
  virtual void createIntData (int value) throw (ClubErreurs);

  // Create a double parameter
  virtual void createRealData (const string& childDataName, double value,
                               const string& unit) throw (ClubErreurs);

  // Create a double parameter (only for tables)
  virtual void createRealData (double value, const string& unit)
    throw (ClubErreurs);
  
  // Create a table
  virtual void createTable (const string& tableName,
                            UniqDataFile::TableElementType tableType,
                            const string& defaultUnit = "") 
    throw (ClubErreurs);
 
  // Create a table (only for tables)
  virtual void createTable (UniqDataFile::TableElementType tableType,
                            const string& defaultUnit = "") 
    throw (ClubErreurs);

  // Create a structure
  virtual void createStructure (const string& structureName) 
    throw (ClubErreurs);

  // Create a new structure
  virtual void createStructure () throw (ClubErreurs);
  
  // Create a reference
  virtual void createReference (const string& childDataName,
                                const string& referencedFileName,
                                const string& referencedDataName) 
    throw (ClubErreurs);

  // Create a reference (only for tables) 
  virtual void createReference (const string& referencedFileName,
                                const string& referencedDataName) 
    throw (ClubErreurs);


  // PARAMETER READING
  
  // Read a string parameter
  virtual string getStringData (const string& childDataName) 
    throw (ClubErreurs);

  // Read a string parameter (only for tables) 
  virtual string getStringData (int index) throw (ClubErreurs);

  // Read an integer parameter
  virtual int    getIntData    (const string& childDataName) 
    throw (ClubErreurs);

  // Read an integer parameter (only for tables) 
  virtual int    getIntData    (int index) throw (ClubErreurs);

  // Read a real parameter
  virtual double getRealData   (const string& childDataName,
                                const string& unit) throw (ClubErreurs);
 
  // Read a real parameter (only for tables) 
  virtual double getRealData (int index, const string& unit) 
    throw (ClubErreurs);

 
  // PARAMETER UPDATE (not implemented)

  // Update a string parameter
  virtual void setStringData (const string& childDataName, 
                              const string& value) throw (ClubErreurs);

  // Update a string parameter
  virtual void setStringData (int index, const string& value)
    throw (ClubErreurs);

  // Update an integer parameter
  virtual void setIntData (const string& childDataName, int value) 
    throw (ClubErreurs);

  // Update an integer parameter
  virtual void setIntData (int index, int value) throw (ClubErreurs);

  // Update a double parameter
  virtual void setRealData (const string& childDataName, double value,
                            const string& unit) throw (ClubErreurs);

  // Update a double parameter
  virtual void setRealData (int index, double value, const string& unit)
    throw (ClubErreurs);

  
  // DATA DELETION (not implemented)

  // Delete a data
  virtual void deleteData (const string& dataName) throw (ClubErreurs);

  // Delete a data (only for tables)
  virtual void deleteData (int index) throw (ClubErreurs);

 // Write all the memory structure in the standard output.
  virtual void writeMemoryStructure() 
    throw (ClubErreurs);
  
protected  :

  FichierStructure  rootElement_;
  FichierStructure  currentElement_;

  FichierStructure& getRootElement ()
  { return rootElement_; }

  void setRootElement (const FichierStructure& rootElement)
  { rootElement_ = rootElement; }
 
  FichierStructure& getCurrentElement ()
  { return currentElement_; }

  void setCurrentElement (const FichierStructure& currentElement)
  { currentElement_ = currentElement; }


  static UniqDataFile::DataType getFichierStructureType (const FichierStructure& fs);

  // Check if moving up is possible
  virtual bool canMoveUp ();

private :

  // OTHER CONSTRUCTORS
  StructureFile (const StructureFile & other) {}
  StructureFile & operator = (const StructureFile & other)
  {
    return *this;
  }

};

  
#endif


