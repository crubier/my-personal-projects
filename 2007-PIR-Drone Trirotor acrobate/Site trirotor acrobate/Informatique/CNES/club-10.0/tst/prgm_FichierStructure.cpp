////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//        DEF
//
//$Projet
//        CHOPE
//
//$Application
//        Club
//
//$Nom
//>       prgm_FichierStructure.cc
//
//$Resume
//       fichier d'implantation du test prgm_FichierStructure
//
//$Description
//       teste la classe FichierStructure
//
//$Contenu
//>       int main()                           
//>       static void ImprimeCaracteristiques()
//
//$Historique
//       $Log: prgm_FichierStructure.cpp,v $
//       Revision 3.14  2003/02/03 14:35:22  club
//       Changement du flux de sortie des erreurs sur la sortie standard pour prévenir des problèmes de flush sur différents systèmes
//
//       Revision 3.13  2002/06/27 15:51:59  club
//       ajout du test de la méthode listeSousBlocs
//
//       Revision 3.12  2001/06/21 15:23:33  club
//       correction d'une signature de directive catch
//
//       Revision 3.11  2000/10/25 09:10:39  club
//       modification des includes du standard C++ : suppression du ".h" dans le
//       nom du fichier inclus.
//
//       Revision 3.10  2000/10/24 14:23:11  club
//       ajout de l'include ClubConfig.h et des tests de configuration.
//
//       Revision 3.9  2000/10/24 08:36:33  club
//       ajout de l'include src/ClubConfig.h et modification des includes du
//       standard C : utilisation des includes du type cNAME au lieu de NAME.h
//       pour permettre la compilation avec le Sun Workshop 5.0
//
//       Revision 3.8  2000/09/07 08:35:52  club
//       utilisation de string de la STL au lieu de ChaineSimple.
//       mise à jour du cartouche.
//
//       Revision 3.7  1999/07/07 08:12:38  club
//       adaptation a la gestion des erreurs par
//       mecanisme d'exception.
//
//$Version
//       $Id: prgm_FichierStructure.cpp,v 3.14 2003/02/03 14:35:22 club Exp $
//$Auteur
//        P-A.Cros      CSSI
//        M. Julien     CSSI 
//        O. Queyrut    CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/FichierStructure.h"
#include "club/ClubErreurs.h"

static void ImprimeCaracteristiques (const FichierStructure& bloc);

int main (int argc, char **argv)
{ ClubAllocHandler h; // utilisé uniquement pour ses constructeur/destructeur
  if (argc != 2)
  { cerr << "usage : prgm_FichierStructure répertoire" << endl;
    return 1;
  }
try
 {
  string repertoire (argv [1]);
  repertoire += "/test_FichierStructure.don";
  FichierStructure fichier (repertoire.c_str ());
   
  // lecture des blocs

  FichierStructure bloc_2  ("nom_2",  &fichier);

  FichierStructure bloc_21 ("nom_21", &bloc_2);

  FichierStructure bloc_1  ("nom_1",  &fichier);
  
  FichierStructure bloc_11 ("nom_11", &bloc_1);
  
  FichierStructure bloc_12 ("nom_12", &bloc_1);
  
  FichierStructure bloc_22 ("nom_22", &bloc_2);


  ImprimeCaracteristiques (bloc_1);
  ImprimeCaracteristiques (bloc_11);
  ImprimeCaracteristiques (bloc_12);
  ImprimeCaracteristiques (bloc_2);
  ImprimeCaracteristiques (bloc_21);
  ImprimeCaracteristiques (bloc_22);
   if (bloc_2.contientSousBloc ("xxx"))
     cout << bloc_2.nomBloc () << " contient le sous-bloc xxx\n";
   else
     cout << bloc_2.nomBloc () << " ne contient pas le sous-bloc xxx\n";

   if (bloc_2.contientSousBloc ("nom_21"))
     cout << bloc_2.nomBloc () << " contient le sous-bloc nom_21\n";
   else
     cout << bloc_2.nomBloc () << " ne contient pas le sous-bloc nom_21\n";

 }
 catch (ClubErreurs ce)
 {
  ce.affiche (cout);
  ce.correction ();
 }


 return 0;

}

static void ImprimeCaracteristiques (const FichierStructure& f)

{ cout << "Bloc: " << f.nomBloc () << ", Fichier: " << f.nomFichier () << endl;
  if (f.terminal ())
    cout << "bloc terminal\n";
  else
    cout << "bloc non terminal\n";
  cout << "nombre de champs du bloc (valide uniquement pour blocs terminaux): "
       << f.nombreChamps () << endl;

  const int maxTampon = 80;
  char      tampon [maxTampon];
  for (int i = 0; i <= f.nombreChamps () + 1; i++)
  {
    try
    {
      f.champ (i, tampon, maxTampon);
      cout << "champ " << i << ": \"" << tampon << "\"\n";    
    }
    catch (ClubErreurs ce)
    { 
      ce.affiche (cout);
      ce.correction ();
    }
    
  }

  try
  {
    vector<string> liste;
    f.listeSousBlocs (&liste);

    for (vector<string>::iterator iter = liste.begin(); iter != liste.end(); ++iter)
    {
      cout << " \"" << *iter << "\"";
    }
    cout << endl;

  }
  catch (ClubErreurs ce)
  { 
    ce.affiche (cout);
    ce.correction ();
  }

  cout << endl;

}
