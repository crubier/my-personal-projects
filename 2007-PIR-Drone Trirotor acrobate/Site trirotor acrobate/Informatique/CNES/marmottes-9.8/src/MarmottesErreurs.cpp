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
//       Marmottes
//
//$Nom
//>       MarmottesErreurs.cpp
//
//$Resume
//       fichier d'implantation de la classe MarmottesErreurs
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       inline const char* trad()  
//>       void InitDomaineMarmottes()
//>       class MarmottesErreurs     
//>         formate()                
//>         MarmottesErreurs()       
//>         operator =()             
//>         erreur()                 
//
//$Historique
//       $Log: MarmottesErreurs.cpp,v $
//       Revision 2.41  2005/03/04 13:45:32  chope
//       correction d'un partage de données erroné entrainant un affichage intempestif
//
//       Revision 2.40  2003/10/08 09:39:41  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 2.39  2003/07/17 12:41:20  marmottes
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 2.38  2003/02/27 16:40:43  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 2.37  2003/02/04 16:29:51  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 2.36  2002/12/11 17:29:31  marmottes
//       DM-ID 12 Ajout de l'initialisation de pointeur.
//
//       Revision 2.35  2002/02/27 14:09:09  marmottes
//       suppression de la description de la révision insérée manuellement
//       et mise à jour du copyright CNES
//
//       Revision 2.34  2002/02/22 09:32:37  marmottes
//       Ajout d'un message d'erreur (DM0002)
//
//       Revision 2.33  2002/02/04 15:31:54  marmottes
//       ajout des messages champ_inhibition_cible_soleil et champ_inhibition_cible_lune
//
//       Revision 2.32  2002/01/17 09:23:13  marmottes
//       (formate): ajout de l'erreur consignes_gyro_elevees (FA 0001)
//
//       Revision 2.31  2001/07/19 08:48:48  luc
//       élimination d'une variable inutilisée
//
//       Revision 2.30  2001/07/17 15:29:13  luc
//       ajout de l'erreur pas_de_point_sol
//
//       Revision 2.29  2001/06/06 08:02:50  luc
//       élimination des erreurs echec_heuristique, ouverture_fichier,
//       trace_inactif et frontiere_ouverte
//
//       Revision 2.28  2000/11/16 18:20:44  luc
//       ajout des erreurs points_echantillon, echantillon_vide et echantillon_rejete
//
//       Revision 2.27  2000/11/13 10:06:29  luc
//       remplacement de l'erreur point_triple par l'erreur echec_heuristique
//       ajout de l'erreur frontiere_ouverte
//       changement des fichiers d'inclusion
//
//       Revision 2.26  2000/10/02 13:17:50  luc
//       remplacement du terme gyroscope par gyromètre
//
//       Revision 2.25  2000/09/13 09:46:35  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 2.24  2000/09/05 13:24:03  luc
//       ajout des erreurs ouverture_fichier, allocation_memoire,
//       trace_inactif, objet_inconnu
//
//       Revision 2.23  2000/06/07 14:07:01  luc
//       ajout de l'erreur senseur_mesure_pure
//
//       Revision 2.22  2000/04/17 06:49:19  luc
//       correction d'un message d'erreur
//
//       Revision 2.21  2000/03/30 17:01:19  luc
//       ajout du copyright CNES
//
//       Revision 2.20  2000/01/07 12:29:23  luc
//       élimination de la traduction inutile des noms de senseurs dans les
//       messages d'erreur
//
//       Revision 2.19  1999/08/20 07:33:01  filaire
//       Création de nouvelles erreurs
//
//       Revision 2.18  1999/04/23 11:40:10  luc
//       ajout de erreur_non_reconnue
//
//       Revision 2.17  1998/10/05 15:14:11  luc
//       inclusion de stdlib.h pour avoir le prototype de exit
//
//       Revision 2.16  1998/09/14 11:47:26  luc
//       ajout de l'erreur consigne_degeneree
//
//       Revision 2.15  1998/08/13 12:32:12  luc
//       ajout des listes des mots-clefs reconnus dans les erreurs
//       genre_cardan_inconnu et reference_cardan_inconnue
//       reformultation des messages des erreurs
//       reference_utilisateur, modifie_reference, senseur_sans_reference
//
//       Revision 2.14  1998/07/22 06:32:06  luc
//       ajout d'une erreur pour les consignes incompatibles
//
//       Revision 2.13  1998/07/15 12:43:26  luc
//       remplacement de l'erreur cardan_inconnu par genre_cardan_inconnu
//       ajout des erreurs : reference_cardan_inconnue, cible_utilisateur,
//       modifie_cible, senseur_sans_cible, pas_gyro_integrateur,
//       reference_utilisateur, modifie_reference, senseur_sans_reference
//       et cas_impossible
//
//       Revision 2.12  1998/06/24 19:57:34  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 2.11  1998/05/14 12:02:01  luc
//       suppression d'erreurs inutilisées (depuis longtemps)
//
//       Revision 2.10  1998/04/26 20:15:52  luc
//       inversion de la convention de nommage des attributs
//       déplacement de Champ et Secteurs vers la bibliothèque marmottes
//
//       Revision 2.9  1998/04/26 18:19:53  luc
//       ajout des messages liés à la gestion d'unités de position et vitesse
//       reformatage de cerains messages
//
//       Revision 2.8  1998/02/04 09:21:42  luc
//       élimination de variables inutilisées
//
//       Revision 2.7  1997/11/27 06:52:36  luc
//       ajout d'un message pour les masques d'antennes des stations sol
//
//       Revision 2.6  1997/09/21 11:07:59  luc
//       ajout d'une erreur pour les variations d'angles de Cardan
//
//       Revision 2.5  1997/09/10 07:02:37  luc
//       traduction de la cible lue et non reconnue dans le message
//
//       Revision 2.4  1997/08/20 08:14:23  luc
//       ajout d'une erreur plus explicite lorsqu'on sait déterminer
//       le senseur qui empêche une résolution d'attitude d'aboutir
//       ajout d'une erreur sur les limitations des senseurs tangage et lacet
//
//       Revision 2.3  1997/04/27 19:35:31  luc
//       inversion des codes de retour
//       correction d'erreurs de passage d'arguments variables
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 2.2  1996/09/11 17:31:43  luc
//       ajout des erreurs "id_marmottes_non_initialise" et "types_incompatibles"
//       élimination de l'erreur "solutions_multiples" (inutilisée depuis longtemps)
//       
//       Revision 2.1  1996/07/31 16:47:21  luc
//       abandon des tools.h++ (Rogue Wave)
//       destruction et création de plusieurs erreurs pour le passage en version 2
//       prise en compte du renommage de erreurs.h en marmottes_erreurs.h
//       
//       Revision 1.4  1996/03/21 17:30:35  luc
//       ajout du senseur STD15
//       
//       Revision 1.3  1995/04/12 13:00:42  mercator
//       modification du comportement par defaut en l'absence de gestion d'erreur: arret
//       correction d'une erreur de classe de declaration (oubli d'un static)
//       
//       Revision 1.2  1995/01/26 15:23:03  mercator
//       ajout d'une verification sur l'ecart de date avec l'etat precedent
//       
//       Revision 1.1  1995/01/04 07:00:28  luc
//       Initial revision
//
//$Version
//       $Id: MarmottesErreurs.cpp,v 2.41 2005/03/04 13:45:32 chope Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "MarmottesConfigNoInstall.h"
#if HAVE_CSTDLIB
# include <cstdlib>
#endif

