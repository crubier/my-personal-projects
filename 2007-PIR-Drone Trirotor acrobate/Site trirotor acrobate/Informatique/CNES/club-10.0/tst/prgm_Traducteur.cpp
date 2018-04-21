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
//>       prgm_Traducteur.cc
//$Resume
//       fichier d'implantation du test prgm_Traducteur
//
//$Description
//       teste la classe Traducteur
//
//$Contenu
//>       int main()                            
//>       static void ImprimerCaracteristiques()
//
//$Historique
//       $Log: prgm_Traducteur.cpp,v $
//       Revision 3.11  2001/06/21 15:21:01  club
//       correction d'une signature de directive catch
//
//       Revision 3.10  2000/10/25 09:10:40  club
//       modification des includes du standard C++ : suppression du ".h" dans le
//       nom du fichier inclus.
//
//       Revision 3.9  2000/10/24 14:23:12  club
//       ajout de l'include ClubConfig.h et des tests de configuration.
//
//       Revision 3.8  2000/10/24 08:36:34  club
//       ajout de l'include src/ClubConfig.h et modification des includes du
//       standard C : utilisation des includes du type cNAME au lieu de NAME.h
//       pour permettre la compilation avec le Sun Workshop 5.0
//
//       Revision 3.7  2000/09/07 08:35:52  club
//       utilisation de string de la STL au lieu de ChaineSimple.
//       mise à jour du cartouche.
//
//$Version
//       $Id: prgm_Traducteur.cpp,v 3.11 2001/06/21 15:21:01 club Exp $
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

#include "club/Traducteur.h"
#include "club/ClubErreurs.h"

static void ImprimerCaracteristiques (const Traducteur& t, const char* sens);

int main (int argc, char **argv)
{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

     if (argc != 2)
     { cerr << "usage : prgm_Traducteur répertoire" << endl;
       return 1;
     }
     string repertoire (argv [1]);

     Traducteur   t1 ("fr");
     Traducteur   t2 ("fr");
     string nomLong = repertoire + "/test_Traducteur.";
     nomLong += t1.langueUtilisateur ().c_str ();
     TamponTexte f (nomLong.c_str ());
     t1.ajouterDomaine ("test_Traducteur", f, 1);
     t2.ajouterDomaine ("test_Traducteur", f, 0);

     ImprimerCaracteristiques (t1, "impair->pair");
     ImprimerCaracteristiques (t2, "pair->impair");

     Traducteur   t3 ("en");
     Traducteur   t4 ("en");
     nomLong = repertoire + "/test_Traducteur.";
     nomLong += t3.langueUtilisateur ().c_str ();
     TamponTexte g (nomLong.c_str ());
     t3.ajouterDomaine ("test_Traducteur", g, 1);
     t4.ajouterDomaine ("test_Traducteur", g, 0);

     ImprimerCaracteristiques (t3, "impair->pair");
     ImprimerCaracteristiques (t4, "pair->impair");

     (void) printf (t3.traductionFormatC ("reel: %7.2le, chaine: %s\n").c_str (),
                    23.5, "aaabbbccc");
     (void) printf (t3.traductionFormatC ("chaine: %s, reel: %7.2le\n").c_str (),
                    "aaabbbccc", 23.5);

     FormatFortran forTrad;
     (void) t3.traductionFormatF ("(I2, 3X, 'nom: ', 2(X, F6.3, X, A5), L)",
                                  &forTrad);
     (void) printf ("%s\n", forTrad.chaine ().c_str ());
     (void) t3.traductionFormatF ("(2(F6.3, X, A5))", &forTrad);
     (void) printf ("%s\n", forTrad.chaine ().c_str ());
     (void) t3.traductionFormatF ("('aaaxx', 2X, 3('ss', X))", &forTrad);
     (void) printf ("%s\n", forTrad.chaine ().c_str ());
     (void) t3.traductionFormatF ("('X, 3('FFF', X))", &forTrad);
     (void) printf ("%s\n", forTrad.chaine ().c_str ());


#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}

static void ImprimerCaracteristiques (const Traducteur& t, const char* sens)
{ cout << "Traducteur langue: " << t.langueUtilisateur () << endl;
  if (t.domaineMembre ("test_Traducteur"))
    cout << "test_Traducteur est un domaine de ce traducteur\n";
  else
    cout << "test_Traducteur n'est pas un domaine de ce traducteur\n";
  if (t.domaineMembre ("xxxxx"))
    cout << "xxxxx est un domaine de ce traducteur\n";
  else
    cout << "xxxxx n'est pas un domaine de ce traducteur\n";
  cout << "sens: " << sens << endl;

  cout << "traducteur (" << "un"   << ") = " << t ("un")   << endl;
  cout << "traducteur (" << "deux" << ") = " << t ("deux") << endl;
  cout << "traducteur (" << "one"  << ") = " << t ("one")  << endl;
  cout << "traducteur (" << "two"  << ") = " << t ("two")  << endl;
  cout << "traducteur (" << "xxx"  << ") = " << t ("xxx")  << endl;

  cout << endl;

}
