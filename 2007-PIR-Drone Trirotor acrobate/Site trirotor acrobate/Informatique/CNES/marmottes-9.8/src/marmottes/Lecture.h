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
//>       Lecture.h
//
//$Resume
//       fichier d'en-tête des fonctions de lecture de senseurs
//
//$Description
//       Module de déclaration des fonctions
//
//$Contenu
//>       Senseur* LireSenseur()  
//>       Parcelle* LireParcelle()
//
//$Historique
//       $Log: Lecture.h,v $
//       Revision 1.12  2001/07/17 15:26:10  luc
//       lancement d'un CantorErreurs par LireParcelle
//
//       Revision 1.11  2001/06/06 07:58:09  luc
//       remontée des exceptions Cantor
//
//       Revision 1.10  2000/09/13 09:32:18  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.9  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 1.8  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.7  1999/08/25 09:41:03  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 1.6  1999/08/06 13:32:17  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.5  1998/06/25 06:00:42  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.4  1997/08/20 09:32:08  luc
//       ajout d'un en-tête de fichier
//       utilisation de ChaineSimple à la place de char *
//
//       Revision 1.3  1997/04/27 19:32:33  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 1.2  1996/07/31 18:11:15  luc
//       prise en compte du renommage de erreurs.h en marmottes_erreurs.h
//       
//       Revision 1.1  1994/12/23 11:00:03  luc
//       Initial revision
//
//$Version
//       $Id: Lecture.h,v 1.12 2001/07/17 15:26:10 luc Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_Lecture_h
#define __marmottes_Lecture_h

#include <string>

#include "club/ClubErreurs.h"
#include "club/FichierStructure.h"

#include "cantor/CantorErreurs.h"

#include "marmottes/MarmottesErreurs.h"
#include "marmottes/Senseur.h"
#include "marmottes/Parcelle.h"

// fonctions d'analyse du fichier des senseurs
Senseur*  LireSenseur  (FichierStructure* f, const string& nom)
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

Parcelle* LireParcelle (FichierStructure* blocPere, const string& nom)
    throw (CantorErreurs, MarmottesErreurs);

#endif
