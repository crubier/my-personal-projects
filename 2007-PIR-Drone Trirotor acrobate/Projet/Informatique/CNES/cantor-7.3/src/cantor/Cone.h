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
//>       Cone.h
//
//$Resume
//       fichier d'en-tête de la classe Cone
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Cone                      
//>       typedef void TypeFoncConstCone()
//>       typedef void TypeFoncCone()     
//
//$Historique
//       $Log: Cone.h,v $
//       Revision 2.15  2002/12/10 14:53:55  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui crée par le compilateur
//
//       Revision 2.14  2002/12/02 13:32:49  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 2.13  2001/09/18 16:07:04  cantor
//       ajout d'un constructeur à partir de trois points,
//       ajout de l'opérateur « - » unaire pour la complémentation
//
//       Revision 2.12  2001/06/05 15:26:24  cantor
//       passage au mécanisme des exceptions pour la gestion des erreurs,
//       utilisation du type bool pour les prédicats
//
//       Revision 2.11  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 2.10.2.1  2000/03/30 15:36:08  cantor
//       ajout du copyright CNES
//
//       Revision 2.10  1999/08/05 09:55:57  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 2.9.2.1  1999/04/26 09:38:15  cantor
//       ajout de la gestion du sinus du demi-angle
//
//       Revision 2.9  1998/07/29 11:46:21  cantor
//       élimination de float.h
//
//       Revision 2.8  1998/06/24 10:25:12  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.7  1998/04/26 15:58:20  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.6  1998/04/18 18:10:14  luc
//       élimination de la méthode estValide
//
//       Revision 2.5  1998/01/22 10:39:09  luc
//       amélioration de l'en-tête de classe
//
//       Revision 2.4  1997/07/06 10:25:21  luc
//       ajout d'un en-tête de fichier
//
//       Revision 2.3  1997/03/26 06:39:38  luc
//       changement des conventions de nommage
//       
//       Revision 2.2  1997/03/24 09:22:10  luc
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/16 11:50:11  luc
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       suppression de l'opérateur == (il n'avait pas de raison d'être intrinsèque,
//       il n'était présent jusqu'ici qu'à cause des tools.h++)
//       
//       Revision 1.5  1994/12/22 16:19:40  mercator
//       utilisation de retours de references constantes pour optimiser la vitesse
//       
//       Revision 1.4  1994/12/13 10:24:38  mercator
//       transformation du type de retour de "intersection" de void a int
//       
//       Revision 1.3  1994/12/12 15:14:31  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.2  1994/11/26 15:13:54  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:56:54  luc
//       Initial revision
//
//$Version
//       $Id: Cone.h,v 2.15 2002/12/10 14:53:55 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Cone_h
#define __cantor_Cone_h

#include "cantor/Util.h"
#include "cantor/CantorErreurs.h"
#include "cantor/DeclDBL.h"

// types d'une fonction globale s'appliquant a un cône
class Cone;
typedef void TypeFoncConstCone (const Cone& c, void* donnee);
typedef void TypeFoncCone      (      Cone& c, void* donnee);

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Cone
//$Resume
//       modélisation d'un cône sur la sphère unité
//
//$Description
//       modélisation d'un cône sur la sphère unité
//
//$Usage
//>     construction : 
//          sans argument, à partir de l'axe et du demi-angle,
//          à partir de trois points
//>     utilisation  : 
//>       Cone& operator =  () 
//          affectation
//>       Cone operator -  () 
//          retourne le cône complémentaire sur la sphère unité
//>       void corrige      () 
//          agrandit (ou réduit) le demi-angle d'ouverture du cône
//>       void intersection () 
//          calcule les vecteurs début et fin de l'intersection de
//          deux cones.
//>       const VecDBL& axe () 
//          retourne une copie de l'axe
//>       double angle      () 
//          retourne le demi-angle d'ouverture
//>       double cosinus    () 
//          retourne le cosinus du demi-angle d'ouverture
//>       double sinus      () 
//          retourne le sinus du demi-angle d'ouverture
//>       bool inclus       () 
//          teste si le vecteur v est dans le cône
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Cone
{ 
  public :

  // constructeurs
  Cone  ();
  Cone  (const VecDBL& a, double mu) throw (CantorErreurs);
  Cone  (const VecDBL& p1, const VecDBL& p2, const VecDBL& p3)
    throw (CantorErreurs);

  // copie constructeur et affectation
  Cone  (const Cone& c)
    : a_ (c.a_), mu_ (c.mu_), cosMu_ (c.cosMu_), sinMu_ (c.sinMu_)
  {}
  Cone& operator = (const Cone& c);

  // destructeur
  ~Cone () {}

  // complémentaire
  Cone operator - () const;

  // accès aux éléments canoniques
  const VecDBL& axe     () const { return a_;     }
  double        angle   () const { return mu_;    }
  double        cosinus () const { return cosMu_; }
  double        sinus   () const { return sinMu_; }

  // modification de la taille d'un cône
  void          corrige (double ecart);

  // présence d'un vecteur dans un cône
  bool inclus (const VecDBL &u) const
  { return (u | a_) / u.norme () >= cosMu_; }

  // intersection par un cône
  void intersection (const Cone &v, VecDBL* p_deb, VecDBL* p_fin) const
    throw (CantorErreurs);

private :

  VecDBL           a_;
  double           mu_;
  double           cosMu_;
  double           sinMu_;

};

#endif
