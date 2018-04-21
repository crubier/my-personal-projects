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
//>       OptionTableauEntiers.cpp
//
//$Resume
//       fichier d'implantation de la classe OptionTabEntiers
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class OptionTableauEntiers
//>         OptionTableauEntiers()  
//>         operator =()            
//>         ~OptionTableauEntiers() 
//>         verifier()              
//>         lireValeur()            
//>         ajouterOccurrence()     
//>         ajouterValeur()         
//
//$Historique
//       $Log: OptionTableauEntiers.cpp,v $
//       Revision 1.6  2003/02/03 13:46:27  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.5  2000/10/24 14:21:01  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
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
//       Revision 1.1.2.1  2000/03/30 14:46:51  club
//       ajout du copyright CNES
//
//       Revision 1.1  1999/07/07 08:06:06  club
//       Changement de nom des fichiers *Tab* en
//       *Tableau* pour correspondre au nom de la classe
//
//       Revision 3.8  1998/11/17 11:51:47  club
//       ajout de (void) explicites pour indiquer que l'on ignore certains retours
//
//       Revision 3.7  1998/07/27 10:13:49  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.6  1998/06/21 16:00:04  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//       élimination de la fonction estValide
//
//       Revision 3.5  1998/04/26 13:02:38  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.4  1997/08/21 16:44:05  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:47:58  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:04:23  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 15:19:41  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.3  1996/10/04 09:47:41  luc
//       appel explicite des méthodes de la classe de base pour
//       éviter le masquage des signatures de lireValeur invalides
//       par la seule signature valide
//       
//       Revision 2.2  1996/09/25 10:54:40  luc
//       ajout d'un "cast" explicite pour le compilateur (idiot) version 3 de Sun
//       
//       Revision 2.1  1996/07/15 17:19:09  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.6  1995/07/12 15:02:16  mercator
//       ajout d'un pointeur this explicite pour aider le compilateur SUN a comprendre
//       
//       Revision 1.5  1995/06/26 07:36:12  mercator
//       modification de la portee de variables de boucle for
//       
//       Revision 1.4  1995/06/26 06:38:10  mercator
//       remplacement d'un copie-constructeur par un operateur =
//       (on ne peut construire une instance de classe abstraite, meme pour initialiser
//       une instance de classe derivee concrete)
//       
//       Revision 1.3  1994/11/09 15:02:14  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/08/30 12:54:25  mercator
//       remplacement de "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 12:05:56  luc
//       Initial revision
//
//$Version
//       $Id: OptionTableauEntiers.cpp,v 1.6 2003/02/03 13:46:27 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
# include <cstdlib>
#endif

#include "club/OptionTableauEntiers.h"
#include "club/ClubErreurs.h"

OptionTableauEntiers::OptionTableauEntiers (const char *code,
                                            int occurrencesMin,
                                            int occurrencesMax,
                                            int valueeParDefaut,
                                            int valeursAttendues,
                                            const int* valeurs,
                                            int limiteInf, int limiteSup)
  throw (ClubErreurs)
  : OptionBase (code, occurrencesMin, occurrencesMax, valueeParDefaut, 
                OptionBase::tableau_d_entiers, valeursAttendues),
    tabValeurs_ (0), limiteInf_ (limiteInf), limiteSup_ (limiteSup)
{ 
  if (valeursAttendues == 0)
    throw  ClubErreurs (ClubErreurs::nombre_arguments_nul,
                        OptionBase::code ().c_str ());
  
  if (valueeParDefaut)
  { 
    if (valeurs == 0)
      throw ClubErreurs (ClubErreurs::valeur_par_defaut_manquante,
                         OptionBase::code ().c_str ());
    else
    { // vérification des valeurs par défaut
      for (int i = 0; i < valeursAttendues; i++)
      { if ((valeurs [i] < limiteInf) || (valeurs [i] > limiteSup))
        throw ClubErreurs (ClubErreurs::option_entiere_hors_limites,
                           OptionBase::code ().c_str (),
                           limiteInf, limiteSup, valeurs [i]);
      }
      
      // stockage
      tabValeurs_     = new int* [1];
      tabValeurs_ [0] = new int  [valeursAttendues];
      for (int k = 0; k < valeursAttendues; k++)
        tabValeurs_ [0][k] = valeurs [k];
      
    }
  }
}

