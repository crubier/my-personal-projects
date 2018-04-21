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
//>       MadonaFile.cpp
//
//$Summary
//       file implementing functions of class MadonaFile
//
//$Description
//       Definition module of class MadonaFile
//
//$Content
//>       static void getLastErrorMessage ()
//>       static void messageReporting ()
//>       class MadonaFile
//>         MadonaFile ()
//>         ~MadonaFile ()
//>         moveDown ()
//>         moveUp ()
//>         readFile ()
//>         writeFile ()
//>         getDataType ()
//>         size ()
//>         dataExists ()
//>         getComment ()
//>         setComment ()
//>         createStringData ()
//>         createIntData ()
//>         createRealData ()
//>         createTable ()
//>         createStructure ()
//>         createReference ()
//>         getStringData ()
//>         getIntData ()
//>         getRealData ()
//>         setStringData ()
//>         setIntData ()
//>         setRealData ()
//>         deleteData ()
//>         writeMemoryStructure()
//>        getAccess ()
//>         canMoveUp ()
//>         reposition ()
//$History
//       $Log: MadonaFile.cpp,v $
//       Revision 1.13  2005/02/21 13:26:49  chope
//       correction d'une faute de frappe (DM-ID 242)
//
//       Revision 1.12  2005/02/04 10:10:41  chope
//       élimination de la méthode loadUnitFile (DM-ID 242)
//
//       Revision 1.11  2003/07/17 12:38:06  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 1.10  2003/07/09 08:09:25  club
//       correction d'une erreur de syntaxe (FA 26)
//
//       Revision 1.9  2003/03/21 15:48:42  club
//       Suppression de la variable path_
//
//       Revision 1.8  2003/03/21 15:40:48  club
//       DM-ID 21: amélioration de la gestion du pointeur madona pour permettre des accès
//       multiples à une donnée partagée entre plusieurs instances sans conflits.
//
//       Revision 1.7  2003/02/03 13:42:28  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.6  2002/12/10 09:09:14  club
//       DM-ID 12 Modification de l'initialisation des pointeurs/variables et ajout d'un cas par défaut dans une instruction switch
//
//       Revision 1.5  2001/03/13 14:06:01  club
//       removed spurious default values in function definitions
//
//       Revision 1.4  2000/10/24 14:21:01  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 1.3  2000/10/24 08:33:30  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.2  2000/10/18 09:13:42  club
//       suppression de la levée d'exception pour le constructeur.
//
//       Revision 1.1  2000/10/16 15:43:51  club
//       Initial revision.
//
//$Version
//       $Id: MadonaFile.cpp,v 1.13 2005/02/21 13:26:49 chope Exp $
//
//$Authors
//       F. Deshaies CSSI
//       Copyright (C) CNES 2000
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_STL
#include <string>
#endif

#ifdef HAVE_ACCES_H
#include <acces.h>
#endif

#include "club/ClubErreurs.h"
#include "club/MadonaFile.h"


static string lastErrorMessage = "";
static bool unitsLoaded        = false;


//-----------------------------------------------------------------------------
// string& getLastErrorMessage ()
// Return the last madona error message
// out
//      the last madona error message
//-----------------------------------------------------------------------------

static string& getLastErrorMessage ()
{
  return lastErrorMessage;
}

//-----------------------------------------------------------------------------
// void messageReporting (int status, const char* subr, 
//                        const char* msg, const char* msg_glob)
// The user function for writing madona error messages.
// This method is used as a parameter while instancing the MadonaFile class . 
// In
//      status :error type
//      subr   : the function name, origin of the error
//      msg    : message of principal level
//      msg_glob : complete message. 
//-----------------------------------------------------------------------------

static void messageReporting (int status, const char* subr, 
                              const char* msg, const char* msg_glob)
{
  switch (status)
  {
    case ACC_ERR_TYPE_ERR :
      lastErrorMessage = "Error - in ";
      break;
    case ACC_ERR_TYPE_WARN :
      lastErrorMessage = "Warning - in ";
      break;
    case ACC_ERR_TYPE_FATAL :
      lastErrorMessage = "Fatal error - in ";
      break;
    case ACC_ERR_TYPE_ERR0 :
      lastErrorMessage = "Use error - in ";
      break;
    default :
      break;
  }  

  lastErrorMessage += subr ;
  lastErrorMessage += " : ";
  lastErrorMessage += msg ;
  lastErrorMessage += " - ";
  lastErrorMessage += msg_glob;
}

