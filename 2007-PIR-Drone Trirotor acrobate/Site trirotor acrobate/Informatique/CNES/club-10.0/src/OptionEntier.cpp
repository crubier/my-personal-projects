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
//>       OptionEntier.cpp
//
//$Resume
//       fichier d'implantation de la classe OptionEntier
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class OptionEntier
//>         operator =()    
//
//$Historique
//       $Log: OptionEntier.cpp,v $
//       Revision 3.7  2003/02/03 13:44:25  club
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
//       Revision 3.4  1998/06/21 15:58:49  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//       élimination de la fonction estValide
//
//       Revision 3.3  1997/08/21 16:44:03  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.2  1997/03/25 15:04:43  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 15:18:35  luc
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:17:41  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.3  1994/11/09 15:01:56  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/08/10 15:48:11  mercator
//       correction d'une erreur de surcharge de constructeur
//       
//       Revision 1.1  1994/07/27 12:05:52  luc
//       Initial revision
//
//$Version
//       $Id: OptionEntier.cpp,v 3.7 2003/02/03 13:44:25 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/OptionEntier.h"

OptionEntier& OptionEntier::operator = (const OptionEntier& opt)
{ if (this != &opt)      // protection contre x = x
    OptionTableauEntiers::operator = ((const OptionTableauEntiers) opt);

  return *this;

}
