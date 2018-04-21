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
//>       Intervalle.cpp
//
//$Resume
//       fichier d'implantation de la classe Intervalle
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Intervalle
//>         operator =()  
//
//$Historique
//       $Log: Intervalle.cpp,v $
//       Revision 1.12  2003/02/04 09:28:36  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.11  2000/08/09 14:36:42  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.10.4.1  2000/03/30 15:36:06  cantor
//       ajout du copyright CNES
//
//       Revision 1.10  1998/07/29 11:34:07  cantor
//       élimination de float.h
//
//       Revision 1.9  1998/07/29 11:27:09  cantor
//       protection de l'inclusion de float.h
//
//       Revision 1.8  1998/06/24 10:10:02  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.7  1998/04/26 15:23:57  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.6  1997/07/06 10:38:53  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:54:31  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:32:42  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 11:56:24  luc
//       suppression de l'opérateur == (il n'avait pas de raison d'être intrinsèque,
//       il n'était présent jusqu'ici qu'à cause des tools.h++)
//       
//       Revision 1.2  1994/11/26 15:16:52  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:53:19  luc
//       Initial revision
//
//$Version
//       $Id: Intervalle.cpp,v 1.12 2003/02/04 09:28:36 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Intervalle.h"


Intervalle& Intervalle::operator = (const Intervalle& i)
{ if (this != &i)      // protection contre x = x
  { inf_ = i.inf_;
    sup_ = i.sup_;
  }

  return *this;

}