//-----------------------------------------------------------------------------
// MadonaFile::MadonaFile ()
// Build a MadonaFile instance.
// Exception
//      ClubErreurs::madona_error thrown if an error occurred while initialization
//-----------------------------------------------------------------------------

MadonaFile::MadonaFile () throw (ClubErreurs)
  : UniqDataFile () 
{
  selectCount_ = 0;
  access_ = acc_open ();

  int ret = acc_set_printfct (messageReporting);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, "");

  if (! unitsLoaded)
  {
    // units should only be loaded once
    ret = acc_unit_load ("unites");  
    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
    unitsLoaded = true;
  }
}

//-----------------------------------------------------------------------------
// MadonaFile::~MadonaFile ()
// Destructs a MadonaFile instance
// Exception
//       ClubErreurs::madona_error
//-----------------------------------------------------------------------------

MadonaFile::~MadonaFile () throw (ClubErreurs)
{
  int ret = acc_close (access_);
  if (ret != 0)
    throw ClubErreurs (ClubErreurs::madona_error, getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// void MadonaFile::moveDown (const string& relativeDataName)
// Move to child (of current data) named relativeDataName 
// In
//      relativeDataName : relative data name of child to move to.
// Exception
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::undefined_table_or_structure
//      ClubErreurs::undefined_index
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::moveDown (const string& childDataName) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName)) 
  {
    moveDown (getIndexValue (childDataName));
  } 
  else 
  { 
    // use the absolute path to go to the current data
    reposition();

    testUndefinedStructureOrTable (childDataName);
    int nat = (acc_get_type (getAccess (), childDataName.c_str ()) == ACC_REF)
            ? ACC_REF : ACC_STRUCT;
    int ret = acc_select (getAccess (), childDataName.c_str (), nat);

    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());

    UniqDataFile::moveDown (childDataName);
    selectCount_ ++;
  }
}

//-----------------------------------------------------------------------------
// void MadonaFile::moveDown (int index)
// Move to child (of current data) whose index is "index". The current data
// must be a table.
// In
//      index : index of child data (first value is "1")
// Exception
//       ClubErreurs::undefined_table_or_structure
//       ClubErreurs::undefined_index if index does not exist
//       ClubErreurs::madona_error 
//-----------------------------------------------------------------------------

void MadonaFile::moveDown (int index) throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedIndex (index);

  int ret = acc_set_index (getAccess (), index);

  if (ret < 0)
    throw ClubErreurs(ClubErreurs::madona_error, getLastErrorMessage().c_str());

  if (getDataType (ACC_INDEX) == ParameterType)
  {
    string badDataName = getAbsoluteDataName (index);
    throw ClubErreurs (ClubErreurs::undefined_table_or_structure, 
                       badDataName.c_str ());
  }

  int nat = (acc_get_type (getAccess (), ACC_INDEX) == ACC_REF)
          ? ACC_REF : ACC_STRUCT;
  ret = acc_select (getAccess (), ACC_INDEX, nat);

  if (ret <0 )
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  UniqDataFile::moveDown (index);
  selectCount_ ++;
}

//-----------------------------------------------------------------------------
// void MadonaFile::moveUp ()
// Move to parent node of current data
// Exception
//      ClubErreurs::move_up_forbidden
//      ClubErreurs::madona_error 
//-----------------------------------------------------------------------------

void MadonaFile::moveUp () throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testMoveUpForbidden ();    

  int ret = acc_select_end (getAccess ());

  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  UniqDataFile::moveUp ();
  selectCount_ --;
}

//-----------------------------------------------------------------------------
// void MadonaFile::readFile (const string& fileName)
// Load a file in memory
// In
//      fileName : name of file to load.
// Exception
//      ClubErreurs::file_error if parsing has failed
//-----------------------------------------------------------------------------

void MadonaFile::readFile (const string& fileName) throw (ClubErreurs)
{
  int ret = acc_connect (getAccess (), fileName.c_str (), ACC_R);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::file_error, fileName.c_str (), 
                       getLastErrorMessage ().c_str ());

  ret = acc_read (getAccess (), ACC_ALL);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::file_error, fileName.c_str (), 
                       getLastErrorMessage ().c_str ());

  ret = acc_deconnect (getAccess (), ACC_R);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::file_error, fileName.c_str (), 
                       getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// void MadonaFile::writeFile (const string& fileName)
// Write the access zone in a file
// In
//      fileName : name of file to write.
// Exception
//      ClubErreurs::file_error if file opening has failed
//-----------------------------------------------------------------------------

