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
//>       Marmottes.h
//$Resume
//       fichier d'en-tête de la classe Marmottes
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Marmottes
//$Historique
//       $Log: Marmottes.h,v $
//       Revision 3.34  2003/10/22 13:01:12  marmottes
//       DM 0027
//
//       Revision 3.33  2003/02/27 16:17:18  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 3.32  2002/11/28 16:13:40  marmottes
//       Ajout de directive throw oubliees
//
//       Revision 3.31  2002/09/09 13:03:41  marmottes
//       ajout de la méthode enregistreCorps (DM 0007)
//
//       Revision 3.30  2002/04/04 09:40:37  marmottes
//       Introduction des méthodes accesSenseur et etat (DM 0004)
//
//       Revision 3.29  2002/02/27 14:09:09  marmottes
//       suppression de la description de la révision insérée manuellement
//       et mise à jour du copyright CNES
//
//       Revision 3.28  2002/02/22 09:41:34  marmottes
//       Ajout de la méthode Marmottes::initialiseDerive (DM 0002)
//
//       Revision 3.27  2002/01/17 09:38:03  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 3.26  2001/07/17 15:28:14  luc
//       lancement de CantorErreurs par toutes les fonctions
//       pouvant lire un nouveau senseur
//
//       Revision 3.25  2001/04/04 12:17:32  luc
//       ajout de la méthode criteresControlabilite
//
//       Revision 3.24  2001/02/27 12:31:51  luc
//       ajout des méthodes imposeAttitude et imposeSpin
//
//       Revision 3.23  2001/02/07 16:46:26  luc
//       remplacement de la classe non standard hash_map par map
//       modification des exceptions lancées par le constructeur
//       par copie et par l'opérateur d'affectation
//
//       Revision 3.22  2000/10/06 09:13:20  luc
//       élimination de la séparation entre états résolu et extrapolé
//
//       Revision 3.21  2000/10/02 13:11:08  luc
//       remplacement d'attributs entiers en booléens
//       ajout d'un destructeur
//
//       Revision 3.20  2000/09/13 09:41:21  luc
//       remplacement de tous les ChaineSimple par des string
//       remplacement de Adressage par hash_map
//
//       Revision 3.19  2000/09/08 07:53:38  luc
//       ajout d'exceptions dans les signatures des méthodes
//       interditExtrapolation et autoriseExtrapolation, à la suite de la mise
//       en place du mécanisme de trace d'exécution
//
//       Revision 3.18  2000/09/05 13:27:29  luc
//       génération d'exceptions par le mécanisme de trace d'exécution dans la
//       méthode desinitialise et dans l'opérateur d'affectation, report du
//       corps de la méthode desinitialise dans Marmottes.cc
//
//       Revision 3.17  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 3.16  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 3.15  1999/08/25 09:41:03  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 3.14  1999/08/06 13:32:17  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 3.13  1998/07/15 12:08:31  luc
//       ajout des méthodes : modifieCible, initialiseGyro et modifieReference
//       ajout de la méthode privée valideNouvelEtat
//
//       Revision 3.12  1998/06/25 06:02:08  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 3.11  1998/05/14 12:05:17  luc
//       intégration des fonctionnalités de la classe ListeSenseurs
//       directement dans la classe Marmottes
//       transfert des fonctions d'interface C dans un fichier spécifique
//
//       Revision 3.10  1998/04/26 18:25:00  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.9  1998/04/26 18:21:01  luc
//       ajout d'une gestion d'unités de position et de vitesse variables
//
//       Revision 3.8  1998/03/24 18:42:27  luc
//       correction de signatures de fonctions extern "C"
//
//       Revision 3.7  1998/02/19 16:18:14  luc
//       déplacement d'un constructeur inline dans le .cc
//       pour contourner un problème d'optimiseur avec g++ 2.8.0
//
//       Revision 3.6  1997/09/21 19:37:15  luc
//       ajout de la possibilité de faire gérer les unités
//       par chaque instance de senseur
//
//       Revision 3.5  1997/08/20 16:50:48  luc
//       ajout d'une fonction de réinitialisation de simulateur Marmottes
//
//       Revision 3.4  1997/08/20 11:50:34  luc
//       remontée du choix de la résolution rapide par extrapolation
//       au niveau de l'utilisateur (résolution rapide autorisée par défaut)
//
//       Revision 3.3  1997/08/20 09:33:22  luc
//       ajout d'un en-tête de fichier
//       utilisation de ChaineSimple à la place de char *
//
//       Revision 3.2  1997/04/27 19:32:45  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 3.1  1997/01/28 12:40:17  luc
//       ajout de la vitesse et du spin à la création et à la réinitialisation
//       ajout de la vitesse pour les calculs d'attitude
//       ajout de qualificateurs "const"
//       
//       Revision 2.2  1996/09/11 17:30:17  luc
//       ajout de la méthode deuxConsignes
//       transfert du constructeur par copie dans le .cc
//       ajout des interfaces C MarmottesCopie et MarmottesDeuxConsignes
//       
//       Revision 2.1  1996/07/31 16:48:50  luc
//       abandon des tools.h++ (Rogue Wave)
//       ajout des fonctions MarmottesNouveauRepere, MarmottesCalage,
//       MarmottesRepereBase, MarmottesRepere
//       (et des fonctions correspondantes de la classe Marmottes)
//       élimination de la limitation à quatre simulateurs simultanés
//       prise en compte du renommage des erreurs.h en util_erreurs.h et marmottes_erreurs.h
//       
//       Revision 1.3  1995/07/12 12:17:35  mercator
//       propagation de la desinitialisation de l'instance aux etats inclus
//       
//       Revision 1.2  1995/07/12 12:01:49  mercator
//       ajout d'un commentaire rappelant les conventions sur les rotations
//       
//       Revision 1.1  1995/01/25 09:29:04  mercator
//       Initial revision
//
//$Version
//       $Id: Marmottes.h,v 3.34 2003/10/22 13:01:12 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_Marmottes_h
#define __marmottes_Marmottes_h

