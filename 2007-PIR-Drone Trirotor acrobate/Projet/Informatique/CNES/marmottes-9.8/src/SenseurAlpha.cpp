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
//>       SenseurAlpha.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurAlpha
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurAlpha  
//>         initialiseCible() 
//>         SenseurAlpha()    
//>         operator =()      
//>         respecterMesures()
//>         convertirMesures()
//>         nouveauRepere()   
//>         modeliseConsigne()
//>         mesure()          
//>         foncEcart()       
//
//$Historique
//       $Log: SenseurAlpha.cpp,v $
//       Revision 1.12  2003/10/08 09:39:41  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.11  2003/02/04 16:37:23  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.10  2002/01/17 09:26:19  marmottes
//       correction de spécifications throw
//
//       Revision 1.9  2000/09/13 10:06:29  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.8  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 1.7  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 1.6  1999/08/06 13:32:15  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.5  1998/06/24 20:02:54  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.4  1998/04/26 20:00:18  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.3  1998/02/06 17:33:14  luc
//       ajout d'une spécialisation de foncEcart de sorte que
//       la valeur produite soit bien un écart entre mesure et consigne
//       (dans le cas contraire, des problèmes se posent pour des
//       pseudo-senseurs utilisant une cible très proche de l'axe sensible)
//
//       Revision 1.2  1997/09/23 09:29:08  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:23:07  luc
//       Initial revision
//
//$Version
//       $Id: SenseurAlpha.cpp,v 1.12 2003/10/08 09:39:41 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurAlpha.h"

void SenseurAlpha::initialiseCible (double alpha)
{ // sauvegarde de la dernière valeur de consigne en ascension droite
  alphaConsigne_ = alpha;

  // initialisation de la direction de pointage cible du senseur
  cible_ = VecDBL (sin (alpha), -cos (alpha), 0.0);

  // on fait la conversion en développement limité une fois pour toutes
  cibleVD1_ = VecDBLVD1 (cible_);

}

SenseurAlpha::SenseurAlpha (const string& nom, const RotDBL& repere,
                            const VecDBL& axeCalage, double precision,
                            const VecDBL& observe)
  : SenseurGeometrique (nom, repere, axeCalage, radians (precision))
{ // calcul du vecteur observé en repère satellite
  observe_       = (-repere) (observe);

  // consigne par défaut: alpha = 0
  initialiseCible (0.0);

}

SenseurAlpha& SenseurAlpha::operator = (const SenseurAlpha& s)
{ if (&s != this)    // protection contre x = x
  { SenseurGeometrique::operator = (s);
    observe_       = s.observe_;
    alphaConsigne_ = s.alphaConsigne_;
  }

  return *this;

}

void SenseurAlpha::respecterMesures ()
{ // mémorisation du besoin de fournir des mesures en radians

  if (conversionMesures ())
    reinitialisePrecision (radians (precision ())); // jusque là on était en degrés

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();

}

void SenseurAlpha::convertirMesures ()
{ // mémorisation du besoin de fournir des mesures en degrés

  if (! conversionMesures ())
    reinitialisePrecision (degres (precision ())); // jusque là on était en radians

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();

}

void SenseurAlpha::nouveauRepere (const RotDBL& nouveau)
{ // réorientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));
  observe_ = decalage (observe_);

  // appel de la fonction de la classe de base
  SenseurGeometrique::nouveauRepere (nouveau);

}

void SenseurAlpha::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  if (conversionConsignes ())
    valeur = radians (valeur);  // la consigne était en degrés

  // la valeur mémorisée doit l'être dans l'unité de mesure
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (valeur));
  else
    Senseur::modeliseConsigne (etat, valeur);

  initialiseCible (valeur);

  // une consigne d'ascension droite est un plan (= cône d'ouverture PI/2)
  secteursConsigne_ = Secteurs (Cone (observe_, 0.5 * M_PI));

  // on fait la conversion en développement limité une fois pour toutes
  axeVD1_ = VecDBLVD1 (observe_);

}

double SenseurAlpha::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{ 
  // projection de l'axe observé dans le repère inertiel
  VecDBL obsInl ((-(etat.attitude ())) (observe_));

  // calcul de l'ascension droite
  double alpha = atan2 (obsInl.y (), obsInl.x ());

  // placement de la discontinuité loin de la valeur de consigne
  double m = recaleAngle (alpha, alphaConsigne_);
  if (conversionMesures ())
    m = degres (m);  // la mesure doit être en degrés

  return m;

}

ValeurDerivee1 SenseurAlpha::foncEcart (const Etat& etatPrecedent,
                                        const Etat& etatResolution,
                                        const RotVD1& attitude,
                                        const VecVD1& spin)
{ VecVD1 obsInl = (-attitude) (axeVD1_);
  ValeurDerivee1 alpha = atan2 (obsInl.y (), obsInl.x ());

  // placement de la discontinuité loin de la valeur de consigne
  int            k = (int) floor ((alpha.f0 () + M_PI - alphaConsigne_) / (M_PI + M_PI));
  ValeurDerivee1 m = alpha - k * (M_PI + M_PI);
  if (conversionMesures ())
    m *= 180.0 / M_PI; // la fonction degres () ne fonctionne qu'avec des doubles

  return m - valeurConsigne ();

}
