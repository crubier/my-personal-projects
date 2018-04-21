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
//>       OptionTableauChaines.cpp
//
//$Resume
//       fichier d'implantation de la classe OptionTabChaines
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class OptionTableauChaines
//>         OptionTableauChaines()  
//>         operator =()            
//>         ~OptionTableauChaines() 
//>         verifier()              
//>         lireValeur()            
//>         ajouterOccurrence()     
//>         ajouterValeur()         
//
//$Historique
//       $Log: OptionTableauChaines.cpp,v $
//       Revision 1.5  2003/02/03 13:45:54  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.4  2000/10/24 08:33:30  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.3  2000/09/07 08:02:09  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.2  2000/07/03 08:57:21  club
//       Ajout du copyright CNES
//
//       Revision 1.1.2.1  2000/03/30 14:46:50  club
//       ajout du copyright CNES
//
//       Revision 1.1  1999/07/07 08:06:05  club
//       Changement de nom des fichiers *Tab* en
//       *Tableau* pour correspondre au nom de la classe
//
//       Revision 3.10  1999/03/18 10:04:08  club
//       modification d'un calcul de longueur de chaîne avec déclaration et utilisation
//       séparée, l'opérateur de coercition et l'utilisation simultanés étant refusés
//       par le compilateur SUN Workshop 5.0
//
//       Revision 3.9  1998/11/17 11:52:48  club
//       ajout de (void) explicites pour indiquer que l'on ignore certains retours
//
//       Revision 3.8  1998/07/27 10:13:47  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.7  1998/06/21 15:59:38  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//       élimination de la fonction estValide
//
//       Revision 3.6  1998/04/26 13:02:36  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.5  1998/01/22 08:22:37  luc
//       ajout d'une cohercition explicite de "unsigned int" en "int"
//
//       Revision 3.4  1997/08/21 16:44:05  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:47:48  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:04:28  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 15:19:25  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.3  1996/10/04 09:47:02  luc
//       appel explicite des méthodes de la classe de base pour
//       éviter le masquage des signatures de lireValeur invalides
//       par la seule signature valide
//       
//       Revision 2.2  1996/09/25 10:54:47  luc
//       ajout d'un "cast" explicite pour le compilateur (idiot) version 3 de Sun
//       
//       Revision 2.1  1996/07/15 17:18:51  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.6  1995/07/12 15:02:14  mercator
//       ajout d'un pointeur this explicite pour aider le compilateur SUN a comprendre
//       
//       Revision 1.5  1995/06/26 07:36:12  mercator
//       modification de la portee de variables de boucle for
//       
//       Revision 1.4  1995/06/26 06:38:08  mercator
//       remplacement d'un copie-constructeur par un operateur =
//       (on ne peut construire une instance de classe abstraite, meme pour initialiser
//       une instance de classe derivee concrete)
//       
//       Revision 1.3  1994/11/09 15:02:10  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/08/30 12:54:25  mercator
//       remplacement de "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 12:05:55  luc
//       Initial revision
//
//$Version
//       $Id: OptionTableauChaines.cpp,v 1.5 2003/02/03 13:45:54 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/OptionTableauChaines.h"
#include "club/ClubErreurs.h"

OptionTableauChaines::OptionTableauChaines
                                       (const char *code,
                                        int occurrencesMin,
                                        int occurrencesMax,
                                        int valueeParDefaut,
                                        int valeursAttendues,
                                        const char **valeurs,
                                        int longueurMax,
                                        int nbAutorisees,
                                        const char **tabAutorisees)
  throw (ClubErreurs)
  : OptionBase (code, occurrencesMin, occurrencesMax, valueeParDefaut,
                OptionBase::tableau_de_chaines, valeursAttendues),
    tabValeurs_ (0), longueurMax_ (longueurMax), nbAutorisees_ (nbAutorisees),
    tabAutorisees_ (nbAutorisees_ ? (new string [nbAutorisees_]) : 0)
{ // construction à partir de char *

  if (valeursAttendues == 0)
  throw ClubErreurs (ClubErreurs::nombre_arguments_nul,
                     OptionBase::code ().c_str ());

  // table des valeurs autorisées (s'il y en a)
  for (int l = 0; l < nbAutorisees; l++)
    tabAutorisees_ [l] = tabAutorisees [l];

  if (valueeParDefaut)
  { // il y a des valeurs par défaut
    // (utilisées s'il n'y a aucune occurrence à l'exécution)

    if (valeurs == 0)
      // il aurait dû y avoir un tableau donnant les valeurs par défaut ...
      throw ClubErreurs (ClubErreurs::valeur_par_defaut_manquante,
                         OptionBase::code ().c_str ());


    for (int i = 0; i < valeursAttendues; i++)
    { // vérification du tableau des valeurs pas défaut

      int longueur = strlen (valeurs [i]);
      if (longueur > longueurMax_)
        // la longueur des valeurs par défaut dépasse le maximum
        throw ClubErreurs (ClubErreurs::option_chaine_trop_longue,
                           OptionBase::code ().c_str (),
                           valeurs [i], longueurMax_);

      if (nbAutorisees)
      { // espace de validité
        int ok = 0;
        for (int j = 0; (!ok) && (j < nbAutorisees); j++)
          ok = (tabAutorisees [j] == valeurs [i]);

        if (! ok) 
          // on a parcouru tout l'espace de validité sans succès
          throw ClubErreurs (ClubErreurs::option_chaine_hors_domaine,
                             OptionBase::code ().c_str (),
                             valeurs [i], nbAutorisees,
                             tabAutorisees);
        
      }

    }

    // stockage des valeurs par défaut dans le tableau des occurrences
    tabValeurs_     = new string* [1];
    tabValeurs_ [0] = new string  [valeursAttendues];
    for (int k = 0; k < valeursAttendues; k++)
      tabValeurs_ [0][k] = valeurs [k];

  }

}

