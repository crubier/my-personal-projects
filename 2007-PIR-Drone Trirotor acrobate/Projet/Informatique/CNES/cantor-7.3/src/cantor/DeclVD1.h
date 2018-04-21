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
//>       DeclVD1.h
//
//$Resume
//       fichier d'en-tête des template <ValeurDerivee1>
//
//$Description
//       Module de déclaration des types
//
//$Contenu
//>       typedef Vecteur3<ValeurDerivee1> VecVD1
//>       typedef Rotation<ValeurDerivee1> RotVD1
//>       typedef Polynome<ValeurDerivee1> PolVD1
//
//$Historique
//       $Log: DeclVD1.h,v $
//       Revision 1.7  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:09  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 10:17:13  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:26:06  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:39:41  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:22:13  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:14:44  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:57:04  luc
//       Initial revision
//
//$Version
//       $Id: DeclVD1.h,v 1.7 2000/08/09 14:36:44 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_DeclVD1_h
#define __cantor_DeclVD1_h

// ce fichier déclare les classes composites basées sur le type ValeurDerivee1

#include "cantor/ValeurDerivee1.h"

#include "cantor/Vecteur3.h"
#include "cantor/Rotation.h"
#include "cantor/Polynome.h"

// renommage des types composites
typedef Vecteur3<ValeurDerivee1> VecVD1;
typedef Rotation<ValeurDerivee1> RotVD1;
typedef Polynome<ValeurDerivee1> PolVD1;

#endif
