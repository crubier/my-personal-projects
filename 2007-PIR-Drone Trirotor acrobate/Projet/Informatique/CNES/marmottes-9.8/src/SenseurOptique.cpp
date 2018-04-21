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
//>       SenseurOptique.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurOptique
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       static VecDBL cibleNadir()
//>       class SenseurOptique      
//>         filtreSecteurs()        
//>         SenseurOptique()        
//>         operator =()            
//>         nouveauRepere()         
//>         reinitVitesseSolApparente()       
//>         initialiseCible()       
//>         controlable()           
//>         criteresControlabilite()   
//>         modifieCible()          
//
//$Historique
//       $Log: SenseurOptique.cpp,v $
//       Revision 1.24  2004/03/04 15:17:02  marmottes
//       correction d'un return pour éliminer un avertissement de gcc 2.95
//
//       Revision 1.23  2003/10/08 09:39:40  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.22  2003/02/27 16:47:25  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.21  2003/02/04 16:41:47  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.20  2002/01/17 09:27:32  marmottes
//       correction de spécifications throw
//
//       Revision 1.19  2001/07/17 15:16:56  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       changement des attributs privés en attributs protégés
//       ajout des attributs visee_, secteursFiltrables_ et observe_
//       la méthode filtreSecteurs n'est plus virtuelle
//
//       Revision 1.18  2001/05/23 11:27:59  luc
//       ajout de la cible lune-sans-eclipse
//
//       Revision 1.17  2001/04/04 12:22:31  luc
//       élimination de la méthode visible,
//       ajout des méthodes ecartFrontiere et criteresControlabilite
//
//       Revision 1.16  2001/03/26 11:16:52  luc
//       prise en charge du traitement des inhibitions implanté auparavant dans
//       l'ancienne classe SenseurTerre
//
//       Revision 1.15  2000/09/13 10:44:54  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.14  2000/03/30 17:01:21  luc
//       ajout du copyright CNES
//
//       Revision 1.13  1999/08/20 07:37:29  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 1.12  1999/08/06 13:32:16  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.11  1999/04/26 11:39:08  luc
//       remplacement de abs par fabs
//
//       Revision 1.10  1999/04/20 16:03:47  luc
//       mise au propre du filtrage des secteurs de consigne par les champs de vue
//
//       Revision 1.9  1998/11/06 12:41:21  luc
//       ajout de la cible nadir
//
//       Revision 1.8  1998/07/15 12:45:56  luc
//       support pour les cibles spécifiées par l'utilisateur
//       (avec ou sans calcul de parallaxe)
//
//       Revision 1.7  1998/06/24 20:05:40  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.6  1998/04/29 10:10:45  luc
//       ajout d'une protection sur les normes litigieuses
//       également pour les senseurs terre (à cause de l'horizon)
//
//       Revision 1.5  1998/04/26 20:01:37  luc
//       inversion de la convention de nommage des attributs
//       prise en compte de la protection contre les normes litigieuses
//
//       Revision 1.4  1997/12/01 13:47:06  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout d'une cible de type station sol
//
//       Revision 1.3  1997/09/20 17:16:17  luc
//       ajout d'une cible pour la direction le long de la trace
//
//       Revision 1.2  1997/09/03 09:26:28  luc
//       renommage de Etat::soleil () en Etat::satSoleil ()
//       renommage de Etat::lune   () en Etat::satLune   ()
//       ajout d'une cible terre-soleil
//
//       Revision 1.1  1997/08/20 09:25:58  luc
//       Initial revision
//
//
//$Version
//       $Id: SenseurOptique.cpp,v 1.24 2004/03/04 15:17:02 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurOptique.h"

