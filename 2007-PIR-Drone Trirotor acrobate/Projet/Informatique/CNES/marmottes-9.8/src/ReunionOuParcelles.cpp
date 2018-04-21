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
//>       ReunionOuParcelles.cpp
//
//$Resume
//       fichier d'implantation de la classe ReunionOuParcelles
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class ReunionOuParcelles
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
//       $Log: ReunionOuParcelles.cpp,v $
//       Revision 1.10  2003/02/04 16:36:47  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.9  2002/04/17 16:10:01  marmottes
//       Corrections de throw
//
//       Revision 1.8  2002/01/17 09:26:19  marmottes
//       correction de spécifications throw
//
//       Revision 1.7  2001/06/22 07:10:40  luc
//       utilisation du type bool pour les prédicats
//       utilisation d'un axe et d'un angle pour spécifier l'intégration le
//       long d'une rotation
//
//       Revision 1.6  2001/04/04 12:32:51  luc
//       ajout de la méthode ecartFrontiere
//
//       Revision 1.5  2000/11/13 10:00:38  luc
//       remplacement de la classe Champ par la classe Field
//
//       Revision 1.4  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 1.3  1998/06/24 20:01:50  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.2  1998/04/26 18:25:23  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.1  1997/08/20 08:38:33  luc
//       Initial revision
//
//$Version
//       $Id: ReunionOuParcelles.cpp,v 1.10 2003/02/04 16:36:47 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/ReunionOuParcelles.h"

void ReunionOuParcelles::rechercheChamp (Field ** adressePtr)
{ if (p1_)
    p1_->rechercheChamp (adressePtr);
  if (p2_)
    p2_->rechercheChamp (adressePtr);
}

Parcelle* ReunionOuParcelles::copie () const
{ return new ReunionOuParcelles (p1_->copie (), p2_->copie ()); }

bool ReunionOuParcelles::inclus (const VecDBL& u) const
{ return (p1_ && p1_->inclus (u)) || (p2_ && p2_->inclus (u)); }

double ReunionOuParcelles::ecartFrontiere (const VecDBL& u) const
{
  double d1 = p1_->ecartFrontiere (u);
  double d2 = p2_->ecartFrontiere (u);
  return (d1 > d2) ? d1 : d2;
}

bool ReunionOuParcelles::visible (const Cone& c) const
  throw (CantorErreurs)
{ return (p1_ && p1_->visible (c)) || (p2_ && p2_->visible (c)); }

Secteurs ReunionOuParcelles::visible (const Secteurs& s) const
  throw (CantorErreurs)
{ if (p1_)
  { if (p2_)
    { Secteurs s1 = p1_->visible (s);
      Secteurs s2 = p2_->visible (s);

      // réunion des portions visibles
      Creneau c12  = s1.creneau ();
              c12 += s2.creneau ();
      return Secteurs (s1.cone (), s1.reference (), c12);

    }
    else
      return p1_->visible (s);
  }
  else if (p2_)
    return p2_->visible (s);
  else
  { // la parcelle est vide : on ne peut rien voir
    Secteurs vide (s);
    vide.intersection (Cone (s.cone ().axe (), 0.0));
    return vide;
  }
}

void ReunionOuParcelles::appliqueRotation (const RotDBL& r)
{ if (p1_)
    p1_->appliqueRotation (r);
  if (p2_)
    p2_->appliqueRotation (r);
}

void ReunionOuParcelles::integreRotation (const VecDBL& axe, double angle)
  throw (CantorErreurs, MarmottesErreurs)
{ if (p1_)
    p1_->integreRotation (axe, angle);
  if (p2_)
    p2_->integreRotation (axe, angle);
}

void ReunionOuParcelles::appliqueMarge (double m)
  throw (CantorErreurs, MarmottesErreurs)
{ if (p1_)
    p1_->appliqueMarge (m);
  if (p2_)
    p2_->appliqueMarge (m);
}

void ReunionOuParcelles::applique (Field::TypeFuncConstField *f, void *d) const
{ p1_->applique (f, d);
  p2_->applique (f, d);
}

void ReunionOuParcelles::applique (Field::TypeFuncField *f, void *d)
{ p1_->applique (f, d);
  p2_->applique (f, d);
}