#include "club/Traducteur.h"

#include "cantor/Util.h"

#include "marmottes/MarmottesErreurs.h"

inline const char* trad (const char* s)
{ return TraduitFormatCVersExterne (s); }

void InitDomaineMarmottes ()
{ // initialisation des domaines de traduction pour la librairie marmottes
  static int dejaInitialise = 0;

  if (!dejaInitialise)
  { // le mécanisme de traduction n'est qu'un "plus" qui peut travailler
    // sans le fichier de ressource (les messages sont alors ceux du code),
    // on ignore donc ici l'erreur d'accès au domaine de traduction
    MarmottesErreurs e;
    (void) AjouterDomaine (e.domaine ());
    e.correction ();

    dejaInitialise = 1;

  }

}

static void appliqueFormat (const string& format, string *ptrDst ...)
{
  va_list ap;
  va_start(ap, ptrDst);
  FormatC f (format);
  ap = f.applique (ap, ptrDst);
  va_end(ap);
}

const string& MarmottesErreurs::formate (int code, va_list ap) const
{ char*      chaine_1 = NULL;
  char*      chaine_2 = NULL;
  double     reel_1;

  // les messages d'erreurs utilisent le domaine de traduction "marmottes"
  InitDomaineMarmottes ();

  // buffer de formatage du message
  static string *tampon = 0;
  if (tampon == 0)
  { // c'est la première fois que l'on passe ici
    // on alloue le tampon une fois pour toutes
    // (si le programme principal n'est pas un C++, les objets statiques
    //  ne sont pas alloués dès l'initialisation ...)
    tampon = new string;
  }

  // formatage du message
  switch (code)
  { case id_marmottes_non_initialise :
      return BaseErreurs::formate ("identificateur marmottes non initialise"
                                   " : %d",
                                   ap);
      break;

    case bloc_non_terminal :
      return BaseErreurs::formate ("bloc \"%s\" non terminal", ap);
      break;

    case rotation_bloc :
      return BaseErreurs::formate ("axe de rotation nul"
                                   " dans le bloc \"%s\" ", ap);
      break;

    case nombre_champs_bloc :
      return BaseErreurs::formate ("le bloc \"%s\" a %d champs (%d demandes)",
                                   ap);
      break;

    case bloc_introuvable :
      return BaseErreurs::formate ("%s", ap);
      break;

    case vecteur_nul :
      return BaseErreurs::formate ("norme du vecteur \"%s\" trop petite",
                                   ap);
      break;

    case quaternion_nul :
      return BaseErreurs::formate ("norme du quaternion \"%s\" trop petite",
                                   ap);
      break;

    case liste_non_initialisee :
      return BaseErreurs::formate ("liste des senseurs de controle non"
                                   " initialisee",
                                   ap);
      break;

    case gyros_coaxiaux :
      return BaseErreurs::formate ("gyrometres coaxiaux", ap);
      break;

    case consignes_gyro_elevees :
      return BaseErreurs::formate ("consignes des senseurs \"%s\" et \"%s\""
                                   " incompatibles avec un omega maximal"
                                   " limite a %f degres par seconde", ap);
      break;

    case consigne_degeneree :
      return BaseErreurs::formate ("consigne du senseur \"%s\" degeneree",
                                   ap);
      break;

    case consignes_incompatibles :
      return BaseErreurs::formate ("consignes des senseurs \"%s\""
                                   " et \"%s\" incompatibles", ap);
      break;

    case type_inconnu :
      chaine_1 = va_arg(ap, char *);
      appliqueFormat (trad ("type d'un senseur inconnu : \"%s\"\ntypes connus :"),
                      tampon, chaine_1);
      do
      {
        chaine_1 = va_arg(ap, char *);

        if (chaine_1 != 0)
        {
          *tampon += " \"";
          *tampon += TraduitVersExterne (chaine_1);
          *tampon += "\"";
        }

      } while (chaine_1 != 0);
      break;

    case cible_inconnue :
      chaine_1 = va_arg(ap, char *);
      appliqueFormat (trad ("cible d'un senseur inconnue : \"%s\"\n"
                             "cibles connues :"),
                      tampon,
                      TraduitVersExterne (chaine_1));
      do
      { chaine_1 = va_arg(ap, char *);

        if (chaine_1 != 0)
        { *tampon += " \"";
          *tampon += TraduitVersExterne (chaine_1);
          *tampon += "\"";
        }

      } while (chaine_1 != 0);
      break;

    case champ_inhibition_cible_soleil :
      return BaseErreurs::formate ("le senseur \"%s\" observe le soleil"
                                   " mais est inhibe par le soleil",
                                   ap);
      break;

    case champ_inhibition_cible_lune :
      return BaseErreurs::formate ("le senseur \"%s\" observe la lune"
                                   " mais est inhibe par la lune",
                                   ap);
      break;

    case champ_inhibition_cible_central :
      return BaseErreurs::formate ("le senseur \"%s\" observe le corps central"
                                   " mais est inhibe par le corps central",
                                   ap);
      break;

    case omega_neg :
      reel_1 = va_arg(ap, double);
      appliqueFormat (trad ("vitesse de rotation max negative ou nulle :"
                             " %f deg/s"),
                      tampon,
                      degres (reel_1));
      break;

    case seuil_neg :
      return BaseErreurs::formate ("seuil de convergence negatif ou nul : %f",
                                   ap);
      break;

    case tranches_neg :
      return BaseErreurs::formate ("nombre de tranches de dichotomie negatif"
                                   " ou nul : %d",
                                   ap);
      break;

    case pas_de_solution :
      return BaseErreurs::formate ("pas de solution aux consignes d'attitude",
                                   ap);
      break;

    case controlabilite :
      return BaseErreurs::formate ("attitude solution theorique incontrolable"
                                   " (senseur %s)",
                                   ap);
      break;

    case calage_interdit :
      return BaseErreurs::formate ("pas d'axe de calage de defini"
                                   " pour ce senseur",
                                   ap);
      break;

    case types_incompatibles :
      return BaseErreurs::formate ("types des senseurs \"%s\" et \"%s\""
                                   " incompatibles",
                                   ap);
      break;

    case consigne_interdite :
      chaine_1 = va_arg(ap, char *);
      chaine_2 = va_arg(ap, char *);
      appliqueFormat (trad ("les senseurs \"%s\" et \"%s\" ne peuvent"
                            " pas etre utilises en consigne simultanement"),
                      tampon, chaine_1, chaine_2);
      break;

    case genre_cardan_inconnu :
      chaine_1 = va_arg(ap, char *);
      appliqueFormat (trad ("genre non reconnu pour le senseur"
                            " d'angle de Cardan \"%s\"\n"
                            "genres connus :"),
                      tampon, chaine_1);
      do
      { chaine_1 = va_arg(ap, char *);

        if (chaine_1 != 0)
        { *tampon += " \"";
          *tampon += TraduitVersExterne (chaine_1);
          *tampon += "\"";
        }

      } while (chaine_1 != 0);
      break;

    case reference_cardan_inconnue :
      chaine_1 = va_arg(ap, char *);
      appliqueFormat (trad ("repere non reconnu pour le senseur d'angle"
                            " de Cardan \"%s\"\nreperes connus :"),
                      tampon, chaine_1);
      do
      { chaine_1 = va_arg(ap, char *);

        if (chaine_1 != 0)
        { *tampon += " \"";
          *tampon += TraduitVersExterne (chaine_1);
          *tampon += "\"";
        }

      } while (chaine_1 != 0);
      break;

    case rotation_cardan :
      return BaseErreurs::formate ("probleme dans la mise a jour"
                                   " du repere de reference du senseur \"%s\")",
                                   ap);
      break;

    case points_masque :
      return BaseErreurs::formate ("nombre de points de masque incorrect"
                                   " (%d points, bloc \"%s\")",
                                   ap);
      break;

    case unite_position :
      chaine_1 = va_arg(ap, char *);
      appliqueFormat (trad ("unite de position inconnue : \"%s\"\n"
                            "unites connues :"),
                      tampon, TraduitVersExterne (chaine_1));
      do
      { chaine_1 = va_arg(ap, char *);

        if (chaine_1 != 0)
        { *tampon += " \"";
          *tampon += TraduitVersExterne (chaine_1);
          *tampon += "\"";
        }

      } while (chaine_1 != 0);
      break;

    case unite_vitesse :
      chaine_1 = va_arg(ap, char *);
      appliqueFormat (trad ("unite de vitesse inconnue : \"%s\"\n"
                            "unites connues :"),
                      tampon, TraduitVersExterne (chaine_1));
      do
      { chaine_1 = va_arg(ap, char *);

        if (chaine_1 != 0)
        { *tampon += " \"";
          *tampon += TraduitVersExterne (chaine_1);
          *tampon += "\"";
        }

      } while (chaine_1 != 0);
      break;

    case normes_litigieuses :
      return BaseErreurs::formate ("la norme des vecteurs position/vitesse est"
                                   " temporairement litigieuse et ne doit pas"
                                   " etre utilisee",
                                   ap);
      break;

    case cible_utilisateur :
      return BaseErreurs::formate ("cible du senseur \"%s\" non initialisee",
                                   ap);
      break;

    case modifie_cible :
      return BaseErreurs::formate ("la cible du senseur \"%s\""
                                   " n'est pas modifiable", ap);
      break;

    case senseur_sans_cible :
      return BaseErreurs::formate ("\"%s\" n'est pas un senseur optique,"
                                   " initialisation de la cible impossible",
                                   ap);
      break;

    case pas_gyro_integrateur :
      return BaseErreurs::formate ("\"%s\" n'est pas un gyrometre integrateur,"
                                   " initialisation impossible", ap);
      break;

    case reference_utilisateur :
      return BaseErreurs::formate ("repere de reference du senseur \"%s\""
                                   " non initialise", ap);
      break;

    case modifie_reference :
      return BaseErreurs::formate ("le repere de reference du senseur \"%s\""
                                   " n'est pas modifiable", ap);
      break;

    case senseur_sans_reference :
      return BaseErreurs::formate ("\"%s\" n'est pas un senseur de Cardan,"
                                   " initialisation du repere de"
                                   " reference impossible", ap);
      break;

    case erreur_non_reconnue :
      return BaseErreurs::formate ("erreur non reconnue", ap);
      break;

    case senseur_mesure_pure :
      return BaseErreurs::formate ("le senseur \"%s\" ne peut etre utilise"
                                   " qu'en mesure, pas en consigne", ap);
      break;

    case allocation_memoire :
      return BaseErreurs::formate ("erreur d'allocation memoire", ap);
      break;

    case points_echantillon :
      return BaseErreurs::formate ("nombre de points d'echantillonnage incorrect"
                                   " (%d points, bloc \"%s\")",
                                   ap);
      break;

    case echantillon_vide :
      return BaseErreurs::formate ("echantillon vide (bloc \"%s\")",
                                   ap);
      break;

    case echantillon_rejete :
      return BaseErreurs::formate ("point echantillon (%f, %f) hors bornes (bloc \"%s\")",
                                   ap);
      break;

    case objet_inconnu :
      return BaseErreurs::formate ("reference a un objet inconnu dans le trace",
                                   ap);
      break;

    case cas_impossible :
      return BaseErreurs::formate ("erreur interne de MARMOTTES,"
                                   " veuillez contacter la maintenance"
                                   " (ligne %d, fichier %s)", ap);
      break;

    case pas_senseur_cinematique :
      return BaseErreurs::formate ("\"%s\" n'est pas un senseur cinematique,"
                                   " initialisation de la derive impossible", ap);
      break;

    default :
      return BaseErreurs::formate (code, ap);
      break;

  }

  // retour du message formaté
  return *tampon;

}

