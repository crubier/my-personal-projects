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
//>       Vecteur3.cpp
//
//$Resume
//       fichier d'implantation de la classe Vecteur3
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Vecteur3      
//>         operator =()      
//>         estNorme()        
//>         estNul()          
//>         normalise()       
//>         orthonormalise()  
//>         angleAvecVecteur()
//>         orthogonal()      
//>         operator ^=()     
//
//$Historique
//       $Log: Vecteur3.cpp,v $
//       Revision 1.15  2003/02/04 09:37:26  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions (CC <- CPP)
//
//       Revision 1.14  2001/06/05 15:18:34  cantor
//       passage au mécanisme des exceptions pour la gestion des erreurs
//
//       Revision 1.13  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.12.2.1  2000/03/30 17:10:27  cantor
//       ajout du copyright CNES
//
//       Revision 1.12  1999/08/05 09:56:52  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.11.2.1  1999/04/26 09:33:05  cantor
//       remplacement de abs par fabs
//
//       Revision 1.11  1998/10/05 13:33:40  cantor
//       utilisation de la constante cantorEpsilon de cantor/Util.h
//
//       Revision 1.10  1998/06/24 10:06:30  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.9  1998/04/26 15:24:17  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.8  1997/07/06 10:37:07  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.7  1997/03/26 06:39:54  luc
//       changement des conventions de nommage
//       
//       Revision 1.6  1997/03/24 09:22:23  luc
//       passage de SCCS à RCS
//       
//       Revision 1.5  1996/07/16 11:00:24  luc
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.4  1994/12/12 15:14:49  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.3  1994/11/26 15:11:47  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/11/09 16:03:50  mercator
//       remplacement de la fonction "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 14:57:23  luc
//       Initial revision
//
//$Version
//       $Id: Vecteur3.cpp,v 1.15 2003/02/04 09:37:26 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Vecteur3_cc
#define __cantor_Vecteur3_cc

#include "cantor/Util.h"
#include "cantor/CantorErreurs.h"


// affectation
template <class T> Vecteur3<T>& Vecteur3<T>::operator = (const Vecteur3<T>& u)
{ if (this != &u)            // protection contre x = x
  { x_ = u.x_;
    y_ = u.y_;
    z_ = u.z_;
  }

  return *this;

}

// test de la norme d'un vecteur
template <class T> int Vecteur3<T>::estNorme () const
{ return fabs (T (1.0) - norme ()) < cantorEpsilon; }

// test de la norme d'un vecteur
template <class T> int Vecteur3<T>::estNul () const
{ return fabs (norme ()) < cantorEpsilon; }

// normalisation d'un vecteur
template <class T> void Vecteur3<T>::normalise ()
  throw (CantorErreurs)
{ T seuil = norme ();
  if (seuil < cantorEpsilon)
    throw CantorErreurs (CantorErreurs::norme_nulle);

  T inverse = T (1.0) / seuil;

  x_ *= inverse;
  y_ *= inverse;
  z_ *= inverse;

}

// calcul d'un vecteur orthogonal à un autre
template <class T> void Vecteur3<T>::orthonormalise ()
  throw (CantorErreurs)
{ T seuil = norme () * T (0.6);
  if (seuil < T (cantorEpsilon))
    throw CantorErreurs (CantorErreurs::norme_nulle);

  if ((x_ >= -seuil) && (x_ <= seuil))
  { T inverse  = T (1.0) / sqrt (z_ * z_ + y_ * y_);
    T ancien_y = y_;

    x_ =  T (0.0);
    y_ =  inverse * z_;
    z_ = -inverse * ancien_y;

  }
  else if ((y_ >= -seuil) && (y_ <= seuil))
  { T inverse  = T (1.0) / sqrt (x_ * x_ + z_ * z_);
    T ancien_x = x_;

    x_ = -inverse * z_;
    y_ =  T (0.0);
    z_ =  inverse * ancien_x;

  }
  else
  { T inverse  = T (1.0) / sqrt (x_ * x_ + y_ * y_);
    T ancien_x = x_;

    x_ =  inverse * y_;
    y_ = -inverse * ancien_x;
    z_ =  T (0.0);

  }

}

// évaluation de l'angle (en radians) entre deux vecteurs
template <class T> T Vecteur3<T>::angleAvecVecteur (const Vecteur3<T>& u) const
{ const T produit_normes   = norme () * u.norme ();
  const T produit_scalaire = (*this) | u;

  const T seuil = produit_normes * 0.9999;
  if ((produit_scalaire < -seuil) || (produit_scalaire > seuil))
  { // vecteurs presqu'alignés: calcul par le sinus
    const Vecteur3<T> w = (*this) ^ u;
    if (produit_scalaire >= 0.0)
      return asin (w.norme () / produit_normes);
    else
      return T (M_PI) - asin (w.norme () / produit_normes);
  }
  else
  { // vecteurs suffisamment éloignés: calcul par le cosinus
    return acos (produit_scalaire / produit_normes);
  }
}

// calcul d'un vecteur orthogonal à un autre
template <class T> Vecteur3<T> Vecteur3<T>::orthogonal () const
  throw (CantorErreurs)
{
  Vecteur3<T> u (*this);
  u.orthonormalise ();
  return u;
}

// calcul de produit vectoriel avec stockage dans le vecteur courant
template <class T>
Vecteur3<T>& Vecteur3<T>::operator ^= (const Vecteur3<T>& u)
{ T a = y_ * u.z_ - z_ * u.y_;
  T b = z_ * u.x_ - x_ * u.z_;
   z_ = x_ * u.y_ - y_ * u.x_;
   x_ = a;
   y_ = b;
  return *this;
}

#endif
