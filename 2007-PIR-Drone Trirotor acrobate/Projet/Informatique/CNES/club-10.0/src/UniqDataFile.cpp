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
//>       UniqDataFile.cpp
//
//$Summary
//       file implementing functions of class UniqDataFile
//
//$Description
//       Definition module of class UniqDataFile
//
//$Content
//>       class UniqDataFile
//>         UniqDataFile()
//>         ~UniqDataFile()
//>         getCurrentData()
//>         moveDown()
//>         moveUp()
//>         moveTo()
//>         getData()
//>         setCurrentData()
//>         getAbsoluteDataName()
//>         testCurrentDataIsATable()
//>         testCurrentDataNotATable()
//>         testUndefinedStructureOrTable()
//>         testUndefinedParameter()
//>         testUndefinedIndex()
//>         testUndefinedData()
//>         testMoveUpForbidden()
//>         testDataAlreadyDefined()
//>       intToString()
//>       doubleToString()
//>       getFirstElementName()
//>       getParentName()
//>       getLastChildName()
//>       hasMoreSubDataNames()
//$History
//       $Log: UniqDataFile.cpp,v $
//       Revision 1.12  2005/02/04 10:07:45  chope
//       élimination des méthodes stringToDouble et stringToInt (DM-ID 242)
//       élimination des références aux classes DataProxyName et DataProxyIndex (DM-ID 241)
//
//       Revision 1.11  2003/02/03 16:09:24  club
//       DM-ID 12 Correction d'une erreur dans un algo suite à la mise
//       à jour d'un include selon la norme C++
//
//       Revision 1.10  2003/02/03 14:12:35  club
//       DM-ID 12 Mise à jour d'un include selon la norme C++ & mise
//       à jour du code en conséquence
//
//       Revision 1.9  2003/02/03 14:08:01  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.8  2001/03/22 11:50:20  club
//       simplified the stringToInt function
//       corrected a wrong deallocation method in intToString
//
//       Revision 1.7  2000/11/10 15:28:16  club
//       élimination de replaceCharacter qui transforme les '.' en ','
//
//       Revision 1.6  2000/11/09 10:32:55  club
//       Création de fichiers afin d'avoir une classe par fichiers.
//       Cette séparation concerne les classes DataProxy, DataProxyIndex
//       et DataProxyName.
//       Mise à jour des inclusions fichiers par rapport à cette séparation.
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
//       Revision 1.2  2000/10/18 09:15:04  club
//       suppression de la méthode testIndexAlreadyDefined et suppression de la
//       levée d'exception par le constructeur.
//
//       Revision 1.1  2000/10/16 15:43:51  club
//       Initial revision.
//
//$Version
//       $Id: UniqDataFile.cpp,v 1.12 2005/02/04 10:07:45 chope Exp $
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

#ifdef HAVE_SSTREAM
#include <sstream>
#endif

#include "club/ClubErreurs.h"
#include "club/UniqDataFile.h"


//-----------------------------------------------------------------------------
// UniqDataFile::UniqDataFile ()
// Build new UniqDataFile and initialize current data with ""
//-----------------------------------------------------------------------------

UniqDataFile::UniqDataFile ()
{
  setCurrentData ("");
}

//-----------------------------------------------------------------------------
// UniqDataFile::~UniqDataFile ()
// Destroy UniqDataFile instance
//-----------------------------------------------------------------------------

UniqDataFile::~UniqDataFile ()
{ }

//-----------------------------------------------------------------------------
// string UniqDataFile::getCurrentData () 
// Return name of current data 
// Out
//      name of current data
//-----------------------------------------------------------------------------

string UniqDataFile::getCurrentData ()
{
  return currentData_;
}

//-----------------------------------------------------------------------------
// void UniqDataFile::moveDown (const string& childDataName)
// Move to a child of current data. This method only executes the modification
// on currentData_
// In
//      childDataName : name of child data
//-----------------------------------------------------------------------------

void UniqDataFile::moveDown (const string& childDataName) throw (ClubErreurs)
{
  if (getCurrentData () == "")
    setCurrentData (childDataName);
  else
    setCurrentData (getCurrentData () + "." + childDataName);
}

