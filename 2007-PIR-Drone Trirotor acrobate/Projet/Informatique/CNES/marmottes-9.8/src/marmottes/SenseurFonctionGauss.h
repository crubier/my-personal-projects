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
//>       SenseurFonctionGauss.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurFonctionGauss
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurFonctionGauss
//
//$Historique
//       $Log: SenseurFonctionGauss.h,v $
//       Revision 1.8  2003/02/27 16:13:34  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.7  2002/12/11 17:18:17  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.6  2002/12/02 17:06:06  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.5  2001/07/17 15:33:13  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.4  2001/03/26 11:13:20  luc
//        mise à jour résultant de la modélisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.3  2000/11/16 07:36:33  luc
//       correction de fautes de frappe
//
//       Revision 1.2  2000/09/13 10:58:26  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.1  2000/06/07 14:06:11  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonctionGauss.h,v 1.8 2003/02/27 16:13:34 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurFonctionGauss_h
#define __marmottes_SenseurFonctionGauss_h

#include "marmottes/SenseurFonction.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurFonctionGauss
//
//$Resume
//       modélisation d'un pseudo-senseur plaquant la fonction gaussienne
//       sur la sphère unité
//
//$Description
//       modélisation d'un senseur plaquant la fonction gaussienne
//       sur la sphère unité. L'utilisation principale d'un tel senseur
//       est de représenter des gains d'antenne.
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage,
//          de la précision, du maximum et de l'angle pour un gain de -3dB
//          par copie
//>     utilisation  : 
//>       SenseurFonctionGauss& operator =        () 
//          affectation
//>       virtual double fonction          () 
//          évalue la fonction gaussienne
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurFonctionGauss : public SenseurFonction
{

  public :

  // constructeurs
  SenseurFonctionGauss (const string& nom, const RotDBL& repere,
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
                        double maximum, double angle3dB)
    throw (CantorErreurs);

  SenseurFonctionGauss (const SenseurFonctionGauss& s)
    : SenseurFonction (s),
      maximum_ (s.maximum_), angle3dB_ (s.angle3dB_)
  {}

  SenseurFonctionGauss& operator = (const SenseurFonctionGauss& s);

  virtual Senseur* copie () const { return new SenseurFonctionGauss (*this); }

  // destructeur
  virtual ~SenseurFonctionGauss () {}

  // fonction sinus cardinal plaquée sur la sphère
  virtual double fonction (double azimut, double depointage) const
    throw (MarmottesErreurs);

  protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurFonctionGauss () {}

  private :

  double maximum_;
  double angle3dB_;

};

#endif
