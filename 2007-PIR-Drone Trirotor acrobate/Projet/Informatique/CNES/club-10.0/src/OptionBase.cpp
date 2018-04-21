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
//>       OptionBase.cpp
//
//$Resume
//       fichier d'implantation de la classe OptionBase
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       static int LectureTypesIncompatibles()
//>       class OptionBase                      
//>         OptionBase()                        
//>         operator =()                        
//>         verifier()                          
//>         lireValeur()                        
//>         ajouterOccurrence()                 
//
//$Historique
//       $Log: OptionBase.cpp,v $
//       Revision 3.19  2003/07/17 12:38:06  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 3.18  2003/02/03 13:43:04  club
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 3.17  2002/12/10 09:09:53  club
//       DM-ID 12 Modification de l'initialisation des pointeurs/variables.
//
//       Revision 3.16  2001/06/22 05:41:04  club
//       remplacement de l'inclusion de cwctype par l'inclusion de cctype
//
//       Revision 3.15  2000/10/24 14:21:01  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 3.14  2000/10/24 08:33:30  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 3.13  2000/09/07 08:03:23  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//       ajout de l'include ctype.h
//
//       Revision 3.12  2000/07/03 08:57:20  club
//       Ajout du copyright CNES
//
//       Revision 3.11.2.1  2000/03/30 14:46:48  club
//       ajout du copyright CNES
//
//       Revision 3.11  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 3.10  1999/03/17 16:44:18  club
//       normalisation des déclarations de chaînes littérales par l'utilisation
//       de const char* au lieu de char*
//
//       Revision 3.9  1998/11/17 11:55:08  club
//       élimination de l'inclusion de ctype.h
//       correction de l'oubli de l'affectation de valeursTrouvees_
//       dans l'opérateur d'affectation
//       ajout de (void) explicite pour indiquer que l'on ignore certains retours
//
//       Revision 3.8  1998/06/21 15:57:58  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//
//       Revision 3.7  1998/04/26 13:02:29  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.6  1998/01/22 08:21:53  luc
//       mise en cohérence d'une liste d'initialisation de constructeur
//       et de l'ordre des attributs dans la classe
//
//       Revision 3.5  1997/09/12 07:39:42  luc
//       élimination d'une redondance de messages d'erreurs
//
//       Revision 3.4  1997/08/21 16:44:02  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:47:28  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:04:51  luc
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 15:18:00  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:16:27  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour entière et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant générer des erreurs
//       
//       Revision 1.4  1995/07/12 15:00:06  mercator
//       elimination du nom d'arguments inutilises pour
//       - supprimer des avertissements du compilateur SUN
//       - montrer explicitement que les variables ne servent pas ici
//       (elles ne servent que dans les classes derivees)
//       
//       Revision 1.3  1994/11/09 15:01:47  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/08/30 12:54:24  mercator
//       remplacement de "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 12:05:51  luc
//       Initial revision
//
//$Version
//       $Id: OptionBase.cpp,v 3.19 2003/07/17 12:38:06 club Exp $
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
# include <cctype>
#endif

#include "club/OptionBase.h"
#include "club/ClubErreurs.h"

static void LectureTypesIncompatibles (const char* code,
                                       const char* typeArgument,
                                       int typeOption)
  throw (ClubErreurs)
{ // transformation du type de l'option en chaîne de caractères
  const char* ptr = NULL;
  switch (typeOption)
  { case OptionBase::tableau_d_entiers :
      ptr = "int";
      break;

    case OptionBase::tableau_de_reels :
      ptr = "double";
      break;

    case OptionBase::tableau_de_chaines :
      ptr = "char*";
      break;

    case OptionBase::sans_valeur :
      ptr = "void";
      break;

    default :
      ptr = "???";
      break;

  }

  throw ClubErreurs (ClubErreurs::lecture_types_incompatibles,
                     code, typeArgument, ptr);

}

OptionBase::OptionBase (const char *code,
                        int occurrencesMin, int occurrencesMax,
                        int valueeParDefaut, int type, int valeursAttendues)
  throw (ClubErreurs)
  : code_ (code),
    occurrencesMin_ (occurrencesMin), occurrencesMax_ (occurrencesMax),
    occurrences_ (0), valueeParDefaut_ (valueeParDefaut),
    type_ (type), valeursAttendues_ (valeursAttendues)
{ 

  if (valeursAttendues < 0)
    throw ClubErreurs (ClubErreurs::nombre_arguments_negatif,
                       code_.c_str (), valeursAttendues);

  if ((code_.empty ()) && (valeursAttendues != 1))
    throw ClubErreurs (ClubErreurs::nb_arguments_option_vide);

  if ((! code_.empty ()) && (! isalpha(*(code_.c_str ()))))
    throw ClubErreurs (ClubErreurs::nom_option_non_lettre,
                       code_.c_str ());

  valeursTrouvees_ = valueeParDefaut ? valeursAttendues : 0;

}

