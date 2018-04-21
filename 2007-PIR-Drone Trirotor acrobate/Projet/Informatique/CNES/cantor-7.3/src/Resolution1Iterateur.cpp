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
//>       Resolution1Iterateur.cpp
//
//$Resume
//       fichier d'implantation de la classe Resolution1Iterateur
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       static CodeConvergence1 ConvergenceXOuY()
//>       static double VariationEstimee()         
//>       static CodeConvergence1 TousPositifs()   
//>       static CodeConvergence1 TousNegatifs()   
//>       class Resolution1Iterateur               
//>         Resolution1Iterateur()                 
//>         reinitialise()                         
//>         zeroSuivant()                          
//
//$Historique
//       $Log: Resolution1Iterateur.cpp,v $
//       Revision 1.22  2003/02/04 09:29:29  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.21  2001/06/05 15:42:49  cantor
//       suppression d'un argument inutilisé
//
//       Revision 1.20  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.19.2.1  2000/03/30 15:36:06  cantor
//       ajout du copyright CNES
//
//       Revision 1.19  1999/08/05 09:55:07  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.18.2.1  1999/04/26 10:38:06  cantor
//       élimination d'évaluations inutiles dans les convergences d'extremums
//
//       Revision 1.18  1998/10/05 13:31:24  cantor
//       utilisation de la constante cantorEpsilon de cantor/Util.h
//
//       Revision 1.17  1998/10/05 12:39:21  cantor
//       remplacement de la constante DBL_EPSILON par 1.0e-15
//       (pour éviter les problèmes de non-portabilité)
//
//       Revision 1.16  1998/06/24 10:10:51  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.15  1998/04/26 15:24:04  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.14  1998/01/22 10:37:19  luc
//       mise en cohérence de listes d'initialisation de constructeurs
//       et de l'ordre des attributs dans la classe
//
//       Revision 1.13  1997/09/10 08:52:40  luc
//       reconnaissance correcte des zéros en fin d'intervalle
//
//       Revision 1.12  1997/07/06 10:39:11  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.11  1997/03/26 06:54:34  luc
//       changement des conventions de nommage
//       
//       Revision 1.10  1997/03/24 09:32:43  luc
//       passage de SCCS à RCS
//       
//       Revision 1.9  1996/07/16 10:41:57  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.8  1995/06/26 16:31:29  mercator
//       encapsulation de la verification d'inversion de pas
//       dans des directives de compilation conditionnelles
//       (la verification confond discontinuite et inversions: a utiliser avec precautions)
//       
//       Revision 1.7  1995/01/30 07:58:19  mercator
//       correction d'un test de convergence (seul le point inf etait teste)
//       
//       Revision 1.6  1995/01/26 16:20:34  mercator
//       correction d'un probleme lorsque l'un des points de dichotomie tombe
//       exactement sur un des zeros de la fonction (il n'etait pas detecte)
//       
//       Revision 1.5  1994/12/12 15:14:40  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.4  1994/11/26 15:17:18  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.3  1994/11/09 16:03:55  mercator
//       remplacement de la fonction "lance" par "erreur"
//       
//       Revision 1.2  1994/08/03 05:53:55  mercator
//       correction d'une erreur empechant la detection des zeros
//       pres de la fin de l'intervalle de recherche
//       modification du choix du point de convergence des extremums
//       
//       Revision 1.1  1994/07/27 14:53:32  luc
//       Initial revision
//
//$Version
//       $Id: Resolution1Iterateur.cpp,v 1.22 2003/02/04 09:29:29 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Util.h"
#include "cantor/Resolution1Iterateur.h"

static CodeConvergence1 ConvergenceXOuY (const Variation1& inf,
                                         const Variation1& sup,
                                         void* donnee)
{ // indicateur de convergence vers un zéro

  // récupération du pointeur sur l'instance de Resolution1Iterateur
  Resolution1Iterateur* iter = (Resolution1Iterateur*) donnee;

  double dx    = fabs (sup.x () - inf.x ());
  double y_inf = fabs (inf.y ().f0 ());
  double y_sup = fabs (sup.y ().f0 ());

  if ((dx >= iter->convergenceX ())
      &&
      (y_inf >= iter->convergenceY ()) && (y_sup >= iter->convergenceY ())
     )
    return CONV1_AUCUNE;
  else
    return (y_inf <= y_sup) ? CONV1_INF : CONV1_SUP;

}

