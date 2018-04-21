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
//>       TableInstances.h
//
//$Resume
//       fichier d'en-tête des fonctions d'accès à la table d'instance
//
//$Description
//       Module de déclaration des fonctions d'accès à la table d'instance,
//       cette table permet aux langages fonctionnels C et fortran
//       d'accéder à des instances de simulateurs Marmottes par un simple
//       numéro qui leur est fourni par des fonctions de création explicites
//
//$Contenu
//>       Marmottes *InstanceInitialisee()
//>       void InstanceNonInitialisee()
//
//$Historique
//       $Log: TableInstances.h,v $
//       Revision 1.5  2000/03/30 17:01:25  luc
//       ajout du copyright CNES
//
//       Revision 1.4  1999/11/02 07:19:23  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.3  1999/04/23 11:42:08  luc
//       élimination de CopieMessageC
//       utilisation d'exceptions simplifiant InstanceInitialisee
//
//       Revision 1.2  1998/06/25 06:16:11  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.1  1998/05/14 12:04:11  luc
//       Initial revision
//
//$Version
//       $Id: TableInstances.h,v 1.5 2000/03/30 17:01:25 luc Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_TableInstances_h
#define __marmottes_TableInstances_h

#include "marmottes/Marmottes.h"
#include "marmottes/MarmottesErreurs.h"

// récupération d'une instance dans une table par son numéro
Marmottes *InstanceInitialisee (int ident) throw (MarmottesErreurs);
      
void InstanceNonInitialisee (int        *ptrIdent,
                             Marmottes **adrPtrInstance);

#endif
