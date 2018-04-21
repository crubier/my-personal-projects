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
//>       FamilleAlignementMoins.h
//
//$Resume
//       fichier d'en-tête de la classe FamilleAlignementMoins
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class FamilleAlignementMoins
//
//$Historique
//       $Log: FamilleAlignementMoins.h,v $
//       Revision 1.3  2000/03/30 17:01:21  luc
//       ajout du copyright CNES
//
//       Revision 1.2  1999/11/02 07:19:20  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.1  1999/07/29 12:11:37  filaire
//       Creation de la classe
//       Solutions qui traitent les singularites
//
//
//$Version
//       $Id: FamilleAlignementMoins.h,v 1.3 2000/03/30 17:01:21 luc Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_FamilleAlignementMoins_h
#define __marmottes_FamilleAlignementMoins_h

#include "cantor/DeclDBLVD1.h"
#include "marmottes/FamilleAbstraite.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FamilleAlignementMoins
//$Resume
//       modèle géométrique d'attitude à un vecteur figé
//
//$Description
//       Cette classe implante un modèle d'attitude à un degré de
//       liberté tel que le secteur rencontre la valeur theta = Pi
//
//$Usage
//>     construction : 
//          sans argument, à partir des caractéristiques complètes du modèle,
//          par copie
//>     utilisation  : 
//>       FamilleAlignementMoins& operator = ()
//          affectation 
//>       virtual FamilleAbstraite * copie   ()
//          retourne une copie de la famille allouée en mémoire
//>       RotVD1 inertielCanonique           () 
//          retourne la rotation qui passe du repère inertiel au repère Canonique
//          pour une famille et une valeur du degré de liberté données
//$<>
///////////////////////////////////////////////////////////////////////////////

class FamilleAlignementMoins : public FamilleAbstraite
{ 
  public :

  // constructeurs
  FamilleAlignementMoins ();
  FamilleAlignementMoins (const Intervalle& plages,
                          const VecVD1& u1, const VecVD1& u2,
                          double signe,
                          double sinMu1, double cosMu1,
                          double sinMu2, double cosMu2);
  FamilleAlignementMoins (const FamilleAlignementMoins& f);

  // opérateur d'affectation
  FamilleAlignementMoins& operator = (const FamilleAlignementMoins& f);

  // opérateur de copie 
  virtual FamilleAbstraite * copie() const ;

  // destructeur
  virtual ~FamilleAlignementMoins() {}

  // méthode qui retourne la rotation de passage du repère inertiel au repère canonique
  virtual RotVD1 inertielCanonique (const ValeurDerivee1& t) const;

  private :

  VecVD1 u1_;
  VecVD1 u2_;
  double signe_;
  double sinMu_1_;
  double cosMu_1_;
  double sinMu_2_;
  double cosMu_2_;
  double deuxSinCos_;
  double deuxSinSin_;  
  double coeff_;

};

#endif
