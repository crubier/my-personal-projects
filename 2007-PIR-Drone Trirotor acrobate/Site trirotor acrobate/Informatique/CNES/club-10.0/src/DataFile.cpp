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
//>       DataFile.cpp
//
//$Summary
//        file implementing functions of class DataFile
//
//$Description
//        Definition module of class DataFile
//
//$Content
//>       static void deleteDataFile()
//>       class DataFile              
//>         getUniqDataFile()         
//>         DataFile()                
//$History
//       $Log: DataFile.cpp,v $
//       Revision 1.8  2005/02/04 10:11:46  chope
//       replaced XMLFile by XMLData
//
//       Revision 1.7  2003/12/08 14:21:36  club
//       DM-ID 32 : Mise en conformite avec Xerces 2.x
//
//       Revision 1.6  2003/12/05 08:16:26  club
//       DM 0031
//
//       Revision 1.5  2003/02/03 09:14:17  club
//       DM-ID 17 Changement de l'extension du fichier dans le bandeau
//
//       Revision 1.4  2002/12/10 09:04:03  club
//       DM-ID 12 Modification portant sur d'un cas par défaut dans une instruction switch.
//
//       Revision 1.3  2000/10/24 14:21:00  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 1.2  2000/10/18 16:59:50  club
//       déplacement des fonctions inline dans le .h
//
//       Revision 1.1  2000/10/16 15:43:50  club
//       Initial revision.
//
//$Version
//       $Id: DataFile.cpp,v 1.8 2005/02/04 10:11:46 chope Exp $
//$Authors
//       F. Deshaies CSSI
//       O. Queyrut  CSSI 
//       Copyright (C) CNES 2000
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#ifdef HAVE_STL
#include <string>
#endif

#include "club/DataFile.h"
#include "club/StructureFile.h"

// include header file if needed and set default type of file
#ifdef HAVE_XERCES_C
#include "club/XMLData.h"
#define DEFAULT_FILE_TYPE XMLType
#endif // HAVE_XERCES_C

#ifdef HAVE_MADONA
#include "club/MadonaFile.h"
#ifndef DEFAULT_FILE_TYPE
#define DEFAULT_FILE_TYPE MadonaType
#endif // !DEFAULT_FILE_TYPE
#endif // HAVE_MADONA

#ifndef DEFAULT_FILE_TYPE
#define DEFAULT_FILE_TYPE StructureType
#endif // !DEFAULT_FILE_TYPE

// static type of file manipulated
FileType DataFile::currentFileType_ = DEFAULT_FILE_TYPE;  

static void deleteDataFileFunction (void * memory, void *arg)
{ ((DataFile *)arg)->deleteDataFile(memory); }

UniqDataFile* DataFile::getUniqDataFile ()
{ return (UniqDataFile *) sharedUniqDataFile_.memoire (); }

// function who determine the type of the file
static FileType checkFileType (const string& fileName);


// CONSTRUCTOR & DESTRUCTOR

// construction by using static member currentFileType_
DataFile::DataFile () throw (ClubErreurs)
{
  UniqDataFile * uniqDataFile = 0;
  FileType type = getCurrentFileType();

  switch (type)
  {
    case StructureType:
        uniqDataFile = new StructureFile ();
        fileType_ = StructureType;
      break;
      
    case MadonaType:
#ifdef HAVE_MADONA
        uniqDataFile = new  MadonaFile ();
        fileType_ = MadonaType;
      break;
#else
      throw ClubErreurs (ClubErreurs::no_madona_lib);
#endif
      
    case XMLType:
#ifdef HAVE_XERCES_C
        uniqDataFile = new  XMLData ();
        fileType_ = XMLType;
      break;
#else
      throw ClubErreurs (ClubErreurs::no_xerces_lib);
#endif

    default :
        fileType_ = UnknownType;
        throw ClubErreurs (ClubErreurs::unknown_file_type);        
      break;
  }

  sharedUniqDataFile_ = TamponPartage (uniqDataFile, deleteDataFileFunction, (void *) this);
}


// construction by specifying file type to use 
// (use it for create a file with a specific type)
DataFile::DataFile (FileType type) throw (ClubErreurs)
{
  UniqDataFile * uniqDataFile = 0;
  switch (type)
  {
    case StructureType:
        uniqDataFile = new StructureFile ();
        fileType_ = StructureType;
      break;
      
    case MadonaType:
#ifdef HAVE_MADONA
        uniqDataFile = new  MadonaFile ();
        fileType_ = MadonaType;
      break;
#else
      throw ClubErreurs (ClubErreurs::no_madona_lib);
#endif
      
    case XMLType:
#ifdef HAVE_XERCES_C
        uniqDataFile = new  XMLData ();
        fileType_ = XMLType;
      break;
#else
      throw ClubErreurs (ClubErreurs::no_xerces_lib);
#endif

    default :
        fileType_ = UnknownType;
        throw ClubErreurs (ClubErreurs::unknown_file_type);        
     break;

  }

  sharedUniqDataFile_ = TamponPartage (uniqDataFile, deleteDataFileFunction, (void *) this);
}


