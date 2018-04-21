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
//>       DeclDBL.h
//
//$Resume
//       fichier d'en-tête des template <double>
//
//$Description
//       Module de déclaration des types
//
//$Contenu
//>       typedef Vecteur3<double> VecDBL
//>       typedef Rotation<double> RotDBL
//>       typedef Polynome<double> PolDBL
//
//$Historique
//       $Log: DeclDBL.h,v $
//       Revision 1.7  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:08  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 10:16:38  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:25:36  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:39:39  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:22:11  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:14:24  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:57:01  luc
//       Initial revision
//
//$Version
//       $Id: DeclDBL.h,v 1.7 2000/08/09 14:36:43 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_DeclDBL_h
#define __cantor_DeclDBL_h

// ce fichier déclare les classes composites basées sur le type double

#include "cantor/Vecteur3.h"
#include "cantor/Rotation.h"
#include "cantor/Polynome.h"

// renommage des types composites
typedef Vecteur3<double> VecDBL;
typedef Rotation<double> RotDBL;
typedef Polynome<double> PolDBL;

#endif