static VecDBL cibleNadir (const Etat& etat)
{ // calcul de la direction du nadir
  const double ae        = etat.rayonEquatorial ();
  const double e2        = (2.0 - etat.aplatissement ()) * etat.aplatissement ();
  const double unMoinsE2 = 1.0 - e2;
  const double racine    = sqrt (unMoinsE2);

  const VecDBL& position = etat.position ();
  double r     = sqrt (position.x () * position.x ()
                     + position.y () * position.y ());
  double alpha = r / ae;
  double beta  = position.z () / ae;

  // recherche du point d'intersection du nadir avec l'équateur
  // ae * eta est la distance entre ce point et l'axe des pôles
  double eta      = 0.0;
  double etaPrime = beta
                  / sqrt (beta * beta + unMoinsE2 * alpha * alpha);
  while (fabs (eta - etaPrime) > 1.0e-7)
  { // itérations sur l'intersection
    eta                  = etaPrime;
    double alphaMoinsEta = alpha - eta;
    double c1            = beta * beta * (1.0 - eta * eta);
    double c2            = unMoinsE2 * alphaMoinsEta * alphaMoinsEta;
    double c3            = racine * eta * alphaMoinsEta;
    double sinLambda     = beta * (sqrt (c1 + c2) - c3)
                         / (beta * beta + c2);
    etaPrime             = e2 * sqrt (1.0 - sinLambda * sinLambda);

  }

  // calcul du nadir
  double ascension = (r < 1.0e-3)
                   ? 0.0 : atan2 (position.y (), position.x ());
  VecDBL nadir = VecDBL (etaPrime * ae * cos (ascension),
                         etaPrime * ae * sin (ascension),
                         0.0) - position;
  nadir.normalise ();
  return nadir;

}

SenseurOptique::SenseurOptique (const string& nom, const RotDBL& repere,
                                const VecDBL& axeCalage, double precision,
                                codeCible code, const StationCible *ptrStation,
                                const VecDBL& observe,
                                Parcelle* ptrChampDeVue,
                                Parcelle* ptrChampInhibitionSoleil,
                                Parcelle* ptrChampInhibitionLune,
                                Parcelle* ptrChampInhibitionCentral,
                                double margeEclipseSoleil,
                                double margeEclipseLune,
                                double seuilPhaseLune)
  : SenseurGeometrique (nom, repere, axeCalage, precision),
    visee_ (1.0, 0.0, 0.0),
    ptrChampDeVue_ (ptrChampDeVue),
    ptrChampInhibitionSoleil_ (ptrChampInhibitionSoleil),
    ptrChampInhibitionLune_ (ptrChampInhibitionLune),
    ptrChampInhibitionCentral_ (ptrChampInhibitionCentral),
    margeEclipseSoleil_ (margeEclipseSoleil),
    margeEclipseLune_ (margeEclipseLune),
    seuilPhaseLune_ (seuilPhaseLune),
    code_ (code), observe_ (observe),
    rapportDistCentral_ (0.0), rapportDistLune_ (0.0),
    utilisateur_(1.0, 0.0, 0.0), utilisateurInitialise_ (false)
{
  if (ptrStation)
    station_ = *ptrStation;

  // projection des champs de vue et d'inhibition dans le repère
  // satellite
  RotDBL sensSat = -repere;

  if (ptrChampDeVue_)
    ptrChampDeVue_->appliqueRotation (sensSat);

  if (ptrChampInhibitionSoleil_)
    ptrChampInhibitionSoleil_->appliqueRotation (sensSat);

  if (ptrChampInhibitionLune_)
    ptrChampInhibitionLune_->appliqueRotation (sensSat);

  if (ptrChampInhibitionCentral_)
    ptrChampInhibitionCentral_->appliqueRotation (sensSat);

  // reconnaissance des cibles pour lesquelles on sait que l'on
  // ne peut pas utiliser le filtrage de secteurs pour accélérer
  // les calculs
  if (code == codeVitesseSolApparente)
    secteursFiltrables_ = false;
  else
    secteursFiltrables_ = true;

}

