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
//>       Creneau.h
//
//$Resume
//       fichier d'en-tête de la classe Creneau
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Creneau              
//>       ostream& operator <<()     
//>       inline Creneau operator +()
//>       inline Creneau operator *()
//
//$Historique
//       $Log: Creneau.h,v $
//       Revision 1.20  2002/12/02 13:33:33  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.19  2002/09/03 15:20:22  cantor
//       surcharge de l'opérateur '-', correction de 'throw' (FA15)
//
//       Revision 1.18  2001/06/12 12:50:50  cantor
//       utilisation du type bool pour les valeurs de retour des prédicats
//
//       Revision 1.17  2001/06/05 15:31:16  cantor
//       passage au mécanisme des exceptions pour la gestion des erreurs,
//       utilisation du type bool pour les prédicats
//
//       Revision 1.16  2000/10/24 16:22:18  cantor
//       modification des includes : suppression de .h dans le nom du fichier
//
//       Revision 1.15  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.14.2.1  2000/03/30 15:36:08  cantor
//       ajout du copyright CNES
//
//       Revision 1.14  1999/08/05 09:55:57  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.13.2.1  1999/04/26 13:51:45  cantor
//       ajout de la méthode decale
//
//       Revision 1.13  1998/07/29 11:47:05  cantor
//       élimination de float.h
//
//       Revision 1.12  1998/06/24 10:36:16  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.11  1998/04/26 15:23:49  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.10  1998/04/06 20:08:16  luc
//       ajout de l'opérateur *= entre créneaux, en s'appuyant sur l'opérateur *
//
//       Revision 1.9  1998/01/22 10:39:27  luc
//       amélioration de l'en-tête de classe
//
//       Revision 1.8  1997/07/06 10:24:38  luc
//       ajout d'un en-tête de fichier
//       remplacement des size_t par des int
//
//       Revision 1.7  1997/03/26 06:39:39  luc
//       changement des conventions de nommage
//       
//       Revision 1.6  1997/03/24 09:22:10  luc
//       passage de SCCS à RCS
//       
//       Revision 1.5  1996/07/16 10:27:54  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       (les intervalles sont désormais conservés dans un tableau géré par l'instance)
//       
//       Revision 1.4  1994/12/12 15:14:34  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.3  1994/11/26 15:14:18  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/08/11 14:56:00  mercator
//       elimination d'un qualificatif const excedentaire
//       
//       Revision 1.1  1994/07/27 14:57:00  luc
//       Initial revision
//
//$Version
//       $Id: Creneau.h,v 1.20 2002/12/02 13:33:33 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Creneau_h
#define __cantor_Creneau_h

#include <iostream>

#include "cantor/CantorErreurs.h"
#include "cantor/Intervalle.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Creneau
//$Resume
//       modélisation de réunion d'intervalles disjoints
//
//$Description
//       modélisation de réunion d'intervalles disjoints
//
//$Usage
//>     construction : 
//          à partir d'un intervalle, des bornes d'un intervalle
//>     utilisation  : 
//>       Creneau& operator =           () 
//          affectation
//>       double inf                    () 
//          retourne une copie de la borne inf du premier intervalle
//>       double sup                    () 
//          retourne une copie de la borne sup du dernier intervalle
//>       const Intervalle& operator [] () 
//          retourne une copie de l'intervalle d'indice i (indices
//          variant de 0 a n-1)
//>       bool vide                     () 
//          teste si le créneau est vide
//>       bool contient                 () 2 signatures - 
//          teste si le créneau contient un réel ou un intervalle
//>       bool rencontre                () 
//          teste si le créneau rencontre un intervalle
//>       bool disjoint                 () 
//          teste si le créneau ne rencontre pas un intervalle
//>       void decale                   () 
//          décale tous les intervalles du créneau
//>       Creneau& operator +=          () 2 signatures - 
//          retourne une référence à l'instance apres l'avoir modifiée
//          par réunion avec un intervalle ou un créneau
//>       Creneau& operator -=          () 2 signatures - 
//          retourne une référence à l'instance apres l'avoir modifiée
//          par disjonction avec un intervalle ou un créneau
//>       Creneau& operator *=          () 2 signatures - 
//          retourne une référence à l'instance apres l'avoir modifiée
//          par intersection avec un intervalle ou un créneau
//>       friend Creneau operator *     () 
//          retourne le Creneau intersection de l'instance et d'un
//          autre Creneau
//>       void nettoie                  () 
//          vide le creneau de ses intervalles
//>       int nombre                    () 
//          retourne une copie du nombre d'intervalles
//>       bool connexe                  () 
//          teste si le créneau est connexe
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Creneau
{ 
  public :

  // constructeurs
  Creneau ()
    : tailleTable_ (0), nbIntervalles_ (0), table_ (0)
  {}
  Creneau (const Intervalle& i);
  Creneau (const Intervalle& i1, const Intervalle& i2);
  Creneau (double a, double b);

  // copie constructeur et affectation
  Creneau (const Creneau& c);
  Creneau& operator = (const Creneau& c);

  // destructeur
  ~Creneau () { if (tailleTable_) delete [] table_; }

  // fonctions de gestion
  void        nettoie     ()     { nbIntervalles_ = 0; }

  // fonctions d'accès aux éléments canoniques
  double      inf         () const throw (CantorErreurs);
  double      sup         () const throw (CantorErreurs);
  int         nombre      () const { return nbIntervalles_; }
  const Intervalle& operator [] (int i) const throw (CantorErreurs);

  // fonctions de tests
  bool        connexe     ()      const { return nbIntervalles_ == 1; }
  bool        vide        ()      const;

  bool        contient    (double x)            const;
  bool        contient    (const Intervalle& i) const;
  bool        rencontre   (const Intervalle& i) const;
  bool        disjoint    (const Intervalle& i) const;

  // fonctions de modification
  void        decale      (double delta);

  // opérations avec des intervalles ('+': réunion, '-': disjonction, '*': intersection)
  Creneau&    operator +=   (const Intervalle& i);
  Creneau&    operator -=   (const Intervalle& i);
  Creneau&    operator *=   (const Intervalle& i);

  // opérations entre créneaux ('+': réunion, '-': disjonction, '*': intersection)
  Creneau&    operator +=   (const Creneau& c);
  Creneau&    operator -=   (const Creneau& c);
  Creneau&    operator *=   (const Creneau& c)
                            { *this = *this * c ; return *this; }

  friend Creneau operator * (const Creneau& c, const Creneau& c2);

private :

  int         tailleTable_;
  int         nbIntervalles_;
  Intervalle *table_;

  void etendTable ();

};

// les opérations suivantes doivent être utilisées avec précautions
// elle peuvent être coûteuses en raison de la variable temporaire copiée
// (la copie étant faite au cours du passage de paramètres)
inline Creneau operator + (Creneau c, const Intervalle& i)
{ return c += i; }

inline Creneau operator - (Creneau c, const Intervalle& i)
{ return c -= i; }

inline Creneau operator * (Creneau c, const Intervalle& i)
{ return c *= i; }

inline Creneau operator + (Creneau c1, const Creneau& c2)
{ return c1 += c2; }

inline Creneau operator - (Creneau c1, const Creneau& c2)
{ return c1 -= c2; }

ostream& operator << (ostream& s, const Creneau& c);

#endif
