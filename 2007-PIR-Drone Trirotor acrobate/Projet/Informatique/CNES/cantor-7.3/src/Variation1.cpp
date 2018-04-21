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
//>       Variation1.cpp
//
//$Resume
//       fichier d'implantation de la classe Variation1
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Variation1
//>         operator =()  
//
//$Historique
//       $Log: Variation1.cpp,v $
//       Revision 1.12  2003/02/04 09:31:05  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.11  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.10.4.1  2000/03/30 15:36:07  cantor
//       ajout du copyright CNES
//
//       Revision 1.10  1998/07/29 11:42:38  cantor
//       élimination de float.h
//
//       Revision 1.9  1998/06/24 10:12:18  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.8  1998/04/26 15:24:14  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.7  1998/04/14 18:24:19  luc
//       suppression de la méthode estValide
//
//       Revision 1.6  1997/07/06 10:39:41  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:54:37  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:32:46  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 10:56:51  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       
//       Revision 1.2  1994/11/26 15:17:49  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:53:37  luc
//       Initial revision
//
//$Version
//       $Id: Variation1.cpp,v 1.12 2003/02/04 09:31:05 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Variation1.h"


Variation1& Variation1::operator = (const Variation1& v)
{ if (this != &v)         // protection contre x = x
  { sens_        = v.sens_;
    sensValide_  = v.sensValide_;
    x_           = v.x_;
    y_           = v.y_;
  }

  return *this;

}
