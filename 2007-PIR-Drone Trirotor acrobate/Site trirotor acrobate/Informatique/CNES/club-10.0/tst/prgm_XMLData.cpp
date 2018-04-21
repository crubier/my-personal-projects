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
//       fichier de tests de la classe XMLData
//
//$Description
//       Module de test de la classe
//
//$Contenu
//
//$Historique
//       $Log: prgm_XMLData.cpp,v $
//       Revision 1.3  2005/02/25 07:57:45  chope
//       use a read only directory to trigger a reproducible error
//
//       Revision 1.1  2005/02/04 10:36:39  chope
//       initial version
//
//$Version
//       $Id: prgm_XMLData.cpp,v 1.3 2005/02/25 07:57:45 chope Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_STL
# include <string>
#endif

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/ClubErreurs.h"
#include "club/XMLData.h"

//Current data pointer must be at root element.
void testDataExists (XMLData* xf)
{
  //--------------- DATA EXISTS  -------------------------------
  cout << endl << "Try to test the existence of data" << endl;
  try 
  {
    bool value = xf->dataExists ("Integer1");
    cout << "OK : Test 1 - must be true :" << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    bool value = xf->dataExists ("String1");
    cout << "OK : Test 2 - must be true :" << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }

  try 
  {
    xf->moveTo ("Structure1.Table1");
    bool value = xf->dataExists (1);
    cout << "OK : Test 3 - must be true :" << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }


  try 
  {
    xf->moveTo ("");
    bool value = xf->dataExists ("unknown_data");
    cout << "OK : Test 4 - must be false :" << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  }
}


void testMoveIntoData (XMLData* xf)
{
  
  //--------------- GET DATA TYPE  -------------------------------
  cout << endl << "Try to get the type of a of data" << endl;
  try 
  {
    UniqDataFile::DataType value = xf->getDataType ("Integer1");
    cout << "OK : Test 1 - must be  " << (int) UniqDataFile::ParameterType << " : " << (int) value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    UniqDataFile::DataType value = xf->getDataType ("Structure1");
    cout << "OK : Test 2 - must be  " << (int) UniqDataFile::StructureType << " : " << (int) value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    UniqDataFile::DataType value = xf->getDataType ("Table2");
    cout << "OK : Test 3 - must be  "<< (int) UniqDataFile::TableType << " : " << (int) value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    UniqDataFile::DataType value = xf->getDataType ("unknown_data");
    cout << "KO : Test 4 - must be ClubErreurs::undefined_data  : " << (int) value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 4 - must be ClubErreurs::undefined_data  " << ce.why () << endl; 
    ce.correction ();
  }


  //--------------- MOVEDOWN  -------------------------------
  cout << endl << "Try to move down" << endl;
  try 
  {
    xf->moveDown ("Structure1");
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->moveDown ("unknownStructure");
    cout << "KO : Test 2 - must be ClubErreurs::undefined_table_or_structure" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::undefined_table_or_structure " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->moveDown ("[0]");
    cout << "KO : Test 3 - must be ClubErreurs::current_data_not_a_table" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 3 - must be ClubErreurs::current_data_not_a_table : " << ce.why () << endl; 
    ce.correction ();
  }
  try
  {
    xf->moveDown ("Table1");
    cout << "OK : Test 4" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->moveDown ("[0]");
    cout << "KO : Test 5 - must be ClubErreurs::undefined_index" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 5 -  must be ClubErreurs::undefined_index : " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->moveDown ("[4]");
    cout << "KO : Test 6 - must be ClubErreurs::undefined_index" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 6 -  must be ClubErreurs::undefined_index : " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->moveDown ("[1]");
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
    string cd = xf->getCurrentData ();
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
    xf->moveUp ();
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->moveUp ();
    cout << "OK : Test 2" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->moveUp ();
    cout << "OK : Test 3" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->moveUp ();
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
    xf->moveTo ("");
    cout << "OK : Test 1 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    xf->moveTo ("Structure1.Table1[1]");
    cout << "OK : Test 2 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    xf->moveTo ("Structure1.Table1[4]");
    cout << "KO : Test 3- must be ClubErreurs::undefined_index " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 3 - must be ClubErreurs::undefined_index : " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    xf->moveTo ("");
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
    int value = xf->getIntData ("Integer1");
    cout << "OK : Test 1 - must be 10 : " << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    double value = xf->getRealData ("Real1", "m");
    cout << "OK : Test 2 - must be 5.5 : " << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    string value = xf->getStringData ("String1");
    cout << "OK : Test 3 - must be Hello : " << value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  } 
  try 
  {
    string value = xf->getStringData ("[0]");
    cout << "KO : Test 4 - must be ClubErreurs::current_data_not_a_table  " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 4 - must be ClubErreurs::current_data_not_a_table : " << ce.why () << endl; 
    ce.correction ();
  } 

  try 
  {
    string value = xf->getStringData ("unknownData");
    cout << "KO : Test 5 - must be ClubErreurs::undefined_parameter " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 5 - must be ClubErreurs::undefined_parameter : " << ce.why () << endl; 
    ce.correction ();
  } 
}


