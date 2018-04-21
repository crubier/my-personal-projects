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
//>       ComparateurFichier.h
//$Resume
//       fichier d'en-tête de la classe ComparateurFichier
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class ComparateurFichier
//$Historique
//       $Log: ComparateurFichier.h,v $
//       Revision 1.7  2000/10/25 10:05:15  club
//       correction du nom du chemin vers le fichier d'en-tête ClubConfig.h
//
//       Revision 1.6  2000/10/25 09:00:38  club
//       modification du répertoire pour l'include ClubConfig.h
//
//       Revision 1.5  2000/10/24 14:16:04  club
//       utilisation de tests de configuration pour les includes.
//
//       Revision 1.4  2000/09/07 08:42:02  club
//       utilisation de string de la STL au lieu de ChaineSimple conformément
//       aux évolutions réalisées sur les classes de l'interface publique de club.
//
//       Revision 1.3  2000/08/04 09:45:46  club
//       calcul et affichage du décalage maximal rencontré.
//
//       Revision 1.2  2000/07/28 13:07:14  club
//       modification de la signature du constructeur pour permettre la prise
//       en compte de l'option pour ignorer des lignes du fichier de référence.
//
//       Revision 1.1  2000/07/26 09:48:06  club
//       Suite à la destruction du répertoire club/utils/club, déplacement
//       des fichiers .h dans le répertoire club/utils.
//
//       Revision 1.3  2000/07/26 07:30:56  club
//       modification profonde de la classe pour permettre l'implantation
//       de l'algorithme "Longest Common Subsequence" dans l'analyse des
//       fichiers : ajout de l'attribut tabLCS_, modification du constructeur,
//       création d'un destructeur et suppression de la méthode repositionner ...
//
//       Revision 1.2  2000/07/07 09:51:20  club
//       suppression de laméthode initialise et de l'attribut lignesDifferentes_.
//       Remplacement de leur utilité algorithmique dans le repositionnement
//       par numPremieresLignesEgales.
//
//       Revision 1.1  2000/07/03 09:27:36  club
//       création d'une classe permettant de comparer deux fichiers tout en
//       acceptant une imprécision numérique.
//       cette classe est utilisé par l'utilitaire difference
//
//$Version
//       $Id: ComparateurFichier.h,v 1.7 2000/10/25 10:05:15 club Exp $
//
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


#ifndef __club_ComparateurFichier_h
#define __club_ComparateurFichier_h

#include <club/ClubConfig.h>
#include <ClubConfigNoInstall.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#ifdef HAVE_STL
#include <string>
#endif

#include "StatDifference.h"
#include "ComparateurLigne.h"

#include "club/ClubErreurs.h"
#include "club/TamponTexte.h"
#include "club/Traducteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ComparateurFichier
//$Resume
//       classe permettant de comparer un fichier résultat avec
//       un fichier référence
//
//$Description
//       Cette classe permet de comparer deux fichiers en acceptant une
//       imprecision numérique sur les réels. Elle permet de formater
//       un message de différence concernant chaque ligne et elle met à jour 
//       des statistiques sur les différences. Il est possible de recaler
//       les tampons si certaines lignes sont propres à un seul d'entre eux.
//       L'algorithme utilisé pour connaître quelles sont les lignes communes,
//       propres à un fichier ou propres à l'autre est appelé "Longest Common
//       Subsequence". Cet algorithme est fourni à l'adresse suivante valide 
//       au 24/07/2000 :
//          http://www.ics.uci.edu/~eppstein/161/960229.html
//
//$Usage
//>     construction : 
//          à partir de deux noms de fichiers, d'une valeur indiquant la 
//          précision numérique souhaitée, du décalage maximal toléré et 
//          du nombre de lignes au début et à la fin du fichier res qu'il faut
//          ignorer. Le constructeur crée des tampons texte contenant 
//          le texte des fichiers
//>     utilisation : 
//>       void analyserFichier     () 
//          analyse les deux fichiers ligne par ligne et permet si nécessaire
//          de sauter des lignes propres à un seul des deux fichiers.
//>       int decalageRencontreMax ()
//          retourne la valeur maximale du décalage rencontré 
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////



class ComparateurFichier
{
public :

  // constructeur
  ComparateurFichier (const string& fichierRes, const string& fichierRef, 
                      double precision, int decalageMax, int suppLignesResDebut, 
                      int suppLignesResFin, int suppLignesRefDebut, 
                      int suppLignesRefFin) throw (ClubErreurs, bad_alloc);
  
  // destructeur
  ~ComparateurFichier ();

  // comparaisons des tampons tamponRes_ et tamponRef_
  void analyserFichier (StatDifference& stats) throw (ClubErreurs);

  int decalageRencontreMax () const { return decalageRencontreMax_; }

private :

  void analyserLignesEgalesDebut (int& debutRes, const int finRes, 
                                  int& debutRef, const int finRef,
                                  StatDifference& stats);

  void analyserLignesEgalesFin (const int debutRes, int& finRes, 
                                const int debutRef, int& finRef,
                                StatDifference& stats);

  // cette méthode privée permet de remplir le tableau tabLCS_ par l'algorithme 
  // "Longest Common Subsequent" de complexité O(nbLignesRes*nbLignesRef)
  void initialiser (const int debutRes, const int finRes, 
                    const int debutRef, const int finRef);

  // noms du fichier résultat et du fichier référence que l'on compare
  string nomFichierRes_;
  string nomFichierRef_;

  // tampon texte contenant le texte du fichier resultat
  TamponTexte tamponRes_;
  // tampon texte contenant le texte du fichier référence
  TamponTexte tamponRef_;

  // précision des calculs souhaitée (pour la comparaison des valeurs numériques)
  double precision_;

  // valeur du décalage maximal toléré pour le repositionnement des analyseurs
  int decalageMax_;
  int decalageRencontreMax_;

  // nombre de lignes à ne pas analyser au début et à la fin du tampon résultat
  int suppLignesResDebut_;
  int suppLignesResFin_;

  // nombre de lignes à ne pas analyser au début et à la fin du tampon référence
  int suppLignesRefDebut_;
  int suppLignesRefFin_;

  // tableau de taille à 2 dimensions utilisés pour stockés les résultats 
  // du calcul de la "Longest Common Subsequence"
  int** tabLCS_;
};

#endif
