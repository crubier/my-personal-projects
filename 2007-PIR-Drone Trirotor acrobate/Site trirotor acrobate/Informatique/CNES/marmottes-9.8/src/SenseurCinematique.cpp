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
//>       SenseurCinematique.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurCinematique
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurCinematique
//>         operator =()          
//>         respecterMesures()    
//>         convertirMesures()    
//>         nouveauRepere()       
//>         modeliseConsigne()    
//>         mesure()              
//>         foncEcart()
//>         initialiseDerive()        
//
//$Historique
//       $Log: SenseurCinematique.cpp,v $
//       Revision 3.14  2003/10/08 09:39:41  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 3.13  2003/02/04 16:38:29  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 3.12  2002/02/27 14:09:09  marmottes
//       suppression de la description de la révision insérée manuellement
//       et mise à jour du copyright CNES
//
//       Revision 3.11  2002/02/22 09:34:15  marmottes
//       Ajout de la méthode initialiseDerive (DM0002); modification de methodes pour prise en compte de la dérive
//
//       Revision 3.10  2002/01/17 09:27:32  marmottes
//       correction de spécifications throw
//
//       Revision 3.9  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 3.8  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 3.7  1999/08/06 13:32:15  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 3.6  1998/06/24 20:03:56  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 3.5  1998/04/26 18:25:31  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.4  1997/09/23 13:46:10  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 3.3  1997/08/20 09:21:10  luc
//       ajout d'un en-tête de fichier
//       utilisation du valeurConsigne () commun à tous les senseurs à la place
//       du omega () spécifique aux senseurs cinématiques qui disparaît
//
//       Revision 3.2  1997/04/27 19:36:39  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 3.1  1997/01/28 12:47:04  luc
//       prise en compte des changements de la classe Etat (passée en version 3.1)
//       
//       Revision 2.1  1996/07/31 17:22:05  luc
//       ajout d'une possibilité de modifier le repère senseur à l'exécution
//       
//       Revision 1.2  1995/01/27 16:59:48  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1994/12/23 11:00:14  luc
//       Initial revision
//
//$Version
//       $Id: SenseurCinematique.cpp,v 3.14 2003/10/08 09:39:41 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurCinematique.h"

SenseurCinematique& SenseurCinematique::operator =
                                                 (const SenseurCinematique& s)
{ if (&s != this)    // protection contre x = x
  { Senseur::operator = (s);
    sensible_    = s.sensible_;
    sensibleVD1_ = s.sensibleVD1_;
  }

  return *this;

}

void SenseurCinematique::respecterMesures ()
{ // mémorisation du besoin de fournir des mesures en radians

  if (conversionMesures ())
    reinitialisePrecision (radians (precision ())); // jusque là on était en degrés

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();

}

void SenseurCinematique::convertirMesures ()
{ // mémorisation du besoin de fournir des mesures en degrés

  if (! conversionMesures ())
    reinitialisePrecision (degres (precision ())); // jusque là on était en radians

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();

}

void SenseurCinematique::nouveauRepere (const RotDBL& nouveau)
{ // réorientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));
  sensible_    = decalage (sensible_);
  sensibleVD1_ = VecDBLVD1 (sensible_);

  // appel de la fonction de la classe de base
  Senseur::nouveauRepere (nouveau);

}

void SenseurCinematique::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  omega_ = (conversionConsignes () ? radians (valeur): valeur)
         - derive_ ;

  // la valeur mémorisée par la classe de base
  // doit l'être dans l'unité de mesure
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (omega_));
  else
    Senseur::modeliseConsigne (etat, omega_);

}

double SenseurCinematique::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{ 
  // L'offset du senseur est ajouté avant toute conversion
  // Ceci permet de n'avoir qu'une seule valeur en mémoire,
  // stockée en unité S.I..
  double m = (etat.spin () | sensible_) + derive_ ;
  if (conversionMesures ())
    m = degres (m);      // la mesure doit être en degrés par seconde

  return m;

}

ValeurDerivee1 SenseurCinematique::foncEcart (const Etat& etatPrecedent,
                                              const Etat& etatResolution,
                                              const RotVD1& attitude,
                                              const VecVD1& spin
                                             )
{ return (spin | sensibleVD1_) - omega_; }

void SenseurCinematique::initialiseDerive (double derive)
  throw (MarmottesErreurs)
{ 
  // La valeur mémorisée par la classe de base
  // l'est en unité S.I. quelle que soit l'unité
  // de mesure de l'utilisateur.
  derive_ = conversionMesures() ? radians(derive) : derive ;
}
