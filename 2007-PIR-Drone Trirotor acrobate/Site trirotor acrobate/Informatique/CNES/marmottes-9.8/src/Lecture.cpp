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
//>       Lecture.cpp
//
//$Resume
//       fichier d'implantation de la classe Lecture
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       static int ChampsTerminaux()                   
//>       static int LireReels()                         
//>       static int LireChaine()                        
//>       static int LireVecteurNorme()                  
//>       static int LireRotation()                      
//>       static int LireChamp()                         
//>       Parcelle *LireParcelle()                       
//>       static int LireStation()                       
//>       Senseur *LireSenseur()                         
//>       static int LireCible()          
//>       static int LireElementsOptiques()          
//>       static SenseurCartesien *LireSenseurCartesien()
//>       static SenseurDiedre *LireSenseurDiedre()      
//>       static SenseurVecteur *LireSenseurVecteur()    
//>       static SenseurElevation *LireSenseurElevation()
//>       static SenseurFonctionEchant1D *LireSenseurFonctionEchant1D()
//>       static SenseurFonctionGauss *LireSenseurFonctionGauss()
//>       static SenseurFonctionSinCard2 *LireSenseurFonctionSinCard2()
//>       static SenseurFonctionSinCardXY *LireSenseurFonctionSinCardXY()
//>       static SenseurLimbe *LireSenseurLimbe()        
//>       static SenseurAlpha *LireSenseurAlpha()        
//>       static SenseurDelta *LireSenseurDelta()        
//>       static SenseurCardan *LireSenseurCardan()      
//
//$Historique
//       $Log: Lecture.cpp,v $
//       Revision 2.48  2004/03/04 15:11:15  marmottes
//       ajout de "polaris-sans-eclipse" et "canopus-sans-eclipse"
//       dans la liste des cibles pour le message d'erreur cible_inconnue
//
//       Revision 2.47  2003/10/22 13:00:38  marmottes
//       DM 0027
//
//       Revision 2.46  2003/06/13 15:24:54  marmottes
//       FA-ID 0023 Ajout des interfaces des fonctions par defaut pour marmottesenregistrecorps
//
//       Revision 2.45  2003/02/27 16:48:16  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 2.44  2003/02/04 16:29:02  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 2.43  2002/12/11 17:29:31  marmottes
//       DM-ID 12 Ajout de l'initialisation de pointeur.
//
//       Revision 2.42  2002/02/04 15:31:19  marmottes
//       ajout d'une vérification de la cohérence entre champs d'inhibition et cible
//
//       Revision 2.41  2001/07/17 15:50:37  luc
//       séparation de la lecture de la cible et des éléments géométriques
//       ajout du senseur gain_sinus_cardinal_xy
//       ajout de la cible vitesse-sol-apparente
//
//       Revision 2.40  2001/06/22 07:12:45  luc
//       utilisation d'un axe et d'un angle pour spécifier l'intégration le
//       long d'une rotation
//
//       Revision 2.39  2001/06/06 08:17:26  luc
//       remontée des exceptions Cantor
//
//       Revision 2.38  2001/05/23 11:27:10  luc
//       ajout de la cible lune-sans-eclipse
//
//       Revision 2.37  2001/04/04 12:28:49  luc
//       remplacement de "horizon" par "limbe" (mots-clefs, classes et fonctions)
//       ajout des mots-clefs liés au corps central
//       ajout des mots-clefs position-sans-eclipse et direction-sans-eclipse
//
//       Revision 2.36  2001/03/26 11:19:04  luc
//       factorisation de la lecture des champs d'inhibition pour tous les
//       capteurs optiques,
//       renommage de la classe SenseurTerre en SenseurHorizon,
//       ajout de mots-clefs "horizon", "corps-central" et
//       "corps-central-soleil" en doublon de mots-clefs existants et en
//       prévision d'une évolution vers l'interplanétaire
//
//       Revision 2.35  2001/03/23 11:44:47  luc
//       correction d'un type de pointeur
//
//       Revision 2.34  2001/03/23 11:24:51  luc
//       suppression de fuites mémoire
//
//       Revision 2.33  2000/12/19 11:26:52  luc
//       correction d'une initialisation oubliée induisant des problèmes en cas
//       de lancement d'exception
//
//       Revision 2.32  2000/11/16 18:23:19  luc
//       ajout du senseur de fonction échantillonnée en radial
//       modifications « cosmétiques » du code
//
//       Revision 2.31  2000/11/13 10:09:59  luc
//       changement des fichiers d'inclusion
//       remplacement de la classe Champ par Field
//
//       Revision 2.30  2000/09/13 09:33:37  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 2.29  2000/06/07 14:05:07  luc
//       ajout de la lecture des senseurs de gain d'antenne en sinus cardianl
//       et en gaussienne
//
//       Revision 2.28  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 2.27  2000/01/07 12:30:13  luc
//       correction du nom du senseur dans les messages d'erreur
//
//       Revision 2.26  2000/01/06 17:01:50  luc
//       correction de la non reconnaissance des genres LRT-lacet, LRT-roulis
//       et LRT-tangage pour les senseurs de Cardan
//
//       Revision 2.25  1999/08/20 07:37:29  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 2.24  1999/08/06 13:32:13  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 2.23  1998/11/06 12:41:41  luc
//       ajout de la cible nadir
//
//       Revision 2.22  1998/07/31 08:37:14  luc
//       protection de l'inclusion de stdlib.h
//
//       Revision 2.21  1998/07/15 12:48:28  luc
//       lecture de tous les senseurs de Cardan par une fonction spécifique
//       ajout des gyros intégrateurs
//
//       Revision 2.20  1998/06/24 19:56:39  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 2.19  1998/05/14 11:56:27  luc
//       élimination des senseurs de tangente d'angles dièdres
//
//       Revision 2.18  1998/04/28 16:23:15  luc
//       ajout de senseurs de Cardan manquant dans un message d'erreur
//
//       Revision 2.17  1998/04/28 14:50:21  luc
//       correction de commentaires
//
//       Revision 2.16  1998/02/04 08:10:02  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout d'une cible de type station sol
//
//       Revision 2.15  1997/11/18 09:14:41  luc
//       modification des paramètres de configuration des
//       inhibitions pour les senseurs terre
//
//       Revision 2.14  1997/09/23 09:27:30  luc
//       ajout d'une gestion des unités de précision interne au senseur
//
//       Revision 2.13  1997/09/21 11:18:10  luc
//       remplacement des senseurs roulis, tangage, lacet
//       par une classe générale pour tous les angles de Cardan et variations
//
//       Revision 2.12  1997/09/15 14:12:26  luc
//       ajout du fichier SenseurCartesien.h
//
//       Revision 2.11  1997/09/03 09:27:28  luc
//       ajout d'une cible terre-soleil
//
//       Revision 2.10  1997/08/27 07:59:14  luc
//       ajout du senseur SenseurDiedreTan
//
//       Revision 2.9  1997/08/20 08:02:38  luc
//       ajout d'un en-tête de fichier
//       prise en compte de la réorganisation des fichiers .h de senseurs
//       utilisation de ChaineSimple à la place de char *
//       ajout des senseurs roulis, tangage, lacet
//
//       Revision 2.8  1997/04/30 06:56:08  luc
//       sauvegarde de la chaîne retournée par TraduitVersExterne
//       dans des variables locales avant tout appel de fonction
//       (la chaîne est modifiée si les fonctions appellent
//        également TraduitVersExterne)
//       
//       Revision 2.7  1997/04/27 19:34:47  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 2.6  1997/02/13 09:57:06  luc
//       ajout du moment comme cible observable
//       
//       Revision 2.5  1997/02/12 10:58:01  luc
//       ajout de la cible pseudo-soleil pour les senseurs optiques
//       
//       Revision 2.4  1997/02/10 11:20:06  luc
//       ajout de la vitesse en tant que cible observable par un senseur
//       
//       Revision 2.3  1996/10/03 14:38:20  luc
//       correction d'un message d'erreur
//       
//       Revision 2.2  1996/09/11 16:04:39  luc
//       passage du nom du senseur dans toutes les fonctions de lecture
//       
//       Revision 2.1  1996/07/31 16:07:05  luc
//       enrichissement de la syntaxe des fichiers de senseurs
//       - vecteurs lus en cartésiennes, en sphériques, ou à travers l'application d'une rotation
//       - rotations définies par axe et angle, "matrice", vecteur(s) et image(s)
//       - remplacement des connexes par des mosaïques
//       - ajout d'opérateurs d'union, de déplacement, de balayage, de marge
//       report au niveau du senseur terre de base de la séparation des inhibitions soleil/lune
//       abandon du senseur std15 (devenu inutile avec les nouveaux champs de vus plus riches)
//       
//       Revision 1.7  1996/05/22 15:12:58  luc
//       changement de libelle pour un type de senseur elevation -> plan_vecteur
//       (le libelle elevation engendrait des conflits avec le site en anglais)
//       
//       Revision 1.6  1996/05/15 14:41:07  luc
//       ajout du type de senseur "elevation"
//       
//       Revision 1.5  1996/03/21 17:30:36  luc
//       ajout du senseur STD15
//       
//       Revision 1.4  1996/03/15 12:00:49  luc
//       ajout d'une possibilité de ne pas préciser le champ d'inhibition
//       pour le senseur terre
//       dans ce cas on recopie le champ de vue (sans ses marges)
//       
//       Revision 1.3  1995/11/22 17:21:54  luc
//       initialisation du domaine de traduction dans les couches basses
//       appelables directement depuis le C (cf module "senseurs")
//       sans passer par Marmottes
//       
//       Revision 1.2  1995/09/12 06:25:05  mercator
//       ajout des pseudo-senseurs d'ascension droite et de declinaison
//       
//       Revision 1.1  1995/01/04 06:56:50  luc
//       Initial revision
//
//$Version
//       $Id: Lecture.cpp,v 2.48 2004/03/04 15:11:15 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "MarmottesConfigNoInstall.h"
#ifdef HAVE_CSTDLIB
#include <cstdlib>
#endif

