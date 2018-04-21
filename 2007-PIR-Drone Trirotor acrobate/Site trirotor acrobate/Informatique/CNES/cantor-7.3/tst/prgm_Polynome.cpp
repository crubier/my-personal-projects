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
//       $Log: prgm_Polynome.cpp,v $
//       Revision 1.10  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_Polynome.cpp,v 1.10 2000/10/24 16:26:42 cantor Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "cantor/Util.h"
#include "cantor/DeclDBL.h"

static void afficheZeros (const PolDBL& p);

int main ()
{ double epsilon = 1.0e-5;
  PolDBL pa (4.0 + 2.0 * epsilon, -2.0);
  PolDBL pb (epsilon - 2.0, 1.0);

  PolDBL p2 = pa * pb * 5.0;
  afficheZeros (p2);
  cout << "P2 (" << 2.0 + epsilon << ") = " << p2 (2.0 + epsilon) << '\n';
  cout << "P2 (" << 2.0 - epsilon << ") = " << p2 (2.0 - epsilon) << '\n';

  cout << endl;

  PolDBL p3 = p2 * PolDBL (1.0, 1.0);
  afficheZeros (p3);
  cout << "P3 (" << 2.0 + epsilon << ") = " << p3 (2.0 + epsilon) << '\n';
  cout << "P3 (" << 2.0 - epsilon << ") = " << p3 (2.0 - epsilon) << '\n';
  cout << "P3 (" << -1.0          << ") = " << p3 (-1.0)          << '\n';

  cout << endl;

  PolDBL p4 = pa * pa * pa;
  afficheZeros (p4);

  cout << endl;

  // calcul des premiers polynomes de Chebyshev
  PolDBL chebyshev [polynome_max_degre];
  chebyshev [0] = PolDBL (1.0);
  chebyshev [1] = PolDBL (0.0, 1.0);
  PolDBL deuxX (0.0, 2.0);
  for (int i = 2; i < polynome_max_degre; i++)
    chebyshev [i] = deuxX * chebyshev [i-1] - chebyshev [i-2];

  // verification de: integrale (Tn) = (Tn+1/(n+1) - Tn-1/(n-1)) / 2
  for (int j = 2; j < polynome_max_degre - 1; j++)
  { double constanteIntegration;
    if (j % 2 == 0)
      constanteIntegration = 0.0;
    else if (((j+1)/2) % 2 == 0)
      constanteIntegration =   double (j) / double ((j-1)*(j+1));
    else
      constanteIntegration = - double (j) / double ((j-1)*(j+1));

    PolDBL integrale = chebyshev [j].integrale (constanteIntegration);
    PolDBL modele    = 0.5 * (chebyshev [j+1] / double (j+1)
                            - chebyshev [j-1] / double (j-1));

    PolDBL ecart     = integrale - modele;

    cout << "integrale de T" << j << ":\n";
    cout << "  polynome d'ecart au modele de degre " << ecart.degre ();

    double maxCoeff = 0.0;
    for (int d = 0; d <= ecart.degre (); d++)
      if (maxCoeff < fabs (ecart.coeff (d)))
        maxCoeff = fabs (ecart.coeff (d));

    cout << " et de coefficient maximal " << maxCoeff << endl;

  }

  cout << endl;

  // verification des derivees
  for (int k = 0; k < polynome_max_degre; k++)
  { PolDBL ecart = chebyshev [k].integrale ().derivee () - chebyshev [k];

    cout << "derivee de l'integrale de T" << k << " moins T" << k << ":\n";
    cout << "  polynome de degre " << ecart.degre ();

    double maxCoeff = 0.0;
    for (int d = 0; d <= ecart.degre (); d++)
      if (maxCoeff < fabs (ecart.coeff (d)))
        maxCoeff = fabs (ecart.coeff (d));

    cout << " et de coefficient maximal " << maxCoeff << endl;

  }

  return 0;

}

static void afficheZeros (const PolDBL& p)
{ double zeros [polynome_max_degre];
  int    ordre [polynome_max_degre];
  int    nb;

  p.zeros (&nb, zeros, ordre); 

  cout << nb << " zeros:\n";
 
  for (int i = 0; i < nb; i++) 
  { cout << ' ' << zeros [i] << " d'ordre " << ordre [i];
    cout << " (P (" << zeros [i] << ") = " << p (zeros [i]) << ")\n";
  }
 
}
