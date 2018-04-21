////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Bibam
//$Application
//        Club
//$Nom
//
//$Resume
//       fichier d'implantation de la classe XXXX
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//
//$Historique
//       $Log: prgm_MadonaFile.cpp,v $
//       Revision 3.8  2005/02/21 12:58:38  chope
//       élimination d'inclusions inutiles
//
//       Revision 3.7  2005/02/04 10:21:38  chope
//       élimination du test de chargement des unités (DM-ID 242)
//
//       Revision 3.6  2000/11/09 10:49:28  club
//       Mise à jour des programmes de test (inclusions) vis à vis
//       de la séparations des fichiers UniqDataFile.cc et UniqDataFile.h
//       (pour avoir un fichier par classe).
//       Modification du programme de test de MadonaFile de façon à
//       fonctionner sous linux (lors de l'appel à writeFile (..), le nom
//       du fichier générait un 'segmentation fault').
//
//       Revision 3.5  2000/10/25 09:10:39  club
//       modification des includes du standard C++ : suppression du ".h"
//       dans le nom du fichier inclus.
//
//       Revision 3.4  2000/10/24 14:23:11  club
//       ajout de l'include ClubConfig.h et des tests de configuration.
//
//       Revision 3.3  2000/10/23 13:54:23  club
//       modification du programme de test pour corriger un warning lors de la
//       compilation.
//
//       Revision 3.2  2000/10/19 14:46:13  club
//       modification des tests pour pouvoir les exécuter à distance.
//
//       Revision 3.1  2000/10/18 08:36:35  club
//       Initial revision.
//
//$Version
//       $Id: prgm_MadonaFile.cpp,v 3.8 2005/02/21 12:58:38 chope Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_STL
#include <string>
#endif

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/ClubErreurs.h"
#include "club/MadonaFile.h"


//Current data pointer must be at root element.
void testDataExists (MadonaFile* mf)
{
 //--------------- DATA EXISTS  -------------------------------
  cout << endl << "Try to test the existence of data" << endl;
  try 
  {
    bool value = mf->dataExists ("Integer1");
    cout << "OK : Test 1 - must be true :" << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    bool value = mf->dataExists ("String1");
    cout << "OK : Test 2 - must be true :" << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }

  try 
  {
    mf->moveTo ("Structure1.Table1");
    bool value = mf->dataExists (1);
    cout << "OK : Test 3 - must be true :" << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }


  try 
  {
    mf->moveTo ("");
    bool value = mf->dataExists ("unknown_data");
    cout << "OK : Test 4 - must be false :" << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  }
}


