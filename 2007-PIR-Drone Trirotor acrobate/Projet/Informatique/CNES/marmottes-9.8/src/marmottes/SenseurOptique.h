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
//>       SenseurOptique.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurOptique
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurOptique
//>       enum codeCible      
//
//$Historique
//       $Log: SenseurOptique.h,v $
//       Revision 2.20  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 2.19  2003/02/27 16:12:37  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 2.18  2002/12/11 17:18:58  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 2.17  2002/01/17 09:39:05  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 2.16  2001/07/17 15:15:32  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       changement des attributs privés en attributs protégés
//       ajout des attributs secteursFiltrables_ et observe_
//       la méthode filtreSecteurs n'est plus virtuelle
//
//       Revision 2.15  2001/05/23 09:54:13  luc
//       ajout de codeLuneSansEclipse
//
//       Revision 2.14  2001/04/04 12:06:00  luc
//       élimination des méthodes visible et inhibe
//       ajout des méthodes ecartFrontiere et criteresControlabilite
//
//       Revision 2.13  2001/03/26 11:12:07  luc
//       prise en charge du traitement des inhibitions implanté auparavant dans
//       l'ancienne classe SenseurTerre,
//       changement du nom de certains codes de cibles, en prévision
//       d'évolutions vers l'interplanétaire,
//       élimination du type énuméré typeOpt et de la fonction associée
//       typeOptique
//
//       Revision 2.12  2000/09/13 10:44:25  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 2.11  2000/03/30 17:01:24  luc
//       ajout du copyright CNES
//
//       Revision 2.10  1999/11/02 07:19:23  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 2.9  1999/08/25 09:41:05  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 2.8  1999/08/06 13:32:20  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 2.7  1999/04/20 16:04:50  luc
//       mise au propre du filtrage des secteurs de consigne
//       par les champs de vue
//
//       Revision 2.6  1998/11/06 12:40:35  luc
//       ajout de la cible nadir
//
//       Revision 2.5  1998/07/15 12:29:55  luc
//       support pour les cibles spécifiées par l'utilisateur
//       (avec ou sans calcul de parallaxe)
//
//       Revision 2.4  1998/06/25 06:15:34  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.3  1998/04/26 19:42:02  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.2  1998/02/04 08:43:47  luc
//       ajout des caractères d'échappement de fin de ligne
//       dans les en-têtes AMIGAU
//
//       Revision 2.1  1997/11/27 07:23:09  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout du paramétrage des cibles de type stations sol
//
//       Revision 1.3  1997/09/20 17:12:57  luc
//       ajout d'une cible pour la direction le long de la trace
//
//       Revision 1.2  1997/09/03 09:26:38  luc
//       ajout d'une cible terre-soleil
//
//       Revision 1.1  1997/08/20 09:54:48  luc
//       Initial revision
//
//$Version
//       $Id: SenseurOptique.h,v 2.20 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurOptique_h
#define __marmottes_SenseurOptique_h