void MadonaFile::writeFile (const string& fileName) throw (ClubErreurs)
{
  int ret = acc_connect (getAccess (), fileName.c_str (), ACC_W);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::file_error, fileName.c_str (), 
                       getLastErrorMessage ().c_str ());

  ret = acc_write (getAccess (), ACC_ALL);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::file_error, fileName.c_str (), 
                       getLastErrorMessage ().c_str ());

  ret = acc_deconnect (getAccess (), ACC_W);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::file_error, fileName.c_str (), 
                       getLastErrorMessage ().c_str ());
}
 
//-----------------------------------------------------------------------------
// UniqDataFile::DataType MadonaFile::getDataType (const string& childDataName)
// Return the type of data named childDataName
// In
//      childDataName : name of data.
// Out
//      type of element (value of enum UniqDataFile::DataType)
// Exception
//      ClubErreurs::undefined_data
//      ClubErreurs::undefined_index
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::madona_error
//      ClubErreurs::string_to_int_conversion
//-----------------------------------------------------------------------------

UniqDataFile::DataType MadonaFile::getDataType (const string& childDataName) 
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    int index = getIndexValue (childDataName);
    return getDataType (index);
  } 
  else
  {
    UniqDataFile::DataType result;

    // use the absolute path to go to the current data
    reposition();

    if (! dataExists (childDataName))
      throw ClubErreurs (ClubErreurs::undefined_data, 
                         getAbsoluteDataName (childDataName).c_str ());

    int ret = acc_get_type (getAccess (), childDataName.c_str ());
    switch (ret)
    {
      case ACC_STRUCT: 
        result = StructureType; 
        break;
      case ACC_TABL:
        result = TableType;
        break;
      case ACC_PARAM:
        result = ParameterType;
        break;
      case ACC_REF:
        result = ReferenceType;
        break;
      default:
        result = UndeterminedType;
        break;
    }

    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());

    return result;
  }
}
 
//-----------------------------------------------------------------------------
// UniqDataFile::DataType MadonaFile::getDataType (const string& childDataName)
// Return the type of an indexed data. Current data must be a table.
// In
//      index : index of the element.
// Out
//      type of element (value of enum UniqDataFile::DataType)
// Exception
//       ClubErreurs::current_data_not_a_table
//       ClubErreurs::undefined_index
//       ClubErreurs::madona_error
//-----------------------------------------------------------------------------

UniqDataFile::DataType MadonaFile::getDataType (int index) 
  throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedIndex(index);
  UniqDataFile::DataType result;

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
  
  ret = acc_get_type (getAccess (), ACC_INDEX);
  switch (ret)
  {
    case ACC_STRUCT: 
      result = StructureType; 
      break;
    case ACC_TABL:
      result = TableType;
      break;
    case ACC_PARAM:
      result = ParameterType;
      break;
    case ACC_REF:
      result = ReferenceType;
      break;
    default:
      result = UndeterminedType;
      break;
  }

  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  return result; 
}

//-----------------------------------------------------------------------------
// int MadonaFile::size ()
// Return the number of children of current data (current data must be a table)
// Out
//      number of children of current data
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

int MadonaFile::size () throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  int ret;
  string child = getLastChildName (getCurrentData ());

  if (! canMoveUp ())
    throw ClubErreurs (ClubErreurs::current_data_not_a_table, 
                       getCurrentData ().c_str ());

  moveUp ();

  if (getDataType (child) != TableType) 
  {
    moveDown (child);
    throw ClubErreurs (ClubErreurs::current_data_not_a_table, 
                       getCurrentData ().c_str ());
  }
  
  if (isDataNameAnIndex (child))
  {
    int index = getIndexValue (child); 
    ret = acc_set_index (getAccess (), index);

    if (ret < 0)
    {
      moveDown (child);
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
    }

    ret = acc_get_dim (getAccess (),  ACC_INDEX);
  } 
  else 
  {
    ret = acc_get_dim (getAccess (), (char*) child.c_str ());
  }

  if (ret < 0)
  {
    moveDown (child);
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
  }
 
  moveDown (child);
  return ret;
}

//-----------------------------------------------------------------------------
// bool MadonaFile::dataExists (const string& childDataName)
// Check whether childDataName exists
// In
//      childDataName : name of child
// out
//      true if childDataName exists, false otherwise
// Exception
//      ClubErreurs::madona_error
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::current_data_not_a_table
//-----------------------------------------------------------------------------

bool MadonaFile::dataExists (const string& childDataName) throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  if (isDataNameAnIndex (childDataName))
  {
    return dataExists (getIndexValue (childDataName));
  } 
  else
  {
    int ret = acc_exist (getAccess (), childDataName.c_str ());

    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());

    return ret == 1;
  }
}  

