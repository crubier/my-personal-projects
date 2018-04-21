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
//>       ComparateurLigne.h
//$Resume
//       fichier d'en-tête de la classe ComparateurLigne
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class ComparateurLigne
//>       inline int max()      
//>       inline int min()      
//$Historique
//       $Log: ComparateurLigne.h,v $
//       Revision 1.9  2001/04/04 11:28:24  club
//       ajout de la reconnaissance des réels du langage fortran
//
//       Revision 1.8  2001/02/16 12:24:27  club
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
//       Revision 1.4  2000/10/23 13:56:05  club
//       modification de l'initialisation des chaînes nomFichierRes et nomFichierRef
//       pour coriger un bug.
//
//       Revision 1.3  2000/09/07 08:42:02  club
//       utilisation de string de la STL au lieu de ChaineSimple conformément
//       aux évolutions réalisées sur les classes de l'interface publique de club.
//
//       Revision 1.2  2000/08/03 08:32:23  club
//       utilisation d'un code de retour plutôt que la levée d'une exception
//       pour la fonction analyserLigne.
//
//       Revision 1.1  2000/07/26 09:48:06  club
//       Suite à la destruction du répertoire club/utils/club, déplacement
//       des fichiers .h dans le répertoire club/utils.
//
//       Revision 1.3  2000/07/26 07:30:03  club
//       modification profonde de la classe ComparateurLigne pour simplifier
//       et améliorer la comparaison et l'analyse de deux lignes.
//       Dans la classe interne AnalyseurLexicalDifference, suppression de
//       l'attribut nbLexemes_ et modification de la méthode fournissant
//       le nombre de lexèmes.
//
//       Revision 1.2  2000/07/07 09:50:33  club
//       ajout de la méthode formaterMessage permettant de créer
//       le message de différence
//
//       Revision 1.1  2000/07/03 09:26:23  club
//       création d'une classe fournissant des services pour comparer de
//       lignes d'un fichier tout en acceptant une imprécision numérique.
//       cette classe est utilisée par l'utilitaire difference
//
//$Version
//       $Id: ComparateurLigne.h,v 1.9 2001/04/04 11:28:24 club Exp $
//
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_ComparateurLigne_h
#define __club_ComparateurLigne_h

#include <club/ClubConfig.h>
#include <ClubConfigNoInstall.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#ifdef HAVE_STL
#include <map>
#include <string>
#endif

#include "StatDifference.h"

