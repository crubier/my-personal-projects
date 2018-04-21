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
//>       InterfaceF.cpp
//$Resume
//       fichier d'implantation des fonctions d'interface avec le fortran
//
//$Description
//       Module de définition des fonctions d'interface
//
//$Contenu
//>       static int CopieMessageF()            
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
//$Historique
//       $Log: InterfaceF.cpp,v $
//       Revision 3.39  2003/10/22 13:00:38  marmottes
//       DM 0027
//
//       Revision 3.38  2003/07/09 12:33:30  marmottes
//       Formattage des paragraphes de commentaires
//
//       Revision 3.37  2003/07/09 12:29:54  marmottes
//       Formattage des paragraphes de commentaires
//
//       Revision 3.36  2003/07/02 15:21:54  marmottes
//       Mise en conf pour sauvegarde des modifs suite a la FA sur la mise a 
//       disposition des fonctions de calcul par defaut du temps sideral, de 
//       la position de la Lune de la Terre et du Soleil pour linterface Fortran
//
//       Revision 3.35  2003/07/02 07:25:12  marmottes
//       Mise en conf pour sauvegarde des modifs suite a la FA sur la mise a 
//       disposition des fonctions de calcul par defaut du temps sideral, de 
//       la position de la Lune de la Terre et du Soleil pour linterface Fortran
//
//       Revision 3.34  2003/03/27 15:48:44  marmottes
//       Suppression des '&' en trop dans enregistreCorps
//
//       Revision 3.33  2003/03/27 14:34:00  marmottes
//       Annulation de la correction de la FA-ID 0023 car la correction ne permettait
//       pas de couvrir tous les cas.
//
//       Revision 3.32  2003/03/26 18:20:28  marmottes
//       FA-ID 0023 Modification du type des fonctions fortran dans enregistreCorps
//
//       Revision 3.31  2003/02/27 16:40:15  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 3.30  2003/02/04 16:28:37  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 3.29  2003/01/22 15:29:49  marmottes
//       DM-ID 0009 Modification de l'interface Fortran de récupération de la version de marmottes.
//
//       Revision 3.28  2002/12/11 17:29:31  marmottes
//       DM-ID 12 Ajout de l'initialisation de pointeur.
//
//       Revision 3.27  2002/11/28 14:46:18  marmottes
//       DM-ID 0009 Ajout d'une interface Fortran pour la fonction de récupération de la version de la bibliothéque
//
//       Revision 3.26  2002/09/12 07:53:25  marmottes
//       Contournement d'un bogue, concernant les déclarations de fonctions, sur le compilateur SUN CC.
//
//       Revision 3.25  2002/09/09 13:43:24  marmottes
//       ajout de la fonction marmottesenregistrecorps_ (DM 0007)
//
//       Revision 3.24  2002/02/27 14:09:09  marmottes
//       suppression de la description de la révision insérée manuellement
//       et mise à jour du copyright CNES
//
//       Revision 3.23  2002/02/22 09:30:45  marmottes
//       Création de l'interface liée à la prise en compte de la DM0002 (fonction marmottesinitialisederive_)
//
//       Revision 3.22  2001/06/06 08:20:05  luc
//       prise en compte du déplacement de CallTrace vers club
//
//       Revision 3.21  2001/04/05 11:56:10  luc
//       amélioration du retour de MarmottesCriteresControlabilite
//
//       Revision 3.20  2001/04/04 12:31:30  luc
//       ajout de la fonction MarmottesCriteresControlabilite
//
//       Revision 3.19  2001/02/27 12:35:58  luc
//       ajout des fonctions MarmottesImposeAttitude et MarmottesImposeSpin
//       élimination de constructions d'objets inutiles
//
//       Revision 3.18  2000/11/13 10:14:05  luc
//       changement des fichiers d'inclusion
//
//       Revision 3.17  2000/09/13 11:00:21  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 3.16  2000/09/05 13:32:45  luc
//       ajout des fonctions marmottesactivetrace_ et marmottesdesactivetrace_
//
//       Revision 3.15  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 3.14  1999/08/20 07:37:29  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 3.13  1999/08/06 13:32:12  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 3.12  1999/04/23 11:46:33  luc
//       ajout de blocs try/catch dans toutes les fonctions d'interface
//
//       Revision 3.11  1998/07/31 08:40:03  luc
//       inclusion de MarmottesConfig.h
//
//       Revision 3.10  1998/07/15 12:38:14  luc
//       ajout des fonctions marmottesmodifiecible_, marmottesinitialisegyro_
//       et marmottesmodifiereference_
//
//       Revision 3.9  1998/06/24 19:55:24  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 3.8  1998/04/29 17:27:18  luc
//       utilisation de la même table entre le fortran et le C
//       correction des messages d'erreur sur les numéros
//
//       Revision 3.7  1998/04/26 18:18:41  luc
//       ajout d'une gestion d'unités de position et de vitesse variables
//
//       Revision 3.6  1997/09/21 19:41:03  luc
//       ajout de la possibilité de faire gérer les unités
//       par chaque instance de senseur
//
//       Revision 3.5  1997/08/20 16:51:06  luc
//       ajout d'une fonction de réinitialisation de simulateur Marmottes
//
//       Revision 3.4  1997/08/20 11:50:15  luc
//       remontée du choix de la résolution rapide par extrapolation
//       au niveau de l'utilisateur (résolution rapide autorisée par défaut)
//
//       Revision 3.3  1997/08/20 08:20:37  luc
//       ajout d'un en-tête de fichier
//       utilisation de ChaineSimple à la place de char *
//
//       Revision 3.2  1997/04/27 19:35:39  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 3.1  1997/01/28 12:42:48  luc
//       ajout de la vitesse et du spin à la création et à la réinitialisation
//       ajout de la vitesse pour les calculs d'attitude
//       création des interfaces fortran à la gestion des repères senseurs
//       (MarmottesNouveauRepere, MarmottesCalage, MarmottesRepereBase, MarmottesRepere)
//       factorisation de code
//       
//       Revision 2.2  1996/09/11 17:37:43  luc
//       ajout des interfaces fortran MarmottesCopie et MarmottesDeuxConsignes
//       
//       Revision 2.1  1996/07/31 17:15:01  luc
//       abandon des tools.h++ (Rogue Wave)
//       ajout des fonctions MarmottesNouveauRepere, MarmottesCalage,
//       MarmottesRepereBase, MarmottesRepere
//       (et des fonctions correspondantes de la classe Marmottes)
//       élimination de la limitation à quatre simulateurs simultanés
//       
//       Revision 1.2  1995/02/06 07:56:47  mercator
//       normalisation du quaternion donne par l'utilisateur a la creation
//       
//       Revision 1.1  1995/01/26 08:41:22  mercator
//       Initial revision
//
//$Version
//       $Id: InterfaceF.cpp,v 3.39 2003/10/22 13:00:38 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include "MarmottesConfigNoInstall.h"

