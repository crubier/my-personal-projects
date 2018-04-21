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
//       $Log: prgm_StructureFile.cpp,v $
//       Revision 3.9  2005/02/21 12:58:05  chope
//       élimination d'inclusions inutiles
//
//       Revision 3.8  2005/02/04 10:26:31  chope
//       élimination de l'utilisation des classes Proxy (DM-ID 241)
//
//       Revision 3.7  2000/11/09 10:49:29  club
//       Mise à jour des programmes de test (inclusions) vis à vis de la
//       séparations des fichiers UniqDataFile.cc et UniqDataFile.h
//       (pour avoir un fichier par classe).
//       Modification du programme de test de MadonaFile de façon à
//       fonctionner sous linux (lors de l'appel à writeFile (..), le nom
//       du fichier générait un 'segmentation fault').
//
//       Revision 3.6  2000/10/25 09:10:39  club
//       modification des includes du standard C++ : suppression du ".h"
//       dans le nom du fichier inclus.
//
//       Revision 3.5  2000/10/24 14:23:12  club
//       ajout de l'include ClubConfig.h et des tests de configuration.
//
//       Revision 3.4  2000/10/24 08:36:33  club
//       ajout de l'include src/ClubConfig.h et modification des includes du
//       standard C : utilisation des includes du type cNAME au lieu de NAME.h
//       pour permettre la compilation avec le Sun Workshop 5.0
//
//       Revision 3.3  2000/10/23 13:54:23  club
//       modification du programme de test pour corriger un warning lors de la
//       compilation.
//
//       Revision 3.2  2000/10/19 14:46:14  club
//       modification des tests pour pouvoir les exécuter à distance.
//
//       Revision 3.1  2000/10/18 08:36:35  club
//       Initial revision.
//
//$Version
//       $Id: prgm_StructureFile.cpp,v 3.9 2005/02/21 12:58:05 chope Exp $
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
#include "club/StructureFile.h"