#include <string>

#include "club/Traducteur.h"

#include "marmottes/Lecture.h"

#include "marmottes/MarmottesErreurs.h"
#include "marmottes/ParcelleElementaire.h"
#include "marmottes/ReunionEtParcelles.h"
#include "marmottes/ReunionOuParcelles.h"
#include "marmottes/SenseurAlpha.h"
#include "marmottes/SenseurCartesien.h"
#include "marmottes/SenseurCinematique.h"
#include "marmottes/SenseurDelta.h"
#include "marmottes/SenseurDiedre.h"
#include "marmottes/SenseurElevation.h"
#include "marmottes/SenseurFonctionEchant1D.h"
#include "marmottes/SenseurFonctionGauss.h"
#include "marmottes/SenseurFonctionSinCard2.h"
#include "marmottes/SenseurFonctionSinCardXY.h"
#include "marmottes/SenseurCardan.h"
#include "marmottes/SenseurGeometrique.h"
#include "marmottes/SenseurGyroInteg.h"
#include "marmottes/SenseurLimbe.h"
#include "marmottes/SenseurOptique.h"
#include "marmottes/SenseurVecteur.h"
#include "marmottes/StationCible.h"

static void
ChampsTerminaux (FichierStructure *blocPere, const string& nom,
                 int *ptrN, string *ptrNomMasque)
  throw (ClubErreurs, MarmottesErreurs);

static void
LireReels (FichierStructure *blocPere, const string& nom,
           int n, double tab [])
  throw (MarmottesErreurs);

static void
LireChaine (FichierStructure *blocPere, const string& nom,
            char *chaine, int maxChaine)
  throw (MarmottesErreurs);

static void
LireVecteurNorme (FichierStructure *blocPere, const string& nom,
                  VecDBL *ptrVecteur)
  throw (MarmottesErreurs);

static void
LireRotation (FichierStructure *blocPere, const string& nom,
              RotDBL *ptrRotation)
  throw (MarmottesErreurs);

static void
LireChamp (FichierStructure *blocPere, const string& nom,
           Field *ptrChamp)
  throw (CantorErreurs, MarmottesErreurs);

static void
LireStation (FichierStructure *blocPere, const string& nom,
             StationCible *ptrStation)
  throw (ClubErreurs, MarmottesErreurs);

static void
LireCible (FichierStructure *blocSenseur, const string& nom,
           bool champInhibitionSoleilPresent,
           bool champInhibitionLunePresent,
           bool champInhibitionCentralPresent,
           int *ptrCodeCible, StationCible *ptrStation, VecDBL *ptrObserve)
  throw (ClubErreurs, MarmottesErreurs);

static void
LireElementsOptiques (FichierStructure *blocSenseur,
                      Parcelle **adrPtrChampDeVue,
                      Parcelle **adrPtrChampInhibitionSoleil,
                      Parcelle **adrPtrChampInhibitionLune,
                      Parcelle **adrPtrChampInhibitionCentral,
                      double *ptrMargeEclipseSoleil,
                      double *ptrMargeEclipseLune,
                      double *ptrSeuilPhaseLune)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurCartesien *
