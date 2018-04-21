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
//>       UniqDataFile.h
//
//$Summary
//       Definition file of class UniqDataFile
//
//$Description
//       Declaration module of class UniqDataFile
//
//$Content
//>       class UniqDataFile
//$History
//       $Log: UniqDataFile.h,v $
//       Revision 1.9  2005/02/04 09:55:13  chope
//       élimination des méthodes stringToDouble et stringToInt (DM-ID 242)
//
//       Revision 1.8  2002/12/09 15:59:26  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec
//       la norme qualité
//
//       Revision 1.7  2001/03/22 11:47:48  club
//       removed an exception throw specification
//
//       Revision 1.6  2000/11/10 15:24:51  club
//       élimination de replaceCharacter
//
//       Revision 1.5  2000/11/09 10:32:55  club
//       Création de fichiers afin d'avoir une classe par fichiers.
//       Cette séparation concerne les classes DataProxy, DataProxyIndex
//       et DataProxyName.
//       Mise à jour des inclusions fichiers par rapport à cette séparation.
//
//       Revision 1.4  2000/10/25 09:31:44  club
//       modification des include du standard C++ : suppression de ".h" dans
//       le nom du fichier inclus.
//
//       Revision 1.3  2000/10/24 14:18:15  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.2  2000/10/17 14:08:29  club
//       suppression de la méthode obsolète testIndexAlreadyDefined.
//       Le constructeur ne lève plus d'exception.
//
//       Revision 1.1  2000/10/16 15:36:05  club
//       Initial revision.
//
//$Version
//       $Id: UniqDataFile.h,v 1.9 2005/02/04 09:55:13 chope Exp $
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI 
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_UniqDataFile_h
#define club_UniqDataFile_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <string>

#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Name
//>       class UniqDataFile
//$Summary
//        UniqDataFile define all generic services for accessing files.
//$Description
//        UniqDataFile is abstract and the base class for StructureFile, 
//        MadonaFile and XMLFile.
//        
//        UniqDataFile defines services for :
//          - reading and writing files
//          - creating data (int, double, string parameter, reference, table
//            and structure)
//          - updating terminal parameters (int, double and string)
//          - reading data
//          - deleting data
//          - handling units
//          - moving into the memory structure
//           
//        UniqDataFile only manages names of data.
//        
//$Usage
//>     construction :
//        with no argument.
//>     usage :
//>       ~UniqDataFile                              ()
//          destructor
//>       virtual string getCurrentData              () 
//          return full path to current data
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
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI 
//       Copyright (C) CNES 2000
//$<>
///////////////////////////////////////////////////////////////////////////////

class UniqDataFile  
{

public :
  
  enum DataType {ParameterType, StructureType, TableType, 
                 ReferenceType, UndeterminedType};

  enum TableElementType {IntTable, RealTable, StringTable, 
                         StructureTable, TableTable};

  // CONSTRUCTOR & DESTRUCTOR
  
  // Build a new UniqDataFile by initializing current data
  UniqDataFile ();

  // Destruct a UniqDataFile instance
  virtual ~UniqDataFile ();


  // DATA POINTER MANAGEMENT

  // Return the absolute name of current data
  string getCurrentData ();

  // Move data pointer on a child of current data
  virtual void moveDown (const string& childDataName) throw (ClubErreurs);

  // Move data pointer on a element of current data 
  // Current data must be a table 
  virtual void moveDown (int index) throw (ClubErreurs);

  // Move data pointer on the mother of current data
  virtual void moveUp   () throw (ClubErreurs);

  // Move data pointer on another data
  virtual void moveTo   (const string& absoluteDataName) throw (ClubErreurs);
  

  // FILE MANAGEMENT

  // Load a file in memory
  virtual void readFile  (const string& fileName) throw (ClubErreurs) = 0;

  // Write a file
  virtual void writeFile (const string& fileName) throw (ClubErreurs) = 0; 


  // DATA INFORMATION
  
  //Return the type of a child of current data
  virtual DataType getDataType (const string& childDataName) 
    throw (ClubErreurs) = 0;

