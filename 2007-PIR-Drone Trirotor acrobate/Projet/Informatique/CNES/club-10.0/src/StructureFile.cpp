////////////////////////////////////////////////////////////////////////////////
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
//>       StructureFile.cpp
//
//$Summary
//       file implementing functions of class StructureFile
//
//$Description
//       Definition module of class StructureFile
//
//$Content
//>       class StructureFile 
//>         canMoveUp()       
//>         size()    
//>         getDataType()   
//>         dataExists()      
//>         readFile()        
//>         moveDown()        
//>         moveUp()          
//>         moveTo()          
//>         getStringData()   
//>         getRealData()     
//>         getIntData()      
//>         getComment()      
//>         setComment()      
//>         writeFile()       
//>         createStringData()
//>         createIntData()   
//>         createRealData()  
//>         createTable()     
//>         createStructure() 
//>         createReference() 
//>         setStringData()   
//>         setIntData()      
//>         setRealData()     
//>         deleteData() 
//>         writeMemoryStructure()   
//$History
//       $Log: StructureFile.cpp,v $
//       Revision 1.7  2005/02/04 10:08:24  chope
//       élimination de la méthode loadUnitFile (DM-ID 242)
//
//       Revision 1.6  2003/02/03 13:48:07  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.5  2001/03/13 14:06:41  club
//       corrected a return statement in a void function
//
//       Revision 1.4  2001/02/16 12:43:34  club
//       correction de redéclarations de valeurs par défaut
//       dans la définition de fonctions en ligne
//
//       Revision 1.3  2000/11/10 15:28:16  club
//       élimination de replaceCharacter qui transforme les '.' en ','
//
//       Revision 1.2  2000/10/24 14:21:01  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 1.1  2000/10/16 15:43:51  club
//       Initial revision.
//
//$Version
//       $Id: StructureFile.cpp,v 1.7 2005/02/04 10:08:24 chope Exp $
//
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI
//       Copyright (C) CNES 2000
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_STL
#include <string>
#endif

#include "club/ClubErreurs.h"
#include "club/StructureFile.h"


//-----------------------------------------------------------------------------
// bool StructureFile::canMoveUp ()
// Check if moving up is allowed
// Out
//      true if parent name of currentElement equals name of root element ,
//      false otherwise
//-----------------------------------------------------------------------------

bool StructureFile::canMoveUp ()
{
  return getCurrentElement ().nomBloc () != getRootElement ().nomBloc ();
}
 
//-----------------------------------------------------------------------------
// int StructureFile::size ()
// Returns the number of children of current data (current data must be a table
// Out
//      number of children of current data
// Exception
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

int StructureFile::size () throw (ClubErreurs)
{
  // Check if current data is a table.
  if (getFichierStructureType (getCurrentElement ()) != TableType)
    throw ClubErreurs (ClubErreurs::current_data_not_a_table,
                       getCurrentData ().c_str ());
  return getCurrentElement ().nombreChamps ();
}

//-----------------------------------------------------------------------------
// UniqDataFile::DataType StructureFile::getFichierStructureType (const FichierStructure& fs)
// Returns the type of data named childDataName
// In
//      fs : a FichierStructure instance.
// Out
//      type of element (value of enum UniqDataFile::DataType)
//-----------------------------------------------------------------------------

UniqDataFile::DataType StructureFile::getFichierStructureType (const FichierStructure& fs)
{
  UniqDataFile::DataType result;

  if (fs.terminal ())
    result = TableType;
  else 
    result = StructureType;

  return result;
}

//-----------------------------------------------------------------------------
// UniqDataFile::DataType StructureFile::getDataType (const string& childDataName)
// Returns the type of data named childDataName
// In
//      childDataName : name of data.
// Out
//      type of element (value of enum UniqDataFile::DataType)
// Exception
//       ClubErreurs::undefined_parameter
//       ClubErreurs::undefined_index
//       ClubErreurs::undefined_table_or_structure
//       ClubErreurs::string_to_int_conversion
//       ClubErreurs::bloc_introuvable
//       ClubErreurs::manque_accolade
//-----------------------------------------------------------------------------

