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
//>       Resolution2.cpp
//
//$Resume
//       fichier d'implantation des fonctions de résolutions à l'ordre 2
//
//$Description
//       Module de définition des fonctions
//
//$Contenu
//>       double ExtremumNewSec()    
//>       Variation2 ExtremumNewSec()
//>       double NewtonSecante()     
//>       Variation2 NewtonSecante() 
//
//$Historique
//       $Log: Resolution2.cpp,v $
//       Revision 1.13  2003/02/04 09:29:46  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.12  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.11.2.1  2000/03/30 15:36:06  cantor
//       ajout du copyright CNES
//
//       Revision 1.11  1999/08/05 09:55:07  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.10.2.2  1999/06/28 15:14:07  cantor
//       limitation du nombre de boucles des fonctions ExtremumNewSec
//       et NewtonSecante
//
//       Revision 1.10.2.1  1999/04/26 10:36:38  cantor
//       ExtremumNewSec : utilisation de la méthode de Newton en deux points
//       NewtonSecante : simplification des imbrications de tests
//
//       Revision 1.10  1998/10/05 13:30:59  cantor
//       utilisation de la constante cantorEpsilon de cantor/Util.h
//
//       Revision 1.9  1998/10/05 12:40:08  cantor
//       remplacement de la constante DBL_EPSILON par 1.0e-15
//       (pour éviter les problèmes de non-portabilité)
//
//       Revision 1.8  1998/07/29 11:37:05  cantor
//       élimination de float.h
//
//       Revision 1.7  1998/06/24 10:11:01  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:39:16  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:54:35  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:32:44  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 10:46:40  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.2  1994/11/26 15:17:24  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/11/09 16:25:07  mercator
//       Initial revision
//
//$Version
//       $Id: Resolution2.cpp,v 1.13 2003/02/04 09:29:46 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Util.h"
#include "cantor/Resolution2.h"
#include "cantor/CantorErreurs.h"

double ExtremumNewSec (TypeFoncVD2   f,           void*  arg,
                       TypeFoncConv2 convergence, void*  arg_conv,
                       double        a,           double b)
{ Variation2 va (a, (*f) (a, arg));
  Variation2 vb (b, (*f) (b, arg));

  return ExtremumNewSec (f, arg, convergence, arg_conv, va, vb).x ();

}

Variation2 ExtremumNewSec (TypeFoncVD2   f,           void* arg,
                           TypeFoncConv2 convergence, void* arg_conv,
                           const Variation2& a, const Variation2& b)
{ // remise en ordre des bornes
  Variation2 inf = (a.x () < b.x ()) ? a : b;
  Variation2 sup = (a.x () < b.x ()) ? b : a;
  int        last_inf;

  // correction du sens de variation donné par les dérivées
  // (si a et b sont des extremums, le signe des dérivées n'est pas fiable)
  if (inf.y ().f1 () <= sup.y ().f1 ())
  { inf.simuleCroissante   ();
    sup.simuleCroissante   ();
  }
  else
  { inf.simuleDecroissante ();
    sup.simuleDecroissante ();
  }

  double           eps;
  CodeConvergence2 code;
  int compteur = 0;
  do
  { // boucle de réduction de l'intervalle de recherche
    compteur++;

    double xi       = inf.x ();
    double yi       = inf.y ().f1 ();
    double absi     = fabs (yi);
    double yi_prime = inf.y ().f2 ();

    double xs       = sup.x ();
    double ys       = sup.y ().f1 ();
    double abss     = fabs (ys);
    double ys_prime = sup.y ().f2 ();

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
    Variation2 b (t, (*f) (t, arg));

    // mise à jour des bornes de l'intervalle encadrant la racine
    if (inf.croissante ())
      b.simuleCroissante   ();
    else
      b.simuleDecroissante ();
    if (((b.y ().f1 () <= 0.0) && (inf.croissante   ()))
     || ((b.y ().f1 () >  0.0) && (inf.decroissante ())))
    { inf      = b;
      last_inf = 1;
    }
    else
    { sup      = b;
      last_inf = 0;
    }

    // test de la convergence de l'algorithme
    code = (*convergence) (inf, sup, arg_conv);

  } while ((compteur < 100) && (code == CONV2_AUCUNE) && ((sup.x () - inf.x ()) > eps));

  // retour de la meilleure estimée du zéro
  if (code == CONV2_AUCUNE)
  { // c'est la taille de l'intervalle qui est devenue trop faible
    return last_inf ? inf : sup;
  }
  else
  { // l'algorithme a bien convergé
    return (code == CONV2_INF) ? inf : sup;
  }

}

double NewtonSecante (TypeFoncVD2   f,           void*  arg,
                      TypeFoncConv2 convergence, void*  arg_conv,
                      double        a,           double b)
{ Variation2 va (a, (*f) (a, arg));
  Variation2 vb (b, (*f) (b, arg));

  return (NewtonSecante (f, arg, convergence, arg_conv, va, vb)).x ();

}

Variation2 NewtonSecante (TypeFoncVD2   f,           void* arg,
                          TypeFoncConv2 convergence, void* arg_conv,
                          const Variation2& a, const Variation2& b)
{ // remise en ordre des bornes
  Variation2  inf = (a.x () < b.x ()) ? a : b;
  Variation2  sup = (a.x () < b.x ()) ? b : a;
  int         last_inf;

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

  double           eps;
  CodeConvergence2 code;
  int compteur = 0;
  do
  { // boucle de réduction de l'intervalle de recherche
    compteur++;

    double xi        = inf.x ();
    double yi        = inf.y ().f0 ();
    double absi      = fabs (yi);
    double yi_prime  = inf.y ().f1 ();
    double yi_prime2 = inf.y ().f2 ();

    double xs        = sup.x ();
    double ys        = sup.y ().f0 ();
    double abss      = fabs (ys);
    double ys_prime  = sup.y ().f1 ();
    double ys_prime2 = sup.y ().f2 ();

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
    // recherche d'un nouveau t par la méthode de Newton améliorée
    if (fabs (ys) >= fabs (yi))
    { // c'est la borne inf qui est la plus proche
      t = xi
        - (2.0 * yi * yi_prime) / (2.0 * yi_prime * yi_prime - yi * yi_prime2);
    }
    else
    { // c'est la borne sup qui est la plus proche
      t = xs
        - (2.0 * ys * ys_prime) / (2.0 * ys_prime * ys_prime - ys * ys_prime2);
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
    Variation2 b (t, (*f) (t, arg));

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

  } while ((compteur < 100) && (code == CONV2_AUCUNE) && ((sup.x () - inf.x ()) > eps));

  // retour de la meilleure estimée du zéro
  if (code == CONV2_AUCUNE)
  { // c'est la taille de l'intervalle qui est devenue trop faible
    return last_inf ? inf : sup;
  }
  else
  { // l'algorithme a bien convergé
    return (code == CONV2_INF) ? inf : sup;
  }

}
