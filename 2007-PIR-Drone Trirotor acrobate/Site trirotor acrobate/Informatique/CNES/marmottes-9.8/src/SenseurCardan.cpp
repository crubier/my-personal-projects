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
//>       SenseurCardan.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurCardan
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurCardan  
//>         metAJourReference()
//>         operator =()       
//>         respecterMesures() 
//>         convertirMesures() 
//>         modeliseConsigne() 
//>         mesure()           
//>         modifieReference() 
//
//$Historique
//       $Log: SenseurCardan.cpp,v $
//       Revision 1.18  2005/03/04 14:10:09  chope
//       recalage de la mesure à moins de 180 degrés de la consigne initiale (FA-ID 230)
//
//       Revision 1.17  2003/02/04 16:38:02  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.16  2002/01/17 09:26:19  marmottes
//       correction de spécifications throw
//
//       Revision 1.15  2001/06/06 08:23:04  luc
//       remontée des exceptions Cantor
//
//       Revision 1.14  2001/01/25 16:28:02  luc
//       changement du type de refUtilInitialisee_ en bool
//       correction d'une erreur de prise en compte du repère senseur
//
//       Revision 1.13  2000/09/13 10:07:01  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.12  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 1.11  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 1.10  1999/08/06 13:32:15  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.9  1998/09/14 11:49:49  luc
//       vérification de la consigne générée
//
//       Revision 1.8  1998/08/13 12:33:58  luc
//       utilisation de l'erreur cas_impossible à la place de genre_cardan_inconnu
//
//       Revision 1.7  1998/08/07 09:40:12  luc
//       introduction d'attributs spécifiques pour le repère utilisateur,
//       correction de l'influence du repère senseur
//
//       Revision 1.6  1998/07/15 12:44:36  luc
//       modélisation de tous les angles
//       (auparavant, le troisième angle n'était pas géré par cette classe)
//       support de plusieurs repères de références
//       (dont un spécifié par l'utilisateur)
//
//       Revision 1.5  1998/06/24 20:03:12  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.4  1998/04/26 19:40:56  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.3  1998/02/04 09:18:26  luc
//       élimination d'une variable inutilisée
//
//       Revision 1.2  1997/09/23 09:29:15  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/09/21 11:16:47  luc
//       Initial revision
//
//$Version
//       $Id: SenseurCardan.cpp,v 1.18 2005/03/04 14:10:09 chope Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Util.h"
#include "cantor/DeclDBLVD1.h"

#include "marmottes/SenseurCardan.h"

void SenseurCardan::metAJourReference (const Etat& etat)
  throw (MarmottesErreurs)
{ // mise à jour du repère de référence

  try
  {
    // axes canoniques
    VecDBL Xcan (1.0, 0.0, 0.0);
    VecDBL Ycan (0.0, 1.0, 0.0);
    VecDBL Zcan (0.0, 0.0, 1.0);

    RotDBL refInert;
    switch (reference_)
    {
      case Geocentrique :
        // Z vers la terre, Y normal à l'orbite, X vers +Vit
        refInert = RotDBL (-Zcan, Ycan,
                           etat.position (), etat.vitesse () ^ etat.position ());
        break;

      case OrbitalTNW :
        // X vers la vitesse, Z normal à l'orbite
        refInert = RotDBL (Xcan, Zcan,
                           etat.vitesse (), etat.position () ^ etat.vitesse ());
        break;

      case OrbitalQSW :
        // X radial extérieur, Z normal à l'orbite
        refInert = RotDBL (Xcan, Zcan,
                           etat.position (), etat.position () ^ etat.vitesse ());
        break;

      case Inertiel :
        refInert = RotDBL (1.0, 0.0, 0.0, 0.0);
        break;

      case Topocentrique :
        // Z vers le nadir, Y vers l'Est
        refInert = RotDBL (-Zcan, Ycan,
                           etat.position (), VecDBL (-(etat.position ().y ()),
                                                     etat.position ().x (),
                                                     0.0));
        break;

      case Utilisateur :
        if (! refUtilInitialisee_)
          throw MarmottesErreurs (MarmottesErreurs::reference_utilisateur,
                                  nom ().c_str ());
        refInert = -(repere () (referenceUtilisateur_));
        break;

      default :
        throw MarmottesErreurs (MarmottesErreurs::cas_impossible,
                                __LINE__, __FILE__);
        break;

    }

    // coordonnées en repère inertiel des vecteurs de base du repère de référence
    xIn_ = refInert (Xcan);
    yIn_ = refInert (Ycan);
    zIn_ = refInert (Zcan);

  }

  catch (CantorErreurs ce)
  { // transcription de l'erreur
    MarmottesErreurs me (MarmottesErreurs::rotation_cardan, nom ().c_str ());
    ce.correction ();
    throw me;
  }

}

