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
//>       Intervalle.h
//
//$Resume
//       fichier d'en-tête de la classe Intervalle
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Intervalle              
//>       inline Intervalle operator +()
//>       inline Intervalle operator *()
//>       inline ostream& operator <<() 
//$Historique
//       $Log: Intervalle.h,v $
//       Revision 1.16  2002/12/10 15:06:09  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui crée par le compilateur
//
//       Revision 1.15  2002/12/02 13:38:50  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.14  2001/06/05 15:31:43  cantor
//       utilisation du type bool pour les prédicats
//
//       Revision 1.13  2000/10/24 16:22:18  cantor
//       modification des includes : suppression de .h dans le nom du fichier
//
//       Revision 1.12  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.11.2.1  2000/03/30 15:36:10  cantor
//       ajout du copyright CNES
//
//       Revision 1.11  1999/08/05 09:55:57  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.10.2.1  1999/04/26 13:44:22  cantor
//       ajout de la méthode decale
//
//       Revision 1.10  1998/06/24 11:49:47  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.9  1998/04/26 15:23:56  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.8  1998/01/22 10:39:59  luc
//       amélioration de l'en-tête de classe
//
//       Revision 1.7  1997/07/06 10:29:52  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.6  1997/03/26 06:39:44  luc
//       changement des conventions de nommage
//       
//       Revision 1.5  1997/03/24 09:22:15  luc
//       passage de SCCS à RCS
//       
//       Revision 1.4  1996/07/16 11:55:57  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       suppression de l'opérateur == (il n'avait pas de raison d'être intrinsèque,
//       il n'était présent jusqu'ici qu'à cause des tools.h++)
//       
//       Revision 1.3  1994/11/26 15:15:08  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/11/09 16:07:47  mercator
//       ajout d'un constructeur par defaut
//       
//       Revision 1.1  1994/07/27 14:57:08  luc
//       Initial revision
//
//$Version
//       $Id: Intervalle.h,v 1.16 2002/12/10 15:06:09 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Intervalle_h
#define __cantor_Intervalle_h

#include <iostream>

#include "cantor/Util.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Intervalle
//$Resume
//       modélisation d'un intervalle sur R
//
//$Description
//       modélisation d'un intervalle sur R
//
//$Usage
//>     construction : 
//          sans argument, ou à partir des bornes, ou par copie
//>     utilisation  : 
//>       Intervalle& operator =  () 
//          affectation
//>       double inf              () 
//          retourne une copie de la borne inf de l'intervalle
//>       double sup              () 
//          retourne une copie de la borne sup de l'intervalle
//>       double longueur         () 
//          retourne une copie de la borne longueur de l'intervalle
//>       bool contient           () 2 signatures - 
//          teste si l'intervalle contient un réel ou un intervalle
//>       bool rencontre          () 
//          teste si l'intervalle rencontre un autre intervalle
//>       bool disjoint           () 
//          teste si l'intervalle ne rencontre pas un autre intervalle
//>       void decale             () 
//          décale globalement l'intervalle
//>       bool operator <         () 
//          teste si l'instance est entièrement inférieure à
//          l'intervalle I
//>       bool operator >         () 
//          teste si l'instance est entièrement supérieure à
//          l'intervalle I
//>       Intervalle& operator += () 
//          retourne une référence à l'instance après l'avoir modifiée
//          par réunion avec un autre intervalle
//>       Intervalle& operator *= () 
//          retourne une référence à l'instance après l'avoir modifiée
//          par intersection avec un autre intervalle
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Intervalle
{ 
  public :

  // constructeurs
  Intervalle () :inf_ (0.0), sup_ (1.0) {}
  Intervalle (double a, double b)
  { if (a <= b)
    { inf_ = a; sup_ = b; }
    else
    { inf_ = b; sup_ = a; }
  }

  Intervalle (const Intervalle& i) : inf_ (i.inf_), sup_ (i.sup_) {}

  Intervalle& operator = (const Intervalle& i);

  // destructeur
  ~Intervalle () {}

  // fonctions d'acces aux elements canoniques
  double inf      () const { return inf_;        }
  double sup      () const { return sup_;        }
  double longueur () const { return sup_ - inf_; }

  // fonctions de tests d'inclusion
  bool contient  (double x) const
  { return (inf_ <= x) && (x <= sup_); }

  bool contient  (const Intervalle& i) const
  { return (inf_ <= i.inf_) && (i.sup_ <= sup_); }

  bool rencontre (const Intervalle& i) const
  { return (inf_ <= i.sup_) && (i.inf_ <= sup_); }

  bool disjoint  (const Intervalle& i) const
  { return (inf_ > i.sup_) || (i.inf_ > sup_); }

  // fonctions de modification
  void decale (double delta) { inf_ += delta; sup_ += delta; }

  // opérateurs relationnels
  bool operator <  (const Intervalle& i) const
  { return sup_ < i.inf_; }

  bool operator >  (const Intervalle& i) const
  { return inf_ > i.sup_; }

  // opérateurs entre intervalles ('+': reunion, '*': intersection)

  // ATTENTION: si intervalles disjoints, on comble le trou !
  Intervalle& operator += (const Intervalle& i)
  { inf_ = min (inf_, i.inf_); sup_ = max (sup_, i.sup_); return *this; }

  Intervalle& operator *= (const Intervalle& i)
  { inf_ = max (inf_, i.inf_);
    sup_ = max (min (sup_, i.sup_), inf_);
    return *this;
  }

private :

  double inf_;
  double sup_;

};

// ATTENTION: si intervalles disjoints, on comble le trou !
inline Intervalle  operator +  (const Intervalle& i, const Intervalle& j)
{ return Intervalle (min (i.inf (), j.inf ()), max (i.sup (), j.sup ())); }

inline Intervalle operator * (const Intervalle& i, const Intervalle& j)
{ double max_inf = max (i.inf (), j.inf ());
  return Intervalle (max_inf, max (min (i.sup (), j.sup ()), max_inf));
}

inline ostream& operator << (ostream& s, const Intervalle& i)
{ return s << '[' << i.inf () << "; " << i.sup () << ']'; }

#endif
