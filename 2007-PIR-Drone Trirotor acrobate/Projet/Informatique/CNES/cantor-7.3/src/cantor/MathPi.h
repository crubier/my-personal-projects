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
//>       MathPi.h
//
//$Resume
//       fichier d'en-tête d'inclusion protégée de <math.h>
//
//$Description
//       Module d'inclusion protégée de <math.h>
//
//$Contenu
//
//$Historique
//       $Log: MathPi.h,v $
//       Revision 1.8  2001/02/16 16:12:32  cantor
//       utilisation de l'espace lexical std
//
//       Revision 1.7  2000/10/24 16:20:20  cantor
//       modification de l'include math.h en cmath (pour permettre la compilation
//       avec le compilateur Sun Workshop 5.0)
//
//       Revision 1.6  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.5.4.1  2000/03/30 15:36:10  cantor
//       ajout du copyright CNES
//
//       Revision 1.5  1998/06/24 10:20:54  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.4  1997/09/10 06:56:52  luc
//       correction des caractères RCS
//
//       Revision 1.3  1997/07/06 10:30:10  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.2  1997/03/26 06:39:45  luc
//       changement des conventions de nommage
//       
//       Revision 1.1  1997/03/24 08:35:44  luc
//       Initial revision
//
//$Version
//       $Id: MathPi.h,v 1.8 2001/02/16 16:12:32 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_MathPi_h
#define __cantor_MathPi_h

#include <cmath>
#include "cantor/CantorConfig.h"
#ifdef CANTOR_HAVE_NAMESPACES
using namespace std;
#endif

#ifndef M_PI
// la constante symbolique M_PI n'a pas été définie par <math.h>
// probablement en raison d'options de compilations (-ansi, ...)
// on force une valeur
#define M_PI 3.14159265358979323846
#endif

#endif