#include <string>
#include <map>

#include "club/FichierStructure.h"

#include "cantor/DeclDBL.h"

#include "marmottes/MarmottesErreurs.h"
#include "marmottes/Etat.h"
#include "marmottes/Senseur.h"
#include "marmottes/ResolveurAttitude.h"
#include "marmottes/BodyEphemC.h"
#include "marmottes/BodyEphemF.h"

//////////////////////////////////////////////////////////////////////////////
//                                RAPPEL                                    //
//                                                                          //
// La convention générale de représentation de l'attitude par MARMOTTES est //
// que l'attitude transforme des vecteurs inertiels en vecteurs satellites. //
//                                                                          //
// On peut donc utiliser l'attitude MARMOTTES de la facon suivante:         //
//     Soient uIn  les coordonnées en repère inertiel d'un vecteur          //
//     Soient uSat les coordonnées en repère satellite du même vecteur      //
//     Soit   att  l'attitude                                               //
//                                                                          //
// Conversion d'un vecteur inertiel en vecteur satellite                    //
//             uSat = att (uIn)             (interface C++     de CANTOR)   //
//        AppliqueRot (att, uIn, uSat)      (interface C       de CANTOR)   //
//   call AppliqueRot (att, uIn, uSat)      (interface fortran de CANTOR)   //
//                                                                          //
// Conversion d'un vecteur satellite en vecteur inertiel                    //
//             uIn = (-att) (uSat)          (interface C++     de CANTOR)   //
//      AppliqueRotInverse (att, uSat, uIn) (interface C       de CANTOR)   //
// call AppliqueRotInverse (att, uSat, uIn) (interface fortran de CANTOR)   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Marmottes
//
//$Resume
//       classe gérant un simulateur d'attitude
//
//$Description
//       Cette classe concrète est la classe de plus haut niveau de la
//       bibliothèque marmottes, elle gère un simulateur d'attitude
//       complet, avec ses états précédent et courant, ses senseurs de
//       contrôle et ses senseurs de mesures. L'utilisation normale est
//       de créer une instance de simulateur avec une position et une
//       attitude initiale, puis à lui faire suivre pas à pas
//       l'évolution du satellite par des appels à la méthode attitude,
//       qui est la méthode la plus importante. De temps à autre on
//       peut changer les senseurs de contrôle par la méthode senseurs.
//
//$Usage
//>     construction : 
//          sans argument, à partir d'un état initial et des senseurs
//          à utiliser, par copie
//>     utilisation  : 
//>       Marmottes& operator =          () 
//          affectation
//>       int reinitialise               () 
//          remet à jour l'ensemble de l'instance (senseurs/etat)
//>       int senseurs                   () 
//          met à jour l'instance à partir de nouveaux noms de senseurs
//          (lus dans le fichier)
//>       int nouveauRepere              () 
//          modifie le repère courant
//>       int calage                     () 
//          recale le senseur (s'il a un axe de calage prédéfini)
//>       int modifieCible               () 
//          mémorise une cible utilisateur pour un senseur optique
//>       int initialiseGyro             () 
//          initialise l'angle d'un gyro intégrateur
//>       int initialiseDerive           () 
//          initialise la dérive d'un senseur cinématique
//>       int modifieReference           () 
//          mémorise un repère de référence pour un senseur de Cardan
//>       int deuxConsignes              () 
//          calcule l'attitude vérifiant deux consignes de mesures
//>       int attitude                   () 
//          calcule l'attitude vérifiant trois consignes de mesures
//>       int imposeAttitude             () 
//          impose à l'instance une attitude fournie par l'utilisateur
//          (le spin en résulte par différences finies)
//>       int imposeSpin                 () 
//          impose à l'instance un spin fourni par l'utilisateur
//          (l'attitude en résulte par intégration)
//>       int repereBase                 () 
//          retourne le repère initial du senseur (lu dans le fichier)
//>       int repere                     () 
//          retourne le repère courant du senseur
//>       int mesure                     () 
//          initialise le réel pointé par m avec la mesure fournie par
//          le senseur dont le nom est fourni, dans l'état courant (le
//          senseur ne correspond pas forcément à un des senseurs
//          utilisés pour le pilotage)
//>       int controlable                () 
//          initialise l'entier pointé par c avec l'indicateur de
//          contrôlabilité du senseur dont le nom est fourni, dans
//          l'état courant (le senseur ne correspond pas forcément à
//          un des senseurs utilisés pour le pilotage)
//>       int criteresControlabilite     () 
//          initialise les variables pointées par inhibant et eclipsant
//          avec les codes des astres inhibant et éclipsant et le réel
//          pointé par ecart avec l'écart disponible par rapport à la
//          frontière du domaine de fonctionnement du senseur du senseur
//          dont le nom est fourni, dans l'état courant (le senseur ne
//          correspond pas forcément à un des senseurs utilisés pour le
//          pilotage)
//>       int unitesPositionVitesse      () 
//          permet de spécifier les unités dans lesquelles
//          l'utilisateur va donner les position/vitesse (par défaut
//          on considère km et km/s)
//>       int respecterConsignes         () 
//          indique que le senseur dont le nom est fourni ne doit pas
//          convertir les valeurs de consignes qu'on lui donnera par
//          la suite, elles seront déjà exprimées dans l'unité
//          interne.
//>       int convertirConsignes         () 
//          indique que le senseur dont le nom est fourni doit
//          convertir lui-même les valeurs de consignes qu'on lui
//          donnera par la suite de l'unité utilisateur à l'unité
//          interne.
//>       int respecterMesures           () 
//          indique que le senseur dont le nom est fourni ne doit pas
//          convertir les mesures qu'il fournira par la suite à
//          l'utilisateur directement dans l'unité interne.
//>       int convertirMesures           () 
//          indique que le senseur dont le nom est fourni doit
//          convertir les mesures qu'il fournira par la suite à
//          l'utilisateur de l'unité interne à l'unité utilisateur.
//>       void desinitialise             () 
//          désinitialise l'instance
//>       const string& nomFichier       () 
//          retourne le nom du fichier des senseurs.
//>       int estInitialise              () 
//          indique si l'instance a été initialisée
//>       int wMax                       () 
//          met à jour le paramètre de réglage correspondant à la
//          vitesse maximale de rotation du satellite utilisée dans
//          les résolutions avec senseurs cinématiques.
//>       int convergence                () 
//          met à jour le paramètre de réglage correspondant au seuil
//          de convergence des algorithmes de résolution.
//>       int dichotomie                 () 
//          met à jour le paramètre de réglage correspondant au nombre
//          de tranches de dichotomie pour la séparation des extremums
//          locaux.
//>       void autoriseExtrapolation     () 
//          autorise l'utilisation de simple extrapolations pour accélérer
//          les calculs (on peut éviter les résolutions complètes)
//>       void interditExtrapolation     () 
//          interdit l'utilisation de simple extrapolations pour accélérer
//          les calculs (on DOIT faire des résolutions complètes)
//>       Senseur * accesSenseur         () 
//          récupére le pointeur sur le senseur initialisé à partir de son
//          nom et de ses caractéristiques lues dans un fichier
//>       void enregistreCorps     () 
//          donne accès aux fonctions utilisateurs de calculs d'éphémérides 
//          par rapport au corps central (écrites en C ou en fortran)
//
//>       void lireParametres      () 
//          donne accès aux valeurs courantes des parametres suivants :     
//          date, position, vitesse, attitude, spin
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////
class Marmottes
{
public :

