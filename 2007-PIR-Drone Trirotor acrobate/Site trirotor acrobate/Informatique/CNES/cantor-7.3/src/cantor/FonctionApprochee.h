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
//>       FonctionApprochee.h
//
//$Resume
//       fichier d'en-tête de la classe FonctionApprochee
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class FonctionApprochee
//
//$Historique
//       $Log: FonctionApprochee.h,v $
//       Revision 2.10  2002/12/02 13:33:56  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 2.9  2001/06/05 15:20:44  cantor
//       passage au mécanisme des exceptions pour la gestion des erreurs
//       (ceci induit des modifications de signatures)
//
//       Revision 2.8  2000/08/09 14:36:44  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 2.7.4.1  2000/03/30 15:36:09  cantor
//       ajout du copyright CNES
//
//       Revision 2.7  1998/07/29 14:19:16  cantor
//       correction d'un oubli d'initialisation d'attribut
//       dans le constructeur par défaut
//
//       Revision 2.6  1998/06/24 16:45:41  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.5  1998/04/26 15:23:54  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.4  1998/01/22 10:39:43  luc
//       amélioration de l'en-tête de classe
//
//       Revision 2.3  1997/07/06 10:26:29  luc
//       ajout d'un en-tête de fichier
//
//       Revision 2.2  1997/03/26 06:39:43  luc
//       changement des conventions de nommage
//       
//       Revision 2.1  1997/03/24 09:31:12  luc
//       séparation de la classe en deux : FonctionApprochee et MoindreCarreLineaire
//       passage de SCCS à RCS
//       
//       Revision 1.1  1996/07/16 10:28:37  luc
//       Initial revision
//
//$Version
//       $Id: FonctionApprochee.h,v 2.10 2002/12/02 13:33:56 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_FonctionApprochee_h
#define __cantor_FonctionApprochee_h

#include "cantor/CantorErreurs.h"
#include "cantor/MoindreCarreLineaire.h"

typedef int (*TypeFonctionsBase) (void *x, void *argsBase, double *ptrY);

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FonctionApprochee
//
//$Resume
//       Approximation d'une fonction par combinaison linéaire
//
//$Description
//       Approximation d'une fonction par combinaison linéaire de
//       fonctions de base, les coefficients étant ajustés au sens des
//       moindres carrés. La fonction est à valeur réelle (type
//       double), mais à paramètres quelconques (type anonyme void *).
//
//$Usage
//>     construction : 
//          sans argument, à partir de la dimension et d'une fonction
//          implantant la base de l'espace vectoriel, par copie
//>     utilisation  : 
//>       FonctionApprochee& operator =   () 
//          affectation
//>       void ajoutePointReference       () 
//          ajoute un point pondéré dans l'échantillon de référence
//>       void otePointReference          () 
//          ote un point pondéré de l'échantillon de référence
//>       void operator()                 () 
//          calcule la valeur (approchée) de la fonction en x.
//>       void oteTousPointsReferences    () 
//          vide l'échantillon de référence
//>       int nbPointsReferences          () 
//          retourne le nombre de points de référence
//>       void ajuste                     () 
//          réalise l'ajustement des coefficients au sens des moindres
//          carrés
//>       bool estAjustee                 () 
//          indique si la fonction a été ajustée
//>       void coefficients               () 
//          copie les coefficients de la fonction dans le tableau
//          fourni en argument
//>       double erreurQuadratique        () 
//          retourne l'erreur quadratique de l'ajustement
//>       int dimension                   () 
//          retourne la dimension de l'espace vectoriel d'ajustement
//>       TypeFonctionsBase fonctionsBase () 
//          retourne un pointeur sur la fonction implantant la base de
//          l'espace vectoriel
//>       void *argsBase                  () 
//          retourne le pointeur anonyme des arguments de
//          fonctionsBase ()
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class FonctionApprochee
{ 
  public :

  // constructeurs
  FonctionApprochee ()
    : moindresCarres_ (), fonctionsBase_ (0), argsBase_ (0), YXk_ (0)
  {}

  FonctionApprochee (int dimension,
                     TypeFonctionsBase fonctionsBase, void *argsBase = 0)
    : moindresCarres_ (dimension),
      fonctionsBase_ (fonctionsBase), argsBase_ (argsBase)
  { alloueTableau (dimension); }

  // copie constructeur et affectation
  FonctionApprochee (const FonctionApprochee& f)
    : moindresCarres_ (f.moindresCarres_),
      fonctionsBase_ (f.fonctionsBase_), argsBase_ (f.argsBase_)
  { alloueTableau (f.moindresCarres_.dimension ()); }

  FonctionApprochee& operator = (const FonctionApprochee& f);

  // destructeur
  ~FonctionApprochee () { libereTableau (); }

  // enregistrement de l'échantillon de points de références
  void ajoutePointReference (void *xk, double yk, double wk = 1.0)
    throw (CantorErreurs);

  void otePointReference (void *xk, double yk, double wk = 1.0)
    throw (CantorErreurs);

  void oteTousPointsReferences ()
  { moindresCarres_.oteTousResidus (); }

  int  nbPointsReferences () const
  { return moindresCarres_.nbResidus (); }

  // ajustement par combinaison linéaire des fonctions de base
  void ajuste  (double seuil = 1.0e-10)
    throw (CantorErreurs)
  { moindresCarres_.ajuste (seuil); }

  bool estAjustee () const
  { return moindresCarres_.estAjuste (); }

  void coefficients (double coeffs []) const
    throw (CantorErreurs)
  { moindresCarres_.coefficients (coeffs); }

  double erreurQuadratique () const
    throw (CantorErreurs)
  { return moindresCarres_.erreurQuadratique (); }

  void operator () (void *xk, double *ptrY) const
    throw (CantorErreurs);

  // accès aux éléments internes
  int               dimension     () const
  { return moindresCarres_.dimension (); }

  TypeFonctionsBase fonctionsBase () const { return fonctionsBase_; }

  void             *argsBase      () const { return argsBase_; }

private :

  MoindreCarreLineaire moindresCarres_; // modèle sous-jacent

  TypeFonctionsBase fonctionsBase_;     // base de l'espace vectoriel
  void             *argsBase_;          // fonctionnel d'approximation

  double           *YXk_;               // table de travail : Y (Xk)

  void alloueTableau (int dimension);
  void libereTableau ();

};

#endif
