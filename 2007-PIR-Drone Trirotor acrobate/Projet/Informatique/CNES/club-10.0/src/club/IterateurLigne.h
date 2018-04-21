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
//>       IterateurLigne.h
//$Resume
//       fichier d'en-tête de la classe IterateurLigne
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class IterateurLigne
//$Historique
//       $Log: IterateurLigne.h,v $
//       Revision 1.6  2003/07/17 12:38:28  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 1.5  2002/12/09 15:55:17  club
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
//       Revision 1.1  1999/03/15 15:06:06  club
//       version initiale
//
//$Version
//       $Id: IterateurLigne.h,v 1.6 2003/07/17 12:38:28 club Exp $
//
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//        G. Lajon  CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_IterateurLigne_h
#define club_IterateurLigne_h

#include "club/IterateurAscii.h"
#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class IterateurLigne
//$Resume
//        classe itérateur qui parcourt ligne à ligne un tampon ascii
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
//          positionne l'itérateur sur la première ligne du tampon
//>       void dernier                () 
//          positionne l'itérateur sur la dernière ligne du tampon
//>       void allerSur               () 
//          positionne l'itérateur sur la ligne l du tampon
//>       int termine                 ()
//          indique que l'itérateur est a la fin du tampon
//>       int nombreIterations        ()
//          renvoie le nombre de lignes du tampon
//>       int operator++              () 
//          positionne l'itérateur sur la ligne suivante du tampon
//>       int operator--              () 
//          positionne l'itérateur sur la ligne précédente du tampon
//>       int longueurElement         () 
//          renvoie la longueur de la ligne
//>       const char* valeur          () 
//          renvoie la valeur de la ligne courante 
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
//>       void rechercheLigne           () protegee - 
//          recherche de la ligne i
//>       int compteLignes            () protegee - 
//          retourne le nombre de lignes a partir d'une position donnee
//          jusqu'à la fin de tampon 
//$Auteur
//        P-A.Cros
//        G. Lajon   CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////




class IterateurLigne : public virtual IterateurAscii {


public :

  // constructeurs :
  IterateurLigne( const TamponAscii& tampon, int compterLignes = 1 ) 
    throw(ClubErreurs);
  IterateurLigne( TamponAscii* tampon, int compterLignes = 1 ) 
    throw(ClubErreurs);

  // destructeur
  ~IterateurLigne () {}

  void                premier          () throw(ClubErreurs);
  void                dernier          () throw(ClubErreurs);
  virtual void        allerSur         (int index)  throw(ClubErreurs);

  int                 termine          () const;

  int                 nombreIterations ()  const throw(ClubErreurs);
  int                 operator++       (int) throw(ClubErreurs);
  int                 operator--       (int)  throw(ClubErreurs);

  int                 longueurElement  (int avecFin = 0) const 
    throw(ClubErreurs);
  const char*         valeur           ()  const throw(ClubErreurs);

  void                synchronize      (int direction = 0)  throw(ClubErreurs);
  void                actualise        ();

protected :
  char* debutLigne_;
  int   numLigne_; 
  int   nombreLignes_;

  void                actualiseEtat          ();

  void                rechercheLigne         (int l) throw(ClubErreurs);
  int                 compteLignes           (const char* mobile) const;

  // autres constructeurs
  IterateurLigne () 
  {
    debutLigne_   = NULL;
    numLigne_     = 0;
    nombreLignes_ = 0;
  }
  IterateurLigne (const IterateurLigne & other)
  {
    debutLigne_   = other.debutLigne_;
    numLigne_     = other.numLigne_;
    nombreLignes_ = other.nombreLignes_;
  }
  IterateurLigne & operator = (const IterateurLigne & other)
  {
    if (this != &other)
    {
      debutLigne_   = other.debutLigne_;
      numLigne_     = other.numLigne_;
      nombreLignes_ = other.nombreLignes_;
    }
    return *this;
  }

};


#endif
