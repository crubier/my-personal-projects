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
//>       ClubErreurs.cpp
//
//$Resume
//       fichier d'implantation de la classe ClubErreurs
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       inline const char* trad()
//>       static void EcritMot()   
//>       class ClubErreurs        
//>         formate()              
//>         ClubErreurs()          
//>         operator =()           
//>         erreur()               
//>       class ClubAllocHandler   
//>         handler()              
//
//$Historique
//       $Log: ClubErreurs.cpp,v $
//       Revision 3.35  2005/03/03 16:18:40  chope
//       correction d'un non partage d'information lors de l'affectation
//       ce qui entraînait un affichage intempestif
//
//       Revision 3.34  2005/02/21 13:27:31  chope
//       ajout des erreurs missing_attribute, redefined_unit, incompatible_units,
//       entity_syntax_error, unknown_general_entity et unit_syntax_error (DM-ID 242)
//
//       Revision 3.33  2005/02/04 10:12:25  chope
//       ajout de l'erreur variable_environnement
//
//       Revision 3.32  2004/06/11 07:52:08  club
//       correction du format d'écriture des réels (FA-ID 33)
//
//       Revision 3.31  2003/12/05 08:16:26  club
//       DM 0031
//
//       Revision 3.30  2003/07/17 12:38:06  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 3.29  2003/02/03 09:05:59  club
//       DM-ID 17 Changement de l'extension du fichier dans le bandeau
//
//       Revision 3.28  2002/12/10 09:02:42  club
//       DM-ID 12 Modification portant sur l'initialisation des pointeurs et des variables.
//
//       Revision 3.27  2001/06/05 15:02:38  club
//       ajout des erreurs calltrace_not_activated, file_open et internal_error
//
//       Revision 3.26  2000/10/26 08:22:12  club
//       Modification des messages d'erreur de l'abstraction commune (XML, Madona,
//       fichiers structrurés)
//
//       Revision 3.25  2000/10/25 09:31:42  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 3.24  2000/10/24 14:21:00  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 3.23  2000/10/24 08:33:29  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 3.22  2000/10/18 16:59:21  club
//       modification des messages émis en cas de non installation de Xerces ou
//       Madona.
//
//       Revision 3.21  2000/10/18 09:18:07  club
//       suppression des messages d'erreur des exceptions no_parent_node,
//       invalid_index et index_already_defined.
//
//       Revision 3.20  2000/10/16 15:43:13  club
//       ajout des messages d'erreur sur les exceptions propres aux classes XMLFile,
//       StructureFile, MadonaFile, DataFile et UniqDataFile.
//
//       Revision 3.19  2000/09/07 07:59:49  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//       ajout de l'include stdio.h
//
//       Revision 3.18  2000/07/03 08:57:19  club
//       Ajout du copyright CNES
//
//       Revision 3.17.2.1  2000/03/30 14:46:46  club
//       ajout du copyright CNES
//
//       Revision 3.17  1999/08/12 09:59:58  club
//       utilisation de l'initialiseur stockeCode du code
//       d'erreur résultant de la modification de la classe
//       BaseErreurs
//
//       Revision 3.16  1999/03/15 13:18:04  club
//       ajout du message d'erreur sur un itérateur inconsistant
//       ajout du message d'erreur sur l'index d'un caractère hors limites
//
//       Revision 3.15  1998/10/05 07:01:27  club
//       inclusion de stdlib.h pour avoir le prototype de exit
//
//       Revision 3.14  1998/09/14 09:10:43  club
//       ajout de l'erreur etat_fichier
//
//       Revision 3.13  1998/07/27 10:13:42  club
//       passage à une configuration de type GNU (fichier ClubConfig.h généré)
//
//       Revision 3.12  1998/07/02 15:35:50  luc
//       correction d'une erreur de construction de message
//       (oubli de réinitialisation d'une variable statique)
//
//       Revision 3.11  1998/06/21 16:14:06  luc
//       modification du format de l'en-tête
//       élimination de la chaîne statique RCS
//
//       Revision 3.10  1998/04/26 13:10:41  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.9  1998/01/22 08:12:42  luc
//       inversion de la macro-définition sur les exceptions
//       (désormais active par défaut)
//       ajout de commentaires
//
//       Revision 3.8  1997/10/14 16:45:42  luc
//       élimination d'un #ifdef différenciant les versions Solaris et Linux
//
//       Revision 3.7  1997/09/12 07:38:45  luc
//       suppression d'erreurs inutilisées
//       amélioration d'un message sur les occurrences d'options
//
//       Revision 3.6  1997/09/07 10:47:51  luc
//       correction des blancs avant les ponctuations doubles
//       amélioration du message sur les guillemets
//
//       Revision 3.5  1997/08/21 16:44:00  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.4  1997/04/28 06:17:13  luc
//       adaptation des messages systèmes liés à errno selon la version d'Unix
//       simplification de certaines concaténations de messages
//       
//       Revision 3.3  1997/04/03 12:46:54  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:02:55  luc
//       changement du type de retour de la méthode formate
//       changement des règles de nommage
//       
//       Revision 3.1  1997/03/25 10:01:28  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la bibliothèque util_c++ en club
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/15 17:32:42  luc
//       élimination de la dépendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       
//       Revision 1.12  1996/05/13 15:55:56  luc
//       ajout de deux erreurs liées à l'inclusion de fichiers
//       
//       Revision 1.11  1995/07/12 14:56:58  mercator
//       mise en commentaire de break pour eliminer des avertissements
//       du compilateur SUN
//       
//       Revision 1.10  1995/06/26 06:39:33  mercator
//       limitation de la portee d'une variable locale dans un "switch"
//       
//       Revision 1.9  1995/04/12 12:57:42  mercator
//       modification du comportement par defaut sans gestion d'erreur: arret
//       
//       Revision 1.8  1995/01/03 07:58:41  mercator
//       remplacement des variables globales de traduction
//       par des fonctions globales
//       
//       Revision 1.7  1994/11/20 14:21:43  mercator
//       ajout des erreurs bloc_non_terminal et bloc_champ_inexistant
//       
//       Revision 1.6  1994/11/09 15:01:25  mercator
//       elimination des directives #pragma
//       
//       Revision 1.5  1994/09/29 15:56:39  mercator
//       ajout de messages d'erreurs
//       correction d'une erreur de passage d'argument variable
//       
//       Revision 1.4  1994/09/13 07:15:04  mercator
//       elimination de l'appel a RWTHROW (qui ne supporte que les classes RogueWave)
//       
//       Revision 1.3  1994/09/09 14:10:37  mercator
//       remplacement des fonctions de lancement d'exceptions
//       par des fonctions configurables par l'utilisateur
//       
//       Revision 1.2  1994/08/10 12:15:57  mercator
//       correction d'une erreur d'utilisation d'arguments variables
//       remplacement de l'argument char* apres msg_errno en char* plus arguments
//       (le char* est alors un format C qui decrit les arguments qui suivent)
//       
//       Revision 1.1  1994/07/27 14:34:36  luc
//       Initial revision
//
//$Version
//       $Id: ClubErreurs.cpp,v 3.35 2005/03/03 16:18:40 chope Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       F. Deshaies  CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
# include <cstdlib>
# include <cstdio>
# include <cerrno>
#endif

