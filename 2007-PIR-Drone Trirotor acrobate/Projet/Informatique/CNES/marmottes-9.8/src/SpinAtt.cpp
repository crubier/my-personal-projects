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
//>       SpinAtt.cpp
//
//$Resume
//       fichier d'implantation de la classe SpinAtt
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SpinAtt 
//>         SpinAtt()   
//>         operator =()
//
//$Historique
//       $Log: SpinAtt.cpp,v $
//       Revision 1.5  2003/02/04 16:42:14  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.4  2000/03/30 17:01:21  luc
//       ajout du copyright CNES
//
//       Revision 1.3  1998/06/24 20:06:40  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.2  1998/04/26 18:25:43  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.1  1997/09/15 09:43:51  luc
//       Initial revision
//
//$Version
//       $Id: SpinAtt.cpp,v 1.5 2003/02/04 16:42:14 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SpinAtt.h"

SpinAtt::SpinAtt (const RotDBL& attitude, const VecDBL& spin)
 : spin_ (spin)
{ // constructeur

  // on s'arrange pour que la partie scalaire du quaternion soit positive
  if (attitude.q0 () >= 0.0)
    attitude_  = attitude;
  else
    attitude_  = RotDBL (-(attitude.q0 ()),
                         -(attitude.q1 ()),
                         -(attitude.q2 ()),
                         -(attitude.q3 ()));

}

SpinAtt& SpinAtt::operator = (const SpinAtt& sa)
{ // affectation
  if (this != &sa)     // protection contre x = x
  { attitude_ = sa.attitude_;
    spin_     = sa.spin_;
  }

  return *this;

}
