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
//>       OptionTableauEntiers.h
//$Resume
//       fichier d'en-tête de la classe OptionTableauEntiers
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class OptionTableauEntiers
//$Historique
//       $Log: OptionTableauEntiers.h,v $
//       Revision 1.5  2003/07/17 12:38:28  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 1.4  2002/12/09 15:57:25  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.3  2000/09/07 07:40:51  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.2  2000/07/03 08:48:31  club
//       Ajout du copyright CNES.
//
//       Revision 1.1.2.1  2000/03/30 14:46:57  club
//       ajout du copyright CNES
//
//       Revision 1.1  1999/07/06 15:52:54  club
//       Changement de nom des fichiers *Tab* en *Tableau* pour
//       correspondre au nom de la classe. Passage à une
//       gestion d'erreurs basée sur les exceptions.
//
//       Revision 3.7  1998/07/27 10:14:11  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.6  1998/06/25 06:43:09  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//       élimination de la méthode estValide
//
//       Revision 3.5  1998/04/26 13:02:38  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.4  1998/01/22 08:33:48  luc
//       amélioration de l'en-tête de classe
//
//       Revision 3.3  1997/08/21 16:36:03  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.2  1997/03/25 15:01:24  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 14:45:47  luc
//       utilisation de la classe ChaineSimple
//       correction du destructeur virtuel
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.2  1996/10/04 09:47:16  luc
//       appel explicite des méthodes de la classe de base pour
//       éviter le masquage des signatures de lireValeur invalides
//       par la seule signature valide
//       
//       Revision 2.1  1996/07/15 17:19:17  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.2  1994/11/09 15:00:20  mercator
//       elimination des directives #pragma
//       
//       Revision 1.1  1994/07/27 11:55:36  luc
//       Initial revision
//
//$Version
//       $Id: OptionTableauEntiers.h,v 1.5 2003/07/17 12:38:28 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_OptionTableauEntiers_h
#define __club_OptionTableauEntiers_h

#include "club/OptionBase.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class OptionTableauEntiers
//
//$Resume
//       classe des options prenant des arguments entiers
//
//$Description
//       gestion d'une option de la ligne de commande à arguments
//       entiers. Cette classe dérive de OptionBase.
//
//$Usage
//>     construction : 
//          à partir du code de l'option (sans le '-') et des drapeaux
//          généraux (nombres limites d'occurrences, presence d'une
//          valeur par defaut).
//>     utilisation  : 
//>       OptionTableauEntiers& operator = () 
//          affectation
//>       virtual int verifier             () 
//          vérifie la présence de l'option si elle est obligatoire
//>       virtual void lireValeur           () 
//          met dans la variable pointée (ou le tableau) la (les)
//          valeur(s) de l'option.
//>       virtual void ajouterOccurrence    () 
//          ajoute une occurrence de l'option
//>       virtual void ajouterValeur        () 
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

class OptionTableauEntiers : public OptionBase
{ 
  public :

  // constructeurs
  OptionTableauEntiers (const char *code,
                        int occurrencesMin, int occurrencesMax,
                        int valueeParDefaut,
                        int nombreValeurs, const int* valeurs = 0,
                        int limiteInf = -1000000000,
                        int limiteSup =  1000000000)
    throw (ClubErreurs);

  OptionTableauEntiers (const string& code,
                        int occurrencesMin, int occurrencesMax,
                        int valueeParDefaut,
                        int nombreValeurs, const int* valeurs = 0,
                        int limiteInf = -1000000000,
                        int limiteSup =  1000000000)
    throw (ClubErreurs);

  // copie constructeur et affectation
  OptionTableauEntiers             (const OptionTableauEntiers& opt);

  OptionTableauEntiers& operator = (const OptionTableauEntiers& opt);

  // destructeur virtuel
  virtual ~OptionTableauEntiers ();

  // fonctions redéfinies par rapport à la classe de base
  virtual int       verifier         (string *ptrMessage) const;
  virtual void      lireValeur       (int nombre, int          dest [],
                                      int occurrence = 1) const
    throw (ClubErreurs);
  virtual void      lireValeur       (int nombre, double       dest [],
                                      int occurrence = 1) const
    throw (ClubErreurs);
  virtual void      lireValeur       (int nombre, char*        dest [],
                                      int occurrence = 1) const
    throw (ClubErreurs);
  virtual void      lireValeur       (int nombre, string dest [],
                                      int occurrence = 1) const
    throw (ClubErreurs);
  virtual void      ajouterOccurrence ()
    throw (ClubErreurs);
  virtual void      ajouterValeur    (const char *chaine)
    throw (ClubErreurs);

protected :

  // AUTRES CONSTRUCTEURS
  OptionTableauEntiers ()
  {
    tabValeurs_   = NULL;
    limiteInf_    = -1000000000;
    limiteSup_    =  1000000000;
  }

private:
  int            **tabValeurs_;
  int              limiteInf_;
  int              limiteSup_;

};

#endif
