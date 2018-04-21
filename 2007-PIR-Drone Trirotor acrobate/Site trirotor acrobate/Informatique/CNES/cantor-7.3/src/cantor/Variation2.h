///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       Cantor
//
//$Nom
//>       Variation2.h
//
//$Resume
//       fichier d'en-tête de la classe Variation2
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Variation2
//
//$Historique
//       $Log: Variation2.h,v $
//       Revision 1.13  2002/12/10 15:39:05  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui créé par le compilateur
//
//       Revision 1.12  2002/12/02 13:49:45  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.11  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.10.4.1  2000/03/30 15:36:11  cantor
//       ajout du copyright CNES
//
//       Revision 1.10  1998/06/24 16:29:06  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.9  1998/04/26 15:24:16  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.8  1998/04/14 18:23:43  luc
//       suppression de la méthode estValide
//
//       Revision 1.7  1998/01/22 10:45:58  luc
//       mise en cohérence de listes d'initialisation de constructeurs
//       et de l'ordre des attributs dans la classe
//       amélioration de l'en-tête de classe
//
//       Revision 1.6  1997/07/06 10:36:56  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:39:53  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:22:23  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 10:57:09  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       
//       Revision 1.2  1994/11/26 15:16:12  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 15:02:52  luc
//       Initial revision
//
//$Version
//       $Id: Variation2.h,v 1.13 2002/12/10 15:39:05 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Variation2_h
#define __cantor_Variation2_h

#include "cantor/ValeurDerivee2.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Variation2
//
//$Resume
//       modélisation de la variation d'une fonction scalaire en un point
//
//$Description
//       modélisation de la variation d'une fonction scalaire en un point
//
//$Usage
//>     construction : 
//          sans argument, à partir d'un couple (x, y)
//>     utilisation  : 
//>       Variation2& operator =  () 
//          affectation
//>       int sens                () 
//          retourne le sens de variation
//>       int croissante          () 
//          teste si la fonction est croissante
//>       int decroissante        () 
//          teste si la fonction est décroissante
//>       int sensValide          () 
//          teste si le sens de variation est valide (c'est à dire non
//          forcé)
//>       double x                () 
//          retourne une copie de l'abscisse de calcul
//>       const ValeurDerivee2& y () 
//          retourne une référence constante sur la valeur de la
//          fonction
//>       void reinitialise       () 
//          réinitialise l'instance avec les caractéristiques d'un
//          nouveau point
//>       void simuleCroissante   () 
//          force le sens de variation
//>       void simuleDecroissante () 
//          force le sens de variation
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Variation2
{ 
  
public :

  // constructeurs
  Variation2 () : sens_ (+1), sensValide_ (0), x_ (0), y_ (0) {}

  Variation2 (double x, const ValeurDerivee2& y)
    : sensValide_ (1), x_ (x), y_ (y)
  { sens_ = (y_.f1 () >= 0.0) ? +1 : -1; }

  // copie constructeur et affectation
  Variation2 (const Variation2& v)
    : sens_ (v.sens_), sensValide_ (v.sensValide_), x_ (v.x_), y_ (v.y_)
  {}

  Variation2& operator = (const Variation2& v);

  // destructeur
  ~Variation2 () {}

  // fonctions d'accès aux éléments canoniques
  int                   sens         () const { return sens_;               }
  int                   croissante   () const { return (sens_ > 0) ? 1 : 0; }
  int                   decroissante () const { return (sens_ > 0) ? 0 : 1; }
  int                   sensValide   () const { return sensValide_;         }
  double                x            () const { return x_;                  }
  const ValeurDerivee2& y            () const { return y_;                  }

  // fonctions de mise a jour de l'ensemble des attributs
  void              reinitialise (double x, const ValeurDerivee2& y)
  { x_ = x; y_ = y; sens_ = (y_.f1 () >= 0.0) ? +1 : -1; sensValide_ = 1; }

  // fonctions de mise a jour du sens de variation
  void              simuleCroissante   () { sens_ = +1; sensValide_ = 0; }
  void              simuleDecroissante () { sens_ = -1; sensValide_ = 0; }

private :

  int              sens_;
  int              sensValide_;
  double           x_;
  ValeurDerivee2   y_;

};

#endif