#include "club/CallTrace.h"

#include "marmottes/InterfaceF.h"
#include "marmottes/TableInstances.h"
#include "marmottes/Marmottes.h"
#include "marmottes/MarmottesVersion.h"

static int CopieMessageF (BaseErreurs *ptrErreur,
                          char *messageErreur, long int lDeclMessage)
{ // copie d'un message d'erreur dans des variables fortran
  int code = ptrErreur->code ();

  // vérification des dépassements de capacité
  int l = strlen (ptrErreur->why ());
  if (l > lDeclMessage)
    l = lDeclMessage;

  // transfert des caractères
  (void) strncpy (messageErreur, ptrErreur->why (), l);
  (void) memset  (messageErreur + l, ' ', lDeclMessage - l);

  // remise à zéro de l'instance d'erreur
  ptrErreur->correction ();

  // on retourne le code d'erreur
  return code;

}

int marmottesactivetrace_ (char *fichier, char* messageErreur,
                           long int lDeclFichier, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // constitution de chaînes C à partir de chaînes fortran
    string sFic (fichier, lDeclFichier);
    string::size_type first = sFic.find_first_not_of (' ', 0);
    string::size_type last  = sFic.find_last_not_of  (' ', sFic.size ());
    string trimmed = sFic.substr (first, last + 1 - first);

    // activation du tracé des appels
    CallTrace::getInstance ()->activate (trimmed);

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesdesactivetrace_ (char* messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // désactivation du tracé des appels
    CallTrace::getInstance ()->deactivate ();

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottescreer_ (double&     date,
                     double      position [3],  double      vitesse [3],
                     double      attitude [4],  double      spin    [3],
                     const char* fichier,       const char* senseur1,
                     const char* senseur2,      const char* senseur3,
                     char*       messageErreur,
                     long int    lDeclFichier,  long int    lDeclSenseur1,
                     long int    lDeclSenseur2, long int    lDeclSenseur3,
                     long int    lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // recherche d'un numéro libre
    int        ident;
    Marmottes *simulateur = NULL;
    InstanceNonInitialisee (&ident, &simulateur);

    // constitution de chaînes C à partir de chaînes fortran
    string sFichier (fichier, lDeclFichier);
    string::size_type first = sFichier.find_first_not_of (' ', 0);
    string::size_type last  = sFichier.find_last_not_of  (' ', sFichier.size ());
    sFichier = sFichier.substr (first, last + 1 - first);

    string sSenseur1 (senseur1, lDeclSenseur1);
    first     = sSenseur1.find_first_not_of (' ', 0);
    last      = sSenseur1.find_last_not_of  (' ', sSenseur1.size ());
    sSenseur1 = sSenseur1.substr (first, last + 1 - first);

    string sSenseur2 (senseur2, lDeclSenseur2);
    first     = sSenseur2.find_first_not_of (' ', 0);
    last      = sSenseur2.find_last_not_of  (' ', sSenseur2.size ());
    sSenseur2 = sSenseur2.substr (first, last + 1 - first);

    string sSenseur3 (senseur3, lDeclSenseur3);
    first     = sSenseur3.find_first_not_of (' ', 0);
    last      = sSenseur3.find_last_not_of  (' ', sSenseur3.size ());
    sSenseur3 = sSenseur3.substr (first, last + 1 - first);

    // normalisation du quaternion d'entrée
    double norme = sqrt (attitude [0] * attitude [0]
                         + attitude [1] * attitude [1]
                         + attitude [2] * attitude [2]
                         + attitude [3] * attitude [3]);
    double attNormee [4];
    if (norme >= 1.0e-8)
    {
      attNormee [0] = attitude [0] / norme;
      attNormee [1] = attitude [1] / norme;
      attNormee [2] = attitude [2] / norme;
      attNormee [3] = attitude [3] / norme;
    }
    else
    {
      attNormee [0] = 1.0;
      attNormee [1] = 0.0;
      attNormee [2] = 0.0;
      attNormee [3] = 0.0;
    }

    // initialisation du simulateur
    simulateur->reinitialise (date,
                              VecDBL (position  [0],
                                      position  [1],
                                      position  [2]),
                              VecDBL (vitesse   [0],
                                      vitesse   [1],
                                      vitesse   [2]),
                              RotDBL (attNormee [0],
                                      attNormee [1],
                                      attNormee [2],
                                      attNormee [3]),
                              VecDBL (spin      [0],
                                      spin      [1],
                                      spin      [2]),
                              sFichier,
                              sSenseur1, sSenseur2, sSenseur3);

    // retour normal à la fonction appelante
    return ident;

  }

  catch (MarmottesErreurs e)
  {
    (void) CopieMessageF (&e, messageErreur, lDeclMessage);
    return 0;
  }

  catch (ClubErreurs e)
  {
    (void) CopieMessageF (&e, messageErreur, lDeclMessage);
    return 0;
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    (void) CopieMessageF (&e, messageErreur, lDeclMessage);
    return 0;
  }

}

int marmottescopie_ (int& ident, char* messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // recherche d'un numéro libre
    int        nouvIdent;
    Marmottes *nouvSim = NULL;
    InstanceNonInitialisee (&nouvIdent, &nouvSim);

    // copie du simulateur
    *nouvSim = *simulateur;

    // retour normal à la fonction appelante
    return nouvIdent;

  }

  catch (MarmottesErreurs e)
  {
    (void) CopieMessageF (&e, messageErreur, lDeclMessage);
    return 0;
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    (void) CopieMessageF (&e, messageErreur, lDeclMessage);
    return 0;
  }

}

