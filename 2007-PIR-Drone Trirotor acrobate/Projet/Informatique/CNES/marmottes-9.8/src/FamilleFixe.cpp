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
//>       FamilleFixe.cpp
//$Resume
//       fichier d'implantation de la classe FamilleFixe
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class FamilleFixe    
//>         FamilleFixe()      
//>         operator =()       
//>         copie()            
//>         inertielCanonique()
//$Historique
//       $Log: FamilleFixe.cpp,v $
//       Revision 1.5  2003/02/04 16:25:14  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.4  2002/01/17 09:19:15  marmottes
//       remplacement de l'attribut v1_ par axe_, passage explicite de v1 et de axe dans le constructeur (FA 0007)
//
//       Revision 1.3  2001/06/06 08:19:38  luc
//       prise en compte du déplacement de Secteurs vers cantor
//
//       Revision 1.2  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 1.1  1999/07/29 12:08:35  filaire
//       Creation de la classe
//       Remplace en partie la classe ModeleGeomV1Fixe
//
//
//$Version
//       $Id: FamilleFixe.cpp,v 1.5 2003/02/04 16:25:14 marmottes Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Secteurs.h"

#include "marmottes/FamilleFixe.h"

FamilleFixe::FamilleFixe ()
  : FamilleAbstraite () 
{}

FamilleFixe::FamilleFixe (const Intervalle& plages,
                          const VecVD1& u1, const VecVD1& u2,
                          const VecVD1& v1, const VecVD1& ref,
                          const VecVD1& axe)
  : FamilleAbstraite (plages), axe_ (axe)
{ 
  // variable intermédiaire
  const double sinUneSec = 4.8e-6;

  // une rotation constante permet d'amener le vecteur fixe à sa place
  // dans le repère canonique
  if (fabs (angle (u1, u2).f0 ()) <= sinUneSec)
  {
    // cas particuler ou u1 = +/- u2
    r_ = RotVD1 (u1, v1);
  }
  else
  {
    r_ = RotVD1 (u1, u2, v1, ref);
  }
}

FamilleFixe::FamilleFixe (const FamilleFixe& f)
  : FamilleAbstraite (f), axe_ (f.axe_), r_ (f.r_) 
{}

FamilleFixe& FamilleFixe::operator = (const FamilleFixe& f)
{ 
  if (&f != this)     // protection contre x = x
  { 
    FamilleAbstraite::operator = (f);
    axe_  = f.axe_;
    r_    = f.r_;
  }
  return *this;
}

FamilleAbstraite * FamilleFixe::copie () const
{
  return new FamilleFixe (*this);
}

RotVD1 FamilleFixe::inertielCanonique (const ValeurDerivee1& t) const
{ 
  // constitution du modèle
  // détermination de l'angle de la rotation autour de v : theta (parametre libre)
  ValeurDerivee1 theta = transforme (t);

  RotVD1 r2 (axe_, theta, ValeurDerivee1 (1.0));

  // composition des rotations
  return r2 (r_);

}
