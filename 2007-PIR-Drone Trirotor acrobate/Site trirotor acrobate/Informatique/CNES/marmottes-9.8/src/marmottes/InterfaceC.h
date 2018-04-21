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
*       Marmottes
*
*$Nom
*>       InterfaceC.h
*$Resume
*       fichier d'en-tête des fonctions d'interface C
*
*$Description
*       Module de déclaration des fonctions d'interface C
*
*$Contenu
*>       typedef int IdentMarmottes           
*>       enum MarmottesAstre                  
*>       typedef double TypeFuncTsidC()       
*>       typedef void TypeFuncPosC()          
*>       int MarmottesActiveTrace()           
*>       int MarmottesDesactiveTrace()        
*>       IdentMarmottes MarmottesCreer()      
*>       IdentMarmottes MarmottesCopie()      
*>       int MarmottesReinitialisation()      
*>       int MarmottesSenseurs()              
*>       int MarmottesNouveauRepere()         
*>       int MarmottesCalage()                
*>       int MarmottesModifieCible()          
*>       int MarmottesInitialiseGyro()        
*>       int MarmottesInitialiseDerive()      
*>       int MarmottesModifieReference()      
*>       void MarmottesDetruire()             
*>       int MarmottesDeuxconsignes()         
*>       int MarmottesAttitude()              
*>       int MarmottesImposeAttitude()        
*>       int MarmottesImposeSpin()            
*>       int MarmottesRepereBase()            
*>       int MarmottesRepere()                
*>       int MarmottesMesure()                
*>       int MarmottesControlable()           
*>       int MarmottesCriteresControlabilite()
*>       int MarmottesUnitesPositionVitesse() 
*>       int MarmottesRespecterConsignes()    
*>       int MarmottesConvertirConsignes()    
*>       int MarmottesRespecterMesures()      
*>       int MarmottesConvertirMesures()      
*>       int MarmottesWMax()                  
*>       int MarmottesConvergence()           
*>       int MarmottesDichotomie()            
*>       int MarmottesAutoriseExtrapolation() 
*>       int MarmottesInterditExtrapolation() 
*>       int MarmottesEnregistreCorps()       
*>       int MarmottesLireParametres()       
*$Historique
*       $Log: InterfaceC.h,v $
*       Revision 1.15  2003/10/22 13:01:12  marmottes
*       DM 0027
*
*       Revision 1.14  2003/02/27 16:17:57  marmottes
*       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
*
*       Revision 1.13  2002/09/09 13:18:26  marmottes
*       ajout de la fonction MarmottesEnregistreCorps et des typedef
*       TypeFuncTsidC et TypeFuncPosC (DM 0007)
*
*       Revision 1.12  2002/02/27 14:09:09  marmottes
*       suppression de la description de la révision insérée manuellement
*       et mise à jour du copyright CNES
*
*       Revision 1.11  2002/02/22 09:36:51  marmottes
*       Ajout de la fonction MarmottesInitialiseDerive (DM 0002)
*
*       Revision 1.10  2002/01/17 14:29:59  marmottes
*       (MarmottesActiveTrace) changement de signature
*
*       Revision 1.9  2001/04/05 11:54:47  luc
*       déclaration d'un type énuméré spécifique pour le retour des astres
*       perturbateurs dans la fonction MarmottesCriteresControlabilite
*
*       Revision 1.8  2001/04/04 12:11:26  luc
*       ajout de la fonction MarmottesCriteresControlabilite
*
*       Revision 1.7  2001/02/27 12:32:49  luc
*       ajout des fonctions MarmottesImposeAttitude et MarmottesImposeSpin
*
*       Revision 1.6  2000/09/05 13:29:47  luc
*       ajout des fonctions MarmottesActiveTrace et MarmottesDesactiveTrace
*
*       Revision 1.5  1999/11/02 07:19:21  luc
*       correction de la macro de protection contre les inclusions multiples
*
*       Revision 1.4  1998/10/12 15:32:00  luc
*       remplacement des commentaires C++ par des commentaires C pour
*       permettre l'inclusion du fichier par un compilateur C ANSI
*
*       Revision 1.3  1998/07/15 12:03:37  luc
*       ajout des fonctions MarmottesModifieCible, MarmottesInitialiseGyro
*       et MarmottesModifieReference
*
*       Revision 1.2  1998/06/25 06:00:21  luc
*       modification du format des en-têtes
*       élimination de la variable statique RCS
*
*       Revision 1.1  1998/04/29 17:11:34  luc
*       Initial revision
*
*$Version
*       $Id: InterfaceC.h,v 1.15 2003/10/22 13:01:12 marmottes Exp $
*
*$Auteur
*       L. Maisonobe CNES
*       Copyright (C) 2000-2001-2002 CNES
*
*$<>
******************************************************************************/

#ifndef __marmottes_InterfaceC_h
#define __marmottes_InterfaceC_h


