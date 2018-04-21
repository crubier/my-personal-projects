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
//>       TamponBase.h
//$Resume
//       fichier d'en-tête de la classe TamponBase
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class TamponBase
//$Historique
//       $Log: TamponBase.h,v $
//       Revision 1.9  2002/12/09 15:58:33  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.8  2000/10/25 09:31:44  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.7  2000/10/24 14:18:15  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.6  2000/10/24 08:31:22  club
//       modification des includes du standard C : utilisation de cNAME au lieu
//       de NAME.h (pour permettre la compilation avec Sun Workshop 5.0)
//
//       Revision 1.5  2000/09/11 12:18:50  club
//       Mise à jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas installé.
//
//       Revision 1.4  2000/09/07 07:43:56  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//       ajout de l'include stdio.h
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
//       Revision 1.1  1999/03/15 15:08:28  club
//       version initiale
//
//$Version
//       $Id: TamponBase.h,v 1.9 2002/12/09 15:58:33 club Exp $
//
//$Auteur
//        P-A.Cros     CSSI
//        M. Julien    CSSI 
//        O. Queyrut   CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_TamponBase_h
#define club_TamponBase_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <cstdio>

#include <iostream>
#include <fstream>
# include <string>

#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class TamponBase
//$Resume
//
//$Description
//
//$Usage
//>     construction :
//        construction reservee aux classes derivees
//>     utilisation  : 
//>       void lit            () 2 signatures - 
//          lit un fichier référencé par son nom ou par un pointeur fichier
//          dans une zone mémoire
//>       void ecrit           () 
//          écrit le contenu de la zone mémoire dans un fichier
//>       const char* nom     () 
//          retourne le nom du fichier
//>       int estVide         () 
//          indique si la zone mémoire est vide ou non
//>       const char* total   () 
//          retourne un pointeur sur la zone mémoire
//>       int longueur        () 
//          retourne la longueur de la zone mémoire
//>       void nettoie         ()
//          vide le buffer sans libérer la mémoire 
//$Auteur
//        P-A.Cros     CSSI
//        O. Queyrut   CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


class TamponBase {

public : 


  // relecture d'un fichier
  void        lit                   (FILE* ptrFic )
    throw(ClubErreurs);
  void        lit                   (const char* nom = NULL )
    throw(ClubErreurs);
  // sauvegarde dans un fichier
  void        ecrit                 (const char* nom = 0 ) const
    throw(ClubErreurs);


  // routines d'accès globales
  const char* nom                   () const { return nom_.c_str ();     }
  int         estVide               () const { return ( total_ ==   0)
                                                   || (*total_ == '\0'); }
  char*       total                 () const { return total_;            }
  int         longueur              () const { return longueur_;         }

  // vider le buffer ( ! ne desalloue pas la memoire )
  void        nettoie               ()
  { etat_++; longueur_ = 0; courant_ = total_; }

protected :
  // attributs :
  string       nom_;
  char*        total_;
  int          tailleTampon_;
  int          longueur_;
  char*        courant_;
  // variable permettant de controler l'etat
  // du tampon. ( compte le nombre de modifications effectuees
  // depuis l'instanciation de l'objet ).
  unsigned long etat_;

  // le constructeur est protege pour empecher l'instanciation.
  TamponBase                        () 
    : nom_ (""), total_ (0), tailleTampon_ (0),
      longueur_ (0), courant_ (0), etat_ (0L)
    {;}
  ~TamponBase                       () { if( total_ ) delete[] total_; }

private :

  // AUTRES CONSTRUCTEURS
  TamponBase (const TamponBase & other) {}
  TamponBase & operator = (const TamponBase & other)
  {
    return *this;
  }

};


#endif
