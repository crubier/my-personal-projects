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
//       $Log: prgm_StatistiqueEchantillon.cpp,v $
//       Revision 1.3  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_StatistiqueEchantillon.cpp,v 1.3 2000/10/24 16:26:42 cantor Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/ClubErreurs.h"
#include "cantor/StatistiqueEchantillon.h"

int main ()

{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    static double tab1 [] = {0.934, 1.0, 0.9, 0.97, 1.025};
    static double tab2 [] = {0.99, 1.001, 1.01};
    StatistiqueEchantillon s1, s2;

    for (int i1 = 0; i1 < int (sizeof(tab1)/sizeof(double)); i1++)
      s1 += tab1 [i1];

    for (int i2 = 0; i2 < int (sizeof(tab2)/sizeof(double)); i2++)
      s2 += tab2 [i2];

    s1 += s2;

    cout << "échantillon de " << s1.nbPoints () << " points" << endl;
    cout << "  min        = " << s1.min       () << endl;
    cout << "  max        = " << s1.max       () << endl;
    cout << "  moyenne    = " << s1.moyenne   () << endl;
    cout << "  écart type = " << s1.ecartType () << endl;

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
