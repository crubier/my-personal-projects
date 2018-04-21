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
//>       Variation2.cpp
//
//$Resume
//       fichier d'implantation de la classe Variation2
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Variation2
//>         operator =()  
//
//$Historique
//       $Log: Variation2.cpp,v $
//       Revision 1.12  2003/02/04 09:31:21  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 1.11  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.10.4.1  2000/03/30 15:36:07  cantor
//       ajout du copyright CNES
//
//       Revision 1.10  1998/07/29 11:42:57  cantor
//       élimination de float.h
//
//       Revision 1.9  1998/06/24 10:12:26  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.8  1998/04/26 15:24:16  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.7  1998/04/14 18:24:02  luc
//       suppression de la méthode estValide
//
//       Revision 1.6  1997/07/06 10:39:50  luc
//       ajout d'un en-tête de fichier
//
//       Revision 1.5  1997/03/26 06:54:38  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:32:47  luc
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/07/16 10:58:51  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       
//       Revision 1.2  1994/11/26 15:17:54  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:53:38  luc
//       Initial revision
//
//$Version
//       $Id: Variation2.cpp,v 1.12 2003/02/04 09:31:21 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Variation2.h"


Variation2& Variation2::operator = (const Variation2& v)
{ if (this != &v)         // protection contre x = x
  { sens_        = v.sens_;
    sensValide_  = v.sensValide_;
    x_           = v.x_;
    y_           = v.y_;
  }

  return *this;

}