OptionBase::OptionBase (const string& code,
                        int occurrencesMin, int occurrencesMax,
                        int valueeParDefaut, int type, int valeursAttendues)
  throw (ClubErreurs)
  : code_ (code),
    occurrencesMin_ (occurrencesMin), occurrencesMax_ (occurrencesMax),
    occurrences_ (0), valueeParDefaut_ (valueeParDefaut),
    type_ (type), valeursAttendues_ (valeursAttendues)
{ 

  if (valeursAttendues < 0)
    throw ClubErreurs (ClubErreurs::nombre_arguments_negatif,
                       code_.c_str (), valeursAttendues);

  if ((code_.empty ()) && (valeursAttendues != 1))
    throw ClubErreurs (ClubErreurs::nb_arguments_option_vide);

  if ((code_.empty ()) && (! isalpha(*(code_.c_str ()))))
    throw ClubErreurs (ClubErreurs::nom_option_non_lettre,
                       code_.c_str ());

  valeursTrouvees_ = valueeParDefaut ? valeursAttendues : 0;
  
}

OptionBase& OptionBase::operator = (const OptionBase& opt)
{ if (this != &opt)  // protection contre x = x
  { code_             = opt.code_;
    occurrencesMin_   = opt.occurrencesMin_;
    occurrencesMax_   = opt.occurrencesMax_;
    valueeParDefaut_  = opt.valueeParDefaut_;
    occurrences_      = opt.occurrences_;
    type_             = opt.type_;
    valeursAttendues_ = opt.valeursAttendues_;
    valeursTrouvees_  = opt.valeursTrouvees_;
  }

  return *this;

}

int OptionBase::verifier (string *ptrMessage) const
{ if ((occurrences_ < occurrencesMin_) || (occurrences_ > occurrencesMax_))
  { ClubErreurs e (ClubErreurs::occurrence_hors_limites,
                   code_.c_str (), occurrencesMin_, occurrencesMax_,
                   occurrences_);
    *ptrMessage = e.why ();
    e.correction ();
    return ClubErreurs::occurrence_hors_limites;
  }
  else if ((occurrences_ > 0) && (valeursAttendues_ != valeursTrouvees_))
  { ClubErreurs e (ClubErreurs::nombres_arguments_incompatibles,
                   code_.c_str (), valeursTrouvees_, valeursAttendues_);
    *ptrMessage = e.why ();
    e.correction ();
    return ClubErreurs::nombres_arguments_incompatibles;
  }
  else
  { *ptrMessage = "";
    return 0;
  }
}

void  OptionBase::lireValeur (int, int [], int) const
  throw (ClubErreurs)
{ LectureTypesIncompatibles (code_.c_str (), "int", type_); }

void OptionBase::lireValeur (int, double [], int) const
  throw (ClubErreurs)
{ LectureTypesIncompatibles (code_.c_str (), "double", type_); }

void OptionBase::lireValeur (int, char* [], int) const
  throw (ClubErreurs)
{ LectureTypesIncompatibles (code_.c_str (), "char*", type_); }

void OptionBase::lireValeur (int, string [], int) const
  throw (ClubErreurs)
{ LectureTypesIncompatibles (code_.c_str (), "string", type_); }

void OptionBase::lireValeur (int* dest, int occurrence) const
  throw (ClubErreurs)
{ if (valeursAttendues_ != 1)
  throw ClubErreurs (ClubErreurs::taille_tableau_arguments,
                     code_.c_str (), valeursAttendues_);
 else
   lireValeur (1, dest, occurrence);
}

void OptionBase::lireValeur (double* dest, int occurrence) const
  throw (ClubErreurs)
{ if (valeursAttendues_ != 1)
  throw ClubErreurs(ClubErreurs::taille_tableau_arguments,
                    code_.c_str (), valeursAttendues_);
 else
   lireValeur (1, dest, occurrence);
}

void OptionBase::lireValeur (char* dest, int occurrence) const
  throw (ClubErreurs)
{ if (valeursAttendues_ != 1)
    throw ClubErreurs (ClubErreurs::taille_tableau_arguments,
                       code_.c_str (), valeursAttendues_);
 else
   lireValeur (1, &dest, occurrence);
}

void OptionBase::lireValeur (string *dest, int occurrence) const
  throw (ClubErreurs)
{ if (valeursAttendues_ != 1)
  throw ClubErreurs (ClubErreurs::taille_tableau_arguments,
                     code_.c_str (), valeursAttendues_);
 else
   lireValeur (1, dest, occurrence);
}

void OptionBase::ajouterOccurrence ()
  throw (ClubErreurs)  
{ if (occurrences_ != 0)
  { // vérification de la complétude de l'occurrence précédente
    if (valeursTrouvees_ != valeursAttendues_)
      throw ClubErreurs (ClubErreurs::nombres_arguments_incompatibles,
                         code_.c_str (), valeursTrouvees_,
                         valeursAttendues_);
  }

  // réinitialisation du compte des arguments
  valeursTrouvees_ = 0;

  occurrences_++;

  if (occurrences_ > occurrencesMax_)
    throw ClubErreurs (ClubErreurs::occurrence_hors_limites,
                       code_.c_str (),
                       occurrencesMin_, occurrencesMax_,
                       occurrences_);

}
