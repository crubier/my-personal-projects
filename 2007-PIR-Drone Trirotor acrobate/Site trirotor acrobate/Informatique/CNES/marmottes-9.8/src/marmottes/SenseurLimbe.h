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
//>       SenseurLimbe.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurLimbe
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurLimbe
//
//$Historique
//       $Log: SenseurLimbe.h,v $
//       Revision 1.6  2003/02/27 16:12:51  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.5  2002/12/11 17:18:58  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.4  2002/01/17 09:39:05  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.3  2001/07/17 15:22:17  luc
//       élimination des arguments code et station inutilisés
//       élimination de la méthode filtreSecteurs
//       (implantée entièrement dans la classe de base)
//
//       Revision 1.2  2001/04/04 12:07:57  luc
//       renommage de SenseurHorizon en SenseurLimbe
//       élimination de la spécialisation de la méthode controlable
//       ajout d'une spécialisation de la méthode ecartFrontiere
//
//       Revision 1.1  2001/03/26 11:10:48  luc
//       version initiale
//
//$Version
//       $Id: SenseurLimbe.h,v 1.6 2003/02/27 16:12:51 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurLimbe_h
#define __marmottes_SenseurLimbe_h

#include "marmottes/SenseurDiedre.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurLimbe
//
//$Resume
//       modélisation d'un cas particulier des senseurs dièdres, les senseurs limbe.
//
//$Description
//       modélisation d'un cas particulier des senseurs dièdres,
//       les senseurs limbe.
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       SenseurLimbe& operator =              () 
//          affectation
//>       virtual int controlable               () 
//          indique si le senseur serait capable de contrôler
//          l'attitude de l'état donné
//>       virtual Senseur* copie                () 
//          retourne une copie du senseur allouée en mémoire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurLimbe : public SenseurDiedre
{

  public :

  // constructeurs
  SenseurLimbe (const string& nom,
                const RotDBL& repere, const VecDBL& axeCalage,
                double precision,
                Parcelle *ptrChampDeVue,
                Parcelle *ptrChampInhibitionSoleil,
                Parcelle *ptrChampInhibitionLune,
                Parcelle *ptrChampInhibitionCentral,
                double margeEclipseSoleil, double margeEclipseLune,
                double seuilPhaseLune,
                const VecDBL& referenceZero, const VecDBL& axeSensible);

  SenseurLimbe (const SenseurLimbe& s);

  SenseurLimbe& operator = (const SenseurLimbe& s);

  // destructeur
  virtual ~SenseurLimbe () {}

  virtual Senseur* copie () const { return new SenseurLimbe (*this); }

  protected :

  virtual void ecartFrontiere (const Etat& etat,
                               double *ptrEcartFrontiere,
                               bool *ptrAmplitudeSignificative) const
    throw (CantorErreurs);

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurLimbe () {}

};

#endif
