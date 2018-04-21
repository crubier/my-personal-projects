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
//>       Util.h
//
//$Resume
//       fichier d'en-tête des utilitaires de Cantor
//
//$Description
//       Module de déclaration des fonctions utilitaires inline
//
//$Contenu
//>       inline double min()        
//>       inline int min()           
//>       inline double max()        
//>       inline int max()           
//>       inline double radians()    
//>       inline double degres()     
//>       inline double recaleAngle()
//
//$Historique
//       $Log: Util.h,v $
//       Revision 1.12  2000/10/25 12:30:56  cantor
//       modification du chemin vers le fichier CantorConfig.h dans l'include
//
//       Revision 1.11  2000/10/24 16:21:38  cantor
//       utilisation du namespace std et ajout de l'include CantorConfig.h
//
//       Revision 1.10  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.9.2.1  2000/03/30 15:36:11  cantor
//       ajout du copyright CNES
//
//       Revision 1.9  1999/08/05 09:56:52  cantor
//       modification résultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.8.2.1  1999/04/26 09:36:07  cantor
//       élimination de la fonction en ligne abs
//
//       Revision 1.8  1998/10/05 13:35:54  cantor
//       ajout des constantes cantorEpsilon et cantorEnorme
//
//       Revision 1.7  1998/06/24 10:21:10  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.6  1998/01/22 10:44:21  luc
//       élimination de directives de compilation conditionnelle
//
//       Revision 1.5  1997/09/10 06:56:45  luc
//       correction des caractères RCS
//
//       Revision 1.4  1997/07/06 10:36:19  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.3  1997/04/26 21:03:08  luc
//       ajout de la fonction recaleAngle
//       
//       Revision 1.2  1997/03/26 06:39:50  luc
//       changement des conventions de nommage
//       
//       Revision 1.1  1997/03/24 08:36:10  luc
//       Initial revision
//
//$Version
//       $Id: Util.h,v 1.12 2000/10/25 12:30:56 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Util_h
#define __cantor_Util_h

#include <cantor/CantorConfig.h>

#if CANTOR_HAVE_NAMESPACES
using namespace std;
#endif

#include "cantor/MathPi.h"

const double  cantorEpsilon = 1.0e-15;
const double  cantorEnorme  = 1.0e300;

inline double min     (double a, double b) { return (a < b) ? a : b; }
inline int    min     (int    a, int    b) { return (a < b) ? a : b; }

inline double max     (double a, double b) { return (a > b) ? a : b; }
inline int    max     (int    a, int    b) { return (a > b) ? a : b; }

inline double radians (double a)           { return a * M_PI / 180.0; }
inline double degres  (double a)           { return a * 180.0 / M_PI; }

// recale un angle entre ref - PI et ref + PI
inline double recaleAngle (double a, double ref)
{ return a - (M_PI + M_PI) * floor ((a + M_PI - ref) / (M_PI + M_PI)); }

#endif
