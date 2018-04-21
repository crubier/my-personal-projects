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
//>       InterfaceC.h
//
//$Resume
//       fichier d'en-tête des fonction d'interface avec le C
//
//$Description
//       Module de déclaration des fonctions d'interface
//
//$Contenu
//>       int RotAxeAngle()        
//>       int RotU1U2V1V2()        
//>       int RotU1V1()            
//>       int RotMatrice()         
//>       int RotTroisAngles()
//>       void RotInverse()        
//>       void RotComposee()       
//>       void AxeRot()            
//>       void AngleRot()          
//>       void AxeAngleRot()       
//>       void MatriceRot()        
//>       int TroisAnglesRot()
//>       void AppliqueRot()       
//>       void AppliqueRotInverse()
//
//$Historique
//       $Log: InterfaceC.h,v $
//       Revision 1.10  2001/06/05 15:36:04  cantor
//       ajout des fonctions RotTroisAngles et TroisAnglesRot
//       ajout de lgMaxMessage dans la signature des fonctions
//
//       Revision 1.9  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.8.4.1  2000/03/30 15:36:09  cantor
//       ajout du copyright CNES
//
//       Revision 1.8  1998/07/29 11:47:51  cantor
//       élimination de string.h
//
//       Revision 1.7  1998/06/24 10:22:12  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:26:44  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:39:43  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:22:14  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 10:33:38  luc
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.2  1995/07/11 14:40:11  mercator
//       modification de la notation des vecteurs (et des fonctions)
//       pour la rendre compatible avec l'interface C++ et la documentation mathematique
//       
//       Revision 1.1  1995/01/19 06:32:58  mercator
//       Initial revision
//
//$Version
//       $Id: InterfaceC.h,v 1.10 2001/06/05 15:36:04 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_InterfaceC_h
#define __cantor_InterfaceC_h

#ifdef __cplusplus

#include "cantor/DeclDBL.h"
#include "cantor/CantorErreurs.h"

extern "C" {
#endif

/* identificateur d'ordre de rotations élémentaires */
enum  CantorAxesRotation { CtrXYZ, CtrXZY, CtrYXZ, CtrYZX, CtrZXY, CtrZYX,
                           CtrXYX, CtrXZX, CtrYXY, CtrYZY, CtrZXZ, CtrZYZ };

/* fabrication d'une rotation */

int  RotAxeAngle (double q [4],
                  double axe [3], double angle,
                  char* message, int lgMaxMessage);

/* notation: R (u1) = v1, R (u2) = v2 */
int  RotU1U2V1V2 (double q [4],
                  double u1 [3], double u2 [3], double v1 [3], double v2 [3],
                  char* message, int lgMaxMessage);

int  RotU1V1     (double q [4],
                  double u1 [3], double v1 [3],
                  char* message, int lgMaxMessage);

int  RotMatrice  (double q [4],
                  double m [3][3], double seuil,
                  char* message, int lgMaxMessage);

int  RotTroisAngles (double q [4],
                     CantorAxesRotation ordre,
                     double alpha1, double alpha2, double alpha3,
                     char* message, int lgMaxMessage);

void RotInverse  (double q [4], double qInitiale [4]);
void RotComposee (double q [4], double q1 [4], double q2 [4]);

/* extraction des éléments internes */
void AxeRot      (double q [4], double  axe [3]);
void AngleRot    (double q [4], double* pAngle);
void AxeAngleRot (double q [4], double axe [3], double* pAngle);
void MatriceRot  (double q [4], double m [3][3]);
int  TroisAnglesRot (double q [4], CantorAxesRotation ordre,
                     double *pAlpha1, double *pAlpha2, double *pAlpha3,
                     char* message, int lgMaxMessage);

/* application d'une rotation */
void AppliqueRot        (double q [4], double u      [3], double uPrime [3]);
void AppliqueRotInverse (double q [4], double uPrime [3], double u      [3]);

#ifdef __cplusplus
           }
#endif

#endif