void testMoveIntoData (MadonaFile* mf)
{
  
  //--------------- GET DATA TYPE  -------------------------------
  cout << endl << "Try to get the type of a of data" << endl;
  try 
  {
    UniqDataFile::DataType value = mf->getDataType ("Integer1");
    cout << "OK : Test 1 - must be  "<< (int) UniqDataFile::ParameterType << " : " << (int) value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    UniqDataFile::DataType value = mf->getDataType ("Structure1");
    cout << "OK : Test 2 - must be  "<< (int) UniqDataFile::StructureType << " : " << (int) value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    UniqDataFile::DataType value = mf->getDataType ("Table2");
    cout << "OK : Test 3 - must be  "<< (int) UniqDataFile::TableType << " : " << (int) value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    UniqDataFile::DataType value = mf->getDataType ("unknown_data");
    cout << "KO : Test 4 - must be ClubErreurs::undefined_data  : " << (int) value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 4 - must be ClubErreurs::undefined_data  " << ce.why () << endl; 
    ce.correction ();
  }

  cout << endl << "Try to manipulate comments" << endl;
  try 
  {
    string value = mf->getComment ("unknown_data");
    cout << "KO : Test 1 - must be ClubErreurs::undefined_data  : " << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 - must be ClubErreurs::undefined_data  " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    string comment = mf->getComment ("Integer1");
    cout << "OK : Test 2 - must be Comment (2 times):" << comment << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    string comment = mf->getComment ("Real1");
    cout << "OK : Test 3 - must be \"\" :" << comment << "."<< endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->setComment ("Real1", "new Comment");
    cout << "OK : Test 4  :" << "."<< endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    string comment = mf->getComment ("Real1");
    cout << "OK : Test 5 - must be \"new Comment\" :" << comment << "." << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 5 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->setComment ("Real1", "new Comment\nnew comment line2");
    cout << "OK : Test 6" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 6 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    string comment = mf->getComment ("Real1");
    cout << "OK : Test 7 - must be \"new Comment\\nnew comment line2\" :" << comment << "." << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 7 - " << ce.why () << endl; 
    ce.correction ();
  }

  //--------------- MOVEDOWN  -------------------------------
  cout << endl << "Try to move down" << endl;
  try 
  {
    mf->moveDown ("Structure1");
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveDown ("unknownStructure");
    cout << "KO : Test 2 - must be ClubErreurs::undefined_table_or_structure" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::undefined_table_or_structure : " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveDown ("[0]");
    cout << "KO : Test 3 - must be ClubErreurs::current_data_not_a_table" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 3 - must be ClubErreurs::current_data_not_a_table : " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveDown ("Table1");
    cout << "OK : Test 4" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveDown ("[0]");
    cout << "KO : Test 5 - must be ClubErreurs::undefined_index" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 5 -  must be ClubErreurs::undefined_index : " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveDown ("[4]");
    cout << "KO : Test 6 - must be ClubErreurs::undefined_index" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 6 -  must be ClubErreurs::undefined_index : " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveDown ("[1]");
    cout << "OK : Test 7" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 7 - " << ce.why () << endl; 
    ce.correction ();
  }
  
  //--------------- GET CURRENT DATA ----------------------
  cout << endl << "Try to get the name of the current data" << endl;
  try 
  {
     string cd = mf->getCurrentData ();
     cout << "OK : Test 1 - must be Structure1.table[1] : " << cd << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }

  

  //--------------- MOVEUP  -------------------------------
  cout << endl << "Try to move up" << endl;
  try 
  {
    mf->moveUp ();
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveUp ();
    cout << "OK : Test 2" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveUp ();
    cout << "OK : Test 3" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveUp ();
    cout << "KO : Test 4 - must be ClubErreurs::move_up_forbidden" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 4 -  must be ClubErreurs::move_up_forbidden : " << ce.why () << endl; 
    ce.correction ();
  }

   //--------------- MOVE TO  -------------------------------
  cout << endl << "Try to move to" << endl;
  try 
  {
    mf->moveTo ("");
    cout << "OK : Test 1 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    mf->moveTo ("Structure1.Table1[1]");
    cout << "OK : Test 2 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    mf->moveTo ("Structure1.Table1[4]");
    cout << "KO : Test 3- must be ClubErreurs::undefined_index " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 3 - must be ClubErreurs::undefined_index : " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    mf->moveTo ("");
    cout << "OK : Test 4 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  } 


   //--------------- GETDATA  -------------------------------
  cout << endl << "Try to get data" << endl;
  try 
  {
    int value = mf->getIntData ("Integer1");
    cout << "OK : Test 1 - must be 10 : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    double value = mf->getRealData ("Real1", "m");
    cout << "OK : Test 2 - must be 5.5 : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    string value = mf->getStringData ("String1");
    cout << "OK : Test 3 - must be Hello : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    string value = mf->getStringData ("[0]");
    cout << "KO : Test 4 - must be ClubErreurs::current_data_not_a_table  " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 4 - must be ClubErreurs::current_data_not_a_table : " << ce.why () << endl; 
    ce.correction ();
  } 

  try 
  {
    string value = mf->getStringData ("unknownData");
    cout << "KO : Test 5 - must be ClubErreurs::undefined_parameter " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 5 - must be ClubErreurs::undefined_parameter : " << ce.why () << endl; 
    ce.correction ();
  } 
}


void testDeleteData (MadonaFile* mf)
{
   //--------------- DELETE DATA   -------------------------------
  cout << endl << "Try to delete data" << endl;
  try {
    mf->moveTo ("Structure1.Table1");
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 0 - must be ClubErreurs::undefined_index : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->deleteData (0);
    cout << "KO : Test 1 - must be ClubErreurs::undefined_index " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 - must be ClubErreurs::undefined_index : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->deleteData ("unknown_data");
    cout << "KO : Test 2 - must be ClubErreurs::undefined_data " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::undefined_data : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->deleteData (1);
    cout << "OK : Test 3" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3" << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->moveUp ();
    mf->deleteData ("Table1");
    cout << "OK : Test 4" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl;
    ce.correction ();
  }

  try 
  {
    mf->moveUp ();
    mf->deleteData ("Structure1");
    cout << "OK : Test 5" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 5 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->deleteData ("Integer1");
    cout << "OK : Test 6" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 6 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->deleteData ("Real1");
    cout << "OK : Test 7" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 7 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->deleteData ("String1");
    cout << "OK : Test 8" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 8 - " << ce.why () << endl;
    ce.correction ();
  }
}



void testCreateData (MadonaFile* mf)
{
   //--------------- DELETE DATA   -------------------------------
  cout << endl << "Try to create data" << endl;
  try 
  {
    mf->moveTo ("");
    mf->createStructure ("Structure1");
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->createStructure ("Structure1");
    cout << "KO : Test 2 - must be ClubErreurs::data_already_defined " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::data_already_defined : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->moveDown ("Structure1");
    mf->createTable ("Table1", UniqDataFile::StructureTable, "");
    cout << "OK : Test 3" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3" << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->moveDown ("Table1");
    mf->createStructure ("[0]");
    cout << "KO : Test 4 - must be ClubErreurs::index_creation_forbidden - " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 4 - must be ClubErreurs::creation_index_forbidden - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    //on crée une structure d'index 1. 
    mf->createStructure ();
    cout << "OK : Test 5 "  << endl;
   }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 5 - "<< ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->moveDown (1);
    mf->createIntData ("integer", 1);
    cout << "OK : Test 6" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 6 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->moveUp ();
    //on crée une structure d'index 2. 
    mf->createStructure ();
    mf->moveDown (2);
    mf->createIntData ("integer", 1);
    cout << "OK : Test 7" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 7 - " << ce.why () << endl;
    ce.correction ();
  }

  try 
  {
    mf->moveTo ("");
    mf->createRealData ("Real1", 5.5, "m");
    cout << "OK : Test 8" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 8 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->createIntData ("Integer1", 10);
    cout << "OK : Test 9" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 9 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->setComment ("Integer1", "Comment\nComment");
    cout << "OK : Test 10" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 10 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->createStringData ("String1", "Hello");
    cout << "OK : Test 11" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 11 - " << ce.why () << endl;
    ce.correction ();
  }
}


