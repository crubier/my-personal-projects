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
//>       StatistiqueEchantillon.h
//
//$Resume
//       fichier d'en-tête de la classe StatistiqueEchantillon
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class StatistiqueEchantillon
//
//$Historique
//       $Log: StatistiqueEchantillon.h,v $
//       Revision 1.5  2002/12/10 15:36:31  cantor
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui créé par le compilateur
//
//       Revision 1.4  2002/12/02 13:48:49  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.3  2000/08/09 14:36:45  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.2.4.1  2000/03/30 15:36:11  cantor
//       ajout du copyright CNES
//
//       Revision 1.2  1998/06/24 15:28:53  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.1  1998/05/12 12:58:37  luc
//       Initial revision
//
//$Version
//       $Id: StatistiqueEchantillon.h,v 1.5 2002/12/10 15:36:31 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __StatistiqueEchantillon_h
#define __StatistiqueEchantillon_h

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class StatistiqueEchantillon
//
//$Resume
//       classe gérant un échantillon statistique
//
//$Description
//       Cette classe concrète permet de constituer un échantillon
//       statistique et d'en extraire les caractéristiques
//
//$Usage
//>     construction : 
//          sans argument, par copie
//>     utilisation  : 
//>       StatistiqueEchantillon& operator =        () 
//          affectation
//>       const StatistiqueEchantillon& operator += () 
//          ajoute un point a l'échantillon.
//>       double ecartType                          () 
//          retourne l'écart type de la loi suivie par l'échantillon
//>       int nbPoints                              () 
//          retourne le nombre de points de l'échantillon
//>       double min                                () 
//          retourne la valeur minimale rencontrée sur l'échantillon
//>       double max                                () 
//          retourne la valeur maximale rencontrée sur l'échantillon
//>       double moyenne                            () 
//          retourne la valeur moyenne de l'échantillon
//
//$Version
//       $Id: StatistiqueEchantillon.h,v 1.5 2002/12/10 15:36:31 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////
class StatistiqueEchantillon
{ 

public :

  // constructeurs
  StatistiqueEchantillon ();
  StatistiqueEchantillon (const StatistiqueEchantillon& s);
  StatistiqueEchantillon& operator = (const StatistiqueEchantillon& s);

  // destructeur
  ~StatistiqueEchantillon () {}

  // enrichissement de l'échantillon
  const StatistiqueEchantillon& operator += (double x);
  const StatistiqueEchantillon& operator += (const StatistiqueEchantillon& s);

  // statistiques
  int    nbPoints  () const { return s1_;  }
  double min       () const { return min_; }
  double max       () const { return max_; }

  double moyenne   () const
  { return (s1_ > 0) ? (sX_ / s1_) : 0.0;  }

  double ecartType () const;

private :

  int                  s1_;
  double               min_;
  double               max_;
  double               sX_;
  double               sX2_;

};

#endif
