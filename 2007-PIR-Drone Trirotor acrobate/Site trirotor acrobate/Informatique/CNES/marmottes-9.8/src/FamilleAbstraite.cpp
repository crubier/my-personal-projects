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
//>       FamilleAbstraite.cpp
//$Resume
//       fichier d'implantation de la classe FamilleAbstraite
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class FamilleAbstraite
//>         FamilleAbstraite()  
//>         operator =()        
//>         transforme()        
//$Historique
//       $Log: FamilleAbstraite.cpp,v $
//       Revision 1.3  2003/02/04 16:23:37  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.2  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 1.1  1999/07/29 12:06:07  filaire
//       Creation de la classe
//       Classe de base pour les familles de solutions mathematiques
//  
//
//$Version
//       $Id: FamilleAbstraite.cpp,v 1.3 2003/02/04 16:23:37 marmottes Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/FamilleAbstraite.h"

FamilleAbstraite::FamilleAbstraite ()
  : plages_ (-M_PI,M_PI) 
{}

FamilleAbstraite::FamilleAbstraite (const Intervalle& plages)
  : plages_ (plages) 
{}

FamilleAbstraite::FamilleAbstraite (const FamilleAbstraite& f)
  : plages_ (f.plages_) 
{}

FamilleAbstraite& FamilleAbstraite::operator = (const FamilleAbstraite& f)
{ 
  if (&f != this)   // protection contre x = x
  { 
    plages_   = f.plages_;
  }
  return *this;
}

ValeurDerivee1 FamilleAbstraite::transforme (const ValeurDerivee1& t) const
{ 
  // parametre intermediaire
  Intervalle i (plages_);

  // calcul du parametre theta lié au cône qui correspond au paramètre libre t
  return ValeurDerivee1 (t * (i.sup () - i.inf ()) + i.inf ());
}

