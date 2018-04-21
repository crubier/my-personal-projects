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
//>       SenseurCartesien.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurCartesien
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurCartesien
//>         operator =()        
//>         respecterMesures()  
//>         convertirMesures()  
//>         modeliseConsigne()  
//>         mesure()            
//
//$Historique
//       $Log: SenseurCartesien.cpp,v $
//       Revision 1.8  2003/02/04 16:38:17  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.7  2002/01/17 09:26:19  marmottes
//       correction de spécifications throw
//
//       Revision 1.6  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 1.5  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 1.4  1999/08/06 13:32:15  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.3  1998/09/14 11:50:16  luc
//       vérification de la consigne générée
//
//       Revision 1.2  1998/06/24 20:03:31  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.1  1997/09/23 09:29:22  luc
//       Initial revision
//
//$Version
//       $Id: SenseurCartesien.cpp,v 1.8 2003/02/04 16:38:17 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurCartesien.h"

SenseurCartesien& SenseurCartesien::operator = (const SenseurCartesien& s)
{ if (&s != this)    // protection contre x = x
    SenseurVecteur::operator = (s);
  return *this;
}

void SenseurCartesien::respecterMesures ()
{ // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();
}

void SenseurCartesien::convertirMesures ()
{ // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();
}

void SenseurCartesien::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  double angle;
  if (! conversionConsignes ())
    angle = acos (valeur);
  else
    angle = degres (acos (valeur));  // la consigne doit être en degrés
                                     // en entrée de la classe de base

  SenseurVecteur::modeliseConsigne (etat, angle);

  // la valeur mémorisée n'a pas d'unité (scalaire entre -1 et 1)
  Senseur::modeliseConsigne (etat, valeur);

  verifieConsigne ();

}

double SenseurCartesien::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{ 
  double m = SenseurVecteur::mesure (etat);
  if (! conversionMesures ())
    m = cos (m);
  else
    m = cos (radians (m));      // la mesure était en degrés
                                // en sortie de la classe de base

  return m;

}
