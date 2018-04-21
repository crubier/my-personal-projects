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
//>       OptionBase.h
//
//$Resume
//       fichier d'en-tête de la classe OptionBase
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class OptionBase
//
//$Historique
//       $Log: OptionBase.h,v $
//       Revision 3.17  2003/01/20 09:45:08  club
//       DM-ID 12 Ajout des initialisations (constructeur par défaut)
//
//       Revision 3.16  2002/12/09 15:55:48  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 3.15  2002/11/29 15:34:55  club
//       DM-ID 12 Correction de l'ordre des déclarations (public, protected, private)
//
//       Revision 3.14  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 3.13  2000/10/24 14:18:15  club
//       mise à jour des includes et ajout des tests de configuration.
//
//       Revision 3.12  2000/09/11 12:18:50  club
//       Mise à jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas installé.
//
//       Revision 3.11  2000/09/07 07:38:45  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.10  2000/07/03 08:48:30  club
//       Ajout du copyright CNES.
//
//       Revision 3.9.2.1  2000/03/30 14:46:55  club
//       ajout du copyright CNES
//
//       Revision 3.9  1999/07/06 15:24:16  club
//       Changement des signatures pour gestion des erreurs
//       par mécanisme d'exception
//
//       Revision 3.8  1998/11/17 11:44:18  club
//       correction de l'oubli de l'initialisation de valeursTrouvees_
//       dans le constructeur par copie
//
//       Revision 3.7  1998/06/25 06:42:28  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//       élimination de la méthode estValide
//
//       Revision 3.6  1998/04/26 13:02:28  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.5  1998/01/22 08:32:10  luc
//       amélioration de l'en-tête de classe
//       mise en cohérence de listes d'initialisation de constructeurs
//       et de l'ordre des attributs dans la classe
//
//       Revision 3.4  1997/09/12 07:40:54  luc
//       correction d'un commentaire dans l'en-tête
//
//       Revision 3.3  1997/08/21 16:35:25  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.2  1997/03/25 15:01:54  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 14:43:06  luc
//       utilisation de la classe ChaineSimple
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:16:43  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.2  1994/11/09 14:59:50  mercator
//       elimination des directives #pragma
//       
//       Revision 1.1  1994/07/27 11:55:31  luc
//       Initial revision
//
//$Version
//       $Id: OptionBase.h,v 3.17 2003/01/20 09:45:08 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_OptionBase_h
#define __club_OptionBase_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <string>

#include "club/ClubErreurs.h"

