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
//>       TamponAscii.h
//$Resume
//       fichier d'en-tête de la classe TamponAscii
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class TamponAscii            
//>       inline ostream& operator <<()
//$Historique
//       $Log: TamponAscii.h,v $
//       Revision 1.7  2000/10/25 09:31:44  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.6  2000/10/24 14:18:15  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.5  2000/09/11 12:18:50  club
//       Mise à jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas installé.
//
//       Revision 1.4  2000/09/07 07:43:03  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.3  2000/07/03 08:53:50  club
//       Ajout du copyright CNES
//
//       Revision 1.2.2.2  2000/04/04 07:08:09  club
//       déplacement du copyright
//
//       Revision 1.2.2.1  2000/03/30 14:46:58  club
//       ajout du copyright CNES
//
//       Revision 1.2  1999/07/06 15:24:17  club
//       Changement des signatures pour gestion des erreurs
//       par mécanisme d'exception
//
//       Revision 1.1  1999/03/15 15:07:58  club
//       version initiale
//
//$Version
//       $Id: TamponAscii.h,v 1.7 2000/10/25 09:31:44 club Exp $
//
//$Auteur
//        P-A.Cros   CSSI
//        M. Julien  CSSI 
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


#ifndef club_TamponAscii_h
#define club_TamponAscii_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <iostream>
#include <fstream>
#include <string>

#include "club/TamponBase.h"
#include "club/IterateurAscii.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class TamponAscii
//$Resume
//
//$Description
//
//$Usage
//>     construction : 
//          avec argument d'interprétation des commentaires
//          par défaut les commentaires sont interprétés
//          (non considérés dans les actions)
//          le tampon peut être créé à partir d'un nom de fichier à lire
//          ou d'un pointeur de fichier
//>     utilisation  : 
//>       TamponAscii& operator =             () 
//          affectation
//>       void  positionneInterprete          ()
//          modification du drapeau d'interprétation des commentaires
//>       void initCarCommentaires            () 
//          utilise les caractères de str comme marqueurs de
//          commentaires. Si str est la chaîne vide ou le pointeur
//          nul, cette fonction réinitialise à la valeur par défaut
//          qui est "#".
//>       void ajouteCarCommentaires          () 
//          ajoute les caractères de str à la liste des caractères
//          marqueurs de commentaires.
//>       const string& carCommentaires       () 
//          retourne la liste des caractères marqueurs de
//          commentaires.
//>       void elimineCommentaires             () 
//          élimine les caractères qui vont d'un caractère marqueur de
//          commentaire à la fin de la ligne (sauf si le marqueur est
//          dans une chaîne entre '"'). 
//          
//>       void initSeparateurs                () 
//          utilise les caractères de str comme caractères séparateurs
//          de champs. Si str est la chaîne vide ou le pointeur nul,
//          cette fonction réinitialise à la valeur par défaut qui est
//          "\t\n\v\f\r ".
//>       void ajouteSeparateurs              () 
//          ajoute les caractères de str à la liste des caractères
//          séparateurs.
//>       const string& separateurs            () 
//          retourne la liste des caractères séparateurs.
//>       void elimineBlancs                   () 
//          élimine les caractères blancs de début et de fin de ligne
//          (pour une ligne entièrement blanche, le '\n' est également
//          éliminé).
//>       void insereDebut                     () 
//          insère avant l'itérateur pos une chaîne de caractères
//>       void insereFin                       () 
//          insère après l'itérateur pos une chaîne de caractères
//>       void supprime                        () 2 signatures - 
//          supprime l'élément courant pointé par l'itérateur
//          ou une zone comprise entre deux itérateurs
//>       void remplace                        () 2 signatures -
//          remplace l'élément courant pointé par l'itérateur
//          ou une zone comprise entre deux itérateurs
//          par une chaîne de caractères
//>       int estCarGuillemet                 () protegee - 
//          retourne vrai si le caractère c est un guillemet
//>       int estCarCommentaire               () protegee - 
//          retourne vrai si le caractère c est un marqueur de commentaire
//>       int estSeparateur                   () protegee - 
//          retourne vrai si le caractère c est un séparateur
//>       int supprimeZone                    () protegee - 
//          supprime une zone entre deux pointeurs de caractères
//          (les itérateurs créés sur le tampon ne sont plus valides)
//>       int insereZone                      () protegee - 
//          insère une zone à la position de l'itérateurs pos
//          (les itérateurs créés sur le tampon ne sont plus valides)
//$Auteur
//        P-A.Cros   CSSI
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

class IterateurAscii;

class TamponAscii : public TamponBase {


public :



  // Constructeurs :

  TamponAscii (int interprete = 1) : interprete_ (interprete)
    { initCarCommentaires (NULL); initSeparateurs (NULL); }

  TamponAscii (FILE* ptrFic, int interprete = 1) throw(ClubErreurs);
  TamponAscii (const char* nom, int interprete = 1) throw(ClubErreurs);

  // constructeur par copie et affectation
  TamponAscii             (const TamponAscii& t);
  TamponAscii             (const TamponAscii* t);
  TamponAscii& operator = (const TamponAscii& t);

  ~TamponAscii            () {}
  // fonctions de filtrage

  // modification du drapeau interprete :
  void                positionneInterprete ( int interprete )
    { interprete_ = interprete; }
  int                 interprete() const
    { return interprete_; }

  // Gestion des commentaires :
  void                initCarCommentaires   (const char* chaine);
  void                ajouteCarCommentaires (const char* chaine);
  const string&       carCommentaires       () const
    { return carCommentaires_; }
  void                elimineCommentaires   () throw(ClubErreurs);

  // Gestion des separateurs :
  void                initSeparateurs       (const char* chaine);
  void                ajouteSeparateurs     (const char* chaine);
  const string&       separateurs           () const
    { return separateurs_; }
  // Gestion des blancs :
  void                elimineBlancs         ();

  
  // fonctions de modification du buffer

  // Insertions :
  void                insereDebut           (IterateurAscii& pos,
					     const char*     valeur )
    throw(ClubErreurs);
  void                insereFin             (IterateurAscii& pos,
					     const char*     valeur )
    throw(ClubErreurs);
  // Suppressions :
  void                supprime              (IterateurAscii& pos )
    throw(ClubErreurs);
  void                supprime              (IterateurAscii& debut,
					     IterateurAscii& fin )
    throw(ClubErreurs);
  // Remplacements :
  void                remplace              (IterateurAscii& pos,
					     const char *    valeur )
    throw(ClubErreurs);
  void                remplace              (IterateurAscii& debut,
					     IterateurAscii& fin,
					     const char*     valeur )
    throw(ClubErreurs);

 
protected :

 // declaration de visibilite pour les iterateurs sur des tampons ascii :

  friend class IterateurAscii;

  string carCommentaires_;
  string separateurs_;
  int    interprete_;


  int         estCarGuillemet      (char c) const;
  int         estCarCommentaire    (char c) const;
  int         estSeparateur        (char& c) const;

  int         supprimeZone         (char* zdebut, char* zfin);
  int         insereZone           (char* pos, const char* valeur);


};


inline ostream& operator << (ostream& s, const TamponBase& t)
{ return s << t.total (); }

#endif
