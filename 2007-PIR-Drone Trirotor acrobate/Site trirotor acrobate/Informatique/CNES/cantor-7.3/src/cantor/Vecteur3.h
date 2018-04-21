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
//>       Vecteur3.h
//
//$Resume
//       fichier d'en-tête de la classe Vecteur3
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Vecteur3                                      
//>       template <class T> inline ostream& operator <<()    
//>       template <class T> inline Vecteur3<T> operator *()  
//>       template <class T> inline T angle()                 
//>       inline Vecteur3<T> vecteurOrthogonalNorme()         
//>       template <class T> inline Vecteur3<T> vecteurNorme()
//
//$Historique
//       $Log: Vecteur3.h,v $
//       Revision 1.22  2002/12/10 15:39:44  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui créé par le compilateur
//
//       Revision 1.21  2002/12/02 13:50:00  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.20  2001/06/05 15:18:10  cantor
//       passage au mécanisme des exceptions pour la gestion des erreurs
//
//       Revision 1.19  2000/10/24 16:22:19  cantor
//       modification des includes : suppression de .h dans le nom du fichier
//
//       Revision 1.18  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.17.2.1  2000/03/30 15:36:12  cantor
//       ajout du copyright CNES
//
//       Revision 1.17  1999/06/28 14:47:02  cantor
//       modification de l'opérateur externe * : l'argument Vecteur3<T> est
//       passé par référence constante plutôt que par valeur
//
//       Revision 1.16  1998/07/29 11:50:58  cantor
//       élimination de float.h
//
//       Revision 1.15  1998/06/24 16:35:41  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.14  1998/04/26 15:34:36  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.13  1998/01/22 10:46:18  luc
//       amélioration de l'en-tête de classe
//
//       Revision 1.12  1997/07/06 10:37:17  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.11  1997/03/26 06:39:54  luc
//       changement des conventions de nommage
//       
//       Revision 1.10  1997/03/24 09:22:24  luc
//       passage de SCCS à RCS
//       
//       Revision 1.9  1996/07/16 12:03:37  luc
//       suppression de l'opérateur == (il n'avait pas de raison d'être intrinsèque,
//       il n'était présent jusqu'ici qu'à cause des tools.h++)
//       
//       Revision 1.8  1996/05/29 17:38:13  luc
//       utilisation d'un fichier d'inclusion garantissant la définition de M_PI
//       même si la compilation a été faite avec l'option -ansi.
//       
//       Revision 1.7  1994/12/22 16:19:41  mercator
//       utilisation de retours de references constantes pour optimiser la vitesse
//       
//       Revision 1.6  1994/12/12 15:14:50  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.5  1994/11/26 15:16:18  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.4  1994/11/14 07:03:44  mercator
//       correction d'une erreur dans la fonction en ligne vecteurNorme
//       
//       Revision 1.3  1994/11/09 16:08:33  mercator
//       ajout de l'operateur de sortie
//       elimination de l'inclusion du source en fin de fichier
//       
//       Revision 1.2  1994/08/11 15:10:41  mercator
//       transformation de fonctions globales en fonctions membres
//       ou en fonctions sans template, pour pallier a un probleme temporaire
//       de compilateur (g++ 2.6.0)
//       
//       Revision 1.1  1994/07/27 14:57:20  luc
//       Initial revision
//
//$Version
//       $Id: Vecteur3.h,v 1.22 2002/12/10 15:39:44 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Vecteur3_h
#define __cantor_Vecteur3_h

#include <iostream>
#include "cantor/MathPi.h"
#include "cantor/CantorErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Vecteur3
//
//$Resume
//       calculs vectoriels en dimension 3
//
//$Description
//       calculs vectoriels en dimension 3
//
//$Usage
//>     construction : 
//          à partir des coordonnées polaires (alpha,delta), radians
//          à partir des coordonnées cartésiennes (x, y, z)
//>     utilisation  : 
//>       Vecteur3<T>& operator =  () 
//          affectation
//>       int estNorme             () 
//          indique si le vecteur est normé
//>       int estNul               () 
//          indique si le vecteur est nul
//>       void normalise           () 
//          normalise le vecteur
//>       void orthonormalise      () 
//          transforme l'instance en un vecteur normé orthogonal à ce
//          qu'il était
//>       T angleAvecVecteur       () 
//          retourne l'angle entre l'instance et un autre vecteur
//>       Vecteur3<T> orthogonal   () 
//          retourne un vecteur normé orthogonal à l'instance
//>       Vecteur3<T>& operator ^= () 
//          remplace l'instance par son produit vectoriel avec un
//          vecteur
//>       const T& x               () 
//          retourne l'abscisse
//>       const T& y               () 
//          retourne l'ordonnée
//>       const T& z               () 
//          retourne la cote
//>       T norme                  () 
//          retourne la norme
//>       T alpha                  () 
//          retourne l'azimut
//>       T delta                  () 
//          retourne l'élévation
//>       Vecteur3<T>& operator -= () 
//          retourne une référence sur l'instance après lui avoir
//          soustrait un autre vecteur
//>       Vecteur3<T>& operator += () 
//          retourne une référence sur l'instance après lui avoir
//          ajouté un autre vecteur
//>       Vecteur3<T> operator -   () 
//          soustrait un vecteur à l'instance
//>       Vecteur3<T> operator +   () 
//          ajoute un vecteur à l'instance
//>       Vecteur3<T> operator ^   () 
//          calcule le produit vectoriel de l'instance et d'un autre
//          vecteur
//>       T operator |             () 
//          calcule le produit scalaire de l'instance et d'un autre
//          vecteur
//>       Vecteur3<T>& operator *= () 
//          retourne une référence sur l'instance après l'avoir
//          multipliée par un scalaire
//>       Vecteur3<T>& operator /= () 
//          retourne une référence sur l'instance après l'avoir
//          divisée par un scalaire
//>       Vecteur3<T> operator *   () 
//          calcule le produit de l'instance par un scalaire
//>       Vecteur3<T> operator /   () 
//          calcule le quotient de l'instance par un scalaire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

