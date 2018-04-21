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
//       Cantor
//
//$Nom
//>       CantorVersion.h
//
//$Resume
//       fichier d'en-tête de la fonction CantorVersion
//
//$Description
//       Module de déclaration de la fonction
//
//$Contenu
//>       const char *cantorVersion()
//
//$Historique
//       $Log: CantorVersion.h,v $
//       Revision 1.6  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.5.4.1  2000/03/30 15:36:08  cantor
//       ajout du copyright CNES
//
//       Revision 1.5  1998/06/24 10:16:19  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.4  1997/07/06 10:25:07  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.3  1997/03/26 06:39:38  luc
//       changement des conventions de nommage
//       
//       Revision 1.2  1997/03/24 09:22:09  luc
//       passage de SCCS à RCS
//       
//       Revision 1.1  1996/07/16 09:43:04  luc
//       Initial revision
//
//$Version
//       $Id: CantorVersion.h,v 1.6 2000/08/09 14:36:43 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Version_h
#define __cantor_Version_h

#ifdef __cplusplus
extern "C" {
#endif

const char *cantorVersion ();

#ifdef __cplusplus
}
#endif

#endif
