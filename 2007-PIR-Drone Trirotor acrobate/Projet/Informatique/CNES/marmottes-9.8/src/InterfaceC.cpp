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
//>       InterfaceC.cpp
//$Resume
//       fichier d'implantation de l'interface C
//
//$Description
//       Module de définition des fonctions de l'interface C
//
//$Contenu
//>       static int CopieMessageC()           
//>       int MarmottesActiveTrace()           
//>       int MarmottesDesactiveTrace()        
//>       IdentMarmottes MarmottesCreer()      
//>       IdentMarmottes MarmottesCopie()      
//>       int MarmottesReinitialisation()      
//>       int MarmottesSenseurs()              
//>       int MarmottesNouveauRepere()         
//>       int MarmottesCalage()                
//>       int MarmottesModifieCible()          
//>       int MarmottesInitialiseGyro()        
//>       int MarmottesInitialiseDerive()      
//>       int MarmottesModifieReference()      
//>       void MarmottesDetruire()             
//>       int MarmottesDeuxConsignes()         
//>       int MarmottesAttitude()              
//>       int MarmottesImposeAttitude()        
//>       int MarmottesImposeSpin()            
//>       int MarmottesRepereBase()            
//>       int MarmottesRepere()                
//>       int MarmottesMesure()                
//>       int MarmottesControlable()           
//>       int MarmottesCriteresControlabilite()
//>       int MarmottesUnitesPositionVitesse() 
//>       int MarmottesRespecterConsignes()    
//>       int MarmottesConvertirConsignes()    
//>       int MarmottesRespecterMesures()      
//>       int MarmottesConvertirMesures()      
//>       int MarmottesWMax()                  
//>       int MarmottesConvergence()           
//>       int MarmottesDichotomie()            
//>       int MarmottesAutoriseExtrapolation() 
//>       int MarmottesInterditExtrapolation() 
//>       int MarmottesEnregistreCorps()       
//$Historique
//       $Log: InterfaceC.cpp,v $
//       Revision 1.22  2003/10/22 13:00:38  marmottes
//       DM 0027
//
//       Revision 1.21  2003/02/27 16:40:02  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.20  2003/02/04 16:28:08  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.19  2002/12/11 17:29:31  marmottes
//       DM-ID 12 Ajout de l'initialisation de pointeur.
//
//       Revision 1.18  2002/09/12 07:53:14  marmottes
//       Contournement d'un bogue, concernant les déclarations de fonctions, sur le compilateur SUN CC.
//
//       Revision 1.17  2002/09/09 13:41:42  marmottes
//       ajout de la fonction MarmottesEnregistreCorps (DM 0007)
//
//       Revision 1.16  2002/02/27 14:09:09  marmottes
//       suppression de la description de la révision insérée manuellement
//       et mise à jour du copyright CNES
//
//       Revision 1.15  2002/02/22 09:30:08  marmottes
//       Création de l'interface liée à la prise en compte de la DM0002 (fonction MarmottesInitialiseDerive)
//
//       Revision 1.14  2002/01/17 14:31:38  marmottes
//       (MarmottesActiveTrace) changement de signature
//
//       Revision 1.13  2001/06/06 08:20:26  luc
//       prise en compte du déplacement de CallTrace vers club
//
//       Revision 1.12  2001/04/05 11:55:54  luc
//       déclaration d'un type énuméré spécifique pour le retour des astres
//       perturbateurs dans la fonction MarmottesCriteresControlabilite
//
//       Revision 1.11  2001/04/04 12:30:55  luc
//       ajout de la fonction MarmottesCriteresControlabilite
//
//       Revision 1.10  2001/02/27 12:35:13  luc
//       ajout des fonctions MarmottesImposeAttitude et MarmottesImposeSpin
//
//       Revision 1.9  2000/11/13 10:14:06  luc
//       changement des fichiers d'inclusion
//
//       Revision 1.8  2000/09/05 13:33:12  luc
//       ajout des fonctions MarmottesActiveTrace et MarmottesDesactiveTrace
//
//       Revision 1.7  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 1.6  1999/08/20 07:37:29  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 1.5  1999/08/06 13:32:12  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.4  1999/04/23 11:46:18  luc
//       ajout de blocs try/catch dans toutes les fonctions d'interface
//
//       Revision 1.3  1998/07/15 12:37:07  luc
//       ajout des fonctions MarmottesModifieCible, MarmottesInitialiseGyro
//       et MarmottesModifieReference
//
//       Revision 1.2  1998/06/24 19:54:49  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.1  1998/05/14 11:55:46  luc
//       Initial revision
//
//$Version
//       $Id: InterfaceC.cpp,v 1.22 2003/10/22 13:00:38 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "MarmottesConfigNoInstall.h"
#include "club/CallTrace.h"
#include "marmottes/TableInstances.h"
#include "marmottes/InterfaceC.h"

