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
//       Marmottes
//
//$Nom
//>       ParcelleElementaire.cpp
//
//$Resume
//       fichier d'implantation de la classe ParcelleElementaire
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class ParcelleElementaire
//>         rechercheChamp()       
//>         copie()                
//>         inclus()               
//>         ecartFrontiere()               
//>         visible()              
//>         visible()              
//>         appliqueRotation()     
//>         integreRotation()      
//>         appliqueMarge()        
//>         applique()             
//
//$Historique
//       $Log: ParcelleElementaire.cpp,v $
//       Revision 1.10  2003/02/04 16:32:13  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.9  2002/04/17 16:09:17  marmottes
//       Corrections de throw
//
//       Revision 1.8  2002/01/17 09:26:19  marmottes
//       correction de spécifications throw
//
//       Revision 1.7  2001/06/22 07:09:42  luc
//       utilisation du type bool pour les prédicats
//       utilisation d'un axe et d'un angle pour spécifier l'intégration le
//       long d'une rotation
//
//       Revision 1.6  2001/04/04 12:32:12  luc
//       ajout de la méthode ecartFrontiere
//
//       Revision 1.5  2000/11/13 10:01:26  luc
//       remplacement de la classe Champ par la classe Field
//
//       Revision 1.4  2000/03/30 17:01:19  luc
//       ajout du copyright CNES
//
//       Revision 1.3  1998/06/24 20:00:40  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.2  1998/04/26 18:25:16  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.1  1997/08/20 08:33:37  luc
//       Initial revision
//
//
//$Version
//       $Id: ParcelleElementaire.cpp,v 1.10 2003/02/04 16:32:13 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/ParcelleElementaire.h"

void ParcelleElementaire::rechercheChamp (Field ** adressePtr)
{ if (*adressePtr == 0)
  { // il n'y a pas de champ sauvegardé : on prend celui de l'instance
    *adressePtr = &f_;
  }
  else if (*adressePtr == &f_)
  { // on vient de retrouver le champ courant : le prochain sera le bon
    *adressePtr = 0;
  }
}

Parcelle* ParcelleElementaire::copie () const
{ return new ParcelleElementaire (f_); }

bool ParcelleElementaire::inclus (const VecDBL& u) const
{ return f_.isInside (u); }

double ParcelleElementaire::ecartFrontiere (const VecDBL& u) const
{ return f_.offsetFromBoundary (u); }

bool ParcelleElementaire::visible (const Cone& c) const
  throw (CantorErreurs)
{ return f_.selectInside (c).nonVide (); }

Secteurs ParcelleElementaire::visible (const Secteurs& s) const
  throw (CantorErreurs)
{ return f_.selectInside (s); }

void ParcelleElementaire::appliqueRotation (const RotDBL& r)
{ f_.rotate (r); }

void ParcelleElementaire::integreRotation (const VecDBL& axe, double angle)
  throw (CantorErreurs, MarmottesErreurs)
{ f_.spread (axe, angle); }

void ParcelleElementaire::appliqueMarge (double m)
  throw (CantorErreurs, MarmottesErreurs)
{ f_.applyMargin (m); }

void ParcelleElementaire::applique (Field::TypeFuncConstField *f,
                                    void *d) const
{ (*f) (f_, d); }

void ParcelleElementaire::applique (Field::TypeFuncField *f, void *d)
{ (*f) (f_, d); }
