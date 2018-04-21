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
//       $Log: prgm_FonctionApprochee.cpp,v $
//       Revision 1.9  2002/09/12 11:30:22  cantor
//       Modifications de la classe Alea (FA 10)
//
//       Revision 1.8  2001/06/06 07:07:36  cantor
//       utilisation du mécanisme des exception pour la gestion des erreurs
//
//       Revision 1.7  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//       Revision 1.6  1999/08/12 16:07:30  cantor
//       utilisation d'un mécanisme de try/catch au lieu
//       d'un test sur retour d'erreur suite à l'évolution
//       du traitement d'erreur par exception de CLUB.
//
//$Version
//       $Id: prgm_FonctionApprochee.cpp,v 1.9 2002/09/12 11:30:22 cantor Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/OptionsAppli.h"
#include "cantor/Util.h"
#include "cantor/FonctionApprochee.h"

class Alea  // générateur pseudo-aléatoire simplifié
{ int _i;
  double _tab[40];
  public :
  Alea () { _i = 0;
  _tab[0] = 0.551327;_tab[1] = 0.793794;_tab[2] = 0.0622134;_tab[3] = 0.209035;_tab[4] = 0.142846;
  _tab[5] = 0.097096;_tab[6] = 0.793127;_tab[7] = 0.5081220;_tab[8] = 0.480140;_tab[9] = 0.666449;
  _tab[10] = 0.406148;_tab[11] = 0.993474;_tab[12] = 0.118197;_tab[13] = 0.026283;_tab[14] = 0.333447;
  _tab[15] = 0.994809;_tab[16] = 0.232022;_tab[17] = 0.902925;_tab[18] = 0.842200;_tab[19] = 0.462159;
  _tab[20] = 0.075107;_tab[21] = 0.840462;_tab[22] = 0.385389;_tab[23] = 0.113261;_tab[24] = 0.551030;
  _tab[25] = 0.877738;_tab[26] = 0.477419;_tab[27] = 0.942948;_tab[28] = 0.901342;_tab[29] = 0.290763;
  _tab[30] = 0.797347;_tab[31] = 0.960900;_tab[32] = 0.208193;_tab[33] = 0.871345;_tab[34] = 0.686222;
  _tab[35] = 0.592805;_tab[36] = 0.152196;_tab[37] = 0.924397;_tab[38] = 0.711154;_tab[39] = 0.456892;}
  double next() {return _tab[_i++%40];}
};

int fonctionsBase (void *x, void *argsBase, double *ptrY)
{ // fonctions de base d'un espace vectoriel
  // f1 : constante, f2 : linéaire, f3 : sinus, f4 : cosinus
  double t = *((double *) x);

  ptrY [0] = 1.0;
  ptrY [1] = t;
  ptrY [2] = sin (t);
  ptrY [3] = cos (t);

  return 0;

}

double fonctionReelle (double x)
{ return 2.3 - 1.2 * x + 0.5 * sin (x) + 3.1 * cos (x); }

int main (int argc, char **argv)
{ ClubAllocHandler h; // utilisé uniquement pour ses constructeur/destructeur

 try
 {
   // récupération de l'erreur maximale
   OptionsAppli analyseur (argv [0]);
   analyseur.ajouterOption (OptionReel ("e", 0, 1, avecValeurDefaut,
                                        0.01, 0.0, 10.0));
   analyseur.ajouterOption (OptionReel ("s", 0, 1, avecValeurDefaut,
                                        0.0, 0.0, 1.0));
   analyseur.ajouterOption (OptionEntier ("n", 0, 1, avecValeurDefaut,
                                          40, 5, 1000000));

   analyseur.initialiser (argc, argv);
   analyseur.garantirComplet ();

   double errMax;
   analyseur.lireValeur ("e", &errMax);

   double semence;
   analyseur.lireValeur ("s", &semence);

   int n;
   analyseur.lireValeur ("n", &n);

   FonctionApprochee approx (4, fonctionsBase);
   Alea              aleatoire;

   for (int i = 0; i < n; i++)
   {
     double x = (4.0 * i) / (n - 1);
     approx.ajoutePointReference ((void *) &x,
                                  fonctionReelle (x) + errMax * aleatoire.next());
   }

   approx.ajuste ();

   // récupération des éléments de l'ajustement
   double coeffs [4];
   approx.coefficients (coeffs);
   cout << "# modèle ajusté : a + b x + c sin (x) + d cos (x)\n"
        << "# a = " << coeffs [0] << " ( 2.3 attendu)\n"
        << "# b = " << coeffs [1] << " (-1.2 attendu)\n"
        << "# c = " << coeffs [2] << " ( 0.5 attendu)\n"
        << "# d = " << coeffs [3] << " ( 3.1 attendu)\n";
   double errQuad = approx.erreurQuadratique ();
   cout << "# écart type de l'ajustement : "
        << sqrt (errQuad / (1.0 + approx.nbPointsReferences ())) << endl;

   for (int j = 0; j < n; j++)
   {
     double x = (4.0 * j) / (n - 1);
     double yApprox;
     approx ((void *) &x, &yApprox);
     double yReel = fonctionReelle (x);
     cout << x << ' ' << yReel << ' ' << yApprox
          << ' ' << (yReel - yApprox) << endl;
   }

   return 0;
 }
 catch (ClubErreurs &cle)
 {
   return 1;
 }
 catch (CantorErreurs &cae)
 {
   return 1;
 }

}
