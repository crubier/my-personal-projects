///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Bibam
//$Application
//        Club
//$Nom
//>       StatDifference.h
//$Resume
//       fichier d'en-tête de la classe StatDifference
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class StatDifference
//$Historique
//       $Log: StatDifference.h,v $
//       Revision 1.8  2001/02/16 12:23:56  club
//       remplacement de l'inclusion de map.h par l'inclusion de map
//
//       Revision 1.7  2000/10/25 10:05:15  club
//       correction du nom du chemin vers le fichier d'en-tête ClubConfig.h
//
//       Revision 1.6  2000/10/25 09:00:38  club
//       modification du répertoire pour l'include ClubConfig.h
//
//       Revision 1.5  2000/10/24 14:16:04  club
//       utilisation de tests de configuration pour les includes.
//
//       Revision 1.4  2000/08/04 09:45:46  club
//       calcul et affichage du décalage maximal rencontré.
//
//       Revision 1.3  2000/08/03 08:34:29  club
//       modification de la méthode majMessagesAffiches :
//       dans le cas où nbMessagesMax = 0, affectation de 0 à messagesAffiches_ [0]
//       et messagesAffiches_ [1].
//       Modification du constructeur : affectation de 0 à messagesAffiches_ [0].
//
//       Revision 1.2  2000/07/28 13:03:56  club
//       Modification de la signature de afficherSynthese : on passe en
//       argument de la fonction la valeur du seuil max toléré.
//
//       Revision 1.1  2000/07/26 09:48:06  club
//       Suite à la destruction du répertoire club/utils/club, déplacement
//       des fichiers .h dans le répertoire club/utils.
//
//       Revision 1.4  2000/07/26 07:28:14  club
//       ajout des attributs nbErrNonAccepteesNumeriques_, afficherMessages_
//       et afficherSynthese_ permettant de fournir les services aux nouvelles
//       options de la ligne de commande (rsynth, rmess).
//       Création des accesseurs à ces attributs
//
//       Revision 1.3  2000/07/07 09:49:54  club
//       création des fonctions permettant de calculer les statistiques
//       sur les différences numériques.
//       modification de l'attribut nbMessagesDiffMax_  en un tableau à deux
//       éléments qui indiquent l'intervalle des messages à afficher
//
//       Revision 1.2  2000/07/06 07:31:19  club
//       modification de l'attribut nbMessagesDiffMax_ (représentant le
//       nombre maximal de messages de différence à afficher) en un tableau
//       à deux éléments qui indiquent respectivement le numéro du premier
//       et le numéro du dernier message à afficher
//
//       Revision 1.1  2000/07/03 09:28:23  club
//       création d'une classe permettant de gérer toutes les statistiques
//       nécessaires à l'utilitaire difference
//
//$Version
//       $Id: StatDifference.h,v 1.8 2001/02/16 12:23:56 club Exp $
//
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


#ifndef __club_StatDifference_h
#define __club_StatDifference_h

#include <club/ClubConfig.h>
#include <ClubConfigNoInstall.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#ifdef HAVE_STL
#include <map>
#endif

#include "club/ClubErreurs.h"
#include "club/Traducteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class StatDifference
//$Resume
//      classe gérant toutes les statistiques utiles à l'utilitaire difference
//
//$Description
//      Cette classe fournit des méthodes permettant de gérer les statistiques
//      de difference (valeur de l'erreur numérique max, ...). Elle permet
//      également de compter le nombre de messages de différences affichés et
//      d'afficher des statistiques sur les différences numériques rencontrées.
//
//$Usage
//>     construction : 
//        sans argument
//>     utilisation  : 
//>       bool traiterDifference              () 
//          permet d'afficher un message de différence si le numéro de ce
//          message appartient à l'intervalle des messages à afficher.
//>       void afficherSynthese               () 
//          affiche la synthèse statistique de l'analyse des fichiers
//>       void majAfficherMessages            () 
//          met à jour le booléen indiquant si l'utilisateur souhaite afficher
//          les messages de différence
//>       void majAfficherSynthese            () 
//          met à jour le booléen indiquant si l'utilisateur souhaite afficher
//          la synthèse de l'analyse
//>       void majMessagesAffiches            () 2 signatures - 
//          met à jour l'intervalle des numéros de messages de différences 
//          à afficher
//>       void majNbErrAcceptees              () 
//          met à jour le nombre d'erreurs acceptées
//>       void majNbErrNonAcceptees           () 
//          met à jour le nombre d'erreurs non acceptées
//>       void majNbErrNonAccepteesNumeriques () 
//          met à jour le nombre d'erreurs numériques non acceptées
//>       void majDifferencesNumeriques       () 
//          met à jour le tableau contenant les valeurs des différences
//          numériques
//>       int nbErrNonAcceptees               () 
//          retourne le nombre d'erreurs non acceptées
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


class StatDifference
{
public :

  StatDifference () : nbErrNonAcceptees_ (0), nbErrNonAccepteesNumeriques_ (0),
                      nbErrAcceptees_ (0), nbMessagesDiffFini_ (false), 
                      nbErrAffichees_ (0), nbDifferencesNumeriques_ (0), 
                      afficherMessages_ (true), afficherSynthese_ (true)
  {
    messagesAffiches_ [0] = 0;
    messagesAffiches_ [1] = 0;
  };
  
  // mise a jour 

  void majAfficherMessages (const bool x) { afficherMessages_ = x; }
  void majAfficherSynthese (const bool x) { afficherSynthese_ = x; }

  void majMessagesAffiches (const int nbMessagesMax) 
  { 
    nbMessagesDiffFini_ = true;

    if (nbMessagesMax > 0)
    {
      messagesAffiches_ [0] = 1;
      messagesAffiches_ [1] = nbMessagesMax;
    }
    else
    {
      messagesAffiches_ [0] = 0;
      messagesAffiches_ [1] = 0;
    }
  }

  void majMessagesAffiches (const int nbMessagesMin, const int nbMessagesMax) 
  { 
    nbMessagesDiffFini_ = true;
    messagesAffiches_ [0] = nbMessagesMin;
    messagesAffiches_ [1] = nbMessagesMax;
  }

  void majNbErrAcceptees () { nbErrAcceptees_++; }
  void majNbErrNonAcceptees () { nbErrNonAcceptees_++; }
  void majNbErrNonAccepteesNumeriques () { nbErrNonAccepteesNumeriques_++; }

  void majDifferencesNumeriques (const double diff)
  {
    nbDifferencesNumeriques_++;
    differencesNumeriques_ [nbDifferencesNumeriques_] = diff;
  }

  // lecture
  int nbErrNonAcceptees () const { return nbErrNonAcceptees_; }

  // fonction permettant :
  //   - d'incrémenter le nombre de messages affichés, 
  //   - d'autoriser l'affichage de message si le numéro du message appartient
  //     à l'intervalle messagesAffiches_
  bool traiterDifference ();

  // fonction permettant d'afficher les résultats finaux
  void afficherSynthese (const double precision, const int decalage);

private :

  void calculerStat (double& errMinRelative, double& errMaxRelative,
                     double& moyenne);

  int nbErrNonAcceptees_;
  int nbErrNonAccepteesNumeriques_;
  int nbErrAcceptees_;

  int messagesAffiches_ [2];
  bool nbMessagesDiffFini_;
  int nbErrAffichees_;

  map<int,double> differencesNumeriques_;
  int nbDifferencesNumeriques_;

  bool afficherMessages_;
  bool afficherSynthese_;
};

#endif
