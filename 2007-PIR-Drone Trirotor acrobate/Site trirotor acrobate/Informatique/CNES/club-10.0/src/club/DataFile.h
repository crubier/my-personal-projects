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
//>       DataFile.h
//
//$Summary
//       Definition file of class DataFile
//
//$Description
//       Declaration module of class DataFile
//
//$Content
//>       class DataFile
//$History
//       $Log: DataFile.h,v $
//       Revision 1.9  2005/02/04 09:59:15  chope
//       élimination des références aux classes DataProxyName et DataProxyIndex (DM-ID 241)
//
//       Revision 1.8  2003/12/05 08:16:38  club
//       DM 0031
//
//       Revision 1.7  2001/02/16 12:30:44  club
//       correction de redéclarations de valeurs par défaut
//       dans la définition de fonctions en ligne
//
//       Revision 1.6  2000/11/09 10:32:55  club
//       Création de fichiers afin d'avoir une classe par fichiers.
//       Cette séparation concerne les classes DataProxy, DataProxyIndex
//       et DataProxyName.
//       Mise à jour des inclusions fichiers par rapport à cette séparation.
//
//       Revision 1.5  2000/10/26 08:27:23  club
//       Protection contre l'auto-assignation dans l'opérateur d'affectation.
//
//       Revision 1.4  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans
//       le nom du fichier inclus.
//
//       Revision 1.3  2000/10/24 14:18:14  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.2  2000/10/18 16:57:46  club
//       ajout de l'implémentation des fonctions inline
//
//       Revision 1.1  2000/10/16 15:36:05  club
//       Initial revision.
//
//$Version
//       $Id: DataFile.h,v 1.9 2005/02/04 09:59:15 chope Exp $
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI 
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_DataFile_h
#define club_DataFile_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <string>

#include "club/ClubErreurs.h"
#include "club/TamponPartage.h"
#include "club/UniqDataFile.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Name
//>       class DataFile
//$Summary
//       DataFile enables to share a UniqDataFile instance.   
//$Description
//       DataFile owns a TamponPartage attribute pointing on a UniqDataFile
//       instance. Each services of DataFile calls the corresponding service
//       of the UniqDataFile instance.
//       DataFile is a canonical form class.
//$Usage
//>     construction : 
//        with the type of file or by copy.
//>     usage :
//>       operator =                         ()
//          equal operator  
//>       UniqDataFile * getUniqDataFile     () 
//          get the shared UniqDataFile
//>       const string getCurrentData        () 
//          return full path to the current data
//>       void moveDown                      () 2 signatures - 
//          move data pointer on a child of current data
//>       void moveUp                        () 
//          move data pointer on the mother of current data
//>       void moveTo                        () 
//          move data pointer on any data 
//>       void readFile                      () 
//          load a file in memory
//>       void writeFile                     () 
//          write a file
//>       UniqDataFile::DataType getDataType () 2 signatures - 
//          return the type of a child of current data
//>       int size                           () 
//          return the number of elements of a table data
//>       bool dataExists                    () 2 signatures - 
//          check whether a data exists
//>       string getComment                  () 2 signatures - 
//          return comments of a data
//>       void setComment                    () 2 signatures - 
//          update or create comment attribute of a data
//>       void createStringData              () 2 signatures - 
//          create a string parameter
//>       void createIntData                 () 2 signatures - 
//          create an integer parameter
//>       void createRealData                () 2 signatures - 
//          create a double parameter
//>       void createTable                   () 2 signatures - 
//          create a table data
//>       void createStructure               () 2 signatures - 
//          create a structure
//>       void createReference               () 2 signatures - 
//          create a reference
//>       string getStringData               () 2 signatures - 
//          read a string parameter
//>       int getIntData                     () 2 signatures - 
//          read an integer parameter
//>       double getRealData                 () 2 signatures - 
//          read a double parameter
//>       void setStringData                 () 2 signatures - 
//          update a string parameter
//>       void setIntData                    () 2 signatures - 
//          update an integer parameter
//>       void setRealData                   () 2 signatures - 
//          update a double parameter
//>       void deleteData                    () 2 signatures - 
//          delete a data and its children
//>       void writeMemoryStructure          ()                   
//          write the memory structure in standard output
//>       FileType  getCurrentFileType       ()                   
//          read the static member currentFileType_
//>       void SetCurrentFileType            ()                   
//          update the static member currentFileType_                          
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI 
//       Copyright (C) CNES 2000
//$<>
///////////////////////////////////////////////////////////////////////////////


