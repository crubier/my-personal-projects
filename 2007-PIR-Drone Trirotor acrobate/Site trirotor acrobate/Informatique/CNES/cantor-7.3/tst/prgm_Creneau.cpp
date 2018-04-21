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
//       $Log: prgm_Creneau.cpp,v $
//       Revision 1.7  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_Creneau.cpp,v 1.7 2000/10/24 16:26:42 cantor Exp $
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
#include "cantor/Creneau.h"

static void afficheRelations (Creneau& c1, Creneau& c2, double x)
{ cout << "Creneau: " << c1
       << (c1.connexe () ? "" : " non") << " connexe,"
       << (c1.vide    () ? "" : " non") << " vide"
       << " (" << c1.nombre () << " intervalle"
       << ((c1.nombre () > 1) ? "s" : "") << ")\n";
  cout << "Creneau: " << c2
       << (c2.connexe () ? "" : " non") << " connexe"
       << (c2.vide    () ? "" : " non") << " vide"
       << " (" << c2.nombre () << " intervalle"
       << ((c2.nombre () > 1) ? "s" : "") << ")\n";

  cout << c1
       << (c1.contient (x) ? " contient " : " ne contient pas ")
       << x
       << endl;

  for (int i = 0; i < c2.nombre (); i++)
  { cout << c1
         << (c1.contient (c2 [i]) ? " contient " : " ne contient pas ")
         << c2 [i]
         << endl;

    cout << c1
         << (c1.rencontre (c2 [i]) ? " rencontre " : " ne rencontre pas ")
         << c2 [i]
         << endl;

    cout << c1 << " et " << c2 [i]
         << (c1.disjoint (c2 [i]) ? " disjoints\n" : " non disjoints\n");

  }

  cout << c1 << " + " << c2 << " = " << c1 + c2 << endl;

  cout << c1 << " * " << c2 << " = " << c1 * c2 << endl;

  Creneau c (c1);
  cout << c << " += " << c2 << " ---> ";
  c += c2;
  cout << c << endl;

}

int main ()

{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    Creneau    c1 (-2.0, -1.0);
    Intervalle i  (-0.9, -0.8);
    Creneau    c2 (i);
    afficheRelations (c1, c2, 2.5);
    cout << endl;

    i = Intervalle (1.0, 3.0);
    cout << c2 << " += " << i << " ---> ";
    c2 += i;
    cout << c2 << endl;
    cout << endl;

    afficheRelations (c1, c2, 2.5);
    cout << endl;

    i = Intervalle (-1.2, 0.0);
    cout << c1 << " += " << i << " ---> ";
    c1 += i;
    cout << c1 << endl;
    cout << endl;

    afficheRelations (c1, c2, -1.1);
    cout << endl;

    i = Intervalle (-6.0, -4.0);
    Creneau c (-10.0, -8.0);
    c = c + i;
    c += Intervalle (-0.85, 1.2);
    cout << c1 << " += " << c << " ---> ";
    c1 += c;
    cout << c1 << endl;
    cout << endl;

    afficheRelations (c1, c2, 0.0);
    cout << endl;

    i = Intervalle (-9.2, -4.5);
    cout << c1 << " *= " << i << " ---> ";
    c1 *= i;
    cout << c1 << endl;
    cout << endl;

    afficheRelations (c1, c2, 0.0);
    cout << endl;

    i = Intervalle (-100.0, -99.0);
    cout << c1 << " *= " << i << " ---> ";
    c1 *= i;
    cout << c1 << endl;
    cout << endl;

    afficheRelations (c1, c2, 0.0);

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