SenseurOptique::SenseurOptique (const SenseurOptique& s)
  : SenseurGeometrique (s),
    visee_ (s.visee_), ptrChampDeVue_ (0), ptrChampInhibitionSoleil_ (0),
    ptrChampInhibitionLune_ (0), ptrChampInhibitionCentral_ (0),
    margeEclipseSoleil_ (s.margeEclipseSoleil_),
    margeEclipseLune_   (s.margeEclipseLune_),
    seuilPhaseLune_     (s.seuilPhaseLune_),
    code_ (s.code_), station_ (s.station_),
    rapportDistCentral_ (s.rapportDistCentral_),
    rapportDistLune_ (s.rapportDistLune_),
    utilisateur_(1.0, 0.0, 0.0), utilisateurInitialise_ (false),
    secteursFiltrables_ (s.secteursFiltrables_)
{
  if (s.ptrChampDeVue_)
    ptrChampDeVue_ = s.ptrChampDeVue_->copie ();
  if (s.ptrChampInhibitionSoleil_)
    ptrChampInhibitionSoleil_ = s.ptrChampInhibitionSoleil_->copie ();
  if (s.ptrChampInhibitionLune_)
    ptrChampInhibitionLune_ = s.ptrChampInhibitionLune_->copie ();
  if (s.ptrChampInhibitionCentral_)
    ptrChampInhibitionCentral_ = s.ptrChampInhibitionCentral_->copie ();
}

SenseurOptique& SenseurOptique::operator = (const SenseurOptique& s)
{
  if (&s != this)    // protection contre x = x
  {
    if (ptrChampDeVue_)
      delete ptrChampDeVue_;
    if (ptrChampInhibitionSoleil_)
      delete ptrChampInhibitionSoleil_;
    if (ptrChampInhibitionLune_)
      delete ptrChampInhibitionLune_;
    if (ptrChampInhibitionCentral_)
      delete ptrChampInhibitionCentral_;

    SenseurGeometrique::operator = (s);
    visee_                    = s.visee_;
    ptrChampDeVue_            = s.ptrChampDeVue_ ?
                                s.ptrChampDeVue_->copie () : 0;
    ptrChampInhibitionSoleil_ = s.ptrChampInhibitionSoleil_ ?
                                s.ptrChampInhibitionSoleil_->copie () : 0;
    ptrChampInhibitionLune_   = s.ptrChampInhibitionLune_   ?
                                s.ptrChampInhibitionLune_->copie   () : 0;
    ptrChampInhibitionCentral_ = s.ptrChampInhibitionCentral_ ?
                                 s.ptrChampInhibitionCentral_->copie   () : 0;
    margeEclipseSoleil_       = s.margeEclipseSoleil_;
    margeEclipseLune_         = s.margeEclipseLune_;
    seuilPhaseLune_           = s.seuilPhaseLune_;
    code_                     = s.code_;
    station_                  = s.station_;
    rapportDistCentral_       = s.rapportDistCentral_;
    rapportDistLune_          = s.rapportDistLune_;
    utilisateur_              = s.utilisateur_;
    utilisateurInitialise_    = s.utilisateurInitialise_;
    secteursFiltrables_       = s.secteursFiltrables_;

  }

  return *this;

}

void SenseurOptique::nouveauRepere (const RotDBL& nouveau)
{ // réorientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));

  if (ptrChampDeVue_)
    ptrChampDeVue_->appliqueRotation             (decalage);
  if (ptrChampInhibitionSoleil_)
    ptrChampInhibitionSoleil_->appliqueRotation  (decalage);
  if (ptrChampInhibitionLune_)
    ptrChampInhibitionLune_->appliqueRotation    (decalage);
  if (ptrChampInhibitionCentral_)
    ptrChampInhibitionCentral_->appliqueRotation (decalage);

  // appel de la fonction de la classe de base
  SenseurGeometrique::nouveauRepere (nouveau);

}

