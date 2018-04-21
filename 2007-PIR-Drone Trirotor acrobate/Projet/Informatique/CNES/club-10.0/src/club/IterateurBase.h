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
//>       IterateurBase.h
//$Resume
//       fichier d'en-tête de la classe IterateurBase
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class IterateurBase
//$Historique
//       $Log: IterateurBase.h,v $
//       Revision 1.4  2002/12/09 15:54:03  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.3  2000/10/24 14:18:14  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 1.2  2000/07/03 08:49:05  club
//       Ajout du copyright CNES
//
//       Revision 1.1.2.2  2000/04/04 07:08:08  club
//       déplacement du copyright
//
//       Revision 1.1.2.1  2000/03/30 14:46:55  club
//       ajout du copyright CNES
//
//       Revision 1.1  1999/03/15 15:04:06  club
//       version initiale
//
//$Version
//       $Id: IterateurBase.h,v 1.4 2002/12/09 15:54:03 club Exp $
//
//$Auteur
//        P-A.Cros CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_IterateurBase_h
#define club_IterateurBase_h

#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class IterateurBase
//$Resume
//       classe abstraite de définition de l'interface minimale d'un itérateur
//       sur une structure de données, l'unité de parcours (élément) est propre 
//       a chaque classe dérivée de cet itérateur (caractère, champ,...)
//$Description
//       classe de base mémorisant la notion d'état de l'itérateur
//       et les opérations indispensables a un objet itérateur
//       
//$Usage
//>     construction :
//          protégée car seuls les classes dérivées peuvent instancier
//          un itérateur de base
//>     utilisation  : 
//>       virtual void premier   () 
//          positionne l'itérateur sur le premier élément de la structure
//          de données
//>       virtual void dernier   () 
//          positionne l'itérateur sur le dernier élément de la structure
//          de données
//>       virtual void allerSur  ()
//          positionne l'itérateur sur l'élément i de la structure
//          de données
//>       virtual int termine    ()
//          indique que l'itérateur est a la fin de la structure
//          de données
//>       virtual int nombreIterations
//          renvoie le nombre d'éléments de la structure de données
//>       virtual int operator++ ()
//          positionne l'itérateur sur l'élément suivant de la structure
//          de données
//>       virtual int operator-- ()
//          positionne l'itérateur sur l'élément suivant de la structure
//          de données
//>       void controleEtat()
//          retourne vrai si l'état de l'itérateur est conforme à l'état du 
//          tampon
//$Auteur
//        P-A.Cros
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


class IterateurBase {

public:

  // positionnement du pointeur :
  virtual void premier          ()           throw(ClubErreurs) = 0;
  virtual void dernier          ()           throw(ClubErreurs) = 0;
  virtual void allerSur         (int index ) throw(ClubErreurs) = 0;

  // indicateur d'etat de l'iterateur :
  virtual int  termine          ()  const                       = 0;

  // mecanisme d'iteration :
  virtual int  nombreIterations ()  const    throw(ClubErreurs) = 0;
  virtual int  operator++(int)               throw(ClubErreurs) = 0;
  virtual int  operator--(int)               throw(ClubErreurs) = 0;

protected :
  // variable permettant de controler l'etat de l'iterateur. 
  unsigned long etat_; 

  // protection des constructeurs pour eviter toute instanciation.
  IterateurBase() : etat_ (0) {}
  IterateurBase (const IterateurBase & other)
  {
    etat_ = other.etat_;
  }
  virtual IterateurBase & IterateurBase::operator = (const IterateurBase & other)
  {
    if (this != &other)
      etat_ = other.etat_;
    return *this;
  }

  // destructeur
  virtual ~IterateurBase () {}

  // etat de l'iterateur :
  virtual void  controleEtat() const throw(ClubErreurs) = 0;

};


#endif