OptionTableauEntiers::OptionTableauEntiers (const string& code,
                                            int occurrencesMin,
                                            int occurrencesMax,
                                            int valueeParDefaut,
                                            int valeursAttendues,
                                            const int* valeurs,
                                            int limiteInf, int limiteSup)
  throw(ClubErreurs)
  : OptionBase (code, occurrencesMin, occurrencesMax, valueeParDefaut, 
                OptionBase::tableau_d_entiers, valeursAttendues),
    tabValeurs_ (0), limiteInf_ (limiteInf), limiteSup_ (limiteSup)
{ 
  if (valeursAttendues == 0)
    throw ClubErreurs (ClubErreurs::nombre_arguments_nul,
                       OptionBase::code ().c_str ());
  
  if (valueeParDefaut)
  { 
    if (valeurs == 0)
      throw ClubErreurs (ClubErreurs::valeur_par_defaut_manquante,
                         OptionBase::code ().c_str ());
    else
    { // vérification des valeurs par défaut
      for (int i = 0; i < valeursAttendues; i++)
      { 
        if ((valeurs [i] < limiteInf) || (valeurs [i] > limiteSup))
          throw ClubErreurs (ClubErreurs::option_entiere_hors_limites,
                             OptionBase::code ().c_str (),
                             limiteInf, limiteSup, valeurs [i]);
      }
      // stockage
      tabValeurs_     = new int* [1];
      tabValeurs_ [0] = new int  [valeursAttendues];
      for (int k = 0; k < valeursAttendues; k++)
        tabValeurs_ [0][k] = valeurs [k];

    }
  }
  
}

OptionTableauEntiers::OptionTableauEntiers (const OptionTableauEntiers& opt)
  : OptionBase (opt),
    tabValeurs_ (0), limiteInf_ (opt.limiteInf_), limiteSup_ (opt.limiteSup_)
{ // copie-constructeur

  if (opt.occurrencesPassees ())
  { // allocation d'une table d'occurrences
    tabValeurs_ = new int* [opt.occurrencesPassees ()];
    for (int i = 0; i < opt.occurrencesPassees (); i++)
    { // allocation d'une table des valeurs pour l'occurrence courante
      tabValeurs_ [i] = new int [opt.valeursAttendues ()];

      // remplissage de la table
      for (int j = 0; j < opt.valeursAttendues (); j++)
        tabValeurs_ [i][j] = opt.tabValeurs_ [i][j];

    }
  }
  else if (opt.estValueeParDefaut ())
  { // allocation d'une entrée par défaut
    tabValeurs_     = new int* [1];
    tabValeurs_ [0] = new int [opt.valeursAttendues ()];

    // remplissage de la table
    for (int k = 0; k < opt.valeursAttendues (); k++)
      tabValeurs_ [0][k] = opt.tabValeurs_ [0][k];

  }
}

OptionTableauEntiers& OptionTableauEntiers::operator =
                                              (const OptionTableauEntiers& opt)
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

    // copie effective
    if (opt.occurrencesPassees ())
    { // allocation d'une table d'occurrences
      tabValeurs_ = new int* [opt.occurrencesPassees ()];
      for (int i = 0; i < opt.occurrencesPassees (); i++)
      { // allocation d'une table des valeurs pour l'occurrence courante
        tabValeurs_ [i] = new int [opt.valeursAttendues ()];

        // remplissage de la table
        for (int j = 0; j < opt.valeursAttendues (); j++)
          tabValeurs_ [i][j] = opt.tabValeurs_ [i][j];

      }
    }
    else if (opt.estValueeParDefaut ())
    { // allocation d'une entrée par défaut
      tabValeurs_ = new int* [1];
      tabValeurs_ [0] = new int [opt.valeursAttendues ()];

      // remplissage de la table
      for (int k = 0; k < opt.valeursAttendues (); k++)
        tabValeurs_ [0][k] = opt.tabValeurs_ [0][k];

    }

    limiteInf_ = opt.limiteInf_;
    limiteSup_ = opt.limiteSup_;

  }

  return *this;

}

