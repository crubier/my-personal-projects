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
//>       MarmottesVersion.h
//
//$Resume
//       fichier d'en-tête de la fonction marmottesVersion
//
//$Description
//       Module de déclaration de la fonction
//
//$Contenu
//>       const char *marmottesVersion()
//
//$Historique
//       $Log: MarmottesVersion.h,v $
//       Revision 1.6  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 1.5  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.4  1998/06/25 06:02:48  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.3  1997/08/20 09:35:09  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.2  1997/04/27 19:33:04  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 1.1  1996/07/31 18:01:32  luc
//       Initial revision
//
//$Version
//       $Id: MarmottesVersion.h,v 1.6 2000/03/30 17:01:22 luc Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_MarmottesVersion_h
#define __marmottes_MarmottesVersion_h

#ifdef __cplusplus
extern "C" {
#endif

const char *marmottesVersion ();

#ifdef __cplusplus
}
#endif

#endif