OptionTableauChaines::OptionTableauChaines
                                       (const string& code,
                                        int occurrencesMin,
                                        int occurrencesMax,
                                        int valueeParDefaut,
                                        int valeursAttendues,
                                        const string *valeurs,
                                        int longueurMax,
                                        int nbAutorisees,
                                        const string *tabAutorisees)
  throw (ClubErreurs)
  : OptionBase (code, occurrencesMin, occurrencesMax, valueeParDefaut,
                OptionBase::tableau_de_chaines, valeursAttendues),
    tabValeurs_ (0), longueurMax_ (longueurMax), nbAutorisees_ (nbAutorisees),
    tabAutorisees_ (nbAutorisees_ ? (new string [nbAutorisees_]) : 0)
{ // construction à partir de string

  if (valeursAttendues == 0)
   throw ClubErreurs (ClubErreurs::nombre_arguments_nul,
                      OptionBase::code ().c_str ());

  // table des valeurs autorisées (s'il y en a)
  for (int l = 0; l < nbAutorisees; l++)
    tabAutorisees_ [l] = tabAutorisees [l];

  if (valueeParDefaut)
  { // il y a des valeurs par défaut
    // (utilisées s'il n'y a aucune occurrence à l'exécution)

    if (valeurs == 0)
    { // il aurait dû y avoir un tableau donnant les valeurs par défaut ...
      throw ClubErreurs (ClubErreurs::valeur_par_defaut_manquante,
                         OptionBase::code ().c_str ());
    }

    for (int i = 0; i < valeursAttendues; i++)
    { // vérification du tableau des valeurs pas défaut

      if (valeurs [i].size () > (unsigned int) longueurMax_)
      { // la longueur des valeurs par défaut dépasse le maximum
        throw ClubErreurs (ClubErreurs::option_chaine_trop_longue,
                           OptionBase::code ().c_str (),
                           valeurs [i].c_str (), longueurMax_);
      }

      if (nbAutorisees)
      { // espace de validité
        int ok = 0;
        for (int j = 0; (!ok) && (j < nbAutorisees); j++)
          ok = (tabAutorisees [j] == valeurs [i]);

        if (! ok) 
        { // on a parcouru tout l'espace de validité sans succès
          throw ClubErreurs (ClubErreurs::option_chaine_hors_domaine,
                             OptionBase::code ().c_str (),
                             valeurs [i].c_str (),
                             nbAutorisees, tabAutorisees);
        }
      }

    }

    // stockage des valeurs par défaut dans le tableau des occurrences
    tabValeurs_     = new string* [1];
    tabValeurs_ [0] = new string  [valeursAttendues];
    for (int k = 0; k < valeursAttendues; k++)
      tabValeurs_ [0][k] = valeurs [k];

  }

}

