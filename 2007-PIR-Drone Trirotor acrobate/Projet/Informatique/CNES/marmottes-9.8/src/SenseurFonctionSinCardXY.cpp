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
//>       SenseurFonctionSinCardXY.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurFonctionSinCardXY
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurFonctionSinCardXY 
//>         SenseurFonctionSinCardXY()   
//>         fonction()       
//
//$Historique
//       $Log: SenseurFonctionSinCardXY.cpp,v $
//       Revision 1.3  2003/02/27 16:46:58  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.2  2003/02/04 16:40:57  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.1  2001/07/17 15:51:20  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonctionSinCardXY.cpp,v 1.3 2003/02/27 16:46:58 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurFonctionSinCardXY.h"

SenseurFonctionSinCardXY::SenseurFonctionSinCardXY (const string& nom,
                                                    const RotDBL& repere,
                                                    const VecDBL& axeCalage,
                                                    double precision,
                                                    codeCible code,
                                                    const StationCible *ptrStation,
                                                    const VecDBL& observe,
                                                    Parcelle* ptrChampDeVue,
                                                    Parcelle *ptrChampInhibitionSoleil,
                                                    Parcelle *ptrChampInhibitionLune,
                                                    Parcelle *ptrChampInhibitionCentral,
                                                    double margeEclipseSoleil,
                                                    double margeEclipseLune,
                                                    double seuilPhaseLune,
                                                    const VecDBL& axe,
                                                    const VecDBL& origine,
                                                    double maximum,
                                                    double angle3dBX,
                                                    double angle3dBY)
  throw (CantorErreurs)
  : SenseurFonction (nom, repere, axeCalage, precision,
                     code, ptrStation, observe, ptrChampDeVue,
                     ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                     ptrChampInhibitionCentral,
                     margeEclipseSoleil, margeEclipseLune, seuilPhaseLune,
                     axe, origine),
  maximum_ (maximum),
  angle3dBX_ (radians (angle3dBX)), angle3dBY_ (radians (angle3dBY))
{}

SenseurFonctionSinCardXY& SenseurFonctionSinCardXY::operator = (const SenseurFonctionSinCardXY& s)
{ if (&s != this)    // protection contre x = x
  {
    SenseurFonction::operator = (s);
    maximum_   = s.maximum_;
    angle3dBX_ = s.angle3dBX_;
    angle3dBY_ = s.angle3dBY_;
  }

  return *this;

}

double SenseurFonctionSinCardXY::fonction (double azimut,
                                           double depointage) const
  throw (MarmottesErreurs)
{
  // calcul des dépointages bidimensionnels
  double sinTheta = sin (depointage);
  double cosTheta = cos (depointage);
  VecDBL cible (sinTheta * cos (azimut), sinTheta * sin (azimut), cosTheta);

  // l'angle 1.89... est tel que sin(x)/x = 1/2 (à 2.0e-17 près)
  double alphaX = atan2 (cible.x (), cible.z ()) * 1.8954942670339809 / angle3dBX_;
  double alphaY = atan2 (cible.y (), cible.z ()) * 1.8954942670339809 / angle3dBY_;

  // si l'angle est trop petit, on utilise un développement limité
  // pour calculer sin (alpha) / alpha. En se limitant à l'ordre 2,
  // on obtient 2.1e-16 en erreur relative (pour des angles
  // inférieurs à 4e-4)
  double sinCardinalX, sinCardinalY;

  if (fabs (alphaX) < 4.0e-4)
    sinCardinalX = (6.0 - alphaX * alphaX) / 6.0;
  else
    sinCardinalX = sin (alphaX) / alphaX;

  if (fabs (alphaY) < 4.0e-4)
    sinCardinalY = (6.0 - alphaY * alphaY) / 6.0;
  else
    sinCardinalY = sin (alphaY) / alphaY;

  return maximum_ + 10.0 * log (sinCardinalX * sinCardinalY) / log (10.0);

}
