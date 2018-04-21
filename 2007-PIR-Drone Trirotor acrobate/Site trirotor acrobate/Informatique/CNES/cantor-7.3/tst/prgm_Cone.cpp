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
//       $Log: prgm_Cone.cpp,v $
//       Revision 1.8  2001/09/18 16:03:44  cantor
//       test du constructeur par trois points et de l'opérateur « - »
//
//       Revision 1.7  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_Cone.cpp,v 1.8 2001/09/18 16:03:44 cantor Exp $
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
#include "cantor/Cone.h"
#include "cantor/Util.h"

int main ()

{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    Cone c1 (VecDBL (1, 0, 0), M_PI / 3);
    Cone c2 (VecDBL (0, 1, 0), M_PI / 4);

    VecDBL deb, fin;
    c1.intersection (c2, &deb, &fin);

    cout << "deb = " << deb;
    cout << '\n';
    cout << "fin = " << fin;
    cout << '\n';

    Cone c3 = c1;
    c3.corrige (1.0e-17);
    c3.corrige (-0.1);
    cout << "axe:     " << c3.axe     ()          << endl;
    cout << "angle:   " << degres (c3.angle   ()) << " degres\n";
    cout << "cosinus: " << c3.cosinus ()          << endl;

    // tests d'inclusion
    VecDBL u (radians (54.0), 0.02);
    if (c3.inclus (u))
      cout << "u inclus dans c3\n";
    else
      cout << "u hors de c3\n";

    VecDBL v (radians (55.0), 0.02);
    if (c3.inclus (v))
      cout << "v inclus dans c3\n";
    else
      cout << "v hors de c3\n";

    // construction par trois points et complémentaire
    VecDBL p1 (0.5, 0.0, 0.0);
    VecDBL p2 (0.0, 0.5, 0.0);
    VecDBL p3 (0.0, 0.0, 0.5);
    Cone c4 (p1, p2, p3);
    Cone c5 = -c4;
    c4.corrige (1.0e-7);
    c5.corrige (1.0e-7);
    if (c4.inclus (p1) && c5.inclus (p1))
      cout << "p1 inclus dans c4 et c5\n";
    else
      cout << "p1 hors de c4 ou de c5\n";
    if (c4.inclus (p2) && c5.inclus (p2))
      cout << "p2 inclus dans c4 et c5\n";
    else
      cout << "p2 hors de c4 ou de c5\n";
    if (c4.inclus (p3) && c5.inclus (p3))
      cout << "p3 inclus dans c4 et c5\n";
    else
      cout << "p3 hors de c4 ou de c5\n";
    if (c4.axe ().angleAvecVecteur (c5.axe ()) > M_PI - 1.0e-6)
      cout << "axe de c5 opposé à l'axe de c4\n"; 
    else
      cout << "axe de c5 non opposé à l'axe de c4\n"; 

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