LireSenseurCartesien (FichierStructure *blocSenseur, const string& nom,
                      const RotDBL& repere, const VecDBL& axeCalage,
                      double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurDiedre *
LireSenseurDiedre (FichierStructure *blocSenseur, const string& nom,
                   const RotDBL& repere, const VecDBL& axeCalage,
                   double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurVecteur *
LireSenseurVecteur (FichierStructure *blocSenseur, const string& nom,
                    const RotDBL& repere, const VecDBL& axeCalage,
                    double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurElevation *
LireSenseurElevation (FichierStructure *blocSenseur, const string& nom,
                      const RotDBL& repere, const VecDBL& axeCalage,
                      double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurFonctionEchant1D *
LireSenseurFonctionEchant1D (FichierStructure *blocSenseur, const string& nom,
                             const RotDBL& repere, const VecDBL& axeCalage,
                             double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurFonctionGauss *
LireSenseurFonctionGauss (FichierStructure *blocSenseur, const string& nom,
                          const RotDBL& repere, const VecDBL& axeCalage,
                          double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurFonctionSinCard2 *
LireSenseurFonctionSinCard2 (FichierStructure *blocSenseur, const string& nom,
                             const RotDBL& repere, const VecDBL& axeCalage,
                             double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurFonctionSinCardXY *
LireSenseurFonctionSinCardXY (FichierStructure *blocSenseur, const string& nom,
                              const RotDBL& repere, const VecDBL& axeCalage,
                              double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurLimbe *
LireSenseurLimbe (FichierStructure *blocSenseur, const string& nom,
                  const RotDBL& repere, const VecDBL& axeCalage,
                  double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

static SenseurAlpha *
LireSenseurAlpha (FichierStructure *blocSenseur, const string& nom,
                  const RotDBL& repere, const VecDBL& axeCalage,
                  double precision)
  throw (MarmottesErreurs);

static SenseurDelta *
LireSenseurDelta (FichierStructure *blocSenseur, const string& nom,
                  const RotDBL& repere, const VecDBL& axeCalage,
                  double precision)
  throw (MarmottesErreurs);

static SenseurCardan *
LireSenseurCardan (FichierStructure *blocSenseur, const string& nom,
                   const RotDBL& repere, const VecDBL& axeCalage,
                   double precision)
    throw (MarmottesErreurs);

static SenseurCinematique *
LireSenseurCinematique (FichierStructure *blocSenseur, const string& nom,
                        const RotDBL& repere, const VecDBL& axeCalage,
                        double precision)
  throw (CantorErreurs, MarmottesErreurs);

static SenseurGyroInteg *
LireSenseurGyroInteg (FichierStructure *blocSenseur, const string& nom,
                      const RotDBL& repere, const VecDBL& axeCalage,
                      double precision)
  throw (MarmottesErreurs);

static void
ChampsTerminaux (FichierStructure *blocPere, const string& nom,
                 int *ptrN, string *ptrNomMasque)
  throw (ClubErreurs, MarmottesErreurs)
{ 
  try
  {
    // recherche du nombre de champs d'un sous-bloc nommé d'un bloc père

    // extraction du bloc fils
    string nomFils (TraduitVersExterne (nom.c_str ()));
    FichierStructure blocFils (nomFils, blocPere);

    // vérification de la syntaxe du bloc
    if (! blocFils.terminal ())
      throw MarmottesErreurs (MarmottesErreurs::bloc_non_terminal,
                              blocFils.nomBloc ().c_str ());

    *ptrN         = blocFils.nombreChamps ();
    *ptrNomMasque = blocFils.nomBloc ();
  }
  
  catch (ClubErreurs ue)
  {
    if (ue.correspond (ClubErreurs::bloc_introuvable, "club"))
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable, ue.why ());
      ue.correction ();
      throw me;
    }
    else
    {
      throw ue;
    }
  }

}


static void
LireReels (FichierStructure *blocPere, const string& nom,
           int n, double tab [])
  throw (MarmottesErreurs)
{ 
  try
  {
    // extraction d'un tableau de réels depuis un sous-bloc
    // nommé d'un bloc père.
    
    const int maxTampon = 80;
    char      tampon [maxTampon];

    // extraction du bloc fils
    string nomFils (TraduitVersExterne (nom.c_str ()));
    FichierStructure blocFils (nomFils, blocPere);

    // vérification de la syntaxe du bloc
    if (! blocFils.terminal ())
      throw MarmottesErreurs (MarmottesErreurs::bloc_non_terminal,
                              blocFils.nomBloc ().c_str ());
    
    if (blocFils.nombreChamps () != n)
      throw MarmottesErreurs (MarmottesErreurs::nombre_champs_bloc,
                              blocFils.nomBloc ().c_str (),
                              blocFils.nombreChamps (), n);

    // lecture des champs
    for (int i = 1; i <= n; i++)
    { 
      blocFils.champ (i, tampon, maxTampon);
      tab [i-1] = atof (tampon); 
    }
  }
  
  catch (ClubErreurs ue)
  { 
    if (ue.correspond (ClubErreurs::bloc_introuvable, "club"))
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable,
                           ue.why ());
      ue.correction ();
      throw me;
    }
    else
    {
      MarmottesErreurs me (ue.why ());
      ue.correction ();
      throw me;
    }
  }
}


static void
LireChaine (FichierStructure *blocPere, const string& nom,
            char *chaine, int maxChaine)
  throw (MarmottesErreurs)
{ 
  try
  {
    // extraction d'une chaîne depuis un sous-bloc nommé d'un bloc père.

    // extraction du bloc fils
    string nomFils (TraduitVersExterne (nom.c_str ()));
    FichierStructure blocFils (nomFils, blocPere);

    // vérification de la syntaxe du bloc
    if (! blocFils.terminal ())
      throw MarmottesErreurs (MarmottesErreurs::bloc_non_terminal,
                              blocFils.nomBloc ().c_str ());

    if (blocFils.nombreChamps () != 1)
      throw MarmottesErreurs (MarmottesErreurs::nombre_champs_bloc,
                              blocFils.nomBloc ().c_str (),
                              blocFils.nombreChamps (), 1);

    // lecture de la chaîne
    blocFils.champ (1, chaine, maxChaine);
  }

  catch (ClubErreurs ue)
  { 
    if (ue.correspond (ClubErreurs::bloc_introuvable, "club"))
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable,
                           ue.why ());
      ue.correction ();
      throw me;
    }
    else
    {
      MarmottesErreurs me (ue.why ());
      ue.correction ();
      throw me; 
    }
  }
}


static void
LireVecteurNorme (FichierStructure *blocPere, const string& nom,
                  VecDBL *ptrVecteur)
  throw (MarmottesErreurs)
{ 
  try
  {
    // extraction d'un vecteur depuis un sous-bloc nommé d'un bloc père.

    // extraction du bloc fils
    string nomFils (TraduitVersExterne (nom.c_str ()));
    FichierStructure blocFils (nomFils, blocPere);

    // un vecteur peut être défini par :
    //  - l'image d'un autre vecteur par une rotation ;
    //  - ses coordonnées sphériques ;
    //  - ses coordonnées cartésiennes.
    string nomRot (TraduitVersExterne ("rotation"));
    if (blocFils.contientSousBloc (nomRot.c_str ()))
    { 
      // le vecteur est probablement défini par l'application d'une rotation
      RotDBL r;
      LireRotation (&blocFils, "rotation", &r);

      VecDBL v;
      LireVecteurNorme (&blocFils, "de", &v);

      // composition
      *ptrVecteur = r (v);     
    }
    else if ((blocFils.terminal ()) && (blocFils.nombreChamps () == 2))
    { 
      // le vecteur est défini par ses coordonnées sphériques
      double tab [2];
      LireReels (blocPere, nom, 2, tab);

      *ptrVecteur = VecDBL (radians (tab [0]), radians (tab [1]));
    }
    else
    { 
      // le vecteur est probablement défini par ses coordonnées cartésiennes
      // (on teste ce cas quand tout le reste a échoué, car c'est
      //  le plus explicite des messages d'erreurs)
      double v [3];
      LireReels (blocPere, nom, 3, v);

      double norme2 = v [0] * v [0] + v [1] * v [1] + v [2] * v [2];
      if (norme2 < 1.0e-10)
        throw MarmottesErreurs (MarmottesErreurs::vecteur_nul,
                                blocFils.nomBloc ().c_str ());

      double inv  = 1.0 / sqrt (norme2);
      *ptrVecteur = VecDBL (inv * v [0], inv * v [1], inv * v [2]);
    }
  }

  catch (ClubErreurs ue)
  {
    if (ue.correspond (ClubErreurs::bloc_introuvable, "club"))
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable,
                           ue.why ());
      ue.correction ();
      throw me;
    }
    else
    {
      MarmottesErreurs me (ue.why ());
      ue.correction ();
      throw me;
    }
  }
}


static void
LireRotation (FichierStructure *blocPere, const string& nom,
              RotDBL *ptrRotation)
  throw (MarmottesErreurs)
{ 
  try
  {
    // extraction d'une rotation depuis un sous-bloc nommé d'un bloc père.

    // extraction du bloc fils
    string nomFils (TraduitVersExterne (nom.c_str ()));
    FichierStructure blocFils (nomFils, blocPere);

    try
    {
      // une rotation peut être définie par :
      //  - un quaternion ;
      //  - la transformée du repère canonique (équivaut à une matrice) ;
      //  - la composition de deux rotations ;
      //  - deux vecteurs et leurs images ;
      //  - un vecteur et son image ;
      //  - un axe et un angle.
      if (blocFils.terminal ())
      { // la rotation est définie par un quaternion
        double q [4];
        LireReels (blocPere, nom, 4, q);

        double norme2 = q [0] * q [0] + q [1] * q [1]
          + q [2] * q [2] + q [3] * q [3];
        if (norme2 < 1.0e-10)
          throw MarmottesErreurs (MarmottesErreurs::quaternion_nul,
                                  blocFils.nomBloc ().c_str ());
        else
        { // construction d'un quaternion normalisé
          double inverse = 1.0 / sqrt (norme2);
          *ptrRotation = RotDBL (inverse * q [0], inverse * q [1],
                                 inverse * q [2], inverse * q [3]);
        }

      }
      else
      { 
        string nomEssai (TraduitVersExterne ("i"));
      
        if (blocFils.contientSousBloc (nomEssai.c_str ()))
        { // la rotation est définie par l'image des axes du repère canonique
          double matrice [3] [3];

          // on ne lit pas les vecteurs par LireVecteurNorme, il est plus prudent
          // d'orthogonaliser la matrice en bloc que vecteur par vecteur
          LireReels (&blocFils, "i", 3, matrice [0]);
          LireReels (&blocFils, "j", 3, matrice [1]);
          LireReels (&blocFils, "k", 3, matrice [2]);

          // construction de la rotation
          // (on accepte une correction de 1e-6 pour rendre la matrice orthogonale)
          *ptrRotation = RotDBL (matrice, 1.0e-6);
        
        }
        else
        { 
          nomEssai = TraduitVersExterne ("rotation");
        
          if (blocFils.contientSousBloc (nomEssai.c_str ()))
          { // la rotation est définie par la composition de deux rotations
            RotDBL r1;
            RotDBL r2;
            LireRotation (&blocFils, "rotation", &r1);
            LireRotation (&blocFils, "de",       &r2);
          
            // composition
            *ptrRotation = r1 (r2);
          
          }
          else
          { 
            nomEssai = TraduitVersExterne ("v_base_1");
          
            if (blocFils.contientSousBloc (nomEssai.c_str ()))
            { // la rotation est définie par deux vecteurs et leurs images
              VecDBL u1, u2, v1, v2;
            
              LireVecteurNorme (&blocFils, "v_base_1",  &u1);
              LireVecteurNorme (&blocFils, "v_base_2",  &u2);
              LireVecteurNorme (&blocFils, "v_image_1", &v1);
              LireVecteurNorme (&blocFils, "v_image_2", &v2);
            
              *ptrRotation = RotDBL (u1, u2, v1, v2);
            
            }
            else
            { 
              nomEssai = TraduitVersExterne ("v_base");
            
              if (blocFils.contientSousBloc (nomEssai.c_str ()))
              { // la rotation est définie par un vecteur et son image
                VecDBL u, v;
                LireVecteurNorme (&blocFils, "v_base",  &u);
                LireVecteurNorme (&blocFils, "v_image", &v);
              
                // construction d'une des rotations transformant u en v
                // (il y en a une infinité d'autre ...)
                *ptrRotation = RotDBL (u, v);
              
              }
              else
              { // la rotation est probablement définie par un axe et un angle
                // (on teste ce cas quand tout le reste a échoué, car c'est
                //  le plus explicite des messages d'erreurs)
                VecDBL axe;
                double angle;
                LireVecteurNorme (&blocFils, "axe", &axe);
                LireReels        (&blocFils, "angle", 1, &angle);
              
                // constitution du repère
                *ptrRotation = RotDBL (axe, radians (angle), 1.0);
              
              }
            }
          }
        }
      }
    }

    catch (CantorErreurs ce)
    { // la construction de la rotation a engendré une erreur
      MarmottesErreurs me (MarmottesErreurs::rotation_bloc,
                           blocFils.nomBloc ().c_str ());      
      ce.correction ();
      throw me;
    }

  }

  catch (ClubErreurs ue)
  { 
    if (ue.correspond (ClubErreurs::bloc_introuvable, "club"))
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable,
                           ue.why ());
      ue.correction ();
      throw me;
    }
    else
    {
      MarmottesErreurs me (ue.why ());
      ue.correction ();
      throw me;
    }
  }
}