#include "marmottes/Parcelle.h"
#include "marmottes/SenseurGeometrique.h"
#include "marmottes/StationCible.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurOptique
//
//$Resume
//       modèle d'un senseur optique, observant un point de l'espace
//
//$Description
//       classe abstraite masquant le type d'angle mesuré par
//       le senseur (angle dièdre ou angle entre vecteurs)
//       dérivation de la classe SenseurGeometrique
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       enum codeCible  : 
//          cible observée
//>       SenseurOptique& operator =            () 
//          affectation
//>       virtual void nouveauRepere            () 
//          tourne le senseur pour l'aligner sur le repère donné
//>       virtual int controlable               () 
//          indique si le senseur serait capable de contrôler
//          l'attitude de l'état donné
//>       virtual ValeurDerivee1 foncEcart      () 
//          calcule la fonction d'écart du senseur par rapport à sa
//          consigne à la date donnée et dans l'attitude donnée en
//          tenant compte de l'état précédent.
//>       virtual int criteresControlabilite    () 
//          calcule les critères de contrôlabilité de l'attitude
//          dans l'état donné
//>       virtual void modifieCible             () 
//          mémorise une cible utilisateur pour un senseur optique
//>       void initialiseCible                  () protegee - 
//          calcule et mémorise la direction de la cible en repère
//          inertiel
//>       virtual void ecartFrontiere           () protegee - 
//          indique si la cible est visible dans le champ de vue
//>       void filtreSecteurs                   () protegee - 
//          permet de filtrer le secteur de consigne par le champ de vue
//>       const Parcelle* champDeVue            () 
//          retourne un pointeur sur le champ de vue
//>       const Parcelle* champInhibitionSoleil () 
//          retourne le champ d'inhibition associé au soleil
//>       const Parcelle* champInhibitionLune   () 
//          retourne le champ d'inhibition associé à la lune
//>       const Parcelle* champInhibitionCentral() 
//          retourne le champ d'inhibition associé au corps central
//>       double margeEclipseSoleil             () 
//          retourne la marge à prendre sur les éclipses solaires
//>       double margeEclipseLune               () 
//          retourne la marge à prendre sur les éclipses lunaires
//>       virtual typeGeom typeGeometrique      () 
//          retourne le type de senseur géométrique (optique)
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class SenseurOptique : public SenseurGeometrique
{

  public :

  enum      codeCible {codeInvalide,             codeSoleil,
                       codeSoleilSansEclipse,    codeCorpsCentralSoleil,
                       codeLune,                 codeLuneSansEclipse,
                       codeCorpsCentral,         codeTerre,
                       codeVitesseSolApparente,  codeNadir,
                       codePolaire,              codeCanope,
                       codeVitesse,              codeMoment,
                       codeDevant,               codePosition,
                       codePositionSansEclipse,  codeDirection,
                       codeDirectionSansEclipse, codeStation,
                       codePolaireSansEclipse,   codeCanopeSansEclipse};

  // constructeurs
  SenseurOptique (const string& nom, const RotDBL& repere,
                  const VecDBL& axeCalage, double precision,
                  codeCible code, const StationCible *ptrStation,
                  const VecDBL& observe,
                  Parcelle* ptrChampDeVue,
                  Parcelle *ptrChampInhibitionSoleil,
                  Parcelle *ptrChampInhibitionLune,
                  Parcelle *ptrChampInhibitionCentral,
                  double margeEclipseSoleil, double margeEclipseLune,
                  double seuilPhaseLune);

  SenseurOptique (const SenseurOptique& s);

  SenseurOptique& operator = (const SenseurOptique& s);

  // destructeur
  virtual ~SenseurOptique ()
  {
    if (ptrChampDeVue_)
      delete ptrChampDeVue_;
    if (ptrChampInhibitionSoleil_)
      delete ptrChampInhibitionSoleil_;
    if (ptrChampInhibitionLune_)
      delete ptrChampInhibitionLune_;
    if (ptrChampInhibitionCentral_)
      delete ptrChampInhibitionCentral_;
   }

  // réorientation du senseur
  virtual void      nouveauRepere          (const RotDBL& nouveau);

  // fonctions d'accès aux éléments internes
  virtual typeGeom  typeGeometrique () const { return optique; }

  const Parcelle* champDeVue             () const
                  { return ptrChampDeVue_; }

  const Parcelle* champInhibitionSoleil  () const
                  { return ptrChampInhibitionSoleil_; }
                  
  const Parcelle* champInhibitionLune    () const
                  { return ptrChampInhibitionLune_; }

  const Parcelle* champInhibitionCentral () const
                  { return ptrChampInhibitionCentral_; }

  double          margeEclipseSoleil     () const
                  { return margeEclipseSoleil_; }

  double          margeEclipseLune       () const
                  { return margeEclipseLune_;   }

  virtual int     controlable            (const Etat& etat)
    throw (MarmottesErreurs, CantorErreurs);

  virtual void    criteresControlabilite (const Etat& etat,
                                          codeAstre *ptrInhibant,
                                          codeAstre *ptrEclipsant,
                                          double    *ptrEcartFrontiere,
                                          bool      *ptrAmplitudeSignificative)
    throw (MarmottesErreurs, CantorErreurs);

  // fonction de résolution de l'attitude
  virtual ValeurDerivee1 foncEcart  (const Etat& etatPrecedent,
                                     const Etat& etatResolution,
                                     const RotVD1& attitude,
                                     const VecVD1& spin
                                    );

  // fonction de mise à jour de la cible utilisateur
  virtual void    modifieCible           (const VecDBL& cible)
    throw (MarmottesErreurs);

  protected :
  VecDBL       visee_;
  Parcelle*    ptrChampDeVue_;
  Parcelle*    ptrChampInhibitionSoleil_;
  Parcelle*    ptrChampInhibitionLune_;
  Parcelle*    ptrChampInhibitionCentral_;
  double       margeEclipseSoleil_;
  double       margeEclipseLune_;
  double       seuilPhaseLune_;
  codeCible    code_;
  StationCible station_;
  VecDBL       observe_;
  double       rapportDistCentral_;
  double       rapportDistLune_;
  VecDBL       utilisateur_;
  bool         utilisateurInitialise_;
  bool         secteursFiltrables_;


  void reinitVitesseSolApparente (const Etat& etatPrecedent,
                                  const RotVD1& attitude)
    throw (MarmottesErreurs);

  void initialiseCible (const Etat& etat)
    throw (MarmottesErreurs);

  virtual void ecartFrontiere (const Etat& etat,
                               double *ptrEcartFrontiere,
                               bool *ptrAmplitudeSignificative) const
    throw (CantorErreurs);

  void filtreSecteurs ()
    throw (CantorErreurs);

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurOptique () {}

};

#endif