UniqDataFile::DataType StructureFile::getDataType (const string& childDataName)
  throw (ClubErreurs)
{  
  if (getFichierStructureType (getCurrentElement ()) == TableType)
  {
    if (! isDataNameAnIndex (childDataName))
      throw ClubErreurs (ClubErreurs::undefined_parameter,
                         getAbsoluteDataName (childDataName).c_str ());
    else
    {
      int index = getIndexValue (childDataName);
      return getDataType (index);
    }
  }
  else
  {         
    string toFind;
    // check if data exists
    if (isDataNameAnIndex (childDataName))
      toFind = intToString( getIndexValue (childDataName));
    else
      toFind = childDataName;

    if (dataExists (toFind))
    {
      FichierStructure fs (toFind.c_str (), &getCurrentElement ());
      return getFichierStructureType (fs);
    } 
    else
      throw ClubErreurs (ClubErreurs::undefined_table_or_structure, 
                         getAbsoluteDataName (toFind).c_str ());
  }
}

//-----------------------------------------------------------------------------
// UniqDataFile::DataType StructureFile::getDataType (int index)
// Returns the type of data named childDataName. 
// In
//      index : index of the element in the table.
// Out
//      type of element (value of enum UniqDataFile::DataType)
// Exception
//       ClubErreurs::undefined_index if data does not exist
//       ClubErreurs::undefined_table_or_structure
//       ClubErreurs::undefined_parameter
//       ClubErreurs::bloc_introuvable
//       ClubErreurs::manque_accolade
//-----------------------------------------------------------------------------

UniqDataFile::DataType StructureFile::getDataType (int index)
  throw (ClubErreurs)
{
  if (getFichierStructureType (getCurrentElement ()) == TableType)
  {
    if ( index <= 0 || index > size ())
      throw ClubErreurs (ClubErreurs::undefined_index, index,
                         getCurrentData ().c_str ());
    return ParameterType;
  }
  else
  {
    string indexstr = intToString (index);
    return getDataType (indexstr);
  }
}


//-----------------------------------------------------------------------------
// bool StructureFile::dataExists (const string& childDataName)
// Checks whether childDataName exists
// In
//      childDataName : name of child
// out
//      true if childDataName exists, false otherwise
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::string_to_int_conversion_error
//      ClubErreurs::manque_accolade 
//-----------------------------------------------------------------------------

bool StructureFile::dataExists (const string& childDataName) 
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    int index = getIndexValue (childDataName);
    return dataExists (index);
  }
  else
    return getCurrentElement ().contientSousBloc (childDataName.c_str ());
}


//-----------------------------------------------------------------------------
// bool StructureFile::dataExists (int index)
// Checks whether data whose index attribute is "index" exists. Current data
// must be a table
// In
//      index : value of index attribute
// out
//      true if child exists, false otherwise
// Exceptions
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::manque_accolade 
//-----------------------------------------------------------------------------

bool StructureFile::dataExists (int index) throw (ClubErreurs)
{  
  if (getFichierStructureType (getCurrentElement ()) == TableType)
    return (index > 0 && index < size ());
  else
  {
    string indexStr = intToString (index);
    return dataExists (indexStr);
  }
}


//-----------------------------------------------------------------------------
// void StructureFile::readFile (const string& fileName)
// Load a file in memory
// In
//      fileName : name of file to load.
// Exception
//      ClubErreurs::accolades_non_equilibrees
//      ClubErreurs::etat_fichier
//      ClubErreurs::manque_guillemet
//      ClubErreurs::manque_chevron
//      ClubErreurs::iterateur_invalid
//      ClubErreurs::caractere_hors_domaine
//      ClubErreurs::nom_inclusion
//-----------------------------------------------------------------------------

void StructureFile::readFile (const string& fileName) throw (ClubErreurs)
{
  FichierStructure fs (fileName);
  setRootElement (fs);
  setCurrentElement (fs);
}

//-----------------------------------------------------------------------------
// void StructureFile::moveDown (const string& relativeDataName)
// Move to child (of current data) named relativeDataName 
// In
//      relativeDataName : relative data name of child to move to.
// Exception
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::undefined_table_or_structure
//      ClubErreurs::bloc_introuvable
//      ClubErreurs::manque_accolade
//-----------------------------------------------------------------------------

