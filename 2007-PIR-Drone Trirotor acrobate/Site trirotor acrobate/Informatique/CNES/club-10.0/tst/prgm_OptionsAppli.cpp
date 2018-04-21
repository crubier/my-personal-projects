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
//>        prgm_OptionsAppli.cc
//
//$Resume
//       fichier d'implantation du test prgm_OptionsAppli
//
//$Description
//       teste la classe OptionsAppli
//
//$Contenu
//>       static void AfficheOptions()
//>       int main()                    
//
//$Historique
//       $Log: prgm_OptionsAppli.cpp,v $
//       Revision 3.14  2001/06/21 15:23:49  club
//       correction d'une signature de directive catch
//
//       Revision 3.13  2001/03/22 12:00:26  club
//       correction de la libération mémoire
//
//       Revision 3.12  2001/03/22 11:16:23  club
//       suppression d'une fuite mémoire
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
//$Version
//       $Id: prgm_OptionsAppli.cpp,v 3.14 2001/06/21 15:23:49 club Exp $
//$Auteur
//        P-A.Cros   CSSI
//        M. Julien  CSSI 
//        O. Queyrut CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/OptionsAppli.h"
#include "club/ClubErreurs.h"

static void AfficheOptions (const OptionsAppli& analyseur)
{ cout << "\noption -c:\n";
  int occurrences = analyseur.occurrencesPassees ("c");
  if (occurrences > 0)
  { cout << occurrences << " occurrence"
                  << ((occurrences > 1) ? "s passees\n" : " passee\n");
    int c;
    for (int i = 1; i <= occurrences; i++)
    { cout << "occurrence " << i << ": ";
      analyseur.lireValeur ("c", &c, i);
      cout << "valeur: " << c << endl;
    }
  }
  else
    cout << "non passee\n";

  cout << "\noption -ce:\n";
  occurrences = analyseur.occurrencesPassees ("ce");
  if (occurrences > 0)
  { cout << occurrences << " occurrence"
         << ((occurrences > 1) ? "s passees\n" : " passee\n");
    int ce [3];
    for (int i = 1; i <= occurrences; i++)
    { cout << "occurrence " << i << ": ";
      analyseur.lireValeur ("ce", 3, ce, i);
      cout << "valeur: " << ce [0] << ' ' << ce [1] << ' ' << ce [2] << endl;
    }
  }
  else
    cout << "non passee\n";

  cout << "\noption -ceci:\n";
  occurrences = analyseur.occurrencesPassees ("ceci");
  if (occurrences > 0)
  { cout << occurrences << " occurrence"
                  << ((occurrences > 1) ? "s passees\n" : " passee\n");
    double ceci;
    for (int i = 1; i <= occurrences; i++)
    { cout << "occurrence " << i << ": ";
      analyseur.lireValeur ("ceci", &ceci, i);
      cout << "valeur: " << ceci << endl;
    }
  }
  else
    cout << "non passee\n";

  cout << "\nargument sans nom:\n";
  occurrences = analyseur.occurrencesPassees ("");
  if (occurrences > 0)
  { cout << occurrences << " occurrence"
                  << ((occurrences > 1) ? "s passees\n" : " passee\n");
    double z;
    for (int i = 1; i <= occurrences; i++)
    { cout << "occurrence " << i << ": ";
      analyseur.lireValeur ("", &z, i);
      cout << "valeur: " << z << endl;
    }
  }
  else
    cout << "non passee\n";

  cout << "\noption -e:\n";
  occurrences = analyseur.occurrencesPassees ("e");
  if (occurrences > 0)
  { cout << occurrences << " occurrence"
                  << ((occurrences > 1) ? "s passees\n" : " passee\n");
    string e;
    for (int i = 1; i <= occurrences; i++)
    { cout << "occurrence " << i << ": ";
      analyseur.lireValeur ("e", &e, i);
      cout << "valeur: " << e << endl;
    }
  }
  else
    cout << "non passee\n";

  cout << "\noption -cela:\n";
  occurrences = analyseur.occurrencesPassees ("cela");
  if (occurrences > 0)
  { cout << occurrences << " occurrence"
                  << ((occurrences > 1) ? "s passees\n" : " passee\n");
    char* cela [3];
    char cela_0 [20];
    char cela_1 [20];
    char cela_2 [20];
    cela [0] = cela_0;
    cela [1] = cela_1;
    cela [2] = cela_2;
    for (int i = 1; i <= occurrences; i++)
    { cout << "occurrence " << i << ": ";
      analyseur.lireValeur ("cela", 3, cela, i);
      cout << "valeur: " << cela [0] << ' ' << cela [1] << ' ' << cela [2]
           << endl;
    }
  }
  else
    cout << "non passee\n";

  cout << "\noption -l:\n";
  occurrences = analyseur.occurrencesPassees ("l");
  if (occurrences > 0)
  { cout << occurrences << " occurrence"
                  << ((occurrences > 1) ? "s passees\n" : " passee\n");
  }
  else
    cout << "non passee\n";

}