//-----------------------------------------------------------------------------
// void UniqDataFile::moveDown (int index)
// Move to child (of current data) whose index is "index". The current data
// must be a table. This method only executes the modification on currentData_
// In
//      index : index of child data (first value is "1")
//-----------------------------------------------------------------------------

void UniqDataFile::moveDown (int index) 
  throw (ClubErreurs)
{
  setCurrentData (getCurrentData () + "[" + intToString (index) + "]");
}

//-----------------------------------------------------------------------------
// void UniqDataFile::moveUp ()
// Move to parent node of current data. This method only executes the  
// modifications on currentData_
//-----------------------------------------------------------------------------

void UniqDataFile::moveUp () throw (ClubErreurs)
{
  setCurrentData (getParentName (getCurrentData ()));
}

//-----------------------------------------------------------------------------
// void UniqDataFile::moveTo (const string& absoluteDataName)
// Move data pointer on any data. This method only executes the modification 
// on currentData_
// In
//      absoluteDataName : absolute data name of data
//-----------------------------------------------------------------------------

void UniqDataFile::moveTo (const string& absoluteDataName) throw (ClubErreurs)
{
  while (canMoveUp ())
    moveUp ();

  string dataName = absoluteDataName;
  string rest;

  while (hasMoreSubDataNames (dataName, &rest))
  {
    moveDown (getFirstElementName (dataName));
    dataName = rest;
  }  
}

//-----------------------------------------------------------------------------
// void UniqDataFile::setCurrentData (const string& currentData) 
// Set current data
// In
//      currentData : new name of current data
//-----------------------------------------------------------------------------

void UniqDataFile::setCurrentData (const string& currentData)
{
  currentData_ = currentData;
}

//-----------------------------------------------------------------------------
// string UniqDataFile::getAbsoluteDataName (const string& childDataName) 
// Return absolute data name of a data
// In
//      childDataName : relative name of a data
// Out
//      the absolute data name of a data
//-----------------------------------------------------------------------------

string UniqDataFile::getAbsoluteDataName (const string& childDataName)
{
  string result;

  if (getCurrentData () == "")
    result = childDataName;

  else if ((childDataName.size () > 0) && (childDataName [0] == '['))
    result = getCurrentData () + childDataName;

  else
    result = getCurrentData () + "." + childDataName;

  return result;
}

//-----------------------------------------------------------------------------
// string UniqDataFile::getAbsoluteDataName (int index) 
// Return absolute data name of a data referenced by index
// In
//      index : index of a data
// Out
//      the absolute data name of a data
//-----------------------------------------------------------------------------

string UniqDataFile::getAbsoluteDataName (int index)
{
  string result;
  result = getCurrentData () + "[" + intToString (index) + "]";
  return result;
}

//-----------------------------------------------------------------------------
// void UniqDataFile::testCurrentDataIsATable () 
// Check if current data is a table
// Exception
//      current_data_not_a_table if current data is not a table
//-----------------------------------------------------------------------------

void UniqDataFile::testCurrentDataIsATable () throw (ClubErreurs)
{
  string lastName = getLastChildName (getCurrentData ());
  // if we can not move up, we are sure that current data is the root.
  if (canMoveUp ())
  {
    moveUp ();
    
    if (getDataType (lastName) == TableType)
    {
      moveDown (lastName);
      throw ClubErreurs (ClubErreurs::current_data_is_a_table, 
                         getCurrentData ().c_str ());
    } 
    else
      moveDown (lastName);
  }
}

//-----------------------------------------------------------------------------
// void UniqDataFile::testCurrentDataNotATable () 
// Check if current data is not a table
// Exception
//      current_data_not_a_table if current data is not a table
//-----------------------------------------------------------------------------

void  UniqDataFile::testCurrentDataNotATable () throw (ClubErreurs)
{
  string lastName = getLastChildName (getCurrentData ());
  // if we can not move up, we are sure that current data is the root.
  if (canMoveUp ())
  {
    moveUp ();
    
    if (getDataType (lastName) != TableType)
    {
      moveDown (lastName);
      throw ClubErreurs (ClubErreurs::current_data_not_a_table, 
                         getCurrentData ().c_str ());
    } 
    else
      moveDown (lastName);
  }
  else
    throw ClubErreurs (ClubErreurs::current_data_not_a_table, 
                       getCurrentData ().c_str ());
    
}

