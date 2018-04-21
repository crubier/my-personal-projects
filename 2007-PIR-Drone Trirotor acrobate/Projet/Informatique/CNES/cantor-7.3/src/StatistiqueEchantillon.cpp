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
//>       StatistiqueEchantillon.cpp
//
//$Resume
//       fichier d'implantation de la classe StatistiqueEchantillon
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class StatistiqueEchantillon
//>         StatistiqueEchantillon()  
//>         operator =()              
//>         operator +=()             
//>         ecartType()               
//
//$Historique
//       $Log: StatistiqueEchantillon.cpp,v $
//       Revision 1.5  2003/02/04 09:30:29  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.4  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.3.4.1  2000/03/30 15:36:07  cantor
//       ajout du copyright CNES
//
//       Revision 1.3  1998/06/24 10:11:39  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.2  1998/06/22 08:27:05  luc
//       ajout d'un #include oublié
//
//       Revision 1.1  1998/05/12 12:56:59  luc
//       Initial revision
//
//$Version
//       $Id: StatistiqueEchantillon.cpp,v 1.5 2003/02/04 09:30:29 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/StatistiqueEchantillon.h"
#include "cantor/MathPi.h"


StatistiqueEchantillon::StatistiqueEchantillon ()
  : s1_ (0), min_ (0.0), max_ (0.0), sX_ (0.0), sX2_ (0.0)
{}


StatistiqueEchantillon::StatistiqueEchantillon
                        (const StatistiqueEchantillon& s)
  : s1_ (s.s1_), min_ (s.min_), max_ (s.max_), sX_ (s.sX_), sX2_ (s.sX2_)
{}


StatistiqueEchantillon& StatistiqueEchantillon::operator =
                        (const StatistiqueEchantillon& s)
{ if (&s != this)       // protection contre x = x
  { s1_  = s.s1_;
    min_ = s.min_;
    max_ = s.max_;
    sX_  = s.sX_;
    sX2_ = s.sX2_;
  }

  return *this; 

}


const StatistiqueEchantillon& StatistiqueEchantillon::operator += (double x)
{ // ajout d'un point dans un échantillon
  if (s1_ == 0)
  { // aucun point n'était mémorisé
    min_ = x;
    max_ = x;
  }
  else
  { // il y avait déjà des extremums mémorisés
    if (x < min_)
      min_ = x;
    if (x > max_)
      max_ = x;
  }

  s1_++;
  sX_  += x;
  sX2_ += x * x;

  return *this;

}


const StatistiqueEchantillon& StatistiqueEchantillon::operator +=
                              (const StatistiqueEchantillon& s)
{ // combinaison de deux échantillons
  if (s.s1_ == 0)
    return *this;

  if (s1_ == 0)
  { // aucun point n'était mémorisé
    min_ = s.min_;
    max_ = s.max_;
  }
  else
  { // il y avait déjà des extremums mémorisés
    if (s.min_ < min_)
      min_ = s.min_;
    if (s.max_ > max_)
      max_ = s.max_;
  }

  s1_  += s.s1_;
  sX_  += s.sX_;
  sX2_ += s.sX2_;

  return *this;

}


double StatistiqueEchantillon::ecartType () const
{ // retourne l'écart type de la loi suivie par les points de l'échantillon

  // pour passer de la variance d'échantillon à la variance de loi, on
  // a corrigé le biais de l'estimateur classique en racine de (n-1)/n
  // c'est la raison pour laquelle on divise par s1_ * (s1_ - 1.0) et
  // non par s1_ * s1_
  if (s1_ > 0)
    return sqrt ((s1_ * sX2_ - sX_ * sX_) / (s1_ * (s1_ - 1.0)));
  else
    return 0.0;

}
