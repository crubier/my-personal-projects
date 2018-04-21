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
//>       FamilleProlongementPi.h
//
//$Resume
//       fichier d'en-tête de la classe FamilleProlongementPi
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class FamilleProlongementPi
//
//$Historique
//       $Log: FamilleProlongementPi.h,v $
//       Revision 1.3  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 1.2  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.1  1999/07/29 12:12:07  filaire
//       Creation de la classe
//       Solutions qui traitent les singularites
//
//
//$Version
//       $Id: FamilleProlongementPi.h,v 1.3 2000/03/30 17:01:22 luc Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_FamilleProlongementPi_h
#define __marmottes_FamilleProlongementPi_h

#include "cantor/DeclDBLVD1.h"
#include "marmottes/FamilleAbstraite.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FamilleProlongementPi
//$Resume
//       modèle géométrique d'attitude (cas d'alignement particuler)
//
//$Description
//       Cette classe implante un modèle d'attitude à un degré de
//       liberté tel que theta rencontre Pi et que Mu1=Gamma=Pi/2
//
//$Usage
//>     construction : 
//          sans argument, à partir des caractéristiques complètes du modèle,
//          par copie
//>     utilisation  : 
//>       FamilleProlongementPi& operator = ()
//          affectation 
//>       virtual FamilleAbstraite * copie  ()
//          retourne une copie de la famille allouée en mémoire
//>       RotVD1 inertielCanonique          () 
//          retourne la rotation qui passe du repère inertiel au repère Canonique
//          pour une famille et une valeur du degré de liberté données
//$<>
///////////////////////////////////////////////////////////////////////////////

class FamilleProlongementPi : public FamilleAbstraite
{ 
  public :

  // constructeurs
  FamilleProlongementPi ();
  FamilleProlongementPi (const Intervalle& plages,
                         const VecVD1& u1, const VecVD1& u2,
                         double signe,
                         double sinMu2, double cosMu2);
  FamilleProlongementPi (const FamilleProlongementPi& f);

  // opérateur d'affectation
  FamilleProlongementPi& operator = (const FamilleProlongementPi& f);

  // opérateur de copie 
  virtual FamilleAbstraite * copie() const ;

  // destructeur
  virtual ~FamilleProlongementPi() {}

  // méthode qui retourne la rotation de passage du repère inertiel au repère canonique
  virtual RotVD1 inertielCanonique (const ValeurDerivee1& t) const;

  private :

  VecVD1 u1_;
  VecVD1 u2_;
  double signe_;
  double sinMu_2_;
  double cosMu_2_;

};

#endif
