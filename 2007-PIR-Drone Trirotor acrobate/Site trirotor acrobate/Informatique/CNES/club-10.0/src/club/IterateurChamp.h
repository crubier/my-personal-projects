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
//>       IterateurChamp.h
//$Resume
//       fichier d'en-tête de la classe IterateurChamp
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class IterateurChamp
//$Historique
//       $Log: IterateurChamp.h,v $
//       Revision 1.5  2002/12/09 15:54:37  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.4  2000/10/24 14:18:15  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.3  2000/07/03 08:49:05  club
//       Ajout du copyright CNES
//
//       Revision 1.2.2.3  2000/04/04 07:08:09  club
//       déplacement du copyright
//
//       Revision 1.2.2.2  2000/04/03 16:37:51  club
//       ajout de ClubErreurs dans la liste des exceptions déclenchées par les
//       constructeurs
//
//       Revision 1.2.2.1  2000/03/30 14:46:55  club
//       ajout du copyright CNES
//
//       Revision 1.2  1999/07/06 15:24:16  club
//       Changement des signatures pour gestion des erreurs
//       par mécanisme d'exception
//
//       Revision 1.1  1999/03/15 15:05:13  club
//       version initiale
//
//$Version
//       $Id: IterateurChamp.h,v 1.5 2002/12/09 15:54:37 club Exp $
//
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//        G. Lajon  CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_IterateurChamp_h
#define club_IterateurChamp_h

#include "club/TamponAscii.h"
#include "club/IterateurAscii.h"
#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class IterateurChamp
//$Resume
//        classe itérateur qui parcourt champ à champ un tampon ascii
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
//          positionne l'itérateur sur le premier champ du tampon
//>       void dernier                () 
//          positionne l'itérateur sur le dernier champ du tampon
//>       void allerSur               () 
//          positionne l'itérateur sur le champ c du tampon
//>       int termine                 ()
//          indique que l'itérateur est a la fin du tampon
//>       int nombreIterations        ()
//          renvoie le nombre de champs du tampon
//>       int operator++              () 
//          positionne l'itérateur sur le champ suivant du tampon
//>       int operator--              () 
//          positionne l'itérateur sur le champ précédent du tampon
//>       int longueurElement         () 
//          renvoie la longueur du champ
//>       const char* valeur          () 
//          renvoie la valeur du champ courant pointé par l'itérateur
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
//>       void actualiseEtat          () protegee - 
//          remet l'itérateur en conformité avec l'état courant du tampon
//>       int analyseChamp            () protegee - 
//          analyse lexicale du champ courant avec mémorisation de la
//          valeur du champ 
//>       int compteChamps            () protegee - 
//          retourne le nombre de champs a partir d'une position donnee
//          jusqu'à la fin de ligne ou fin de tampon 
//>       const char* sauteChampAvant () protegee - 
//          saute n champs a partir d'une position donnee
//>       void rechercheChamp          () protegee - 
//          recherche du champ numero c
//>       void debutDeChamp           () protegee - 
//          positionner la position courante sur un début de champ
//$Auteur
//        P-A.Cros
//        G. Lajon   CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


class IterateurChamp : public virtual IterateurAscii {


public :

  // constructeurs :
  IterateurChamp( const TamponAscii& tampon, int compterChamps = 1 )
    throw(ClubErreurs);
  IterateurChamp( const TamponAscii* tampon, int compterChamps = 1 )
    throw(ClubErreurs);

  // destructeur
  ~IterateurChamp () {}

  void                premier          ()  throw(ClubErreurs);
  void                dernier          ()  throw(ClubErreurs);
  void                allerSur         (int index)  throw(ClubErreurs);

  int                 termine          () const;

  int                 nombreIterations ()  const throw(ClubErreurs);
  int                 operator++       (int)  throw(ClubErreurs);
  int                 operator--       (int)  throw(ClubErreurs);

  int                 longueurElement  (int avecFin = 0) const 
    throw(ClubErreurs);
  const char*         valeur           ()  const throw(ClubErreurs);

  void                synchronize      (int direction = 0)  throw(ClubErreurs);
  void                actualise        ();

protected :
  char *debutChamp_;
  int   numChamp_;
  int   nombreChamps_;

  void        actualiseEtat            ();

  int         analyseChamp             (const char*   mobile,
                                        int           sauteFinLigne) const
    throw(ClubErreurs);
  int         compteChamps             (char*   mobile,
                                        int           sauteFinLigne) const;
  const char* sauteChampAvant          (char*   mobile,
                                        int           n,
                                        int           sauteFinLigne) const;
  void        rechercheChamp           (int           c, 
                                        int           sauteFinLigne) 
    throw(ClubErreurs);
  void        debutDeChamp             (const char *mobile,
                                        int sauteFinLigne);
  // autres constructeurs
  IterateurChamp ()
    : IterateurAscii ()
  {
    *debutChamp_  = '\0';
    numChamp_     = 0;
    nombreChamps_ = 0;

  }
  IterateurChamp (const IterateurChamp & other)
  {
    debutChamp_  = other.debutChamp_ ;
    numChamp_     = other.numChamp_ ;
    nombreChamps_ = other.nombreChamps_ ;
  }
  IterateurChamp & operator = (const IterateurChamp & other)
  {
    if ( this != &other )
    {
      debutChamp_  = other.debutChamp_ ;
      numChamp_     = other.numChamp_ ;
      nombreChamps_ = other.nombreChamps_ ;
    }
    return *this;
  }

};

#endif