/****************************************************************************/
/*                                RAPPEL                                    */
/*                                                                          */
/* La convention générale de représentation de l'attitude par MARMOTTES est */
/* que l'attitude transforme des vecteurs inertiels en vecteurs satellites. */
/*                                                                          */
/* On peut donc utiliser l'attitude MARMOTTES de la facon suivante:         */
/*     Soient uIn  les coordonnées en repère inertiel d'un vecteur          */
/*     Soient uSat les coordonnées en repère satellite du même vecteur      */
/*     Soit   att  l'attitude                                               */
/*                                                                          */
/* Conversion d'un vecteur inertiel en vecteur satellite                    */
/*             uSat = att (uIn)             (interface C++     de CANTOR)   */
/*        AppliqueRot (att, uIn, uSat)      (interface C       de CANTOR)   */
/*   call AppliqueRot (att, uIn, uSat)      (interface fortran de CANTOR)   */
/*                                                                          */
/* Conversion d'un vecteur satellite en vecteur inertiel                    */
/*             uIn = (-att) (uSat)          (interface C++     de CANTOR)   */
/*      AppliqueRotInverse (att, uSat, uIn) (interface C       de CANTOR)   */
/* call AppliqueRotInverse (att, uSat, uIn) (interface fortran de CANTOR)   */
/*                                                                          */
/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* identificateur d'instance de simulateur marmottes */
typedef int     IdentMarmottes;

/* identificateur d'astre occultant ou inhibant */
enum  MarmottesAstre { MrmNonSig, MrmSoleil, MrmLune, MrmCentral, MrmAucun };

/* définition des types des fonctions utilisateurs */
typedef double TypeFuncTsidC (double, double);    /* for sidereal time computation */
typedef void   TypeFuncPosC (double, double [3]); /* for position computation */

/* gestion des traces d'exécution */
int             MarmottesActiveTrace    (const char *fichier,
                                         char* messageErreur,
                                         int lgMaxMessage);

int             MarmottesDesactiveTrace (char* messageErreur,
                                         int lgMaxMessage);

/* création d'une instance */
IdentMarmottes  MarmottesCreer       (double         date,
                                      const double   position [3],
                                      const double   vitesse  [3],
                                      const double   attitude [4],
                                      const double   spin     [3],
                                      const char    *fichier,
                                      const char    *senseur1,
                                      const char    *senseur2,
                                      const char    *senseur3,
                                      char          *messageErreur,
                                      int            lgMaxMessage);

/* copie d'une instance */
IdentMarmottes  MarmottesCopie       (IdentMarmottes ident,
                                      char          *messageErreur,
                                      int            lgMaxMessage);

/* réinitialisation d'une instance */
int            MarmottesReinitialisation (IdentMarmottes ident,
                                          double         date,
                                          const double   position [3],
                                          const double   vitesse  [3],
                                          const double   attitude [4],
                                          const double   spin     [3],
                                          const char    *senseur1,
                                          const char    *senseur2,
                                          const char    *senseur3,
                                          char          *messageErreur,
                                          int            lgMaxMessage);

/* modification des senseurs utilisés par une instance */
int             MarmottesSenseurs    (IdentMarmottes ident,
                                      const char    *senseur1,
                                      const char    *senseur2,
                                      const char    *senseur3,
                                      char          *messageErreur,
                                      int            lgMaxMessage);

/* modification du repère d'un senseur */
int             MarmottesNouveauRepere (IdentMarmottes ident,
                                        const char    *senseur,
                                        double         nouveau [4],
                                        char          *messageErreur,
                                        int            lgMaxMessage);

/* modification du calage d'un senseur */
int             MarmottesCalage        (IdentMarmottes ident,
                                        const char    *senseur,
                                        double         calage,
                                        char          *messageErreur,
                                        int            lgMaxMessage);

/* modification de la cible d'un senseur optique */
int             MarmottesModifieCible  (IdentMarmottes ident,
                                        const char    *senseur,
                                        double         cible [3],
                                        char          *messageErreur,
                                        int            lgMaxMessage);

/* réinitialisation d'un gyroscope intégrateur */
int             MarmottesInitialiseGyro (IdentMarmottes ident,
                                         const char    *senseur,
                                         double         date,
                                         double         angle,
                                         char          *messageErreur,
                                         int            lgMaxMessage);

/* initialisation de la dérive d'un senseur cinématique */
int             MarmottesInitialiseDerive (IdentMarmottes ident,
                                           const char     *senseur,
                                           double         derive,
                                           char           *messageErreur,
                                           int            lgMaxMessage);


/* mise en place du repère de référence pour un senseur de Cardan */
int             MarmottesModifieReference (IdentMarmottes ident,
                                           const char    *senseur,
                                           double         reference [4],
                                           char          *messageErreur,
                                           int            lgMaxMessage);

/* destruction d'une instance */
void            MarmottesDetruire    (IdentMarmottes ident);

