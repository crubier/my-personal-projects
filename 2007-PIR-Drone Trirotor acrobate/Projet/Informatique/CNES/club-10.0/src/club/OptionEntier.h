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
//>       OptionEntier.h
//
//$Resume
//       fichier d'en-tête de la classe OptionEntier
//
//$Description
//       Module de déclaration de la classe OptionEntier
//
//$Contenu
//>       class OptionEntier
//
//$Historique
//       $Log: OptionEntier.h,v $
//       Revision 3.10  2002/12/09 15:56:21  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 3.9  2000/09/07 07:41:45  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.8  2000/07/03 08:48:30  club
//       Ajout du copyright CNES.
//
//       Revision 3.7.2.1  2000/03/30 14:46:56  club
//       ajout du copyright CNES
//
//       Revision 3.7  1999/07/06 15:24:17  club
//       Changement des signatures pour gestion des erreurs
//       par mécanisme d'exception
//
//       Revision 3.6  1998/07/27 10:14:09  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.5  1998/06/25 06:42:45  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//       élimination de la méthode estValide
//
//       Revision 3.4  1998/01/22 08:32:51  luc
//       amélioration de l'en-tête de classe
//
//       Revision 3.3  1997/08/21 16:35:38  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.2  1997/03/25 15:01:43  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 14:44:31  luc
//       utilisation de la classe ChaineSimple
//       correction du destructeur virtuel
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.2  1996/09/25 10:55:41  luc
//       ajout d'un "cast" explicite pour le compilateur (idiot) version 3 de Sun
//       
//       Revision 2.1  1996/07/15 17:17:52  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.2  1994/11/09 14:59:59  mercator
//       elimination des directives #pragma
//       
//       Revision 1.1  1994/07/27 11:55:32  luc
//       Initial revision
//
//$Version
//       $Id: OptionEntier.h,v 3.10 2002/12/09 15:56:21 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_OptionEntier_h
#define __club_OptionEntier_h

#include "club/OptionTableauEntiers.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class OptionEntier
//
//$Resume
//       classe des options prenant des arguments entiers
//
//$Description
//       gestion d'une option de la ligne de commande à argument
//       entier. Cette classe dérive de OptionTabEntiers
//
//$Usage
//>     construction : 
//          à partir du code de l'option (sans le '-') et des drapeaux
//          généraux (nombres limites d'occurrences, presence d'une
//          valeur par defaut).
//>     utilisation  : 
//>       OptionEntier& operator = () 
//           affectation
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class OptionEntier : public OptionTableauEntiers
{ public :

  // constructeurs
  OptionEntier (const char *code,
                int occurrencesMin, int occurrencesMax, int valueeParDefaut,
                int valeur = 0,
                int limiteInf = -1000000000,
                int limiteSup =  1000000000)
    throw (ClubErreurs)
    : OptionTableauEntiers (code, occurrencesMin, occurrencesMax,
                            valueeParDefaut, 1, &valeur, limiteInf, limiteSup)
  {}

  OptionEntier (const string& code,
                int occurrencesMin, int occurrencesMax, int valueeParDefaut,
                int valeur = 0,
                int limiteInf = -1000000000,
                int limiteSup =  1000000000)
                throw (ClubErreurs)
    : OptionTableauEntiers (code, occurrencesMin, occurrencesMax,
                            valueeParDefaut, 1, &valeur, limiteInf, limiteSup)
  {}

  // copie constructeur et affectation
  OptionEntier             (const OptionEntier& opt)
    : OptionTableauEntiers (opt)
  {}

  OptionEntier& operator = (const OptionEntier& opt);

  // destructeur virtuel
  virtual ~OptionEntier () {}

protected :

  // CE CONSTRUCTEUR NE DOIT JAMAIS ETRE APPELE
  OptionEntier () {}

};

#endif
