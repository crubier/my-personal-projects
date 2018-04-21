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
//       fichier d'implantation de la classe Datafile
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//
//$Historique
//       $Log:
//
//$Version
//       $Id: 
//$Auteur
//        F. Auguie CSSI 
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
#include "club/DataFile.h"

// ------------------------------------- METHODES ---------------------------------------

void writeCurrentFileType(DataFile& dataf)
{

  FileType current = dataf.getCurrentFileType();

  switch(current)
  {

    case StructureType:
      cout << "StructureType" << endl;
      break;
      
    case MadonaType:
      cout << "MadonaType" << endl;
      break;

    case XMLType:
      cout << "XMLType" << endl;
      break;

    default :
      cout << "!! Inconnu !!" << endl;
      break;
  }
}
void writeFileType(DataFile& dataf)
{

  FileType current = dataf.getFileType();

  switch(current)
  {

    case StructureType:
      cout << "StructureType" << endl;
      break;
      
    case MadonaType:
      cout << "MadonaType" << endl;
      break;

    case XMLType:
      cout << "XMLType" << endl;
      break;

    default :
      cout << "!! Inconnu !!" << endl;
      break;
  }
}

// ---------------------------------------- MAIN ----------------------------------------

int main (int argc, char **argv)
{
  try 
  {

  if (argc != 2)
  {
    cerr << "prgm_DataFile rep" << endl;
    return 1;
  }
  string directory = argv[1];

  // CAS NOMINAUX 
  // ------------               
    cout << endl << " -------------- ";
    cout << endl << "| CAS NOMINAUX |";
    cout << endl << " -------------- " << endl;

  //- INSTANCIATION POUR LA CREATION DE FICHIERS -

    cout << endl << endl << "INSTANCIATIONS POUR LA CREATION DE FICHIERS";
    cout << endl << "-------------------------------------------" << endl;

#ifdef HAVE_MADONA
    cout << endl << "Creation d'une instance pour un fichier Madona en donnant le type du fichier : ";
    try 
    {
      DataFile datafile(MadonaType);
      cout << "OK" << endl;

      cout << endl << " Type de fichier pour cette instance : ";
      writeFileType(datafile);

      cout << endl << " Type courant de fichier utilise : ";
      writeCurrentFileType(datafile);

      cout << endl << " Mise a MadonaType du type courant de fichier utilise : "<< endl;
      datafile.setCurrentFileType(MadonaType);

      cout << endl << " Verification du type courant de fichier utilise : ";
      writeCurrentFileType(datafile);
    }
    catch (ClubErreurs ce)
    {
      cout << "!! Erreur club lors des instanciations pour la creation du 1er fichier Madonna !!" << endl; 
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "!! Erreur inconnue lors des instanciations pour la creation du 1er fichier Madonna !!" << endl; 
    }
    
    cout << endl << "Creation d'une instance pour un fichier Madona a partir du constructeur par defaut (currentFileType_) : ";
    try 
    {
      DataFile datafile;
      cout << "OK" << endl;

      cout << endl << " Type de fichier pour cette instance : ";
      writeFileType(datafile);
    }
    catch (ClubErreurs ce)
    {
      cout << "!! Erreur club lors des instanciations pour la creation du 2eme fichier Madonna !!" << endl; 
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "!! Erreur inconnue lors des instanciations pour la creation du 2eme fichier Madonna !!" << endl; 
    }
#endif

#ifdef HAVE_XERCES_C
    cout << endl << "Creation d'une instance pour un fichier XML en donnant le type du fichier : ";
    try 
    {
      DataFile datafile(XMLType);
      cout << "OK" << endl;

      cout << endl << " Type de fichier pour cette instance : ";
      writeFileType(datafile);

      cout << endl << " Type courant de fichier utilise : ";
      writeCurrentFileType(datafile);

      cout << endl << " Mise a XMLType du type courant de fichier utilise : "<< endl;
      datafile.setCurrentFileType(XMLType);

      cout << endl << " Consultation du type courant de fichiers utilise : ";
      writeCurrentFileType(datafile);

    }
    catch (ClubErreurs ce)
    {
      cout << "!! Erreur club lors de l'instanciation pour la creation du 1er fichier XML !!" << endl;  
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "!! Erreur inconnue lors de l'instanciation pour la creation du 1er fichier XML !!" << endl; 
    }

    cout << endl << "Creation d'une instance pour un fichier XML a partir du constructeur par defaut (currentFileType_) : ";
    try 
    {
      DataFile datafile;
      cout << "OK" << endl;

      cout << endl << " Type de fichier pour cette instance : ";
      writeFileType(datafile);
    }
    catch (ClubErreurs ce)
    {
      cout << "!! Erreur club lors de l'instanciation pour la creation du 2eme fichier XML !!" << endl;  
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "!! Erreur inconnue lors de l'instanciation pour la creation du 2eme fichier XML !!" << endl; 
    }
#endif

     cout << endl << "Creation d'une instance pour un fichier structure en donnant le type du fichier : ";
    try 
    {
      DataFile datafile(StructureType);
      cout << "OK" << endl;

      cout << endl << " Type de fichier pour cette instance : ";
      writeFileType(datafile);

      cout << endl << " Type courant de fichier utilise : ";
      writeCurrentFileType(datafile);

      cout << endl << " Mise a StructureType du type courant de fichier utilise : "<< endl;
      datafile.setCurrentFileType(StructureType);

      cout << endl << " Consultation du type courant de fichiers utilise : ";
      writeCurrentFileType(datafile);

    }
    catch (ClubErreurs ce)
    {
      cout << "!! Erreur club lors de l'instanciation pour la creation du 1er fichier structure !!" << endl; 
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "!! Erreur inconnue lors de l'instanciation pour la creation du 1er fichier structure !!" << endl; 
    }

    cout << endl << "Creation d'une instance pour un fichier structure a partir du constructeur par defaut (currentFileType_) : ";
    try 
    {
      DataFile datafile;
      cout << "OK" << endl;

      cout << endl << " Type de fichier pour cette instance : ";
      writeFileType(datafile);
    }
    catch (ClubErreurs ce)
    {
      cout << "!! Erreur club lors de l'instanciation pour la creation du 2eme fichier structure !!" << endl;  
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "!! Erreur inconnue lors de l'instanciation pour la creation du 2eme fichier structure !!" << endl; 
    }


  //- INSTANCIATION POUR LA LECTURE DE FICHIERS -
  //---------------------------------------------

    cout << endl << endl << "INSTANCIATIONS POUR LA LECTURE DE FICHIERS";
    cout << endl << "------------------------------------------" << endl;

    string filename = directory + "/test_StructureFile.don";
    cout << endl << "Lecture du fichier " << filename << " : ";


    try 
    {
      DataFile datafile(filename);
      cout << "OK" << endl;

      cout << endl << " Type de fichier pour cette instance : ";
      writeFileType(datafile);
    }
    catch (ClubErreurs ce)
    {
      cout << "!! Erreur club lors de l'instanciation pour la lecture du fichier structure !!" << endl;
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "!! Erreur inconnue lors de l'instanciation pour la lecture du fichier structure !!" << endl;
    }
   
#ifdef HAVE_MADONA    
    filename = directory + "/test_MadonaFile.don1";
    cout << endl << "Lecture du fichier " << filename << " : ";

    try 
    {
      DataFile datafile(filename);
      cout << "OK" << endl;

      cout << endl << " Type de fichier pour cette instance : ";
      writeFileType(datafile);
    }
    catch (ClubErreurs ce)
    {
      cout << "!! Erreur club lors de l'instanciation pour la lecture du fichier Madona !!" << endl;
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "!! Erreur inconnue lors de l'instanciation pour la lecture du fichier Madona !!" << endl;
    }
#endif

#ifdef HAVE_XERCES_C
    filename = directory + "/test_XMLData.don1";
    cout << endl << "Lecture du fichier XML " << filename << " : ";


    try 
    {
      DataFile datafile(filename);
      cout << "OK" << endl;

      cout << endl << " Type de fichier pour cette instance : ";
      writeFileType(datafile);
     }
    catch (ClubErreurs ce)
    {
      cout << "!! Erreur club lors de l'instanciation pour la lecture du fichier XML !!" << endl;
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "!! Erreur inconnue lors de l'instanciation pour la lecture du fichier XML !!" << endl;
    }
#endif

  // CAS DEGRADES 
  // ------------
    cout << endl << " -------------- ";
    cout << endl << "| CAS DEGRADES |";
    cout << endl << " -------------- " << endl;

    // Si le type de fichier n'existe pas :
    cout << endl << "Le type de fichier demande n'existe pas : ";
          
    try 
    {
      FileType unknownFileType = UnknownType;

      DataFile datafile(unknownFileType);
      cout << "KO" << endl;

      cout << endl << " Exception non levee : ";
      writeFileType(datafile);
     }
    catch (ClubErreurs ce)
    {
      cout << "OK : message d'erreur club :" << endl;
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "OK : exception inconnue !!" << endl;
    }

    // Si le fichier n'existe pas :
    filename = "NoFile.txt";
    cout << endl << "Le fichier " << filename << " n'existe pas : ";          

    try 
    {
      DataFile datafile(filename);
      cout << "KO" << endl;

      cout << endl << " Exception non levee : ";
      writeFileType(datafile);
     }
    catch (ClubErreurs ce)
    {
      cout << "OK : message d'erreur club :" << endl;
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "OK : exception inconnue !!" << endl;
    }

    // Si le format du fichier ne correspond pas a 1 des 3 attendus :
    filename = "Makefile";
    cout << endl << "Le format du fichier " << filename << " n'est pas valide : ";
          
    try 
    {
      DataFile datafile(filename);
      cout << "KO" << endl;

      cout << endl << " Exception non levee : ";
      writeFileType(datafile);
     }
    catch (ClubErreurs ce)
    {
      cout << "OK : message d'erreur club :" << endl;
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "OK : exception inconnue !!" << endl;
    }

#ifdef HAVE_XERCES_C
    // Si le fichier est au format XML mais qu'il ne respecte pas la DTD :
    filename = directory + "/test_DataFile_BadXmlF";
    cout << endl << "Le fichier " << filename << " ne respecte pas la DTD : ";
          

    try 
    {
      DataFile datafile(filename);
      cout << "KO" << endl;

      cout << endl << " Exception non levee : ";
      writeFileType(datafile);
     }
    catch (ClubErreurs ce)
    {
      cout << "OK : message d'erreur club :" << endl;
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "OK : exception inconnue !!" << endl;
    }
#endif

#ifdef HAVE_MADONA    
    // Si le fichier au format Madonna est invalide :
    filename = directory + "/test_DataFile_BadMadF";
    cout << endl << "Le fichier " << filename << " est invalide : ";
          

    try 
    {
      DataFile datafile(filename);
      cout << "KO" << endl;

      cout << endl << " Exception non levee : ";
      writeFileType(datafile);
     }
    catch (ClubErreurs ce)
    {
      cout << "OK : message d'erreur club :" << endl;
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "OK : exception inconnue !!" << endl;
    }
#endif

    // Si le fichier au format Structure est invalide :
    filename = directory + "/test_DataFile_BadSF";
    cout << endl << "Le fichier " << filename << " est invalide : ";
          

    try 
    {
      DataFile datafile(filename);
      cout << "KO" << endl;

      cout << endl << " Exception non levee : ";
      writeFileType(datafile);
     }
    catch (ClubErreurs ce)
    {
      cout << "OK : message d'erreur club :" << endl;
      cout << ce.why () << endl;
      ce.correction ();
    }
    catch (...)
    {
      cout << "OK : exception inconnue !!" << endl;
    }

    return 0;
  }

  // pour l'instant inutile !! 
  catch (...)
  {
    cout << "!! Il y a des erreurs !!" << endl; 
  }
}
