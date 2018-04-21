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
//>       FamilleFixe.h
//
//$Resume
//       fichier d'en-tête de la classe FamilleFixe
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class FamilleFixe
//
//$Historique
//       $Log: FamilleFixe.h,v $
//       Revision 1.4  2002/01/17 09:34:40  marmottes
//       (class FamilleFixe): remplacement de l'attribut v1_ par axe_, passage explicite de v1 et de axe dans le constructeur (FA 0007)
//
//       Revision 1.3  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 1.2  1999/11/02 07:19:20  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.1  1999/07/29 12:12:35  filaire
//       Creation de la classe
//       Remplace en partie la classe ModeleGeomV1Fixe
//
//
//$Version
//       $Id: FamilleFixe.h,v 1.4 2002/01/17 09:34:40 marmottes Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_FamilleFixe_h
#define __marmottes_FamilleFixe_h

#include "cantor/DeclVD1.h"
#include "marmottes/FamilleAbstraite.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FamilleFixe
//$Resume
//       modèle géométrique d'attitude à un vecteur figé
//
//$Description
//       Cette classe implante un modèle d'attitude à un degré de
//       liberté tel qu'un vecteur particulier de l'espace ait une
//       direction constante quelle que soit la valeur du degré de
//       liberté.
//
//$Usage
//>     construction : 
//          sans argument, à partir des caractéristiques complètes du modèle,
//          par copie
//>     utilisation  : 
//>       FamilleFixe& operator =            ()
//          affectation 
//>       virtual FamilleAbstraite * copie   ()
//          retourne une copie de la famille allouée en mémoire
//>       RotVD1 inertielCanonique           () 
//          retourne la rotation de passage du repère inertiel au 
//          repère canonique modélisés pour une valeur
//          du degré de liberté donnée
//>       const VecVD1& vecteur              () 
//          retourne le premier vecteur (repere inertiel)
//>       const RotVD1& rotation             () 
//          retourne la rotation constante qui permet d'amener 
//          le vecteur fixe à sa place dans le repère canonique
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class FamilleFixe : public FamilleAbstraite
{
  public :

  // constructeurs
  FamilleFixe ();
  FamilleFixe (const Intervalle& plages,
               const VecVD1& u1, const VecVD1& u2,
               const VecVD1& v1, const VecVD1& ref,
               const VecVD1& axe);
  FamilleFixe (const FamilleFixe& f);

  // opérateur d'affectation
  FamilleFixe& operator = (const FamilleFixe& f);

  // opérateur de copie 
  virtual FamilleAbstraite * copie() const ;

  // destructeur
  virtual ~FamilleFixe () {}

  // retourne la rotation de passage du repère inertiel au repère canonique
  virtual RotVD1 inertielCanonique (const ValeurDerivee1& t) const ;

  private:

  VecVD1 axe_; // axe de rotation dans le repère canonique
               // (le vecteur fixe vaut +/- cet axe)

  RotVD1 r_;   // rotation constante amenant le vecteur fixe
               // à sa place dans le repère canonique

};

#endif
