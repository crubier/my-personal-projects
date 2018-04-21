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
//>       SenseurFonctionGauss.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurFonctionGauss
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurFonctionGauss 
//>         SenseurFonctionGauss()   
//>         fonction()       
//
//$Historique
//       $Log: SenseurFonctionGauss.cpp,v $
//       Revision 1.7  2003/02/27 16:41:58  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.6  2003/02/04 16:40:28  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.5  2001/07/17 15:38:01  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.4  2001/03/26 11:17:55  luc
//       mise à jour résultant de la modélisation des inhibitions
//       dans la classe SenseurOptique
//
//       Revision 1.3  2000/09/18 10:44:56  luc
//       correction d'une conversion inutile dans le constructeur, changement
//       de sémantique du maximum, désormais en dB
//
//       Revision 1.2  2000/09/13 10:58:45  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.1  2000/06/07 14:05:41  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonctionGauss.cpp,v 1.7 2003/02/27 16:41:58 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurFonctionGauss.h"

SenseurFonctionGauss::SenseurFonctionGauss (const string& nom,
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

SenseurFonctionGauss& SenseurFonctionGauss::operator = (const SenseurFonctionGauss& s)
{ if (&s != this)    // protection contre x = x
  {
    SenseurFonction::operator = (s);
    maximum_  = s.maximum_;
    angle3dB_ = s.angle3dB_;
  }

  return *this;

}

double SenseurFonctionGauss::fonction (double azimut,
                                       double depointage) const
  throw (MarmottesErreurs)
{
  // l'angle 1.17... est tel que exp(-(x^2/2)) = 1/2 (à 5.3e-18 près)
  double x = depointage * 1.1774100225154747 / angle3dB_;
  return maximum_ - 5.0 * x * x / log (10.0);
}