#ifdef HAVE_CSTDARG
# include <cstdarg>
#endif

#include "club/ClubErreurs.h"
#include "club/Traducteur.h"

const  int max_mot = 80;

inline const char* trad (const char* s)
{ return TraduitFormatCVersExterne (s); }

static void EcritMot (char* mot, int maxMot, const char* chaine)
{ // copie de la chaîne (complète ou avec des "..." à la fin)
  (void) strncpy (mot, chaine, maxMot - 4);
  (void) strcpy  (mot + maxMot - 4, "...");

  // élimination des mots excédentaires
  while (*mot && (!isspace(*mot)))
    mot++;
  *mot = '\0';

}

const string& ClubErreurs::formate (int code, va_list ap) const
{ char*      chaine_1 = NULL;
  char*      chaine_2 = NULL;
  char*      chaine_3 = NULL;
  int        entier_1;
  int        entier_2;
  int        entier_3;
  int        entier_4;
  double     reel_2;
  double     reel_3;
  double     reel_4;
  char       mot_1  [max_mot];
  char       mot_2  [max_mot];

  // les messages d'erreurs utilisent le domaine de traduction "club"
  InitDomaineClub ();

  // buffer de formatage du message
  static string *tampon = 0;
  if (tampon == 0)
  { // c'est la première fois que l'on passe ici
    // on alloue le tampon une fois pour toutes
    // (si le programme principal n'est pas un C++, les objets statiques
    //  ne sont pas alloués dès l'initialisation ...)
    tampon = new string;
  }

  // écriture dans un tampon de taille supposée suffisante
  char temp[4096];

  // formatage du message
  switch (code)
  { case allocation_memoire :
      return BaseErreurs::formate ("probleme d'allocation memoire", ap);

    case message_simple :
      chaine_1 = va_arg(ap, char *);
      *tampon  = trad (chaine_1);
      break;

    case etat_fichier :
      { // on encapsule ce cas entre {} pour limiter la portée
        // des variables "base", et "tmp"
        string base (BaseErreurs::formate ("probleme d'obtention de"
                                           " l'etat du fichier \"%s\"", ap));

        ClubErreurs tmp (msg_errno, base.c_str ());
        *tampon = tmp.why ();
        tmp.correction ();

      }
      break;

    case ouverture_fichier :
      { // on encapsule ce cas entre {} pour limiter la portée
        // des variables "base", et "tmp"
        string base (BaseErreurs::formate ("probleme d'ouverture du"
                                           " fichier \"%s\"", ap));

        ClubErreurs tmp (msg_errno, base.c_str ());
        *tampon = tmp.why ();
        tmp.correction ();

      }
      break;

    case lecture_types_incompatibles :
      return BaseErreurs::formate ("types incompatibles a la lecture de"
                                   " l'option -%s : %s/%s", ap);

    case taille_tableau_arguments :
      return BaseErreurs::formate ("arguments de l'option -%s accessibles"
                                   " uniquement par tableau de taille %d",
                                   ap);

    case nombres_arguments_incompatibles :
      return BaseErreurs::formate ("nombre d'arguments de l'option -%s"
                                   " incompatibles : %d trouves, %d attendus",
                                   ap);

    case nombre_arguments_negatif :
      return BaseErreurs::formate ("nombre d'arguments de l'option -%s"
                                   " negatif : %d", ap);

    case nb_arguments_option_vide :
      return BaseErreurs::formate ("l'option sans nom doit avoir un argument"
                                   " et un seul", ap);

    case nom_option_non_lettre :
      return BaseErreurs::formate ("nom d'option illegal (ne commence pas"
                                   " par une lettre) : -%s", ap);

    case nombre_arguments_nul :
      return BaseErreurs::formate ("pas d'argument pour l'option -%s", ap);

    case valeur_par_defaut_manquante :
      return BaseErreurs::formate ("valeur par defaut manquante pour"
                                   " l'option -%s", ap);

    case option_chaine_trop_longue :
      return BaseErreurs::formate ("argument de l'option -%s trop long :"
                                   " \"%s\" (%d caracteres max)", ap);

    case option_chaine_hors_domaine :
      { // on encapsule ce cas entre {} pour limiter la portée
        // des variables tabChaines et i

        chaine_1          = va_arg(ap, char *);
        chaine_2          = va_arg(ap, char *);
        entier_1          = va_arg(ap, int);
        string *tabChaines = va_arg(ap, string *);

        (void) sprintf (temp, trad ("argument hors domaine pour l'option -%s :"
                                    " \"%s\", arguments autorises :"),
                        chaine_1, chaine_2);
        *tampon = temp;

        for (int i = 0; i < entier_1; i++)
        { (*tampon) += "\n\"";
          (*tampon) += tabChaines [i];
          (*tampon) += "\"";
        }
      }
      break;

    case option_entiere_hors_limites :
      chaine_1 = va_arg(ap, char *);
      entier_2 = va_arg(ap, int);
      entier_3 = va_arg(ap, int);
      entier_4 = va_arg(ap, int);
      if (entier_2 <= -1000000000)
        (void) sprintf (temp, trad ("option -%s hors limites ]-infini ; %d] : %d"),
                        chaine_1, entier_3, entier_4);
      else if (entier_3 >= 1000000000)
        (void) sprintf (temp, trad ("option -%s hors limites [%d ; +infini[ : %d"),
                        chaine_1, entier_2, entier_4);
      else
        (void) sprintf (temp, trad ("option -%s hors limites [%d ; %d] : %d"),
                        chaine_1, entier_2, entier_3, entier_4);

      *tampon = temp;
      break;

    case option_reelle_hors_limites :
      chaine_1 = va_arg(ap, char *);
      reel_2   = va_arg(ap, double);
      reel_3   = va_arg(ap, double);
      reel_4   = va_arg(ap, double);
      if (reel_2 <= -1.0e30)
        (void) sprintf (temp, trad ("option -%s hors limites ]-infini ; %f] : %f"),
                        chaine_1, reel_3, reel_4);
      else if (reel_3 >= 1.0e30)
        (void) sprintf (temp, trad ("option -%s hors limites [%f ; +infini[ : %f"),
                        chaine_1, reel_2, reel_4);
      else
        (void) sprintf (temp, trad ("option -%s hors limites [%f ; %f] : %f"),
                        chaine_1, reel_2, reel_3, reel_4);

      *tampon = temp;
      break;

    case code_option_non_reconnu :
      return BaseErreurs::formate ("code d'option \"%s\" non reconnu", ap);

    case plus_d_argument :
      return BaseErreurs::formate ("argument manquant pour l'option -%s", ap);

    case option_deja_definie :
      return BaseErreurs::formate ("option -%s definie deux fois", ap);

    case options_appli_deja_initialise :
      return BaseErreurs::formate ("analyseur d'options de %s deja initialise",
                                   ap);

    case options_appli_non_initialise :
      return BaseErreurs::formate ("analyseur d'options de %s non initialise",
                                   ap);

    case arguments_non_reconnus :
      return BaseErreurs::formate ("arguments non reconnus par l'analyseur"
                                   " d'options de %s :", ap);

    case occurrence_inexistante :
      return BaseErreurs::formate ("occurrence %d de l'option -%s inexistante"
                                   " (%d occurrences passees)", ap);

    case occurrence_hors_limites :
      chaine_1 = va_arg(ap, char *);
      entier_2 = va_arg(ap, int);
      entier_3 = va_arg(ap, int);
      entier_4 = va_arg(ap, int);
      if (entier_2 == entier_3)
        (void) sprintf (temp, trad ("option -%s absente"), chaine_1);
      else
        (void) sprintf (temp, trad ("nombre d'occurrences de l'option -%s"
                                    " hors limites [%d ; %d] : %d"),
                        chaine_1, entier_2, entier_3, entier_4);
      
      *tampon = temp;
      break;

    case tampon_vide :
      return BaseErreurs::formate ("tampon \"%s\" vide", ap);

    case manque_guillemet :
      return BaseErreurs::formate ("caractere \" ou caractere \' manquant"
                                   " dans le tampon \"%s\"", ap);

    case ligne_hors_domaine :
      return BaseErreurs::formate ("ligne %d hors limites [%d ; %d],"
                                   " tampon \"%s\"", ap);

    case champ_ligne_hors_domaine :
      return BaseErreurs::formate ("champ %d hors limites [%d ; %d],"
                                   " ligne %d du tampon \"%s\"", ap);

   case champ_hors_domaine :
      return BaseErreurs::formate ("champ %d hors limites [%d ; %d],"
                                   " tampon \"%s\"", ap);

    case accolades_non_equilibrees :
      return BaseErreurs::formate ("accolades non equilibrees dans le"
                                   " fichier \"%s\"", ap);

    case bloc_introuvable :
      chaine_1 = va_arg(ap, char*);
      chaine_2 = va_arg(ap, char*);
      chaine_3 = va_arg(ap, char*);

      EcritMot (mot_1, max_mot, chaine_1);

      if (*chaine_2 != '\0')
      { EcritMot (mot_2, max_mot, chaine_2);
        (void) sprintf (temp, trad ("sous-bloc \"%s\" introuvable dans le"
                                    " bloc \"%s\" du fichier \"%s\""),
                        mot_1, mot_2, chaine_3);
      }
      else
      { (void) sprintf (temp, trad ("bloc \"%s\" introuvable dans le"
                                    " fichier \"%s\""), mot_1, chaine_3);
      }

      *tampon = temp;
      break;

    case bloc_champ_inexistant :
      entier_1 = va_arg(ap, int);
      chaine_2 = va_arg(ap, char*);
      chaine_3 = va_arg(ap, char*);

      EcritMot (mot_2, max_mot, chaine_2);

      (void) sprintf (temp, trad ("pas de champ %d dans le bloc \"%s\""
                                  " du fichier \"%s\""),
                      entier_1, mot_2, chaine_3);
      *tampon = temp;
      break;

    case bloc_non_terminal :
      chaine_1 = va_arg(ap, char*);
      chaine_2 = va_arg(ap, char*);

      EcritMot (mot_1, max_mot, chaine_1);

      (void) sprintf (temp, trad ("bloc \"%s\" non terminal dans"
                                  " le fichier \"%s\""), 
                      mot_1, chaine_2);
      *tampon = temp;
      break;

    case manque_accolade :
      chaine_1 = va_arg(ap, char*);
      chaine_2 = va_arg(ap, char*);

      EcritMot (mot_1, max_mot, chaine_1);

      (void) sprintf (temp, trad ("'{' manquante (bloc \"%s\" du fichier \"%s\")"),
                      mot_1, chaine_2);
      *tampon = temp;
      break;

    case manque_chevron :
      chaine_1 = va_arg(ap, char*);
      chaine_2 = va_arg(ap, char*);

      EcritMot (mot_1, max_mot, chaine_1);
      EcritMot (mot_2, max_mot, chaine_2);

      (void) sprintf (temp, trad ("'>' manquant apres \"%s\" (fichier \"%s\")"),
                      mot_1, mot_2);
      *tampon = temp;
      break;

    case nom_inclusion :
      chaine_1 = va_arg(ap, char*);

      EcritMot (mot_1, max_mot, chaine_1);

      (void) sprintf (temp, trad ("nom de fichier a inclure manquant"
                                  " (fichier \"%s\")"), mot_1);
      *tampon = temp;
      break;

    case msg_errno :
      { // on encapsule ce cas entre {} pour limiter la portée
        // de la variable msg

        chaine_1 = va_arg(ap, char*);
        *tampon  = chaine_1;
        *tampon += ": ";
        string msg;
#ifdef HAVE_STRERROR
        msg = strerror (errno);
#else
        (void) sprintf (temp, "errno = %d", errno);
        msg = temp;
#endif
        *tampon += msg;
      }
      break;

    case format_fortran :
      return BaseErreurs::formate ("erreur d'analyse du format fortran \"%s\"",
                                   ap);

    case trace :
      return BaseErreurs::formate ("passage par la ligne %d du fichier \"%s\"",
                                   ap);
 
    case iterateur_invalide :      
      return BaseErreurs::formate ("iterateur inconsistant pour le tampon \"%s\"", ap);

    case caractere_hors_domaine :
      return BaseErreurs::formate ("caractere %d hors limites [%d ; %d],"
                                   " tampon \"%s\"", ap);

    case variable_environnement :
      return BaseErreurs::formate ("variable d'environnement \"%s\" manquante",
                                   ap);

    case calltrace_not_activated :
      return BaseErreurs::formate ("trace des executions desactivee", ap);

    case internal_error :
      return BaseErreurs::formate ("erreur interne de CLUB,"
                                   " veuillez contacter la maintenance"
                                   " (ligne %d, fichier %s)", ap);

    case not_implemented :
      return BaseErreurs::formate("fonction \"%s\" non implementee", ap);

    case name_error :
      return BaseErreurs::formate("designation \"%s\" non valide", ap);

    case string_to_int_conversion_error:
      return BaseErreurs::formate ("impossible de convertir \"%s\" en entier",
                                   ap);

    case string_to_double_conversion_error:
      return BaseErreurs::formate ("impossible de convertir \"%s\" en reel",
                                   ap);

    case file_error:
      return BaseErreurs::formate ("erreur fichier \"%s\": \"%s\"", ap);

    case malformed_data:
      return BaseErreurs::formate ("structure de donnees non valide : %s", ap);

    case missing_tag:
      return BaseErreurs::formate ("le tag %s manque", ap);
   
    case missing_attribute:
      return BaseErreurs::formate ("attribut %s manquant dans l'element %s", ap);
   
    case xpointer_syntax_error:
      return BaseErreurs::formate ("reference xpointer \"%s\" incorrecte", ap);

    case redefined_unit:
      return BaseErreurs::formate ("redefinition de l'unite %s", ap);

    case incompatible_units:
      return BaseErreurs::formate ("impossible d'effectuer une conversion"
                                   " entre les unites incompatibles %s et %s",
                                   ap);

    case entity_syntax_error:
      return BaseErreurs::formate ("erreur de syntaxe d'appel a une entite"
                                   " dans la chaine \"%s\"",
                                   ap);

    case unknown_general_entity:
      return BaseErreurs::formate ("entite generale %s inconnue"
                                   " dans la chaine \"%s\"",
                                   ap);

    case unit_syntax_error:
      return BaseErreurs::formate ("erreur de syntaxe dans l'unite %s",
                                   ap);

    case undefined_data :
       return BaseErreurs::formate ("donnee \"%s\" non definie", ap);
     
    case undefined_table_or_structure :
      return BaseErreurs::formate ("structure ou table \"%s\" non definie",
                                   ap);

    case undefined_parameter :
      return BaseErreurs::formate ("parametre \"%s\" non defini", ap);
     
    case undefined_index :
      return BaseErreurs::formate ("index %d de la table \"%s\" non defini",
                                   ap);

    case undefined_unit:
      return BaseErreurs::formate ("unite \"%s\" non reconnue", ap);

    case undefined_node_type:
      return BaseErreurs::formate ("noeud %s de type inconnu", ap);

    case current_data_not_a_table:
      return BaseErreurs::formate ("donnee courante \"%s\" n'est pas un "
                                   "tableau", ap);

    case current_data_is_a_table:
      return BaseErreurs::formate ("donnee courante \"%s\" est un "
                                   "tableau", ap);

    case move_up_forbidden :
      return BaseErreurs::formate ("impossible de remonter d'un niveau depuis "
                                   "la racine du document", ap);

    case madona_error :
      return BaseErreurs::formate ("erreur Madona : \"%s\"", ap);

    case xml_error :
      return BaseErreurs::formate ("erreur XML : \"%s\"", ap);
      
    case invalid_element_type :
      return BaseErreurs::formate ("table \"%s\" de type \"%s\" ne peut "
                                   "contenir des elements de type \"%s\"", ap);

    case no_madona_lib :
      return BaseErreurs::formate ("fonction non accessible : "
                                   "Madona n'est pas installee", 
                                   ap);

    case no_xerces_lib :
      return BaseErreurs::formate ("fonction non accessible : "
                                   "Xerces n'est pas installee", 
                                   ap);

    case index_creation_forbidden:
      return BaseErreurs::formate ("creation de l'index dans %s interdite", ap);

    case data_already_defined :
      return BaseErreurs::formate("donnee \"%s\" deja definie", ap);
     
    case unknown_file_type :
      return BaseErreurs::formate("le format du fichier est invalide", ap);
     
    default :
      return BaseErreurs::formate (code, ap);

  }

  // retour du message formaté
  return *tampon;

}