static int CopieMessageC (BaseErreurs *ptrErreur,
                          char *messageErreur, long int lgMaxMessage)
{ // copie d'un message d'erreur dans une chaîne C
  int code = ptrErreur->code ();

  // vérification des dépassements de capacité
  int lg = strlen (ptrErreur->why ());
  if (lg >= lgMaxMessage)
    lg = lgMaxMessage - 1;

  // transfert des caractères
  (void) strncpy (messageErreur, ptrErreur->why (), lg);
  messageErreur [lg] = '\0';

  // remise à zéro de l'instance d'erreur
  ptrErreur->correction ();

  // on retourne le code d'erreur
  return code;

}

int MarmottesActiveTrace (const char *fichier,
                          char* messageErreur, int lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // activation du tracé des appels
    CallTrace::getInstance ()->activate (string (fichier));

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesDesactiveTrace (char* messageErreur, int lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // désactivation du tracé des appels
    CallTrace::getInstance ()->deactivate ();

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

IdentMarmottes MarmottesCreer        (double         date,
                                      const double   position [3],
                                      const double   vitesse  [3],
                                      const double   attitude [4],
                                      const double   spin     [3],
                                      const char    *fichier,
                                      const char    *senseur1,
                                      const char    *senseur2,
                                      const char    *senseur3,
                                      char          *messageErreur,
                                      int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // recherche d'un numéro libre
    IdentMarmottes ident;
    Marmottes     *simulateur = NULL;
    InstanceNonInitialisee (&ident, &simulateur);

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
                              fichier, senseur1, senseur2, senseur3);

    // retour normal à la fonction appelante
    return ident;

  }

  catch (MarmottesErreurs e)
  {
    (void) CopieMessageC (&e, messageErreur, lgMaxMessage);
    return 0;
  }

  catch (ClubErreurs e)
  {
    (void) CopieMessageC (&e, messageErreur, lgMaxMessage);
    return 0;
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    (void) CopieMessageC (&e, messageErreur, lgMaxMessage);
    return 0;
  }

}

IdentMarmottes MarmottesCopie (IdentMarmottes ident,
                               char *messageErreur, int lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // recherche d'un numéro libre
    IdentMarmottes nouvIdent;
    Marmottes     *nouvSim = NULL;
    InstanceNonInitialisee (&nouvIdent, &nouvSim);

    // copie du simulateur
    *nouvSim = *simulateur;

    // retour normal à la fonction appelante
    return nouvIdent;

  }

  catch (MarmottesErreurs e)
  {
    (void) CopieMessageC (&e, messageErreur, lgMaxMessage);
    return 0;
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    (void) CopieMessageC (&e, messageErreur, lgMaxMessage);
    return 0;
  }

}

