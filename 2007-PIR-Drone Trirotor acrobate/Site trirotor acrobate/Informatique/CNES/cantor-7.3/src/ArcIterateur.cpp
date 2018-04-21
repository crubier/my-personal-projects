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
//>       ArcIterateur.cpp
//
//$Resume
//       fichier d'implantation de la classe ArcIterateur
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class ArcIterateur
//>         ArcIterateur()  
//>         operator =()    
//>         point()         
//
//$Historique
//       $Log: ArcIterateur.cpp,v $
//       Revision 1.5  2003/02/04 09:24:40  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.4  2000/08/09 14:36:41  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.3.4.1  2000/03/30 15:36:05  cantor
//       ajout du copyright CNES
//
//       Revision 1.3  1998/06/24 10:07:22  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.2  1998/04/26 15:23:41  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.1  1997/07/08 10:16:26  luc
//       Initial revision
//
//
//$Version
//       $Id: ArcIterateur.cpp,v 1.5 2003/02/04 09:24:40 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/ArcIterateur.h"


ArcIterateur::ArcIterateur (const Arc& a, double tolerance)
  : arc_ (&a)
{ // recherche de l'angle maximal respectant la tolérance demandée
  // (écart entre l'interpolation linéaire et l'arc de cercle)
  double theta_max = asin (sqrt (8 * tolerance / a.sinus ()));

  segments_ = int (ceil (a.balayage () / theta_max));
  if (segments_ < 2)
    segments_ = 2;
  pas_      = a.balayage () / segments_;

  // mise en place de l'itérateur
  reinitialise ();

}

ArcIterateur& ArcIterateur::operator = (const ArcIterateur& i)
{ if (this != &i)       // protection contre x = x
  { arc_      = i.arc_;
    pas_      = i.pas_;
    indice_   = i.indice_;
    segments_ = i.segments_;
  }

  return *this;

}

VecDBL ArcIterateur::point () const
{ if (indice_ == 0)
  { // l'itérateur a été juste initialisé, il n'a pas encore bougé
    return arc_->debut ();
  }
  else if (indice_ >= segments_)
  { // l'itérateur a atteint sa limite
    return arc_->fin ();
  }
  else
  { // récupération du point courant
    return arc_->intermediaire ((indice_ - 1) * pas_);
  }
}