OptionTableauChaines::OptionTableauChaines (const OptionTableauChaines& opt)
  : OptionBase (opt),
    tabValeurs_ (0), longueurMax_ (opt.longueurMax_),
    nbAutorisees_ (opt.nbAutorisees_),
    tabAutorisees_ (nbAutorisees_ ? (new string [nbAutorisees_]) : 0)
{ // copie-constructeur

  if (opt.occurrencesPassees ())
  { // allocation d'une table d'occurrences
    tabValeurs_ = new string* [opt.occurrencesPassees ()];
    for (int i = 0; i < opt.occurrencesPassees (); i++)
    { // allocation d'une table des valeurs pour l'occurrence courante
      tabValeurs_ [i] = new string [opt.valeursAttendues ()];

      // remplissage de la table
      for (int j = 0; j < opt.valeursAttendues (); j++)
        tabValeurs_ [i][j] = opt.tabValeurs_ [i][j];

    }
  }
  else if (opt.estValueeParDefaut ())
  { // allocation d'une entrée par défaut
    tabValeurs_     = new string* [1];
    tabValeurs_ [0] = new string  [opt.valeursAttendues ()];

    // remplissage de la table
    for (int k = 0; k < opt.valeursAttendues (); k++)
      tabValeurs_ [0][k] = opt.tabValeurs_ [0][k];

  }

  // table des chaînes autorisées
  for (int l = 0; l < nbAutorisees_; l++)
    tabAutorisees_ [l] = opt.tabAutorisees_ [l];

}

OptionTableauChaines& OptionTableauChaines::operator =
                                              (const OptionTableauChaines& opt)
{ if (this != &opt)      // protection contre x = x
  { this->OptionBase::operator = (opt);

    // libération des tables précédentes
    if (occurrencesPassees ())
    { for (int i = 0; i < occurrencesPassees (); i++)
        delete [] tabValeurs_ [i];
      delete [] tabValeurs_;
    }
    else if (estValueeParDefaut ())
    { delete [] tabValeurs_ [0];
      delete [] tabValeurs_;
    }

    if (nbAutorisees_)
      delete [] tabAutorisees_;

    // copie effective
    if (opt.occurrencesPassees ())
    { // allocation d'une table d'occurrences
      tabValeurs_ = new string* [opt.occurrencesPassees ()];
      for (int i = 0; i < opt.occurrencesPassees (); i++)
      { // allocation d'une table des valeurs pour l'occurrence courante
        tabValeurs_ [i] = new string [opt.valeursAttendues ()];

        // remplissage de la table
        for (int j = 0; j < opt.valeursAttendues (); j++)
          tabValeurs_ [i][j] = opt.tabValeurs_ [i][j];

      }
    }
    else if (opt.estValueeParDefaut ())
    { // allocation d'une entrée par défaut
      tabValeurs_ = new string* [1];
      tabValeurs_ [0] = new string [opt.valeursAttendues ()];

      // remplissage de la table
      for (int k = 0; k < opt.valeursAttendues (); k++)
        tabValeurs_ [0][k] = opt.tabValeurs_ [0][k];

    }

    longueurMax_    = opt.longueurMax_;

    for (int l = 0; l < nbAutorisees_; l++)
      tabAutorisees_ [l] = opt.tabAutorisees_ [l];

  }

  return *this;

}

OptionTableauChaines::~OptionTableauChaines ()
{ if (occurrencesPassees ())
  { for (int i = 0; i < occurrencesPassees (); i++)
      delete [] tabValeurs_ [i];
    delete [] tabValeurs_;
  }
  else if (estValueeParDefaut ())
  { delete [] tabValeurs_ [0];
    delete [] tabValeurs_;
  }

  if (nbAutorisees_)
    delete [] tabAutorisees_;

}

int OptionTableauChaines::verifier (string *ptrMessage) const
{ int r = OptionBase::verifier (ptrMessage);
  if (r)
    return r;

  for (int n = 0; n < occurrencesPassees (); n++)
  { for (int i = 0; i < valeursAttendues (); i++)
    { if (tabValeurs_ [n][i].size () > (unsigned int) longueurMax_)
      { ClubErreurs e (ClubErreurs::option_chaine_trop_longue,
                       code ().c_str (),
                       tabValeurs_ [n][i].c_str (), longueurMax_);
        *ptrMessage = e.why ();
        e.correction ();
        return ClubErreurs::option_chaine_trop_longue;
      }

      if (nbAutorisees_)
      { // espace de validité
        int ok = 0;
        for (int j = 0; (!ok) && (j < nbAutorisees_); j++)
          ok = (tabValeurs_ [n][i] == tabAutorisees_ [j]);
        if (! ok) 
        { ClubErreurs e (ClubErreurs::option_chaine_hors_domaine,
                         code ().c_str (), tabValeurs_ [n][i].c_str (),
                         nbAutorisees_, tabAutorisees_);
          *ptrMessage = e.why ();
          e.correction ();
          return ClubErreurs::option_chaine_hors_domaine;
        }
      }

    }
  }

  return 0;

}