/* utilisation d'une instance de simulateur d'attitude */
int             MarmottesDeuxconsignes (IdentMarmottes ident,
                                        double         date,
                                        const double   position [3],
                                        const double   vitesse  [3],
                                        double         mesure1,
                                        double         mesure2,
                                        double         attitude [4],
                                        double         spin     [3],
                                        char          *messageErreur,
                                        int            lgMaxMessage);

int             MarmottesAttitude    (IdentMarmottes ident,
                                      double         date,
                                      const double   position [3],
                                      const double   vitesse  [3],
                                      double         mesure1,
                                      double         mesure2,
                                      double         mesure3,
                                      double         attitude [4],
                                      double         spin     [3],
                                      char          *messageErreur,
                                      int            lgMaxMessage);

int             MarmottesImposeAttitude (IdentMarmottes ident,
                                         double         date,
                                         const double   position [3],
                                         const double   vitesse  [3],
                                         const double   attit    [4],
                                         char          *messageErreur,
                                         int            lgMaxMessage);

int             MarmottesImposeSpin  (IdentMarmottes ident,
                                      double         date,
                                      const double   position [3],
                                      const double   vitesse  [3],
                                      const double   spin     [3],
                                      char          *messageErreur,
                                      int            lgMaxMessage);

int             MarmottesRepereBase  (IdentMarmottes ident,
                                      const char    *senseur,
                                      double         r [4],
                                      char          *messageErreur,
                                      int            lgMaxMessage);

int             MarmottesRepere      (IdentMarmottes ident,
                                      const char    *senseur,
                                      double         r [4],
                                      char          *messageErreur,
                                      int            lgMaxMessage);

int             MarmottesMesure      (IdentMarmottes ident,
                                      const char    *senseur,
                                      double        *mesure,
                                      char          *messageErreur,
                                      int            lgMaxMessage);

int             MarmottesControlable (IdentMarmottes ident,
                                      const char    *senseur,
                                      int           *controlable,
                                      char          *messageErreur,
                                      int            lgMaxMessage);

int             MarmottesCriteresControlabilite (IdentMarmottes  ident,
                                                 const char     *senseur,
                                                 MarmottesAstre *inhibant,
                                                 MarmottesAstre *eclipsant,
                                                 double         *ecartFrontiere,
                                                 int            *amplitudeSignificative,
                                                 char           *messageErreur,
                                                 int             lgMaxMessage);

int             MarmottesUnitesPositionVitesse (IdentMarmottes ident,
                                                const char    *unitePos,
                                                const char    *uniteVit,
                                                char          *messageErreur,
                                                int            lgMaxMessage);

int             MarmottesRespecterConsignes (IdentMarmottes ident,
                                             const char    *senseur,
                                             char          *messageErreur,
                                             int            lgMaxMessage);

int             MarmottesConvertirConsignes (IdentMarmottes ident,
                                             const char    *senseur,
                                             char          *messageErreur,
                                             int            lgMaxMessage);

int             MarmottesRespecterMesures   (IdentMarmottes ident,
                                             const char    *senseur,
                                             char          *messageErreur,
                                             int            lgMaxMessage);

int             MarmottesConvertirMesures   (IdentMarmottes ident,
                                             const char    *senseur,
                                             char          *messageErreur,
                                             int            lgMaxMessage);

/* fonctions annexes de réglage des algorithmes (convergence, ...) */
int             MarmottesWMax        (IdentMarmottes ident,
                                      double         omega,
                                      char          *messageErreur,
                                      int            lgMaxMessage);

int             MarmottesConvergence (IdentMarmottes ident,
                                      double         seuil,
                                      char          *messageErreur,
                                      int            lgMaxMessage);

int             MarmottesDichotomie  (IdentMarmottes ident,
                                      int            tranches,
                                      char          *messageErreur,
                                      int            lgMaxMessage);

int             MarmottesAutoriseExtrapolation  (IdentMarmottes ident,
                                                 char          *messageErreur,
                                                 int            lgMaxMessage);

int             MarmottesInterditExtrapolation  (IdentMarmottes ident,
                                                 char          *messageErreur,
                                                 int            lgMaxMessage);

/* récupération des fonctions utilisateurs de calculs d'éphémérides */

int             MarmottesEnregistreCorps (IdentMarmottes           ident,
                                          double                   equatorialRadius, 
                                          double                   oblateness, 
                                          double                   rotationVelocity, 
                                          double                   moonRadius, 
                                          double                   sunRadius, 
                                          TypeFuncTsidC *tsidFunc, 
                                          TypeFuncPosC  *sunFunc, 
                                          TypeFuncPosC  *moonFunc, 
                                          TypeFuncPosC  *earthFunc,
                                          char                     *messageErreur,
                                          int                       lgMaxMessage);

int             MarmottesLireParametres  (IdentMarmottes ident, 
                                          double         *date,
                                          double         position [3],
                                          double         vitesse  [3],
                                          double         attitude [4],
                                          double         spin     [3],
                                          char*          messageErreur, 
                                          int            lgMaxMessage);

#ifdef __cplusplus
}
#endif

#endif
