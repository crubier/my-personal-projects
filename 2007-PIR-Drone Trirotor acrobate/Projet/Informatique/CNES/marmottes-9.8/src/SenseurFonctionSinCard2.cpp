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
//>       SenseurFonctionSinCard2.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurFonctionSinCard2
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurFonctionSinCard2 
//>         SenseurFonctionSinCard2()   
//>         fonction()       
//
//$Historique
//       $Log: SenseurFonctionSinCard2.cpp,v $
//       Revision 1.8  2003/02/27 16:47:49  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.7  2003/02/04 16:40:46  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.6  2001/07/17 15:37:25  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.5  2001/03/26 11:18:06  luc
//       mise à jour résultant de la modélisation des inhibitions
//       dans la classe SenseurOptique
//
//       Revision 1.4  2000/09/18 10:42:23  luc
//       correction d'une conversion inutile dans le constructeur, changement
//       de sémantique du maximum, désormais en dB
//
//       Revision 1.3  2000/09/13 10:59:16  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.2  2000/06/07 16:47:05  filaire
//       correction d'une erreur de syntaxe
//
//       Revision 1.1  2000/06/07 14:05:32  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonctionSinCard2.cpp,v 1.8 2003/02/27 16:47:49 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurFonctionSinCard2.h"

SenseurFonctionSinCard2::SenseurFonctionSinCard2 (const string& nom,
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
                                                  double angle3dB)
  throw (CantorErreurs)
  : SenseurFonction (nom, repere, axeCalage, precision,
                     code, ptrStation, observe, ptrChampDeVue,
                     ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                     ptrChampInhibitionCentral,
                     margeEclipseSoleil, margeEclipseLune, seuilPhaseLune,
                     axe, origine),
    maximum_ (maximum), angle3dB_ (radians (angle3dB))
{}

SenseurFonctionSinCard2& SenseurFonctionSinCard2::operator = (const SenseurFonctionSinCard2& s)
{ if (&s != this)    // protection contre x = x
  {
    SenseurFonction::operator = (s);
    maximum_  = s.maximum_;
    angle3dB_ = s.angle3dB_;
  }

  return *this;

}

double SenseurFonctionSinCard2::fonction (double azimut,
                                          double depointage) const
  throw (MarmottesErreurs)
{
  // l'angle 1.39... est tel que (sin(x)/x)^2 = 1/2 (à 8.1e-17 près)
  double alpha = depointage * 1.39155737825151 / angle3dB_;

  double sinCardinal;
  if (fabs (alpha) < 4.0e-4)
  { // si l'angle est trop petit, on utilise un développement limité
    // pour calculer sin (alpha) / alpha. En se limitant à l'ordre 2,
    // on obtient 2.1e-16 en erreur relative (pour des angles
    // inférieurs à 4e-4)
    sinCardinal = (6.0 - alpha * alpha) / 6.0;
  }
  else
    sinCardinal = sin (alpha) / alpha;
  return maximum_ + 20.0 * log (sinCardinal) / log (10.0);
}
