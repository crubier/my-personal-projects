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
//>       MoindreCarreLineaire.h
//
//$Resume
//       fichier d'en-tête de la classe MoindreCarreLineaire
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class MoindreCarreLineaire
//>       void factLDLt()            
//>       void resoudLDLt()         
//
//$Historique
//       $Log: MoindreCarreLineaire.h,v $
//       Revision 1.10  2002/12/02 13:39:09  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.9  2001/06/05 15:19:24  cantor
//       passage au mécanisme des exceptions pour la gestion des erreurs
//       (ceci induit des modifications de signatures)
//
//       Revision 1.8  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.7.4.1  2000/03/30 15:36:10  cantor
//       ajout du copyright CNES
//
//       Revision 1.7  1998/06/24 16:45:00  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.6  1998/04/26 15:23:58  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.5  1998/01/22 10:40:21  luc
//       amélioration de l'en-tête de classe
//
//       Revision 1.4  1997/09/10 06:56:23  luc
//       correction des caractères RCS
//
//       Revision 1.3  1997/07/06 10:30:22  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.2  1997/03/26 06:39:45  luc
//       changement des conventions de nommage
//       
//       Revision 1.1  1997/03/24 08:37:10  luc
//       Initial revision
//
//$Version
//       $Id: MoindreCarreLineaire.h,v 1.10 2002/12/02 13:39:09 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_MoindreCarreLineaire_h
#define __cantor_MoindreCarreLineaire_h

#include "cantor/CantorErreurs.h"

// fonctions de résolution en place d'un système linéaire symétrique
void factLDLt   (double *m, int n, double seuil) throw (CantorErreurs);
void resoudLDLt (const double *m, int n, double x []);

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class MoindreCarreLineaire
//$Resume
//       Résolution d'un problème de moindres carrés linéaire
//
//$Description
//       Résolution au sens des moindres carrés pondérés d'un modèle
//       linéaire de dimension n : rk = a1 rk,1 + ... + an rk,n des
//       résidus de mesures d'un système rk = mk - mthk connaissant
//       les mesures rélles mk et théoriques mthk et les coefficients
//       de linéarité rk,i. Cette classe peut être utilisée pour
//       résoudre une itération d'un problème général d'ajustement au
//       sens des moindre carrés (les fki sont alors les dérivées
//       partielles des mesures autour de la valeur courante du
//       vecteur d'état).
//
//$Usage
//>     construction : 
//          sans argument, à partir de la dimension, par copie
//>     utilisation  : 
//>       MoindreCarreLineaire& operator = () 
//          affectation
//>       void ajouteResidu                () 
//          ajoute un résidu pondéré dans l'échantillon de référence
//>       void oteResidu                   () 
//          ote un résidu pondéré dans l'échantillon de référence
//>       void oteTousResidus              () 
//          vide l'échantillon de référence
//>       void ajuste                      () 
//          réalise l'ajustement des coefficients au sens des moindres
//          carrés
//>       void coefficients                () 
//          copie les coefficients du modèle dans le tableau fourni en
//          argument
//>       double erreurQuadratique         () 
//          retourne l'erreur quadratique (somme des rk au carré)
//>       void operator()                  () 
//          calcule le résidu linéaire obtenu après ajustement
//>       int nbResidus                    () 
//          retourne le nombre de résidus de l'échantillon
//>       bool estAjuste                   () 
//          indique si le modèle a été ajusté
//>       int dimension                    () 
//          retourne la dimension de l'espace vectoriel d'ajustement
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class MoindreCarreLineaire
{

public :

  // constructeurs
  MoindreCarreLineaire ()
    : dimension_ (0), nbResidus_ (0), sommeRk2_ (0.0), vecSommeRkFk_ (0),
      matSommeFkFk_ (0), estAjuste_ (false), ai_ (0), errQuad_ (0.0)
  {}

  MoindreCarreLineaire (int dimension)
    : nbResidus_ (0), estAjuste_ (false), errQuad_ (0.0)
  { alloueTableaux (dimension); }

  // copie constructeur et affectation
  MoindreCarreLineaire (const MoindreCarreLineaire& m);
  MoindreCarreLineaire& operator = (const MoindreCarreLineaire& m);

  // destructeur
  ~MoindreCarreLineaire () { libereTableaux (); }

  // enregistrement de l'échantillon de points de références
  void ajouteResidu     (double rk, double fki [], double wk = 1.0);
  void oteResidu        (double rk, double fki [], double wk = 1.0);
  void oteTousResidus   ();
  int  nbResidus        () const { return nbResidus_; }

  // ajustement par combinaison linéaire des fonctions de base
  void ajuste (double seuil = 1.0e-10)
    throw (CantorErreurs);

  bool estAjuste () const { return estAjuste_; }

  void coefficients (double ai []) const
    throw (CantorErreurs);

  double erreurQuadratique () const
    throw (CantorErreurs);

  void operator () (double *ptrFk, double fki []) const
    throw (CantorErreurs);

  // accès aux éléments internes
  int dimension         () const { return dimension_; }

private :

  int               dimension_;      // dimension du modèle linéaire

  // attributs de gestion de l'échantillon de points du moindres carrés
  int               nbResidus_;      // taille de l'échantillon
  double            sommeRk2_;       // scalaire pour le calcul de l'erreur
  double           *vecSommeRkFk_;   // second membre des moindres carrés
  double           *matSommeFkFk_;   // matrice des moindres carrés

  // attributs de gestion de l'ajustement
  bool              estAjuste_;
  double           *ai_;
  double            errQuad_;

  void alloueTableaux (int dimension);
  void libereTableaux ();

};

#endif
