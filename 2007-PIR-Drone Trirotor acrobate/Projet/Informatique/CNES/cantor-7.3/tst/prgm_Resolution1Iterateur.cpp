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
//       $Log: prgm_Resolution1Iterateur.cpp,v $
//       Revision 1.7  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_Resolution1Iterateur.cpp,v 1.7 2000/10/24 16:26:42 cantor Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#ifdef HAVE_IOMANIP
#include <iomanip>
#endif

#include "club/OptionsAppli.h"
#include "club/ClubErreurs.h"
#include "cantor/DeclVD1.h"
#include "cantor/Resolution1Iterateur.h"

static void analyseLigneCommande (int argc, char** argv,
                                  int*       n,
                                  double*    a, double*    b,
                                  double*    seuil)
{ OptionsAppli analyseur (argv [0]);

  // nombre de tranches de dichotomies
  // option n: une occurrence, valeur par defaut: 200, domaine: [0; INT_MAX]
  analyseur.ajouterOption (OptionEntier ("n", 0, 1, avecValeurDefaut,
                                         200, 0));

  // borne inferieure de l'intervalle
  // option a: une occurrence, pas de valeur par defaut, domaine [-100.0; 100.0]
  analyseur.ajouterOption (OptionReel   ("a", 1, 1, sansValeurDefaut,
                                         0.0, -1000.0, 1000.0));

  // borne superieure de l'intervalle
  // option b: une occurrence, pas de valeur par defaut, domaine [-100.0; 100.0]
  analyseur.ajouterOption (OptionReel   ("b", 1, 1, sansValeurDefaut,
                                         0.0, -1000.0, 1000.0));

  // seuil de convergence
  // option s: une occurrence, valeur par defaut: 1.1e-5, domaine [0.0; 0.1]
  analyseur.ajouterOption (OptionReel   ("s", 0, 1, avecValeurDefaut,
                                         1.1e-5, 0.0, 0.1));

  // analyse de la ligne
  analyseur.initialiser (argc, argv);
  analyseur.garantirComplet ();

  // recuperation des donnees
  analyseur.lireValeur ("n", n);
  analyseur.lireValeur ("a", a);
  analyseur.lireValeur ("b", b);
  analyseur.lireValeur ("s", seuil);
  if (*a > *b)
  { double tmp = *a;
    *a = *b;
    *b = tmp;
  }

}

static ValeurDerivee1 SinusCroissant (double t, void* d)
{ *((int *) d) += 1;
  ValeurDerivee1 x (t, 1.0);
  return sin (x) + x * 0.091325;
}

int main (int argc, char** argv)

{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

  int compteurAppels;
  int    n;
  double a;
  double b;
  double seuil;

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    analyseLigneCommande (argc, argv, &n, &a, &b, &seuil);

    cout << "resolution avec des derivees d'ordre 1:\n";
    compteurAppels = 0;
    Resolution1Iterateur iter (SinusCroissant, (void *) &compteurAppels,
                               a, b, n, seuil, seuil);
    int decimales = -int (ceil (log (seuil) / log (10.0)));

    int i = 0;
    double x0;
    while ((x0 = iter.zeroSuivant ()) <= b)
    { i++;
      cout << setiosflags (ios::fixed) << setprecision (decimales)
           << "solution " << i << ": " << x0 << '\n';
    }
    cout << "nombre d'appels a la fonction f: " << compteurAppels << '\n';

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