//Current data pointer must be at root element.
void testDataExists (StructureFile* sf)
{
  //--------------- DATA EXISTS  -------------------------------
  cout << endl << "Try to test the existence of data" << endl;
  try 
  {
    bool value = sf->dataExists ("Integer1");
    cout << "OK : Test 1 - must be true : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    bool value = sf->dataExists ("String1");
    cout << "OK : Test 2 - must be true : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }

  try 
  {
    sf->moveTo ("Structure1.Table1");
    bool value = sf->dataExists (1);
    cout << "OK : Test 3 - must be true : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }


  try 
  {
    sf->moveTo ("");
    bool value = sf->dataExists ("unknown_data");
    cout << "OK : Test 4 - must be false : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  }
  cout << sf->getCurrentData () << endl;
}


void testMoveIntoData (StructureFile* sf)
{
  


  //--------------- MOVEDOWN  -------------------------------
  cout << endl << "Try to move down" << endl;
  try 
  {
    sf->moveDown ("Structure1");
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    sf->moveDown ("unknownStructure");
    cout << "KO : Test 2 - must be ClubErreurs::undefined_table_or_structure" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::undefined_table_or_structure " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    sf->moveDown ("[0]");
    cout << "KO : Test 3 - must be ClubErreurs::undefined_table_or_structure" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 3 - must be ClubErreurs::undefined_table_or_structure : " << ce.why () << endl; 
    ce.correction ();
  }
  try {
    sf->moveDown ("Table1");
    cout << "OK : Test 4" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  }
  try {
    sf->moveDown ("[0]");
    cout << "KO : Test 5 - must be ClubErreurs:undefined_table_or_structure" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 5 -  must be ClubErreurs::undefined_table_or_structure : " << ce.why () << endl; 
    ce.correction ();
  }
  try {
    sf->moveDown ("[4]");
    cout << "KO : Test 6 - must be ClubErreurs::undefined_table_or_structure" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 6 -  must be ClubErreurs::undefined_table_or_structure : " << ce.why () << endl; 
    ce.correction ();
  }
  try {
    sf->moveDown ("[1]");
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
    string cd = sf->getCurrentData ();
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
    sf->moveUp ();
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    sf->moveUp ();
    cout << "OK : Test 2" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    sf->moveUp ();
    cout << "OK : Test 3" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    sf->moveUp ();
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
    sf->moveTo ("");
    cout << "OK : Test 1 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    sf->moveTo ("Structure1.Table1[1]");
    cout << "OK : Test 2 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    sf->moveTo ("Structure1.Table1[4]");
    cout << "KO : Test 3- must be ClubErreurs::undefined_structure_or_table " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 3 - must be ClubErreurs::undefined_structure_or_table : " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    sf->moveTo ("");
    cout << "OK : Test 4 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  } 

  //--------------- GET DATA TYPE  -------------------------------
  cout << endl << "Try to get the type of a of data" << endl;
  try 
  {
    sf->moveDown ("Integer1");
    UniqDataFile::DataType value = sf->getDataType (1);
    sf->moveUp ();
    cout << "OK : Test 1 - must be  "<< (int)UniqDataFile::ParameterType << " : " << (int)value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
    sf->moveUp ();
  }
  try 
  {
    UniqDataFile::DataType value = sf->getDataType ("Structure1");
    cout << "OK : Test 2 - must be  "<< (int)UniqDataFile::StructureType << " : " << (int)value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    UniqDataFile::DataType value = sf->getDataType ("Table2");
    cout << "OK : Test 3 - must be  "<< (int)UniqDataFile::TableType << " : " << (int)value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    UniqDataFile::DataType value = sf->getDataType ("unknown_data");
    cout << "KO : Test 4 - must be ClubErreurs::undefined_data  : "<< (int)value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 4 - must be ClubErreurs::undefined_data  " << ce.why () << endl; 
    ce.correction ();
  }

  //--------------- GETDATA  -------------------------------
  cout << endl << "Try to get data" << endl;
  try 
  {
    sf->moveDown ("Integer1");
    int value = sf->getIntData (1);
    sf->moveUp ();
    cout << "OK : Test 1 - must be 10 : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    int value = sf->getIntData ("Integer1");
    cout << "KO : Test 2 - must be ClubErreurs::undefined_parameter"<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::undefined_parameter : " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    sf->moveDown ("Integer1");
    int value = sf->getIntData ("[10]");
    cout << "KO : Test 3 - must be ClubErreurs::bloc_champ_inexistant"<< value << endl; 
    sf->moveUp ();
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 3 - must be ClubErreurs::bloc_champ_inexistant : " << ce.why () << endl; 
    ce.correction ();
    sf->moveUp ();
  }
 
  try 
  {
    sf->moveDown ("Real1");
    double value = sf->getRealData (1, "m");
    sf->moveUp ();
    cout << "OK : Test 4 - must be 5.5 : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    sf->moveDown ("String1");
    string value = sf->getStringData (1);
    sf->moveUp ();
    cout << "OK : Test 5 - must be Hello : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 5 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    string value = sf->getStringData ("[0]");
    cout << "KO : Test 6 - must be ClubErreurs::bloc_non_terminal  " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 6 - must be ClubErreurs::bloc_non_terminal : " << ce.why () << endl; 
    ce.correction ();
  } 

  try 
  {
    string value = sf->getStringData ("unknownData");
    cout << "KO : Test 7 - must be ClubErreurs::undefined_parameter " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 7 - must be ClubErreurs::undefined_parameter : " << ce.why () << endl; 
    ce.correction ();
  } 
}


void testDeleteData (StructureFile* sf)
{
  //--------------- DELETE DATA   -------------------------------
  cout << endl << "Try to delete data" << endl;
  try 
  {
    sf->moveTo ("Structure1.Table1");
    sf->deleteData (0);
    cout << "KO : Test 1 - must be ClubErreurs::not_implemented " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->deleteData ("unknown_data");
    cout << "KO : Test 2 - must be ClubErreurs::not_implemented " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->deleteData (1);
    cout << "KO : Test 3 - must be ClubErreurs::not_implemented " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 3 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->moveUp ();
    sf->deleteData ("Table1");
    cout << "KO : Test 4 - must be ClubErreurs::not_implemented " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 4 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
 

  try 
  {
    sf->moveUp ();
    sf->deleteData ("Structure1");
    cout << "KO : Test 5 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 5 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->deleteData ("Integer1");
    cout << "KO : Test 6 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 6 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->deleteData ("Real1");
    cout << "KO : Test 7 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 7 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->deleteData ("String1");
    cout << "KO : Test 8 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 8 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
}



void testCreateData (StructureFile* sf)
{
  //--------------- CREATE DATA   -------------------------------
  cout << endl << "Try to create data" << endl;
  try 
  {
    sf->moveTo ("");
    sf->createStructure ("Structure1");
    cout << "KO : Test 1 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->createStructure ("Structure1");
    cout << "KO : Test 2 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->moveDown ("Structure1");
    sf->createTable ("Table1", UniqDataFile::StructureTable, "");
    cout << "KO : Test 3 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 3 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->moveDown ("Table1");
    sf->createStructure ();
    cout << "KO : Test 4 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "0K : Test 4 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->createStructure ();
    cout << "KO : Test 5 - must be ClubErreurs::not_implemented "  << endl;
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 5 - must be ClubErreurs::not_implemented : "<< ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    sf->moveDown (1);
    sf->createIntData ("integer", 1);
    cout << "KO : Test 6 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 6 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->moveUp ();
    sf->createStructure ();
    sf->moveDown (2);
    sf->createIntData ("integer", 1);
    cout << "KO : Test 7 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 7 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }


  try 
  {
    sf->moveTo ("");
    sf->createRealData ("Real1", 5.5, "m");
    cout << "KO : Test 8 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 8 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->createIntData ("Integer1", 10);
    cout << "KO : Test 9 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 9 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    sf->createStringData ("String1", "Hello");
    cout << "KO : Test 10 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 10 - must be ClubErreurs::not_implemented : " << ce.why () << endl;
    ce.correction ();
  }
}


void testReadFile (StructureFile* sf, string fileName)
{
  //--------------- READFILE   -------------------------------
  cout << endl << "Try to read a file" << endl;
  try 
  {
    sf->readFile ("unknowMadonaFile");
    cout << "KO : Test 1 - must be ClubErreurs::file_error" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 must be ClubErreurs::file_error - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    sf->readFile (fileName);
    cout << "OK : Test 2"  << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
}

void testWriteFile (StructureFile* sf, string fileName)
{
  //--------------- READFILE   -------------------------------
  cout << endl << "Try to write a file" << endl;
  try 
  {
    sf->writeFile ("%*$=/ +^?");
    cout << "KO : Test 1 - must be ClubErreurs::not_implemented" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 - must be ClubErreurs::not_implemented : " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    sf->writeFile (fileName);
    cout << "KO : Test 2 - must be ClubErreurs::not_implemented"  << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::not_implemented : " << ce.why () << endl; 
    ce.correction ();
  }
}


int main (int argc, char **argv)
{
  // check the command line
  if (argc != 2)
  {
    cout << "prgm_StructureFile répertoire" << endl;
    return 1;
  }

  string directory = argv[1];
  string fileName = directory + "/test_StructureFile.don";

  //--------------- INSTANCIATION -------------------------------
  cout << endl << "Try to instanciate" << endl;
  try 

  {
    StructureFile *sf = new StructureFile ();
    cout << "OK : Test 1-" << endl; 

    testReadFile (sf, fileName);
    
    testDataExists (sf);
    
    testMoveIntoData (sf);
    
    testDeleteData (sf);
    
    testCreateData (sf);
    
    testWriteFile (sf, "toto.xml");  
    
    //--------------- FINALIZATION -------------------------------
    
    cout << endl << "Try to destruct" << endl;
    try 
    {
      delete sf;
      cout << "OK : Test 1" << endl; 
    }
    catch (ClubErreurs ce)
    {
      cout << "KO : Test 1" << ce.why () << endl; 
      ce.correction ();
    }
 
    return 0;
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 -" << ce.why () << endl; 
    ce.correction ();
  }
}
 