void testDeleteData (XMLData* xf)
{
  //--------------- DELETE DATA   -------------------------------
  cout << endl << "Try to delete data" << endl;
  try 
  {
    xf->moveTo ("Structure1.Table1");
    xf->deleteData (0);
    cout << "KO : Test 1 - must be ClubErreurs::undefined_index " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 - must be ClubErreurs::undefined_index : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->deleteData ("unknown_data");
    cout << "KO : Test 2 - must be ClubErreurs::undefined_data " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::undefined_data : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->deleteData (1);
    cout << "OK : Test 3" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3" << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->moveUp ();
    xf->deleteData ("Table1");
    cout << "OK : Test 4" << endl; 
  }

  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl;
    ce.correction ();
  }
 

  try 
  {
    xf->moveUp ();
    xf->deleteData ("Structure1");
    cout << "OK : Test 5" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 5 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->deleteData ("Integer1");
    cout << "OK : Test 6" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 6 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->deleteData ("Real1");
    cout << "OK : Test 7" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 7 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->deleteData ("String1");
    cout << "OK : Test 8" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 8 - " << ce.why () << endl;
    ce.correction ();
  }
}



void testCreateData (XMLData* xf)
{
  //--------------- CREATE DATA   -------------------------------
  cout << endl << "Try to create data" << endl;
  try 
  {
    xf->moveTo ("");
    xf->createStructure ("Structure1");
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->createStructure ("Structure1");
    cout << "KO : Test 2 - must be ClubErreurs::data_already_defined " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 2 - must be ClubErreurs::data_already_defined : " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->moveDown ("Structure1");
    xf->createTable ("Table1", UniqDataFile::StructureTable, "");
    cout << "OK : Test 3" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3" << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->moveDown ("Table1");
    xf->createStructure ();
    cout << "OK : Test 4" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "K0 : Test 4 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->createStructure ();
    cout << "OK : Test 5 "  << endl;
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 5 - "<< ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->moveDown (1);
    xf->createIntData ("integer", 1);
    cout << "OK : Test 6" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 6 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->moveUp ();
    xf->createStructure ();
    xf->moveDown (2);
    xf->createIntData ("integer", 1);
    cout << "OK : Test 7" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 7 - " << ce.why () << endl;
    ce.correction ();
  }


  try 
  {
    xf->moveTo ("");
    xf->createRealData ("Real1", 5.5, "m");
    cout << "OK : Test 8" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 8 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->createIntData ("Integer1", 10);
    cout << "OK : Test 9" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 9 - " << ce.why () << endl;
    ce.correction ();
  }
  try 
  {
    xf->createStringData ("String1", "Hello");
    cout << "OK : Test 10" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 10 - " << ce.why () << endl;
    ce.correction ();
  }
}