  //Return the type of a child of current data (only for tables).
  virtual DataType getDataType (int index) 
    throw (ClubErreurs) = 0;

  // Return the number of elements (only for tables)
  virtual int size () throw (ClubErreurs) = 0;

  // Check whether a data exists
  virtual bool dataExists (const string& childDataName) throw (ClubErreurs) = 0;

  // Check whether a data exists (only for tables)
  virtual bool dataExists (int index) throw (ClubErreurs) = 0;

  // Return the comments for a given parameter
  virtual string getComment (const string& childDataName) 
    throw (ClubErreurs) = 0;

  // Return the comments for a given element (only for tables)
  virtual string getComment (int index) 
    throw (ClubErreurs) = 0;

  // Update comments for a given parameter
  virtual void setComment (const string& childDataName,
                           const string& comment) throw (ClubErreurs) = 0;

  // Update comments for a given element (only for table)
  virtual void setComment (int index, const string& comment) 
    throw (ClubErreurs) = 0;


  // PARAMETER CREATION
  
  // Create a string parameter
  virtual void createStringData (const string& childDataName, 
                                 const string& value) throw (ClubErreurs) = 0;
  
  // Create a string parameter (only for tables)
  virtual void createStringData (const string& value) throw (ClubErreurs) = 0;

  // Create an integer parameter
  virtual void createIntData (const string& childDataName, int value) 
    throw (ClubErreurs) = 0;

  // Create an integer parameter (only for tables)
  virtual void createIntData (int value) throw (ClubErreurs) = 0;

  // Create a double parameter
  virtual void createRealData (const string& childDataName, double value, 
                               const string& unit) throw (ClubErreurs) = 0;

  // Create a double parameter (only for tables)
  virtual void createRealData (double value, const string& unit)
    throw (ClubErreurs) = 0;
  
  // Create a table
  virtual void createTable (const string& tableName,
                            TableElementType tableType,
                            const string& defaultUnit = "") 
    throw (ClubErreurs) = 0;

  // Create a table (only for tables)
  virtual void createTable (TableElementType tableType,
                            const string& defaultUnit = "") 
    throw (ClubErreurs) = 0;

  // Create a structure
  virtual void createStructure (const string& structureName) 
    throw (ClubErreurs) = 0;

  // Create a structure (only for tables)
  virtual void createStructure () throw (ClubErreurs) = 0;
  
  // Create a reference 
  virtual void createReference (const string& childDataName,
                                const string& referencedFileName,
                                const string& referencedDataName) 
    throw (ClubErreurs) = 0;

  // Create a reference 
  virtual void createReference (const string& referencedFileName,
                                const string& referencedDataName) 
    throw (ClubErreurs) = 0;


  // PARAMETER READING
  
  // Read a string parameter
  virtual string getStringData (const string& childDataName) 
    throw (ClubErreurs) = 0;

  // Read a string parameter (only for tables) 
  virtual string getStringData (int index) throw (ClubErreurs) = 0;

  // Read an integer parameter
  virtual int    getIntData    (const string& childDataName) 
    throw (ClubErreurs) = 0;

  // Read an integer parameter (only for tables) 
  virtual int    getIntData    (int index) throw (ClubErreurs) = 0;

  // Read a real parameter
  virtual double getRealData   (const string& childDataName,
                                const string& unit) throw (ClubErreurs) = 0;
 
  // Read a real parameter (only for tables) 
  virtual double getRealData   (int index, const string& unit) 
    throw (ClubErreurs) = 0;


  // PARAMETER UPDATE

  // Create a string parameter
  virtual void setStringData (const string& childDataName, 
                              const string& value) throw (ClubErreurs) = 0;

  // Create an integer parameter
  virtual void setIntData (const string& childDataName, int value) 
    throw (ClubErreurs) = 0;

  // Create a double parameter
  virtual void setRealData (const string& childDataName, double value, 
                            const string& unit) throw (ClubErreurs) = 0;

  // Create a string parameter
  virtual void setStringData (int index, const string& value)
    throw (ClubErreurs) = 0;

  // Create an integer parameter
  virtual void setIntData (int index, int value) throw (ClubErreurs) = 0;

