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
//       Club
//
//$Nom
//>       OptionReel.cpp
//
//$Resume
//       fichier d'implantation de la classe OptionReel
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class OptionReel
//>         operator =()  
//
//$Historique
//       $Log: OptionReel.cpp,v $
//       Revision 3.7  2003/02/03 13:44:54  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 3.6  2000/07/03 08:57:20  club
//       Ajout du copyright CNES
//
//       Revision 3.5.2.1  2000/03/30 14:46:49  club
//       ajout du copyright CNES
//
//       Revision 3.5  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 3.4  1998/06/21 15:59:04  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//       élimination de la fonction estValide
//
//       Revision 3.3  1997/08/21 16:44:04  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.2  1997/03/25 15:04:38  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 15:18:45  luc
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:18:05  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.3  1994/11/09 15:02:00  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/08/10 15:48:13  mercator
//       correction d'une erreur de surcharge de constructeur
//       
//       Revision 1.1  1994/07/27 12:05:53  luc
//       Initial revision
//
//$Version
//       $Id: OptionReel.cpp,v 3.7 2003/02/03 13:44:54 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/OptionReel.h"

OptionReel& OptionReel::operator = (const OptionReel& opt)
{ if (this != &opt)      // protection contre x = x
    OptionTableauReels::operator = ((const OptionTableauReels) opt);

  return *this;

}
