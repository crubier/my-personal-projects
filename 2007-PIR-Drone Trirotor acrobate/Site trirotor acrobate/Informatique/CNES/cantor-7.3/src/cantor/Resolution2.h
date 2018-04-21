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
//>       Resolution2.h
//
//$Resume
//       fichier d'en-tête des fonctions de résolutions à l'ordre 2
//
//$Description
//       Module de déclaration des fonctions
//
//$Contenu
//>       enum CodeConvergence2      
//>       Variation2 NewtonSecante() 
//>       double NewtonSecante()     
//>       Variation2 ExtremumNewSec()
//>       double ExtremumNewSec()    
//
//$Historique
//       $Log: Resolution2.h,v $
//       Revision 1.7  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:10  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 15:16:54  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:31:26  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.4  1997/03/26 06:39:48  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:22:17  luc
//       passage de SCCS à RCS
//       
//       Revision 1.2  1994/11/26 15:15:34  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:57:13  luc
//       Initial revision
//
//$Version
//       $Id: Resolution2.h,v 1.7 2000/08/09 14:36:44 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Resolution2_h
#define __cantor_Resolution2_h

#include "cantor/ValeurDerivee2.h"
#include "cantor/Variation2.h"

typedef ValeurDerivee2 (*TypeFoncVD2) (double t, void* donnee);

enum CodeConvergence2 { CONV2_AUCUNE, CONV2_INF, CONV2_SUP };
typedef CodeConvergence2 (*TypeFoncConv2) (const Variation2& inf,
                                           const Variation2& sup,
                                           void* donnee);

Variation2 NewtonSecante  (TypeFoncVD2   f,           void* arg,
                           TypeFoncConv2 convergence, void* arg_conv,
                           const Variation2& a, const Variation2& b);

double     NewtonSecante  (TypeFoncVD2   f,           void*  arg,
                           TypeFoncConv2 convergence, void*  arg_conv,
                           double        a,           double b);

Variation2 ExtremumNewSec (TypeFoncVD2   f,           void* arg,
                           TypeFoncConv2 convergence, void* arg_conv,
                           const Variation2& a, const Variation2& b);

double     ExtremumNewSec (TypeFoncVD2   f,           void*  arg,
                           TypeFoncConv2 convergence, void*  arg_conv,
                           double        a,           double b);

#endif