static void
LireChamp (FichierStructure *blocPere, const string& nom,
           Field *ptrChamp)
  throw (CantorErreurs, MarmottesErreurs)
{ 

  try
  {
    // extraction d'un champ depuis un sous-bloc nommé d'un bloc père.

    // extraction du bloc fils
    string nomFils (TraduitVersExterne (nom.c_str ()));
    FichierStructure blocFils (nomFils, blocPere);

    // un champ peut être défini par :
    //  - l'intégration d'un autre champ selon une rotation ;
    //  - le déplacement d'un autre champ selon une rotation ;
    //  - la prise d'une marge sur un autre champ ;
    //  - l'intersection de deux champs ;
    //  - la réunion de deux champs ;
    //  - la "différence" de deux champs ;
    //  - un cône.
    string nomEssai (TraduitVersExterne ("balayage"));
    if (blocFils.contientSousBloc (nomEssai.c_str ()))
    { // définition par intégration d'un champ élémentaire
      LireChamp (&blocFils, "de", ptrChamp);

      VecDBL axe;
      double angle;
      FichierStructure blocBalayage (nomEssai, &blocFils);
      LireVecteurNorme (&blocBalayage, "axe", &axe);
      LireReels (&blocBalayage, "angle", 1, &angle);
      
      ptrChamp->spread (axe, radians (angle));
      
    }
    else
    { 
      nomEssai = TraduitVersExterne ("rotation");
      
      if (blocFils.contientSousBloc (nomEssai.c_str ()))
      { // définition par déplacement d'un champ élémentaire
        LireChamp (&blocFils, "de", ptrChamp);

        RotDBL operateur;
        LireRotation (&blocFils, "rotation", &operateur);
        
        ptrChamp->rotate (operateur);
        
      }
      else
      { 
        nomEssai = TraduitVersExterne ("marge");
        
        if (blocFils.contientSousBloc (nomEssai.c_str ()))
        { // définition par prise d'une marge sur un champ élémentaire
          LireChamp (&blocFils, "sur", ptrChamp);
          
          double marge;
          LireReels (&blocFils, "marge", 1, &marge);
          
          ptrChamp->applyMargin (radians (marge));
          
        }
        else
        { 
          nomEssai = TraduitVersExterne ("inter");

          if (blocFils.contientSousBloc (nomEssai.c_str ()))
          { // définition par intersection de champs
          LireChamp (&blocFils, "", ptrChamp);

          Field c2;
          LireChamp (&blocFils, "inter", &c2);
          
          *ptrChamp *= c2;      
    
          }
          else
          { 
            nomEssai = TraduitVersExterne ("union");

            if (blocFils.contientSousBloc (nomEssai.c_str ()))
            { // définition par réunion de champs
            LireChamp (&blocFils, "", ptrChamp);

            Field c2;
            LireChamp (&blocFils, "union", &c2);
            
            *ptrChamp += c2;
            
            }
            else
            { 
              nomEssai = TraduitVersExterne ("sauf");

              if (blocFils.contientSousBloc (nomEssai.c_str ()))
              { // définition par différence de champs
                LireChamp (&blocFils, "", ptrChamp);

                Field c2;
                LireChamp (&blocFils, "sauf", &c2);

                *ptrChamp -= c2;
                
              }
              else
              { // c'est probablement un cône simple
                string nomCone (TraduitVersExterne ("cone"));
                FichierStructure blocCone (nomCone, &blocFils);

                // recherche de l'axe
                VecDBL axe;
                LireVecteurNorme (&blocCone, "axe", &axe);
                
                // recherche de l'angle
                double angle;
                LireReels (&blocCone, "angle", 1, &angle);
                
                // empaquetage dans un champ
                *ptrChamp = Field (Cone (axe, radians (angle)));
                
              }
            }
          }
        }
      }
    }
  }

  catch (ClubErreurs ue)
  {
    if (ue.correspond (ClubErreurs::bloc_introuvable, "club"))
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable,
                           ue.why ());
      ue.correction ();
      throw me;
    }
    else
    {
      MarmottesErreurs me (ue.why ());
      ue.correction ();
      throw me;
    }
  }
}


Parcelle *
LireParcelle (FichierStructure *blocPere, const string& nom)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  Parcelle *p1 = 0;
  Parcelle *p2 = 0;
  try
  {
    // extraction d'une parcelle depuis un sous-bloc nommé d'un bloc père.

    // extraction du bloc fils
    FichierStructure blocFils (nom, blocPere);
    
    // une parcelle peut être définie par :
    //  - une réunion "et" de parcelles ;
    //  - une réunion "ou" de parcelles ;
    //  - prise d'une marge sur une parcelle ;
    //  - un champ.
    string nomEssai (TraduitVersExterne ("et"));
    if (blocFils.contientSousBloc (nomEssai.c_str ()))
    { // c'est une réunion "et" de parcelles
      p1 = LireParcelle (&blocFils, string (""));
      p2 = LireParcelle (&blocFils, nomEssai);

      return new ReunionEtParcelles (p1, p2);

    }
    else
    { 
      nomEssai = TraduitVersExterne ("ou");
      
      if (blocFils.contientSousBloc (nomEssai.c_str ()))
      { // c'est une réunion "ou" de parcelles
        p1 = LireParcelle (&blocFils, string (""));
        p2 = LireParcelle (&blocFils, nomEssai);

        return new ReunionOuParcelles (p1, p2);
        
      }
      else
      { 
        nomEssai = TraduitVersExterne ("marge");
        
        if (blocFils.contientSousBloc (nomEssai.c_str ()))
        { // définition par prise d'une marge sur une parcelle élémentaire
          string nomSur (TraduitVersExterne ("sur"));
          
          p1 = LireParcelle (&blocFils, nomSur);

          double marge;
          LireReels (&blocFils, "marge", 1, &marge);

          p1->appliqueMarge (radians (marge));

          return p1;

        }
        else
        { // ce doit être une parcelle élémentaire: un champ
          Field c;
          LireChamp (blocPere, nom, &c);
          return (Parcelle *) new ParcelleElementaire (c);
        }
      }
    }
  }

  catch (ClubErreurs ue)
  { 
    if (ue.correspond (ClubErreurs::bloc_introuvable, "club"))
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable,
                           ue.why ());
      ue.correction ();
      throw me;
    }
    else
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable,
                           ue.why ());
      ue.correction ();
      throw me;
    }
  }

  catch (...)
  {
    if (p1)
      delete p1;    
    if (p2)
      delete p2;
    throw;
  }
}


static void
LireStation (FichierStructure *blocPere, const string& nom,
             StationCible *ptrStation)
  throw (ClubErreurs, MarmottesErreurs)
{ 
  double *tab = 0;
  try
  {
    // extraction d'une description de station depuis un sous-bloc
    // nommé d'un bloc père.

    // extraction du bloc fils
    string nomFils (TraduitVersExterne (nom.c_str ()));
    FichierStructure blocFils (nomFils, blocPere);

    // conditions atmosphériques
    double pression, temperature, hygrometrie;
    LireReels (&blocFils, "pression",    1, &pression);
    LireReels (&blocFils, "temperature", 1, &temperature);
    LireReels (&blocFils, "hygrometrie", 1, &hygrometrie);
    
    // coordonnées de la station
    double longitude, latitude, altitude;
    LireReels (&blocFils, "longitude", 1, &longitude);
    LireReels (&blocFils, "latitude",  1, &latitude);
    LireReels (&blocFils, "altitude",  1, &altitude);
    longitude = radians (longitude);
    latitude  = radians (latitude);
    
    // masque d'antenne
    int nbChamps;
    string nomMasque;
    // L'appel de ChampsTerminaux peut "lancer" un ClubErreurs
    ChampsTerminaux (&blocFils, "masque", &nbChamps, &nomMasque);
    if ((nbChamps < 2) || (nbChamps % 2))
      throw MarmottesErreurs (MarmottesErreurs::points_masque,
                              nbChamps, nomMasque.c_str ());
    tab = new double [nbChamps];
    LireReels (&blocFils, "masque", nbChamps, tab);

    double *tabAz = new double [nbChamps / 2];
    double *tabSi = new double [nbChamps / 2];
    for (int i = 0; i < nbChamps / 2; i++)
    { // répartition des données dans les tables azimut et site
      tabAz [i] = radians (tab [2 * i]);
      tabSi [i] = radians (tab [2 * i + 1]);
    }
    delete [] tab;
    
    // construction effective de la station
    *ptrStation = StationCible (pression, temperature, hygrometrie,
                                longitude, latitude, altitude,
                                nbChamps / 2, tabAz, tabSi);
    delete [] tabAz;
    delete [] tabSi;
  }

  catch (ClubErreurs ue)
  {
    if (ue.correspond (ClubErreurs::bloc_introuvable, "club"))
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable,
                           ue.why ());
      ue.correction ();
      throw me;
    }
    else
    {
      MarmottesErreurs me (ue.why ());
      ue.correction ();
      throw me;
    }
  }

  catch (...)
  {
    if (tab)
      delete [] tab;
    throw;
  }
}