void testReadFile (MadonaFile* mf, string fileName)
{
   //--------------- READFILE   -------------------------------
  cout << endl << "Try to read a file" << endl;
  try 
  {
    mf->readFile ("unknowMadonaFile");
    cout << "KO : Test 1 - must be ClubErreurs::file_error" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 must be ClubErreurs::file_error - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    mf->readFile (fileName);
    cout << "OK : Test 2"  << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
}

void testWriteFile (MadonaFile* mf, string fileName)
{
   //--------------- READFILE   -------------------------------
  cout << endl << "Try to write a file" << endl;
  try 
  {
    mf->writeFile ("^df$&/");
    cout << "KO : Test 1 - must be ClubErreurs::file_error" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 must be ClubErreurs::file_error - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    mf->writeFile (fileName);
    cout << "OK : Test 2"  << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
}

void testCreateTableOfTables (MadonaFile * mf)
{
 cout << endl << "Try to create a table of tables" << endl;
 try
 {
   mf->moveTo ("");
   mf->createTable ("Table3", UniqDataFile::TableTable, "");
   cout << "OK : Test 1 " << endl; 
 }
 catch (ClubErreurs ce)
 {
   cout << "KO : Test 1 - " << ce.why () << endl; 
   ce.correction ();
 }
 
 try
 {
   mf->moveDown ("Table3");
   //on crée un table à l'index 1. 
   mf->createTable (UniqDataFile::TableTable, "");
   cout << "OK : Test 2 - must be Table3 : " << mf->getCurrentData () << endl; 
 }
 catch (ClubErreurs ce)
 {
   cout << "KO : Test 2 - " << ce.why () << endl; 
   ce.correction ();
 }
 
 try
 { 
    mf->moveDown (1);
    cout << "OK : Test 3 - must be Table3[1] : " << mf->getCurrentData () <<endl; 
  }
 catch (ClubErreurs ce)
 {
   cout << "KO : Test 3 - " << ce.why () << endl; 
   ce.correction ();
 }
 
 try
  { 
    //on crée un table à l'index 1. 
    mf->createTable (UniqDataFile::RealTable, "");
    mf->moveDown (1);
    cout << "OK : Test 4 - must be Table3[1][1] : " << mf->getCurrentData () <<endl; 
  }
 catch (ClubErreurs ce)
 {
   cout << "KO : Test 4 - " << ce.why () << endl; 
   ce.correction ();
 }
 
 try
 {
   mf->createRealData (5.5, "");
   cout << "OK : Test 4.5 - must be Table3[1][1] "<< mf->getCurrentData ()  << endl; 
 }
 catch (ClubErreurs ce)
 {
   cout << "KO : Test 4.5 - " << ce.why () << endl; 
   ce.correction ();
 }
 
 try
 { 
   mf->createRealData (10.0, "");
   cout << "OK : Test 5 " << endl; 
 }
 catch (ClubErreurs ce)
 {
    cout << "KO : Test 5 - " << ce.why () << endl; 
    ce.correction ();
 }
 
 try
 {
   mf->moveUp ();
   //index 2
   mf->createTable (UniqDataFile::RealTable, "");
   cout << "OK : Test 6 " << endl; 
 }
 catch (ClubErreurs ce)
 {
   cout << "KO : Test 6 - " << ce.why () << endl; 
   ce.correction ();
 }
 
 try
  { 
    mf->moveDown (2);
    cout << "OK : Test 7 - must be Table3[1][2] : " << mf->getCurrentData () <<endl; 
  }
 catch (ClubErreurs ce)
 {
   cout << "KO : Test 7 - " << ce.why () << endl; 
   ce.correction ();
 }
 
 try
 { 
   mf->createRealData (6.3, "");
   cout << "OK : Test 8 " << endl; 
 }
 catch (ClubErreurs ce)
 {
   cout << "KO : Test 8 - " << ce.why () << endl; 
   ce.correction ();
 }

 try
 { 
   mf->createRealData (7.8, "");
   cout << "OK : Test 9 " << endl; 
 }
 catch (ClubErreurs ce)
 {
   cout << "KO : Test 9 - " << ce.why () << endl; 
   ce.correction ();
 }
}



void testReference (MadonaFile* mf, 
                    const string& referencedFileName)
{
  cout << endl << "Try to reference data" << endl;
  try
  {
    mf->moveTo ("");
    mf->createReference ("Reference1", referencedFileName, "Structure1");
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 : " << ce.why () << endl; 
    ce.correction ();
  }

  try
  {
    mf->moveTo ("Reference1");
    cout << "OK : Test 2 "<< endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try
  {
    mf->moveDown ("Table1");
    cout << "OK : Test 3  " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try
  {
    mf->moveDown (1);
    cout << "OK : Test 4  " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try {
    int value = mf->getIntData ("integer");
    cout << "OK : Test 5  - must be 1 : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 5 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try{
    mf->setIntData ("integer", 2);
    cout << "OK : Test 6  " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 6 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try {
    int value = mf->getIntData ("integer");
    cout << "OK : Test 7  - must be 2 : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 7 - "<< ce.why () << endl; 
    ce.correction ();
  }

} 


int main (int argc, char **argv)
{
// check the command line
  if (argc != 3)
  {
    cout << "prgm_MadonaFile répertoire <outputFile>" << endl;
    return 1;
  }

  string directory = argv[1];
  string inputFileName = directory + "/test_MadonaFile.don1";
  string referencedFileName = directory + "/test_MadonaFile.don2";
  string outputFileName = argv[2];

  //--------------- INSTANCIATION -------------------------------
  cout << endl << "Try to instanciate" << endl;
  try 
  { 
    MadonaFile* mf = new MadonaFile ();
    cout << "OK : Test 1-" << endl; 

    testReadFile (mf, inputFileName);
    
    testDataExists (mf);
    
    testMoveIntoData (mf);
    
    testDeleteData (mf);
    
    testCreateData (mf);
    
    testDataExists (mf);
    
    testMoveIntoData (mf);
    
    testWriteFile (mf, outputFileName);
    
    testCreateTableOfTables (mf);
    
    testReference (mf, referencedFileName);
    
    
    
    //--------------- FINALIZATION -------------------------------
    
    cout << endl << "Try to destruct" << endl;
    try 
    {
      delete mf;
      cout << "OK : Test 1" << endl; 
    }
    catch (ClubErreurs ce)
    {
      cout << "KO : Test 1 - " << ce.why () << endl; 
      ce.correction ();
    }
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 -" << ce.why () << endl; 
    ce.correction ();
  }
}