// FILE TYPE USED
enum FileType {StructureType, MadonaType, XMLType, UnknownType}; 

class DataFile
{
public :
  
  // CONSTRUCTOR & DESTRUCTOR
 
  // construction by specifying file type to use 
  // (use it for create a file with a specific type)
  DataFile  (FileType type) throw (ClubErreurs);

  // construction by using static member currentFileType_
  // (for a first instanciation of DataFile, the type by default is XML)
  DataFile  () throw (ClubErreurs);

  // construction by checking file type
  // (use it for open an existing file)
  DataFile  (const string& fileName) throw (ClubErreurs);

  // constructor by copy
  DataFile (const DataFile& other) 
    : sharedUniqDataFile_ (other.sharedUniqDataFile_)
  {}

  DataFile& DataFile::operator = (const DataFile& other)
  {
    if (this != &other)
    {
      sharedUniqDataFile_ = other.sharedUniqDataFile_;
    }

    return *this;
  }
  
  // destructor
  ~DataFile ()
  {}

  UniqDataFile* getUniqDataFile();

  
  // DATA POINTER MANAGEMENT

  const string getCurrentData ();

  // move data pointer
  void moveDown (const string& childDataName)    throw (ClubErreurs);
  void moveDown (int index)                      throw (ClubErreurs);
  void moveUp   ()                               throw (ClubErreurs);
  void moveTo   (const string& absoluteDataName) throw (ClubErreurs);

  
  // FILE MANAGEMENT

  // Load a file in memory
  void readFile  (const string& fileName) throw (ClubErreurs);

  // Write a file.
  void writeFile (const string& fileName) throw (ClubErreurs); 


  // DATA INFORMATION
  
  // Return the type of a child of the current data.
  UniqDataFile::DataType getDataType (const string& childDataName) 
    throw (ClubErreurs);

  // Return the type of a child of the current data (only for tables).
  UniqDataFile::DataType getDataType (int index) 
    throw (ClubErreurs);

  // Return the number of elements (only for tables).
  int size () throw (ClubErreurs);

  // Check whether a child data exists
  bool dataExists (const string& childDataName) throw (ClubErreurs);
  bool dataExists (int index)                   throw (ClubErreurs);

  // Return the comments for a given parameter.
  string getComment (const string& childDataName) throw (ClubErreurs);
  string getComment (int index)                   throw (ClubErreurs);

  // Set comments for a given parameter.
  void setComment (const string& childDataName, const string& comment) 
    throw (ClubErreurs);

  void setComment (int index, const string& comment) throw (ClubErreurs);


  // PARAMETER CREATION
  
  // Create a parameter.
  void createStringData (const string& childDataName, const string& value) 
    throw (ClubErreurs);

  void createIntData    (const string& childDataName, int value) 
    throw (ClubErreurs);

  void createRealData   (const string& childDataName, double value, 
                         const string& unit) throw (ClubErreurs);
  
  // Create a parameter (only for tables).
  void createStringData (const string& value)              throw (ClubErreurs);
  void createIntData    (int value)                        throw (ClubErreurs);
  void createRealData   (double value, const string& unit) throw (ClubErreurs);
  
  // Create a table.
  void createTable (const string& tableName,
                    UniqDataFile::TableElementType tableType,
                    const string& defaultUnit = "") throw (ClubErreurs);

  void createTable (UniqDataFile::TableElementType tableType,
                    const string& defaultUnit = "") throw (ClubErreurs);
  
  // Create a structure.
  void createStructure (const string& structureName) throw (ClubErreurs);
  void createStructure ()                            throw (ClubErreurs);
  
  // Create a reference. 
  void createReference (const string& childDataName,
                        const string& referencedFileName,
                        const string& referencedDataName) throw (ClubErreurs);
  
  void createReference (const string& referencedFileName,
                        const string& referencedDataName) throw (ClubErreurs);
  
  
  // DATA READING
  
  // Read a parameter.
  string getStringData (const string& childDataName) throw (ClubErreurs);
  int    getIntData    (const string& childDataName) throw (ClubErreurs);
  double getRealData   (const string& childDataName, const string& unit) 
    throw (ClubErreurs);
 
  
  // Read a parameter (only for tables). 
  string getStringData (int index)                     throw (ClubErreurs);
  int    getIntData    (int index)                     throw (ClubErreurs);
  double getRealData   (int index, const string& unit) throw (ClubErreurs);


