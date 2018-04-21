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
//>       DeclDBLVD2.h
//
//$Resume
//       fichier d'en-tête des templates <double> et <ValeurDerivee2>
//
//$Description
//       Module de regroupement des inclusions
//
//$Contenu
//
//$Historique
//       $Log: DeclDBLVD2.h,v $
//       Revision 1.8  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.7.4.1  2000/03/30 15:36:09  cantor
//       ajout du copyright CNES
//
//       Revision 1.7  1998/06/24 10:17:02  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:26:00  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:39:40  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:22:12  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 11:54:45  luc
//       suppression de l'inclusion du fichier des opérateurs de rotation
//       (il n'y a plus d'opérateur de rotation après la suppression du ==)
//       
//       Revision 1.2  1994/11/26 15:14:37  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:57:03  luc
//       Initial revision
//
//$Version
//       $Id: DeclDBLVD2.h,v 1.8 2000/08/09 14:36:43 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_DeclDBLVD2_h
#define __cantor_DeclDBLVD2_h

// ce fichier regroupe les conversions et combinaisons d'opérateurs
// entre scalaires et classes composites basées sur les types suivants:
//          double
//          ValeurDerivee2

// déclarations des types
#include "cantor/DeclDBL.h"
#include "cantor/DeclVD2.h"


// déclaration et définition de toutes les opérations entre
// scalaires, vecteurs, rotations et polynômes des deux types de base.

// remarque: les fichiers situés dans le répertoire "conversions"
// sont écrits avec le principe théorique suivant:
// si le type B est une "restriction" du type A (par exemple A est une
// dérivée et B est un réel simple), alors une opération entre un A et un B
// donnera un A, le B ayant été "complété" par des 0.
// (ceci n'est bien sur pas vrai pour une opération du type B += A, dans
//  ce cas on restreint le type A pour réaliser l'opération).
// sous ces mêmes hypothèses, une comparaison entre un A et un B (<, <=, ...)
// sera réalisée entre une restriction du A et le B original.

// Dans la pratique, le calcul n'est pas fait en créant un A avec des 0,
// mais par des formules adaptées à chaque cas, pour des raisons d'efficacité.

// Ce principe est l'extension naturelle des formules donnant la dérivée
// d'une opération arithmétique entre une dérivée et un réel, considéré
// comme une fonction constante.

#include "cantor/conversions/ConvDBLVD2.h"
#include "cantor/conversions/CombScalDBLVD2.h"
#include "cantor/conversions/CombVecDBLVD2.h"
#include "cantor/conversions/CombPolDBLVD2.h"

#endif