  // Create a double parameter
  virtual void setRealData (int index, double value, const string& unit)
    throw (ClubErreurs) = 0;
  

  // DATA DELETION

  // Delete a data
  virtual void deleteData (const string& dataName) throw (ClubErreurs) = 0;

  // Delete a data (only for tables)
  virtual void deleteData (int index) throw (ClubErreurs) = 0;

 // Write all the memory structure in the standard output.
  virtual void writeMemoryStructure() 
    throw (ClubErreurs) = 0;

 
  
protected  :

  // MANAGEMENT OF THE NAME OF THE DATA POINTER

  // The name of current data
  string currentData_;

  // Update the name of current data
  void setCurrentData (const string& currentData);

  // Return the absolute name of a data according to the current data name
  string getAbsoluteDataName (const string& childDataName);

  // Return the absolute name of a data according to the current data name
  string getAbsoluteDataName (int index);
 

  // EXCEPTIONS MANAGEMENT

  // Throw ClubErreur::current_data_is_a_table if the current data
  // is a table
  virtual void testCurrentDataIsATable () throw (ClubErreurs);

  // Throw ClubErreur::current_data_not_a_table if the current data is
  // not a table.
  virtual void testCurrentDataNotATable () throw (ClubErreurs);

  // Throw ClubErreur::undefined_table_or_structure if the given data
  // does not define a table or a structure
  void testUndefinedStructureOrTable (const string& childDataName) 
    throw (ClubErreurs);

  // Throw ClubErreur::undefined_parameter if the given 
  // parameter does not exist
  void testUndefinedParameter (const string& childDataName) 
    throw (ClubErreurs);
  
  // Throw ClubErreur::undefined_index if the given index does not exist
  // The current data must be a table
  void testUndefinedIndex (int index) throw (ClubErreurs);

  // Throw ClubErreur::undefined_data if the given data does not exist 
  void testUndefinedData (const string& childDataName) throw (ClubErreurs);

  // Throw ClubErreur::move_up_forbidden if moving up is not possible
  void testMoveUpForbidden () throw (ClubErreurs);

  // Throw ClubErreurs::already_defined_data exception is the given data 
  // already exists
  void testDataAlreadyDefined (const string& childDataName) 
    throw (ClubErreurs);

  // Check if moving up is possible
  virtual bool canMoveUp () = 0;

private :
  // OTHER CONSTRUCTORS
  UniqDataFile (const UniqDataFile & other) {}
  UniqDataFile & operator = (const UniqDataFile & other)
  {
    return *this;
  }

};


// STRING MANAGEMENT

// Convert an integer value into a string 
string intToString (int i);

// Convert a double value into a string
string doubleToString (double d);
  

//DATA NAMES MANAGEMENT

// Return the first data name (on the left side) of a complete data name
string getFirstElementName (const string& dataName) throw (ClubErreurs);

// Return the parent data name of a complete data name
string getParentName       (const string& dataName);

// Return the relative data (on the right side) name of a complete data name
string getLastChildName    (const string& dataName);

// Return the next token and the "rest" of a data name  
bool hasMoreSubDataNames   (const string& dataName, string* subDataName);

//-----------------------------------------------------------------------------
// bool isDataNameAnIndex (const string& dataName)
// Check if dataName is an index name (check for presence of '[' in 
// first position and ']' in last position)
// In 
//     dataName : a data name
// Out
//     true if dataName is an index name.
//-----------------------------------------------------------------------------

inline bool isDataNameAnIndex (const string& dataName)
{
  return (dataName [0] == '[') && (dataName [dataName.size ()-1] == ']');
}

//-----------------------------------------------------------------------------
// int getIndexValue (const string& dataName) 
// if dataName is an index name, return the value of index
// In
//     dataName : a data name
// Out
//     value of index if dataName is an index name
// Eception
//     string_to_int_conversion_error if dataName is not an index name
//-----------------------------------------------------------------------------

inline int getIndexValue (const string& dataName) throw (ClubErreurs)
{
  return atoi (dataName.substr (1, dataName.size ()-2).c_str ());
}

#endif


