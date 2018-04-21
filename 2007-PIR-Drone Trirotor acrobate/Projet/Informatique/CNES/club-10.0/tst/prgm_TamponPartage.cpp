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
//>       prgm_TamponPartage.cc
//
//$Resume
//       fichier d'implantation du test prgm_TamponPartage
//
//$Description
//       teste la classe TamponPartage
//
//$Contenu
//>       static char *AlloueChaine()
//>       static void LibereChaine() 
//>       int main()                 
//
//$Historique
//       $Log: prgm_TamponPartage.cpp,v $
//       Revision 3.11  2001/06/21 15:22:00  club
//       correction d'une signature de directive catch
//
//       Revision 3.10  2000/10/25 09:10:39  club
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
//       Revision 3.7  2000/09/07 08:36:18  club
//       mise à jour du cartouche du fichier.
//
//$Version
//       $Id: prgm_TamponPartage.cpp,v 3.11 2001/06/21 15:22:00 club Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
# include <cstring>
#endif

#ifdef HAVE_IOSTREAM
# include <iostream>
#endif

#include "club/TamponPartage.h"
#include "club/ClubErreurs.h"

static char *AlloueChaine (int longueur)
{ return new char [longueur + 1]; }

static void LibereChaine (void *memoire, void *)
{ delete [] ((char *) memoire); }

int main ()
{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    // allocation memoire du tampon
    char* origine = AlloueChaine (9);
    (void) strcpy (origine, "123456789");

    TamponPartage* tampon1 = new TamponPartage(origine, LibereChaine, 0);
    TamponPartage tampon2 (*tampon1);
    cout << "apres une creation et un copie constructeur:\n";
    cout << "nombre de references = " << tampon1->references () << endl;
    cout << "chaine partagee: \"" << (char *) tampon2.memoire () << "\"\n";

    TamponPartage tampon3;
    tampon2 = tampon3;
    cout << "apres un ecrasement:\n";
    cout << "nombre de references = " << tampon1->references () << endl;

    tampon2 = *tampon1;
    cout << "avant une destruction:\n";
    cout << "nombre de references = " << tampon2.references () << endl;
    delete tampon1;
    cout << "apres la destruction:\n";
    cout << "nombre de references = " << tampon2.references () << endl;
    cout << "chaine partagee: \"" << (char *) tampon2.memoire () << "\"\n";

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
