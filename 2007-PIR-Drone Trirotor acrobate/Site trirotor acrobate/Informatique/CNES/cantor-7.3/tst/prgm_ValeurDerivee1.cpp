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
//       $Log: prgm_ValeurDerivee1.cpp,v $
//       Revision 1.7  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_ValeurDerivee1.cpp,v 1.7 2000/10/24 16:26:42 cantor Exp $
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
#include "cantor/DeclVD1.h"

template <class T> T fonctionCompliquee (const T& x)
{ // fonction utilisant tous les operateurs de ValeurDerivee1

  T y1  = x + x;
  T y2  = y1 * x;
  T y3  = y1 - y2;
  T y4  = y3 / (x + 25.0);

    y4 += y2;
    y4 *= y3;
    y4 /= (y2 - 12.0);
    y4 -= x;

  T y5  = y4 + 3.54253;
  T y6  = y5 * 6.3543;
  T y7  = y6 / 3952.42453;
  T y8  = y7 - 2.5354;

    y8 += 4.243;
    y8 *= -65.343;
    y8 /= 3.22;
    y8 -= -87.4532;

  T y9  = 3.5343 + y8;
  T y10 = 5.453 * y9;
  T y11 = 7.534 / y10;
  T y12 = 6.433323 - y11;

  T y13 = -y12;

  T y14 = log (sqrt (exp (y13)));
  T y15 = atan2 (y14, y6);
  T y16 = asin (cos (atan (y15)));
  T y17 = 10000.0 * sin (acos (tan (pow (y16, y15) / 10.0)) - 2.0) +5000.0;

  return y17;

}

// instanciations explicites
template double         fonctionCompliquee (const double&         x);
template ValeurDerivee1 fonctionCompliquee (const ValeurDerivee1& x);

int main ()

{ ClubAllocHandler hdl; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    ValeurDerivee1 x (2.0, 1.0);

    ValeurDerivee1 f  = 2.0 * sin (x * (1.0 + x) + 1.0);
    cout << "f(x) = " << f << '\n';

    f = ValeurDerivee1 (3.0, 1.0);
    cout << "f(x) = " << f << '\n';

    ValeurDerivee1 g = 2.9;
    cout << "g(x) = " << g << '\n';

    cout << "f <  g: " << (f <  g) << '\n';
    cout << "f <= g: " << (f <= g) << '\n';
    cout << "f >  g: " << (f >  g) << '\n';
    cout << "f >= g: " << (f >= g) << '\n';

    cout << "f <  3.0: " << (f <  3.0) << '\n';
    cout << "f <= 3.0: " << (f <= 3.0) << '\n';
    cout << "f >  3.0: " << (f >  3.0) << '\n';
    cout << "f >= 3.0: " << (f >= 3.0) << '\n';

    cout << "\n  valeur     taylor     ecart\n";
    ValeurDerivee1 x0 (1.0, 1.0);
    ValeurDerivee1 y0 = fonctionCompliquee (x0);
    cout.flags     (ios::fixed);
    cout.precision (8);
    for (double h = -1.0; h < 1.0; h += 0.02)
    { cout << 1.0 + h;
      cout << ' ' << fonctionCompliquee (1.0 + h);
      cout << ' ' << y0.taylor (h);
      cout << ' ' << y0.taylor (h) - fonctionCompliquee (1.0 + h);
      cout << '\n';
    }

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