// construction by checking file type
// (use it for open an existing file)
DataFile::DataFile (const string& fileName) throw (ClubErreurs)
{
  UniqDataFile * uniqDataFile = 0;

  // determine file type
  FileType type = checkFileType(fileName);

  switch (type)
  {
    case StructureType:
        uniqDataFile = new StructureFile ();
        fileType_ = StructureType;
      break;
      
    case MadonaType:
#ifdef HAVE_MADONA
        uniqDataFile = new  MadonaFile ();
        fileType_ = MadonaType;
      break;
#else
      throw ClubErreurs (ClubErreurs::no_madona_lib);
#endif
      
    case XMLType:
#ifdef HAVE_XERCES_C
        uniqDataFile = new  XMLData ();
        fileType_ = XMLType;
      break;
#else
      throw ClubErreurs (ClubErreurs::no_xerces_lib);
#endif

    default : // unusefull
        fileType_ = UnknownType;
        throw ClubErreurs (ClubErreurs::unknown_file_type);        
      break;

  }

  sharedUniqDataFile_ = TamponPartage (uniqDataFile, deleteDataFileFunction, (void *) this);
}


const FileType DataFile::getCurrentFileType () 
  throw (ClubErreurs)
{return currentFileType_;}


void DataFile::setCurrentFileType (const FileType fileTypeToUse) 
  throw (ClubErreurs)
{ currentFileType_ = fileTypeToUse; }


const FileType DataFile::getFileType () 
  throw (ClubErreurs)
{return fileType_;}


static FileType checkFileType (const string& fileName)
{
  FileType type = UnknownType;

  // As XML and Madona files have tag, we try to parse those type before

#ifdef HAVE_XERCES_C
  try
  {
    // try to parse a XML file
    UniqDataFile * uniqDataFile = 0;
    uniqDataFile = new  XMLData ();
    uniqDataFile->readFile(fileName);
    delete(uniqDataFile);
    type = XMLType;
  }
  catch (ClubErreurs ce)
  {
    // if file not found : exit
    if (ce.code() == ClubErreurs::ouverture_fichier)
      throw;

    // Handle error
    ce.correction();
  }
  catch (...)
  {
    // there was a problem : the file filename is not a XML one
  }    
#endif

  if (type != XMLType)
  {
#ifdef HAVE_MADONA
      try
      {
        // try to parse a Madona file
        UniqDataFile * uniqDataFile = 0;
        uniqDataFile = new  MadonaFile ();
        uniqDataFile->readFile(fileName);
        delete(uniqDataFile);
        type = MadonaType;
      }
      catch (ClubErreurs ce)
      {
        // if file not found : exit
        if (ce.code() == ClubErreurs::ouverture_fichier)
          throw;        

        // Handle error
        ce.correction();
      }
      catch (...)
      {
        // there was a problem : the file filename is not a Madona one
      }
#endif  
      if (type != MadonaType)
      {
         UniqDataFile * uniqDataFile = 0;
         uniqDataFile = new  StructureFile ();
         try
          {
            // try to parse a Structure file
            uniqDataFile->readFile(fileName);
            type = StructureType;
          }
            // there was a problem : type of file filename is unknown
          catch (ClubErreurs ce)
          {
            // if file not found : exit
            if (ce.code() == ClubErreurs::ouverture_fichier)
              throw;        

            // Handle error
            ce.correction();
            // file type is not structure, Madona or XML
            throw ClubErreurs (ClubErreurs::unknown_file_type);        
          }
          catch(...)
          {
            // file type is not structure, Madona or XML
            throw ClubErreurs (ClubErreurs::unknown_file_type);        
          }
          delete(uniqDataFile);
      }
  }

  return(type);
}

void DataFile::deleteDataFile(void *memory)
{
  switch(fileType_)
  {
    case StructureType:
        delete (StructureFile *) memory;
      break;
      
    case MadonaType:
#ifdef HAVE_MADONA
        delete (MadonaFile *) memory;
      break;
#endif
      
    case XMLType:
#ifdef HAVE_XERCES_C
        delete (XMLData *) memory;
      break;
#endif

    default :
      // do nothing (happens only if instance was not built properly)
      break;
  }
}
