///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       Cantor
//
//$Nom
//>       Resolution1.cpp
//
//$Resume
//       fichier d'implantation des fonctions de résolutions à l'ordre 1
//
//$Description
//       Module de définition des fonctions
//
//$Contenu
//>       double ExtremumNewSec()    
//>       Variation1 ExtremumNewSec()
//>       double NewtonSecante()     
//>       Variation1 NewtonSecante() 
//
//$Historique
//       $Log: Resolution1.cpp,v $
//       Revision 1.14  2003/02/04 09:29:16  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.13  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.12.2.1  2000/03/30 15:36:06  cantor
//       ajout du copyright CNES
//
//       Revision 1.12  1999/08/05 09:54:29  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.11.2.2  1999/06/28 15:14:07  cantor
//       limitation du nombre de boucles des fonctions ExtremumNewSec
//       et NewtonSecante
//
//       Revision 1.11.2.1  1999/04/26 10:35:56  cantor
//       ExtremumNewSec : utilisation de la méthode de Brent
//       NewtonSecante: utilisation d'une méthode de Newton en deux points
//
//       Revision 1.11  1998/10/05 13:30:44  cantor
//       utilisation de la constante cantorEpsilon de cantor/Util.h
//
//       Revision 1.10  1998/10/05 12:37:57  cantor
//       remplacement de la constante DBL_EPSILON par 1.0e-15
//       (pour éviter les problèmes de non-portabilité)
//
//       Revision 1.9  1998/07/29 11:34:25  cantor
//       élimination de float.h
//
//       Revision 1.8  1998/07/29 11:27:50  cantor
//       protection de l'inclusion de float.h
//
//       Revision 1.7  1998/06/24 10:10:36  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:39:06  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:54:33  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:32:43  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 10:37:21  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.2  1994/11/26 15:17:11  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:53:31  luc
//       Initial revision
//
//$Version
//       $Id: Resolution1.cpp,v 1.14 2003/02/04 09:29:16 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Util.h"
#include "cantor/Resolution1.h"
#include "cantor/CantorErreurs.h"

double ExtremumNewSec (TypeFoncVD1   f,           void*  arg,
                       TypeFoncConv1 convergence, void*  arg_conv,
                       double        a,           double b)
{ Variation1 va (a, (*f) (a, arg));
  Variation1 vb (b, (*f) (b, arg));

  return ExtremumNewSec (f, arg, convergence, arg_conv, va, vb).x ();

}

Variation1 ExtremumNewSec (TypeFoncVD1   f,           void* arg,
                           TypeFoncConv1 convergence, void* arg_conv,
                           const Variation1& a, const Variation1& b)
{ // calcul de l'extremum de f entre a et b en cherchant le zéro
  // de la dérivée de f par la méthode de Brent
  // (cf note J.-C. Berges, DTS/MPI/MS/MN/98-092, 27 Novembre 1998)
  Variation1 u (a);
  Variation1 v (b);

  Variation1 w (u);
  double d = v.x () - u.x ();
  double e = d;

  double           tol_s;
  CodeConvergence1 code;
  Variation1 inf, sup;
  int compteur = 0;
  do
  { // boucle de recherche
    compteur++;
 
    if (fabs (w.y ().f1 ()) < fabs (v.y ().f1 ()))
    { // inversion des points
      u = v;
      v = w;
      w = u;
    }

    tol_s = cantorEpsilon * max (1.0, fabs (v.x ()));
    double xm = 0.5 * (w.x () - v.x ());

    if ((fabs (e) < tol_s)
        ||
        (fabs (u.y ().f1 ()) <= fabs (v.y ().f1 ())))
    { // on utilise la bissection
      d = xm;
      e = d;
    }
    else
    { // méthode de la sécante
      double s = v.y ().f1 () / u.y ().f1 ();

      double p, q;
      if (fabs (u.x () - w.x ()) < cantorEpsilon)
      { // interpolation linéaire sur les seuls points v et w
        p = 2.0 * xm * s;
        q = 1.0 - s;
      }
      else
      { // interpolation quadratique inverse
        q        = u.y ().f1 () / w.y ().f1 ();
        double r = v.y ().f1 () / w.y ().f1 ();
        p = s * (2.0 * xm * q * (q - r) - (v.x () - u.x ()) * (r - 1.0));
        q = (q - 1.0) * (r - 1.0) * (s - 1.0);
      }

      if (p > 0.0)
        q = -q;
      else
        p = -p;

      s = e;
      e = d;

      if (((2.0 * p) < (3.0 * xm * q - fabs (tol_s * q)))
          &&
          (p < fabs (0.5 * s * q)))
        d = p / q;
      else
      { // on revient sur la bissection
        d = xm;
        e = d;
      }
    }

    u = v;

    // calcul de la fonction pour le nouveau t
    double t = v.x () + ((fabs (d) > tol_s) ? d : (xm > 0.0 ? tol_s : -tol_s));
    v = Variation1 (t, (*f) (t, arg));

    // mise à jour des bornes de l'intervalle encadrant la racine
    if (v.sens () == w.sens ())
    {
      w = u;
      d = v.x () - u.x ();
      e = d;
    }

    // test de la convergence de l'algorithme
    if (v.x () < w.x ())
    {
      inf = v;
      sup = w;
    }
    else
    {
      inf = w;
      sup = v;
    }
    code = (*convergence) (inf, sup, arg_conv);

  } while ((compteur < 100) && (code == CONV1_AUCUNE) && (sup.x () - inf.x () > tol_s));

  return (code == CONV1_INF) ? inf : sup;

}

