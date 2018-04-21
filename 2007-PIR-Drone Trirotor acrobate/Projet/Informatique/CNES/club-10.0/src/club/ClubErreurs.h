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
//>       ClubErreurs.h
//
//$Resume
//       fichier d'en-tête de la classe ClubErreurs
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class ClubErreurs     
//>       class ClubAllocHandler
//
//$Historique
//       $Log: ClubErreurs.h,v $
//       Revision 3.22  2005/02/21 13:16:40  chope
//       ajout des erreurs missing_attribute, redefined_unit, incompatible_units,
//       entity_syntax_error, unknown_general_entity et unit_syntax_error (DM-ID 242)
//
//       Revision 3.21  2005/02/04 10:00:09  chope
//       ajout de l'erreur variable_environnement (DM-ID 242)
//
//       Revision 3.20  2003/12/05 08:16:38  club
//       DM 0031
//
//       Revision 3.19  2002/12/09 15:53:09  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 3.18  2002/11/29 15:08:34  club
//       DM-ID 12 Correction de l'ordre des déclarations (public, protected, private)
//
//       Revision 3.17  2001/06/05 14:59:53  club
//       ajout des erreurs calltrace_not_activated, file_open et internal_error
//
//       Revision 3.16  2000/12/04 17:02:32  club
//       correction d'une faute de frappe
//
//       Revision 3.15  2000/10/17 14:08:46  club
//       suppression de l'exception no_parent_node
//
//       Revision 3.14  2000/10/16 15:35:36  club
//       ajout des exceptions liées aux fichiers XMLFile, MadonaFile, StructureFile,
//       UniqDataFile et DataFile
//
//       Revision 3.13  2000/09/07 07:39:24  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.12  2000/07/03 08:54:19  club
//       Ajout du copyright CNES
//
//       Revision 3.11.2.1  2000/03/30 14:46:54  club
//       ajout du copyright CNES
//
//       Revision 3.11  1999/03/15 15:03:07  club
//       ajout du message d'erreur sur un itérateur inconsistant
//       ajout du message d'erreur sur l'index d'un caractère hors limites
//
//       Revision 3.10  1998/09/14 09:09:09  club
//       ajout de l'erreur etat_fichier
//
//       Revision 3.9  1998/06/25 06:40:44  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 3.8  1998/01/22 08:27:54  luc
//       amélioration des en-têtes de classe
//       ajout d'accents dans des commentaires
//
//       Revision 3.7  1997/12/15 07:39:50  luc
//       renommage de la macro-définition TRACE en CLUB_TRACE
//
//       Revision 3.6  1997/09/12 07:37:52  luc
//       suppression de codes d'erreur inutilisés
//
//       Revision 3.5  1997/08/27 20:59:48  luc
//       ajout d'une erreur pour l'analyse syntaxique des formats fortran
//
//       Revision 3.4  1997/08/21 16:34:11  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/03 12:50:30  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:02:37  luc
//       changement du type de retour de la méthode formate
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/19 14:41:59  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:33:31  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       
//       Revision 1.6  1996/05/13 15:56:13  luc
//       ajout de deux erreurs liées à l'inclusion de fichiers
//       
//       Revision 1.5  1994/11/26 15:25:36  mercator
//       ajout des erreurs bloc_non_terminal et bloc_champ_inexistant
//       modification du nom de la variable statique d'identification SCCS
//       
//       Revision 1.4  1994/11/09 14:59:39  mercator
//       elimination des directives #pragma
//       
//       Revision 1.3  1994/09/29 15:56:42  mercator
//       ajout de messages d'erreurs
//       correction d'une erreur de passage d'argument variable
//       
//       Revision 1.2  1994/09/02 12:48:20  mercator
//       remplacement des fonctions de lancement d'exceptions
//       par des fonctions configurables par l'utilisateur
//       
//       Revision 1.1  1994/07/29 14:37:17  luc
//       Initial revision
//
//$Version
//       $Id: ClubErreurs.h,v 3.22 2005/02/21 13:16:40 chope Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       M. Julien    CSSI
//       F. Deshaies  CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_ClubErreurs_h
#define __club_ClubErreurs_h

