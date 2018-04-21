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
//       Marmottes
//
//$Nom
//>       FamilleAbstraite.h
//$Resume
//       fichier d'en-tête de la classe FamilleAbstraite
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class FamilleAbstraite
//>          
//$Historique
//       $Log: FamilleAbstraite.h,v $
//       Revision 1.4  2000/03/30 17:01:21  luc
//       ajout du copyright CNES
//
//       Revision 1.3  1999/11/02 07:19:20  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.2  1999/09/14 07:55:44  filaire
//       ajout de la variable globale marmottesPrecision
//
//       Revision 1.1  1999/07/29 12:10:51  filaire
//       Creation de la classe
//       Classe de base pour les familles de solutions mathematiques
//
//
//$Version
//       $Id: FamilleAbstraite.h,v 1.4 2000/03/30 17:01:21 luc Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_FamilleAbstraite_h
#define __marmottes_FamilleAbstraite_h

#include "cantor/DeclVD1.h"
#include "cantor/Intervalle.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FamilleAbstraite
//$Resume
//       modèle géométrique d'attitude
//
//$Description
//       Cette classe présente l'interface abstraite aux familles de solutions.
//
//$Usage
//>     construction : 
//          sans argument, par plage de validité, par copie
//>     utilisation  : 
//>       FamilleAbstraite& operator =     () 
//          affectation
//>       virtual FamilleAbstraite * copie () 
//          retourne une copie de la famille allouée en mémoire
//>       virtual RotVD1 inertielCanonique (t) 
//          retourne la rotation qui passe du repère inertiel au repère canonique
//          pour une famille et une valeur du degré de liberté données
//>       const Intervalle plages          () 
//          retourne la plage de validité
//$<>
///////////////////////////////////////////////////////////////////////////////

// on se donne une marge sur la précision de la machine
const double marmottesPrecision = 1e-10;

class FamilleAbstraite
{ 
  public :

  // constructeurs
  FamilleAbstraite ();
  FamilleAbstraite (const Intervalle& plages);
  FamilleAbstraite (const FamilleAbstraite& f);

  // opérateur d'affectation
  FamilleAbstraite& operator = (const FamilleAbstraite& f);

  // opérateur de copie (permet de faire une copie "propre" d'un 
  // élément de type FamilleAbstraite)
  virtual FamilleAbstraite * copie() const = 0;

  // destructeur
  virtual ~FamilleAbstraite () {}

  // fonction d'accès à l'élément interne
  const Intervalle  plages () const { return plages_; }

  // méthode qui retourne la rotation de passage du repère inertiel au repère canonique
  virtual RotVD1 inertielCanonique (const ValeurDerivee1& t) const = 0;

  protected :

  Intervalle  plages_;

  // méthode qui transforme t en theta
  ValeurDerivee1 transforme (const ValeurDerivee1& t) const;

};

#endif
