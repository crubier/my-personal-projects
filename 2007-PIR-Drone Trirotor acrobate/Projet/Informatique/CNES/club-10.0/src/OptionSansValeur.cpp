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
//>       OptionSansValeur.cpp
//
//$Resume
//       fichier d'implantation de la classe OptionSansValeur
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class OptionSansValeur
//>         operator =()        
//>         ajouterValeur()     
//
//$Historique
//       $Log: OptionSansValeur.cpp,v $
//       Revision 3.8  2003/02/03 13:45:23  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 3.7  2000/09/07 08:02:50  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.6  2000/07/03 08:57:20  club
//       Ajout du copyright CNES
//
//       Revision 3.5.2.1  2000/03/30 14:46:50  club
//       ajout du copyright CNES
//
//       Revision 3.5  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 3.4  1998/06/21 15:59:21  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//       élimination de la fonction estValide
//
//       Revision 3.3  1997/08/21 16:44:04  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.2  1997/03/25 15:04:33  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 15:19:05  luc
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:18:30  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.5  1995/07/12 15:02:13  mercator
//       ajout d'un pointeur this explicite pour aider le compilateur SUN a comprendre
//       
//       Revision 1.4  1995/06/26 06:38:07  mercator
//       remplacement d'un copie-constructeur par un operateur =
//       (on ne peut construire une instance de classe abstraite, meme pour initialiser
//       une instance de classe derivee concrete)
//       
//       Revision 1.3  1994/11/09 15:02:05  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/08/30 08:42:56  mercator
//       remplacement de l'appel a "lance" par un appel a "erreur"
//       
//       Revision 1.1  1994/07/27 12:05:54  luc
//       Initial revision
//
//$Version
//       $Id: OptionSansValeur.cpp,v 3.8 2003/02/03 13:45:23 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/OptionSansValeur.h"
#include "club/ClubErreurs.h"

OptionSansValeur& OptionSansValeur::operator = (const OptionSansValeur& opt)
{ if (this != &opt)      // protection contre x = x
    this->OptionBase::operator = (opt);

  return *this;

}

void OptionSansValeur::ajouterValeur (const char*) throw (ClubErreurs)
{ incrementeValeursTrouvees ();

  throw ClubErreurs(ClubErreurs::nombres_arguments_incompatibles,
                    code ().c_str (),
                    valeursTrouvees (), valeursAttendues ());

}
