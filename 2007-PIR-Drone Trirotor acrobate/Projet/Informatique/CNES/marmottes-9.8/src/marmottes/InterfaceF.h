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
//       Marmottes
//
//$Nom
//>       InterfaceF.h
//$Resume
//       fichier d'en-tête des fonctions d'interface fortran
//
//$Description
//       Module de déclaration des fonctions
//
//$Contenu
//>       typedef double TypeFuncTsidF()        
//>       typedef void TypeFuncPosF()           
//>       int marmottesactivetrace_()           
//>       int marmottesdesactivetrace_()        
//>       int marmottescreer_()                 
//>       int marmottescopie_()                 
//>       int marmottesreinitialisation_()      
//>       int marmottessenseurs_()              
//>       int marmottesnouveaurepere_()         
//>       int marmottescalage_()                
//>       int marmottesmodifiecible_()          
//>       int marmottesinitialisegyro_()        
//>       int marmottesinitialisederive_()      
//>       int marmottesmodifiereference_()      
//>       void marmottesdetruire_()             
//>       int marmottesdeuxconsignes_()         
//>       int marmottesattitude_()              
//>       int marmottesimposeattitude_()        
//>       int marmottesimposespin_()            
//>       int marmottesreperebase_()            
//>       int marmottesrepere_()                
//>       int marmottesmesure_()                
//>       int marmottescontrolable_()           
//>       int marmottescriterescontrolabilite_()
//>       int marmottesunitespositionvitesse_() 
//>       int marmottesrespecterconsignes_()    
//>       int marmottesconvertirconsignes_()    
//>       int marmottesrespectermesures_()      
//>       int marmottesconvertirmesures_()      
//>       int marmotteswmax_()                  
//>       int marmottesconvergence_()           
//>       int marmottesdichotomie_()            
//>       int marmottesautoriseextrapolation_() 
//>       int marmottesinterditextrapolation_() 
//>       int marmottesenregistrecorps_()       
//>       int marmottesversion_()       
//>       int marmotteslireparametres_()       
//$Historique
//       $Log: InterfaceF.h,v $
//       Revision 3.31  2003/10/22 13:01:12  marmottes
//       DM 0027
//
//       Revision 3.30  2003/07/09 12:33:49  marmottes
//       Formattage des paragraphes de commentaires
//
//       Revision 3.29  2003/07/02 15:22:37  marmottes
//       Mise en conf pour sauvegarde des modifs suite a la FA sur la mise a disposition 
//       des fonctions de calcul par defaut du temps sideral, de la position de la Lune 
//       de la Terre et du Soleil pour linterface Fortran
//
//       Revision 3.28  2003/07/02 07:25:51  marmottes
//       Mise en conf pour sauvegarde des modifs suite a la DM sur la mise a disposition 
//       des fonctions de calcul par defaut du temps sideral, de la position de la Lune 
//       de la Terre et du Soleil pour linterface Fortran
//
//       Revision 3.27  2003/06/13 15:24:54  marmottes
//       FA-ID 0023 Ajout des interfaces des fonctions par defaut pour marmottesenregistrecorps
//
//       Revision 3.26  2003/03/27 15:49:15  marmottes
//       Suppression des '&' en trop dans enregistreCorps
//
//       Revision 3.25  2003/03/27 14:34:01  marmottes
//       Annulation de la correction de la FA-ID 0023 car la correction ne permettait
//       pas de couvrir tous les cas.
//
//       Revision 3.24  2003/03/26 18:21:23  marmottes
//       FA-ID 0023 Modification du type des fonctions fortran dans enregistreCorps
//
//       Revision 3.23  2003/02/27 16:17:40  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 3.22  2003/01/22 15:32:28  marmottes
//       DM-ID 0009 Modification des paramétres de l'interface Fortran de récupération de la version de marmottes.
//
//       Revision 3.21  2002/11/28 16:12:16  marmottes
//       DM-ID 0009 Ajout d'une interface Fortran pour la fonction de récupération de la version de la bibliothéque
//
//       Revision 3.20  2002/09/09 13:06:29  marmottes
//       ajout de la fonction marmottesenregistrecorps_ et des typedef
//       TypeFuncTsidF et TypeFuncPosF (DM 0007)
//
//       Revision 3.19  2002/04/29 09:37:20  marmottes
//       correction de l'oubli d'un paramétre dans InterfaceF.h (fonction initialisederive)
//
//       Revision 3.18  2002/02/27 14:09:09  marmottes
//       suppression de la description de la révision insérée manuellement
//       et mise à jour du copyright CNES
//
//       Revision 3.17  2002/02/22 09:37:55  marmottes
//       Ajout de la fonction marmottesinitialisederive_ (DM 0002)
//
//       Revision 3.16  2001/04/04 12:12:23  luc
//       ajout de la fonction MarmottesCriteresControlabilite
//
//       Revision 3.15  2001/02/27 12:33:07  luc
//       ajout des fonctions MarmottesImposeAttitude et MarmottesImposeSpin
//
//       Revision 3.14  2000/09/05 13:29:06  luc
//       ajout des fonctions marmottesactivetrace_ et marmottesdesactivetrace_
//
//       Revision 3.13  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 3.12  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 3.11  1998/10/05 15:14:59  luc
//       correction de références oubliées dans une signature
//
//       Revision 3.10  1998/07/15 12:05:03  luc
//       ajout des fonctions marmottesmodifiecible_, marmottesinitialisegyro_
//       et marmottesmodifiereference_
//
//       Revision 3.9  1998/06/25 05:59:08  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 3.8  1998/04/29 17:12:22  luc
//       renommage du fichier (et donc des protections d'inclusion)
//
//       Revision 3.7  1998/04/26 18:21:08  luc
//       ajout d'une gestion d'unités de position et de vitesse variables
//
//       Revision 3.6  1997/09/21 19:37:22  luc
//       ajout de la possibilité de faire gérer les unités
//       par chaque instance de senseur
//
//       Revision 3.5  1997/08/20 16:50:39  luc
//       ajout d'une fonction de réinitialisation de simulateur Marmottes
//
//       Revision 3.5  1997/08/20 16:31:15  luc
//       ajout d'une fonction de réinitialisation de simulateur Marmottes
//
//       Revision 3.4  1997/08/20 11:50:44  luc
//       remontée du choix de la résolution rapide par extrapolation
//       au niveau de l'utilisateur (résolution rapide autorisée par défaut)
//
//       Revision 3.3  1997/08/20 09:34:53  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.2  1997/04/27 19:32:58  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 3.1  1997/01/28 12:43:27  luc
//       ajout de la vitesse et du spin à la création et à la réinitialisation
//       ajout de la vitesse pour les calculs d'attitude
//       création des interfaces fortran à la gestion des repères senseurs
//       (MarmottesNouveauRepere, MarmottesCalage, MarmottesRepereBase, MarmottesRepere)
//       
//       Revision 2.2  1996/09/11 17:37:59  luc
//       ajout des interfaces fortran MarmottesCopie et MarmottesDeuxConsignes
//       
//       Revision 2.1  1996/07/31 17:15:46  luc
//       prise en compte du renommage des erreurs.h en util_erreurs.h et marmottes_erreurs.h
//       
//       Revision 1.1  1995/01/25 09:45:45  mercator
//       Initial revision
//
//$Version
//       $Id: InterfaceF.h,v 3.31 2003/10/22 13:01:12 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_InterfaceF_h
#define __marmottes_InterfaceF_h

