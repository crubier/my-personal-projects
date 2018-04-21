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
//>       Rotation.cpp
//
//$Resume
//       fichier d'implantation de la classe Rotation
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       template <class T> void corrigeOrthog()
//>       class Rotation                        
//>         Rotation()                          
//>         operator =()                        
//>         axe()                               
//>         angle()                             
//>         initMatrice()                       
//>         operator()()                        
//>         operator()()                        
//
//$Historique
//       $Log: Rotation.cpp,v $
//       Revision 2.4  2003/02/04 09:37:14  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions (CC <- CPP)
//
//       Revision 2.3  2002/02/14 08:57:10  cantor
//       Declaration de small au niveau lmethode plutot qu'au niveau classe car small existe dans d'autres classes - detecte par CC, ignore par gcc
//
//       Revision 2.2  2002/02/04 09:14:37  cantor
//       ajout d'une protection lors du calcul des angles de rotation de Cardan ou d'Euler
//
//       Revision 2.2  2002/18/01 15:27:58  cantor
//       ajout du controle des sinus ou cosinus des angles de rotation de 
//       Cardan et d'Euler et ajout de l'erreur singularite_angle
//
//       Revision 2.1  2001/06/05 15:27:58  cantor
//       passage au mécanisme des exceptions pour la gestion des erreurs,
//       ajout des angles de Cardan et d'Euler
//
//       Revision 1.26  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.25.2.1  2000/03/30 17:10:27  cantor
//       ajout du copyright CNES
//
//       Revision 1.25  1999/08/05 09:55:57  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.24.2.1  1999/04/26 09:37:39  cantor
//       remplacement de abs par fabs
//
//       Revision 1.24  1999/02/05 07:39:55  cantor
//       élimination d'un const dans une signature (encore ...)
//
//       Revision 1.23  1998/10/05 13:33:24  cantor
//       utilisation de la constante cantorEpsilon de cantor/Util.h
//
//       Revision 1.22  1998/07/29 11:50:33  cantor
//       élimination de float.h
//
//       Revision 1.21  1998/07/24 14:10:16  luc
//       ajout d'une vérification de l'orientation du repère
//       lors de la construction à partir d'une matrice
//
//       Revision 1.20  1998/06/24 10:06:10  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.19  1998/04/26 15:24:08  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.18  1998/04/18 13:41:21  luc
//       élimination de la méthode estValide
//
//       Revision 1.17  1998/02/19 17:25:22  luc
//       élimination du const rajouté à la version précédente
//
//       Revision 1.16  1998/01/22 10:42:43  luc
//       ajout d'un qualificatif const dans une signature
//
//       Revision 1.15  1997/11/06 20:00:42  luc
//       correction d'un test d'alignement incohérent avec la précision machine
//
//       Revision 1.14  1997/07/06 10:33:38  luc
//       ajout d'un en-tête de fichier
//       correction de tests de sécurité sur la norme de l'axe
//
//       Revision 1.13  1997/04/17 06:19:49  luc
//       transfert de corrigeOrthog dans l'interface publique de la bibliothèque
//       inversion du code de retour de corrigOrthog
//       intégration de fonctions statiques dans corrigeOrthog
//       correction d'une signature de template
//       
//       Revision 1.12  1997/03/26 06:39:49  luc
//       changement des conventions de nommage
//       
//       Revision 1.11  1997/03/24 09:22:19  luc
//       passage de SCCS à RCS
//       
//       Revision 1.10  1996/07/16 11:58:55  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       utilisation de l'encapsulation de math.h garantissant la définition de M_PI
//       suppression de l'opérateur == (il n'avait pas de raison d'être intrinsèque,
//       il n'était présent jusqu'ici qu'à cause des tools.h++)
//       
//       Revision 1.9  1995/08/16 12:14:39  mercator
//       elimination d'une division par 0 dans la construction de l'identite
//       a partir d'un couple de vecteurs et de son image
//       
//       Revision 1.8  1995/07/11 16:03:20  mercator
//       correction d'une erreur dans le cas: u1 = v1 et u2 = -v2
//       (rotation d'angle PI autour du premier vecteur fourni)
//       la formulation precedente engendrait une division par 0
//       
//       Revision 1.7  1995/06/26 16:25:01  mercator
//       elimination d'un const dans une signature template trop compliquee
//       modification de la portee d'une variable de boucle
//       
//       Revision 1.6  1995/01/19 06:32:03  mercator
//       elimination des references inutilisees a la librairie rwmth (DoubleGenMat)
//       
//       Revision 1.5  1994/12/12 15:14:46  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.4  1994/11/26 14:57:39  mercator
//       correction d'un oubli de declaration
//       correction d'une erreur d'indice
//       remplacement du pragma interface par une variable statique
//       
//       Revision 1.3  1994/11/10 07:13:41  mercator
//       simplification de la methode d'orthogonalisation de matrice
//       ajout d'un argument CantorErreurs* a certaines fonctions
//       remplacement de la fonction "lance" par "erreur"
//       correction du type de la fonction template "ecartQuadratique"
//       
//       Revision 1.2  1994/08/09 08:38:38  mercator
//       correction d'erreurs de syntaxe sur des appels a operator ()
//       dans des portions de code conditionnelles (RWDEBUG)
//       
//       Revision 1.1  1994/07/27 14:57:22  luc
//       Initial revision
//
//$Version
//       $Id: Rotation.cpp,v 2.4 2003/02/04 09:37:14 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Rotation_cc
#define __cantor_Rotation_cc

