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
//>       SenseurLimbe.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurLimbe
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurLimbe  
//>         SenseurLimbe()    
//>         operator =()      
//>         ecartFrontiere()      
//
//$Historique
//       $Log: SenseurLimbe.cpp,v $
//       Revision 1.6  2003/02/27 16:47:38  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.5  2003/02/04 16:41:35  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.4  2002/01/17 09:27:32  marmottes
//       correction de spécifications throw
//
//       Revision 1.3  2001/07/17 15:36:40  luc
//       forçage du code et de la station pour la classe de base
//       élimination de la méthode filtreSecteurs
//       (implantée entièrement dans la classe de base)
//
//       Revision 1.2  2001/04/04 12:24:02  luc
//       renommage de SenseurHorizon en SenseurLimbe,
//       élimination de la spécialisation de la méthode controlable,
//       ajout d'une spécialisation de la méthode ecartFrontiere
//
//       Revision 1.1  2001/03/26 11:15:47  luc
//       version initiale
//
//$Version
//       $Id: SenseurLimbe.cpp,v 1.6 2003/02/27 16:47:38 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurLimbe.h"
#include "marmottes/StationCible.h"

SenseurLimbe::SenseurLimbe (const string& nom, const RotDBL& repere,
                            const VecDBL& axeCalage, double precision,
                            Parcelle* ptrChampDeVue,
                            Parcelle* ptrChampInhibitionSoleil,
                            Parcelle* ptrChampInhibitionLune,
                            Parcelle* ptrChampInhibitionCentral,
                            double margeEclipseSoleil,
                            double margeEclipseLune,
                            double seuilPhaseLune,
                            const VecDBL& referenceZero,
                            const VecDBL& axeSensible)
  : SenseurDiedre (nom, repere, axeCalage, precision,
                   SenseurOptique::codeCorpsCentral,
                   0, VecDBL (0.0, 0.0, 0.0),
                   ptrChampDeVue,
                   ptrChampInhibitionSoleil,
                   ptrChampInhibitionLune,
                   ptrChampInhibitionCentral,
                   margeEclipseSoleil,
                   margeEclipseLune, seuilPhaseLune,
                   referenceZero, axeSensible)
{
  // pour les senseurs de limbe, on ne peut pas filtrer
  // les secteurs de consigne par le champ de vue, car
  // la cible correspond au centre du corps central, alors
  // que le champ de vue n'observe que le limbe
  secteursFiltrables_ = false;
}

SenseurLimbe::SenseurLimbe (const SenseurLimbe& s)
  : SenseurDiedre (s)
{}

SenseurLimbe& SenseurLimbe::operator = (const SenseurLimbe& s)
{
  if (&s != this)    // protection contre x = x
    SenseurDiedre::operator   = (s);
  return *this;
}

void SenseurLimbe::ecartFrontiere (const Etat& etat,
                                   double *ptrEcartFrontiere,
                                   bool   *ptrAmplitudeSignificative) const
  throw (CantorErreurs)
{ 
  // calcul du limbe complet
  Cone complet (etat.attitude () (visee_), etat.rayonCorpsCentral ());
 
  // filtrage du limbe par le champ de vue
  if (ptrChampDeVue_->visible (complet))
    *ptrEcartFrontiere = +1.0;
  else
    *ptrEcartFrontiere = -1.0;

  *ptrAmplitudeSignificative = false;

}
