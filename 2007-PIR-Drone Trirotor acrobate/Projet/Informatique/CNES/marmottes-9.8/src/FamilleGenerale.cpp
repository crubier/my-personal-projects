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
//>       FamilleGenerale.cpp
//$Resume
//       fichier d'implantation de la classe FamilleGenerale
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class FamilleGenerale
//>         FamilleGenerale()  
//>         operator =()       
//>         copie()            
//>         inertielCanonique()
//$Historique
//       $Log: FamilleGenerale.cpp,v $
//       Revision 1.5  2003/02/04 16:25:49  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.4  2001/06/22 07:12:10  luc
//       correction d'une utilisation ambigue d'une surcharge de acos
//
//       Revision 1.3  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 1.2  1999/09/14 07:57:52  filaire
//       test sur la valeur sous l'arccos
//
//       Revision 1.1  1999/07/29 12:09:00  filaire
//       Creation de la classe
//       Traite le cas general
//
//
//$Version
//       $Id: FamilleGenerale.cpp,v 1.5 2003/02/04 16:25:49 marmottes Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/FamilleGenerale.h"

FamilleGenerale::FamilleGenerale ()
  : FamilleAbstraite () 
{}

FamilleGenerale::FamilleGenerale (const Intervalle& plages,
                                  const VecVD1& u1, const VecVD1& u2,
                                  double signe,
                                  double sinMu1, double cosMu1,
                                  double sinMu2, double cosMu2,
                                  double sinGamma, double cosGamma,
                                  double cosAlpha_1_2)
  : FamilleAbstraite (plages), u1_ (u1), u2_ (u2), signe_ (signe),
    sinMu_1_ (sinMu1), sinMu_2_ (sinMu2), cosMu_2_ (cosMu2)
{
  sinGammaCosMu1_       = sinGamma * cosMu1;
  cosGammaSinMu1_       = cosGamma * sinMu1;
  sinGammaSinMu1_       = sinGamma * sinMu1;
  cosGammaCosMu1_       = cosGamma * cosMu1;
  partieConstante_      = cosAlpha_1_2 - cosMu2 * cosGamma * cosMu1;
  cosMu2SinGammaSinMu1_ = cosMu2 * sinGamma * sinMu1;
}

FamilleGenerale::FamilleGenerale (const FamilleGenerale& f)
  : FamilleAbstraite (f), u1_ (f.u1_), u2_ (f.u2_), signe_ (f.signe_),
    sinMu_1_ (f.sinMu_1_), sinMu_2_ (f.sinMu_2_), 
    cosMu_2_ (f.cosMu_2_), sinGammaCosMu1_ (f.sinGammaCosMu1_),
    cosGammaSinMu1_ (f.cosGammaSinMu1_), sinGammaSinMu1_ (f.sinGammaSinMu1_),
    cosGammaCosMu1_ (f.cosGammaCosMu1_), partieConstante_ (f.partieConstante_),
    cosMu2SinGammaSinMu1_ (f.cosMu2SinGammaSinMu1_)
{}

FamilleGenerale& FamilleGenerale::operator = (const FamilleGenerale& f)
{ 
  if (&f != this)     // protection contre x = x
  { 
    FamilleAbstraite::operator = (f);
    u1_                   = f.u1_;
    u2_                   = f.u2_;
    signe_                = f.signe_;
    sinMu_1_              = f.sinMu_1_;
    sinMu_2_              = f.sinMu_2_;
    cosMu_2_              = f.cosMu_2_;
    sinGammaCosMu1_       = f.sinGammaCosMu1_;
    cosGammaSinMu1_       = f.cosGammaSinMu1_;
    sinGammaSinMu1_       = f.sinGammaSinMu1_;
    cosGammaCosMu1_       = f.cosGammaCosMu1_;
    partieConstante_      = f.partieConstante_;
    cosMu2SinGammaSinMu1_ = f.cosMu2SinGammaSinMu1_;
  }
  return *this;
}

FamilleAbstraite * FamilleGenerale::copie () const
{
  return new FamilleGenerale (*this);
}

RotVD1 FamilleGenerale::inertielCanonique (const ValeurDerivee1& t) const
{ 
  // constitution du modèle
  // détermination de l'angle de la rotation autour de v : theta (paramètre libre)
  ValeurDerivee1 theta = transforme (t);

  // équations du vecteur V1
  ValeurDerivee1 v1X = sinGammaCosMu1_ - cosGammaSinMu1_ * cos(theta);
  ValeurDerivee1 v1Y = - sinMu_1_*sin(theta);
  ValeurDerivee1 v1Z = cosGammaCosMu1_ + sinGammaSinMu1_ * cos(theta);
  VecVD1 v1 = VecVD1 (v1X, v1Y, v1Z);
 
  // Résolution
  ValeurDerivee1 lamda = atan2 (v1Y, v1X);
  ValeurDerivee1 sousACos = (partieConstante_ - cosMu2SinGammaSinMu1_ * cos(theta))/
    (sinMu_2_ * sqrt(1- v1Z * v1Z));
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