static double VariationEstimee (double ta, const ValeurDerivee1& fa,
                                double tb, const ValeurDerivee1& fb)
{ // estimation de la variation de la fonction sur l'intervalle

  if (((fa.f0 () <= 0.0) && (fb.f0 () >= 0.0))
      ||
      ((fa.f0 () >= 0.0) && (fb.f0 () <= 0.0)))
  { // la fonction change de signe, la variation relative est infinie
    return 1.0e10;
  }

  // calcul de l'intersection des modèles linéaires en a et b
  double y_inters = (fb.f1 () * (fa.f0 () - ta * fa.f1 ())
                   - fa.f1 () * (fb.f0 () - tb * fb.f1 ())
                    ) / (fb.f1 () - fa.f1 ());

  // estimation de l'ecart maximal
  double ecart     = max (fabs (y_inters - fa.f0 ()),
                          fabs (y_inters - fb.f0 ()));
  double reference = min (fabs (fa.f0 ()), fabs (fb.f0 ()));

  // variation relative de la valeur de la fonction (estimation)
  return ecart / max (reference, cantorEpsilon);

}

static CodeConvergence1 TousPositifs (const Variation1& inf,
                                      const Variation1& sup,
                                      void*)
{ // indicateur de convergence vers un maximum local
  // on s'arrête soit quand tout l'intervalle est positif
  // soit quand la variation relative devient trop faible
  if (((inf.y ().f0 () <= 0.0) || (sup.y ().f0 () <= 0.0))
      &&
      (VariationEstimee (inf.x (), inf.y (), sup.x (), sup.y ()) >= 1.0e-9))
    return CONV1_AUCUNE;
  else
    return CONV1_SUP; // le sup est plus proche du tronçon suivant

}

static CodeConvergence1 TousNegatifs (const Variation1& inf,
                                      const Variation1& sup,
                                      void*)
{ // indicateur de convergence vers un minimum local
  // on s'arrête soit quand tout l'intervalle est négatif
  // soit quand la variation relative devient trop faible
  if (((inf.y ().f0 () >= 0.0) || (sup.y ().f0 () >= 0.0))
      &&
      (VariationEstimee (inf.x (), inf.y (), sup.x (), sup.y ()) >= 1.0e-9))
    return CONV1_AUCUNE;
  else
    return CONV1_SUP; // le sup est plus proche du tronçon suivant

}

Resolution1Iterateur::Resolution1Iterateur (TypeFoncVD1 f, void* arg,
                                            double a, double b,
                                            double pas,
                                            double convergenceX,
                                            double convergenceY)
  : convergenceX_ (convergenceX), convergenceY_ (convergenceY),
    pas_ (pas), f_ (f), arg_ (arg)
{ if (a <= b)
  { tMin_ = a;
    tMax_ = b;
  }
  else
  { tMin_ = b;
    tMax_ = a;
  }

  reinitialise ();

}

Resolution1Iterateur::Resolution1Iterateur (TypeFoncVD1 f, void* arg,
                                            double a, double b,
                                            int n,
                                            double convergenceX,
                                            double convergenceY)
  : convergenceX_ (convergenceX), convergenceY_ (convergenceY),
    f_ (f), arg_ (arg)
{ if (a <= b)
  { tMin_ = a;
    tMax_ = b;
    pas_  = (b - a) / n;
  }
  else
  { tMin_ = b;
    tMax_ = a;
    pas_  = (a - b) / n;
  }

  reinitialise ();

}

void Resolution1Iterateur::reinitialise ()
{ precedente_ = Variation1 (tMin_, evalueFonction (tMin_));
  if (precedente_.croissante ())
    min_ = precedente_;
  else
    max_ = precedente_;

}