#include "club/BaseErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ClubErreurs
//
//$Resume
//       classe de gestion des erreurs de la bibliothèque CLUB
//
//$Description
//       cette classe gère toutes les erreurs de la bibliothèque CLUB,
//       elle dérive de BaseErreurs
//
//$Usage
//>     construction : 
//         à partir du code d'erreur et des arguments associés, par copie
//>     utilisation  : 
//>       ClubErreurs& operator =     () 
//          affectation
//>       static int erreur           () 
//          crée une erreur dans l'instance fournie en argument si
//          elle existe (pointeur non nul) ou dans un objet local
//>       virtual const char* domaine () 
//          retourne le domaine "club"
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ClubErreurs : public BaseErreurs
{ 
  public :

  // liste des codes d'erreurs
  enum { allocation_memoire = 1,
         message_simple,
         etat_fichier,
         ouverture_fichier,
         lecture_types_incompatibles,
         taille_tableau_arguments,
         nombres_arguments_incompatibles,
         nombre_arguments_negatif,
         nb_arguments_option_vide,
         nom_option_non_lettre,
         nombre_arguments_nul,
         valeur_par_defaut_manquante,
         option_chaine_trop_longue,
         option_chaine_hors_domaine,
         option_entiere_hors_limites,
         option_reelle_hors_limites,
         code_option_non_reconnu,
         plus_d_argument,
         option_deja_definie,
         options_appli_deja_initialise,
         options_appli_non_initialise,
         arguments_non_reconnus,
         occurrence_inexistante,
         occurrence_hors_limites,
         tampon_vide,
         manque_guillemet,
         ligne_hors_domaine,
         champ_ligne_hors_domaine,
         champ_hors_domaine,
         accolades_non_equilibrees,
         bloc_introuvable,
         bloc_champ_inexistant,
         bloc_non_terminal,
         manque_accolade,
         manque_chevron,
         nom_inclusion,
         msg_errno,
         format_fortran,
         trace,
         iterateur_invalide,
         caractere_hors_domaine,
         variable_environnement,

         calltrace_not_activated,
         internal_error,

         not_implemented,
         name_error,
         string_to_int_conversion_error,
         string_to_double_conversion_error,
         file_error,
         malformed_data,
         missing_tag,
         missing_attribute,
         xpointer_syntax_error,
         redefined_unit,
         incompatible_units,
         entity_syntax_error,
         unknown_general_entity,
         unit_syntax_error,
         
         undefined_data,
         undefined_table_or_structure,
         undefined_parameter,
         undefined_index,
         undefined_unit,
         undefined_node_type,

         current_data_not_a_table,
         current_data_is_a_table,
         move_up_forbidden,

         madona_error,
         xml_error,
         invalid_element_type,
         no_madona_lib,
         no_xerces_lib,
         
         index_creation_forbidden,
         data_already_defined,
         unknown_file_type
       };

  // constructeurs
  ClubErreurs     () : BaseErreurs () {}
  ClubErreurs     (int code ...);
  ClubErreurs     (const char* format ...);
  ClubErreurs     (const ClubErreurs& e) : BaseErreurs (e) {}

  // destructeur
  virtual ~ClubErreurs () {}

  // affectation
  ClubErreurs& operator =        (const ClubErreurs& e);

  // fonctions d'acces aux elements canoniques
  virtual const char* domaine    () const { return "club"; }

  // declenchement general d'une erreur
  static int erreur (ClubErreurs* ptr, int code ...);
  static int erreur (ClubErreurs* ptr, const char* format ...);

  protected :
  virtual const string& formate (int code, va_list ap) const;
};


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ClubAllocHandler
//
//$Resume
//       classe de gestion des erreurs d'allocation mémoire
//
//$Description
//       cette classe permet de récupérer les erreurs d'allocation
//       mémoire sous forme de ClubErreurs, à l'aide de
//       "set_new_handler"
//
//$Usage
//>     construction : 
//         sans argument, met en place le handler générant une
//         exception de type ClubErreurs
//>     utilisation  : 
//         uniquement par les effets de bord des constructeur et
//         destructeur
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ClubAllocHandler
{
  public :
    ClubAllocHandler () { _ancien = set_new_handler (&handler); }
   ~ClubAllocHandler () { (void)    set_new_handler (_ancien);  }

  protected :

  // AUTRES CONSTRUCTEURS
  // constructeur par copie
  ClubAllocHandler (const ClubAllocHandler & other)
  {
    _ancien = other._ancien;
  }
  //constructeur par affectation
  ClubAllocHandler &  ClubAllocHandler::operator = (const ClubAllocHandler & other)
  {
    if (this != &other)
      _ancien = other._ancien;
    return *this;
  }

  void      (*_ancien) ();
  static void handler ();  // déclaré static pour être de type: "void (*) ()"
};


#endif