int MarmottesReinitialisation (IdentMarmottes ident,
                               double         date,
                               const double   position [3],
                               const double   vitesse  [3],
                               const double   attitude [4],
                               const double   spin     [3],
                               const char    *senseur1,
                               const char    *senseur2,
                               const char    *senseur3,
                               char          *messageErreur,
                               int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

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
                              simulateur->nomFichier (),
                              senseur1, senseur2, senseur3);

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesSenseurs (IdentMarmottes ident,
                       const char    *senseur1,
                       const char    *senseur2,
                       const char    *senseur3,
                       char          *messageErreur,
                       int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification des senseurs
    MarmottesErreurs erreur;
    simulateur->senseurs (simulateur->nomFichier (),
                          senseur1, senseur2, senseur3);

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesNouveauRepere (IdentMarmottes ident,
                            const char    *senseur,
                            double         nouveau [4],
                            char          *messageErreur,
                            int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du repère
    simulateur->nouveauRepere (simulateur->nomFichier (), senseur,
                               RotDBL (nouveau [0],
                                       nouveau [1],
                                       nouveau [2],
                                       nouveau [3]));

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesCalage (IdentMarmottes ident,
                     const char    *senseur, double c,
                     char          *messageErreur,
                     int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du calage
    MarmottesErreurs erreur;
    simulateur->calage (simulateur->nomFichier (), senseur, c);

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesModifieCible (IdentMarmottes ident,
                           const char    *senseur,
                           double         cible [3],
                           char          *messageErreur,
                           int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    MarmottesErreurs erreur;
    simulateur->modifieCible (simulateur->nomFichier (), senseur,
                              VecDBL (cible [0],
                                      cible [1],
                                      cible [2]));

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesInitialiseGyro (IdentMarmottes ident,
                             const char    *senseur,
                             double         date,
                             double         angle,
                             char          *messageErreur,
                             int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    MarmottesErreurs erreur;
    simulateur->initialiseGyro (simulateur->nomFichier (), senseur,
                                date, angle);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesInitialiseDerive (IdentMarmottes ident,
                               const char    *senseur,
                               double         derive,
                               char          *messageErreur,
                               int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // initialisation de la dérive (offset) d'un senseur cinématique
    simulateur->initialiseDerive (simulateur->nomFichier (),
                                  senseur, derive);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesModifieReference (IdentMarmottes ident,
                               const char    *senseur,
                               double         reference [4],
                               char          *messageErreur,
                               int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    MarmottesErreurs erreur;
    simulateur->modifieReference (simulateur->nomFichier (), senseur,
                                  RotDBL (reference [0],
                                          reference [1],
                                          reference [2],
                                          reference [3]));

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

void MarmottesDetruire (IdentMarmottes ident)
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

}

int MarmottesDeuxConsignes (IdentMarmottes ident,
                            double         date,
                            const double   position [3],
                            const double   vitesse  [3],
                            double mesure_1, double mesure_2,
                            double         attitude [4], double spin [3],
                            char          *messageErreur,
                            int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // vérification du numéro
    Marmottes *simulateur = InstanceInitialisee (ident);

    // résolution de l'attitude
    MarmottesErreurs erreur;
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

    // recopie des resultats
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
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesAttitude (IdentMarmottes ident,
                       double         date,
                       const double   position [3], const double vitesse [3],
                       double mesure_1, double mesure_2, double mesure_3,
                       double         attitude [4], double spin [3],
                       char          *messageErreur,
                       int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

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

    // recopie des resultats
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
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (CantorErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesImposeAttitude (IdentMarmottes ident,
                             double         date,
                             const double   position [3], const double vitesse [3],
                             const double   attitude [4],
                             char          *messageErreur,
                             int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

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
                                RotDBL (attitude  [0],
                                        attitude  [1],
                                        attitude  [2],
                                        attitude  [3]));

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (CantorErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesImposeSpin (IdentMarmottes ident,
                         double         date,
                         const double   position [3], const double vitesse [3],
                         const double   spin [3],
                         char          *messageErreur,
                         int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

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
                            VecDBL (spin  [0],
                                    spin  [1],
                                    spin  [2]));

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (CantorErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesRepereBase (IdentMarmottes ident,
                         const char    *senseur, double r [4],
                         char          *messageErreur,
                         int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // récupération du repère de base
    RotDBL repere;
    simulateur->repereBase (simulateur->nomFichier (), senseur,
                            &repere);

    // recopie des résultats
    r [0] = repere.q0 ();
    r [1] = repere.q1 ();
    r [2] = repere.q2 ();
    r [3] = repere.q3 ();

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesRepere (IdentMarmottes ident, const char *senseur, double r [4],
                     char          *messageErreur,
                     int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // récupération du repère de base
    RotDBL repere;
    simulateur->repere (simulateur->nomFichier (), senseur,
                        &repere);

    // recopie des résultats
    r [0] = repere.q0 ();
    r [1] = repere.q1 ();
    r [2] = repere.q2 ();
    r [3] = repere.q3 ();

    // retour normal à la fonction appelante
    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesMesure   (IdentMarmottes ident,
                       const char    *senseur,
                       double        *mesure,
                       char          *messageErreur,
                       int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // calcul de la mesure
    simulateur->mesure (simulateur->nomFichier (), senseur,
                        mesure);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesControlable (IdentMarmottes ident,
                          const char    *senseur,
                          int           *controlable,
                          char          *messageErreur,
                          int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // calcul de la contrôlabilité
    simulateur->controlable (simulateur->nomFichier (), senseur,
                             controlable);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesCriteresControlabilite (IdentMarmottes  ident,
                                     const char     *senseur,
                                     MarmottesAstre *inhibant,
                                     MarmottesAstre *eclipsant,
                                     double         *ecartFrontiere,
                                     int            *amplitudeSignificative,
                                     char           *messageErreur,
                                     int             lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // calcul de la contrôlabilité
    Senseur::codeAstre codeInhib, codeEclips;
    bool bAmplitudeSignificative;
    simulateur->criteresControlabilite (simulateur->nomFichier (), senseur,
                                        &codeInhib, &codeEclips,
                                        ecartFrontiere,
                                        &bAmplitudeSignificative);

    switch (codeInhib)
    {
      case Senseur::soleil :
        *inhibant = MrmSoleil;
        break;
      case Senseur::lune :
        *inhibant = MrmLune;
        break;
      case Senseur::corpsCentral :
        *inhibant = MrmCentral;
        break;
      case Senseur::aucunAstre :
        *inhibant = MrmAucun;
        break;
      default :
        *inhibant = MrmNonSig;
        break;
    }

    switch (codeEclips)
    {
      case Senseur::soleil :
        *eclipsant = MrmSoleil;
        break;
      case Senseur::lune :
        *eclipsant = MrmLune;
        break;
      case Senseur::corpsCentral :
        *eclipsant = MrmCentral;
        break;
      case Senseur::aucunAstre :
        *eclipsant = MrmAucun;
        break;
      default :
        *eclipsant = MrmNonSig;
        break;
    }

    if (bAmplitudeSignificative)
      *amplitudeSignificative = 1;
    else
      *amplitudeSignificative = 0;

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesUnitesPositionVitesse (IdentMarmottes ident,
                                    const char    *unitePos,
                                    const char    *uniteVit,
                                    char          *messageErreur,
                                    int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // initialisation de la non-conversion
    simulateur->unitesPositionVitesse (unitePos, uniteVit);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesRespecterConsignes (IdentMarmottes ident,
                                 const char    *senseur,
                                 char          *messageErreur,
                                 int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // initialisation de la non-conversion
    simulateur->respecterConsignes (simulateur->nomFichier (),
                                    senseur);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesConvertirConsignes (IdentMarmottes ident,
                                 const char    *senseur,
                                 char          *messageErreur,
                                 int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // initialisation de la conversion
    simulateur->convertirConsignes (simulateur->nomFichier (),
                                    senseur);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesRespecterMesures (IdentMarmottes ident,
                               const char    *senseur,
                               char          *messageErreur,
                               int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // initialisation de la non-conversion
    simulateur->respecterMesures (simulateur->nomFichier (),
                                  senseur);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesConvertirMesures (IdentMarmottes ident,
                               const char    *senseur,
                               char          *messageErreur,
                               int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // initialisation de la conversion
    simulateur->convertirMesures (simulateur->nomFichier (),
                                  senseur);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (ClubErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesWMax (IdentMarmottes ident,
                   double         omega,
                   char          *messageErreur,
                   int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre de vitesse max
    simulateur->wMax (omega);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}


int MarmottesConvergence (IdentMarmottes ident,
                          double         seuil,
                          char          *messageErreur,
                          int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre de convergence
    simulateur->convergence (seuil);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesDichotomie  (IdentMarmottes ident,
                          int            tranches,
                          char          *messageErreur,
                          int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre de dichotomie
    simulateur->dichotomie (tranches);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesAutoriseExtrapolation  (IdentMarmottes ident,
                                     char *messageErreur, 
                                     int lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre d'extrapolation
    MarmottesErreurs erreur;
    simulateur->autoriseExtrapolation ();

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesInterditExtrapolation  (IdentMarmottes ident,
                                     char *messageErreur, 
                                     int lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // modification du paramètre d'extrapolation
    simulateur->interditExtrapolation ();

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesEnregistreCorps (IdentMarmottes            ident,
                              double                    equatorialRadius, 
                              double                    oblateness, 
                              double                    rotationVelocity, 
                              double                    moonRadius, 
                              double                    sunRadius, 
                              TypeFuncTsidC *tsidFunc, 
                              TypeFuncPosC  *sunFunc, 
                              TypeFuncPosC  *moonFunc, 
                              TypeFuncPosC  *earthFunc,
                              char                     *messageErreur,
                              int                       lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    // accès aux fonctions utilisateurs
    simulateur->enregistreCorps (equatorialRadius, oblateness, rotationVelocity,
                                 moonRadius, sunRadius,
                                 (BodyEphemC::TypeFuncTsid *) tsidFunc,
                                 (BodyEphemC::TypeFuncPos *) sunFunc,
                                 (BodyEphemC::TypeFuncPos *) moonFunc,
                                 (BodyEphemC::TypeFuncPos *) earthFunc);

    return 0;

  }

  catch (MarmottesErreurs e)
  {
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}

int MarmottesLireParametres  (IdentMarmottes ident, 
                              double         *date,
                              double         position [3],
                              double         vitesse  [3],
                              double         attitude [4],
                              double         spin     [3],
                              char           *messageErreur, 
                              int            lgMaxMessage)
{
  try
  { // initialisation du message d'erreur
    *messageErreur = '\0';

    // récupération de l'instance
    Marmottes *simulateur = InstanceInitialisee (ident);

    VecDBL position_lue(0.0, 0.0, 0.0);
    VecDBL vitesse_lue(0.0, 0.0, 0.0);
    RotDBL attitude_lue(0.0, 0.0, 0.0, 0.0);
    VecDBL spin_lu(0.0, 0.0, 0.0);
    
    // recuperation des valeurs courtantes des parametres
    simulateur->lireParametres(date, &position_lue, &vitesse_lue, &attitude_lue, &spin_lu);

    // affectation des valeurs retournees
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
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

  catch (...)
  {
    MarmottesErreurs e (MarmottesErreurs::erreur_non_reconnue);
    return CopieMessageC (&e, messageErreur, lgMaxMessage);
  }

}
