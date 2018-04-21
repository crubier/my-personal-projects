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
//>       Resolution2Iterateur.h
//
//$Resume
//       fichier d'en-tête de la classe Resolution2Iterateur
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Resolution2Iterateur
//
//$Historique
//       $Log: Resolution2Iterateur.h,v $
//       Revision 1.13  2002/12/10 15:10:09  cantor
//       DM-ID 12 Ajout d'un destructeur, d'un operateur d'assignation et d'un constructeur par recopie pour prévenir ceux créés par le compilateur
//
//       Revision 1.12  2002/12/02 13:40:09  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.11  2001/06/05 15:30:03  cantor
//       suppression d'un argument inutilisé
//
//       Revision 1.10  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.9.4.1  2000/03/30 15:36:11  cantor
//       ajout du copyright CNES
//
//       Revision 1.9  1998/06/24 15:20:48  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.8  1998/04/26 15:24:06  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.7  1998/01/22 10:42:03  luc
//       amélioration de l'en-tête de classe
//
//       Revision 1.6  1997/07/06 10:31:41  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:39:49  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:22:18  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1994/12/12 15:14:44  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.2  1994/11/26 15:15:40  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 15:02:45  luc
//       Initial revision
//
//$Version
//       $Id: Resolution2Iterateur.h,v 1.13 2002/12/10 15:10:09 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Resolution2Iterateur_h
#define __cantor_Resolution2Iterateur_h

#include "cantor/Resolution2.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Resolution2Iterateur
//$Resume
//       itérateur sur tous les zéros d'une fonction
//
//$Description
//       itérateur sur tous les zéros d'une fonction
//       à l'interieur d'un intervalle
//
//$Usage
//>     construction : 
//          à partir de la fonction, d'un pointeur sur un argument,
//          des bornes de l'intervalle, d'un pas (ou d'un nombre
//          d'intervalle) de séparation des extremums locaux et de
//          seuils de convergence en x et y.
//>     utilisation  : 
//>       void reinitialise             () 
//          réinitialise la recherche
//>       double zeroSuivant            () 
//         retourne une copie de l'abscisse du zéro suivant (ou un
//         nombre très supérieur à la borne sup de l'intervalle de
//         recherche s'il n'y a plus de zéro)
//>       double convergenceX           () 
//          retourne une copie du seuil de convergence en x
//>       double convergenceY           () 
//          retourne une copie du seuil de convergence en y
//>       ValeurDerivee2 evalueFonction () 
//          retourne la valeur de la fonction en x
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Resolution2Iterateur
{ 

public :

  // constructeurs
  Resolution2Iterateur (TypeFoncVD2 f, void* arg, double a, double b,
                        double pas, double convergenceX, double convergenceY);
  Resolution2Iterateur (TypeFoncVD2 f, void* arg, double a, double b,
                        int n, double convergenceX, double convergenceY);

  // fonctions d'acces aux elements
  double         convergenceX  ()         const { return convergenceX_; }
  double         convergenceY  ()         const { return convergenceY_; }

  // calcul de la valeur de la fonction en x
  ValeurDerivee2 evalueFonction (double x) const { return (*f_) (x, arg_); }

  // extraction des zeros successifs
  void           reinitialise   ();
  double         zeroSuivant    ();

  // destructeur
  ~Resolution2Iterateur () {}

protected :

  // constructeur par défaut
  Resolution2Iterateur () {}

  // constructeur par copie
  Resolution2Iterateur (const Resolution2Iterateur & other)
  {
    convergenceX_ = other.convergenceX_;
    convergenceY_ = other.convergenceY_;
    tMin_         = other.tMin_;
    tMax_         = other.tMax_;
    pas_          = other.pas_;
    min_          = other.min_;
    max_          =  other.max_;
    precedente_   =  other.precedente_;
    f_            =  other.f_;
    arg_          =  other.arg_;
  }

  // operateur d'assignation
  Resolution2Iterateur & operator = (const Resolution2Iterateur & other)
  {
    if ( this != &other )
    {
      convergenceX_ = other.convergenceX_;
      convergenceY_ = other.convergenceY_;
      tMin_         = other.tMin_;
      tMax_         = other.tMax_;
      pas_          = other.pas_;
      min_          = other.min_;
      max_          =  other.max_;
      precedente_   =  other.precedente_;
      f_            =  other.f_;
      arg_          =  other.arg_;
    }
    return *this;
  }

private :

  double      convergenceX_;
  double      convergenceY_;

  double      tMin_;
  double      tMax_;
  double      pas_;

  Variation2  min_;
  Variation2  max_;
  Variation2  precedente_;

  TypeFoncVD2 f_;
  void*       arg_;

};

#endif