void StructureFile::moveDown (const string& childDataName) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    int index = getIndexValue (childDataName);
    moveDown (index);
  }
  else
  {
    // check if childDataName exists and is a table or a structure
    testUndefinedStructureOrTable (childDataName);
    
    // create a new FichierStructure
    FichierStructure fs (childDataName.c_str (), &getCurrentElement ());
    setCurrentElement (fs);

    UniqDataFile::moveDown (childDataName);
  }
}

//-----------------------------------------------------------------------------
// void StructureFile::moveDown (int index)
// Move to child (of current data) whose index is "index". The current data
// must be a table.
// In
//      index : index of child data (first value is "1")
// Exception
//      ClubErreurs::undefined_table_or_structure
//      ClubErreurs::bloc_introuvable
//      ClubErreurs::manque_accolade
//-----------------------------------------------------------------------------
void StructureFile::moveDown (int index) throw (ClubErreurs)
{
  string indexStr = intToString (index);

  if (! getCurrentElement ().contientSousBloc (indexStr.c_str ()))
  {
    throw ClubErreurs (ClubErreurs::undefined_table_or_structure,  
                       getAbsoluteDataName (indexStr).c_str ());
  }

  // create a new FichierStructure
  FichierStructure fs (indexStr, &getCurrentElement ());
  setCurrentElement (fs);

  UniqDataFile::moveDown (index);
}

//-----------------------------------------------------------------------------
// void StructureFile::moveUp ()
// Move to parent node of current data
// Exception
//      ClubErreurs::move_up_forbidden
//      ClubErreurs::undefined_table_or_structure
//      ClubErreurs::int_to_string_conversion
//      ClubErreurs::bloc_introuvable
//      ClubErreurs::manque_accolade
//-----------------------------------------------------------------------------

void StructureFile::moveUp () throw (ClubErreurs)
{
  // check if moving up is allowed
  testMoveUpForbidden ();

  string parentName = getParentName (getCurrentData ());
  moveTo (parentName);
}

//-----------------------------------------------------------------------------
// void StructureFile::moveTo (const string& absoluteDataName)
// Move data pointer on any data. 
// In
//      absoluteDataName : absolute data name of data
// Exceptions
//      ClubErreurs::undefined_table_or_structure
//      ClubErreurs::int_to_string_conversion
//      ClubErreurs::bloc_introuvable
//      ClubErreurs::manque_accolade
//-----------------------------------------------------------------------------

void StructureFile::moveTo (const string& absoluteDataName) throw (ClubErreurs)
{
  setCurrentElement (getRootElement ());
  setCurrentData ("");
  string dataName = absoluteDataName;
  string rest;

  while (hasMoreSubDataNames (dataName, &rest))
  {
    moveDown (getFirstElementName (dataName));
    dataName = rest;
  }  
}

//-----------------------------------------------------------------------------
// string StructureFile::getStringData (const string& childDataName)
// Reads the string attribute of data named childDataName
// In
//      childDataName : name of child
// Out
//      value of data
// Exception
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::undefined_parameter if data  does not exist
//      ClubErreurs::bloc_champ_inexistant
//      ClubErreurs::bloc_non_terminal
//-----------------------------------------------------------------------------

string StructureFile::getStringData (const string& childDataName) 
  throw (ClubErreurs)
{
 if (isDataNameAnIndex (childDataName))
 {
   int index = getIndexValue (childDataName);
   return getStringData (index);
 } 
 else
   throw ClubErreurs (ClubErreurs::undefined_parameter, 
                      getAbsoluteDataName (childDataName).c_str ()); 
}

//-----------------------------------------------------------------------------
// string StructureFile::getStringData (int index)
// Reads the string attribute of data whose index attribute is "index". Current
// data must be a table. 
// In
//      index : value of index attribute 
// Out
//      value of data
// Exceptions
//      ClubErreurs::bloc_champ_inexistant
//      ClubErreurs::bloc_non_terminal
//-----------------------------------------------------------------------------

