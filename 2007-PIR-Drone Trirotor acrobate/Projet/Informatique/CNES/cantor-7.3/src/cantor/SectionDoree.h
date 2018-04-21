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
//>       SectionDoree.h
//
//$Resume
//       fichier d'en-tête de la fonction de l'algorithme de section dorée
//
//$Description
//       Module de déclaration de la fonction
//
//$Contenu
//>       void SectionDoree()            
//
//$Historique
//       $Log: SectionDoree.h,v $
//       Revision 1.3  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.2.4.1  2000/03/30 15:36:11  cantor
//       ajout du copyright CNES
//
//       Revision 1.2  1998/06/24 10:21:31  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.1  1998/05/13 07:40:48  luc
//       Initial revision
//
//$Version
//       $Id: SectionDoree.h,v 1.3 2000/08/09 14:36:45 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_SectionDoree_h
#define __cantor_SectionDoree_h

void SectionDoree (double fonc (double x, void *), void *arg,
                   double eps, double xa, double xb,
                   double *ptrXMin = 0, double *ptrFMin = 0);

#endif