int marmottesreinitialisation_ (int&        ident,         double&     date,
                                double      position [3],  double      vitesse [3],
                                double      attitude [4],  double      spin    [3],
                                const char* senseur1,      const char* senseur2,
                                const char* senseur3,      char*       messageErreur,
                                long int    lDeclSenseur1, long int    lDeclSenseur2,
                                long int    lDeclSenseur3, long int    lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur1 (senseur1, lDeclSenseur1);
    string::size_type first = sSenseur1.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur1.find_last_not_of  (' ', sSenseur1.size ());
    sSenseur1 = sSenseur1.substr (first, last + 1 - first);
    string sSenseur2 (senseur2, lDeclSenseur2);
    first     = sSenseur2.find_first_not_of (' ', 0);
    last      = sSenseur2.find_last_not_of  (' ', sSenseur2.size ());
    sSenseur2 = sSenseur2.substr (first, last + 1 - first);
    string sSenseur3 (senseur3, lDeclSenseur3);
    first     = sSenseur3.find_first_not_of (' ', 0);
    last      = sSenseur3.find_last_not_of  (' ', sSenseur3.size ());
    sSenseur3 = sSenseur3.substr (first, last + 1 - first);

    // normalisation du quaternion d'entrée
    double norme = sqrt (attitude [0] * attitude [0]
                         + attitude [1] * attitude [1]
                         + attitude [2] * attitude [2]
                         + attitude [3] * attitude [3]);
    double attNormee [4];
    if (norme >= 1.0e-8)
    {
      attNormee [0] = attitude [0] / norme;
      attNormee [1] = attitude [1] / norme;
      attNormee [2] = attitude [2] / norme;
      attNormee [3] = attitude [3] / norme;
    }
    else
    {
      attNormee [0] = 1.0;
      attNormee [1] = 0.0;
      attNormee [2] = 0.0;
      attNormee [3] = 0.0;
    }

    // réinitialisation du simulateur
    simulateur->reinitialise (date,
                              VecDBL (position  [0],
                                      position  [1],
                                      position  [2]),
                              VecDBL (vitesse   [0],
                                      vitesse   [1],
                                      vitesse   [2]),
                              RotDBL (attNormee [0],
                                      attNormee [1],
                                      attNormee [2],
                                      attNormee [3]),
                              VecDBL (spin      [0],
                                      spin      [1],
                                      spin      [2]),
                              simulateur->nomFichier (),
                              sSenseur1, sSenseur2, sSenseur3);

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottessenseurs_ (int&        ident,
                        const char* senseur1,      const char* senseur2,
                        const char* senseur3,      char*       messageErreur,
                        long int    lDeclSenseur1, long int    lDeclSenseur2,
                        long int    lDeclSenseur3, long int    lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur1 (senseur1, lDeclSenseur1);
    string::size_type first = sSenseur1.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur1.find_last_not_of  (' ', sSenseur1.size ());
    sSenseur1 = sSenseur1.substr (first, last + 1 - first);
    string sSenseur2 (senseur2, lDeclSenseur2);
    first     = sSenseur2.find_first_not_of (' ', 0);
    last      = sSenseur2.find_last_not_of  (' ', sSenseur2.size ());
    sSenseur2 = sSenseur2.substr (first, last + 1 - first);
    string sSenseur3 (senseur3, lDeclSenseur3);
    first     = sSenseur3.find_first_not_of (' ', 0);
    last      = sSenseur3.find_last_not_of  (' ', sSenseur3.size ());
    sSenseur3 = sSenseur3.substr (first, last + 1 - first);

    // modification des senseurs
    simulateur->senseurs (simulateur->nomFichier (),
                          sSenseur1, sSenseur2, sSenseur3);

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesnouveaurepere_ (int&     ident,        const char *senseur,
                             double   nouveau [4],  char       *messageErreur,
                             long int lDeclSenseur, long int    lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // normalisation du quaternion d'entrée
    double norme = sqrt (nouveau [0] * nouveau [0]
                         + nouveau [1] * nouveau [1]
                         + nouveau [2] * nouveau [2]
                         + nouveau [3] * nouveau [3]);
    double nouNorme [4];
    if (norme >= 1.0e-8)
    {
      nouNorme [0] = nouveau [0] / norme;
      nouNorme [1] = nouveau [1] / norme;
      nouNorme [2] = nouveau [2] / norme;
      nouNorme [3] = nouveau [3] / norme;
    }
    else
    {
      nouNorme [0] = 1.0;
      nouNorme [1] = 0.0;
      nouNorme [2] = 0.0;
      nouNorme [3] = 0.0;
    }

    // modification du repère
    simulateur->nouveauRepere (simulateur->nomFichier (), sSenseur,
                               RotDBL (nouNorme [0],
                                       nouNorme [1],
                                       nouNorme [2],
                                       nouNorme [3]));

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottescalage_ (int&     ident,        const char *senseur,
                      double&  calage,       char       *messageErreur,
                      long int lDeclSenseur, long int    lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // modification du calage
    simulateur->calage (simulateur->nomFichier (), sSenseur, calage);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesmodifiecible_ (int &        ident,
                            const char  *senseur,
                            const double cible [3],
                            char        *messageErreur,
                            long int     lDeclSenseur,
                            long int     lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // appel à la fonction modifieCible du senseur
    simulateur->modifieCible (simulateur->nomFichier (), sSenseur,
                              VecDBL (cible [0],
                                      cible [1],
                                      cible [2]));

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesinitialisegyro_ (int &        ident,
                              const char  *senseur,
                              double&      date,
                              double&      angle,
                              char        *messageErreur,
                              long int     lDeclSenseur,
                              long int     lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // appel à la fonction initialiseGyro du senseur
    simulateur->initialiseGyro (simulateur->nomFichier (), sSenseur,
                                date, angle);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (CantorErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesinitialisederive_ (int&  ident,
                                const char *senseur,
                                double &derive,
                                char* messageErreur,
                                long int lDeclSenseur, 
                                long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // initialisation de la dérive (offset) du senseur cinématique
    simulateur->initialiseDerive (simulateur->nomFichier (), sSenseur, derive);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (CantorErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesmodifiereference_ (int &        ident,
                                const char  *senseur,
                                const double reference [4],
                                char        *messageErreur,
                                long int     lDeclSenseur,
                                long int     lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // appel à la fonction modifieReference du senseur
    simulateur->modifieReference (simulateur->nomFichier (), sSenseur,
                                  RotDBL (reference [0],
                                          reference [1],
                                          reference [2],
                                          reference [3]));

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}


void marmottesdetruire_ (int& ident)
{
  try
  { // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);
    simulateur->desinitialise ();
  }

  catch (MarmottesErreurs e)
  { // on accepte les demandes de destruction d'instances inexistantes
    e.correction ();
  }
  catch (BaseErreurs e)
  { // on accepte les demandes de destruction d'instances inexistantes
    e.correction ();
  }
  catch (...)
  {}
}

int marmottesdeuxconsignes_ (int&    ident, double& date,
                             const double position [3],
                             const double vitesse  [3],
                             double& mesure_1,      double&      mesure_2,
                             double  attitude [4],  double       spin [3],
                             char*   messageErreur, long int     lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // résolution de l'attitude
    RotDBL attit;
    VecDBL vecSpin;
    simulateur->deuxConsignes (date,
                               VecDBL (position [0],
                                       position [1],
                                       position [2]),
                               VecDBL (vitesse  [0],
                                       vitesse  [1],
                                       vitesse  [2]),
                               mesure_1, mesure_2,
                               &attit, &vecSpin);

    // recopie des résultats
    attitude [0] = attit.q0 ();
    attitude [1] = attit.q1 ();
    attitude [2] = attit.q2 ();
    attitude [3] = attit.q3 ();

    spin     [0] = vecSpin.x ();
    spin     [1] = vecSpin.y ();
    spin     [2] = vecSpin.z ();

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesattitude_ (int&    ident, double& date,
                        const double position [3], const double vitesse  [3],
                        double& mesure_1,          double&      mesure_2,
                        double& mesure_3,
                        double  attitude [4],      double       spin [3],
                        char*   messageErreur,     long int     lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // résolution de l'attitude
    RotDBL attit;
    VecDBL vecSpin;
    simulateur->attitude (date,
                          VecDBL (position [0],
                                  position [1],
                                  position [2]),
                          VecDBL (vitesse  [0],
                                  vitesse  [1],
                                  vitesse  [2]),
                          mesure_1, mesure_2, mesure_3,
                          &attit, &vecSpin);

    // recopie des résultats
    attitude [0] = attit.q0 ();
    attitude [1] = attit.q1 ();
    attitude [2] = attit.q2 ();
    attitude [3] = attit.q3 ();

    spin     [0] = vecSpin.x ();
    spin     [1] = vecSpin.y ();
    spin     [2] = vecSpin.z ();

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (CantorErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesimposeattitude_ (int& ident, double& date,
                              const double position [3], const double vitesse [3],
                              const double attitude [4],
                              char* messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // forçage de l'attitude
    simulateur->imposeAttitude (date,
                                VecDBL (position [0],
                                        position [1],
                                        position [2]),
                                VecDBL (vitesse  [0],
                                        vitesse  [1],
                                        vitesse  [2]),
                                RotDBL (attitude [0],
                                        attitude [1],
                                        attitude [2],
                                        attitude [3]));

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (CantorErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesimposespin_ (int& ident, double& date,
                          const double position [3], const double vitesse [3],
                          const double spin [3],
                          char* messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // forçage du spin
    simulateur->imposeSpin (date,
                            VecDBL (position [0],
                                    position [1],
                                    position [2]),
                            VecDBL (vitesse  [0],
                                    vitesse  [1],
                                    vitesse  [2]),
                            VecDBL (spin [0],
                                    spin [1],
                                    spin [2]));

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (CantorErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesreperebase_ (int&     ident,        const char *senseur,
                          double   r [4],        char       *messageErreur,
                          long int lDeclSenseur, long int    lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // récupération du repère
    RotDBL repere;
    simulateur->repereBase (simulateur->nomFichier (), sSenseur,
                            &repere);

    // recopie des résultats
    r [0] = repere.q0 ();
    r [1] = repere.q1 ();
    r [2] = repere.q2 ();
    r [3] = repere.q3 ();

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesrepere_ (int&     ident,        const char *senseur,
                      double   r [4],        char       *messageErreur,
                      long int lDeclSenseur, long int    lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // récupération du repère
    RotDBL repere;
    simulateur->repere (simulateur->nomFichier (), sSenseur,
                        &repere);

    // recopie des résultats
    r [0] = repere.q0 ();
    r [1] = repere.q1 ();
    r [2] = repere.q2 ();
    r [3] = repere.q3 ();

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesmesure_ (int&        ident,        const char* senseur,
                      double&     mesure,       char*       messageErreur,
                      long int    lDeclSenseur, long int    lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // calcul de la mesure
    simulateur->mesure (simulateur->nomFichier (), sSenseur,
                        &mesure);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottescontrolable_ (int&      ident,        const char* senseur,
                           int&      controlable,  char*       messageErreur,
                           long int  lDeclSenseur, long int    lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // calcul de la controlabilité
    simulateur->controlable (simulateur->nomFichier (),
                             sSenseur, &controlable);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottescriterescontrolabilite_ (int&           ident,
                                      const char*    senseur,
                                      int&           inhibant,
                                      int&           eclipsant,
                                      double&        ecartFrontiere,
                                      int&           amplitudeSignificative,
                                      char*          messageErreur,
                                      long int       lDeclSenseur,
                                      long int       lDeclMessage
                                     )
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // calcul de la controlabilité
    Senseur::codeAstre codeInhibant, codeEclipsant;
    bool bAmplitudeSignificative;
    simulateur->criteresControlabilite (simulateur->nomFichier (),
                                        sSenseur,
                                        &codeInhibant, &codeEclipsant,
                                        &ecartFrontiere,
                                        &bAmplitudeSignificative);
    switch (codeInhibant)
    {
      case Senseur::soleil :
        inhibant = 2; // PARAMETER MrmSoleil dans marmdefs.f
        break;
      case Senseur::lune :
        inhibant = 3; // PARAMETER MrmLune dans marmdefs.f
        break;
      case Senseur::corpsCentral :
        inhibant = 4; // PARAMETER MrmCentral dans marmdefs.f
        break;
      case Senseur::aucunAstre :
        inhibant = 5; // PARAMETER MrmAucun dans marmdefs.f
        break;
      default :
        inhibant = 1; // PARAMETER MrmNonSig dans marmdefs.f
        break;
    }

    switch (codeEclipsant)
    {
      case Senseur::soleil :
        eclipsant = 2; // PARAMETER MrmSoleil dans marmdefs.f
        break;
      case Senseur::lune :
        eclipsant = 3; // PARAMETER MrmLune dans marmdefs.f
        break;
      case Senseur::corpsCentral :
        eclipsant = 4; // PARAMETER MrmCentral dans marmdefs.f
        break;
      case Senseur::aucunAstre :
        eclipsant = 5; // PARAMETER MrmAucun dans marmdefs.f
        break;
      default :
        eclipsant = 1; // PARAMETER MrmNonSig dans marmdefs.f
        break;
    }

    if (bAmplitudeSignificative)
      amplitudeSignificative = 1;
    else
      amplitudeSignificative = 0;

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesunitespositionvitesse_ (int& ident,
                                     const char *unitePos,
                                     const char *uniteVit,
                                     char *messageErreur,
                                     long int lDeclUnitePos,
                                     long int lDeclUniteVit,
                                     long int lDeclMessage
                                    )
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sUnitePos (unitePos, lDeclUnitePos);
    string::size_type first = sUnitePos.find_first_not_of (' ', 0);
    string::size_type last  = sUnitePos.find_last_not_of  (' ', sUnitePos.size ());
    sUnitePos = sUnitePos.substr (first, last + 1 - first);
    string sUniteVit (uniteVit, lDeclUniteVit);
    first     = sUniteVit.find_first_not_of (' ', 0);
    last      = sUniteVit.find_last_not_of  (' ', sUniteVit.size ());
    sUniteVit = sUniteVit.substr (first, last + 1 - first);

    // initialisation des unités
    simulateur->unitesPositionVitesse (sUnitePos, sUniteVit);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesrespecterconsignes_ (int& ident, const char* senseur,
                                  char* messageErreur,
                                  long int lDeclSenseur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // initialisation de la non-conversion
    simulateur->respecterConsignes (simulateur->nomFichier (), sSenseur);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesconvertirconsignes_ (int& ident, const char* senseur,
                                  char* messageErreur,
                                  long int lDeclSenseur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // initialisation de la conversion
    simulateur->convertirConsignes (simulateur->nomFichier (), sSenseur);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesrespectermesures_ (int& ident, const char* senseur,
                                char* messageErreur,
                                long int lDeclSenseur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // initialisation de la non-conversion
    simulateur->respecterMesures (simulateur->nomFichier (), sSenseur);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesconvertirmesures_ (int& ident, const char* senseur,
                                char* messageErreur,
                                long int lDeclSenseur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // constitution de chaînes C à partir de chaînes fortran
    string sSenseur (senseur, lDeclSenseur);
    string::size_type first = sSenseur.find_first_not_of (' ', 0);
    string::size_type last  = sSenseur.find_last_not_of  (' ', sSenseur.size ());
    sSenseur = sSenseur.substr (first, last + 1 - first);

    // initialisation de la conversion
    simulateur->convertirMesures (simulateur->nomFichier (), sSenseur);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmotteswmax_ (int&  ident,         double&  omega,
                    char* messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre de vitesse max
    simulateur->wMax (omega);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}


int marmottesconvergence_ (int&  ident,         double&  seuil,
                           char* messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre de convergence
    simulateur->convergence (seuil);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesdichotomie_ (int&  ident,         int&     tranches,
                          char* messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre de dichotomie
    simulateur->dichotomie (tranches);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesautoriseextrapolation_ (int&  ident,
                                     char* messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre d'extrapolation
    simulateur->autoriseExtrapolation ();

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesinterditextrapolation_ (int&  ident,
                                     char* messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre d'extrapolation
    simulateur->interditExtrapolation ();

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesenregistrecorps_ (int&    ident,
                               double& equatorialRadius, 
                               double& oblateness, 
                               double& rotationVelocity, 
                               double& moonRadius, 
                               double& sunRadius, 
                               TypeFuncTsidF tsidFunc, 
                               TypeFuncPosF  sunFunc, 
                               TypeFuncPosF  moonFunc, 
                               TypeFuncPosF  earthFunc,
                               char*   messageErreur, long int lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // transformation des entrées
    
    // accès aux fonctions utilisateurs
    simulateur->enregistreCorps (equatorialRadius, oblateness, rotationVelocity,
                                 moonRadius, sunRadius,
                                 (BodyEphemF::TypeFuncTsid *) tsidFunc,
                                 (BodyEphemF::TypeFuncPos *) sunFunc,
                                 (BodyEphemF::TypeFuncPos *) moonFunc,
                                 (BodyEphemF::TypeFuncPos *) earthFunc);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}

int marmottesversion_ (char *   version,
                       long int lDeclVersion)
{
  long int l = 0;
  int err    = 0;
  const char * versionComplete;

  // Vérification que la chaine Fortran ne soit pas
  // de longueur nulle.
  if (lDeclVersion <= 0 )
    return -1;

  // Initialisation de la chaine en paramétre.
  (void) memset (version, ' ', lDeclVersion);

  // Récupération de la version dans une chaine :
  // à cette étape, la version est compléte.
  versionComplete = marmottesVersion();
  l               = strlen(versionComplete);

  // La chaine passée en paramétre de sortie peut ne
  // pas être suffisamment dimensionnée. La fonction
  // strncpy tronque, si besoin, la chaine.
  if (l > lDeclVersion)
  {
     l = lDeclVersion;
     err = 1;
  }

  (void) strncpy(version, versionComplete, l);

  // La chaine est eventuellement nettoyée, si sa longueur
  // spécifiée le permet, sinon rien n'est fait.
  (void) memset  (version + l, ' ', lDeclVersion - l);

  return err;
}


double marmottestempssideralpardefaut_ (double*       t,
                                        double*       offset
                                       )
{
    return (BodyEphem::defaultFsiderealTime(t, offset));
}


void marmottespositionsoleilpardefaut_ (double*       t,
                                        double        pos[3]
                                       )
{
  BodyEphem::defaultFsunPosition(t, pos);
}


void marmottespositionterrepardefaut_ (double*       t,
                                       double        pos[3]
                                      )
{
  BodyEphem::defaultFearthPosition(t, pos);
}


void marmottespositionlunepardefaut_ (double*       t,
                                      double        pos[3]
                                     )
{
  BodyEphem::defaultFmoonPosition(t, pos);
}


int  marmotteslireparametres_  (int&           ident, 
                                double&        date,
                                double         position [3],
                                double         vitesse  [3],
                                double         attitude [4],
                                double         spin     [3],
                                char*          messageErreur, 
                                long int       lDeclMessage)
{
  try
  { // initialisation du message d'erreur
    (void) memset (messageErreur, ' ', lDeclMessage);

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    double date_lue(0.0);
    VecDBL position_lue(0.0, 0.0, 0.0);
    VecDBL vitesse_lue(0.0, 0.0, 0.0);
    RotDBL attitude_lue(0.0, 0.0, 0.0, 0.0);
    VecDBL spin_lu(0.0, 0.0, 0.0);
    
    // recuperation des valeurs courtantes des parametres
    simulateur->lireParametres(&date_lue, &position_lue, &vitesse_lue, &attitude_lue, &spin_lu);

    // affectation des valeurs retournees
    date = date_lue;
    position[0] = position_lue.x();
    position[1] = position_lue.y();
    position[2] = position_lue.z();
    vitesse[0]  = vitesse_lue.x();
    vitesse[1]  = vitesse_lue.y();
    vitesse[2]  = vitesse_lue.z();
    attitude[0] = attitude_lue.q0();
    attitude[1] = attitude_lue.q1();
    attitude[2] = attitude_lue.q2();
    attitude[3] = attitude_lue.q3();
    spin[0]     = spin_lu.x();
    spin[1]     = spin_lu.y();
    spin[2]     = spin_lu.z();

    return 0;
  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageF (&e, messageErreur, lDeclMessage);
  }

}
