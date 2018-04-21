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
//>       FamilleAlignementPlus.cpp
//$Resume
//       fichier d'implantation de la classe FamilleAlignementPlus
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class FamilleAlignementPlus
//>         FamilleAlignementPlus()  
//>         operator =()             
//>         copie()                  
//>         inertielCanonique()      
//$Historique
//       $Log: FamilleAlignementPlus.cpp,v $
//       Revision 1.5  2003/02/04 16:24:43  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.4  2001/06/22 07:11:59  luc
//       correction d'une utilisation ambigue d'une surcharge de acos
//
//       Revision 1.3  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 1.2  1999/09/14 07:57:52  filaire
//       test sur la valeur sous l'arccos
//
//       Revision 1.1  1999/07/29 12:07:01  filaire
//       Creation de la classe
//       Solutions qui traitent les singularites
//
//
//$Version
//       $Id: FamilleAlignementPlus.cpp,v 1.5 2003/02/04 16:24:43 marmottes Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/FamilleAlignementPlus.h"

FamilleAlignementPlus::FamilleAlignementPlus ()
  : FamilleAbstraite ()
{}

FamilleAlignementPlus::FamilleAlignementPlus (const Intervalle& plages,
                                              const VecVD1& u1, const VecVD1& u2,
                                              double signe,
                                              double sinMu1, double cosMu1,
                                              double sinMu2, double cosMu2)
  : FamilleAbstraite (plages), u1_ (u1), u2_ (u2), signe_ (signe),
    sinMu_1_ (sinMu1), cosMu_1_ (cosMu1), sinMu_2_ (sinMu2), cosMu_2_ (cosMu2)
{
  deuxSinCos_ = 2 * sinMu1 * cosMu1;
  deuxSinSin_ = 2 * sinMu1 * sinMu1;
  coeff_      = sinMu1 * cosMu2;
}

FamilleAlignementPlus::FamilleAlignementPlus (const FamilleAlignementPlus& f)
  : FamilleAbstraite (f), u1_ (f.u1_), u2_ (f.u2_), signe_ (f.signe_),
    sinMu_1_ (f.sinMu_1_), cosMu_1_ (f.cosMu_1_), sinMu_2_ (f.sinMu_2_), 
    cosMu_2_ (f.cosMu_2_), deuxSinCos_ (f.deuxSinCos_), deuxSinSin_ (f.deuxSinSin_),
    coeff_ (f.coeff_)
{}

FamilleAlignementPlus& FamilleAlignementPlus::operator = (const FamilleAlignementPlus& f)
{
  if (&f != this)     // protection contre x = x
  { 
    FamilleAbstraite::operator = (f);
    u1_         = f.u1_;
    u2_         = f.u2_;
    signe_      = f.signe_;
    sinMu_1_    = f.sinMu_1_;
    cosMu_1_    = f.cosMu_1_;
    sinMu_2_    = f.sinMu_2_;
    cosMu_2_    = f.cosMu_2_;
    deuxSinCos_ = f.deuxSinCos_;
    deuxSinSin_ = f.deuxSinSin_;
    coeff_      = f.coeff_;
  }
  return *this;
}

FamilleAbstraite * FamilleAlignementPlus::copie () const
{
  return new FamilleAlignementPlus (*this);
}

RotVD1 FamilleAlignementPlus::inertielCanonique (const ValeurDerivee1& t) const
{ 
  // constitution du modèle
  // détermination de l'angle de la rotation autour de v : theta (paramètre libre)
  ValeurDerivee1 theta = transforme (t);

  // valeurs intermédiaires
  ValeurDerivee1 sin1DemiTheta = sin(0.5*theta);
  ValeurDerivee1 sin1DemiThetaAuCarre = sin1DemiTheta * sin1DemiTheta;

  // équations du vecteur V1
  ValeurDerivee1 v1X = deuxSinCos_ * sin1DemiThetaAuCarre;
  ValeurDerivee1 v1Y = - sinMu_1_ * sin(theta);
  ValeurDerivee1 v1Z = 1 - deuxSinSin_ * sin1DemiThetaAuCarre;
  VecVD1 v1 = VecVD1 (v1X, v1Y, v1Z);
 
  // Résolution
  ValeurDerivee1 lamda = atan2 (-cos(0.5*theta), cosMu_1_ * sin1DemiTheta);
  ValeurDerivee1 sousACos = coeff_ * sin1DemiTheta/
    (sinMu_2_ * sqrt(1 - sinMu_1_ * sinMu_1_ * sin1DemiThetaAuCarre));
  ValeurDerivee1 phi;
  if (sousACos.f0 () > 1 - marmottesPrecision)
  {
    phi = lamda + ValeurDerivee1 (0.0, -10000000.0);
  }
  else if (sousACos.f0 () < -1 + marmottesPrecision)
  {
    phi = lamda + ValeurDerivee1 (signe_ * M_PI, -10000000.0);
  }
  else
  {
    phi = lamda + signe_ * acos (sousACos);
  }

  // équations du vecteur V2
  ValeurDerivee1 v2X = sinMu_2_ * cos(phi);
  ValeurDerivee1 v2Y = sinMu_2_ * sin(phi);
  ValeurDerivee1 v2Z = cosMu_2_;
  VecVD1 v2 = VecVD1 (v2X, v2Y, v2Z);

  // rotation qui passe de l'inertiel au canonique
  return RotVD1 (u1_, u2_, v1, v2);

}