SenseurCardan& SenseurCardan::operator = (const SenseurCardan& s)
{ if (&s != this)    // protection contre x = x
  { Senseur::operator = (s);
    genre_                = s.genre_;
    reference_            = s.reference_;
    refUtilInitialisee_   = s.refUtilInitialisee_;
    referenceUtilisateur_ = s.referenceUtilisateur_;
    xIn_                  = s.xIn_;
    yIn_                  = s.yIn_;
    zIn_                  = s.zIn_;
  }

  return *this;

}

void SenseurCardan::respecterMesures ()
{ // mémorisation du besoin de fournir des mesures en radians

  if (conversionMesures ())
    reinitialisePrecision (radians (precision ())); // jusque là on était en degrés

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();

}

void SenseurCardan::convertirMesures ()
{ // mémorisation du besoin de fournir des mesures en degrés

  if (! conversionMesures ())
    reinitialisePrecision (degres (precision ())); // jusque là on était en radians

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();

}

void SenseurCardan::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  if (conversionConsignes ())
    valeur = radians (valeur);  // la consigne était en degrés

  // la valeur mémorisée doit l'être dans l'unité de mesure
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (valeur));
  else
    Senseur::modeliseConsigne (etat, valeur);

  // axes canoniques
  VecDBL Xcan (1.0, 0.0, 0.0);
  VecDBL Ycan (0.0, 1.0, 0.0);
  VecDBL Zcan (0.0, 0.0, 1.0);

  metAJourReference (etat);

  switch (genre_)
  { // chaque angle dans chaque série a un modèle propre

    case LRTLacet :
      cible_            = cos (valeur) * xIn_ + sin (valeur) * yIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (Ycan), 0.5 * M_PI));
      break;

    case LRTRoulis :
      cible_            = zIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (Ycan),
                                          0.5 * M_PI - valeur));
      break;

    case LRTTangage :
      cible_            = zIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (cos (valeur) * Xcan
                                                   + sin (valeur) * Zcan),
                                          0.5 * M_PI));
      break;

    case LTRLacet :
      cible_            = -sin (valeur) * xIn_ + cos (valeur) * yIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (Xcan), 0.5 * M_PI));
      break;

    case LTRTangage :
      cible_            = zIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (-Xcan),
                                          0.5 * M_PI - valeur));
      break;

    case LTRRoulis :
      cible_            = zIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (cos (valeur) * Ycan
                                                 - sin (valeur) * Zcan),
                                          0.5 * M_PI));
      break;

    case RLTRoulis :
      cible_            = -sin (valeur) * yIn_ + cos (valeur) * zIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (Ycan), 0.5 * M_PI));
      break;

    case RLTLacet :
      cible_            = xIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (-Ycan),
                                          0.5 * M_PI - valeur));
      break;

    case RLTTangage :
      cible_            = xIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (cos (valeur) * Zcan
                                                 - sin (valeur) * Xcan),
                                          0.5 * M_PI));
      break;

    case RTLRoulis :
      cible_            = cos (valeur) * yIn_ + sin (valeur) * zIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (Zcan), 0.5 * M_PI));
      break;

    case RTLTangage :
      cible_            = xIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (Zcan),
                                          0.5 * M_PI - valeur));
      break;

    case RTLLacet :
      cible_            = xIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (cos (valeur) * Ycan
                                                 + sin (valeur) * Xcan),
                                          0.5 * M_PI));
      break;

    case TLRTangage :
      cible_            = sin (valeur) * xIn_ + cos (valeur) * zIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (Xcan), 0.5 * M_PI));
      break;

    case TLRLacet :
      cible_            = -yIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (-Xcan),
                                          0.5 * M_PI - valeur));
      break;

    case TLRRoulis :
      cible_            = -yIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (cos (valeur) * Zcan
                                                 + sin (valeur) * Ycan),
                                          0.5 * M_PI));
      break;

    case TRLTangage :
      cible_            = cos (valeur) * xIn_ - sin (valeur) * zIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (Zcan), 0.5 * M_PI));
      break;

    case TRLRoulis :
      cible_            = -yIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (Zcan),
                                          0.5 * M_PI - valeur));
      break;

    case TRLLacet :
      cible_            = -yIn_;
      secteursConsigne_ = Secteurs (Cone (sensSat (cos (valeur) * Xcan
                                                 - sin (valeur) * Ycan),
                                          0.5 * M_PI));
      break;

    default :
      throw MarmottesErreurs (MarmottesErreurs::cas_impossible,
                              __LINE__, __FILE__);

  }

  // on fait les conversions en développement limité une fois pour toutes
  cibleVD1_ = VecDBLVD1 (cible_);
  axeVD1_   = VecDBLVD1 (secteursConsigne_.cone ().axe ());

  // retour normal à la fonction appelante
  verifieConsigne ();

}