//-----------------------------------------------------------------------------
// bool MadonaFile::dataExists (int index)
// Check whether data whose index is "index" exists. Current data
// must be a table.
// In
//      index : value of index attribute
// out
//      true if child exists, false otherwise
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

bool MadonaFile::dataExists (int index) throw (ClubErreurs)
{
  int tableSize = size ();
  return (index >= 1) && (index <= tableSize);
}


//-----------------------------------------------------------------------------
// string MadonaFile::getComment (const string& childDataName)
// Return comments of childDataName
// In
//      childDataName : Name of child whose comments must be returned
// Out
//      comments of childDataName
// Exception
//      ClubErreurs::undefined_data if childDataName does not exist
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::not_implemented
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

string MadonaFile::getComment (const string& childDataName) throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  // check whether data exists
  testUndefinedData (childDataName);
  
  if (isDataNameAnIndex (childDataName))
  {
    int index = getIndexValue (childDataName);
    return getComment (index);
  }
  else
  {
    string result ("");
    char * c_comment = NULL;

    // getting comment ...
    int ret = acc_getcom (getAccess (), childDataName.c_str (), 
                        ACC_FIRST_LINE, &c_comment);

    // ... has succedded
    if (ret >= 0)
    {
      result += c_comment;
      while (acc_getcom (getAccess (), childDataName.c_str (), 
                         ACC_NEXT_LINE, &c_comment) >= 0)
      {
        result += "\n";
        result += c_comment;
      }
    }
    
    return result;
  }
}

//-----------------------------------------------------------------------------
// string MadonaFile::getComment (int index)
// 
// This method is not implemented. Always throw ClubErreurs::not_implemented 
// exception.
// In
//      index : index of child data (first value is "1")
// Exception
//      ClubErreurs::not_implemented.
//-----------------------------------------------------------------------------

string MadonaFile::getComment (int index) throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented, 
                     "string MadonaFile::getComment (int index)");
} 

//-----------------------------------------------------------------------------
// void MadonaFile::setComment (const string& childDataName, 
//                              const string& comment)
// Set comments of childDataName
// In
//      childDataName : name of child whose comments must be set
//      comment       : comment of childDataName
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_data if childDataName does not exist
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::setComment (const string& childDataName,
                             const string& comment) throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedData (childDataName);

  if (isDataNameAnIndex (childDataName))
  {
    int index = getIndexValue (childDataName);
    setComment (index, comment);
  }
  else
  {
    string commentTemp = comment;
    string line;
    int index = commentTemp.find_first_of ("\n");
    
    if (index == -1)
    {
      line = commentTemp;
      commentTemp = "";
    }
    else 
    {
      line = line.append (commentTemp, 0, index);
      commentTemp = commentTemp.assign (commentTemp, index, 
                                        commentTemp.size ()-index-1);
    }
    
    int ret = acc_putcom (getAccess (), childDataName.c_str (), 
                          ACC_FIRST_LINE, (char*)line.c_str ());
    
    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
    
    while ((index = commentTemp.find_first_of ("\n")) != -1)
    {
      line = line.append (commentTemp, 0, index);
      
      int ret = acc_putcom (getAccess (), childDataName.c_str (), 
                            ACC_NEXT_LINE, (char*)line.c_str ());
      if (ret < 0)
        throw ClubErreurs (ClubErreurs::madona_error, 
                           getLastErrorMessage ().c_str ());
      
      commentTemp = commentTemp.assign (commentTemp, index+1, 
                                        commentTemp.size ()-index-1);  
    }
  }
}

//-----------------------------------------------------------------------------
// void MadonaFile::setComment (int index, 
//                              const string& comment)
// This method is not implemented. Always throw ClubErreurs::not_implemented 
// exception.
// In
//      index   : index of child data (first value is "1")
//      comment : comment of childDataName
// Exception
//      ClubErreurs::not_implemented.
//-----------------------------------------------------------------------------

void MadonaFile::setComment (int index, const string& comment)
  throw (ClubErreurs)
{
  throw ClubErreurs (ClubErreurs::not_implemented,
                     "MadonaFile::setComment (int index, const string& comment)");
}
 
//-----------------------------------------------------------------------------
// void MadonaFile::createStringData (const string& childDataName, 
//                                    const string& value)
// Create a child of type String named childDataName
// In
//      childDataName : name of string data
//      value : new value
// Exception
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::data_already_defined
//      ClubErreurs::index_creation_forbidden if childDataName is an index name
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------
   