void SenseurOptique::reinitVitesseSolApparente (const Etat& etat,
                                                const RotVD1& attitude)
  throw (MarmottesErreurs)
{
  VecVD1 visee  = (-attitude) (VecDBLVD1 (observe_));
  visee_        = VecVD1DBL (visee);
  VecDBL p      = etat.position ();
  double r      = etat.rayonEquatorial ();
  double uMApla = 1.0 - etat.aplatissement ();
  double k      = uMApla * uMApla;

  ValeurDerivee1 a = k * (visee.x () * visee.x () + visee.y () * visee.y ())
                   + visee.z () * visee.z ();
  ValeurDerivee1 b = k * (p.x () * visee.x () + p.y () * visee.y ())
                   + p.z () * visee.z ();
  double c = k * (p.x () * p.x () + p.y () * p.y () - r * r) + p.z () * p.z ();

  // si on suppose le point hors de l'ellipsoïde (ce qui semble
  // réaliste ...), alors "c" est positif, on sait d'autre part que "a"
  // est toujours positif. S'il y a des solutions, elles seront alors
  // toutes deux de même signe, et ce signe est l'opposé du signe de
  // "b". Il se trouve que l'on cherche une solution positive (seule la
  // demi-droite dans le sens de l'observation nous intéresse) et plus
  // précisément la solution la plus petite (l'autre solution
  // correspond au point où la demi-droite de visée ressort de
  // l'ellipsoïde)
  VecVD1 vitesseSol (0, 0, 0);
  ValeurDerivee1 lambda = 0;
  ValeurDerivee1 delta  = b * b - a * c;
  if ((delta.f0 () >= 0) && (b.f0 () <= 0))
  {
    // la direction visée rencontre pas l'ellipsoïde, on sait
    // calculer une vitesse propre non nulle
    ValeurDerivee1 omega (etat.vitesseRotation ());
    lambda = (-b - sqrt (delta)) / a;
    VecVD1 pointSol (VecDBLVD1 (p) + lambda * visee);
    vitesseSol = VecVD1 (ValeurDerivee1 (0.0), ValeurDerivee1 (0.0), omega)
               ^ pointSol;
  }

  // la cible est la vitesse apparente du point au sol visé
  cibleVD1_ = vitesseSol - VecDBLVD1 (etat.vitesse ());
  ValeurDerivee1 vR = cibleVD1_.norme ();
  if (vR.f0 () < 1.0e-10)
  {
    // satellite géostationnaire pur, on choisit une direction raisonnable
    cibleVD1_ = VecDBLVD1 (-etat.vitesse ());
    cibleVD1_.normalise ();
  }
  else
  {
    cibleVD1_ *= ValeurDerivee1 (1.0) / vR;
  }
  rapportDistCentral_ = 0.0;
  rapportDistLune_    = lambda.f0 () / etat.distLune ();

  cible_ = VecVD1DBL (cibleVD1_);

}