#include "club/AnalyseurLexical.h"
#include "club/ClubErreurs.h"
#include "club/Traducteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ComparateurLigne
//$Resume
//       classe permettant de comparer une ligne d'un fichier résultat avec
//       une ligne d'un fichier référence
//
//$Description
//       Cette classe permet de comparer deux lignes en acceptant une
//       imprecision numérique sur les réels. Elle permet de formater
//       un message de différence concernant la ligne et elle met à jour des
//       statistiques sur les différences. Il est possible de recaler
//       les tampons si certaines lignes sont propres à un seul d'entre eux.
//       L'algorithme utilisé pour connaître quelles sont les lignes communes,
//       propres à un fichier ou propres à l'autre s'inspire de l'algorithme
//       "Longest Common Subsequence". Cet algorithme est fourni à l'adresse 
//       suivante valide au 24/07/2000 :
//          http://www.ics.uci.edu/~eppstein/161/960229.html
//       L'algorithme utilisé ne permet pas forcément d'avoir la plus longue
//       séquence commune mais permet de facon simple de s'en approcher voire
//       de la trouver.
// 
//$Usage
//>     construction : 
//          à partir de deux noms de fichiers et d'une valeur indiquant la 
//          précision numérique souhaitée
//>     utilisation  : 
//>       void initialiser           () 
//          après la création de l'instance, cette méthode permet d'initialiser
//          les analyseurs lexicaux avec des chaines de caractères fournies
//          en paramètres.
//>       int analyserLigne          ()
//          permet de comparer les deux lignes et si nécessaire de repositionner
//          les analyseurs lexicaux si certains lexèmes ne sont que dans une
//          des deux lignes. Retourne le nombre de différences entre
//          les deux lignes.
//>       bool comparerLigne         ()
//          compare la ligne res avec la ligne ref. Retourne true si les lignes
//          sont égales, false sinon. 
//
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class ComparateurLigne
{

public :

  // constructeur
  ComparateurLigne (const string& fichierRes, const string& fichierRef, 
                    double precision)
    : nomFichierRes_ (fichierRes.c_str ()), nomFichierRef_ (fichierRef.c_str ()),
      alres_ (" "), alref_ (" "), precision_ (precision)
  {
    alres_.autoriseReelsFortran ();
    alref_.autoriseReelsFortran ();
  }

  // initialise le comparateur de lignes avec les lignes cres et cref.
  void initialiser (const string& cres, int numLigneRes,
                    const string& cref, int numLigneRef);

  // comparaisons des lexèmes de alres_ et alref_ par une méthode gloutonne
  int analyserLigne (StatDifference& stats);

  // fonction permettant de comparer la ligne de alres_ avec celle de alref_
  // Retourne true si les lignes sont égales, false sinon.
  bool comparerLigne ();

  // retourne la chaine messageDiff_
  const string& messageDiff () const
  { return messageDiff_; }

private :

  // calcul les positions dans le fichier res et ref des deux premiers 
  // lexèmes égaux en favorisant des positions proches. C'est à dire que
  // si les 1er et 2ème lexèmes de res sont égaux au 3ème lexème de ref,
  // la fonction retournera numeroRes = 2 et numeroRef = 3.
  void lexemesSuivantsIdentiques (int& numeroRes, int& numeroRef);

  // méthode permettant de formater le message de différence
  void formaterMessage (int index, double diff);

  // compare les lexèmes courants en acceptant une différence numérique
  // Retourne :
  //  - 0 : si les lexèmes sont égaux
  //  - 1 : si les lexèmes sont des chaines de caractères différentes
  //  - 2 : si les lexèmes sont deux entiers différents
  //  - 3 : si les lexèmes sont des valeurs numériques différentes
  int comparerLexeme (double& diff);

  // classe dérivée de AnalyseurLexical ajoutant la notion de
  // valeur numérique (englobe entier et reel) et fournissant le nombre
  // de lexèmes analysés
  class AnalyseurLexicalDifference : public AnalyseurLexical
  {
    double derniereValeurNumerique_;
    
  public :
    
    // constructeur
    AnalyseurLexicalDifference (const string& c) : 
      AnalyseurLexical (c)
    {};
    
    // mise a jour
    void majValeurNumerique (double x) { derniereValeurNumerique_ = x; }
    
    // lecture
    int nbLexemes ()
    {
      redemarre ();
      int nbLexemes = 0;
      while (suivant () != codeFin)
        nbLexemes++;
      return nbLexemes; 
    }

    double valeurNumerique () const { return derniereValeurNumerique_; }    
  };

  // noms du fichier résultat et du fichier référence que l'on compare
  string nomFichierRes_;
  string nomFichierRef_;

  // analyseurs lexicaux pour comparer la ligne du fichier res par rapport
  // à celle du fichier ref
  AnalyseurLexicalDifference alres_;
  AnalyseurLexicalDifference alref_;

  // chaines contenant le texte de toute la ligne à analyser
  string ligneRes_;
  string ligneRef_;

  // numéro de la ligne analysée dans le fichier
  int numeroLigneRes_;
  int numeroLigneRef_;

  // précision des calculs souhaitée
  double precision_;

  // message de différence sur la ligne
  string messageDiff_;
};

// calcule le maximum de deux entiers
inline int max (int i, int j) { return ((i<j) ? j : i); }

// calcule le minimum de deux entiers
inline int min (int i, int j) { return ((i<j) ? i : j); }

#endif