double NewtonSecante (TypeFoncVD1   f,           void*  arg,
                      TypeFoncConv1 convergence, void*  arg_conv,
                      double        a,           double b)
{ Variation1 va (a, (*f) (a, arg));
  Variation1 vb (b, (*f) (b, arg));

  return (NewtonSecante (f, arg, convergence, arg_conv, va, vb)).x ();

}

Variation1 NewtonSecante (TypeFoncVD1   f,           void* arg,
                          TypeFoncConv1 convergence, void* arg_conv,
                          const Variation1& a, const Variation1& b)
{ // remise en ordre des bornes
  Variation1 inf = (a.x () < b.x ()) ? a : b;
  Variation1 sup = (a.x () < b.x ()) ? b : a;
  int        last_inf;

  // correction du sens de variation donné par les dérivées
  // (si a et b sont des extremums, le signe des dérivées n'est pas fiable)
  if (inf.y () <= sup.y ())
  { inf.simuleCroissante   ();
    sup.simuleCroissante   ();
  }
  else
  { inf.simuleDecroissante ();
    sup.simuleDecroissante ();
  }

  double eps;
  CodeConvergence1 code;
  int compteur = 0;
  do
  { // boucle de réduction de l'intervalle de recherche
    compteur++;

    double xi       = inf.x ();
    double yi       = inf.y ().f0 ();
    double absi     = fabs (yi);
    double yi_prime = inf.y ().f1 ();

    double xs       = sup.x ();
    double ys       = sup.y ().f0 ();
    double abss     = fabs (ys);
    double ys_prime = sup.y ().f1 ();

    if (absi > 10.0 * abss)
    { // intervalle disproportionné
      // on décale les ordonnées pour chercher -sup.y () au lieu de 0
      yi += ys;
      ys += ys;
    }
    else if (abss > 10.0 * absi)
    { // intervalle disproportionné
      // on décale les ordonnées pour chercher -inf.y () au lieu de 0
      ys += yi;
      yi += yi;
    }

    double xsmxi = xs - xi;
    double ysmyi = ys - yi;
    double t = xi - 1.0;
    if ((fabs (yi_prime) > cantorEpsilon) && (fabs (ys_prime) > cantorEpsilon))
    { // les dérivées sont suffisantes pour appliquer une méthode de
      // Newton en deux points
      double r1 = (yi * yi_prime + ys * ys_prime) / (yi_prime * ys_prime);
      double r2 = xsmxi * (yi + ys) / ysmyi;
      t = (xi * ys - xs * yi - (yi * ys) * (r1 - r2) / ysmyi) / ysmyi;
    }

    // protection contre les t hors intervalle
    if ((t < xi) || (t > xs))
      t = (xi * ys - xs * yi) / ysmyi;

    // protection contre les t trop proches des bornes
    double milieu = 0.5 * (xi + xs);
    eps = cantorEpsilon * max (1.0, fabs (milieu));
    if (t < xi + eps)
      t = (xsmxi < 1000.0 * eps) ? milieu : (0.999 * xi + 0.001 * xs);
    else if (t > xs - eps)
      t = (xsmxi < 1000.0 * eps) ? milieu : (0.001 * xi + 0.999 * xs);

    // calcul de la fonction pour le nouveau t
    Variation1 b (t, (*f) (t, arg));

    // mise à jour des bornes de l'intervalle encadrant la racine
    if (inf.croissante ())
      b.simuleCroissante   ();
    else
      b.simuleDecroissante ();
    if (((b.y () <= 0.0) && (inf.croissante   ()))
     || ((b.y () >  0.0) && (inf.decroissante ())))
    { inf      = b;
      last_inf = 1;
    }
    else
    { sup      = b;
      last_inf = 0;
    }

    // test de la convergence de l'algorithme
    code = (*convergence) (inf, sup, arg_conv);

  } while ((compteur < 100) && (code == CONV1_AUCUNE) && ((sup.x () - inf.x ()) > eps));

  // retour de la meilleure estimée du zéro
  if (code == CONV1_AUCUNE)
  { // c'est la taille de l'intervalle qui est devenue trop faible
    return last_inf ? inf : sup;
  }
  else
  { // l'algorithme a bien convergé
    return (code == CONV1_INF) ? inf : sup;
  }

}