template <class T> class Vecteur3
{

public :

  // constructeurs
  Vecteur3   ()                 : x_ (0), y_ (0), z_ (0) {}
  Vecteur3   (T alpha, T delta) { z_ = cos (delta);
                                  x_ = cos (alpha) * z_;
                                  y_ = sin (alpha) * z_;
                                  z_ = sin (delta);
                                 }
  Vecteur3   (T x, T y, T z)    : x_ (x), y_ (y), z_ (z) {}

  // copie-constructeur et affectation
  Vecteur3   (const Vecteur3<T>& u) : x_ (u.x_), y_ (u.y_), z_ (u.z_) {}

  Vecteur3<T>& operator = (const Vecteur3<T>& u);

  // fonctions d'accès aux coordonnées
  const T&     x              () const { return x_; }
  const T&     y              () const { return y_; }
  const T&     z              () const { return z_; }
  T            norme          () const { return sqrt (x_*x_ + y_*y_ + z_*z_); }
  T            alpha          () const { return atan2 (y_, x_); }
  T            delta          () const { return asin (z_ / norme ()); }

  // tests du vecteur courant
  int          estNorme       () const;
  int          estNul         () const;

  // transformations du vecteur courant
  void         normalise      () throw (CantorErreurs);
  void         orthonormalise () throw (CantorErreurs);

  T            angleAvecVecteur (const Vecteur3<T>& u) const;

  // creation d'un vecteur normé orthogonal au vecteur courant
  // (il existe une infinité d'autres solutions)
  Vecteur3<T>  orthogonal     () const throw (CantorErreurs);

  // opérations arithmétiques entre Vecteur3<T>
  Vecteur3<T>& operator -=    (const Vecteur3<T>& u)
  { x_ -= u.x_; y_ -= u.y_; z_ -= u.z_; return *this; }

  Vecteur3<T>& operator +=    (const Vecteur3<T>& u)
  { x_ += u.x_; y_ += u.y_; z_ += u.z_; return *this; }

  Vecteur3<T>  operator -     () const
  { return Vecteur3<T> (-x_, -y_, -z_); }

  Vecteur3<T>  operator -     (const Vecteur3<T>& v) const
  { Vecteur3<T> u = *this; return u -= v; }

  Vecteur3<T>  operator +     (const Vecteur3<T>& v) const
  { Vecteur3<T> u = *this; return u += v; }

  // produit vectoriel
  Vecteur3<T>& operator ^=    (const Vecteur3<T>& u);

  Vecteur3<T>  operator ^     (const Vecteur3<T>& v) const
  { Vecteur3<T> u = *this; return u ^= v; }

  // produit scalaire
  T            operator |     (const Vecteur3<T>& v) const
  { return x_ * v.x_ + y_ * v.y_ + z_ * v.z_; }

  // opérations arithmétiques avec le patron T
  Vecteur3<T>& operator *=    (const T& t)
  { x_ *= t; y_ *= t; z_ *= t; return *this; }

  Vecteur3<T>& operator /=    (const T& t)
  { x_ /= t; y_ /= t; z_ /= t; return *this; }

  Vecteur3<T>  operator *     (const T& t)           const
  { Vecteur3<T> u = *this; return u *= t; }

  Vecteur3<T>  operator /     (const T& t)           const
  { Vecteur3<T> u = *this; return u /= t; }

  // destructeur
  ~Vecteur3 () {}

private :

  T x_;
  T y_;
  T z_;

};

// opérateur de sortie
template <class T> inline ostream& operator << (ostream& s,
                                                const Vecteur3<T>& u)
{ return s << '{' << u.x () << ' ' << u.y () << ' ' << u.z () << '}'; }

// multiplication du patron T par un Vecteur3<T>
template <class T> inline Vecteur3<T> operator *  (const T& t, 
                                                   const Vecteur3<T>& u)
{ return (u * t); }


// les fonctions suivantes sont une alternative permettant d'écrire
// xxx (u, v)  au lieu de u.xxx (v)
// le choix d'une interface ou de l'autre est une question de goût ...
template <class T> inline T angle (const Vecteur3<T>& u,
                                   const Vecteur3<T>& v)
{ return u.angleAvecVecteur (v); }

template <class T>
inline Vecteur3<T> vecteurOrthogonalNorme (const Vecteur3<T>& u)
  throw (CantorErreurs)
{ return u.orthogonal (); }

// attention: passage par valeur, u est modifié dans la fonction
template <class T> inline Vecteur3<T> vecteurNorme (Vecteur3<T> u)
  throw (CantorErreurs)
{ u.normalise (); return u; }


#endif