  // constructeurs
  Marmottes ();
  Marmottes (double date, const VecDBL& position, const VecDBL& vitesse,
             const RotDBL& attitude, const VecDBL& spin,
             const string& fichier,
             const string& senseur1,
             const string& senseur2,
             const string& senseur3) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
  {
    reinitialise (date, position, vitesse, attitude, spin,
                  fichier, senseur1, senseur2, senseur3);
  }
  Marmottes (const Marmottes& m)
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  Marmottes& operator = (const Marmottes& m)
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  // destructeur
  ~Marmottes ();

  // fonctions de modification des éléments internes
  void desinitialise   ()
    throw (MarmottesErreurs);
  void reinitialise    (double date,
                        const VecDBL& position, const VecDBL& vitesse,
                        const RotDBL& attitude, const VecDBL& spin,
                        const string& fichier,
                        const string& senseur1,
                        const string& senseur2,
                        const string& senseur3) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void senseurs        (const string& fichier,
                        const string& senseur1,
                        const string& senseur2,
                        const string& senseur3) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void nouveauRepere   (const string& fichier,
                        const string& senseur,
                        const RotDBL& nouveau) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void calage          (const string& fichier,
                        const string& senseur,
                        double c) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void modifieCible    (const string& fichier,  
                        const string& senseur,
                        const VecDBL& cible) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);  
  void initialiseGyro  (const string& fichier,  
                        const string& senseur,
                        double              date,
                        double              angle)  
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void initialiseDerive(const string& fichier,
                        const string& senseur,
                        double derive) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);  
  void modifieReference (const string& fichier,  
                         const string& senseur,
                         const RotDBL&       reference) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);  

  // fonctions de résolution
  void deuxConsignes (double date,
                      const VecDBL& position, const VecDBL& vitesse,
                      double m1, double m2,
                      RotDBL *attitude, VecDBL *spin)
    throw (CantorErreurs, MarmottesErreurs);
  void attitude      (double date,
                      const VecDBL& position, const VecDBL& vitesse,
                      double m1, double m2, double m3,
                      RotDBL *attit, VecDBL *spin) 
    throw (CantorErreurs, MarmottesErreurs);
  void imposeAttitude (double date,
                       const VecDBL& position, const VecDBL& vitesse,
                       const RotDBL& attit) 
    throw (MarmottesErreurs);
  void imposeSpin     (double date,
                       const VecDBL& position, const VecDBL& vitesse,
                       const VecDBL& spin) 
    throw (MarmottesErreurs);

  // fonctions d'utilisation de l'attitude
  void repereBase    (const string& fichier,
                      const string& senseur, RotDBL *r) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void repere        (const string& fichier,
                      const string& senseur, RotDBL *r) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void mesure        (const string& fichier,
                      const string& senseur, double *m) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void controlable   (const string& fichier,
                      const string& senseur, int    *c) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void criteresControlabilite (const string& fichier,
                               const string& senseur,
                               Senseur::codeAstre *inhibant,
                               Senseur::codeAstre *eclipsant,
                               double *ecartFrontiere,
                               bool *amplitudeSignificative) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  void unitesPositionVitesse (const string& unitePos,
                              const string& uniteVit)
    throw (MarmottesErreurs);

  void respecterConsignes (const string& fichier,
                           const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void convertirConsignes (const string& fichier,
                           const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void respecterMesures   (const string& fichier,
                           const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void convertirMesures   (const string& fichier,
                           const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  const string& nomFichier    () const
                { return fichier_.nomFichier (); }

  bool          estInitialise () const
                { return initialise_; }

  // récupération de l'état
  const Etat&   etat          () const
                { return etat_ ; }

  // fonctions de réglage des paramètres de l'algorithme de résolution
  void wMax (double omega) 
    throw (MarmottesErreurs);

  void convergence (double seuil) 
    throw (MarmottesErreurs);

  void dichotomie (int tranches) 
    throw (MarmottesErreurs);

  void autoriseExtrapolation () 
    throw (MarmottesErreurs);

  void interditExtrapolation () 
    throw (MarmottesErreurs);

  // récupération de pointeurs
  Senseur * accesSenseur(const string& fichier,
                         const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  // récupération des fonctions utilisateurs de calculs d'éphémérides
  void enregistreCorps (double equatorialRadius, 
                        double oblateness, double rotationVelocity,
                        double moonRadius, double sunRadius,
                        BodyEphemC::TypeFuncTsid *tsidFunc, 
                        BodyEphemC::TypeFuncPos *sunFunc, BodyEphemC::TypeFuncPos *moonFunc, 
                        BodyEphemC::TypeFuncPos *earthFunc) 
    throw (MarmottesErreurs);

  void enregistreCorps (double equatorialRadius, 
                        double oblateness, double rotationVelocity, 
                        double moonRadius, double sunRadius,
                        BodyEphemF::TypeFuncTsid *tsidFunc, 
                        BodyEphemF::TypeFuncPos *sunFunc, BodyEphemF::TypeFuncPos *moonFunc, 
                        BodyEphemF::TypeFuncPos *earthFunc) 
    throw (MarmottesErreurs);

  void lireParametres  (double *ptrDate,
                        VecDBL *ptrPosition, VecDBL *ptrVitesse, 
                        RotDBL *ptrAttitude, VecDBL *ptrSpin);

private :

  bool                 initialise_;
  bool                 extrapolationOk_;
  Etat                 etat_;

  ResolveurAttitude    solveur_;

  FichierStructure     fichier_;
  map<string, Senseur *> senseurs_;

  void      initialiseSenseurs (const string& nomFichier)
    throw (ClubErreurs, MarmottesErreurs);

  Senseur* recupParNom        (const string& nom)
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  void     valideNouvelEtat   (double date,
                               const VecDBL& position, const VecDBL& vitesse,
                               const RotDBL& attitude, const VecDBL& spin);

};

#endif