Senseur *
LireSenseur (FichierStructure *fichier, const string& nom)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ 
  try
  {
    // initialisation du domaine de traduction (pour analyser les mots-clefs)
    InitDomaineMarmottes ();
    
    // recherche d'un bloc ayant le nom demandé
    FichierStructure blocSenseur (nom, fichier);

    // recherche des paramètres communs à tous les types de senseurs
    RotDBL repere;
    LireRotation (&blocSenseur, "repere", &repere);

    double precision;
    LireReels (&blocSenseur, "precision", 1, &precision);

    VecDBL axeCalage (0.0, 0.0, 0.0);
    string nomCalage (TraduitVersExterne ("axe_calage"));
    if (blocSenseur.contientSousBloc (nomCalage.c_str ()))
    { 
      // un axe de calage est prévu
      LireVecteurNorme (&blocSenseur, "axe_calage",  &axeCalage);
    }

    // recherche du type du senseur
    const int   maxTampon = 80;
    char        tampon [maxTampon];
    LireChaine (&blocSenseur, "type", tampon, maxTampon);

    // sélection de la classe adaptée au type de senseur
    string codeType (TraduitVersInterne (tampon));
    if ((codeType == "limbe") || (codeType == "terre"))
      return LireSenseurLimbe       (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else if (codeType == "cartesien")
      return LireSenseurCartesien   (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else if (codeType == "diedre")
      return LireSenseurDiedre      (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else if (codeType == "vecteur")
      return LireSenseurVecteur     (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else if (codeType == "plan_vecteur")
      return LireSenseurElevation   (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else if (codeType == "gain_echantillonne_1D")
      return LireSenseurFonctionEchant1D (&blocSenseur,
                                          nom, repere, axeCalage, precision);
    else if (codeType == "gain_gauss")
      return LireSenseurFonctionGauss (&blocSenseur,
                                       nom, repere, axeCalage, precision);
    else if (codeType == "gain_sinus_cardinal_2")
      return LireSenseurFonctionSinCard2 (&blocSenseur,
                                          nom, repere, axeCalage, precision);
    else if (codeType == "gain_sinus_cardinal_xy")
      return LireSenseurFonctionSinCardXY (&blocSenseur,
                                           nom, repere, axeCalage, precision);
    else if (codeType == "ascension_droite")
      return LireSenseurAlpha       (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else if (codeType == "declinaison")
      return LireSenseurDelta       (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else if (codeType == "cinematique")
      return LireSenseurCinematique (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else if (codeType == "gyro_integrateur")
      return LireSenseurGyroInteg   (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else if (codeType == "cardan")
      return LireSenseurCardan      (&blocSenseur,
                                     nom, repere, axeCalage, precision);
    else
    { 
      throw MarmottesErreurs (MarmottesErreurs::type_inconnu,
                              codeType.c_str (),
                              "limbe", "terre", "cartesien", "diedre",
                              "vecteur", "plan_vecteur",
                              "gain_echantillonne_1D", "gain_gauss",
                              "gain_sinus_cardinal_2",
                              "ascension_droite", "declinaison",
                              "cinematique", "gyro_integrateur", "cardan",
                              (char *) 0);
    }
  }

  catch (ClubErreurs ue)
  { 
    if (ue.correspond (ClubErreurs::bloc_introuvable, "club"))
    {
      MarmottesErreurs me (MarmottesErreurs::bloc_introuvable,
                           ue.why ());
      ue.correction ();
      throw me;
    }
    else
      throw;
  }
}


static void
LireCible (FichierStructure *blocSenseur, const string& nom,
           bool champInhibitionSoleilPresent,
           bool champInhibitionLunePresent,
           bool champInhibitionCentralPresent,
           int *ptrCodeCible, StationCible *ptrStation, VecDBL *ptrObserve)
  throw (ClubErreurs, MarmottesErreurs)
{

  // extraction de la cible
  const int   maxTampon = 80;
  char        tampon [maxTampon];
  LireChaine (blocSenseur, "cible", tampon, maxTampon);

  // détermination du code de la cible
  string interne (TraduitVersInterne (tampon));
  if (interne == "soleil")
    *ptrCodeCible = SenseurOptique::codeSoleil;
  else if ((interne == "soleil-sans-eclipse") || (interne == "pseudo-soleil"))
    *ptrCodeCible = SenseurOptique::codeSoleilSansEclipse;
  else if ((interne == "corps-central-soleil") || (interne == "terre-soleil"))
    *ptrCodeCible = SenseurOptique::codeCorpsCentralSoleil;
  else if (interne == "lune")
    *ptrCodeCible = SenseurOptique::codeLune;
  else if (interne == "lune-sans-eclipse")
    *ptrCodeCible = SenseurOptique::codeLuneSansEclipse;
  else if (interne == "corps-central")
    *ptrCodeCible = SenseurOptique::codeCorpsCentral;
  else if (interne == "terre")
    *ptrCodeCible = SenseurOptique::codeTerre;
  else if (interne == "nadir")
    *ptrCodeCible = SenseurOptique::codeNadir;
  else if (interne == "vitesse-sol-apparente")
  { // la cible est la vitesse d'un point au sol,
    // il faut extraire les moyens de le calculer
    *ptrCodeCible = SenseurOptique::codeVitesseSolApparente;
    LireVecteurNorme (blocSenseur, "observe", ptrObserve);
  }
  else if (interne == "polaris")
    *ptrCodeCible = SenseurOptique::codePolaire;
  else if (interne == "canopus")
    *ptrCodeCible = SenseurOptique::codeCanope;
  else if (interne == "vitesse")
    *ptrCodeCible = SenseurOptique::codeVitesse;
  else if (interne == "moment")
    *ptrCodeCible = SenseurOptique::codeMoment;
  else if (interne == "devant")
    *ptrCodeCible = SenseurOptique::codeDevant;
  else if (interne == "position")
    *ptrCodeCible = SenseurOptique::codePosition;
  else if (interne == "position-sans-eclipse")
    *ptrCodeCible = SenseurOptique::codePositionSansEclipse;
  else if (interne == "direction")
    *ptrCodeCible = SenseurOptique::codeDirection;
  else if (interne == "direction-sans-eclipse")
    *ptrCodeCible = SenseurOptique::codeDirectionSansEclipse;
  else if (interne == "station")
  { // la cible est une station sol, il faut extraire ses caractéristiques
    *ptrCodeCible = SenseurOptique::codeStation;
    LireStation (blocSenseur, "station", ptrStation);
  }
  else if (interne == "polaris-sans-eclipse")
    *ptrCodeCible = SenseurOptique::codePolaireSansEclipse;
  else if (interne == "canopus-sans-eclipse")
    *ptrCodeCible = SenseurOptique::codeCanopeSansEclipse;
  else
  { 
    *ptrCodeCible = SenseurOptique::codeInvalide;
    throw MarmottesErreurs (MarmottesErreurs::cible_inconnue,
                            interne.c_str (),
                            "soleil", "soleil-sans-eclipse",
                            "corps-central-soleil", "lune",
                            "lune-sans-eclipse", "corps-central",
                            "terre", "nadir", "vitesse-sol-apparente",
                            "polaris", "canopus", 
                            "polaris-sans-eclipse", "canopus-sans-eclipse"
                            "vitesse", "moment", "devant", "position",
                            "position-sans-eclipse", "direction",
                            "direction-sans-eclipse", "station",
                            (char *) 0);
  }

  // vérification de la cohérence champs d'inhibition / cible
  if (champInhibitionSoleilPresent
      && (*ptrCodeCible == SenseurOptique::codeSoleil
          || *ptrCodeCible == SenseurOptique::codeSoleilSansEclipse
          || *ptrCodeCible == SenseurOptique::codeCorpsCentralSoleil))
    throw MarmottesErreurs (MarmottesErreurs::champ_inhibition_cible_soleil,
                            nom.c_str ());
  if (champInhibitionLunePresent
      && (*ptrCodeCible == SenseurOptique::codeLune
          || *ptrCodeCible == SenseurOptique::codeLuneSansEclipse))
    throw MarmottesErreurs (MarmottesErreurs::champ_inhibition_cible_lune,
                            nom.c_str ());
  if (champInhibitionCentralPresent
      && (*ptrCodeCible == SenseurOptique::codeCorpsCentral
          || *ptrCodeCible == SenseurOptique::codeVitesseSolApparente
          || *ptrCodeCible == SenseurOptique::codeNadir
          || *ptrCodeCible == SenseurOptique::codeLuneSansEclipse))
    throw MarmottesErreurs (MarmottesErreurs::champ_inhibition_cible_central,
                            nom.c_str ());

}


static void
LireElementsOptiques (FichierStructure *blocSenseur,
                      Parcelle **adrPtrChampDeVue,
                      Parcelle **adrPtrChampInhibitionSoleil,
                      Parcelle **adrPtrChampInhibitionLune,
                      Parcelle **adrPtrChampInhibitionCentral,
                      double *ptrMargeEclipseSoleil,
                      double *ptrMargeEclipseLune,
                      double *ptrSeuilPhaseLune)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{

  *adrPtrChampDeVue             = 0;
  *adrPtrChampInhibitionSoleil  = 0;
  *adrPtrChampInhibitionLune    = 0;
  *adrPtrChampInhibitionCentral = 0;

  try
  {

    // extraction du champ de vue
    string nomChamp (TraduitVersExterne ("champ_de_vue"));
    *adrPtrChampDeVue = LireParcelle (blocSenseur, nomChamp);

    // extraction du champ d'inhibition Soleil
    nomChamp = TraduitVersExterne ("champ_d_inhibition_soleil");
    if (blocSenseur->contientSousBloc (nomChamp.c_str ()))
      *adrPtrChampInhibitionSoleil = LireParcelle (blocSenseur, nomChamp);

    // extraction du champ d'inhibition Lune 
    nomChamp = TraduitVersExterne ("champ_d_inhibition_lune");
    if (blocSenseur->contientSousBloc (nomChamp.c_str ()))
      *adrPtrChampInhibitionLune = LireParcelle (blocSenseur, nomChamp);
    
    // extraction du champ d'inhibition corps central
    nomChamp = TraduitVersExterne ("champ_d_inhibition_corps_central");
    if (blocSenseur->contientSousBloc (nomChamp.c_str ()))
      *adrPtrChampInhibitionCentral = LireParcelle (blocSenseur, nomChamp);
    
    // recherche des marges sur les éclipses
    *ptrMargeEclipseSoleil = 0.0;
    nomChamp = TraduitVersExterne ("marge_eclipse_soleil");
    if (blocSenseur->contientSousBloc (nomChamp.c_str ()))
      LireReels (blocSenseur, nomChamp.c_str (), 1, ptrMargeEclipseSoleil);

    *ptrMargeEclipseLune = 0.0;
    nomChamp = TraduitVersExterne ("marge_eclipse_lune");
    if (blocSenseur->contientSousBloc (nomChamp.c_str ()))
      LireReels (blocSenseur, nomChamp.c_str (), 1, ptrMargeEclipseLune);
    
    // recherche du seuil de phase tolérable de la lune (la valeur de
    // 180 degrés par défaut indique que la lune est toujours gênante)
    *ptrSeuilPhaseLune = 180.0;
    nomChamp = TraduitVersExterne ("seuil_phase_lune");
    if (blocSenseur->contientSousBloc (nomChamp.c_str ()))
      LireReels (blocSenseur, nomChamp.c_str (), 1, ptrSeuilPhaseLune);

  }

  catch (...)
  {
    // élimination des éléments déjà lus
    if (*adrPtrChampDeVue)
      delete *adrPtrChampDeVue;
    if (*adrPtrChampInhibitionSoleil)
      delete *adrPtrChampInhibitionSoleil;
    if (*adrPtrChampInhibitionLune)
      delete *adrPtrChampInhibitionLune;
    if (*adrPtrChampInhibitionCentral)
      delete *adrPtrChampInhibitionCentral;

    *adrPtrChampDeVue             = 0;
    *adrPtrChampInhibitionSoleil  = 0;
    *adrPtrChampInhibitionLune    = 0;
    *adrPtrChampInhibitionCentral = 0;

    // on remonte l'erreur
    throw;

  }    
}


static SenseurCartesien *
LireSenseurCartesien (FichierStructure *blocSenseur, const string& nom,
                      const RotDBL& repere, const VecDBL& axeCalage,
                      double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ 
  // Ce sont les méthodes LireVecteurNorme et LireElementsOptiques
  // qui "lancent" des MarmottesErreurs et LireElementsOptiques
  // qui "lance" un ClubErreurs

  // extraction des éléments communs à tous les senseurs optiques
  Parcelle *ptrChampDeVue = NULL;
  Parcelle *ptrChampInhibitionSoleil  = NULL;
  Parcelle *ptrChampInhibitionLune    = NULL;
  Parcelle *ptrChampInhibitionCentral = NULL;
  double    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune;
  LireElementsOptiques (blocSenseur,
                        &ptrChampDeVue, &ptrChampInhibitionSoleil,
                        &ptrChampInhibitionLune, &ptrChampInhibitionCentral,
                        &margeEclipseSoleil,
                        &margeEclipseLune, &seuilPhaseLune);

  // extraction de la cible
  int          codeCible;
  StationCible station;
  VecDBL       observe;
  LireCible (blocSenseur, nom,
             (ptrChampInhibitionSoleil  != 0),
             (ptrChampInhibitionLune    != 0),
             (ptrChampInhibitionCentral != 0),
             &codeCible, &station, &observe);

  // recherche de l'axe de mesure
  VecDBL axeReference;
  try
  {
    LireVecteurNorme (blocSenseur, "reference", &axeReference);
  }
  catch (...)
  { 
    if (ptrChampDeVue)
      delete ptrChampDeVue;
    throw;
  }

  // construction du senseur
  return new SenseurCartesien (nom, repere, axeCalage, precision,
                               SenseurOptique::codeCible (codeCible),
                               &station, observe, ptrChampDeVue,
                               ptrChampInhibitionSoleil,
                               ptrChampInhibitionLune,
                               ptrChampInhibitionCentral,
                               radians (margeEclipseSoleil),
                               radians (margeEclipseLune),
                               radians (seuilPhaseLune),
                               axeReference);

}


static SenseurDiedre *
LireSenseurDiedre (FichierStructure *blocSenseur, const string& nom,
                   const RotDBL& repere, const VecDBL& axeCalage,
                   double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ 
  // Ce sont les méthodes LireVecteurNorme et LireElementsOptiques
  // qui "lancent" des MarmottesErreurs et LireElementsOptiques
  // qui "lance" un ClubErreurs

  // extraction des éléments communs à tous les senseurs optiques
  Parcelle *ptrChampDeVue = NULL;
  Parcelle *ptrChampInhibitionSoleil  = NULL;
  Parcelle *ptrChampInhibitionLune    = NULL;
  Parcelle *ptrChampInhibitionCentral = NULL;
  double    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune;
  LireElementsOptiques (blocSenseur,
                        &ptrChampDeVue, &ptrChampInhibitionSoleil,
                        &ptrChampInhibitionLune, &ptrChampInhibitionCentral,
                        &margeEclipseSoleil,
                        &margeEclipseLune, &seuilPhaseLune);

  // extraction de la cible
  int          codeCible;
  StationCible station;
  VecDBL       observe;
  LireCible (blocSenseur, nom,
             (ptrChampInhibitionSoleil  != 0),
             (ptrChampInhibitionLune    != 0),
             (ptrChampInhibitionCentral != 0),
             &codeCible, &station, &observe);

  // recherche de l'axe de référence du zéro
  // recherche de l'axe sensible
  VecDBL referenceZero;
  VecDBL axeSensible;
  try
  {
    LireVecteurNorme (blocSenseur, "reference_zero", &referenceZero);
    LireVecteurNorme (blocSenseur, "axe_sensible", &axeSensible);
  }
  catch (...)
  { 
    if (ptrChampDeVue)
      delete ptrChampDeVue;
    throw;
  }

  // construction du senseur
  return new SenseurDiedre (nom, repere, axeCalage, precision,
                            SenseurOptique::codeCible (codeCible),
                            &station, observe, ptrChampDeVue,
                            ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                            ptrChampInhibitionCentral,
                            radians (margeEclipseSoleil),
                            radians (margeEclipseLune),
                            radians (seuilPhaseLune),
                            referenceZero, axeSensible);

}


static SenseurVecteur *
LireSenseurVecteur (FichierStructure *blocSenseur, const string& nom,
                    const RotDBL& repere, const VecDBL& axeCalage,
                    double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ 
  // Ce sont les méthodes LireVecteurNorme et LireElementsOptiques
  // qui "lancent" des MarmottesErreurs et LireElementsOptiques
  // qui "lance" un ClubErreurs

  // extraction des éléments communs à tous les senseurs optiques
  Parcelle *ptrChampDeVue = NULL;
  Parcelle *ptrChampInhibitionSoleil  = NULL;
  Parcelle *ptrChampInhibitionLune    = NULL;
  Parcelle *ptrChampInhibitionCentral = NULL;
  double    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune;
  LireElementsOptiques (blocSenseur,
                        &ptrChampDeVue, &ptrChampInhibitionSoleil,
                        &ptrChampInhibitionLune, &ptrChampInhibitionCentral,
                        &margeEclipseSoleil,
                        &margeEclipseLune, &seuilPhaseLune);

  // extraction de la cible
  int          codeCible;
  StationCible station;
  VecDBL       observe;
  LireCible (blocSenseur, nom,
             (ptrChampInhibitionSoleil  != 0),
             (ptrChampInhibitionLune    != 0),
             (ptrChampInhibitionCentral != 0),
             &codeCible, &station, &observe);

  // recherche de l'axe de référence
  VecDBL axeReference;
  try
  {
    LireVecteurNorme (blocSenseur, "reference", &axeReference);
  }
  catch (...)
  { 
    if (ptrChampDeVue)
      delete ptrChampDeVue;
    throw;
  }

  // construction du senseur
  return new SenseurVecteur (nom, repere, axeCalage, precision,
                             SenseurOptique::codeCible (codeCible),
                             &station, observe, ptrChampDeVue,
                             ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                             ptrChampInhibitionCentral,
                             radians (margeEclipseSoleil),
                             radians (margeEclipseLune),
                             radians (seuilPhaseLune),
                             axeReference);

}


static SenseurElevation *
LireSenseurElevation (FichierStructure *blocSenseur, const string& nom,
                      const RotDBL& repere, const VecDBL& axeCalage,
                      double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ 
  // Ce sont les méthodes LireVecteurNorme et LireElementsOptiques
  // qui "lancent" des MarmottesErreurs et LireElementsOptiques
  // qui "lance" un ClubErreurs

  // extraction des éléments communs à tous les senseurs optiques
  Parcelle *ptrChampDeVue = NULL;
  Parcelle *ptrChampInhibitionSoleil  = NULL;
  Parcelle *ptrChampInhibitionLune    = NULL;
  Parcelle *ptrChampInhibitionCentral = NULL;
  double    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune;
  LireElementsOptiques (blocSenseur,
                        &ptrChampDeVue, &ptrChampInhibitionSoleil,
                        &ptrChampInhibitionLune, &ptrChampInhibitionCentral,
                        &margeEclipseSoleil,
                        &margeEclipseLune, &seuilPhaseLune);

  // extraction de la cible
  int          codeCible;
  StationCible station;
  VecDBL       observe;
  LireCible (blocSenseur, nom,
             (ptrChampInhibitionSoleil  != 0),
             (ptrChampInhibitionLune    != 0),
             (ptrChampInhibitionCentral != 0),
             &codeCible, &station, &observe);

  // recherche de la normale au plan de référence
  VecDBL axeReference;
  try
  {
    LireVecteurNorme (blocSenseur, "normale_reference", &axeReference);
  }
  catch (...)
  { 
    if (ptrChampDeVue)
      delete ptrChampDeVue;
    throw;
  }

  // construction du senseur
  return new SenseurElevation (nom, repere, axeCalage, precision,
                               SenseurOptique::codeCible (codeCible),
                               &station, observe, ptrChampDeVue,
                               ptrChampInhibitionSoleil,
                               ptrChampInhibitionLune,
                               ptrChampInhibitionCentral,
                               radians (margeEclipseSoleil),
                               radians (margeEclipseLune),
                               radians (seuilPhaseLune),
                               axeReference);

}


static SenseurFonctionEchant1D *
LireSenseurFonctionEchant1D (FichierStructure *blocSenseur, const string& nom,
                             const RotDBL& repere, const VecDBL& axeCalage,
                             double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ 
  // Ce sont les méthodes LireVecteurNorme et LireElementsOptiques
  // qui "lancent" des MarmottesErreurs et LireElementsOptiques
  // qui "lance" un ClubErreurs

  // extraction des éléments communs à tous les senseurs optiques
  Parcelle *ptrChampDeVue = NULL;
  Parcelle *ptrChampInhibitionSoleil  = NULL;
  Parcelle *ptrChampInhibitionLune    = NULL;
  Parcelle *ptrChampInhibitionCentral = NULL;
  double    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune;
  LireElementsOptiques (blocSenseur,
                        &ptrChampDeVue, &ptrChampInhibitionSoleil,
                        &ptrChampInhibitionLune, &ptrChampInhibitionCentral,
                        &margeEclipseSoleil,
                        &margeEclipseLune, &seuilPhaseLune);

  // extraction de la cible
  int          codeCible;
  StationCible station;
  VecDBL       observe;
  LireCible (blocSenseur, nom,
             (ptrChampInhibitionSoleil  != 0),
             (ptrChampInhibitionLune    != 0),
             (ptrChampInhibitionCentral != 0),
             &codeCible, &station, &observe);

  // recherche de l'axe, de l'origine, du maximum et de la largeur à 3dB
  VecDBL axe;
  VecDBL origine;
  int nbEchantillons;
  double *angles  = 0;
  double *valeurs = 0;
  try
  {
    LireVecteurNorme (blocSenseur, "axe", &axe);
    LireVecteurNorme (blocSenseur, "origine", &origine);

    // échantillonnage de la fonction de mesure
    int nbChamps;
    string nomEchantillon;
    ChampsTerminaux (blocSenseur, "echantillon", &nbChamps, &nomEchantillon);
    if ((nbChamps < 2) || (nbChamps % 2))
      throw MarmottesErreurs (MarmottesErreurs::points_echantillon,
                              nbChamps, nomEchantillon.c_str ());
    double *tab = new double [nbChamps];
    LireReels (blocSenseur, "echantillon", nbChamps, tab);

    nbEchantillons = nbChamps / 2;
    angles  = new double [nbEchantillons];
    valeurs = new double [nbEchantillons];
    for (int i = 0; i < nbEchantillons; i++)
    { // répartition des données dans les tables azimut et site
      angles  [i] = radians (tab [2 * i]);
      valeurs [i] = tab [2 * i + 1];
    }
    delete [] tab;

  }
  catch (...)
  { 
    if (ptrChampDeVue)
      delete ptrChampDeVue;
    if (angles)
      delete [] angles;
    if (valeurs)
      delete [] valeurs;
    throw;
  }

  // construction du senseur
  SenseurFonctionEchant1D *s =
    new SenseurFonctionEchant1D (nom, repere,
                                 axeCalage, precision,
                                 SenseurOptique::codeCible (codeCible),
                                 &station, observe, ptrChampDeVue,
                                 ptrChampInhibitionSoleil,
                                 ptrChampInhibitionLune,
                                 ptrChampInhibitionCentral,
                                 radians (margeEclipseSoleil),
                                 radians (margeEclipseLune),
                                 radians (seuilPhaseLune),
                                 axe, origine, nbEchantillons, angles, valeurs);

  // suppression des tables temporaires
  delete [] angles;
  delete [] valeurs;

  return s;

}


static SenseurFonctionGauss *
LireSenseurFonctionGauss (FichierStructure *blocSenseur, const string& nom,
                          const RotDBL& repere, const VecDBL& axeCalage,
                          double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ 
  // Ce sont les méthodes LireVecteurNorme et LireElementsOptiques
  // qui "lancent" des MarmottesErreurs et LireElementsOptiques
  // qui "lance" un ClubErreurs

  // extraction des éléments communs à tous les senseurs optiques
  Parcelle *ptrChampDeVue = NULL;
  Parcelle *ptrChampInhibitionSoleil  = NULL;
  Parcelle *ptrChampInhibitionLune    = NULL;
  Parcelle *ptrChampInhibitionCentral = NULL;
  double    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune;
  LireElementsOptiques (blocSenseur,
                        &ptrChampDeVue, &ptrChampInhibitionSoleil,
                        &ptrChampInhibitionLune, &ptrChampInhibitionCentral,
                        &margeEclipseSoleil,
                        &margeEclipseLune, &seuilPhaseLune);

  // extraction de la cible
  int          codeCible;
  StationCible station;
  VecDBL       observe;
  LireCible (blocSenseur, nom,
             (ptrChampInhibitionSoleil  != 0),
             (ptrChampInhibitionLune    != 0),
             (ptrChampInhibitionCentral != 0),
             &codeCible, &station, &observe);

  // recherche de l'axe, de l'origine, du maximum et de la largeur à 3 dB
  VecDBL axe;
  VecDBL origine;
  double maximum, angle3dB;
  try
  {
    LireVecteurNorme (blocSenseur, "axe", &axe);
    LireVecteurNorme (blocSenseur, "origine", &origine);
    LireReels (blocSenseur, "maximum", 1, &maximum);
    LireReels (blocSenseur, "angle_3dB", 1, &angle3dB);
  }
  catch (...)
  { 
    if (ptrChampDeVue)
      delete ptrChampDeVue;
    throw;
  }

  // construction du senseur
  return new SenseurFonctionGauss (nom, repere, axeCalage, precision,
                                   SenseurOptique::codeCible (codeCible),
                                   &station, observe, ptrChampDeVue,
                                   ptrChampInhibitionSoleil,
                                   ptrChampInhibitionLune,
                                   ptrChampInhibitionCentral,
                                   radians (margeEclipseSoleil),
                                   radians (margeEclipseLune),
                                   radians (seuilPhaseLune),
                                   axe, origine, maximum, angle3dB);

}


static SenseurFonctionSinCard2 *
LireSenseurFonctionSinCard2 (FichierStructure *blocSenseur, const string& nom,
                             const RotDBL& repere, const VecDBL& axeCalage,
                             double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ 
  // Ce sont les méthodes LireVecteurNorme et LireElementsOptiques
  // qui "lancent" des MarmottesErreurs et LireElementsOptiques
  // qui "lance" un ClubErreurs

  // extraction des éléments communs à tous les senseurs optiques
  Parcelle *ptrChampDeVue = NULL;
  Parcelle *ptrChampInhibitionSoleil  = NULL;
  Parcelle *ptrChampInhibitionLune    = NULL;
  Parcelle *ptrChampInhibitionCentral = NULL;
  double    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune;
  LireElementsOptiques (blocSenseur,
                        &ptrChampDeVue, &ptrChampInhibitionSoleil,
                        &ptrChampInhibitionLune, &ptrChampInhibitionCentral,
                        &margeEclipseSoleil,
                        &margeEclipseLune, &seuilPhaseLune);

  // extraction de la cible
  int          codeCible;
  StationCible station;
  VecDBL       observe;
  LireCible (blocSenseur, nom,
             (ptrChampInhibitionSoleil  != 0),
             (ptrChampInhibitionLune    != 0),
             (ptrChampInhibitionCentral != 0),
             &codeCible, &station, &observe);

  // recherche de l'axe, de l'origine, du maximum et de la largeur à 3dB
  VecDBL axe;
  VecDBL origine;
  double maximum, angle3dB;
  try
  {
    LireVecteurNorme (blocSenseur, "axe", &axe);
    LireVecteurNorme (blocSenseur, "origine", &origine);
    LireReels (blocSenseur, "maximum", 1, &maximum);
    LireReels (blocSenseur, "angle_3dB", 1, &angle3dB);
  }
  catch (...)
  { 
    if (ptrChampDeVue)
      delete ptrChampDeVue;
    throw;
  }

  // construction du senseur
  return new SenseurFonctionSinCard2 (nom, repere, axeCalage, precision,
                                      SenseurOptique::codeCible (codeCible),
                                      &station, observe, ptrChampDeVue,
                                      ptrChampInhibitionSoleil,
                                      ptrChampInhibitionLune,
                                      ptrChampInhibitionCentral,
                                      radians (margeEclipseSoleil),
                                      radians (margeEclipseLune),
                                      radians (seuilPhaseLune),
                                      axe, origine, maximum, angle3dB);

}


static SenseurFonctionSinCardXY *
LireSenseurFonctionSinCardXY (FichierStructure *blocSenseur, const string& nom,
                              const RotDBL& repere, const VecDBL& axeCalage,
                              double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{ 
  // Ce sont les méthodes LireVecteurNorme et LireElementsOptiques
  // qui "lancent" des MarmottesErreurs et LireElementsOptiques
  // qui "lance" un ClubErreurs

  // extraction des éléments communs à tous les senseurs optiques
  Parcelle *ptrChampDeVue = NULL;
  Parcelle *ptrChampInhibitionSoleil  = NULL;
  Parcelle *ptrChampInhibitionLune    = NULL;
  Parcelle *ptrChampInhibitionCentral = NULL;
  double    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune;
  LireElementsOptiques (blocSenseur,
                        &ptrChampDeVue, &ptrChampInhibitionSoleil,
                        &ptrChampInhibitionLune, &ptrChampInhibitionCentral,
                        &margeEclipseSoleil,
                        &margeEclipseLune, &seuilPhaseLune);

  // extraction de la cible
  int          codeCible;
  StationCible station;
  VecDBL       observe;
  LireCible (blocSenseur, nom,
             (ptrChampInhibitionSoleil  != 0),
             (ptrChampInhibitionLune    != 0),
             (ptrChampInhibitionCentral != 0),
             &codeCible, &station, &observe);

  // recherche de l'axe, de l'origine, du maximum et de la largeur à 3dB
  VecDBL axe;
  VecDBL origine;
  double maximum, angle3dBX, angle3dBY;
  try
  {
    LireVecteurNorme (blocSenseur, "axe", &axe);
    LireVecteurNorme (blocSenseur, "origine", &origine);
    LireReels (blocSenseur, "maximum", 1, &maximum);
    LireReels (blocSenseur, "angle_3dB_x", 1, &angle3dBX);
    LireReels (blocSenseur, "angle_3dB_y", 1, &angle3dBY);
  }
  catch (...)
  { 
    if (ptrChampDeVue)
      delete ptrChampDeVue;
    throw;
  }

  // construction du senseur
  return new SenseurFonctionSinCardXY (nom, repere, axeCalage, precision,
                                       SenseurOptique::codeCible (codeCible),
                                       &station, observe, ptrChampDeVue,
                                       ptrChampInhibitionSoleil,
                                       ptrChampInhibitionLune,
                                       ptrChampInhibitionCentral,
                                       radians (margeEclipseSoleil),
                                       radians (margeEclipseLune),
                                       radians (seuilPhaseLune),
                                       axe, origine, maximum,
                                       angle3dBX, angle3dBY);

}


static SenseurLimbe *
LireSenseurLimbe (FichierStructure *blocSenseur, const string& nom,
                    const RotDBL& repere, const VecDBL& axeCalage,
                    double precision)
  throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
{
  // C'est la méthode LireReels qui "lance" une MarmottesErreurs

  // extraction des éléments communs à tous les senseurs optiques
  Parcelle *ptrChampDeVue = NULL;
  Parcelle *ptrChampInhibitionSoleil  = NULL;
  Parcelle *ptrChampInhibitionLune    = NULL;
  Parcelle *ptrChampInhibitionCentral = NULL;
  double    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune;
  LireElementsOptiques (blocSenseur,
                        &ptrChampDeVue, &ptrChampInhibitionSoleil,
                        &ptrChampInhibitionLune, &ptrChampInhibitionCentral,
                        &margeEclipseSoleil,
                        &margeEclipseLune, &seuilPhaseLune);

  // recherche de l'axe de référence du zéro
  VecDBL referenceZero;
  LireVecteurNorme (blocSenseur, "reference_zero", &referenceZero);
    
  // recherche de l'axe sensible
  VecDBL axeSensible;
  LireVecteurNorme (blocSenseur, "axe_sensible", &axeSensible);
    
  // construction du senseur
  return new SenseurLimbe (nom, repere, axeCalage, precision,
                           ptrChampDeVue,
                           ptrChampInhibitionSoleil,
                           ptrChampInhibitionLune,
                           ptrChampInhibitionCentral,
                           radians (margeEclipseSoleil),
                           radians (margeEclipseLune),
                           radians (seuilPhaseLune),
                           referenceZero, axeSensible);

}


static SenseurAlpha *
LireSenseurAlpha (FichierStructure *blocSenseur, const string& nom,
                  const RotDBL& repere, const VecDBL& axeCalage,
                  double precision)
  throw (MarmottesErreurs)
{ 
  // C'est la méthode LireVecteurNorme qui "lance" une MarmottesErreurs

  // recherche de l'axe observé
  VecDBL observe;
  LireVecteurNorme (blocSenseur, "observe", &observe);

  // construction du senseur
  return new SenseurAlpha (nom, repere, axeCalage, precision, observe);

}


static SenseurDelta *
LireSenseurDelta (FichierStructure *blocSenseur, const string& nom,
                  const RotDBL& repere, const VecDBL& axeCalage,
                  double precision)
  throw (MarmottesErreurs)
{ 
  // C'est la méthode LireVecteurNorme qui "lance" une MarmottesErreurs

  // recherche de l'axe observé
  VecDBL observe;
  LireVecteurNorme (blocSenseur, "observe", &observe);

  // construction du senseur
  return new SenseurDelta (nom, repere, axeCalage, precision, observe);

}


static SenseurCardan *
LireSenseurCardan (FichierStructure *blocSenseur, const string& nom,
                   const RotDBL& repere, const VecDBL& axeCalage,
                   double precision)
  throw (MarmottesErreurs)
{ // recherche du type de mesure
  const int   maxTampon = 80;
  char        tampon [maxTampon];
  LireChaine (blocSenseur, "genre", tampon, maxTampon);

  string codeGenre (TraduitVersInterne (tampon));
  SenseurCardan::typeGenre genre = SenseurCardan::GenreInconnu;
  if (codeGenre == "LRT-lacet")
    genre = SenseurCardan::LRTLacet;
  else if (codeGenre == "LRT-roulis")
    genre = SenseurCardan::LRTRoulis;
  else if (codeGenre == "LRT-tangage")
    genre = SenseurCardan::LRTTangage;
  else if (codeGenre == "LTR-lacet")
    genre = SenseurCardan::LTRLacet;
  else if (codeGenre == "LTR-tangage")
    genre = SenseurCardan::LTRTangage;
  else if (codeGenre == "LTR-roulis")
    genre = SenseurCardan::LTRRoulis;
  else if (codeGenre == "RLT-roulis")
    genre = SenseurCardan::RLTRoulis;
  else if (codeGenre == "RLT-lacet")
    genre = SenseurCardan::RLTLacet;
  else if (codeGenre == "RLT-tangage")
    genre = SenseurCardan::RLTTangage;
  else if (codeGenre == "RTL-roulis")
    genre = SenseurCardan::RTLRoulis;
  else if (codeGenre == "RTL-tangage")
    genre = SenseurCardan::RTLTangage;
  else if (codeGenre == "RTL-lacet")
    genre = SenseurCardan::RTLLacet;
  else if (codeGenre == "TLR-tangage")
    genre = SenseurCardan::TLRTangage;
  else if (codeGenre == "TLR-lacet")
    genre = SenseurCardan::TLRLacet;
  else if (codeGenre == "TLR-roulis")
    genre = SenseurCardan::TLRRoulis;
  else if (codeGenre == "TRL-tangage")
    genre = SenseurCardan::TRLTangage;
  else if (codeGenre == "TRL-roulis")
    genre = SenseurCardan::TRLRoulis;
  else if (codeGenre == "TRL-lacet")
    genre = SenseurCardan::TRLLacet;
  else
  { 
    throw MarmottesErreurs (MarmottesErreurs::genre_cardan_inconnu,
                            nom.c_str (),
                            "LRT-lacet",   "LRT-roulis",  "LRT-tangage",
                            "LTR-lacet",   "LTR-tangage", "LTR-roulis",
                            "RLT-roulis",  "RLT-lacet",   "RLT-tangage",
                            "RTL-roulis",  "RTL-tangage", "RTL-lacet",
                            "TLR-tangage", "TLR-lacet",   "TLR-roulis",
                            "TRL-tangage", "TRL-roulis",  "TRL-lacet",
                            (char *) 0);
  }

  // recherche du repère de référence
  LireChaine (blocSenseur, "reference", tampon, maxTampon);

  string codeReference (TraduitVersInterne (tampon));
  SenseurCardan::typeReference reference = SenseurCardan::ReferenceInconnue;
  if (codeReference == "geocentrique")
    reference = SenseurCardan::Geocentrique;
  else if (codeReference == "orbital-TNW")
    reference = SenseurCardan::OrbitalTNW;
  else if (codeReference == "orbital-QSW")
    reference = SenseurCardan::OrbitalQSW;
  else if (codeReference == "inertiel")
    reference = SenseurCardan::Inertiel;
  else if (codeReference == "topocentrique")
    reference = SenseurCardan::Topocentrique;
  else if (codeReference == "utilisateur")
    reference = SenseurCardan::Utilisateur;
  else
  { 
    throw MarmottesErreurs (MarmottesErreurs::reference_cardan_inconnue,
                            nom.c_str (),
                            "geocentrique", "orbital-TNW", "orbital-QSW",
                            "inertiel",     "topocentrique", "utilisateur",
                            (char *) 0);
  }

  // construction du senseur
  return new SenseurCardan (genre, reference,
                            nom, repere, axeCalage, precision);

}


static SenseurCinematique *
LireSenseurCinematique (FichierStructure *blocSenseur, const string& nom,
                        const RotDBL& repere, const VecDBL& axeCalage,
                        double precision)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  // C'est la méthode LireVecteurNorme qui "lance" une MarmottesErreurs

  // recherche de l'axe sensible
  VecDBL axeSensible;
  LireVecteurNorme (blocSenseur, "axe_sensible", &axeSensible);

  // construction du senseur
  return new SenseurCinematique (nom, repere, axeCalage, precision,
                                 axeSensible);

}


static SenseurGyroInteg *
LireSenseurGyroInteg (FichierStructure *blocSenseur, const string& nom,
                      const RotDBL& repere, const VecDBL& axeCalage,
                      double precision)
  throw (MarmottesErreurs)
{ 
  // C'est la méthode LireVecteurNorme qui "lance" une MarmottesErreurs

  // recherche de l'axe sensible
  VecDBL axeSensible;
  LireVecteurNorme (blocSenseur, "axe_sensible", &axeSensible);

  // construction du senseur
  return new SenseurGyroInteg (nom, repere, axeCalage, precision,
                               axeSensible);

}