string StructureFile::getStringData (int index) throw (ClubErreurs)
{
  char buffer [1000];
  getCurrentElement ().champ (index, buffer, 1000);      
  return (string) buffer;
}

//-----------------------------------------------------------------------------
// double StructureFile::getRealData (const string& childDataName,
//                              const string& unit)
// Reads the real attribute of data named childDataName
// In
//      childDataName : name of child
//      unit : physical unit for value to return
// Out
//      value of data
// Exception
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::string_to_double_conversion
//      ClubErreurs::undefined_parameter 
//      ClubErreurs::bloc_champ_inexistant
//      ClubErreurs::bloc_non_terminal
//-----------------------------------------------------------------------------

double StructureFile::getRealData(const string& childDataName,
                                  const string& unit) throw (ClubErreurs)
{
 if (isDataNameAnIndex (childDataName))
 {
   int index = getIndexValue (childDataName);
   return getRealData (index, unit);
 } 
 else
   throw ClubErreurs (ClubErreurs::undefined_parameter, 
                      getAbsoluteDataName (childDataName).c_str ()); 
}
//-----------------------------------------------------------------------------
// double StructureFile::getRealData (int index, const string& unit)
// Reads the real attribute of data whose index attribute is "index". Current
// data must be a table. 
// In
//      index : value of index attribute 
//      unit  : physical unit for value to return
// Out
//      value of data
// Exception
//      ClubErreurs::string_to_double_conversion
//      ClubErreurs::bloc_champ_inexistant
//      ClubErreurs::bloc_non_terminal
//-----------------------------------------------------------------------------

double StructureFile::getRealData (int index, const string& unit) 
  throw (ClubErreurs)
{
  char buffer [1000];
  getCurrentElement ().champ (index, buffer, 1000);      
  string valueStr (buffer);
  return atof(valueStr.c_str());
}


//-----------------------------------------------------------------------------
// int StructureFile::getIntData (const string& childDataName)
// Reads the int attribute of data named childDataName
// In
//      childDataName : name of child
// Out
//      value of data
// Exception
//      ClubErreurs::undefined_parameter if data does not exist
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::bloc_champ_inexistant
//      ClubErreurs::bloc_non_terminal
//-----------------------------------------------------------------------------

int StructureFile::getIntData (const string& childDataName) 
  throw (ClubErreurs)
{
 if (isDataNameAnIndex (childDataName))
 {
   int index = getIndexValue (childDataName);
   return getIntData (index);
 } 
 else
   throw ClubErreurs (ClubErreurs::undefined_parameter, 
                      getAbsoluteDataName (childDataName).c_str ()); 
}

//-----------------------------------------------------------------------------
// int StructureFile::getIntData (int index)
// Reads the int attribute of data whose index attribute is "index". 
// Current data must be a table. 
// In
//      index : value of index attribute 
// Out
//      value of data
// Exception
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::bloc_champ_inexistant
//      ClubErreurs::bloc_non_terminal
//-----------------------------------------------------------------------------

int StructureFile::getIntData (int index) throw (ClubErreurs)
{
  char buffer [1000];
  getCurrentElement ().champ (index, buffer, 1000);      
  string valueStr (buffer);
  return atoi (valueStr.c_str ());
}   

//-----------------------------------------------------------------------------
// string StructureFile::getComment (const string& childDataName)
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

string StructureFile::getComment (const string& childDataName)
  throw (ClubErreurs)
{
 throw ClubErreurs (ClubErreurs::not_implemented, 
                    "StructureFile::getComment (const string& childDataName)");
}

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

string StructureFile::getComment (int index) throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::getComment (int index)");
}

//-----------------------------------------------------------------------------
// StructureFile::setComment (const string& childDataName,
//                            const string& comment)// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::setComment (const string& childDataName,
                                const string& comment) throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::setComment (const string& childDataName, "
                     "const string& comment");
}

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::setComment (int index, const string& comment) 
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::setComment (int index, const string& "
                     "comment");
}

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::writeFile (const string& fileName) throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::writeFile (const string& fileName)");
} 

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createStringData (const string& childDataName, 
                                      const string& value) throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createStringData (const string& "
                     "childDataName, const string& value)");
}

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createIntData (const string& childDataName, int value) 
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createIntData (const string& "
                     "childDataName, int value)");
}

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createRealData (const string& childDataName, double value,
                                    const string& unit) throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createRealData (const string& "
                     "childDataName, double value, const string& unit)");
}
 