void MadonaFile::createStringData (const string& childDataName, 
                                   const string& value) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
     throw ClubErreurs (ClubErreurs::index_creation_forbidden, 
                        getAbsoluteDataName (childDataName).c_str ());
  else
  { 
    // use the absolute path to go to the current data
    reposition();

    // Check if the current data is a table.
    testCurrentDataIsATable ();

    testDataAlreadyDefined (childDataName);

    int ret = acc_puts (getAccess (), childDataName.c_str (), 
                        (char*) value.c_str ());
    if (ret < 0) 
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}
  
//-----------------------------------------------------------------------------
// void MadonaFile::createStringData (const string& value)
// Create new string data. Current data must be a table. 
// In
//      value : new value
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::createStringData (const string& value) throw (ClubErreurs)
{
  int index = size () + 1; 

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_puts (getAccess (), ACC_INDEX, (char*) value.c_str ());
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// void MadonaFile::createIntData (const string& childDataName, int value)
// Create a child of type Int named childDataName
// In
//      childDataName : name of string data
//      value : new value
// Exception
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::data_already_defined
//      ClubErreurs::index_creation_forbidden if childDataName is an index name
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::createIntData (const string& childDataName, int value) 
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
     throw ClubErreurs (ClubErreurs::index_creation_forbidden, 
                        getAbsoluteDataName (childDataName).c_str ());
  else
  {
    // use the absolute path to go to the current data
    reposition();

    // Check if the current data is a table.
    testCurrentDataIsATable ();

    testDataAlreadyDefined (childDataName);

    int ret = acc_puti (getAccess (), childDataName.c_str (), value);
    if (ret < 0) 
      throw ClubErreurs ( ClubErreurs::madona_error, 
                          getLastErrorMessage ().c_str ());
  }
}

