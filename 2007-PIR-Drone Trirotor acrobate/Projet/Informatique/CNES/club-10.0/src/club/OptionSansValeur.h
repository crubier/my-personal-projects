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
//>       OptionSansValeur.h
//
//$Resume
//       fichier d'en-tête de la classe OptionSansValeur
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class OptionSansValeur
//
//$Historique
//       $Log: OptionSansValeur.h,v $
//       Revision 3.10  2003/07/17 12:38:28  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 3.9  2002/12/09 15:56:55  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 3.8  2000/09/07 07:41:45  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.7  2000/07/03 08:48:31  club
//       Ajout du copyright CNES.
//
//       Revision 3.6.2.1  2000/03/30 14:46:56  club
//       ajout du copyright CNES
//
//       Revision 3.6  1999/07/06 15:24:17  club
//       Changement des signatures pour gestion des erreurs
//       par mécanisme d'exception
//
//       Revision 3.5  1998/06/25 06:42:57  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//       élimination de la méthode estValide
//
//       Revision 3.4  1998/01/22 08:33:18  luc
//       amélioration de l'en-tête de classe
//
//       Revision 3.3  1997/08/21 16:35:50  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.2  1997/03/25 15:01:33  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 14:45:05  luc
//       utilisation de la classe ChaineSimple
//       correction du destructeur virtuel
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.2  1996/09/25 10:54:54  luc
//       ajout d'un "cast" explicite pour le compilateur (idiot) version 3 de Sun
//       
//       Revision 2.1  1996/07/15 17:18:40  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.2  1994/11/09 15:00:10  mercator
//       elimination des directives #pragma
//       
//       Revision 1.1  1994/07/27 11:55:34  luc
//       Initial revision
//
//$Version
//       $Id: OptionSansValeur.h,v 3.10 2003/07/17 12:38:28 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __clubOptionSansValeur_h
#define __clubOptionSansValeur_h

#include "club/OptionBase.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class OptionSansValeur
//
//$Resume
//       classe des options ne prenant pas d'arguments
//
//$Description
//       gestion d'une option de la ligne de commande sans
//       valeur. Cette classe dérive de OptionBase.
//
//$Usage
//>     construction : 
//          à partir du code de l'option (sans le '-') et des drapeaux
//          généraux (nombres limites d'occurrences, presence d'une
//          valeur par defaut).
//>     utilisation  : 
//>       OptionSansValeur& operator = () 
//          affectation
//>       virtual void ajouterValeur    () 
//          ajoute une valeur à l'option
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class OptionSansValeur : public OptionBase
{ public :

  // constructeurs
  OptionSansValeur (const char *code, int occurrencesMin, int occurrencesMax)
    throw (ClubErreurs)
    : OptionBase (code, occurrencesMin, occurrencesMax, sansValeurDefaut,
                  OptionBase::sans_valeur, 0)
  {}

  OptionSansValeur (const string& code,
                    int occurrencesMin, int occurrencesMax)
    throw (ClubErreurs)
    : OptionBase (code, occurrencesMin, occurrencesMax, sansValeurDefaut,
                  OptionBase::sans_valeur, 0)
  {}

  // copie constructeur et affectation
  OptionSansValeur             (const OptionSansValeur& opt)
    : OptionBase (opt)
  {}

  OptionSansValeur& operator = (const OptionSansValeur& opt);

  // destructeur virtuel
  virtual ~OptionSansValeur () {}

  // fonctions redéfinies par rapport à la classe de base
  virtual void      ajouterValeur (const char *chaine)
    throw (ClubErreurs);

private :

  // AUTRES CONSTRUCTEURS
  OptionSansValeur ()
    throw (ClubErreurs)
    : OptionBase ("", 0, 0, sansValeurDefaut,
                  OptionBase::sans_valeur, 0)
  {}

};

#endif