void OptionTableauChaines::lireValeur (int nombre, int dest [],
                                      int occurrence) const
  throw (ClubErreurs)
{ OptionBase::lireValeur (nombre, dest, occurrence); }

void OptionTableauChaines::lireValeur (int nombre, double dest [],
                                      int occurrence) const
  throw (ClubErreurs)
{ OptionBase::lireValeur (nombre, dest, occurrence); }

void OptionTableauChaines::lireValeur (int nombre, char* dest [],
                                      int occurrence) const
  throw (ClubErreurs)
{ if (nombre != valeursAttendues ())
   throw ClubErreurs (ClubErreurs::taille_tableau_arguments,
                      code ().c_str (), valeursAttendues ());

  if (occurrencesPassees () == 0)
  { if (! estValueeParDefaut ())
      throw ClubErreurs (ClubErreurs::valeur_par_defaut_manquante,
                         code ().c_str ());
    else
    { // en l'absence d'option, on utilise les valeurs par défaut
      for (int i = 0; i < nombre; i++)
      { int taille = tabValeurs_ [0][i].size () + 1;
        if (taille > longueurMax_)
          taille = longueurMax_;
        (void) strncpy (dest [i], tabValeurs_ [0][i].c_str (), taille);
        dest [i] [taille - 1] = '\0';
      }
    }
  }
  else
  { if ((occurrence < 1) || (occurrence > occurrencesPassees ()))
      throw ClubErreurs (ClubErreurs::occurrence_inexistante,
                         occurrence, code ().c_str (),
                         occurrencesPassees ());
  else
    { for (int i = 0; i < nombre; i++)
      { int taille = tabValeurs_ [occurrence - 1][i].size () + 1;
        if (taille > longueurMax_)
          taille = longueurMax_;
        (void) strncpy (dest [i], tabValeurs_ [occurrence - 1][i].c_str (),
                        taille);
        dest [i] [taille] = '\0';
      }
    }

  }
}

void OptionTableauChaines::lireValeur (int nombre, string dest [],
                                      int occurrence) const
  throw (ClubErreurs)
{ if (nombre != valeursAttendues ())
   throw ClubErreurs (ClubErreurs::taille_tableau_arguments,
                      code ().c_str (), valeursAttendues ());

  if (occurrencesPassees () == 0)
  { if (! estValueeParDefaut ())
      throw ClubErreurs (ClubErreurs::valeur_par_defaut_manquante,
                         code ().c_str ());
    else
    { // en l'absence d'option, on utilise les valeurs par défaut
      for (int i = 0; i < nombre; i++)
        dest [i] = tabValeurs_ [0][i];
    }
  }
  else
  { if ((occurrence < 1) || (occurrence > occurrencesPassees ()))
      throw ClubErreurs (ClubErreurs::occurrence_inexistante,
                          occurrence, code ().c_str (),
                          occurrencesPassees ());
    else
      for (int i = 0; i < nombre; i++)
        dest [i] = tabValeurs_ [occurrence - 1][i];

  }

}

void OptionTableauChaines::ajouterOccurrence ()
  throw (ClubErreurs)
{ 
  OptionBase::ajouterOccurrence ();

  if ((occurrencesPassees () != 1) || (! estValueeParDefaut ()))
  { // on doit allouer une nouvelle entrée dans la table des occurrences

    // allocation d'une table complète plus grande
    string **nouvelleTable = new string* [occurrencesPassees ()];

    // déplacement des occurrences précédentes (copie des pointeurs seuls)
    for (int i = 0; i < occurrencesPassees () - 1; i++)
      nouvelleTable [i] = tabValeurs_ [i];

    // création d'une table des valeurs pour la nouvelle occurrence
    nouvelleTable [occurrencesPassees () - 1] =
                                      new string [valeursAttendues ()];

    // remplacement de l'ancienne table par la nouvelle
    if (occurrencesPassees () != 1)
      delete [] tabValeurs_;
    tabValeurs_ = nouvelleTable;

  }


}

void OptionTableauChaines::ajouterValeur (const char *chaine)
  throw (ClubErreurs)
{ // ajout d'une valeur pour une occurrence d'option donnée
  incrementeValeursTrouvees ();

  if (valeursTrouvees () > valeursAttendues ())
    throw ClubErreurs (ClubErreurs::nombres_arguments_incompatibles,
                       code ().c_str (),
                       valeursTrouvees (), valeursAttendues ());

  int n = occurrencesPassees () - 1;
  int i = valeursTrouvees    () - 1;
  tabValeurs_ [n][i] = chaine;

}
