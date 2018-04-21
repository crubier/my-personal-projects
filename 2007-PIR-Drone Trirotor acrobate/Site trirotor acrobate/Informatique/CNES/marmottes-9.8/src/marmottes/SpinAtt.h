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
//>       SpinAtt.h
//
//$Resume
//       fichier d'en-tête de la classe SpinAtt
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SpinAtt
//
//$Historique
//       $Log: SpinAtt.h,v $
//       Revision 2.10  2002/12/11 17:21:22  marmottes
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui construit par le compilateur.
//
//       Revision 2.9  2002/12/02 17:07:55  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 2.8  2000/03/30 17:01:25  luc
//       ajout du copyright CNES
//
//       Revision 2.7  1999/11/02 07:19:23  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 2.6  1998/06/25 06:15:55  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.5  1998/04/26 18:25:42  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.4  1997/09/15 09:47:26  luc
//       déplacement de certains constructeurs dans le .cc
//
//       Revision 2.3  1997/08/20 09:55:42  luc
//       ajout d'un en-tête de fichier
//
//       Revision 2.2  1997/04/27 19:33:56  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/31 17:24:50  luc
//       abandon des tools.h++ (Rogue Wave)
//       
//       Revision 1.1  1995/01/27 17:01:01  mercator
//       Initial revision
//
//$Version
//       $Id: SpinAtt.h,v 2.10 2002/12/11 17:21:22 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SpinAtt_h
#define __marmottes_SpinAtt_h

#include "cantor/DeclDBL.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SpinAtt
//
//$Resume
//       conteneur pour une attitude et un axe de spin
//
//$Description
//       Cette classe concrète mémorise les solutions d'attitude avant leur tri.
//
//$Usage
//>     construction : 
//          sans argument, à partir d'une attitude et d'un spin, par copie
//>     utilisation  : 
//>       SpinAtt& operator =    () 
//          affectation
//>       const RotDBL& attitude () 
//          retourne l'attitude mémorisée
//>       const VecDBL& spin     () 
//          retourne le spin mémorisé
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SpinAtt
{

public :

  // constructeurs
  SpinAtt () {}

  SpinAtt (const RotDBL& attitude, const VecDBL& spin);

  SpinAtt (const SpinAtt& sa)
    :attitude_ (sa.attitude_), spin_ (sa.spin_)
  {}

  SpinAtt& operator = (const SpinAtt& sa);

  // accès aux éléments internes
  const RotDBL& attitude () const { return attitude_; }
  const VecDBL& spin     () const { return spin_;     }

  ~SpinAtt () {}

private :

  RotDBL attitude_;
  VecDBL spin_;

};


#endif
