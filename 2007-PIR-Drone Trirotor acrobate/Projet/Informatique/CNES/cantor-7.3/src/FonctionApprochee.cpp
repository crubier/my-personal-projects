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
//>       FonctionApprochee.cpp
//
//$Resume
//       fichier d'implantation de la classe FonctionApprochee
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class FonctionApprochee 
//>         alloueTableau()       
//>         libereTableau()       
//>         operator =()          
//>         ajoutePointReference()
//>         otePointReference()   
//>         operator()()          
//
//$Historique
//       $Log: FonctionApprochee.cpp,v $
//       Revision 2.10  2003/02/04 09:27:44  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 2.9  2001/06/05 15:46:35  cantor
//       utilisation du mécanisme des exceptions pour la gestion des erreurs
//
//       Revision 2.8  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 2.7.4.1  2000/03/30 15:36:05  cantor
//       ajout du copyright CNES
//
//       Revision 2.7  1998/06/24 10:09:06  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.6  1998/04/26 15:23:54  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.5  1998/04/19 18:25:44  luc
//       récupération du code d'erreur de la routine utilisateur
//
//       Revision 2.4  1997/07/06 10:38:37  luc
//       ajout d'un en-tête de fichier
//
//       Revision 2.3  1997/04/03 19:31:01  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 2.2  1997/03/26 06:54:29  luc
//       changement des conventions de nommage
//       
//       Revision 2.1  1997/03/24 09:29:13  luc
//       séparation de la classe en deux : FonctionApprochee et MoindreCarreLineaire
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/10/07 15:14:11  luc
//       correction d'une erreur dans le cas de la copie d'une fonction
//       deja ajustee (constructeur par copie et affectation)
//       
//       Revision 1.2  1996/08/05 17:53:06  luc
//       détection de la non-inversibilité d'une matrice
//       quand seul le dernier pivot est inférieur au seuil
//       
//       Revision 1.1  1996/07/16 10:28:48  luc
//       Initial revision
//
//$Version
//       $Id: FonctionApprochee.cpp,v 2.10 2003/02/04 09:27:44 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/FonctionApprochee.h"


void FonctionApprochee::alloueTableau (int dimension)
{ // mise à jour du tableau de travail d'une instance

  YXk_  = (dimension <= 0) ? 0 : (new double [dimension]);
  oteTousPointsReferences ();

}

void FonctionApprochee::libereTableau ()
{ if (YXk_)
    delete [] YXk_;
  YXk_            = 0;
}

FonctionApprochee& FonctionApprochee::operator = (const FonctionApprochee& f)
{ if (this != &f)     // protection contre x = x
  { if (moindresCarres_.dimension () < f.moindresCarres_.dimension ())
    { // il est possible que le tableau soit trop petit
      libereTableau ();
      alloueTableau (f.moindresCarres_.dimension ());
    }

    moindresCarres_ = f.moindresCarres_;
    fonctionsBase_  = f.fonctionsBase_;
    argsBase_       = f.argsBase_;

  }

  return *this;

}

void FonctionApprochee::ajoutePointReference (void *xk, double yk, double wk)
  throw (CantorErreurs)
{ // ajout d'un point dans l'échantillon de référence utilisé pour l'ajustement
  if (!fonctionsBase_)
    throw CantorErreurs (CantorErreurs::aucune_fonction_base);

  // évaluation des fonctions de base en xk
  int code = fonctionsBase_ (xk, argsBase_, YXk_);
  if (code)
    throw CantorErreurs (CantorErreurs::erreur_fonction_base, code);

  moindresCarres_.ajouteResidu (yk, YXk_, wk);

}

void FonctionApprochee::otePointReference (void *xk, double yk, double wk)
  throw (CantorErreurs)
{ // élimination d'un point dans l'échantillon de référence
  if (!fonctionsBase_)
    throw CantorErreurs (CantorErreurs::aucune_fonction_base);

  // évaluation des fonctions de base en xk
  int code = fonctionsBase_ (xk, argsBase_, YXk_);
  if (code)
    throw CantorErreurs (CantorErreurs::erreur_fonction_base, code);

  moindresCarres_.oteResidu (yk, YXk_, wk);

}

void FonctionApprochee::operator () (void *xk, double *ptrY) const
  throw (CantorErreurs)
{ // application de la fonction ajustée en xk

  // évaluation des fonctions de base en x
  int code = fonctionsBase_ (xk, argsBase_, YXk_);
  if (code)
    throw CantorErreurs (CantorErreurs::erreur_fonction_base, code);

  moindresCarres_ (ptrY, YXk_);

}
