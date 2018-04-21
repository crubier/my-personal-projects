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
//>       ReunionEtParcelles.cpp
//
//$Resume
//       fichier d'implantation de la classe ReunionEtParcelles
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class ReunionEtParcelles
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
//       $Log: ReunionEtParcelles.cpp,v $
//       Revision 1.10  2003/02/04 16:35:23  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.9  2002/04/17 16:09:44  marmottes
//       Corrections de throw
//
//       Revision 1.8  2002/01/17 09:26:19  marmottes
//       correction de spécifications throw
//
//       Revision 1.7  2001/06/22 07:10:28  luc
//       utilisation du type bool pour les prédicats
//       utilisation d'un axe et d'un angle pour spécifier l'intégration le
//       long d'une rotation
//
//       Revision 1.6  2001/04/04 12:32:42  luc
//       ajout de la méthode ecartFrontiere
//
//       Revision 1.5  2000/11/13 10:01:10  luc
//       remplacement de la classe Champ par la classe Field
//
//       Revision 1.4  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 1.3  1998/06/24 20:01:28  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.2  1998/04/26 18:25:22  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.1  1997/08/20 08:38:23  luc
//       Initial revision
//
//$Version
//       $Id: ReunionEtParcelles.cpp,v 1.10 2003/02/04 16:35:23 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/ReunionEtParcelles.h"

void ReunionEtParcelles::rechercheChamp (Field ** adressePtr)
{ if (p1_)
    p1_->rechercheChamp (adressePtr);
  if (p2_)
    p2_->rechercheChamp (adressePtr);
}

Parcelle* ReunionEtParcelles::copie () const
{ return new ReunionEtParcelles (p1_->copie (), p2_->copie ()); }

bool ReunionEtParcelles::inclus (const VecDBL& u) const
{ return (p1_ && p1_->inclus (u)) || (p2_ && p2_->inclus (u)); }

double ReunionEtParcelles::ecartFrontiere (const VecDBL& u) const
{
  double d1 = p1_->ecartFrontiere (u);
  double d2 = p2_->ecartFrontiere (u);
  return (d1 > d2) ? d1 : d2;
}

bool ReunionEtParcelles::visible (const Cone& c) const
  throw (CantorErreurs)
{ return (p1_ && p1_->visible (c)) && (p2_ && p2_->visible (c)); }

Secteurs ReunionEtParcelles::visible (const Secteurs& s) const
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

void ReunionEtParcelles::appliqueRotation (const RotDBL& r)
{ if (p1_)
    p1_->appliqueRotation (r);
  if (p2_)
    p2_->appliqueRotation (r);
}

void ReunionEtParcelles::integreRotation (const VecDBL& axe, double angle)
  throw (CantorErreurs, MarmottesErreurs)
{ if (p1_)
    p1_->integreRotation (axe, angle);
  if (p2_)
    p2_->integreRotation (axe, angle);
}

void ReunionEtParcelles::appliqueMarge (double m)
  throw (CantorErreurs, MarmottesErreurs)
{ if (p1_)
    p1_->appliqueMarge (m);
  if (p2_)
    p2_->appliqueMarge (m);
}

void ReunionEtParcelles::applique (Field::TypeFuncConstField *f, void *d) const
{ p1_->applique (f, d);
  p2_->applique (f, d);
}

void ReunionEtParcelles::applique (Field::TypeFuncField *f, void *d)
{ p1_->applique (f, d);
  p2_->applique (f, d);
}
