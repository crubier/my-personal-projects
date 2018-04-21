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
//>       SenseurFonctionSinCardXY.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurFonctionSinCardXY
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurFonctionSinCardXY
//
//$Historique
//       $Log: SenseurFonctionSinCardXY.h,v $
//       Revision 1.4  2003/02/27 16:13:06  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.3  2002/12/11 17:18:58  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.2  2002/12/02 17:06:54  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.1  2001/07/17 15:34:19  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonctionSinCardXY.h,v 1.4 2003/02/27 16:13:06 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurFonctionSinCardXY_h
#define __marmottes_SenseurFonctionSinCardXY_h

#include "marmottes/SenseurFonction.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurFonctionSinCardXY
//
//$Resume
//       modélisation d'un pseudo-senseur plaquant la fonction sin(x)/x * sin(y)/y
//       sur la sphère unité
//
//$Description
//       modélisation d'un senseur plaquant la fonction sin(x)/x * sin(y)/y
//       sur la sphère unité. L'utilisation principale d'un tel senseur
//       est de représenter des gains d'antenne.
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage,
//          de la précision, du maximum et des angles pour un gain de -3dB
//          par copie
//>     utilisation  : 
//>       SenseurFonctionSinCardXY& operator =        () 
//          affectation
//>       virtual double fonction          () 
//          évalue la fonction sinus cardinal
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurFonctionSinCardXY : public SenseurFonction
{

public :

  // constructeurs
  SenseurFonctionSinCardXY (const string& nom, const RotDBL& repere,
                            const VecDBL& axeCalage, double precision,
                            codeCible code, const StationCible *ptrStation,
                            const VecDBL& observe,
                            Parcelle* ptrChampDeVue,
                            Parcelle *ptrChampInhibitionSoleil,
                            Parcelle *ptrChampInhibitionLune,
                            Parcelle *ptrChampInhibitionCentral,
                            double margeEclipseSoleil, double margeEclipseLune,
                            double seuilPhaseLune,
                            const VecDBL& axe, const VecDBL& origine,
                            double maximum, double angle3dBX, double angle3dBY)
    throw (CantorErreurs);

  SenseurFonctionSinCardXY (const SenseurFonctionSinCardXY& s)
    : SenseurFonction (s),
      maximum_ (s.maximum_),
      angle3dBX_ (s.angle3dBX_), angle3dBY_ (s.angle3dBY_)
  {}

  SenseurFonctionSinCardXY& operator = (const SenseurFonctionSinCardXY& s);

  virtual Senseur* copie () const { return new SenseurFonctionSinCardXY (*this); }

  // destructeur
  virtual ~SenseurFonctionSinCardXY () {}

  // fonction sinus cardinal plaquée sur la sphère
  virtual double fonction (double azimut, double depointage) const
    throw (MarmottesErreurs);

protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurFonctionSinCardXY () {}

private :

  double maximum_;
  double angle3dBX_;
  double angle3dBY_;

};

#endif