#include "cantor/Util.h"

template <class T> void corrigeOrthog (T m [3][3], T orth [3][3],
                                       T convergence)
  throw (CantorErreurs)
{ // recherche de la matrice de rotation "la plus proche" d'une matrice
  // initiale au sens de la norme de Frobenius (somme des carrés des éléments)
  T x [3][3];
  x [0][0] = m [0][0];  x [0][1] = m [0][1];  x [0][2] = m [0][2];
  x [1][0] = m [1][0];  x [1][1] = m [1][1];  x [1][2] = m [1][2];
  x [2][0] = m [2][0];  x [2][1] = m [2][1];  x [2][2] = m [2][2];
  T fn = 0;
  T fn1;

  // correction itérative
  int i = 0;
  while (++i < 11)
  { // calcul d'une itération: Xn+1 = Xn - 0.5 * (Xn.Dt.Xn - D)

    // Xn.Dt.Xn
    int i;
    for (i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        orth [i][j] = x [i][0] * (m [0][0] * x [0][j]
                                + m [1][0] * x [1][j]
                                + m [2][0] * x [2][j]
                                 )
                    + x [i][1] * (m [0][1] * x [0][j]
                                + m [1][1] * x [1][j]
                                + m [2][1] * x [2][j]
                                 )
                    + x [i][2] * (m [0][2] * x [0][j]
                                + m [1][2] * x [1][j]
                                + m [2][2] * x [2][j]
                                 );

    // Xn+1
    for (i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        orth [i][j] = x [i][j] - 0.5 * (orth [i][j] - m [i] [j]);

    // écart quadratique
    T d [3][3];
    d [0][0] = orth [0][0] - m [0][0];
    d [0][1] = orth [0][1] - m [0][1];
    d [0][2] = orth [0][2] - m [0][2];
    d [1][0] = orth [1][0] - m [1][0];
    d [1][1] = orth [1][1] - m [1][1];
    d [1][2] = orth [1][2] - m [1][2];
    d [2][0] = orth [2][0] - m [2][0];
    d [2][1] = orth [2][1] - m [2][1];
    d [2][2] = orth [2][2] - m [2][2];

    fn1 = d [0][0] * d [0][0] + d [0][1] * d [0][1] + d [0][2] * d [0][2]
        + d [1][0] * d [1][0] + d [1][1] * d [1][1] + d [1][2] * d [1][2]
        + d [2][0] * d [2][0] + d [2][1] * d [2][1] + d [2][2] * d [2][2];

    // test de convergence
    if (fabs (fn1 - fn) <= convergence)
      return;

    // préparation de l'itération suivante
    x [0][0] = orth [0][0];  x [0][1] = orth [0][1];  x [0][2] = orth [0][2];
    x [1][0] = orth [1][0];  x [1][1] = orth [1][1];  x [1][2] = orth [1][2];
    x [2][0] = orth [2][0];  x [2][1] = orth [2][1];  x [2][2] = orth [2][2];
    fn       = fn1;

  }

  // on n'a pas convergé en 10 itérations
  throw CantorErreurs (CantorErreurs::matrice_non_orthogonalisable);

}

// construction d'un quaternion à partir d'un axe et d'un angle
template <class T>
Rotation<T>::Rotation (const Vecteur3<T>& axe, const T& angle, T norme)
  throw (CantorErreurs)
{

  if (norme < T (cantorEpsilon))
  { // la norme n'a pas été fournie en argument (valeur par défaut = -1)
    norme = axe.norme ();

    if (norme < T (cantorEpsilon))
      throw CantorErreurs (CantorErreurs::axe_rotation_nul);
  }

  q0_ = angle * -0.5;
  q_  = axe * (sin (q0_) / norme);
  q0_ = cos (q0_);

}

// construction d'un quaternion à partir d'une matrice
template <class T>
Rotation<T>::Rotation (T matrice [3][3], T convergence)
  throw (CantorErreurs)
{

  T x0;
  T x1;
  T x2;
  T x3;

  // calcul de la vraie matrice de rotation "la plus proche"
  T corrigee [3][3];
  corrigeOrthog (matrice, corrigee, convergence);

  // vérification de l'orientation du repère par le déterminant
  T det = corrigee [0][0] * (corrigee [1][1] * corrigee [2][2]
                           - corrigee [2][1] * corrigee [1][2])
        - corrigee [1][0] * (corrigee [0][1] * corrigee [2][2]
                           - corrigee [2][1] * corrigee [0][2])
        + corrigee [2][0] * (corrigee [0][1] * corrigee [1][2]
                           - corrigee [1][1] * corrigee [0][2]);
  if (det < 0.0)
    throw CantorErreurs (CantorErreurs::repere_indirect);

  T s = corrigee [0][0] + corrigee [1][1] + corrigee [2][2];
  if (s > -0.1)
  { x0    = sqrt (s + 1.0) * 0.5;
    T inv = 0.25 / x0;
    x1    = inv * (corrigee [1][2] - corrigee [2][1]);
    x2    = inv * (corrigee [2][0] - corrigee [0][2]);
    x3    = inv * (corrigee [0][1] - corrigee [1][0]);
  }
  else
  { s = corrigee [0][0] - corrigee [1][1] - corrigee [2][2];
    if (s > -0.1)
    { x1    = sqrt (s + 1.0) * 0.5;
      T inv = 0.25 / x1;
      x0    = inv * (corrigee [1][2] - corrigee [2][1]);
      x2    = inv * (corrigee [0][1] + corrigee [1][0]);
      x3    = inv * (corrigee [0][2] + corrigee [2][0]);
    }
    else
    { s = corrigee [1][1] - corrigee [0][0] - corrigee [2][2];
      if (s > -0.1)
      { x2    = sqrt (s + 1.0) * 0.5;
        T inv = 0.25 / x2;
        x0    = inv * (corrigee [2][0] - corrigee [0][2]);
        x1    = inv * (corrigee [0][1] + corrigee [1][0]);
        x3    = inv * (corrigee [2][1] + corrigee [1][2]);
      }
      else
      { s   = corrigee [2][2] - corrigee [0][0] - corrigee [1][1];
        x3    = sqrt (s + 1.0) * 0.5;
        T inv = 0.25 / x3;
        x0    = inv * (corrigee [0][1] - corrigee [1][0]);
        x1    = inv * (corrigee [0][2] + corrigee [2][0]);
        x2    = inv * (corrigee [2][1] + corrigee [1][2]);
      }
    }
  }

  q0_ = x0;
  q_  = Vecteur3<T> (x1, x2, x3);

}

// calcul d'une rotation à partir de la transformée d'un couple de vecteurs
template <class T>
Rotation<T>::Rotation (Vecteur3<T> u1, Vecteur3<T> u2,
                       Vecteur3<T> v1, Vecteur3<T> v2)
  throw (CantorErreurs)
{

  // normalisation des vecteurs
  u1.normalise ();
  u2.normalise ();
  v1.normalise ();
  v2.normalise ();

  // recalage de v2 pour avoir (u1|u2) = (v1|v2)
  T scal_u = u1 | u2;
  T scal_v = v1 | v2;
  T coeff  = sqrt ((T (1.0) - scal_u * scal_u) / (T (1.0) - scal_v * scal_v));
  v2      *= coeff;
  v2      += (scal_u - coeff * scal_v) * v1;

  // calcul de la composante vectorielle
  Vecteur3<T>* ptrU      = &u1;
  Vecteur3<T>* ptrV      = &v1;
  Vecteur3<T>  v1MoinsU1 = (v1 - u1);
  Vecteur3<T>  v2MoinsU2 = (v2 - u2);
  Vecteur3<T>  k = v1MoinsU1 ^ v2MoinsU2;
           T   c = k | (u1 ^ u2);

  if (c < T (1.0e-10))
  { // q_ est dans le plan (u1, u2): on essaie d'autres vecteurs
    coeff = T (1.0) / sqrt (T (1.0) - scal_u * scal_u);

    Vecteur3<T> u3 = (u1 ^ u2) * coeff;
    Vecteur3<T> v3 = (v1 ^ v2) * coeff;

    Vecteur3<T> v3MoinsU3 = (v3 - u3);
    k = v1MoinsU1 ^ v3MoinsU3;
    c = k | (u1 ^ u3);

    if (c < T (1.0e-10))
    { // q_ est aligné avec u1, on essaie (u2, u3) et (v2, v3)
      k = v2MoinsU2 ^ v3MoinsU3;
      c = k | (u2 ^ u3);

      if (c < T(1.0e-10))
      { // q_ est aligné avec tout vecteur: rotation identité
        q_  = Vecteur3<T> (0.0, 0.0, 0.0);
        q0_ = 1.0;
        return;
      }

      // il faudra utiliser u2 et v2 pour calculer la composante scalaire
      ptrU = &u2;
      ptrV = &v2;

    }

  }
   c = sqrt (c);
  q_ = k / (c + c);

  // calcul de la composante scalaire
   k  = *ptrU ^ q_;
   c  = k | k;
  q0_ = (*ptrV | k) / (c + c);

}

// calcul d'une des rotations transformant un vecteur en un autre
template <class T>
Rotation<T>::Rotation (Vecteur3<T> u, Vecteur3<T> v)
  throw (CantorErreurs)
{

  // normalisation des vecteurs
  u.normalise ();
  v.normalise ();

  T scal = u | v;
  if (scal < T (2.0 * cantorEpsilon - 1.0)) // cas particulier u = -v:
  {
    Vecteur3<T> w = u.orthogonal ();        // rotation d'angle PI
    *this = Rotation<T> (w, T (M_PI));      // autour d'un axe normal à u 
  }
  else
  { // cas général (u, v) définit un plan
    q0_ = sqrt (T (0.5) * (T (1.0) + scal));
    q_  = (v ^ u) / (T (2.0) * q0_);
  }

}

template <class T> Rotation<T>::Rotation  (AxesRotation ordre,
                                           const T& alpha1,
                                           const T& alpha2,
                                           const T& alpha3)
  throw (CantorErreurs)
{
  // vecteur canoniques
  Vecteur3<T> xCan (T (1.0), T (0.0), T (0.0));
  Vecteur3<T> yCan (T (0.0), T (1.0), T (0.0));
  Vecteur3<T> zCan (T (0.0), T (0.0), T (1.0));

  switch (ordre)
  {
    case XYZ :
    {
      Rotation<T> r1 = Rotation<T> (xCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (yCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (zCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case XZY :
    {
      Rotation<T> r1 = Rotation<T> (xCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (zCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (yCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case YXZ :
    {
      Rotation<T> r1 = Rotation<T> (yCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (xCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (zCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case YZX :
    {
      Rotation<T> r1 = Rotation<T> (yCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (zCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (xCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case ZXY :
    {
      Rotation<T> r1 = Rotation<T> (zCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (xCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (yCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case ZYX :
    {
      Rotation<T> r1 = Rotation<T> (zCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (yCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (xCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case XYX :
    {
      Rotation<T> r1 = Rotation<T> (xCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (yCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (xCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case XZX :
    {
      Rotation<T> r1 = Rotation<T> (xCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (zCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (xCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case YXY :
    {
      Rotation<T> r1 = Rotation<T> (yCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (xCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (yCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case YZY :
    {
      Rotation<T> r1 = Rotation<T> (yCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (zCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (yCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case ZXZ :
    {
      Rotation<T> r1 = Rotation<T> (zCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (xCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (zCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    case ZYZ :
    {
      Rotation<T> r1 = Rotation<T> (zCan, alpha1, T (1.0));
      Rotation<T> r2 = Rotation<T> (yCan, alpha2, T (1.0));
      Rotation<T> r3 = Rotation<T> (zCan, alpha3, T (1.0));
      *this = r1 (r2 (r3));
    }
    break;

    default :
    {
      throw CantorErreurs (CantorErreurs::erreur_interne,
                           __LINE__, __FILE__);
    }
    break;

  }

}

// affectation
template <class T> Rotation<T>& Rotation<T>::operator = (const Rotation<T>& r)
{

  if (this != &r)           // protection contre x = x
  {
    q_  = r.q_;
    q0_ = r.q0_;
  }

  return *this;

}

// extraction de l'axe d'une rotation
template <class T> Vecteur3<T>  Rotation<T>::axe () const
{ T sin_carre = q_ | q_;
  if (sin_carre <= cantorEpsilon)
    return Vecteur3<T> (T (1.0), T (0.0), T (0.0));
  else if (q0_ < T (0.0))
    return q_ /  sqrt (sin_carre);
  else
    return q_ / -sqrt (sin_carre);

}

// extraction de l'angle d'une rotation (entre 0 et 2PI)
template <class T> T Rotation<T>::angle () const
{ T theta_sur_2;
  if ((q0_ < T (-0.1)) || (q0_ > T (0.1)))
    theta_sur_2 =  asin (q_.norme ());
  else if (q0_ < T (0.0))
    theta_sur_2 = acos (-q0_);
  else
    theta_sur_2 = acos (q0_);
  return theta_sur_2 + theta_sur_2;

}

// extraction des angles de rotation élémentaires
template <class T> void Rotation<T>::initAngles (AxesRotation ordre,
                                                 T *ptrAlpha1,
                                                 T *ptrAlpha2,
                                                 T *ptrAlpha3) const
  throw (CantorErreurs)
{
  // vecteur canoniques
  Vecteur3<T> xCan (T (1.0), T (0.0), T (0.0));
  Vecteur3<T> yCan (T (0.0), T (1.0), T (0.0));
  Vecteur3<T> zCan (T (0.0), T (0.0), T (1.0));
  Vecteur3<T> v1, v2;

  const double small  = 4.85e-6;
  const double seuilMax = 1. - small;
  const double seuilMin = - seuilMax;

  switch (ordre)
  {
    case XYZ :
      // (*this) (zCan) a comme coordonnées :
      //  sin (theta), -cos (theta) sin (phi), cos (theta) cos (phi)
      // (-*this) (xCan) a comme coordonnées :
      // cos (psi) cos (theta), -sin (psi) cos (theta), sin (theta)
      // et on peut imposer à theta de rester dans [-PI/2 ; +PI/2]
      v1 = (*this) (zCan);
      v2 = (-*this) (xCan);
      if  ((v2.z() < seuilMin) || (v2.z() > seuilMax))
        throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (-(v1.y ()), v1.z ());
      *ptrAlpha2 = asin (v2.z ());
      *ptrAlpha3 = atan2 (-(v2.y ()), v2.x ());
      break;

    case XZY :
      // (*this) (yCan) a comme coordonnées :
      // -sin (psi), cos (psi) cos (phi), cos (psi) sin (phi)
      // (-*this) (xCan) a comme coordonnées :
      // cos (theta) cos (psi), -sin (psi), sin (theta) cos (psi)
      // et on peut imposer à psi de rester dans [-PI/2 ; +PI/2]
      v1 = (*this) (yCan);
      v2 = (-*this) (xCan);
      if ((v2.y() < seuilMin) || (v2.y() > seuilMax))
        throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (v1.z (), v1.y ());
      *ptrAlpha2 = -asin (v2.y ());
      *ptrAlpha3 = atan2 (v2.z (), v2.x ());
      break;

    case YXZ :
      // (*this) (zCan) a comme coordonnées :
      //  cos (phi) sin (theta), -sin (phi), cos (phi) cos (theta)
      // (-*this) (yCan) a comme coordonnées :
      // sin (psi) cos (phi), cos (psi) cos (phi), -sin (phi)
      // et on peut imposer à phi de rester dans [-PI/2 ; +PI/2]
      v1 = (*this) (zCan);
      v2 = (-*this) (yCan);
      if ((v2.z() < seuilMin) || (v2.z() > seuilMax))
          throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (v1.x (), v1.z ());
      *ptrAlpha2 = -asin (v2.z ());
      *ptrAlpha3 = atan2 (v2.x (), v2.y ());
      break;

    case YZX :
      // (*this) (xCan) a comme coordonnées :
      // cos (psi) cos (theta), sin (psi), -cos (psi) sin (theta)
      // (-*this) (yCan) a comme coordonnées :
      // sin (psi), cos (phi) cos (psi), -sin (phi) cos (psi)
      // et on peut imposer à psi de rester dans [-PI/2 ; +PI/2]
      v1 = (*this) (xCan);
      v2 = (-*this) (yCan);
      if ((v2.x() < seuilMin) || (v2.x() > seuilMax))
          throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (-(v1.z ()), v1.x ());
      *ptrAlpha2 = asin (v2.x ());
      *ptrAlpha3 = atan2 (-(v2.z ()), v2.y ());
      break;

    case ZXY :
      // (*this) (yCan) a comme coordonnées :
      // -cos (phi) sin (psi), cos (phi) cos (psi), sin (phi)
      // (-*this) (zCan) a comme coordonnées :
      // -sin (theta) cos (phi), sin (phi), cos (theta) cos (phi)
      // et on peut imposer à phi de rester dans [-PI/2 ; +PI/2]
      v1 = (*this) (yCan);
      v2 = (-*this) (zCan);
      if ((v2.y() < seuilMin) || (v2.y() > seuilMax))
          throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (-(v1.x ()), v1.y ());
      *ptrAlpha2 = asin (v2.y ());
      *ptrAlpha3 = atan2 (-(v2.x ()), v2.z ());
      break;

    case ZYX :
      // (*this) (xCan) a comme coordonnées :
      //  cos (theta) cos (psi), cos (theta) sin (psi), -sin (theta)
      // (-*this) (zCan) a comme coordonnées :
      // -sin (theta), sin (phi) cos (theta), cos (phi) cos (theta)
      // et on peut imposer à theta de rester dans [-PI/2 ; +PI/2]
      v1 = (*this) (xCan);
      v2 = (-*this) (zCan);
      if ((v2.x() < seuilMin) || (v2.x() > seuilMax))
          throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (v1.y (), v1.x ());
      *ptrAlpha2 = -asin (v2.x ());
      *ptrAlpha3 = atan2 (v2.y (), v2.z ());
      break;

    case XYX :
      // (*this) (xCan) a comme coordonnées :
      //  cos (theta), sin (phi1) sin (theta), -cos (phi1) sin (theta)
      // (-*this) (xCan) a comme coordonnées :
      // cos (theta), sin (theta) sin (phi2), sin (theta) cos (phi2)
      // et on peut imposer à theta de rester dans [0 ; PI]
      v1 = (*this) (xCan);
      v2 = (-*this) (xCan);
      if ((v2.x() < seuilMin) || (v2.x() > seuilMax))
          throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (v1.y (), -v1.z ());
      *ptrAlpha2 = acos (v2.x ());
      *ptrAlpha3 = atan2 (v2.y (), v2.z ());
      break;

    case XZX :
      // (*this) (xCan) a comme coordonnées :
      //  cos (psi), cos (phi1) sin (psi), sin (phi1) sin (psi)
      // (-*this) (xCan) a comme coordonnées :
      // cos (psi), -sin (psi) cos (phi2), sin (psi) sin (phi2)
      // et on peut imposer à psi de rester dans [0 ; PI]
      v1 = (*this) (xCan);
      v2 = (-*this) (xCan);
      if ((v2.x() < seuilMin) || (v2.x() > seuilMax))
          throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (v1.z (), v1.y ());
      *ptrAlpha2 = acos (v2.x ());
      *ptrAlpha3 = atan2 (v2.z (), -v2.y ());
      break;

    case YXY :
      // (*this) (yCan) a comme coordonnées :
      //  sin (theta1) sin (phi), cos (phi), cos (theta1) sin (phi)
      // (-*this) (yCan) a comme coordonnées :
      // sin (phi) sin (theta2), cos (phi), -sin (phi) cos (theta2)
      // et on peut imposer à phi de rester dans [0 ; PI]
      v1 = (*this) (yCan);
      v2 = (-*this) (yCan);
      if ((v2.y() < seuilMin) || (v2.y() > seuilMax))
        throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (v1.x (), v1.z ());
      *ptrAlpha2 = acos (v2.y ());
      *ptrAlpha3 = atan2 (v2.x (), -v2.z ());
      break;

    case YZY :
      // (*this) (yCan) a comme coordonnées :
      //  -cos (theta1) sin (psi), cos (psi), sin (theta1) sin (psi)
      // (-*this) (yCan) a comme coordonnées :
      // sin (psi) cos (theta2), cos (psi), sin (psi) sin (theta2)
      // et on peut imposer à psi de rester dans [0 ; PI]
      v1 = (*this) (yCan);
      v2 = (-*this) (yCan);
      if ((v2.y() < seuilMin) || (v2.y() > seuilMax))
        throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (v1.z (), -v1.x ());
      *ptrAlpha2 = acos (v2.y ());
      *ptrAlpha3 = atan2 (v2.z (), v2.x ());
      break;

    case ZXZ :
      // (*this) (zCan) a comme coordonnées :
      //  sin (psi1) sin (phi), -cos (psi1) sin (phi), cos (phi)
      // (-*this) (zCan) a comme coordonnées :
      // sin (phi) sin (psi2), sin (phi) cos (psi2), cos (phi)
      // et on peut imposer à phi de rester dans [0 ; PI]
      v1 = (*this) (zCan);
      v2 = (-*this) (zCan);
      if ((v2.z() < seuilMin) || (v2.z() > seuilMax))
        throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (v1.x (), -v1.y ());
      *ptrAlpha2 = acos (v2.z ());
      *ptrAlpha3 = atan2 (v2.x (), v2.y ());
      break;

    case ZYZ :
      // (*this) (zCan) a comme coordonnées :
      //  cos (psi1) sin (theta), sin (psi1) sin (theta), cos (theta)
      // (-*this) (zCan) a comme coordonnées :
      // -sin (theta) cos (psi2), sin (theta) sin (psi2), cos (theta)
      // et on peut imposer à theta de rester dans [0 ; PI]
      v1 = (*this) (zCan);
      v2 = (-*this) (zCan);
      if ((v2.z() < seuilMin) || (v2.z() > seuilMax))
        throw CantorErreurs (CantorErreurs::singularite_angle);
      *ptrAlpha1 = atan2 (v1.y (), v1.x ());
      *ptrAlpha2 = acos (v2.z ());
      *ptrAlpha3 = atan2 (v2.y (), -v2.x ());
      break;

    break;

    default :
    {
      throw CantorErreurs (CantorErreurs::erreur_interne,
                           __LINE__, __FILE__);
    }
    break;

  }

}

// initialisation d'une matrice de rotation
template <class T> void Rotation<T>::initMatrice (T m [3][3]) const
{ // calcul des produits
  T q0q0  = q0_     * q0_;
  T q0q1  = q0_     * q_.x ();
  T q0q2  = q0_     * q_.y ();
  T q0q3  = q0_     * q_.z ();
  T q1q1  = q_.x () * q_.x ();
  T q1q2  = q_.x () * q_.y ();
  T q1q3  = q_.x () * q_.z ();
  T q2q2  = q_.y () * q_.y ();
  T q2q3  = q_.y () * q_.z ();
  T q3q3  = q_.z () * q_.z ();

  // multiplication par 2 (les additions sont plus rapides pour certains T)
  T q0q0_2 = q0q0 + q0q0;
  T q0q1_2 = q0q1 + q0q1;
  T q0q2_2 = q0q2 + q0q2;
  T q0q3_2 = q0q3 + q0q3;
  T q1q1_2 = q1q1 + q1q1;
  T q1q2_2 = q1q2 + q1q2;
  T q1q3_2 = q1q3 + q1q3;
  T q2q2_2 = q2q2 + q2q2;
  T q2q3_2 = q2q3 + q2q3;
  T q3q3_2 = q3q3 + q3q3;

  // constitution de la matrice
  m [0][0] = q0q0_2 + q1q1_2 - T (1.0);
  m [1][0] = q1q2_2 - q0q3_2;
  m [2][0] = q1q3_2 + q0q2_2;

  m [0][1] = q1q2_2 + q0q3_2;
  m [1][1] = q0q0_2 + q2q2_2 - T (1.0);
  m [2][1] = q2q3_2 - q0q1_2;

  m [0][2] = q1q3_2 - q0q2_2;
  m [1][2] = q2q3_2 + q0q1_2;
  m [2][2] = q0q0_2 + q3q3_2 - T (1.0);

}

// application de la rotation courante à une autre rotation
template <class T>
Rotation<T>  Rotation<T>::operator () (const Rotation<T>&  r) const
{ Vecteur3<T> sq  = q_ * r.q0_ + r.q_ * q0_ + (r.q_ ^ q_);
  T           sq0 = r.q0_ * q0_ - (r.q_ | q_);

  return Rotation<T> (sq0, sq.x (), sq.y (), sq.z ());

}

// application de la rotation courante à un vecteur
template <class T>
Vecteur3<T> Rotation<T>::operator () (const Vecteur3<T>& u) const
{ Vecteur3<T> v  = u * q0_ - (q_ ^ u);
              v *= q0_;
              v += q_ * (q_ | u);
              v += v;
              v -= u;

  return v;

}

#endif