#ifdef __cplusplus
extern "C" {
#endif

/* définition des types des fonctions utilisateurs */
typedef double TypeFuncTsidF (double*, double*);    /* for sidereal time computation */
typedef void   TypeFuncPosF (double*, double [3]);  /* for position computation */

/* fonctions d'interface avec le fortran */

/* gestion des traces d'exécution */
int            marmottesactivetrace_    (char *fichier,
                                         char* messageErreur,
                                         long int lDeclFichier,
                                         long int lDeclMessage);

int            marmottesdesactivetrace_ (char* messageErreur,
                                         long int lDeclMessage);

/* création d'une instance */
int            marmottescreer_       (double&        date,
                                      double         position [3],
                                      double         vitesse  [3],
                                      double         attitude [4],
                                      double         spin     [3],
                                      const char*    fichier,
                                      const char*    senseur1,
                                      const char*    senseur2,
                                      const char*    senseur3,
                                      char*          messageErreur,
                                      long int       lDeclFichier,
                                      long int       lDeclSenseur1,
                                      long int       lDeclSenseur2,
                                      long int       lDeclSenseur3,
                                      long int       lDeclMessage
                                      );

/* copie d'une instance */
int            marmottescopie_       (int&           ident,
                                      char*          messageErreur,
                                      long int       lDeclMessage
                                      );

/* réinitialisation d'une instance */
int            marmottesreinitialisation_ (int&           ident,
                                           double&        date,
                                           double         position [3],
                                           double         vitesse  [3],
                                           double         attitude [4],
                                           double         spin     [3],
                                           const char*    senseur1,
                                           const char*    senseur2,
                                           const char*    senseur3,
                                           char*          messageErreur,
                                           long int       lDeclSenseur1,
                                           long int       lDeclSenseur2,
                                           long int       lDeclSenseur3,
                                           long int       lDeclMessage
                                          );

/* modification des senseurs utilisés par une instance */
int            marmottessenseurs_    (int&           ident,
                                      const char*    senseur1,
                                      const char*    senseur2,
                                      const char*    senseur3,
                                      char*          messageErreur,
                                      long int       lDeclSenseur1,
                                      long int       lDeclSenseur2,
                                      long int       lDeclSenseur3,
                                      long int       lDeclMessage
                                      );

/* modification du repère d'un senseur */
int            marmottesnouveaurepere_ (int&        ident,
                                        const char *senseur,
                                        double      nouveau [4],
                                        char       *messageErreur,
                                        long int    lDeclSenseur,
                                        long int    lDeclMessage);

/* modification du calage d'un senseur */
int            marmottescalage_        (int&        ident,
                                        const char *senseur,
                                        double&     calage,
                                        char       *messageErreur,
                                        long int    lDeclSenseur,
                                        long int    lDeclMessage);

/* modification de la cible d'un senseur optique */
int            marmottesmodifiecible_  (int &        ident,
                                        const char  *senseur,
                                        const double cible [3],
                                        char        *messageErreur,
                                        long int     lDeclSenseur,
                                        long int     lDeclMessage);

/* réinitialisation d'un gyroscope intégrateur */
int            marmottesinitialisegyro_ (int &        ident,
                                         const char  *senseur,
                                         double&      date,
                                         double&      angle,
                                         char        *messageErreur,
                                         long int     lDeclSenseur,
                                         long int     lDeclMessage);

/* initialisation de la dérive (offset) d'un senseur cinématique */
int            marmottesinitialisederive_ (int&           ident,
                                           const char     *senseur,
                                           double&        derive,
                                           char*          messageErreur,
                                           long int       lDeclSenseur, 
                                           long int       lDeclMessage);

/* mise en place du repère de référence pour un senseur de Cardan */
int            marmottesmodifiereference_ (int &        ident,
                                           const char  *senseur,
                                           const double reference [4],
                                           char        *messageErreur,
                                           long int     lDeclSenseur,
                                           long int     lDeclMessage);

/* destruction d'une instance */
void           marmottesdetruire_    (int&           ident);

/* utilisation d'une instance de simulateur d'attitude */
int            marmottesdeuxconsignes_ (int&           ident,
                                        double&        date,
                                        const double   position [3],
                                        const double   vitesse  [3],
                                        double&        mesure1,
                                        double&        mesure2,
                                        double         attitude [4],
                                        double         spin     [3],
                                        char*          messageErreur,
                                        long int       lDeclMessage
                                       );

int            marmottesattitude_    (int&           ident,
                                      double&        date,
                                      const double   position [3],
                                      const double   vitesse  [3],
                                      double&        mesure1,
                                      double&        mesure2,
                                      double&        mesure3,
                                      double         attitude [4],
                                      double         spin     [3],
                                      char*          messageErreur,
                                      long int       lDeclMessage
                                      );

int            marmottesimposeattitude_ (int&           ident,
                                         double&        date,
                                         const double   position [3],
                                         const double   vitesse  [3],
                                         const double   attitude [4],
                                         char*          messageErreur,
                                         long int       lDeclMessage);

int            marmottesimposespin_ (int&           ident,
                                     double&        date,
                                     const double   position [3],
                                     const double   vitesse  [3],
                                     const double   spin     [3],
                                     char*          messageErreur,
                                     long int       lDeclMessage);

int            marmottesreperebase_  (int&           ident,
                                      const char    *senseur,
                                      double         r [4],
                                      char          *messageErreur,
                                      long int       lDeclSenseur,
                                      long int       lDeclMessage);
             
int            marmottesrepere_      (int&           ident,
                                      const char    *senseur,
                                      double         r [4],
                                      char          *messageErreur,
                                      long int       lDeclSenseur,
                                      long int       lDeclMessage);

int            marmottesmesure_      (int&           ident,
                                      const char*    senseur,
                                      double&        mesure,
                                      char*          messageErreur,
                                      long int       lDeclSenseur,
                                      long int       lDeclMessage
                                      );

int            marmottescontrolable_ (int&           ident,
                                      const char*    senseur,
                                      int&           controlable,
                                      char*          messageErreur,
                                      long int       lDeclSenseur,
                                      long int       lDeclMessage
                                      );

int            marmottescriterescontrolabilite_ (int&           ident,
                                                 const char*    senseur,
                                                 int&           inhibant,
                                                 int&           eclipsant,
                                                 double&        ecartFrontiere,
                                                 int&           amplitudeSignificative,
                                                 char*          messageErreur,
                                                 long int       lDeclSenseur,
                                                 long int       lDeclMessage
                                                 );

int            marmottesunitespositionvitesse_ (int&           ident,
                                                const char    *unitePos,
                                                const char    *uniteVit,
                                                char          *messageErreur,
                                                long int       lDeclUnitePos,
                                                long int       lDeclUniteVit,
                                                long int       lDeclMessage
                                               );

int            marmottesrespecterconsignes_ (int&           ident,
                                             const char*    senseur,
                                             char*          messageErreur,
                                             long int       lDeclSenseur,
                                             long int       lDeclMessage
                                             );

int            marmottesconvertirconsignes_ (int&           ident,
                                             const char*    senseur,
                                             char*          messageErreur,
                                             long int       lDeclSenseur,
                                             long int       lDeclMessage
                                             );

int            marmottesrespectermesures_   (int&           ident,
                                             const char*    senseur,
                                             char*          messageErreur,
                                             long int       lDeclSenseur,
                                             long int       lDeclMessage
                                             );

int            marmottesconvertirmesures_   (int&           ident,
                                             const char*    senseur,
                                             char*          messageErreur,
                                             long int       lDeclSenseur,
                                             long int       lDeclMessage
                                             );

/* fonctions annexes de réglage des algorithmes (convergence, ...) */
int            marmotteswmax_        (int&           ident,
                                      double&        omega,
                                      char*          messageErreur,
                                      long int       lDeclMessage
                                     );

int            marmottesconvergence_ (int&           ident,
                                      double&        seuil,
                                      char*          messageErreur,
                                      long int       lDeclMessage
                                     );

int            marmottesdichotomie_  (int&           ident,
                                      int&           tranches,
                                      char*          messageErreur,
                                      long int       lDeclMessage
                                     );

int            marmottesautoriseextrapolation_ (int&           ident,
                                                char*          messageErreur,
                                                long int       lDeclMessage
                                               );

int            marmottesinterditextrapolation_ (int&           ident,
                                                char*          messageErreur,
                                                long int       lDeclMessage
                                               );

/* récupération des fonctions utilisateurs de calculs d'éphémérides */

int            marmottesenregistrecorps_ (int&          ident,
                                          double&       equatorialRadius, 
                                          double&       oblateness, 
                                          double&       rotationVelocity, 
                                          double&       moonRadius, 
                                          double&       sunRadius, 
                                          TypeFuncTsidF tsidFunc, 
                                          TypeFuncPosF  sunFunc, 
                                          TypeFuncPosF  moonFunc, 
                                          TypeFuncPosF  earthFunc,
                                          char*         messageErreur,
                                          long int      lDeclMessage
                                          );

/* récupération de la version de Marmottes */

int            marmottesversion_          (char *    version,
                                           long int  lDeclVersion     
                                          );

/* nom des fonctions par défaut a appeler à */
/* l'utilisation de marmottesenregistrecorps_ */

double         marmottestempssideralpardefaut_   (double*       t,
                                                  double*       offset
                                                 );

void           marmottespositionsoleilpardefaut_ (double*       t,
                                                  double        pos[3]
                                                 );

void           marmottespositionterrepardefaut_  (double*       t,
                                                  double        pos[3]
                                                 );

void           marmottespositionlunepardefaut_   (double*       t,
                                                  double        pos[3]
                                                 );

int            marmotteslireparametres_  (int&           ident, 
                                          double&        date,
                                          double         position [3],
                                          double         vitesse  [3],
                                          double         attitude [4],
                                          double         spin     [3],
                                          char*          messageErreur, 
                                          long int       lDeclMessage);

#ifdef __cplusplus
           }
#endif

#endif