//-----------------------------------------------------------------------------
// void MadonaFile::createIntData (int value)
// Create new int data. Current data must be a table. 
// In
//      value : new value
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::createIntData (int value) throw (ClubErreurs)
{
  int index = size () + 1;

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_puti (getAccess (), ACC_INDEX, value);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// void MadonaFile::createRealData (const string& childDataName, double value,
//                                  const string& unit)
// Create a child of type Real named childDataName
// In
//      childDataName : name of string data
//      value : new value
//      unit  : unit of value
// Exception
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::data_already_defined
//      ClubErreurs::index_creation_forbidden if childDataName is an index name
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::createRealData (const string& childDataName, double value,
                                 const string& unit) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
     throw ClubErreurs (ClubErreurs::index_creation_forbidden, 
                        getAbsoluteDataName (childDataName).c_str ());
  else
  {
    // use the absolute path to go to the current data
    reposition();

    // Check if the current data is a table.
    testCurrentDataIsATable ();

    testDataAlreadyDefined (childDataName);

    int ret = acc_putd( getAccess (), childDataName.c_str (), value, 
                        (char*) unit.c_str ());
    if (ret < 0) 
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}

//-----------------------------------------------------------------------------
// void MadonaFile::createRealData (double value, const string& unit)
// Create new real data. Current data must be a table.
// In
//      value : new value
//      unit  : unit of value
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::index_creation_forbidden if childDataName is an index name
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::createRealData (double value, const string& unit)
  throw (ClubErreurs)
{
  int index = size () + 1;

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_putd (getAccess (), ACC_INDEX, value, (char*) unit.c_str ());
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// void MadonaFile::createTable (const string& tableName,
//                            UniqDataFile::TableElementType tableType,
//                            const string& defaultUnit)
// Create a child of type Table named tableName
// In
//      tableName : name of table data
//      tableType : type of table created (IntTable, StringTable, ...)
//      defaultUnit : default unit of tableName (optional)
// Exception
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::index_creation_forbidden if tableName is an index name
//      ClubErreurs::data_already_defined
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::createTable (const string& tableName,
                              UniqDataFile::TableElementType tableType,
                              const string& defaultUnit) 
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (tableName))
    throw ClubErreurs (ClubErreurs::index_creation_forbidden, 
                       getAbsoluteDataName (tableName).c_str ());
  else 
  {
    // use the absolute path to go to the current data
    reposition();

    // Check if the current data is a table.
    testCurrentDataIsATable ();

    testDataAlreadyDefined (tableName);
    int ret;

    if (tableType == UniqDataFile::RealTable)
      ret = acc_create (getAccess (), tableName.c_str (), 
                        ACC_TABL, (char*) defaultUnit.c_str ());
    else 
      ret = acc_create (getAccess (), tableName.c_str (), ACC_TABL, "");

    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}

//-----------------------------------------------------------------------------
// void MadonaFile::createTable (UniqDataFile::TableElementType tableType,
//                            const string& defaultUnit)
// Create new table. Current data must be a table.
// In
//      tableType : type of table created (IntTable, StringTable, ...)
//      defaultUnit : default unit of tableName (optional)
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::createTable (UniqDataFile::TableElementType tableType,
                              const string& defaultUnit) 
  throw (ClubErreurs)
{
  int index = size () + 1;

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  if (tableType == UniqDataFile::RealTable)
    ret = acc_create (getAccess (), ACC_INDEX, ACC_TABL, 
                      (char*) defaultUnit.c_str ());
  else 
    ret = acc_create (getAccess (), ACC_INDEX, ACC_TABL, "");

  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// void MadonaFile::createStructure (const string& structureName)
// Create a child of type Structure named structureName
// In
//      structureName : name of structure data
// Exception
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::index_creation_forbidden if structureName is an index name
//      ClubErreurs::madona_error
//      ClubErreurs::data_already_defined;
//-----------------------------------------------------------------------------

void MadonaFile::createStructure (const string& structureName) 
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (structureName))
    throw ClubErreurs (ClubErreurs::index_creation_forbidden, 
                       getAbsoluteDataName (structureName).c_str ());
  else 
  {    
    // use the absolute path to go to the current data
    reposition();

    // Check if the current data is a table.
    testCurrentDataIsATable ();

    testDataAlreadyDefined (structureName);

    int ret = acc_create (getAccess (), structureName.c_str (), ACC_STRUCT, "");
    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}

//-----------------------------------------------------------------------------
// void MadonaFile::createStructure ()
// Create new structure. Current data must be a table.
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::createStructure () throw (ClubErreurs)
{
  int index = size () + 1;

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_create (getAccess (), ACC_INDEX, ACC_STRUCT, "");
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}


//-----------------------------------------------------------------------------
// void MadonaFile::createReference (const string& childDataName,
//                                const string& referencedFileName,
//                                const string& referencedDataName)
// Create new reference to another data.
// In
//      childDataName : name of child
//      referencedFileName : file containing the referenced data.
//      referencedDataName : the name of the referenced data.  
// Exception
//      ClubErreurs::data_already_defined if data exists
//      ClubErreurs::current_data_is_a_table
//      ClubErreurs::index_creation_forbidden if childDataName is an index name
//      ClubErreurs::madona_error 
//-----------------------------------------------------------------------------

void MadonaFile::createReference (const string& childDataName,
                                  const string& referencedFileName,
                                  const string& referencedDataName) 
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
    throw ClubErreurs (ClubErreurs::index_creation_forbidden, 
                       getAbsoluteDataName (childDataName).c_str ());
  else 
  {
    // use the absolute path to go to the current data
    reposition();

    // Check if the current data is a table.
    testCurrentDataIsATable ();

    testDataAlreadyDefined (childDataName);

    int ret = acc_putr (getAccess (), childDataName.c_str (), 
                        referencedFileName.c_str (), 
                        referencedDataName.c_str ());
    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}


//-----------------------------------------------------------------------------
// void MadonaFile::createReference (const string& referencedFileName,
//                                const string& referencedDataName) 
// Create new reference. Current data must be a table.
// In
//      referencedFileName : file containing the referenced data.
//      referencedDataName : the name of the referenced data.  
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::createReference (const string& referencedFileName,
                                  const string& referencedDataName) 
  throw (ClubErreurs)
{
  int index = size ()+ 1; 

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_putr (getAccess (), ACC_INDEX, referencedFileName.c_str (), 
                  referencedDataName.c_str ());
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// string MadonaFile::getStringData (const string& childDataName)
// Read the string attribute of data named childDataName
// In
//      childDataName : name of child
// Out
//      value of data
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::undefined_parameter 
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error 
//-----------------------------------------------------------------------------

string MadonaFile::getStringData (const string& childDataName) 
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    return getStringData (getIndexValue (childDataName));
  }
  else 
  {
    // use the absolute path to go to the current data
    reposition();

    testUndefinedParameter (childDataName);
    char* c_value = NULL;

    int ret = acc_gets (getAccess (), childDataName.c_str (), &c_value);
    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
    else
      return (string) c_value;
  }
}

//-----------------------------------------------------------------------------
// string MadonaFile::getStringData (int index)
// Read the string attribute of data whose index attribute is "index". Current
// data must be a table. 
// In
//      index : value of index attribute 
// Out
//      value of data
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index 
//      ClubErreurs::madona_error 
//-----------------------------------------------------------------------------