ClubErreurs::ClubErreurs (int code ...)
  : BaseErreurs ()
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, code);

  // sauvegarde du code d'erreur dans la partie privée de la classe
  stockeCode (code);

  // formatage et stockage du message
  stockeMessage (formate (code, ap));

  // fin de récupération des arguments d'appel
  va_end(ap);

}

ClubErreurs::ClubErreurs (const char* format ...)
  : BaseErreurs ()
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, format);

  // sauvegarde du code d'erreur dans la partie privée de la classe
  stockeCode (CodeInconnu);

  // formatage et stockage du message
  stockeMessage (BaseErreurs::formate (format, ap));

  // fin de récupération des arguments d'appel
  va_end(ap);

}

ClubErreurs& ClubErreurs::operator = (const ClubErreurs& e)
{ if (this != &e)     // protection contre x = x
  {
    BaseErreurs::operator = (e);
  }

  return *this;

}

int ClubErreurs::erreur (ClubErreurs* ptr, int code ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, code);

  // gestion de l'erreur sans argument variable
  if (ptr != 0)
  { // l'appelant a donné une instance d'erreur à remplir
    ptr->stockeCode (code);
    ptr->stockeMessage (ptr->formate (code, ap));
  }
  else
  { // l'appelant n'a pas donné d'instance, il faut la créer
    ClubErreurs err;
    err.stockeCode (code);
    err.stockeMessage (err.formate (code, ap));

    if (BaseErreurs::exceptions ())
#ifdef HAVE_EXCEPTIONS
      throw err;
#else
    { // l'utilisateur veut des exceptions, mais le code est compilé sans
      err.affiche    ();
      err.correction ();
      exit (1);
    }
#endif
    else
    { err.affiche    ();
      err.correction ();
      exit (1);
    }

   }

  // fin de récupération des arguments d'appel
  va_end(ap);

  // retour avec un code d'erreur à la fonction appelante
  return code;

}

int ClubErreurs::erreur (ClubErreurs* ptr, const char* format ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, format);

  // gestion de l'erreur sans argument variable
  if (ptr != 0)
  { // l'appelant a donné une instance d'erreur à remplir
    ptr->stockeCode (CodeInconnu);
    ptr->stockeMessage (ptr->BaseErreurs::formate (format, ap));
  }
  else
  { // l'appelant n'a pas donné d'instance, il faut la créer
    ClubErreurs err;
    err.stockeCode (CodeInconnu);
    err.stockeMessage (err.BaseErreurs::formate (format, ap));

    if (BaseErreurs::exceptions ())
#ifdef HAVE_EXCEPTIONS
      throw err;
#else
    { // l'utilisateur veut des exceptions, mais le code est compilé sans
      err.affiche    ();
      err.correction ();
      exit (1);
    }
#endif
    else
    { err.affiche    ();
      err.correction ();
      exit (1);
    }

  }

  // fin de récupération des arguments d'appel
  va_end(ap);

  // retour avec un code d'erreur à la fonction appelante
  return CodeInconnu;


}

void ClubAllocHandler::handler ()
{ (void) ClubErreurs::erreur (0, ClubErreurs::allocation_memoire); }
