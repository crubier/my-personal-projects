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
//>       IterateurCaractere.h
//$Resume
//       fichier d'en-t�te de la classe IterateurCaractere
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class IterateurCaractere
//$Historique
//       $Log: IterateurCaractere.h,v $
//       Revision 1.5  2002/12/09 15:54:21  club
//       DM-ID 12 Mise en conformit� des constructeurs/destructeurs avec la norme qualit�
//
//       Revision 1.4  2000/10/24 14:18:14  club
//       mise � jour des includes et ajout des tests de configuration.
//
//       Revision 1.3  2000/07/03 08:49:05  club
//       Ajout du copyright CNES
//
//       Revision 1.2.2.2  2000/04/04 07:08:08  club
//       d�placement du copyright
//
//       Revision 1.2.2.1  2000/03/30 14:46:55  club
//       ajout du copyright CNES
//
//       Revision 1.2  1999/07/06 15:24:16  club
//       Changement des signatures pour gestion des erreurs
//       par m�canisme d'exception
//
//       Revision 1.1  1999/03/15 15:04:40  club
//       version initiale
//
//$Version
//       $Id: IterateurCaractere.h,v 1.5 2002/12/09 15:54:21 club Exp $
//
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//        G. Lajon  CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_IterateurCaractere_h
#define club_IterateurCaractere_h

#include "club/IterateurAscii.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class IterateurCaractere
//$Resume
//
//$Description
//
//$Usage
//>     construction :
//          avec r�f�rence ou avec pointeur sur un tampon ascii
//>     utilisation : 
//>       void premier         () 
//          positionne l'it�rateur sur le premier caract�re du tampon
//>       void dernier         () 
//          positionne l'it�rateur sur le dernier caract�re du tampon
//>       void allerSur        () 
//          positionne l'it�rateur sur l'�l�ment i du tampon
//>       int termine          ()
//          indique que l'it�rateur est a la fin du tampon
//>       int nombreIterations ()
//          renvoie le nombre de caract�res du tampon
//>       int operator++       () 
//          positionne l'it�rateur sur le caract�re suivant du tampon
//>       int operator--       () 
//          positionne l'it�rateur sur le caract�re pr�c�dent du tampon
//>       int longueurElement  () 
//          renvoie la longueur du caract�re
//>       const char* valeur   () 
//          renvoie la valeur du caract�re courant point� par l'it�rateur
//>       void synchronize     () 
//          si direction = 1 synchronise la position de l'it�rateur 
//          sur la position r�elle dans le tampon (it�rateur alt�r� 
//          lors d'une modification du tampon)
//          si direction = 0 (par defaut)
//          synchronise l'�tat du tampon (position courante du curseur) 
//          sur la position courante de l'it�rateur (m�morisation avant
//          alt�ration du tampon)  
//>       void actualiseEtat   () protegee - 
//          remet l'it�rateur en conformit� avec l'�tat courant du tampon
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//        G. Lajon  CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////



class IterateurCaractere : public IterateurAscii {

public :

  // constructeurs :
  IterateurCaractere( const TamponAscii& tampon )  throw(ClubErreurs);
  IterateurCaractere( TamponAscii* tampon )        throw(ClubErreurs);

  ~IterateurCaractere () {}

  // positionnement du pointeur :
  void                premier          ()          throw(ClubErreurs);
  void                dernier          ()          throw(ClubErreurs);
  void                allerSur         (int index) throw(ClubErreurs);

  // indicateur d'etat de l'iterateur :
  int                 termine          () const;

  // mecanisme d'iteration :
  int                 nombreIterations () const    throw(ClubErreurs);
  int                 operator++       (int)       throw(ClubErreurs);
  int                 operator--       (int)       throw(ClubErreurs);

  // informations diverses
  const char*         valeur           () const throw(ClubErreurs);
  int                 longueurElement  (int avecFin = 0) const 
    throw(ClubErreurs)
    { return 1; }

 // mises a jour
  void                synchronize      (int direction = 0) throw(ClubErreurs);

protected :
  char* caractereCourant_;

  void actualiseEtat()
       { etat_ = etat(); caractereCourant_ = courant(); } 

  IterateurCaractere () 
    : IterateurAscii ()
  {
    caractereCourant_ = '\0';
  }

  IterateurCaractere (const IterateurCaractere & other)
  {
    caractereCourant_ = other.caractereCourant_;
  }

  IterateurCaractere & operator = (const IterateurCaractere & other)
  {
    if (this != &other)
      caractereCourant_ = other.caractereCourant_;
    return *this;
  }

};


#endif