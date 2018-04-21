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
//       $Log: prgm_SectionDoree.cpp,v $
//       Revision 1.4  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_SectionDoree.cpp,v 1.4 2000/10/24 16:26:42 cantor Exp $
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
#include "cantor/SectionDoree.h"
#include "cantor/Util.h"

double fonc (double x, void* arg)
{ int *ptrN = (int *) arg;
  (*ptrN)++;

  return floor (fabs (10.0 * x - 5.0))
       + 1.0 / sqrt (x * (1.0 - x));
}

int main ()

{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    int n = 0;
    for (double x = 0.025; x < 1.0; x += 0.05)
      cout << x << ' ' << fonc (x, (void *) &n) << endl;

    cout << endl;

    n = 0;
    double xMin, fMin;
    SectionDoree (fonc, (void *) &n,
                  0.001, 0.001, 1.0, &xMin, &fMin);

    cout << n << " appels de la fonction" << endl;
    cout << "  xMin = " << xMin << endl;
    cout << "  fMin = " << fMin << endl;

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
