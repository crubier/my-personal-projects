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
//>       InterfaceF.h
//
//$Resume
//       fichier d'en-tête des fonctions d'interface avec le fortran
//
//$Description
//       Module de déclaration des fonctions d'interface
//
//$Contenu
//>       int rotaxeangle_()        
//>       int rotu1u2v1v2_()        
//>       int rotu1v1_()            
//>       int rotmatrice_()         
//>       int rottroisangles_()         
//>       void rotinverse_()        
//>       void rotcomposee_()       
//>       void axerot_()            
//>       void anglerot_()          
//>       void axeanglerot_()       
//>       void matricerot_()        
//>       int troisanglesrot_()
//>       void appliquerot_()       
//>       void appliquerotinverse_()
//
//$Historique
//       $Log: InterfaceF.h,v $
//       Revision 1.10  2001/06/05 15:32:51  cantor
//       ajout des fonctions rottroisangles_ et troisanglesrot_
//
//       Revision 1.9  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.8.4.1  2000/03/30 15:36:10  cantor
//       ajout du copyright CNES
//
//       Revision 1.8  1998/07/29 11:48:45  cantor
//       élimination de string.h
//
//       Revision 1.7  1998/06/24 10:22:38  luc
//       modification du format de l'en-tête
//       élimination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:28:52  luc
//       ajout d'un en-tête de fichier
//       correction des signatures de longueurs de chaînes de caractères
//       (elles ne sont pas passées par référence)
//
//       Revision 1.5  1997/03/26 06:39:44  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:22:15  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 10:33:58  luc
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.2  1995/07/11 14:40:13  mercator
//       modification de la notation des vecteurs (et des fonctions)
//       pour la rendre compatible avec l'interface C++ et la documentation mathematique
//       
//       Revision 1.1  1995/01/19 07:08:32  mercator
//       Initial revision
//
//$Version
//       $Id: InterfaceF.h,v 1.10 2001/06/05 15:32:51 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_InterfaceF_h
#define __cantor_InterfaceF_h

#ifdef __cplusplus

#include "cantor/DeclDBL.h"
#include "cantor/CantorErreurs.h"

extern "C" {
#endif

/* fabrication d'une rotation */
int  rotaxeangle_    (double q [4],
                      double axe [3], double& angle,
                      char* message, long int lDeclMessage);

/* notation: R (u1) = v1, R (u2) = v2 */
int  rotu1u2v1v2_    (double q [4],
                      double u1 [3], double u2 [3],
                      double v1 [3], double v2 [3],
                      char* message, long int lDeclMessage);
int  rotu1v1_        (double q [4],
                      double u1 [3], double v1 [3],
                      char* message, long int lDeclMessage);

int  rotmatrice_     (double q [4],
                      double m [3][3], double& seuil,
                      char* message, long int lDeclMessage);

int  rottroisangles_ (double q [4],
                      int& ordre,
                      double& alpha1, double& alpha2, double& alpha3,
                      char* message, long int lDeclMessage);

void rotinverse_     (double q [4], double qInitiale [4]);
void rotcomposee_    (double q [4], double q1 [4], double q2 [4]);

/* extraction des éléments internes */
void axerot_         (double q [4], double  axe [3]);
void anglerot_       (double q [4], double& angle);
void axeanglerot_    (double q [4], double axe [3], double& angle);
void matricerot_     (double q [4], double m [3][3]);
int  troisanglesrot_ (double q [4], int& ordre,
                      double& alpha1, double& alpha2, double& alpha3,
                      char* message, long int lDeclMessage);

/* application d'une rotation */
void appliquerot_        (double q [4], double u      [3], double uPrime [3]);
void appliquerotinverse_ (double q [4], double uPrime [3], double u      [3]);

#ifdef __cplusplus
           }
#endif

#endif