double SenseurCardan::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{
  // axes canoniques
  VecDBL Xcan (1.0, 0.0, 0.0);
  VecDBL Ycan (0.0, 1.0, 0.0);
  VecDBL Zcan (0.0, 0.0, 1.0);

  metAJourReference (etat);

  // rotation permettant de projeter des vecteurs de repère de
  // référence (qui est le repère senseur pour les mesures nulles) en
  // repère inertiel
  RotDBL referenceInertiel (Zcan, Ycan, zIn_, yIn_);

  // passage du repère de référence au repère senseur
  // référence -> inertiel -> satellite -> senseur
  RotDBL referenceSenseur = repere () (etat.attitude () (referenceInertiel));

  VecDBL v;
  double m;
  switch (genre_)
  { // chaque angle dans chaque série a un modèle propre

    case LRTLacet :
      // Ysenseur a comme coordonnées dans le repère de référence :
      // -cos (phi) sin (psi), cos (phi) cos (psi), sin (phi)
      // et on peut imposer à phi de rester dans [-PI/2 ; +PI/2]
      v = (-referenceSenseur) (Ycan);
      m = atan2 (-(v.x ()), v.y ());
      break;

    case LRTRoulis :
      // Zréférence a comme coordonnées dans le repère senseur :
      // -sin (theta) cos (phi), sin (phi), cos (theta) cos (phi)
      v = referenceSenseur (Zcan);
      m = asin (v.y ());
      break;

    case LRTTangage :
      // Zréférence a comme coordonnées dans le repère senseur :
      // -sin (theta) cos (phi), sin (phi), cos (theta) cos (phi)
      v = referenceSenseur (Zcan);
      m = atan2 (-(v.x ()), v.z ());
      break;

    case LTRLacet :
      // Xsenseur a comme coordonnées dans le repère de référence :
      //  cos (theta) cos (psi), cos (theta) sin (psi), -sin (theta)
      // et on peut imposer à theta de rester dans [-PI/2 ; +PI/2]
      v = (-referenceSenseur) (Xcan);
      m = atan2 (v.y (), v.x ());
      break;

    case LTRTangage :
      // Zréférence a comme coordonnées dans le repère senseur :
      // -sin (theta), sin (phi) cos (theta), cos (phi) cos (theta)
      v = referenceSenseur (Zcan);
      m = -asin (v.x ());
      break;

    case LTRRoulis :
      // Zréférence a comme coordonnées dans le repère senseur :
      // -sin (theta), sin (phi) cos (theta), cos (phi) cos (theta)
      v = referenceSenseur (Zcan);
      m = atan2 (v.y (), v.z ());
      break;

    case RLTRoulis :
      // Ysenseur a comme coordonnées dans le repère de référence :
      // -sin (psi), cos (psi) cos (phi), cos (psi) sin (phi)
      // et on peut imposer à psi de rester dans [-PI/2 ; +PI/2]
      v = (-referenceSenseur) (Ycan);
      m = atan2 (v.z (), v.y ());
      break;

    case RLTLacet :
      // Xréférence a comme coordonnées dans le repère senseur :
      // cos (theta) cos (psi), -sin (psi), sin (theta) cos (psi)
      v = referenceSenseur (Xcan);
      m = -asin (v.y ());
      break;

    case RLTTangage :
      // Xréférence a comme coordonnées dans le repère senseur :
      // cos (theta) cos (psi), -sin (psi), sin (theta) cos (psi)
      v = referenceSenseur (Xcan);
      m = atan2 (v.z (), v.x ());
      break;

    case RTLRoulis :
      // Zsenseur a comme coordonnées dans le repère de référence :
      //  sin (theta), -cos (theta) sin (phi), cos (theta) cos (phi)
      // et on peut imposer à theta de rester dans [-PI/2 ; +PI/2]
      v = (-referenceSenseur) (Zcan);
      m = atan2 (-(v.y ()), v.z ());
      break;

    case RTLTangage :
      // Xréférence a comme coordonnées dans le repère senseur :
      // cos (psi) cos (theta), -sin (psi) cos (theta), sin (theta)
      v = referenceSenseur (Xcan);
      m = asin (v.z ());
      break;

    case RTLLacet :
      // Xréférence a comme coordonnées dans le repère senseur :
      // cos (psi) cos (theta), -sin (psi) cos (theta), sin (theta)
      v = referenceSenseur (Xcan);
      m = atan2 (-(v.y ()), v.x ());
      break;

    case TLRTangage :
      // Xsenseur a comme coordonnées dans le repère de référence :
      // cos (psi) cos (theta), sin (psi), -cos (psi) sin (theta)
      // et on peut imposer à psi de rester dans [-PI/2 ; +PI/2]
      v = (-referenceSenseur) (Xcan);
      m = atan2 (-(v.z ()), v.x ());
      break;

    case TLRLacet :
      // Yréférence a comme coordonnées dans le repère senseur :
      // sin (psi), cos (phi) cos (psi), -sin (phi) cos (psi)
      v = referenceSenseur (Ycan);
      m = asin (v.x ());
      break;

    case TLRRoulis :
      // Yréférence a comme coordonnées dans le repère senseur :
      // sin (psi), cos (phi) cos (psi), -sin (phi) cos (psi)
      v = referenceSenseur (Ycan);
      m = atan2 (-(v.z ()), v.y ());
      break;

    case TRLTangage :
      // Zsenseur a comme coordonnées dans le repère de référence :
      //  cos (phi) sin (theta), -sin (phi), cos (phi) cos (theta)
      // et on peut imposer à phi de rester dans [-PI/2 ; +PI/2]
      v = (-referenceSenseur) (Zcan);
      m = atan2 (v.x (), v.z ());
      break;

    case TRLRoulis :
      // Yréférence a comme coordonnées dans le repère senseur :
      // sin (psi) cos (phi), cos (psi) cos (phi), -sin (phi)
      v = referenceSenseur (Ycan);
      m = -asin (v.z ());
      break;

    case TRLLacet :
      // Yréférence a comme coordonnées dans le repère senseur :
      // sin (psi) cos (phi), cos (psi) cos (phi), -sin (phi)
      v = referenceSenseur (Ycan);
      m = atan2 (v.x (), v.y ());
      break;

    default :
      throw MarmottesErreurs (MarmottesErreurs::cas_impossible,
                              __LINE__, __FILE__);
  }

  if (conversionMesures ())
  {
    m = degres (m);  // la mesure doit être en degrés
    m -= 360.0 * floor ((m - valeurConsigne () + 180.0) / 360.0);
  }
  else
    m -= (M_PI + M_PI) * floor ((m - valeurConsigne () + M_PI) / (M_PI + M_PI));

  return m;

}

void SenseurCardan::modifieReference (const RotDBL& reference)
  throw (MarmottesErreurs)
{ // mémorisation d'un repère de référence utilisateur
  if (reference_ != Utilisateur)
    throw MarmottesErreurs (MarmottesErreurs::modifie_reference,
                            nom ().c_str ());

  // on considère la référence comme une attitude, c'est à dire que la
  // rotation transforme des vecteurs du repère inertiel en repère de
  // référence (ceci permet d'utiliser comme référence une attitude
  // directement issue d'une simulation Marmottes précédente)
  refUtilInitialisee_   = true;
  referenceUtilisateur_ = reference;

}