void SenseurOptique::initialiseCible (const Etat& etat)
  throw (MarmottesErreurs)
{ // initialisation de la direction de la cible en repère inertiel

  switch (code_)
  { case codeSoleil       :
      etat.normesLitigieuses ();
      cible_ = etat.satSoleil ();
      visee_ = cible_;
      rapportDistCentral_ = etat.distSoleil () / etat.position ().norme ();
      rapportDistLune_    = etat.distSoleil () / etat.distLune ();
      break;

    case codeSoleilSansEclipse :
      etat.normesLitigieuses ();
      cible_ = etat.satSoleil ();
      visee_ = cible_;
      rapportDistCentral_ = 0.0;
      rapportDistLune_    = 0.0;
      break;

    case codeCorpsCentralSoleil :
      cible_ = etat.terreSoleil ();
      visee_ = cible_;
      rapportDistCentral_ = 100.0;
      rapportDistLune_    = 100.0;
      break;

    case codeLune :
      etat.normesLitigieuses ();
      cible_ = etat.satLune ();
      visee_ = cible_;
      rapportDistCentral_ = etat.distLune () / etat.position ().norme ();
      rapportDistLune_    = 0.0;
      break;

    case codeLuneSansEclipse :
      etat.normesLitigieuses ();
      cible_ = etat.satLune ();
      visee_ = cible_;
      rapportDistCentral_ = 0.0;
      rapportDistLune_    = 0.0;
      break;

    case codeCorpsCentral :
      { // encapsulation du cas entre "{}" pour limiter la portée
        // des variables locales
        
        // pour l'instant, les cibles terre et corps-central sont identiques
        etat.normesLitigieuses ();
        double d = etat.position ().norme ();
        cible_ = etat.position () / -d;
        visee_ = cible_;
        rapportDistCentral_ = 0.0;
        rapportDistLune_    = d / etat.distLune ();
      }
      break;

    case codeTerre :
      { // encapsulation du cas entre "{}" pour limiter la portée
        // des variables locales
        
        // pour l'instant, les cibles terre et corps-central sont identiques
        etat.normesLitigieuses ();
        double d = etat.position ().norme ();
        cible_ = etat.position () / -d;
        visee_ = cible_;
        rapportDistCentral_ = 0.0;   //  <--- à revoir en interplanétaire
        rapportDistLune_    = d / etat.distLune ();
      }
      break;

    case codeVitesseSolApparente :
      reinitVitesseSolApparente (etat, RotDBLVD1 (etat.attitude ()));
      return;

    case codeNadir :
      etat.normesLitigieuses ();
      cible_ = cibleNadir (etat);
      visee_ = cible_;
      rapportDistCentral_ = 0.0;
      rapportDistLune_    = 0.0;
      break;

    case codePolaire :
      // ascension droite et déclinaison en J2000, le 01/01/1990
      cible_ = VecDBL (radians (37.9119222), radians (89.2643222));
      visee_ = cible_;
      rapportDistCentral_ = 100.0;
      rapportDistLune_    = 100.0;
      break;

    case codePolaireSansEclipse :
      // ascension droite et déclinaison en J2000, le 01/01/1990
      cible_ = VecDBL (radians (37.9119222), radians (89.2643222));
      visee_ = cible_;
      rapportDistCentral_ = 0.0;
      rapportDistLune_    = 0.0;
      break;

    case codeCanope :
      // ascension droite et déclinaison en J2000, le 01/01/1990
      cible_ = VecDBL (radians (95.9875194), radians (-52.6959861));
      visee_ = cible_;
      rapportDistCentral_ = 100.0;
      rapportDistLune_    = 100.0;
      break;

    case codeCanopeSansEclipse :
      // ascension droite et déclinaison en J2000, le 01/01/1990
      cible_ = VecDBL (radians (95.9875194), radians (-52.6959861));
      visee_ = cible_;
      rapportDistCentral_ = 0.0;
      rapportDistLune_    = 0.0;
      break;

    case codeVitesse :
      cible_ = etat.vitesse () / etat.vitesse ().norme ();
      visee_ = cible_;
      rapportDistCentral_ = 0.0;
      rapportDistLune_    = 0.0;
      break;

    case codeMoment :
      cible_ = etat.position () ^ etat.vitesse ();
      cible_.normalise ();
      visee_ = cible_;
      rapportDistCentral_ = 0.0;
      rapportDistLune_    = 0.0;
      break;

    case codeDevant :
      cible_ = (etat.position () ^ etat.vitesse ()) ^ etat.position ();
      cible_.normalise ();
      visee_ = cible_;
      rapportDistCentral_ = 0.0;
      rapportDistLune_    = 0.0;
      break;

    case codePosition :
        // on corrige la parallaxe
        if (utilisateurInitialise_)
        {
          cible_ = utilisateur_ - etat.position ();
          double d = cible_.norme ();
          cible_ /= d;
          visee_ = cible_;
          rapportDistCentral_ = d / etat.position ().norme ();
          rapportDistLune_    = d / etat.distLune ();
        }
        else
           throw MarmottesErreurs (MarmottesErreurs::cible_utilisateur,
                                   nom ().c_str ());
      break;

    case codePositionSansEclipse :
        // on corrige la parallaxe
        if (utilisateurInitialise_)
        { cible_ = utilisateur_ - etat.position ();
          cible_.normalise ();
          visee_ = cible_;
          rapportDistCentral_ = 0.0;
          rapportDistLune_    = 0.0;
        }
        else
           throw MarmottesErreurs (MarmottesErreurs::cible_utilisateur,
                                   nom ().c_str ());
      break;

    case codeDirection :
        if (utilisateurInitialise_)
        { cible_ = utilisateur_;
          cible_.normalise ();
          visee_ = cible_;
          rapportDistCentral_ = 100.0;
          rapportDistLune_    = 100.0;
        }
        else
           throw MarmottesErreurs (MarmottesErreurs::cible_utilisateur,
                                   nom ().c_str ());
      break;

    case codeDirectionSansEclipse :
        if (utilisateurInitialise_)
        { cible_ = utilisateur_;
          cible_.normalise ();
          visee_ = cible_;
          rapportDistCentral_ = 0.0;
          rapportDistLune_    = 0.0;
        }
        else
           throw MarmottesErreurs (MarmottesErreurs::cible_utilisateur,
                                   nom ().c_str ());
      break;

    case codeStation :
      { // encapsulation du cas entre "{}" pour limiter la portée
        // des variables locales
        etat.normesLitigieuses ();

        RotDBL terreInert (VecDBL (0.0, 0.0, 1.0), etat.tempsSideral ());
        cible_ = terreInert (station_.position ()) - etat.position ();
        double d = cible_.norme ();
        cible_ /= d;
        visee_ = cible_;

        // il FAUT mettre une valeur > 1 ici, pour que le calcul de
        // masquage par la terre en tenant compte du site minimal soit
        // déclenché correctement
        rapportDistCentral_ = 1.1;

        rapportDistLune_    = d / etat.distLune ();
      
      }
      break;

    default : // on ne peut passer ici qu'en cas d'incohérence dans le code
      cible_ = VecDBL (1, 0, 0);
      visee_ = cible_;
      rapportDistCentral_ = 0.0;
      rapportDistLune_    = 0.0;
      throw MarmottesErreurs (MarmottesErreurs::cas_impossible,
                              __LINE__, __FILE__);
      break;

  }

  // on fait la conversion en développement limité une fois pour toutes
  cibleVD1_ = VecDBLVD1 (cible_);

}