string MadonaFile::getStringData (int index) throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedIndex (index);

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  char * c_value = NULL;

  ret = acc_gets (getAccess (), ACC_INDEX, &c_value);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
  else
    return (string) c_value;
} 

//-----------------------------------------------------------------------------
// int MadonaFile::getIntData (const string& childDataName)
// Read the int attribute of data named childDataName
// In
//      childDataName : name of child
// Out
//      value of data
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::undefined_parameter 
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error 
//-----------------------------------------------------------------------------

int MadonaFile::getIntData (const string& childDataName) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    return getIntData (getIndexValue (childDataName));
  } 
  else
  {
    // use the absolute path to go to the current data
    reposition();

    testUndefinedParameter (childDataName);
    int value;

    int ret = acc_geti (getAccess (), childDataName.c_str (), &value);
    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
    else
      return value;
  }
}

//-----------------------------------------------------------------------------
// int MadonaFile::getIntData (int index)
// Read the int attribute of data whose index attribute is "index". 
// Current data must be a table. 
// In
//      index : value of index attribute 
// Out
//      value of data
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index 
//      ClubErreurs::madona_error 
//-----------------------------------------------------------------------------

int MadonaFile::getIntData (int index) throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedIndex (index);
  int value;

  int ret = acc_set_index (getAccess(), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_geti (getAccess (), ACC_INDEX, &value);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
  else
    return value;
}

//-----------------------------------------------------------------------------
// double MadonaFile::getRealData (const string& childDataName,
//                              const string& unit)
// Read the real attribute of data named childDataName
// In
//      childDataName : name of child
//      unit : physical unit for value to return
// Out
//      value of data
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::undefined_parameter if data does not exist
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error 
//-----------------------------------------------------------------------------

double MadonaFile::getRealData (const string& childDataName,
                                const string& unit) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    return getRealData (getIndexValue (childDataName), unit);
  } 
  else
  {
    // use the absolute path to go to the current data
    reposition();
    
    testUndefinedParameter (childDataName);
    double value;
    int ret = acc_getd (getAccess (), childDataName.c_str (), 
                        &value, (char*) unit.c_str ());

    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
    else
      return value;
  }
}

//-----------------------------------------------------------------------------
// double MadonaFile::getRealData (int index, const string& unit)
// Read the real attribute of data whose index attribute is "index". Current
// data must be a table. 
// In
//      index : value of index attribute 
//      unit  : physical unit for value to return
// Out
//      value of data
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::madona_error 
//-----------------------------------------------------------------------------

double MadonaFile::getRealData (int index, const string& unit)
  throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedIndex (index);
  double value;

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_getd (getAccess (), ACC_INDEX, &value, (char*) unit.c_str ());
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
  else
    return value;
}

//-----------------------------------------------------------------------------
// void MadonaFile::setStringData (const string& childDataName, 
//                              const string& value)
// Update the value attribute of childDataName (childDataName must
// be a string data)
// In
//      childDataName : name of string data
//      value : new value
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::undefined_parameter
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::setStringData (const string& childDataName, 
                                const string& value) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    int index = getIndexValue (childDataName);
    setStringData (index, value);
  } 
  else
  {
    // use the absolute path to go to the current data
    reposition();

    testUndefinedParameter (childDataName);

    int ret = acc_puts (getAccess (), childDataName.c_str (), 
                        (char*) value.c_str ());
    if (ret < 0) 
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}  

//-----------------------------------------------------------------------------
// void MadonaFile::setStringData (int index, const string& value)
// Update the value attribute of a string data. Current data must
// be a table
// In
//      index : index of child
//      value : new value
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::setStringData (int index, const string& value) 
  throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedIndex (index);

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_puts (getAccess (), ACC_INDEX, (char*) value.c_str ());
  if (ret < 0) 
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// void MadonaFile::setIntData (const string& childDataName, int value)
// Update the value attribute of childDataName (childDataName must
// be an int data)
// In
//      childDataName : name of int data
//      value : new value
// Exception
//      ClubErreurs::undefined_parameter
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::setIntData (const string& childDataName, int value) 
  throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    int index = getIndexValue (childDataName);
    setIntData (index, value);
  } 
  else
  {
    // use the absolute path to go to the current data
    reposition();
    
    testUndefinedParameter (childDataName);

    int ret = acc_puti (getAccess (), childDataName.c_str (), value);
    if (ret < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}

//-----------------------------------------------------------------------------
// void MadonaFile::setIntData (int index, int value))
// Update the value attribute of an int data. Current data must
// be a table
// In
//      index : index of child
//      value : new value
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::setIntData (int index, int value) throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedIndex (index);

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0 )
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_puti (getAccess (), ACC_INDEX, value);
  if (ret < 0) 
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// void MadonaFile::setRealData (const string& childDataName, double value,
//                               const string& unit)
// Update the value attribute of childDataName (childDataName must
// be a real data)
// In
//      childDataName : name of real data
//      value : new value
//      unit : unit of value
// Exception
//      ClubErreurs::undefined_parameter
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::setRealData (const string& childDataName, double value,
                              const string& unit) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    int index = getIndexValue (childDataName);
    setRealData (index, value, unit);
  } 
  else
  { 
    // use the absolute path to go to the current data
    reposition();

    testUndefinedParameter (childDataName);

    int ret = acc_putd (getAccess (), childDataName.c_str (), value, 
                        (char*) unit.c_str ());
    if (ret < 0) 
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}