void testReadFile (XMLData* xf, string fileName)
{
  //--------------- READFILE   -------------------------------
  cout << endl << "Try to read a file" << endl;
  try 
  {
    xf->readFile ("unknowMadonaFile");
    cout << "KO : Test 1 - must be ClubErreurs::file_error" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 must be ClubErreurs::file_error - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->readFile (fileName);
    cout << "OK : Test 2"  << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
}

void testWriteFile (XMLData* xf, string fileName)
{
  //--------------- READFILE   -------------------------------
  cout << endl << "Try to write a file" << endl;
  try 
  {
    xf->writeFile ("read-only-dir/file.xml");
    cout << "KO : Test 1 - must be ClubErreurs::file_error" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "OK : Test 1 must be ClubErreurs::file_error - " << ce.why () << endl; 
    ce.correction ();
  }
  try 
  {
    xf->writeFile (fileName);
    cout << "OK : Test 2"  << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
}

void testCreateTableOfTables (XMLData * xf)
{
  cout << endl << "Try to create a table of tables" << endl;
  try
  {
    xf->moveTo ("");
    xf->createTable ("Table3", UniqDataFile::TableTable, "");
    cout << "OK : Test 1 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 - " << ce.why () << endl; 
    ce.correction ();
  }
 
  try
  {
    xf->moveDown ("Table3");
    xf->createTable (UniqDataFile::TableTable, "");
    cout << "OK : Test 2 - must be Table3 : " << xf->getCurrentData () << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - " << ce.why () << endl; 
    ce.correction ();
  }
 
  try
  { 
    xf->moveDown (1);
    cout << "OK : Test 3 - must be Table3[1] : " << xf->getCurrentData () <<endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - " << ce.why () << endl; 
    ce.correction ();
  }
 
  try
  { 
    xf->createTable (UniqDataFile::RealTable, "");
    xf->moveDown (1);
    cout << "OK : Test 4 - must be Table3[1][1] : " << xf->getCurrentData () <<endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - " << ce.why () << endl; 
    ce.correction ();
  }
 
  try
  {
    xf->createRealData (5.5, "");
    cout << "OK : Test 4.5 - must be Table3[1][1] "<< xf->getCurrentData ()  << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4.5 - " << ce.why () << endl; 
    ce.correction ();
  }
 
  try
  { 
    xf->createRealData (10.0, "");
    cout << "OK : Test 5 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 5 - " << ce.why () << endl; 
    ce.correction ();
  }
 
  try
  {
    xf->moveUp ();
    xf->createTable (UniqDataFile::RealTable, "");
    cout << "OK : Test 6 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 6 - " << ce.why () << endl; 
    ce.correction ();
  }
 
  try
  { 
    xf->moveDown (2);
    cout << "OK : Test 7 - must be Table3[1][2] : " << xf->getCurrentData () <<endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 7 - " << ce.why () << endl; 
    ce.correction ();
  }
 
  try
  { 
    xf->createRealData (6.3, "");
    cout << "OK : Test 8 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 8 - " << ce.why () << endl; 
    ce.correction ();
  }

  try
  { 
    xf->createRealData (7.8, "");
    cout << "OK : Test 9 " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 9 - " << ce.why () << endl; 
    ce.correction ();
  }
}





void testReference (XMLData* xf, 
                    const string& referencedFileName)
{
  cout << endl << "Try to reference data" << endl;
  try
  {
    xf->moveTo ("");
    xf->createReference ("Reference1", referencedFileName, "Structure1");
    cout << "OK : Test 1" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 1 : " << ce.why () << endl; 
    ce.correction ();
  }

  try
  {
    xf->moveTo ("Reference1");
    cout << "OK : Test 2 "<< endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 2 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try
  {
    xf->moveDown ("Table1");
    cout << "OK : Test 3  " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 3 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try
  {
    xf->moveDown (1);
    cout << "OK : Test 4  " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 4 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try {
    int value = xf->getIntData ("integer");
    cout << "OK : Test 5  - must be 1 : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 5 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try{
    xf->setIntData ("integer", 2);
    cout << "OK : Test 6  " << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 6 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try {
    int value = xf->getIntData ("integer");
    cout << "OK : Test 7  - must be 2 : "<< value << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 7 - "<< ce.why () << endl; 
    ce.correction ();
  }

  try {
    xf->moveUp ();
    xf->deleteData (3);
    cout << "OK : Test 8" << endl; 
  }
  catch (ClubErreurs ce)
  {
    cout << "KO : Test 8 "<< ce.why () << endl; 
    ce.correction ();
  }
} 


int main (int argc, char **argv)
{
  // check the command line
  if (argc != 4)
  {
    cout << "prgm_XMLData inputFile referencedFile outputFile" << endl;
    return 1;
  }
  string inputFileName      = argv[1];
  string referencedFileName = argv[2];
  string outputFileName     = argv[3];


  //--------------- INSTANCIATION -------------------------------
  cout << endl << "Try to instanciate" << endl;
  try 

  {
    XMLData* xf = new XMLData ();
    cout << "OK : Test 1-" << endl; 

    testReadFile (xf, inputFileName);
    
    testDataExists (xf);
    
    testMoveIntoData (xf);

    testDeleteData (xf);
    
    testCreateData (xf);
    
    testDataExists (xf);
    
    testMoveIntoData (xf);
    
    testCreateTableOfTables (xf);
    
    testReference (xf, referencedFileName);

    testWriteFile (xf, outputFileName);
    
    
    
    //--------------- FINALIZATION -------------------------------
    
    cout << endl << "Try to destruct" << endl;
    try 
    {
      delete xf;
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
