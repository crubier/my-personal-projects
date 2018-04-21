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
//>       Rotation.h
//
//$Resume
//       fichier d'en-tête de la classe Rotation
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Rotation                                    
//>       template <class T> int corrigeOrthog()            
//>       template <class T> inline Rotation<T> operator -()
//
//$Historique
//       $Log: Rotation.h,v $
//       Revision 2.3  2002/12/10 15:11:03  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui créé par le compilateur
//
//       Revision 2.2  2002/12/02 13:40:25  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 2.1  2001/06/05 15:27:30  cantor
//       passage au mécanisme des exceptions pour la gestion des erreurs,
//       ajout des angles de Cardan et d'Euler
//
//       Revision 1.19  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.18.4.1  2000/03/30 15:36:11  cantor
//       ajout du copyright CNES
//
//       Revision 1.18  1999/02/05 07:39:19  cantor
//       élimination d'un const dans une signature (encore ...)
//
//       Revision 1.17  1998/06/24 15:25:17  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.16  1998/04/26 15:24:08  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.15  1998/04/18 13:40:46  luc
//       élimination de la méthode estValide
//
//       Revision 1.14  1998/02/19 17:25:09  luc
//       élimination du const rajouté à la version précédente
//
//       Revision 1.13  1998/01/22 10:43:32  luc
//       amélioration de l'en-tête de classe
//       ajout d'un qualificatif const dans une signature
//
//       Revision 1.12  1997/07/06 10:33:55  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.11  1997/04/17 06:16:47  luc
//       transfert de corrigeOrthog dans l'interface publique de la bibliothèque
//       
//       Revision 1.10  1997/03/26 06:39:50  luc
//       changement des conventions de nommage
//       
//       Revision 1.9  1997/03/24 09:22:19  luc
//       passage de SCCS à RCS
//       
//       Revision 1.8  1996/07/16 11:57:04  luc
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       suppression de l'opérateur == (il n'avait pas de raison d'être intrinsèque,
//       il n'était présent jusqu'ici qu'à cause des tools.h++)
//       
//       Revision 1.7  1995/06/26 16:24:31  mercator
//       elimination d'un const dans une signature template trop compliquee
//       
//       Revision 1.6  1995/01/19 06:32:02  mercator
//       elimination des references inutilisees a la librairie rwmth (DoubleGenMat)
//       
//       Revision 1.5  1994/12/22 16:19:40  mercator
//       utilisation de retours de references constantes pour optimiser la vitesse
//       
//       Revision 1.4  1994/12/12 15:14:47  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.3  1994/11/26 15:15:46  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/11/09 16:37:58  mercator
//       ajout d'un argument CantorErreurs* nul par defaut a certaines fonctions
//       elimination de l'inclusion du source en fin de fichier
//       
//       Revision 1.1  1994/07/27 14:57:15  luc
//       Initial revision
//
//$Version
//       $Id: Rotation.h,v 2.3 2002/12/10 15:11:03 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Rotation_h
#define __cantor_Rotation_h

#include "cantor/Vecteur3.h"
#include "cantor/CantorErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Rotation
//
//$Resume
//       modélisation de rotation en dimension 3
//
//$Description
//       modélisation de rotation en dimension 3
//       (implantée par les quaternions)
//
//$Usage
//>     construction : 
//          à partir de l'axe et de l'angle, d'une matrice, de deux
//          couples de vecteurs, d'un couple de vecteurs, de trois
//          angles successifs ou des composantes d'un quaternion.
//>     utilisation  : 
//>       Rotation<T>& operator = () 
//          affectation
//>       Vecteur3<T> axe         () 
//          retourne une copie de l'axe de rotation (orienté de sorte
//          que l'angle soit entre 0 et PI)
//>       T angle                 () 
//          retourne une copie de l'angle de rotation en radians entre
//          0 et PI
//>       void initAngles         () 
//          retourne une copie des angles de rotation successifs
//          correspondant à la succession de rotations élémentaires
//          spécifiée
//>       void initMatrice        () 
//          retourne dans le tableau passé en argument une copie de la
//          matrice
//>       Rotation<T> operator()  () 
//          retourne une copie de l'image de la rotation donnée en
//          argument.
//>       Vecteur3<T> operator()  () 
//          retourne une copie de l'image du vecteur donné en
//          argument.
//>       const T& q0             () 
//          retourne une copie de la première composante du quaternion
//>       const T& q1             () 
//          retourne une copie de la deuxième composante du quaternion
//>       const T& q2             () 
//          retourne une copie de la troisième composante du quaternion
//>       const T& q3             () 
//          retourne une copie de la quatrième composante du quaternion
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

template <class T> class Rotation
{

public :

  // spécification des conventions pour les angles de Cardan et d'Euler
  enum AxesRotation { XYZ, XZY, YXZ, YZX, ZXY, ZYX,
                      XYX, XZX, YXY, YZY, ZXZ, ZYZ };

  // constructeurs
  Rotation  () : q_ (T (0.0), T (0.0), T (0.0)), q0_ (T (1.0)) {}
  Rotation  (const Vecteur3<T>& axe, const T& angle, T norme = T (-1.0))
    throw (CantorErreurs);
  Rotation  (T matrice [3][3], T convergence = T (1.0e-6))
    throw (CantorErreurs);
  Rotation  (Vecteur3<T> u1, Vecteur3<T> u2, Vecteur3<T> v1, Vecteur3<T> v2)
    throw (CantorErreurs);
  Rotation  (Vecteur3<T> u,  Vecteur3<T> v)
    throw (CantorErreurs);
  Rotation  (AxesRotation ordre,
             const T& alpha1, const T& alpha2, const T& alpha3)
    throw (CantorErreurs);
  Rotation  (const T& q0, const T& q1, const T& q2, const T& q3)
    : q_ (q1, q2, q3), q0_ (q0)
  {}

  // copie constructeur et affectation
  Rotation  (const Rotation<T>& r) : q_ (r.q_), q0_ (r.q0_) {}
  Rotation<T>& operator = (const Rotation<T>& r);

  // fonctions d'accès aux éléments canoniques
  const T&           q0           () const { return q0_;     }
  const T&           q1           () const { return q_.x (); }
  const T&           q2           () const { return q_.y (); }
  const T&           q3           () const { return q_.z (); }

  Vecteur3<T>        axe          () const;
  T                  angle        () const;

  void               initAngles   (AxesRotation ordre,
                                   T *ptrAlpha1,
                                   T *ptrAlpha2,
                                   T *ptrAlpha3) const
    throw (CantorErreurs);

  void               initMatrice  (T m [3][3])      const;

  // application d'une rotation à des éléments divers
  Rotation<T>        operator () (const Rotation<T>& r) const;
  Vecteur3<T>        operator () (const Vecteur3<T>& u) const;

  // destructeur
  ~Rotation () {}

private :

  Vecteur3<T> q_;
  T           q0_;

};

// inversion de la rotation
template <class T> inline
Rotation<T> operator - (const Rotation<T>& r)
{ return Rotation<T> (-(r.q0 ()), r.q1 (), r.q2 (), r.q3 ()); }

// recherche d'une matrice orthogonale proche d'une matrice donnée
template <class T>
void corrigeOrthog (T m [3][3], T orth [3][3], T convergence)
  throw (CantorErreurs);

#endif