int SenseurOptique::controlable (const Etat& etat)
  throw (MarmottesErreurs, CantorErreurs)
{ 
  codeAstre astreInhibant, astreEclipsant;
  double    ecart;
  bool      ignored;
  criteresControlabilite (etat,
                          &astreInhibant, &astreEclipsant, &ecart,
                          &ignored);

  return (astreInhibant == aucunAstre)
    && (astreEclipsant  == aucunAstre)
    && (ecart >= 0.0);

}


void SenseurOptique::criteresControlabilite (const Etat& etat,
                                             codeAstre *ptrInhibant,
                                             codeAstre *ptrEclipsant,
                                             double *ptrEcartFrontiere,
                                             bool *ptrAmplitudeSignificative)
  throw (MarmottesErreurs, CantorErreurs)
{ // test de l'inhibition du senseur par la lune ou le soleil

    // initialisation de la direction de la cible du senseur
    initialiseCible (etat);

    // traitement des inhibitions
    *ptrInhibant = aucunAstre;
    if (ptrChampInhibitionSoleil_
        || ptrChampInhibitionLune_
        || ptrChampInhibitionCentral_)
    { // il y a des champs d'inhibition

      // direction des astres perturbateurs en repère satellite
      VecDBL dirSoleil  = etat.attitude () (etat.satSoleil  ());
      VecDBL dirLune    = etat.attitude () (etat.satLune    ());
      VecDBL dirCentral = etat.attitude () (-(etat.position ()));

      dirCentral.normalise();

      double anglePhaseLune = dirSoleil.angleAvecVecteur (-dirLune);

      // prise en compte des éclipses des astres inhibants
      double angleCorpsCentral = etat.rayonCorpsCentral ();

      double corpsSol   = etat.satSoleil ().angleAvecVecteur (-(etat.position ()));
      double luneSol    = etat.satSoleil ().angleAvecVecteur (etat.satLune ());
      bool   eclipseSol = ((corpsSol + margeEclipseSoleil_) <= angleCorpsCentral)
        || ((luneSol  + margeEclipseSoleil_) <= etat.rayonLune ());

      double corpsLune   = etat.satLune ().angleAvecVecteur (-(etat.position ()));
      bool   eclipseLune = ((corpsLune + margeEclipseLune_) <= angleCorpsCentral);

      // test de la présence dans les champs d'inhibition
      if (ptrChampInhibitionSoleil_
          && (code_ != codeSoleil)
          && (code_ != codeSoleilSansEclipse)
          && (! eclipseSol)
          && (ptrChampInhibitionSoleil_->ecartFrontiere (dirSoleil)
              > -(etat.rayonSoleil())))
        *ptrInhibant = soleil;
      else if (ptrChampInhibitionLune_
               && (code_ != codeLune)
               && (anglePhaseLune <= seuilPhaseLune_)
               && (! eclipseLune)
               && (ptrChampInhibitionLune_->ecartFrontiere (dirLune)
                   > -(etat.rayonLune())))
        *ptrInhibant = lune;
      else if (ptrChampInhibitionCentral_
               && ((code_ != codeCorpsCentral)
                   && (code_ != codeVitesseSolApparente)
                   && (code_ != codeNadir))
               && (ptrChampInhibitionCentral_->ecartFrontiere (dirCentral)
                   > -(etat.rayonCorpsCentral())))
        *ptrInhibant = corpsCentral;

    }

    // traitement des éclipses (et phénomènes assimilés)
    *ptrEclipsant = aucunAstre;
    if (rapportDistCentral_ > 1.0)
    { // la cible peut être cachée par le corps central

      if (code_ == codeStation)
      { // cas particulier des stations, on considère le site minimal
        RotDBL inertCentral (VecDBL (0.0, 0.0, 1.0), -(etat.tempsSideral ()));
        if (! station_.visiblePt (inertCentral (etat.position ())))
          *ptrEclipsant = corpsCentral;
      }
      else
      {
        double angleVisee = visee_.angleAvecVecteur (-(etat.position ()));
        if (angleVisee <= etat.rayonCorpsCentral ())
          *ptrEclipsant = corpsCentral;
      }

    }

    if ((*ptrEclipsant == aucunAstre) && (rapportDistLune_ > 1.0))
    { // la cible peut être cachée par la lune
      double angleVisee = visee_.angleAvecVecteur (etat.satLune ());
      if (angleVisee <= etat.rayonLune ())
        *ptrEclipsant = lune;
    }


    // traitement des champs de vue
    ecartFrontiere (etat, ptrEcartFrontiere, ptrAmplitudeSignificative);


}


