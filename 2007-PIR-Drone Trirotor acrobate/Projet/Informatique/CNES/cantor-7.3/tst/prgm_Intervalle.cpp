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
//       $Log: prgm_Intervalle.cpp,v $
//       Revision 1.6  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_Intervalle.cpp,v 1.6 2000/10/24 16:26:42 cantor Exp $
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
#include "cantor/Intervalle.h"

static void afficheRelations (const Intervalle& i1, const Intervalle& i2,
                              double x)
{ cout << "Intervalle: " << i1 << " (longueur " << i1.longueur () << ")\n";
  cout << "Intervalle: " << i2 << " (longueur " << i2.longueur () << ")\n";

  cout << i1
       << (i1.contient (x) ? " contient " : " ne contient pas ")
       << x
       << endl;

  cout << i1
       << (i1.contient (i2) ? " contient " : " ne contient pas ")
       << i2
       << endl;

  cout << i1
       << (i1.rencontre (i2) ? " rencontre " : " ne rencontre pas ")
       << i2
       << endl;

  cout << i1 << " et " << i2
       << (i1.disjoint (i2) ? " disjoints\n" : " non disjoints\n");

  cout << i1
       << ((i1 < i2) ? " < " : " non < ")
       << i2
       << endl;

  cout << i1
       << ((i1 > i2) ? " > " : " non > ")
       << i2
       << endl;

  cout << i1 << " + " << i2 << " = " << i1 + i2 << endl;

  cout << i1 << " * " << i2 << " = " << i1 * i2 << endl;

  Intervalle i (i1);
  cout << i << " += " << i2 << " ---> ";
  i += i2;
  cout << i << endl;

  i = i1;
  cout << i << " *= " << i2 << " ---> ";
  i *= i2;
  cout << i << endl;

}

int main ()

{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    afficheRelations (Intervalle (-10.0, 10.0), Intervalle (11.0, 12.0), 2.5);
    cout << endl;

    afficheRelations (Intervalle (-10.0, 10.0), Intervalle (9.0, 12.0), 50.0);
    cout << endl;

    afficheRelations (Intervalle (-10.0, 10.0), Intervalle (-12.0, -11.0), 0.0);
    cout << endl;

    afficheRelations (Intervalle (-10.0, 10.0), Intervalle (-4.0, 5.0), 0.0);
    cout << endl;

    afficheRelations (Intervalle (-10.0, 10.0), Intervalle (-10.0, 10.0), 0.0);
    cout << endl;

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