  // PARAMETER UPDATE

  // Create ou update a parameter.
  void setStringData (const string& childDataName, const string& value) 
    throw (ClubErreurs);

  void setIntData    (const string& childDataName, int value) 
    throw (ClubErreurs);

  void setRealData   (const string& childDataName, double value, 
                      const string& unit) throw (ClubErreurs);

  // Create or update a string parameter (only for tables).
  void setStringData (int index, const string& value) throw (ClubErreurs);
  void setIntData (int index, int value)              throw (ClubErreurs);
  void setRealData (int index, double value, const string& unit)
    throw (ClubErreurs);
  

  // DATA DELETION

  void deleteData (const string& dataName) throw (ClubErreurs);
  void deleteData (int index)              throw (ClubErreurs);

  // Write the memory structure in standard output.
  void writeMemoryStructure () throw (ClubErreurs);

  // FILE TYPE MANAGEMENT
  const FileType DataFile::getCurrentFileType () throw (ClubErreurs);
  void DataFile::setCurrentFileType (const FileType fileTypeToUse) throw (ClubErreurs);
  void DataFile::deleteDataFile(void *memory);
  const FileType DataFile::getFileType () throw (ClubErreurs);

protected :
  static FileType  currentFileType_;
  FileType         fileType_;
  TamponPartage    sharedUniqDataFile_;
};

 
// DATA POINTER MANAGEMENT

inline const string DataFile::getCurrentData ()
{ return getUniqDataFile ()->getCurrentData (); }

inline void DataFile::moveDown (const string& childDataName) 
  throw (ClubErreurs)
{ getUniqDataFile ()->moveDown (childDataName); }

inline void DataFile::moveDown (int index) throw (ClubErreurs)
{ getUniqDataFile ()->moveDown (index); }

inline void DataFile::moveUp () throw (ClubErreurs)
{ getUniqDataFile ()->moveUp (); }

inline void DataFile::moveTo (const string& absoluteDataName) 
  throw (ClubErreurs)
{ getUniqDataFile ()->moveTo (absoluteDataName); }


// FILE MANAGEMENT

inline void DataFile::readFile (const string& fileName) throw (ClubErreurs)
{ getUniqDataFile ()->readFile (fileName); }

inline void DataFile::writeFile (const string& fileName) throw (ClubErreurs)
{ getUniqDataFile ()->writeFile (fileName); }


// DATA INFORMATION
  
inline UniqDataFile::DataType DataFile::getDataType (const string& childDataName) 
  throw (ClubErreurs)
{ return getUniqDataFile ()->getDataType (childDataName); }

inline UniqDataFile::DataType DataFile::getDataType (int index) 
  throw (ClubErreurs)
{ return getUniqDataFile ()->getDataType (index); }

inline int DataFile::size () throw (ClubErreurs)
{ return getUniqDataFile ()->size (); }

inline bool DataFile::dataExists (const string& childDataName) 
  throw (ClubErreurs)
{ return getUniqDataFile ()->dataExists (childDataName); }

inline bool DataFile::dataExists (int index) throw (ClubErreurs)
{ return getUniqDataFile ()->dataExists (index); }

inline string DataFile::getComment (const string& childDataName) 
  throw (ClubErreurs)
{ return getUniqDataFile ()->getComment (childDataName); }

inline string DataFile::getComment (int index) throw (ClubErreurs)
{ return getUniqDataFile ()->getComment (index); }

inline void DataFile::setComment (const string& childDataName,
                                  const string& comment) throw (ClubErreurs)
{ getUniqDataFile ()->setComment (childDataName, comment); }

inline void DataFile::setComment (int index, const string& comment) 
  throw (ClubErreurs)
{ getUniqDataFile ()->setComment (index, comment); }

// PARAMETER CREATION
  
inline void DataFile::createStringData (const string& childDataName, 
                                        const string& value) 
  throw (ClubErreurs)
{ getUniqDataFile ()->createStringData (childDataName, value); }

inline void DataFile::createIntData (const string& childDataName, int value) 
  throw (ClubErreurs)
{ getUniqDataFile ()->createIntData (childDataName, value); }

