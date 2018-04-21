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
//>       Resolution1.h
//
//$Resume
//       fichier d'en-tête des fonctions de résolutions à l'ordre 1
//
//$Description
//       Module de déclaration des fonctions
//
//$Contenu
//>       enum CodeConvergence1      
//>       Variation1 NewtonSecante() 
//>       double NewtonSecante()     
//>       Variation1 ExtremumNewSec()
//>       double ExtremumNewSec()    
//
//$Historique
//       $Log: Resolution1.h,v $
//       Revision 1.7  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:10  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 15:16:43  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:31:04  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:39:47  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:22:16  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:15:21  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:57:11  luc
//       Initial revision
//
//$Version
//       $Id: Resolution1.h,v 1.7 2000/08/09 14:36:44 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Resolution1_h
#define __cantor_Resolution1_h

#include "cantor/ValeurDerivee1.h"
#include "cantor/Variation1.h"

typedef ValeurDerivee1 (*TypeFoncVD1) (double t, void* donnee);

enum CodeConvergence1 { CONV1_AUCUNE, CONV1_INF, CONV1_SUP };
typedef CodeConvergence1 (*TypeFoncConv1) (const Variation1& inf,
                                           const Variation1& sup,
                                           void* donnee);

Variation1 NewtonSecante  (TypeFoncVD1   f,           void* arg,
                           TypeFoncConv1 convergence, void* arg_conv,
                           const Variation1& a, const Variation1& b);

double     NewtonSecante  (TypeFoncVD1   f,           void* arg,
                           TypeFoncConv1 convergence, void* arg_conv,
                           double        a,           double b);

Variation1 ExtremumNewSec (TypeFoncVD1   f,           void* arg,
                           TypeFoncConv1 convergence, void* arg_conv,
                           const Variation1& a, const Variation1& b);

double     ExtremumNewSec (TypeFoncVD1   f,           void*  arg,
                           TypeFoncConv1 convergence, void*  arg_conv,
                           double        a,           double b);

#endif
