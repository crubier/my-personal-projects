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
//>       Senseur.cpp
//
//$Resume
//       fichier d'implantation de la classe Senseur
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Senseur       
//>         operator =()      
//>         respecterMesures()
//>         convertirMesures()
//>         nouveauRepere()   
//>         criteresControlabilite()   
//>         calage()          
//>         modeliseConsigne()
//
//$Historique
//       $Log: Senseur.cpp,v $
//       Revision 2.14  2003/02/04 16:37:05  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 2.13  2002/01/17 09:26:19  marmottes
//       correction de spécifications throw
//
//       Revision 2.12  2001/04/04 12:24:53  luc
//       ajout de la méthode criteresControlabilite
//
//       Revision 2.11  2000/10/02 13:16:29  luc
//       remplacement d'attributs entiers en booléens
//
//       Revision 2.10  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 2.9  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 2.8  1999/08/06 13:32:15  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 2.7  1998/06/24 20:02:34  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 2.6  1998/04/26 18:25:26  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.5  1997/09/23 09:29:01  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 2.4  1997/08/20 08:41:58  luc
//       ajout d'un en-tête de fichier
//       utilisation de ChaineSimple
//       déplacement de constructeurs dans le .h (simplifiés grâce à ChaineSimple)
//       implantation d'une version générique de la méthode modeliseConsigne
//
//       Revision 2.3  1997/04/27 19:36:34  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 2.2  1996/09/11 17:43:04  luc
//       ajout du nom du senseur dans l'instance
//       
//       Revision 2.1  1996/07/31 17:21:34  luc
//       ajout d'une possibilité de modifier le repère senseur à l'exécution
//       
//       Revision 1.1  1994/12/23 11:00:13  luc
//       Initial revision
//
//$Version
//       $Id: Senseur.cpp,v 2.14 2003/02/04 16:37:05 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/Senseur.h"

Senseur& Senseur::operator = (const Senseur& s)
{ if (&s != this)    // protection contre x = x
  { nom_                = s.nom_;
    repereBase_         = s.repereBase_;
    repere_             = s.repere_;
    axeCalage_          = s.axeCalage_;
    precision_          = s.precision_;
    convertirConsignes_ = s.convertirConsignes_;
    convertirMesures_   = s.convertirMesures_;
    valeurConsigne_     = s.valeurConsigne_;
  }

  return *this;

}


void Senseur::respecterMesures ()
{ // implantation de la méthode virtuelle dans la classe de base

  // ATTENTION : bien que cette méthode soit implantée, elle est virtuelle pure
  // les classes dérivées DOIVENT fournir également une implantation
  // qui peut éventuellement faire appel à cette implantation de base
  convertirMesures_ = false;

}


void Senseur::convertirMesures ()
{ // implantation de la méthode virtuelle dans la classe de base

  // ATTENTION : bien que cette méthode soit implantée, elle est virtuelle pure
  // les classes dérivées DOIVENT fournir également une implantation
  // qui peut éventuellement faire appel à cette implantation de base
  convertirMesures_ = true;

}


void Senseur::nouveauRepere (const RotDBL& nouveau)
{ // rotation du senseur

  // les coordonnées de axeCalage_ sont (et restent en permanence)
  // exprimées dans le repère de base : on ne les touche donc pas

  // modification du repère courant
  repere_ = nouveau;

}


void Senseur::criteresControlabilite (const Etat& etat,
                                      codeAstre *ptrInhibant,
                                      codeAstre *ptrEclipsant,
                                      double    *ptrEcartFrontiere,
                                      bool      *ptrAmplitudeSignificative)
  throw (MarmottesErreurs, CantorErreurs)
{ // calcul des critères de contrôlabilité

  // l'implémentation par défaut consiste à dire que tout est parfait
  *ptrInhibant               = nonSignificatif;
  *ptrEclipsant              = nonSignificatif;
  *ptrEcartFrontiere         = +1.0;
  *ptrAmplitudeSignificative = false;

}

void Senseur::calage (double c)
  throw (MarmottesErreurs)
{ // rotation du senseur autour d'un axe de calage prévu

  if (axeCalage_.norme () < 0.5)
    throw MarmottesErreurs (MarmottesErreurs::calage_interdit);

  // remise à zéro du repère
  nouveauRepere (repereBase_);

  // prise en compte du calage
  nouveauRepere (RotDBL (axeCalage_, -c) (repereBase_));

}

void Senseur::modeliseConsigne (const Etat&, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ // implantation de la méthode virtuelle dans la classe de base

  // ATTENTION : bien que cette méthode soit implantée, elle est virtuelle pure
  // les classes dérivées DOIVENT fournir également une implantation
  // qui peut éventuellement faire appel à cette implantation de base
  valeurConsigne_ = valeur;

}