OptionTableauEntiers::~OptionTableauEntiers ()
{ if (occurrencesPassees ())
  { for (int i = 0; i < occurrencesPassees (); i++)
      delete [] tabValeurs_ [i];
    delete [] tabValeurs_;
  }
  else if (estValueeParDefaut ())
  { delete [] tabValeurs_ [0];
    delete [] tabValeurs_;
  }

}

int OptionTableauEntiers::verifier (string *ptrMessage) const
{ int r = OptionBase::verifier (ptrMessage);
  if (r)
    return r;

  for (int n = 0; n < occurrencesPassees (); n++)
  { for (int i = 0; i < valeursAttendues (); i++)
    { int* tableau = tabValeurs_ [n];

      if ((tableau [i] < limiteInf_) || (tableau [i] > limiteSup_))
      { ClubErreurs e (ClubErreurs::option_entiere_hors_limites,
                       code ().c_str (), limiteInf_, limiteSup_,
                       tableau [i]);
        *ptrMessage = e.why ();
        e.correction ();
        return ClubErreurs::option_entiere_hors_limites;
      }

    }
  }

  return 0;

}

void OptionTableauEntiers::lireValeur (int nombre, int dest [],
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
      int* tableau = tabValeurs_ [0];
      for (int i = 0; i < nombre; i++)
         dest [i] = tableau [i];
    }
  }
  else
  { if ((occurrence < 1) || (occurrence > occurrencesPassees ()))
      throw ClubErreurs (ClubErreurs::occurrence_inexistante,
                         occurrence, code ().c_str (),
                         occurrencesPassees ());
    else
    { int* tableau = tabValeurs_ [occurrence - 1];
      for (int i = 0; i < nombre; i++)
         dest [i] = tableau [i];
    }

  }

}

void OptionTableauEntiers::lireValeur (int nombre, double dest [],
                                      int occurrence) const
  throw (ClubErreurs)
{ OptionBase::lireValeur (nombre, dest, occurrence); }

void OptionTableauEntiers::lireValeur (int nombre, char *dest [],
                                      int occurrence) const
  throw (ClubErreurs)
{ OptionBase::lireValeur (nombre, dest, occurrence); }

void OptionTableauEntiers::lireValeur (int nombre, string dest [],
                                      int occurrence) const
  throw (ClubErreurs)
{ OptionBase::lireValeur (nombre, dest, occurrence); }

void OptionTableauEntiers::ajouterOccurrence ()
  throw (ClubErreurs)
{ 
  OptionBase::ajouterOccurrence ();

  if ((occurrencesPassees () != 1) || (! estValueeParDefaut ()))
  { // on doit allouer une nouvelle entrée dans la table des occurrences
    int **nouvelleTable = new int* [occurrencesPassees ()];
    for (int i = 0; i < occurrencesPassees () - 1; i++)
      nouvelleTable [i] = tabValeurs_ [i];
    if (occurrencesPassees () != 1)
      delete [] tabValeurs_;
    tabValeurs_ = nouvelleTable;

    tabValeurs_ [occurrencesPassees () - 1] = new int [valeursAttendues ()];
    for (int j = 0; j < valeursAttendues (); j++)
      tabValeurs_ [occurrencesPassees () - 1][j] = 0;

  }

}

void OptionTableauEntiers::ajouterValeur (const char *chaine)
  throw (ClubErreurs)
{ incrementeValeursTrouvees ();

  if (valeursTrouvees () > valeursAttendues ())
    throw ClubErreurs (ClubErreurs::nombres_arguments_incompatibles,
                       code ().c_str (),
                       valeursTrouvees (), valeursAttendues ());

  tabValeurs_ [occurrencesPassees()-1][valeursTrouvees()-1] = atoi (chaine);


}