void SenseurOptique::ecartFrontiere (const Etat& etat,
                                     double *ptrEcartFrontiere,
                                     bool *ptrAmplitudeSignificative) const
  throw (CantorErreurs)
{

  if (ptrChampDeVue_)
  {
    VecDBL v = etat.attitude () (visee_);
    *ptrEcartFrontiere         = ptrChampDeVue_->ecartFrontiere (v);
    *ptrAmplitudeSignificative = true;
  }
  else
  {
    *ptrEcartFrontiere         = -1.0;
    *ptrAmplitudeSignificative = false;
  }

}


void SenseurOptique::modifieCible (const VecDBL& cible)
  throw (MarmottesErreurs)
{ // mémorisation d'une cible utilisateur
  if ((code_ != codePosition)  && (code_ != codePositionSansEclipse)
   && (code_ != codeDirection) && (code_ != codeDirectionSansEclipse))
    throw MarmottesErreurs (MarmottesErreurs::modifie_cible,
                            nom ().c_str ());

  utilisateur_           = cible;
  utilisateurInitialise_ = true;

}

void SenseurOptique::filtreSecteurs ()
  throw (CantorErreurs)
{ // filtrage du secteur de consigne par le champ de vue
  if (secteursFiltrables_ && (ptrChampDeVue_ != 0))
    secteursConsigne_ = ptrChampDeVue_->visible (secteursConsigne_);
}

ValeurDerivee1 SenseurOptique::foncEcart (const Etat& etatPrecedent,
                                          const Etat& etatResolution,
                                          const RotVD1& attitude,
                                          const VecVD1& spin)
{

  if (code_ == codeVitesseSolApparente)
  { // il faut réinitialiser la cible, qui dépend de l'attitude
    reinitVitesseSolApparente (etatResolution, attitude);
  }

  return SenseurGeometrique::foncEcart (etatPrecedent, etatResolution,
                                        attitude, spin);

}