//-----------------------------------------------------------------------------
// void UniqDataFile::testUndefinedStructureOrTable (const string& dataName) 
// Check if the table or structure childDataName exists
// In
//      childDataName : relative name of data searched
// Exception
//      ClubErreurs::undefined_structure_or_table if data does not exist, or
//      if data is not a table or structure
//-----------------------------------------------------------------------------

void UniqDataFile::testUndefinedStructureOrTable (const string& childDataName) 
  throw (ClubErreurs)
{
  if (! dataExists (childDataName))
  {
    throw ClubErreurs (ClubErreurs::undefined_table_or_structure, 
                       getAbsoluteDataName (childDataName).c_str ());
  } 

  UniqDataFile::DataType type = getDataType (childDataName); 

  if (type != ReferenceType && type != TableType && type != StructureType)
  {
    throw ClubErreurs (ClubErreurs::undefined_table_or_structure, 
                       getAbsoluteDataName (childDataName).c_str ());
  }
}

//-----------------------------------------------------------------------------
// void UniqDataFile::testUndefinedParameter (const string& childDataName) 
// Check if the parameter childDataName exists
// In
//      childDataName : relative name of data searched
// Exception
//      ClubErreurs::undefined_parameter if data does not exist, or if data is
//      not a parameter
//-----------------------------------------------------------------------------

void  UniqDataFile::testUndefinedParameter (const string& childDataName) 
  throw (ClubErreurs)
{
  if (! dataExists (childDataName))
  {
    throw ClubErreurs (ClubErreurs::undefined_parameter, 
                       getAbsoluteDataName (childDataName).c_str ());
  } 

  UniqDataFile::DataType type = getDataType (childDataName); 

  if (type!= ReferenceType && type != ParameterType)
  {
    throw ClubErreurs (ClubErreurs::undefined_parameter, 
                       getAbsoluteDataName (childDataName).c_str ());
  }
}  

//-----------------------------------------------------------------------------
// void UniqDataFile::testUndefinedIndex (int index)
// Check if data indexed by index exists
// In
//      index : index of data
// Exception
//      ClubErreurs::undefined_index if data does not exist
//-----------------------------------------------------------------------------

void  UniqDataFile::testUndefinedIndex (int index) throw (ClubErreurs)
{
  if (! dataExists (index))
    throw ClubErreurs (ClubErreurs::undefined_index, index, 
                       getCurrentData ().c_str ());
}  

//-----------------------------------------------------------------------------
// void UniqDataFile::testUndefinedData (const string& childDataName) 
// Check if the data named childDataName exists
// In
//      childDataName : relative name of data searched
// Exception
//      ClubErreurs::undefined_data if data does not exist
//-----------------------------------------------------------------------------

void UniqDataFile::testUndefinedData (const string& childDataName) 
  throw (ClubErreurs)
{
  if (! dataExists (childDataName))
    throw ClubErreurs (ClubErreurs::undefined_data, 
                       getAbsoluteDataName (childDataName).c_str ());
}

//-----------------------------------------------------------------------------
// void UniqDataFile::testMoveUpForbidden () 
// Check if moving up is allowed
// Exception
//      ClubErreurs::move_up_forbidden if moving up is forbidden 
//-----------------------------------------------------------------------------

void UniqDataFile::testMoveUpForbidden () throw (ClubErreurs)
{
  if (! canMoveUp ())
    throw ClubErreurs (ClubErreurs::move_up_forbidden);
}

//-----------------------------------------------------------------------------
// void UniqDataFile::testDataAlreadyDefined (const string& childDataName) 
// Check if data named childDataName already exists
// In
//      childDataName : name of data
// Exception
//      ClubErreurs::data_already_defined if data exists
//-----------------------------------------------------------------------------

void UniqDataFile::testDataAlreadyDefined (const string& childDataName)
  throw (ClubErreurs)
{
  if (dataExists (childDataName))
    throw ClubErreurs (ClubErreurs::data_already_defined, 
                       getAbsoluteDataName (childDataName).c_str ());
}

