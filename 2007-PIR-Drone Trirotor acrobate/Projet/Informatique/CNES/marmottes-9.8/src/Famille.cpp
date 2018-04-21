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
//>       Famille.cpp
//$Resume
//       fichier d'implantation de la classe Famille
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Famille        
//>         Famille()          
//>         operator =()       
//>         ~Famille()         
//>         inertielCanonique()
//$Historique
//       $Log: Famille.cpp,v $
//       Revision 1.4  2003/02/04 16:22:58  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.3  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 1.2  1999/10/15 11:50:13  luc
//       ajout d'un booléen dans le constructeur par pointeur
//       de façon à déterminer si l'instance peut prendre la
//       responsabilité de la désallocation mémoire ou si elle
//       doit se faire sa propre copie
//
//       Revision 1.1  1999/07/29 12:03:29  filaire
//       Creation de la classe
//       Sert d'interface a la classe FamilleAbstraite
//
//
//$Version
//       $Id: Famille.cpp,v 1.4 2003/02/04 16:22:58 marmottes Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/Famille.h"

Famille::Famille ()
  : ptrFamille_ (0) 
{}

Famille::Famille (const Famille& f)
  : ptrFamille_ (f.ptrFamille_->copie ()) 
{}

Famille::Famille (FamilleAbstraite *ptr, bool copieRequise)
  : ptrFamille_ (copieRequise ? ptr->copie () : ptr)
{}

Famille& Famille::operator = (const Famille& f)
{ 
  if (&f != this)   // protection contre x = x
  { 
    if (ptrFamille_)
      delete ptrFamille_;
    ptrFamille_ = f.ptrFamille_->copie ();
  }
 return *this;
}

Famille::~Famille ()
{ 
  if (ptrFamille_ != 0) 
    delete ptrFamille_;
}

RotVD1 Famille::inertielCanonique (const ValeurDerivee1& t) const
{
  return ptrFamille_->inertielCanonique (t);
}
