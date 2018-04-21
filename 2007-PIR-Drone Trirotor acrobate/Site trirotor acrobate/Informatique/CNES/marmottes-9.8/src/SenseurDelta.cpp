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
//>       SenseurDelta.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurDelta
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurDelta  
//>         operator =()      
//>         respecterMesures()
//>         convertirMesures()
//>         nouveauRepere()   
//>         modeliseConsigne()
//>         mesure()          
//
//$Historique
//       $Log: SenseurDelta.cpp,v $
//       Revision 1.10  2003/02/04 16:39:08  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.9  2002/01/17 09:27:32  marmottes
//       correction de spécifications throw
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
//       Revision 1.5  1998/09/14 11:50:38  luc
//       vérification de la consigne générée
//
//       Revision 1.4  1998/06/24 20:04:15  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.3  1998/04/26 19:43:20  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.2  1997/09/23 09:29:39  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:23:12  luc
//       Initial revision
//
//$Version
//       $Id: SenseurDelta.cpp,v 1.10 2003/02/04 16:39:08 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurDelta.h"

SenseurDelta& SenseurDelta::operator = (const SenseurDelta& s)
{ if (&s != this)    // protection contre x = x
  { SenseurGeometrique::operator = (s);
    observe_       = s.observe_;
  }

  return *this;

}

void SenseurDelta::respecterMesures ()
{ // mémorisation du besoin de fournir des mesures en radians

  if (conversionMesures ())
    reinitialisePrecision (radians (precision ())); // jusque là on était en degrés

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();

}

void SenseurDelta::convertirMesures ()
{ // mémorisation du besoin de fournir des mesures en degrés

  if (! conversionMesures ())
    reinitialisePrecision (degres (precision ())); // jusque là on était en radians

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();

}

void SenseurDelta::nouveauRepere (const RotDBL& nouveau)
{ // réorientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));
  observe_ = decalage (observe_);

  // appel de la fonction de la classe de base
  SenseurGeometrique::nouveauRepere (nouveau);

}

void SenseurDelta::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  if (conversionConsignes ())
    valeur = radians (valeur);  // la consigne était en degrés

  // la valeur mémorisée doit l'être dans l'unité de mesure
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (valeur));
  else
    Senseur::modeliseConsigne (etat, valeur);

  // la cible pointe toujours vers le pôle
  cible_    = VecDBL    (0.0, 0.0, 1.0);
  cibleVD1_ = VecDBLVD1 (cible_);

  // déclinaison fixée => distance du pôle fixée
  secteursConsigne_ = Secteurs (Cone (observe_, 0.5 * M_PI - valeur));

  // on fait la conversion en développement limité une fois pour toutes
  axeVD1_ = VecDBLVD1 (observe_);

  // retour normal à la fonction appelante
  verifieConsigne ();

}

double SenseurDelta::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{
  // projection de l'axe observé dans le repère inertiel
  RotDBL satInl = -(etat.attitude ());
  VecDBL obsInl (satInl (observe_));

  double m = asin (obsInl.z ());
  if (conversionMesures ())
    m = degres (m);      // la mesure doit être en degrés

  return m;

}