//-----------------------------------------------------------------------------
// string intToString (int i)
// Convert an integer into a string
// In
//       i : an integer
// Out
//       the corresponding string.
//-----------------------------------------------------------------------------

string intToString (int i)
{
  ostringstream tab;
  tab << i;
  return tab.str();
}

//-----------------------------------------------------------------------------
// string doubleToString (double d)
// Convert a real into a string
// In
//       d : a real
// Out
//       the corresponding string.
//-----------------------------------------------------------------------------

string doubleToString (double d)
{
  ostringstream tab;
  tab << d ;
  return tab.str();
}

//-----------------------------------------------------------------------------
// string getFirstElementName (const string& dataName)
// Return the first data name (on the left side) of a complete data name.
// In
//     dataName : a complete data name
// Out
//     name of dataName's root element or "" if it does not exist
// Exception
//     ClubErreurs : name_error if dataName is malformed (missing ']' while
//     '[' if found).
//----------------------------------------------------------------------------

string getFirstElementName (const string& dataName) throw (ClubErreurs)
{
  if (dataName.size () > 0)
  {
    if (dataName [0] == '[')
    {
      int index = dataName.find_first_of ("]");

      if (index == -1)
        throw ClubErreurs (ClubErreurs::name_error, dataName.c_str ());
      else
        return dataName.substr (0, index+1);
    } 
    else 
    {
      int index = dataName.find_first_of ("[.");

      if (index == -1)
        return dataName;
      else
        return dataName.substr (0, index);
    }
  }
  else
    return string ("");
}

//-----------------------------------------------------------------------------
// string getParentName (const string& dataName)
// Return name of dataName's parent data
// In
//     dataName : a complete data name
// Out
//     name of dataName's parent data or "" if parent data does not exist
//-----------------------------------------------------------------------------

string getParentName (const string& dataName)
{
  int index = dataName.find_last_of (".[");

  if (index == -1)
    return string ("");
  else
    return dataName.substr (0, index);
}

//-----------------------------------------------------------------------------
// string getLastChildName (const string& dataName)
// Return name of last element of dataName
// In
//     dataName : a complete data name
// Out
//     name of last element 
//-----------------------------------------------------------------------------

string getLastChildName (const string& dataName)
{
  int index = dataName.find_last_of (".[");

  if (index == -1)
    return dataName;
  else if (dataName [index] == '.')
    return dataName.substr (index+1, dataName.size ()-index-1);
  else
    return dataName.substr (index, dataName.size ()-index);
}

//-----------------------------------------------------------------------------
// bool hasMoreSubDataNames (const string& dataName, string* subDataName)
// Return the sub data name of a data name without root element
// It allows such usage :
// while (hasMoreSubDataName (des, subdes)){
//   des = subdes;
//   any_function ();
// }
//
// In 
//     dataName : a data name
// Out
//     subDataName : a sub data name without root element
//     true if dataName has sub data, false otherwise
//-----------------------------------------------------------------------------

bool hasMoreSubDataNames (const string& dataName, string* subDataName)
{
  bool result;
  int index = dataName.find_first_of (".[");

  if (dataName == "")
  {
    result = false;
    *subDataName = "";
  }
  else if (index != -1)
  {
    result = true;
    if (dataName[index] == '.')
    {
      *subDataName = subDataName->assign (dataName, index+1, 
                                          dataName.size ()-index-1);
    } 
    else
    { 
      // cas ou dataName[index] == '['
      if (index == 0)
      {
        //on recherche le ']' correspondant;
        index = dataName.find_first_of ("]");
        *subDataName = subDataName->assign (dataName, index+1, 
                                            dataName.size ()-index-1);

        //On supprime le '.' si ']' en est suivi.
        if ((subDataName->size() > 0) && ((*subDataName) [0] == '.'))
          *subDataName = subDataName->assign (*subDataName, 1, 
                                              subDataName->size ()-1);
      }
      else
        *subDataName = subDataName->assign (dataName, index, 
                                            dataName.size ()-index);
    }
  } 
  else
  { 
    // cas ou index ==-1;
    result = true;
    *subDataName = "";
  }

  return result;
}