//-----------------------------------------------------------------------------
// void MadonaFile::setRealData (int index, int value, const string& unit)
// Update the value attribute of a real data. Current data must
// be a table
// In
//      index : index of child
//      value : new value
//      unit  : unit of value
// Exception
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_index
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::setRealData (int index, double value, const string& unit) 
  throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedIndex (index);

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0 )
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_putd (getAccess (), ACC_INDEX, value, (char*) unit.c_str ());
  if (ret < 0) 
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}
 
//-----------------------------------------------------------------------------
// void MadonaFile::deleteData (const string& dataName)
// Delete a data.
// In
//      dataName : name of data to delete
// Exception
//      ClubErreurs::undefined_index 
//      ClubErreurs::current_data_is_table
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::undefined_data
//      ClubErreurs::string_to_int_conversion
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::deleteData (const string& childDataName) throw (ClubErreurs)
{
  if (isDataNameAnIndex (childDataName))
  {
    int index= getIndexValue (childDataName);
    deleteData (index);
  } 
  else
  {
    // use the absolute path to go to the current data
    reposition();

    testCurrentDataIsATable ();

    testUndefinedData (childDataName);

    int ret = acc_delete (getAccess (), childDataName.c_str ());
    if (ret < 0) 
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}

//-----------------------------------------------------------------------------
// void MadonaFile::deleteData (int index)
// Delete a data. Current data must be a table.
// In
//      index : value of index attribute of data to delete
// Exception
//      ClubErreurs::undefined_index 
//      ClubErreurs::current_data_not_a_table
//      ClubErreurs::madona_error
//-----------------------------------------------------------------------------

void MadonaFile::deleteData (int index) throw (ClubErreurs)
{
  // use the absolute path to go to the current data
  reposition();

  testUndefinedIndex (index);

  int ret = acc_set_index (getAccess (), index);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());

  ret = acc_delete (getAccess (), ACC_INDEX);
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());
}

//-----------------------------------------------------------------------------
// void MadonaFile::writeMemoryStructure () 
// Write the access zone in the standard output
// Exception
//      Club_erreurs::madona_error 
//-----------------------------------------------------------------------------

void MadonaFile::writeMemoryStructure () throw (ClubErreurs)
{
  int ret = acc_map (getAccess ());
  if (ret < 0)
    throw ClubErreurs (ClubErreurs::madona_error, 
                       getLastErrorMessage ().c_str ());  
}

//------------------------------------------------------------------------------
// ACCES * MadonaFile::getAccess ()
// Return the pointer on the access zone.
// Out
//       The pointer on the access zone.L
//------------------------------------------------------------------------------

ACCES * MadonaFile::getAccess ()
{
  return  access_;  
}

//-----------------------------------------------------------------------------
// bool MadonaFile::canMoveUp ()
// Check if moving up is allowed
// Out
//      true if selectCount_ != 0, false otherwise
//-----------------------------------------------------------------------------

bool MadonaFile::canMoveUp ()
{
  return selectCount_ != 0;
}

//-----------------------------------------------------------------------------
// void MadonaFile::reposition ()
// Reposition the acces pointer to the current position
//-----------------------------------------------------------------------------

void MadonaFile::reposition () throw (ClubErreurs)
{
  if(! getCurrentData().empty()) {
    while(acc_select_end(getAccess()) == 0)
    {}
    
    int nat = (acc_get_type (getAccess (), getCurrentData().c_str ()) == ACC_REF)
            ? ACC_REF : ACC_STRUCT;
    int repos = acc_select(getAccess (), getCurrentData().c_str (), nat);
    if (repos < 0)
      throw ClubErreurs (ClubErreurs::madona_error, 
                         getLastErrorMessage ().c_str ());
  }
}