MarmottesErreurs::MarmottesErreurs (int code ...)
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

MarmottesErreurs::MarmottesErreurs (const char* format ...)
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

MarmottesErreurs& MarmottesErreurs::operator = (const MarmottesErreurs& e)
{ if (this != &e)     // protection contre x = x
  { 
    BaseErreurs::operator = (e);
  }

  return *this;

}

int MarmottesErreurs::erreur (MarmottesErreurs* ptr, int code ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, code);

  // gestion de l'erreur sans argument variable
  if (ptr != 0)
  { ptr->stockeCode (code);
    ptr->stockeMessage (ptr->formate (code, ap));
  }
  else
  { MarmottesErreurs err;
    err.stockeCode (code);
    err.stockeMessage (err.formate (code, ap));

    if (BaseErreurs::exceptions ())
#ifdef AVEC_EXCEPTIONS
      throw err;
#else
    { err.affiche    ();
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

int MarmottesErreurs::erreur (MarmottesErreurs* ptr, const char* format ...)
{ va_list    ap;

  // initialisation du traitement des arguments variables
  va_start(ap, format);

  // gestion de l'erreur sans argument variable
  if (ptr != 0)
  { ptr->stockeCode (CodeInconnu);
    ptr->stockeMessage (ptr->BaseErreurs::formate (format, ap));
  }
  else
  { MarmottesErreurs err;
    err.stockeCode (CodeInconnu);
    err.stockeMessage (err.BaseErreurs::formate (format, ap));

    if (BaseErreurs::exceptions ())
#ifdef AVEC_EXCEPTIONS
      throw err;
#else
    { err.affiche    ();
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
