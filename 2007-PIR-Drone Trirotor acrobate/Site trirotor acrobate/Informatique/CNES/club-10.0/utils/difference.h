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
//>       difference.h
//$Resume
//       fichier d'en-tête de l'utilitaire difference
//
//$Description
//       module de déclaration des fonctions utiles à difference
//
//$Contenu
//>       void analyserArguments()
//>       int main()              
//$Historique
//       $Log: difference.h,v $
//       Revision 1.6  2000/10/25 10:05:15  club
//       correction du nom du chemin vers le fichier d'en-tête ClubConfig.h
//
//       Revision 1.5  2000/10/25 09:00:38  club
//       modification du répertoire pour l'include ClubConfig.h
//
//       Revision 1.4  2000/10/24 14:16:04  club
//       utilisation de tests de configuration pour les includes.
//
//       Revision 1.3  2000/09/07 08:42:03  club
//       utilisation de string de la STL au lieu de ChaineSimple conformément
//       aux évolutions réalisées sur les classes de l'interface publique de club.
//
//       Revision 1.2  2000/07/28 13:02:24  club
//       modification de la signature de analyserArguments
//
//       Revision 1.1  2000/07/26 09:48:06  club
//       Suite à la destruction du répertoire club/utils/club, déplacement
//       des fichiers .h dans le répertoire club/utils.
//
//       Revision 1.4  2000/07/26 07:26:47  club
//       modification de l'entête interface suite à la modification des
//       valeurs de retour de l'utilitaire pour avoir une similitude avec
//       diff (0=pas de différence ; 1=des différences ; 2=problème d'exécution)
//
//       Revision 1.3  2000/07/07 09:52:03  club
//       Mise au propre des includes et des commentaires de l'entete
//
//       Revision 1.2  2000/07/03 09:29:34  club
//       modification complète de l'utilitaire difference :
//       suppression des appels aux fonctions système
//       utilisation des classes C++ ComparateurFichier et StatDifference
//
//       Revision 1.1  1999/10/12 12:03:41  club
//       Initial revision
//
//$Version
//       $Id: difference.h,v 1.6 2000/10/25 10:05:15 club Exp $
//
//$Auteur
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


#ifndef __club_difference_h
#define __club_difference_h

#include <club/ClubConfig.h>
#include <ClubConfigNoInstall.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#ifdef HAVE_STL
#include <string>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "StatDifference.h"
#include "ComparateurFichier.h"
#include "club/ClubErreurs.h"
#include "club/OptionsAppli.h"
#include "club/Traducteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       difference.h
//$Resume
//        cet utilitaire permet de répertorier les différences entre deux
//        fichiers tout en acceptant des imprécisions numériques dûes à un
//        changement de plateforme par exemple.
//$Description
//        Le but de cet utilitaire est d'offrir un mécanisme souple et évolutif
//        pour répertorier les différences entre deux fichiers à l'aide de
//        messages plus explicites que ceux fournis par le diff système, ces
//        messages pouvant être traduits en francais avec accents ou en anglais.
//        L'utilitaire retourne :
//          * 0 : lorsque le programme arrive à sa fin normale
//          * 1 : lorsque les deux fichiers contiennent au moins une différence
//          * 2 : lorsqu'il y a un problème d'analyse de la ligne de commande 
//                ou un problème d'ouverture des fichiers
//
//$Usage
//>     utilisation : 
//>       void analyserArguments () 
//>       int main               () 
//$Auteur
//       O. Queyrut CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


// fonction permettant d'analyser la ligne de commande
void analyserArguments (int nombreArguments, char** arguments,
                        double* precision, int* decalageMax,
                        int* numLignesResDebut, int* numLignesResFin,
                        int* numLignesRefDebut, int* numLignesRefFin,
                        StatDifference& stats,
                        string *ptrFichierRes,
                        string *ptrFichierRef) throw (ClubErreurs);

// main de l'utilitaire
int main (int argc, char **argv);

#endif