int main (int argc, char** argv)
{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    // creation de l'analyseur de base
    OptionsAppli base ("nom_de_l_analyseur");
    base.ajouterOption (OptionEntier         ("c",
                                              1, 1, sansValeurDefaut,
                                              0, -10, 10));
    base.ajouterOption (OptionTableauEntiers ("ce",
                                              1, 1, sansValeurDefaut,
                                              3, (int *) 0, -5));
    base.ajouterOption (OptionReel           ("ceci",
                                              1, 5, sansValeurDefaut,
                                              0.0, -10.0, 10.0));
    base.ajouterOption (OptionTableauReels   ("",
                                              1, 6, sansValeurDefaut,
                                              1, (double *) 0, -5.0, 5.0));

    static const char * choix [] = {"oui", "OUI", "o", "O",
                                    "non", "NON", "n", "N"};
    base.ajouterOption (OptionChaine         ("e",
                                              1, 1, sansValeurDefaut,
                                              "", 4,
                                              sizeof(choix)/sizeof(char *),
                                              choix));
    base.ajouterOption (OptionTableauChaines ("cela",
                                              1, 1, sansValeurDefaut,
                                              3, 0, 10));
    base.ajouterOption (OptionSansValeur     ("l", 0, 1));

    // essai des fonctions membres generales
    OptionsAppli copie (base);
    cout << "avant initialisation:\n";
    cout << "   analyseur " << copie.nom ()
         << (copie.estInitialise () ? "" : " non")
         << " initialise\n";
    cout << copie.usage () << endl;

    // initialisation ne devant pas generer d'erreur
    int   i1 = 0;
    const char* t1 [50];
    t1 [i1++]  = argv [0];
    t1 [i1++]  = "-cececi";
    t1 [i1++]  = "-5"; t1 [i1++] = "0"; t1 [i1++] = "5"; // arguments de -ce
    t1 [i1++]  = "-9.98765";                             // argument  de -ceci
    t1 [i1++]  = "-4.5";                                 // donnee 1  sans nom
    t1 [i1++]  = "-celaececic";
    t1 [i1++]  = "x"; t1 [i1++] = "y"; t1 [i1++] = "-c"; // arguments de -cela
    t1 [i1++] = "OUI";                                   // argument  de -e
    t1 [i1++] = "+4.653";                                // argument  de -ceci
    t1 [i1++] = "3";                                     // argument  de -c
    t1 [i1++] = "0.12";                                  // donnee 2  sans nom
    t1 [i1++] = "4.5";                                   // donnee 3  sans nom

    copie.initialiser (i1, t1);

    cout << "apres initialisation:\n";
    cout << "   analyseur " << copie.nom ()
         << (copie.estInitialise () ? "" : " non")
         << " initialise\n";
    copie.garantirComplet ();
    AfficheOptions (copie);

    cout << "\n\ntest des detections d'erreurs\n";

    // initialisation devant generer une erreur d'espace de validite
    copie = base;
    t1 [11] = "YES";
    copie.initialiser (i1, t1);
    string message;
    if (copie.verifier (&message))
    { cout << "probleme a l'analyse:\n";
      cout << message << endl;
    }
    else
    { cout << "analyse correcte\n";
      AfficheOptions (copie);
    }
    t1 [11] = "OUI";

    // initialisation devant generer une erreur d'espace de validite
    copie = base;
    t1 [3] = "-6";
    copie.initialiser (i1, t1);
    if (copie.verifier (&message))
    { cout << "probleme a l'analyse:\n";
      cout << message << endl;
    }
    else
    { cout << "analyse correcte\n";
      AfficheOptions (copie);
    }
    t1 [3] = "0";

    // initialisation devant generer une erreur d'espace de validite
    copie = base;
    t1 [8] = "000000000000000000000";
    copie.initialiser (i1, t1);
    if (copie.verifier (&message))
    { cout << "probleme a l'analyse:\n";
      cout << message << endl;
    }
    else
    { cout << "analyse correcte\n";
      AfficheOptions (copie);
    }
    t1 [8] = "x";

    cout << "\n\ntest de l'analyse en plusieurs passes\n";
    i1--;
    t1 [i1++] = "-a";
    t1 [i1++] = "-bdr";
    t1 [i1++] = "4.5";
    copie = base;
    copie.initialiser (i1, t1);
    if (copie.verifier (&message))
    { cout << "probleme a l'analyse:\n";
      cout << message << endl;
    }
    else
    { cout << "analyse correcte\n";
      AfficheOptions (copie);
    }
    int i2 = copie.argcReste ();
    char* t2 [50];
    copie.argvReste (t2);
    if (i2 > 0)
    { cout << "il reste " << i2 << " arguments non reconnus apres la passe 1\n";
      for (int i = 0; i < i2; i++)
        cout << ' ' << t2 [i];
      cout << endl;
      OptionsAppli second ("second_analyseur");
      second.ajouterOption (OptionSansValeur ("a", 1, 1));
      second.ajouterOption (OptionSansValeur ("b", 1, 1));
      second.ajouterOption (OptionSansValeur ("d", 1, 1));
      second.ajouterOption (OptionSansValeur ("r", 1, 1));
      second.initialiser (i2, t2);
      second.garantirComplet ();
      cout << "execution de la passe 2 correcte\n";
    }

    for (int i = 0; i < i2; i++)
      delete [] t2 [i];

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
