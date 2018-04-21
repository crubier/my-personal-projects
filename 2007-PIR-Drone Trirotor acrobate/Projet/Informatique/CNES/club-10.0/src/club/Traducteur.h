/******************************************************************************
*$<AM-V1.0>
*
*$Type
*       DEF
*
*$Projet
*       Marmottes
*
*$Application
*       Club
*$Nom
*>       Traducteur.h
*$Resume
*       fichier d'en-tête des fonctions C d'interface de la classe Traducteur
*
*$Description
*       Module de déclaration des fonctions
*
*$Contenu
*>       int AjouterDomaine()                   
*          AjouterDomaine retourne un code non nul en cas de problème    
*          on peut l'ignorer                                             
*          (pour la traduction des erreurs c'est même recommandé)        
*>       const char* TraduitVersExterne()       
*>       const char* TraduitVersInterne()       
*>       const char* TraduitFormatCVersExterne()
*>       const char* VariableLangue()           
*>       const char* VariableCheminsTraduction()
*$Historique
*       $Log: Traducteur.h,v $
*       Revision 3.9  2000/08/30 14:11:00  club
*       suppression de l'include Adressage.h
*
*       Revision 3.8  1999/06/01 14:55:00  club
*       rectification des commentaires de style C++ vers style C pour utilisation
*       multi-langages
*
*       Revision 3.7  1998/11/17 11:41:27  club
*       élimination de l'inclusion de ctype.h
*       (inclus par l'intermédiaire de ClubErreurs.h et ChaineSimple.h)
*
*       Revision 3.6  1998/08/11 07:40:25  club
*       ajout des fonctions VariableLangue et VariableCheminsTraduction
*
*       Revision 3.5  1998/06/21 16:09:30  luc
*       modification du format de l'en-tête
*
*       Revision 3.4  1997/08/21 16:38:58  luc
*       ajout d'un en-tête de fichier
*
*       Revision 3.3  1997/04/03 12:51:01  luc
*       inversion des codes de retour, 0 signifie désormais : pas d'erreur
*       
*       Revision 3.2  1997/03/25 15:00:58  luc
*       changement des règles de nommage
*       
*       Revision 3.1  1997/03/19 14:51:21  luc
*       utilisation de la classe ChaineSimple
*       renommage de la bibliothèque util_c++ en club
*       passage de SCCS à RCS
*       
*       Revision 2.1  1996/07/15 17:31:35  luc
*       élimination de la dépendance au tools.h++ (Rogue Wave)
*       
*       Revision 1.7  1995/10/09 16:05:26  mercator
*       separation des lexemes C++ dans un autre fichier pour eviter des
*       problemes d'analyse lexicale pour le preprocesseur C
*       
*       Revision 1.6  1995/07/12 14:55:23  mercator
*       suppression d'un argument inutilise dans une methode privee
*       
*       Revision 1.5  1995/01/05 13:01:00  mercator
*       ajout de fonctions d'interface avec le fortran
*       
*       Revision 1.4  1995/01/03 07:58:45  mercator
*       remplacement des variables globales de traduction
*       par des fonctions globales
*       
*       Revision 1.3  1994/11/09 15:00:51  mercator
*       elimination des directives #pragma
*       
*       Revision 1.2  1994/09/28 16:28:43  mercator
*       prise en compte du changement de nom:
*       FichierTexte --> TamponTexte
*       
*       Revision 1.1  1994/07/27 11:55:40  luc
*       Initial revision
*
*
*$Version
*       $Id: Traducteur.h,v 3.9 2000/08/30 14:11:00 club Exp $
*
*$Auteur
*       L. Maisonobe CNES
*      
*$<>
******************************************************************************/



#ifndef __club_Traducteur_h
#define __club_Traducteur_h

#ifdef __cplusplus

#include "club/TamponTexte.h"
#include "club/ClubErreurs.h"

#endif



#ifdef __cplusplus
extern "C" {
#endif

/* fonctions C d'interface avec le système de traduction général */
int         AjouterDomaine            (const char* domaine);
const char* TraduitVersExterne        (const char* interne);
const char* TraduitVersInterne        (const char* externe);
const char* TraduitFormatCVersExterne (const char* format);
const char* VariableLangue            ();
const char* VariableCheminsTraduction ();

#ifdef __cplusplus
           }
#endif

#ifdef __cplusplus
/* inclusion de la partie de l'en-tête contenant des lexèmes C++ */
/* pouvant poser des problèmes à un préprocesseur C ANSI         */
#include "club/TraducteurCC.h"
#endif

#endif