// définition de constantes booléennes pour faciliter la lecture
// des arguments de construction
const int avecValeurDefaut = 1;
const int sansValeurDefaut = 0;

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class OptionBase
//
//$Resume
//       classe abstraite de gestion d'options de la ligne de commande
//
//$Description
//       classe de base permettant la gestion d'options de la ligne de
//       commande, options avec ou sans arguments, de plusieurs types
//       possibles (entiers, réels, chaînes de caractères, tableaux),
//       avec des vérifications sur les nombres d'occurrences, sur les
//       valeurs autorisées, ...
//
//$Usage
//>     construction : 
//          à partir du code de l'option (sans le '-') et des drapeaux
//          généraux (nombres limites d'occurrences, presence d'une
//          valeur par defaut).
//>     utilisation  : 
//>       OptionBase& operator =        () 
//          affectation
//>       void lireValeur                () 
//>       virtual int verifier          () 
//          vérifie la présence de l'option si elle est obligatoire
//          (d'autres vérifications peuvent être ajoutées dans les
//          classes dérivées, comme la vérification des espaces de
//          validité)
//>       virtual void lireValeur        () 
//          met dans la variable pointée (ou le tableau) la (les)
//          valeur(s) de l'option. Dans la classe de base, toutes les
//          signatures de cette fonction génèrent une exception,
//          chaque classe dérivée doit redéfinir la signature qui lui
//          est propre de façon à la rendre opérationnelle).
//>       virtual void ajouterOccurrence () 
//          ajoute une occurrence de l'option
//>       virtual void ajouterValeur     () 
//          ajoute une valeur à l'option
//>       const string& code             () 
//          retourne le code de l'option
//>       int occurrencesMin             () 
//          retourne le nombre minimal d'occurrences de l'option
//>       int occurrencesMax             () 
//          retourne le nombre maximal d'occurrences de l'option
//>       int occurrencesPassees         () 
//          retourne le nombre d'occurrences effectivement passées
//>       int estValueeParDefaut         () 
//          teste si l'option a une valeur par défaut
//>       int type                       () 
//          retourne le type de l'option.
//>       int valeursAttendues           () 
//          retourne le nombre de valeurs attendues par l'option
//>       int valeursTrouvees            () 
//          retourne le nombre de valeurs trouvées dans la ligne de
//          commande
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class OptionBase
{ 
  public :

  enum {tableau_d_entiers, tableau_de_reels, tableau_de_chaines, sans_valeur};

  // constructeurs
  OptionBase (const char *code,
              int occurrencesMin, int occurrencesMax, int valueeParDefaut,
              int type, int valeursAttendues) 
    throw (ClubErreurs);
  OptionBase (const string& code,
              int occurrencesMin, int occurrencesMax, int valueeParDefaut,
              int type, int valeursAttendues)
    throw (ClubErreurs);


  OptionBase (const OptionBase& opt)
   : code_ (opt.code_),
     occurrencesMin_ (opt.occurrencesMin_),
     occurrencesMax_ (opt.occurrencesMax_),
     occurrences_ (opt.occurrences_),
     valueeParDefaut_ (opt.valueeParDefaut_), type_ (opt.type_),
     valeursAttendues_ (opt.valeursAttendues_),
     valeursTrouvees_ (opt.valeursTrouvees_)
  {}

  OptionBase& operator = (const OptionBase& opt);

  // destructeur virtuel
  virtual ~OptionBase () {}

  // fonctions d'accès aux éléments canoniques
  const string& code               () const { return code_;             }
  int           occurrencesMin     () const { return occurrencesMin_;   }
  int           occurrencesMax     () const { return occurrencesMax_;   }
  int           occurrencesPassees () const { return occurrences_;      }
  int           estValueeParDefaut () const { return valueeParDefaut_;  }
  int           type               () const { return type_;             }
  int           valeursAttendues   () const { return valeursAttendues_; }
  int           valeursTrouvees    () const { return valeursTrouvees_;  }

  // fonctions d'accès aux valeurs élémentaires
  // (utilisent les fonctions complètes par tableaux, avec un seul élément)
  void             lireValeur (int    *dest, int occurrence = 1) const
    throw (ClubErreurs) ;
  void             lireValeur (double *dest, int occurrence = 1) const
    throw (ClubErreurs) ;
  void             lireValeur (char   *dest, int occurrence = 1) const
    throw (ClubErreurs) ;
  void             lireValeur (string *dest, int occurrence = 1) const
    throw (ClubErreurs) ;

  // fonctions implantées (ou redéfinies) dans les classes dérivées
  virtual int      verifier  (string *ptrMessage)     const;

  virtual void     lireValeur (int nombre, int          dest [],
                               int occurrence = 1) const
    throw (ClubErreurs) ;
  virtual void     lireValeur (int nombre, double       dest [],
                               int occurrence = 1) const
    throw (ClubErreurs) ;
  virtual void     lireValeur (int nombre, char *       dest [],
                               int occurrence = 1) const
    throw (ClubErreurs) ;
  virtual void     lireValeur (int nombre, string dest [],
                               int occurrence = 1) const
    throw (ClubErreurs) ;

  virtual void     ajouterOccurrence () throw (ClubErreurs);
  virtual void     ajouterValeur     (const char  *chaine) = 0;


  protected :

  OptionBase ()
  {
    code_             = "";
    occurrencesMin_   = 0;
    occurrencesMax_   = 0;
    occurrences_      = 0;
    valueeParDefaut_  = 0;
    type_             = 0;
    valeursAttendues_ = 0;
    valeursTrouvees_  = 0;
  }
  
  protected :

  void           incrementeValeursTrouvees () { valeursTrouvees_++; }  

  private :

  string         code_;
  int            occurrencesMin_;
  int            occurrencesMax_;
  int            occurrences_;
  int            valueeParDefaut_;
  int            type_;
  int            valeursAttendues_;
  int            valeursTrouvees_;


};

#endif