//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createStringData (const string& value) throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createStringData (const string& value)");
}

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createIntData (int value) 
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createIntData (int value)");
}


void StructureFile::createRealData (double value, const string& unit)
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented,
                     "StructureFile::createRealData (double value, "
                     "const string& unit)");
}
  
//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createTable (const string& tableName,
                                 UniqDataFile::TableElementType tableType,
                                 const string& defaultUnit) 
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createTable (const string& tableName, "
                     "UniqDataFile::TableElementType tableType, "
                     "const string& defaultUnit)");
}

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createTable (UniqDataFile::TableElementType tableType,
                                 const string& defaultUnit) 
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createTable (UniqDataFile::TableElementType "
                     "tableType, const string& defaultUnit)");
}

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createStructure (const string& structureName) 
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createStructure (const string& "
                     "structureName)");
}

//-----------------------------------------------------------------------------
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createStructure () throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createStructure ()");
}
 
//-----------------------------------------------------------------------------
// void StructureFile::createReference (const string& childDataName,
//                                     const string& referencedFileName,
//                                     const string& referencedDataName) 
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createReference (const string& childDataName,
                                     const string& referencedFileName,
                                     const string& referencedDataName) 
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createReference (const string& "
                     "childDataName, const string& referencedFileName, "
                     "const string& referencedDataName)");
}

//-----------------------------------------------------------------------------
// StructureFile::createReference (const string& referencedFileName,
//                                 const string& referencedDataName)
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::createReference (const string& referencedFileName,
                                     const string& referencedDataName) 
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::createReference (const string& "
                     "referencedFileName, const string& referencedDataName)");
}

//-----------------------------------------------------------------------------
// StructureFile::setStringData (const string& childDataName, 
//                               const string& value)
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------
  
void StructureFile::setStringData (const string& childDataName, 
                                   const string& value) throw (ClubErreurs) 
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "setStringData (const string& childDataName, "
                     "const string& value)");
}

//-----------------------------------------------------------------------------
// StructureFile::setIntData (const string& childDataName, int value) 
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::setIntData (const string& childDataName, int value) 
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::setIntData (const string& childDataName, "
                     "int value)");
}

//-----------------------------------------------------------------------------
// StructureFile::setRealData (const string& childDataName, double value,
//                             const string& unit) 
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::setRealData (const string& childDataName, double value,
                                 const string& unit) throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::setRealData (const string& childDataName,"
                     " double value, const string& unit)");
}

//-----------------------------------------------------------------------------
// StructureFile::setStringData (int index, const string& value)
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::setStringData (int index, const string& value)
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::setStringData (int index, "
                     "const string& value)");
}

//-----------------------------------------------------------------------------
// StructureFile::setIntData (int index, int value)
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::setIntData (int index, int value) throw (ClubErreurs) 
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::setIntData (int index, int value)");
}

//-----------------------------------------------------------------------------
// StructureFile::setRealData (int index, double value, const string& unit)
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::setRealData (int index, double value, const string& unit)
  throw (ClubErreurs) 
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::setRealData (int index, double value, "
                     "const string& unit)");
}
  
//-----------------------------------------------------------------------------
// StructureFile::deleteData (const string& dataName) 
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::deleteData (const string& dataName) throw (ClubErreurs) 
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::deleteData (const string& dataName)");
}

//-----------------------------------------------------------------------------
// StructureFile::deleteData (int index)
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::deleteData (int index)
  throw (ClubErreurs) 
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::deleteData (int index)");
}



//-----------------------------------------------------------------------------
// void StructureFile::writeMemoryStructure ()
// Not implemented
// Exception
//      ClubErreurs::not_implemented
//-----------------------------------------------------------------------------

void StructureFile::writeMemoryStructure () throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "StructureFile::writeMemoryStructure ()");
}
  