inline void DataFile::createRealData (const string& childDataName, double value, 
                                      const string& unit) throw (ClubErreurs)
{ getUniqDataFile ()->createRealData (childDataName, value, unit); }
  
inline void DataFile::createStringData (const string& value) 
  throw (ClubErreurs)
{ getUniqDataFile ()->createStringData (value); }

inline void DataFile::createIntData (int value) throw (ClubErreurs)
{ getUniqDataFile ()->createIntData (value); }

inline void DataFile::createRealData (double value, const string& unit)
  throw (ClubErreurs)
{ getUniqDataFile ()->createRealData (value, unit); }
  
inline void DataFile::createTable (const string& tableName,
                                   UniqDataFile::TableElementType tableType,
                                   const string& defaultUnit) 
  throw (ClubErreurs)
{ getUniqDataFile ()->createTable (tableName, tableType, defaultUnit); }

inline void DataFile::createTable (UniqDataFile::TableElementType tableType,
                                   const string& defaultUnit) 
  throw (ClubErreurs)
{ getUniqDataFile ()->createTable (tableType, defaultUnit); }

inline void DataFile::createStructure (const string& structureName) 
  throw (ClubErreurs)
{ getUniqDataFile ()->createStructure (structureName); }

inline void DataFile::createStructure () throw (ClubErreurs)
{ getUniqDataFile ()->createStructure (); }
  
inline void DataFile::createReference (const string& childDataName,
                                       const string& referencedFileName,
                                       const string& referencedDataName) 
  throw (ClubErreurs)
{ 
  getUniqDataFile ()->createReference (childDataName, referencedFileName,
                                       referencedDataName); 
}

inline void DataFile::createReference (const string& referencedFileName,
                                       const string& referencedDataName) 
  throw (ClubErreurs)
{ 
  getUniqDataFile ()->createReference (referencedFileName, referencedDataName);
}


// PARAMETER READING
  
inline double DataFile::getRealData (const string& childDataName,
                                     const string& unit) throw (ClubErreurs)
{ return getUniqDataFile ()->getRealData (childDataName, unit); }

inline int DataFile::getIntData (const string& childDataName) 
  throw (ClubErreurs)
{ return getUniqDataFile ()->getIntData (childDataName); }

inline string DataFile::getStringData (const string& childDataName) 
  throw (ClubErreurs)
{ return getUniqDataFile ()->getStringData (childDataName); }
 
inline double DataFile::getRealData (int index, const string& unit) 
  throw (ClubErreurs)
{ return getUniqDataFile ()->getRealData (index, unit); }

inline int DataFile::getIntData (int index) throw (ClubErreurs)
{ return getUniqDataFile ()->getIntData (index); }

inline string DataFile::getStringData (int index) throw (ClubErreurs)
{ return getUniqDataFile ()->getStringData (index); }

   
// PARAMETER UPDATE

inline void DataFile::setStringData (const string& childDataName, 
                                     const string& value) throw (ClubErreurs)
{ getUniqDataFile ()->setStringData (childDataName, value); }

inline void DataFile::setIntData (const string& childDataName, int value) 
  throw (ClubErreurs)
{ getUniqDataFile ()->setIntData (childDataName, value); }

inline void DataFile::setRealData (const string& childDataName, double value, 
                                   const string& unit) throw (ClubErreurs)
{ getUniqDataFile ()->setRealData (childDataName, value, unit); }

inline void DataFile::setStringData (int index, const string& value) 
  throw (ClubErreurs)
{ getUniqDataFile ()->setStringData (index, value); }

inline void DataFile::setIntData (int index, int value) throw (ClubErreurs)
{ getUniqDataFile ()->setIntData (index, value); }

inline void DataFile::setRealData (int index, double value, const string& unit)
  throw (ClubErreurs)
{ getUniqDataFile ()->setRealData (index, value, unit); }

inline void DataFile::writeMemoryStructure ()
  throw (ClubErreurs)
{ getUniqDataFile ()->writeMemoryStructure (); }

  
// DATA DELETION

inline void DataFile::deleteData (const string& dataName) throw (ClubErreurs)
{ getUniqDataFile ()->deleteData (dataName); }

inline void DataFile::deleteData (int index) throw (ClubErreurs)
{ getUniqDataFile ()->deleteData (index); }
 
#endif


