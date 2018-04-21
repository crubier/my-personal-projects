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
//>       IterateurChampLigne.h
//$Resume
//       fichier d'en-tête de la classe IterateurChampLigne
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class IterateurChampLigne
//$Historique
//       $Log: IterateurChampLigne.h,v $
//       Revision 1.5  2002/12/09 15:54:59  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.4  2000/10/24 14:18:15  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.3  2000/07/03 08:49:05  club
//       Ajout du copyright CNES
//
//       Revision 1.2.2.2  2000/04/04 07:08:09  club
//       déplacement du copyright
//
//       Revision 1.2.2.1  2000/03/30 14:46:55  club
//       ajout du copyright CNES
//
//       Revision 1.2  1999/07/06 15:24:16  club
//       Changement des signatures pour gestion des erreurs
//       par mécanisme d'exception
//
//       Revision 1.1  1999/03/15 15:05:36  club
//       version initiale
//
//$Version
//       $Id: IterateurChampLigne.h,v 1.5 2002/12/09 15:54:59 club Exp $
//
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//        G. Lajon  CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_IterateurChampLigne_h
#define club_IterateurChampLigne_h

#include "club/IterateurAscii.h"
#include "club/IterateurLigne.h"
#include "club/IterateurChamp.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class IterateurChampLigne
//$Resume
//        classe itérateur qui parcourt par ligne puis par champ un tampon ascii
//
//$Description
//        la classe hérite de manière virtuelle de la classe
//        IterateurAscii, ce qui permet lors d'une dérivation multiple
//        de cette classe de partager les méthodes et attributs de la classe
//        IterateurAscii ( sinon une instance par classe de base dans le cas
//        d'un héritage multiple ).
//$Usage
//>     construction :
//          avec référence ou avec pointeur sur un tampon ascii
//>     utilisation : 
//>       void premier                () 
//          positionne l'itérateur sur le premier champ de la  première ligne 
//          du tampon
//>       void dernier                () 
//          positionne l'itérateur sur le dernier champ de la dernière ligne 
//          du tampon
//>       void allerSur               () 2 signatures -
//          positionne l'itérateur sur le champ c de la ligne l du tampon
//          ou sur le champ c de la ligne courante
//>       int termine                 ()
//          indique que l'itérateur est a la fin du tampon
//>       int nombreIterations        ()
//          renvoie le nombre de lignes du tampon
//>       int nombreIterationsChamps  ()
//          renvoie le nombre de champs dans la ligne l
//          ou dans la ligne courante (si l = 0, par défaut) 
//>       int operator++              () 
//          positionne l'itérateur sur le champ suivant du tampon
//>       int operator--              () 
//          positionne l'itérateur sur le champ précédent du tampon
//>       int longueurElement         () 
//          renvoie la longueur du champ courant
//>       const char* valeur          () 
//          renvoie la valeur du champ courant
//>       void synchronize            () 
//          si direction = 1 synchronise la position de l'itérateur 
//          sur la position réelle dans le tampon (itérateur altéré 
//          lors d'une modification du tampon)
//          si direction = 0 (par defaut)
//          synchronise l'état du tampon (position courante du curseur) 
//          sur la position courante de l'itérateur (mémorisation avant
//          altération du tampon)  
//>       void actualise              () 
//          réinitialise l'itérateur sur le début du tampon
//$Auteur
//        P-A.Cros
//        G. Lajon    CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


class IterateurChampLigne :public IterateurChamp,
                           public IterateurLigne{

public :

  // constructeurs :
  IterateurChampLigne( const TamponAscii &tampon, int compterChampsLignes = 1)
    throw(ClubErreurs);
  IterateurChampLigne( const TamponAscii* tampon, int compterChampsLignes = 1) 
    throw(ClubErreurs);

  // destructeur
  ~IterateurChampLigne () {}

  void                premier               () throw(ClubErreurs);
  void                dernier               () throw(ClubErreurs);
  void                allerSur              (int champ,
					     int ligne ) throw(ClubErreurs);
  void                allerSur              (int index) throw(ClubErreurs);

  int                 termine               () const;

  int                 nombreIterations      () const throw(ClubErreurs);
  int                 nombreIterationsChamps(int l = 0) throw(ClubErreurs);
  int                 operator++            (int) throw(ClubErreurs);
  int                 operator--            (int) throw(ClubErreurs);
  int                 longueurElement       (int avecFin = 0) const
    throw(ClubErreurs);
  const char*         valeur                () const throw(ClubErreurs);

  void                synchronize           (int direction = 0) 
    throw(ClubErreurs);

  void                actualise             () throw(ClubErreurs);

protected :
  // constructeur par defaut
  IterateurChampLigne ()
    : IterateurChamp(), IterateurLigne()
  {}

private :

  void                actualiseEtat         ();

  void                rechercheChampLigne   (int c) throw(ClubErreurs);
  void                debutDeChampLigne     (const char* mobile);


  // AUTRES CONSTRUCTEURS

  // IMPORTANT : Les constructeurs définient ci-après sont
  // des membres privés parce qu'il faut en interdire
  // l'utilisation intempestive.

  // constructeur par copie
  IterateurChampLigne (const IterateurChampLigne & other) {}

  // constructeur par affectation
  // Due a l'heritage multiple ,et, meme s'il est possible de definir
  // cet operateur, nous preferons en interdire l'utilisation
  // dangereuse sans savoir plainement ce qui est fait
  IterateurChampLigne & operator = (const IterateurChampLigne & other)
  {
    return *this;
  }

};

#endif
