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
//>       SenseurElevation.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurElevation
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurElevation
//>         operator =()        
//>         modeliseConsigne()  
//>         mesure()            
//
//$Historique
//       $Log: SenseurElevation.cpp,v $
//       Revision 1.9  2003/02/04 16:39:37  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.8  2002/01/17 09:27:32  marmottes
//       correction de spécifications throw
//
//       Revision 1.7  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 1.6  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 1.5  1999/08/06 13:32:16  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.4  1998/09/14 11:51:04  luc
//       vérification de la consigne générée
//
//       Revision 1.3  1998/06/24 20:04:59  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.2  1998/02/04 07:54:27  luc
//       correction d'une erreur de conversion des valeurs
//       du senseur de base dans le cas d'une utilisation sans
//       conversion de mesures (c'est à dire quand tout est en degrés)
//
//       Revision 1.1  1997/09/23 09:31:30  luc
//       Initial revision
//
//$Version
//       $Id: SenseurElevation.cpp,v 1.9 2003/02/04 16:39:37 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurElevation.h"

SenseurElevation& SenseurElevation::operator = (const SenseurElevation& s)
{ if (&s != this)    // protection contre x = x
    SenseurVecteur::operator = (s);
  return *this;
}

void SenseurElevation::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  double complementaire;
  if (! conversionConsignes ())
    complementaire = 0.5 * M_PI - valeur;
  else
  { // la consigne était en degrés
    complementaire = 90.0 - valeur;
    valeur = radians (valeur);
  }

  SenseurVecteur::modeliseConsigne (etat, complementaire);

  // la valeur mémorisée doit l'être dans l'unité de mesure
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (valeur));
  else
    Senseur::modeliseConsigne (etat, valeur);

  verifieConsigne ();

}

double SenseurElevation::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{ 
  double m = SenseurVecteur::mesure (etat);
  if (! conversionMesures ())
    m = 0.5 * M_PI - m;
  else
    m = 90.0 - m; // la mesure était en degrés en sortie de la classe de base

  return m;

}