double Resolution1Iterateur::zeroSuivant ()
{ // itération sur les zéros de la fonction
  int    dernier = 0;
  double t;

  // vérification de dépassement de l'intervalle spécifié à la construction
  if (precedente_.x () > tMax_)
    return precedente_.x ();

  while (1)
  { // boucle de parcours de l'intervalle

    if (precedente_.x () + pas_ > tMax_)
    { // réduction du pas à l'approche de la fin de l'intervalle
      pas_ = tMax_ - precedente_.x ();

      // il ne faut pas que le pas devienne nul !...
      const double eps = 2.0 * cantorEpsilon
                             * max (1.0, fabs (precedente_.x ()));
      if (pas_ < eps)
        pas_ = eps;

      dernier = 1;

    }

    // progression dans l'intervalle
    t = precedente_.x () + pas_;
    if (t > tMax_)
    { // on a dépassé la fin de l'intervalle, on se positionne loin par sécurité
      precedente_ = Variation1 (tMin_ + 1.0e6 * (tMax_ - tMin_),
                                ValeurDerivee1 (0.0, 0.0));
      return precedente_.x ();
    }

    // calcul de la fonction et de ses dérivées au point courant
    Variation1 courante (t, evalueFonction (t));

    if (courante.sens () == precedente_.sens ())
    { // a priori, on reste dans le domaine de monotonie

      if (precedente_.croissante ())
      { // la fonction croît normalement

        if (courante.y ().f0 () <= 0.0)
        { // on se rapproche de l'axe des abscisses par dessous

          if (dernier && (courante.y ().f0 () >= -convergenceY_))
          { // le point courant peut être considéré comme un zéro
            precedente_ = courante;
            min_        = courante;

            return courante.x ();

          }

          // on peut rapprocher le min sans perdre de zéro
          min_ = courante;

        }
        else if (min_.y ().f0 () <= 0.0)
        { // on vient de franchir un zéro
          double t0 = NewtonSecante (f_, arg_, ConvergenceXOuY, (void *) this,
                                     min_, courante
                                    ).x ();

          // préparation de la recherche suivante
          precedente_ = courante;
          min_        = courante;

          return t0;

        }
      }
      else
      { // la fonction décroît normalement
        if (courante.y ().f0 () >= 0.0)
        { // on se rapproche de l'axe des abscisses par dessus

          if (dernier && (courante.y ().f0 () <= convergenceY_))
          { // le point courant peut être considéré comme un zéro
            precedente_ = courante;
            min_        = courante;

            return courante.x ();

          }

          // on peut rapprocher le max sans perdre de zéro
          max_ = courante;
        }
        else if (max_.y ().f0 () >= 0.0)
        { // on vient de franchir un zéro
          double t0 = NewtonSecante (f_, arg_, ConvergenceXOuY, (void *) this,
                                     max_, courante
                                    ).x ();

          // préparation de la recherche suivante
          precedente_ = courante;
          max_        = courante;

          return t0;

        }
      }
    }
    else
    { // il y a un extremum dans [precedente.t; courante.t]
      int reinitialiser_min = 0;
      int reinitialiser_max = 0;

      if (precedente_.croissante ())
      { // on approche d'un maximum local

        if ((precedente_.y ().f0 () <= 0.0) || (courante.y ().f0 () <= 0.0))
        { // on ne peut pas garantir que tout l'intervalle soit de signe constant
          max_     = ExtremumNewSec (f_, arg_, TousPositifs, (void *) 0,
                                     precedente_, courante);
          max_.simuleDecroissante ();  // le tronçon suivant descendra
          courante = max_;             // le tronçon suivant partira du max
        }
        else
        { // on sait d'emblée que tout l'intervalle est positif
          max_              = precedente_;
          reinitialiser_max = 1; // démarrage décroissant du tronçon suivant
        }
      }
      else
      { // on approche d'un minimum local

        if ((precedente_.y ().f0 () >= 0.0) || (courante.y ().f0 () >= 0.0))
        { // on ne peut pas garantir que tout l'intervalle soit de signe constant
          min_     = ExtremumNewSec (f_, arg_, TousNegatifs, (void *) 0,
                                     precedente_, courante);
          min_.simuleCroissante ();    // le troncon suivant montera
          courante = min_;             // le troncon suivant partira du min
        }
        else
        { // on sait d'emblée que tout l'intervalle est négatif
          min_              = precedente_;
          reinitialiser_min = 1; // démarrage croissant du tronçon suivant
        }
      }

      if ((min_.y ().f0 () <= 0.0) && (max_.y ().f0 () >= 0.0))
      { // recherche d'un zéro dans l'intervalle monotone identifié
        double t0 = NewtonSecante (f_, arg_, ConvergenceXOuY, (void *) this,
                                   min_, max_
                                  ).x ();

        // préparation de la recherche sur le tronçon suivant
        precedente_ = courante;
        if (reinitialiser_min)
          min_ = courante;
        else if (reinitialiser_max)
          max_ = courante;

        // retour du zéro identifié
        return t0;

      }

      // préparation de la recherche sur le tronçon suivant
      if (reinitialiser_min)
        min_ = courante;
      else if (reinitialiser_max)
        max_ = courante;

    }

    // passage au point suivant
    precedente_ = courante;

  }
}
